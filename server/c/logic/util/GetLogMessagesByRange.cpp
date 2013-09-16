/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetLogMessagesByRange.h"
using namespace Helix::Logic::util;

#include "Statics.h"
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
#include "GetLogMessages.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetLogMessagesByRange> GetLogMessagesByRange::reg("GetLogMessagesByRange", 1, "/logic/util/GetLogMessagesByRange");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetLogMessagesByRange Input=LogMessageFilter

GetLogMessagesByRange::GetLogMessagesByRange(xmlNodePtr action)
{
	EnEx ee(FL, "GetLogMessagesByRange::GetLogMessagesByRange(xmlNodePtr action)");
	
}

GetLogMessagesByRange::GetLogMessagesByRange(const GetLogMessagesByRange& c)
{
	EnEx ee(FL, "GetLogMessagesByRange::GetLogMessagesByRange(const GetLogMessagesByRange& c)");

}

GetLogMessagesByRange& GetLogMessagesByRange::operator=(const GetLogMessagesByRange& c)
{
	EnEx ee(FL, "GetLogMessagesByRange::operator=(const GetLogMessagesByRange& c)");

	return *this;
}

GetLogMessagesByRange::~GetLogMessagesByRange()
{
	EnEx ee(FL, "GetLogMessagesByRange::~GetLogMessagesByRange()");

}

bool GetLogMessagesByRange::isLongRunning()
{
	EnEx ee(FL, "GetLogMessagesByRange::isLongRunning()");

	// If we are a long running transaction, we need to return true here.  This will trigger
	// special logic that causes an immediate return to the caller, and for us to be executed
	// via the internal server queue - rather than executed in-line on the http thread.

	// Most of the time our server logic classes are _NOT_ long running.  But in the rare
	// case when they are, simply return true here.
	// return true;

	// This is the default.  And in fact, if this method returns false, it's better to just
	// delete this whole method to save confusion.  Our super-class already returns false for us.
	return false;
}

twine GetLogMessagesByRange::lrTaskName()
{
	EnEx ee(FL, "GetLogMessagesByRange::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetLogMessagesByRange Request";
}


void GetLogMessagesByRange::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetLogMessagesByRange::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetLogMessagesByRange");

	LogMessageFilter local( XmlHelpers::FindChild( ioc.GetRequestRoot(), LogMessageFilter::Name()() ) );
	GetLogMessages::SaveLogFilters( ioc, local );

	// Which log file are we going to read?
	LogFile2* ourLogFile = NULL;
	dptr<LogFile2> logSptr;
	if(local.LogFile.length() == 0){
		ourLogFile = &TheMain::getInstance()->GetAdaptiveLogs().LogFile();
	} else {
		ourLogFile = new LogFile2( local.LogFile );
		logSptr = ourLogFile; // ensure this goes away when we are done.
	}

	// Open it up:
	local.LogFileOldestID = ourLogFile->getOldestMessageID();
	local.LogFileNewestID = ourLogFile->getNewestMessageID();

	// Our return data:
	LogObj_svect vect = new vector<LogObj*>();

	// Check to see if we have an empty filter:
	if( GetLogMessages::isFilterEmpty(local) ){
		// We can calculate the rows to return based on oldest and newest ID's
		int startID = ourLogFile->getOldestMessageID() + local.FirstRow;
		int endID = ourLogFile->getOldestMessageID() + local.LastRow;

		twine where; where.format("where id >= %d and id <= %d", startID, endID);
		dptr<vector<LogMsg*> > messages = ourLogFile->getMessages(where);

		for(size_t i = 0; i < messages->size(); i++){
			dptr<LogMsg> lm = messages->at( i ); // ensure it gets deleted
			vect->push_back( GetLogMessages::CreateLogObj( lm ) );
		}
	} else {
		// We have to use a filter query to pull up the messages that will match:
		dptr<vector<LogMsg*> > messages = ourLogFile->getMessages( GetLogMessages::BuildFilter(local),
			local.LastRow - local.FirstRow + 1, local.FirstRow - 1 );
		for(size_t i = 0; i < messages->size(); i++){
			dptr<LogMsg> lm = messages->at( i ); // ensure it gets deleted
			vect->push_back( GetLogMessages::CreateLogObj( lm ) );
		}
	}

	LogObj::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
