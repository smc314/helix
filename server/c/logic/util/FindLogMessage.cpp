/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "FindLogMessage.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <Date.h>
#include <AnException.h>
#include <XmlHelpers.h>
#include <LogFile2.h>
using namespace SLib;

// Include local data objects here
#include "LogMessageFilter.h"
#include "GetLogMessages.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<FindLogMessage> FindLogMessage::reg("FindLogMessage", 1, "/logic/util/FindLogMessage");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/FindLogMessage Input=LogMessageFilter

FindLogMessage::FindLogMessage(xmlNodePtr action)
{
	EnEx ee(FL, "FindLogMessage::FindLogMessage(xmlNodePtr action)");
	
}

FindLogMessage::FindLogMessage(const FindLogMessage& c)
{
	EnEx ee(FL, "FindLogMessage::FindLogMessage(const FindLogMessage& c)");

}

FindLogMessage& FindLogMessage::operator=(const FindLogMessage& c)
{
	EnEx ee(FL, "FindLogMessage::operator=(const FindLogMessage& c)");

	return *this;
}

FindLogMessage::~FindLogMessage()
{
	EnEx ee(FL, "FindLogMessage::~FindLogMessage()");

}

bool FindLogMessage::isLongRunning()
{
	EnEx ee(FL, "FindLogMessage::isLongRunning()");

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

twine FindLogMessage::lrTaskName()
{
	EnEx ee(FL, "FindLogMessage::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "FindLogMessage Request";
}


void FindLogMessage::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "FindLogMessage::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("FindLogMessage");

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

	twine whereClause = GetLogMessages::BuildFilter( local );
	// What are they searching for:
	if(local.FindByID != 0){
		// Our log file always re-starts with ID = 1 at the beginning.  This means
		// rowid = id.
		local.FirstRow = local.FindByID;

		// Send it right back immediately.
		local.createXmlNode( ioc.getResponseRoot() );
		ioc.SendReturn();
		ioc.Close();
		return;
	} 
	
	// Find by date or find by message actually requires a query:
	if (local.FindByDate.length() != 0){
		// Convert this to a date we can compare with:
		Date targetDate; targetDate.SetValue( local.FindByDate );
		DEBUG(FL, "Looking for first log message with date (%s) (%d)", 
			targetDate.GetValue(), (int)(time_t)targetDate );
		
		if(whereClause.length() == 0){
			whereClause.format("where timestamp_a = %d", (int)(time_t)targetDate );
		} else {
			twine tmp; tmp.format(" and timestamp_a = %d ", (int)(time_t)targetDate );
			whereClause.append( tmp );
		}
	} else if( local.FindByMsg.length() != 0){
		local.Message = local.FindByMsg;
		// rebuild the where clause:
		whereClause = GetLogMessages::BuildFilter( local );
	}

	dptr<vector<LogMsg*> > messages = ourLogFile->getMessages( whereClause, 1, 0 );
	if(messages->size() != 0){
		local.FirstRow = messages->at(0)->id;
		delete messages->at(0);
	} else {
		local.FirstRow = ourLogFile->getOldestMessageID();
	}

	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
