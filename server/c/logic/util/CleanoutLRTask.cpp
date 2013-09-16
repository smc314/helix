/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
#include "LongRunningTask.h"
using namespace Helix::Glob;

#include "CleanoutLRTask.h"
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
ActionClassRegister<CleanoutLRTask> CleanoutLRTask::reg("CleanoutLRTask", 1, "/logic/util/CleanoutLRTask");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/CleanoutLRTask Input=LRTask

CleanoutLRTask::CleanoutLRTask(xmlNodePtr action)
{
	EnEx ee(FL, "CleanoutLRTask::CleanoutLRTask(xmlNodePtr action)");
	
}

CleanoutLRTask::CleanoutLRTask(const CleanoutLRTask& c)
{
	EnEx ee(FL, "CleanoutLRTask::CleanoutLRTask(const CleanoutLRTask& c)");

}

CleanoutLRTask& CleanoutLRTask::operator=(const CleanoutLRTask& c)
{
	EnEx ee(FL, "CleanoutLRTask::operator=(const CleanoutLRTask& c)");

	return *this;
}

CleanoutLRTask::~CleanoutLRTask()
{
	EnEx ee(FL, "CleanoutLRTask::~CleanoutLRTask()");

}

void CleanoutLRTask::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "CleanoutLRTask::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("CleanoutLRTask");

	LRTask local( XmlHelpers::FindChild( ioc.GetRequestRoot(), LRTask::Name()() ) );
	LongRunningTask::getInstance().removeTask( local.TaskID );

	LongRunningTask::getInstance().describeTasks( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
