/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
#include "LongRunningTask.h"
using namespace Helix::Glob;

#include "GetAllLRTasks.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "LRTask.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetAllLRTasks> GetAllLRTasks::reg("GetAllLRTasks", 1, "/logic/util/GetAllLRTasks");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetAllLRTasks Input=NULL

GetAllLRTasks::GetAllLRTasks(xmlNodePtr action)
{
	EnEx ee(FL, "GetAllLRTasks::GetAllLRTasks(xmlNodePtr action)");
	
}

GetAllLRTasks::GetAllLRTasks(const GetAllLRTasks& c)
{
	EnEx ee(FL, "GetAllLRTasks::GetAllLRTasks(const GetAllLRTasks& c)");

}

GetAllLRTasks& GetAllLRTasks::operator=(const GetAllLRTasks& c)
{
	EnEx ee(FL, "GetAllLRTasks::operator=(const GetAllLRTasks& c)");

	return *this;
}

GetAllLRTasks::~GetAllLRTasks()
{
	EnEx ee(FL, "GetAllLRTasks::~GetAllLRTasks()");

}

void GetAllLRTasks::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetAllLRTasks::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetAllLRTasks");

	LongRunningTask::getInstance().describeTasks( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
