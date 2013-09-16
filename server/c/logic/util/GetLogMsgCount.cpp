/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetLogMsgCount.h"
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
ActionClassRegister<GetLogMsgCount> GetLogMsgCount::reg("GetLogMsgCount", 1, "/logic/util/GetLogMsgCount");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetLogMsgCount Input=LogMessageFilter

GetLogMsgCount::GetLogMsgCount(xmlNodePtr action)
{
	EnEx ee(FL, "GetLogMsgCount::GetLogMsgCount(xmlNodePtr action)");
	
}

GetLogMsgCount::GetLogMsgCount(const GetLogMsgCount& c)
{
	EnEx ee(FL, "GetLogMsgCount::GetLogMsgCount(const GetLogMsgCount& c)");

}

GetLogMsgCount& GetLogMsgCount::operator=(const GetLogMsgCount& c)
{
	EnEx ee(FL, "GetLogMsgCount::operator=(const GetLogMsgCount& c)");

	return *this;
}

GetLogMsgCount::~GetLogMsgCount()
{
	EnEx ee(FL, "GetLogMsgCount::~GetLogMsgCount()");

}

bool GetLogMsgCount::isLongRunning()
{
	EnEx ee(FL, "GetLogMsgCount::isLongRunning()");

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

twine GetLogMsgCount::lrTaskName()
{
	EnEx ee(FL, "GetLogMsgCount::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetLogMsgCount Request";
}


void GetLogMsgCount::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetLogMsgCount::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetLogMsgCount");

	LogMessageFilter local( XmlHelpers::FindChild( ioc.GetRequestRoot(), LogMessageFilter::Name()() ) );
	GetLogMessages::SaveLogFilters( ioc, local );

	// Which log file are we going to read?
	LogFile2* ourLogFile = NULL;
	dptr<LogFile2> logSptr;
	if(local.LogFile.length() == 0){
		LogFile2& lf = TheMain::getInstance()->GetAdaptiveLogs().LogFile();
		ourLogFile = &lf;
	} else {
		// Open it up:
		ourLogFile = new LogFile2(local.LogFile);
		logSptr = ourLogFile; // ensure this goes away when we are done.
	}

	local.LogFileOldestID = ourLogFile->getOldestMessageID();
	local.LogFileNewestID = ourLogFile->getNewestMessageID();

	// Check to see if we have an empty filter:
	if( GetLogMessages::isFilterEmpty(local) ){
		// We have an empty filter.  Set the record count to Newest - Oldest + 1;
		local.FilterMatchCount = local.LogFileNewestID - local.LogFileOldestID + 1;
	} else {
		// We have a non-empty filter.  We have to walk the log file and count everything
		// that matches.
		local.FilterMatchCount = ourLogFile->messageCount( GetLogMessages::BuildFilter( local ) );
	}

	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
