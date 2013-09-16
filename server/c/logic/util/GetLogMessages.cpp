/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetLogMessages.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
#include <LogFile2.h>
using namespace SLib;

// Include local data objects here
#include "LogMessageFilter.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetLogMessages> GetLogMessages::reg("GetLogMessages", 1, "/logic/util/GetLogMessages");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetLogMessages Input=LogMessageFilter

GetLogMessages::GetLogMessages(xmlNodePtr action)
{
	EnEx ee(FL, "GetLogMessages::GetLogMessages(xmlNodePtr action)");
	
}

GetLogMessages::GetLogMessages(const GetLogMessages& c)
{
	EnEx ee(FL, "GetLogMessages::GetLogMessages(const GetLogMessages& c)");

}

GetLogMessages& GetLogMessages::operator=(const GetLogMessages& c)
{
	EnEx ee(FL, "GetLogMessages::operator=(const GetLogMessages& c)");

	return *this;
}

GetLogMessages::~GetLogMessages()
{

}

void GetLogMessages::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetLogMessages::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetLogMessages");

	// Pull up our input document and convert it into an object we can use:
	LogMessageFilter local( XmlHelpers::FindChild(ioc.GetRequestRoot(), LogMessageFilter::Name()()) );

	SaveLogFilters(ioc, local);

	// Which log file are we going to read?
	LogFile2* ourLogFile = NULL;
	dptr<LogFile2> logSptr;
	if(local.LogFile.length() == 0){
		ourLogFile = &TheMain::getInstance()->GetAdaptiveLogs().LogFile();
	} else {
		ourLogFile = new LogFile2(local.LogFile);
		logSptr = ourLogFile; // ensure this goes away when we are done.
	}
	if(local.GetMax <= 0 || local.GetMax > 1000){
		local.GetMax = 50; // Sensible default
	}

	LogObj_svect vect = new vector<LogObj*>();

	// Open it up:
	if(local.StartId == -1 || local.StartId >= ourLogFile->getNewestMessageID() ){
		local.StartId = ourLogFile->getNewestMessageID();
		local.Forward = -1;
	} else if(local.StartId <= ourLogFile->getOldestMessageID()){
		local.StartId = ourLogFile->getOldestMessageID();
		local.Forward = 1;
	}

	if(local.Forward == -1){
		// walk backward in the file
		while( (int)vect->size() < local.GetMax && local.StartId >= ourLogFile->getOldestMessageID() && local.StartId > 0){
			dptr<LogMsg> lm = ourLogFile->getMessage( local.StartId-- );
			if(lm == NULL) continue; // bad log message
			if(MatchesFilter(lm, local)){
				// add this to the beginning of the vector:
				vect->insert( vect->begin(), CreateLogObj(lm) );
			}
		}
	} else {
		// Start at StartId and walk forward until we hit GetMax or the end of the file
		while( (int)vect->size() < local.GetMax && local.StartId <= ourLogFile->getNewestMessageID() ){
			dptr<LogMsg> lm = ourLogFile->getMessage( local.StartId++ );
			if(lm == NULL) continue; // bad log message
			if(MatchesFilter(lm, local)){
				// add this to the end of the vector:
				vect->push_back( CreateLogObj(lm) );
			}
		}
	}

	// Now add all of the log messages we found to the response message
	xmlNodePtr resp = ioc.getResponseRoot();
	LogObj::createXmlChildren( resp, vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}

LogObj* GetLogMessages::CreateLogObj(LogMsg* lm)
{
	EnEx ee(FL, "GetLogMessages::CreateLogObj(LogMsg* lm)");
	
	// Create the Log Object:
	LogObj* lo = new LogObj();
	lo->id = lm->id;
	lo->file = lm->file;
	lo->line = lm->line;
	lo->tid = (size_t)lm->tid;
	lo->timestamp_c = lm->GetTimestamp();
	lo->channel = lm->channel;
	lo->appName = lm->appName;
	lo->SUID= lm->appSession;
	lo->machineName = lm->machineName;
	lo->msg = lm->msg;

	return lo;

}
				

twine GetLogMessages::GetCurrentLogFileName()
{
	EnEx ee(FL, "GetLogMessages::GetCurrentLogFileName()");

	xmlNodePtr root = xmlDocGetRootElement(TheMain::getInstance()->GetConfig() );
	xmlNodePtr log = XmlHelpers::FindChild(root, "AdaptiveLogs");
	twine logName(log, "filename");

	return logName;
}

bool GetLogMessages::isFilterEmpty(LogMessageFilter& filter)
{
	EnEx ee(FL, "GetLogMessages::isFilterEmpty(LogMessageFilter& filter)");

	if(filter.MachineName.length() == 0 &&
		filter.AppName.length() == 0 &&
		filter.ThreadID == 0 &&
		filter.SUID.length() == 0 &&
		filter.Message.length() == 0 &&
		filter.Panic == 1 &&
		filter.Error == 1 &&
		filter.Warn == 1 &&
		filter.Info == 1 &&
		filter.Debug == 1 &&
		filter.Trace == 1 &&
		filter.SqlTrace == 1
	) {
		return true; // filter is empty
	} else {
		return false; // filter has something in it
	}

}

twine GetLogMessages::BuildFilter(LogMessageFilter& filter)
{
	EnEx ee(FL, "GetLogMessages::BuildFilter(LogMessageFilter& filter)");

	twine whereClause;
	twine channelCol;
	twine threadCol;
	twine suidCol;
	twine machineCol;
	twine appCol;
	twine msgCol;

	// Include the channel settings:
	if(filter.Panic && filter.Error && filter.Warn && filter.Info && filter.Debug && filter.Trace &&
		filter.SqlTrace
	){ 
		// They are all on - don't include a channel filter at all
	} else {
		twine cList;
		if(filter.Panic) if(cList.size() != 0) cList.append(", 0"); else cList.append("0");
		if(filter.Error) if(cList.size() != 0) cList.append(", 1"); else cList.append("1");
		if(filter.Warn) if(cList.size() != 0) cList.append(", 2"); else cList.append("2");
		if(filter.Info) if(cList.size() != 0) cList.append(", 3"); else cList.append("3");
		if(filter.Debug) if(cList.size() != 0) cList.append(", 4"); else cList.append("4");
		if(filter.Trace) if(cList.size() != 0) cList.append(", 5"); else cList.append("5");
		if(filter.SqlTrace) if(cList.size() != 0) cList.append(", 6"); else cList.append("6");

		channelCol.append( " channel in (" + cList + ") " );
	}

	if(filter.ThreadID != 0){
		threadCol.format(" tid = %d ", (int)filter.ThreadID );
	}

	if(filter.SUID.length() != 0){
		suidCol.format(" appSession = '%s' ", filter.SUID() );
	}

	if(filter.MachineName.length() != 0){
		machineCol.format(" machineName like '%%%s%%' ", filter.MachineName() );
	}

	if(filter.AppName.length() != 0){
		appCol.format(" appName like '%%%s%%' ", filter.AppName() );
	}

	if(filter.Message.length() != 0){
		msgCol.format(" msg like '%%%s%%' ", filter.Message() );
	}

	if(channelCol.size() != 0) {
		if(whereClause.size() != 0) {
			whereClause.append( " and " + channelCol );
		} else {
			whereClause.append( "where " + channelCol );
		}
	}	
	if(threadCol.size() != 0) {
		if(whereClause.size() != 0) {
			whereClause.append( " and " + threadCol );
		} else {
			whereClause.append( "where " + threadCol );
		}
	}	
	if(suidCol.size() != 0) {
		if(whereClause.size() != 0) {
			whereClause.append( " and " + suidCol );
		} else {
			whereClause.append( "where " + suidCol );
		}
	}	
	if(machineCol.size() != 0) {
		if(whereClause.size() != 0) {
			whereClause.append( " and " + machineCol );
		} else {
			whereClause.append( "where " + machineCol );
		}
	}	
	if(appCol.size() != 0) {
		if(whereClause.size() != 0) {
			whereClause.append( " and " + appCol );
		} else {
			whereClause.append( "where " + appCol );
		}
	}	
	if(msgCol.size() != 0) {
		if(whereClause.size() != 0) {
			whereClause.append( " and " + msgCol );
		} else {
			whereClause.append( "where " + msgCol );
		}
	}	

	DEBUG(FL, "Where clause filter: '%s'", whereClause() );

	return whereClause;
}
	

bool GetLogMessages::MatchesFilter(LogMsg* lm, LogMessageFilter& filter)
{
	EnEx ee(FL, "GetLogMessages::MatchesFilter(LogMsg* lm, LogMessageFilter& filter)");

	// Do the fast filters first:
	if(filter.Panic == 0 && lm->channel == 0) return false; // doesn't match
	if(filter.Error == 0 && lm->channel == 1) return false; // doesn't match
	if(filter.Warn == 0 && lm->channel == 2) return false; // doesn't match
	if(filter.Info == 0 && lm->channel == 3) return false; // doesn't match
	if(filter.Debug == 0 && lm->channel == 4) return false; // doesn't match
	if(filter.Trace == 0 && lm->channel == 5) return false; // doesn't match
	if(filter.SqlTrace == 0 && lm->channel == 6) return false; // doesn't match

	// These take a bit more time each
	if(filter.ThreadID != 0 && lm->tid != filter.ThreadID){
		return false; // doesn't match the given thread ID filter
	}

	if(filter.SUID.length() != 0 && lm->appSession != filter.SUID ){
		return false; // doesn't match the given suid ID filter
	}

	if(filter.MachineName.length() != 0 && 
		lm->machineName.find( filter.MachineName ) == TWINE_NOT_FOUND
	){
		return false; // doesn't match the given machine name filter
	}

	if(filter.AppName.length() != 0 && 
		lm->appName.find( filter.AppName ) == TWINE_NOT_FOUND
	){
		return false; // doesn't match the given application name filter
	}

	if(filter.Message.length() != 0 && 
		lm->msg.find( filter.Message ) == TWINE_NOT_FOUND
	){
		return false; // doesn't match the given message filter
	}

	// If all of that goes through, then we've matched the filter
	return true;

}

void GetLogMessages::SaveLogFilters(IOConn& ioc, LogMessageFilter& filter)
{
	EnEx ee(FL, "GetLogMessages::SaveLogFilters(IOConn& ioc, LogMessageFilter& filter)");

	SessionInfo& si = ioc.getSessionInfo();
	twine tmp;
	si.userProperties[ "LogMessageFilter.LogFile" ] = filter.LogFile;
	tmp = filter.GetMax;
	si.userProperties[ "LogMessageFilter.GetMax" ] = tmp;
	si.userProperties[ "LogMessageFilter.MachineName" ] = filter.MachineName;
	si.userProperties[ "LogMessageFilter.AppName" ] = filter.AppName;
	tmp = filter.ThreadID;
	si.userProperties[ "LogMessageFilter.ThreadID" ] = tmp;
	si.userProperties[ "LogMessageFilter.SUID" ] = filter.SUID;
	si.userProperties[ "LogMessageFilter.Message" ] = filter.Message;
	tmp = filter.Panic;
	si.userProperties[ "LogMessageFilter.Panic" ] = tmp;
	tmp = filter.Error;
	si.userProperties[ "LogMessageFilter.Error" ] = tmp;
	tmp = filter.Warn;
	si.userProperties[ "LogMessageFilter.Warn" ] = tmp;
	tmp = filter.Info;
	si.userProperties[ "LogMessageFilter.Info" ] = tmp;
	tmp = filter.Debug;
	si.userProperties[ "LogMessageFilter.Debug" ] = tmp;
	tmp = filter.Trace;
	si.userProperties[ "LogMessageFilter.Trace" ] = tmp;
	tmp = filter.SqlTrace;
	si.userProperties[ "LogMessageFilter.SqlTrace" ] = tmp;
	tmp = filter.ShowColIcon;
	si.userProperties[ "LogMessageFilter.ShowColIcon" ] = tmp;
	tmp = filter.ShowColID;
	si.userProperties[ "LogMessageFilter.ShowColID" ] = tmp;
	tmp = filter.ShowColDate;
	si.userProperties[ "LogMessageFilter.ShowColDate" ] = tmp;
	tmp = filter.ShowColMachine;
	si.userProperties[ "LogMessageFilter.ShowColMachine" ] = tmp;
	tmp = filter.ShowColApplication;
	si.userProperties[ "LogMessageFilter.ShowColApplication" ] = tmp;
	tmp = filter.ShowColThread;
	si.userProperties[ "LogMessageFilter.ShowColThread" ] = tmp;
	tmp = filter.ShowColSUID;
	si.userProperties[ "LogMessageFilter.ShowColSUID" ] = tmp;
	tmp = filter.ShowColFile;
	si.userProperties[ "LogMessageFilter.ShowColFile" ] = tmp;
	tmp = filter.ShowColLine;
	si.userProperties[ "LogMessageFilter.ShowColLine" ] = tmp;
	tmp = filter.ShowColChannel;
	si.userProperties[ "LogMessageFilter.ShowColChannel" ] = tmp;
	tmp = filter.ShowColMessage;
	si.userProperties[ "LogMessageFilter.ShowColMessage" ] = tmp;

	si.Save();
}
