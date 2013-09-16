/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
#include "LongRunningTask.h"
using namespace Helix::Glob;

#include "GetOneLRTask.h"
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
ActionClassRegister<GetOneLRTask> GetOneLRTask::reg("GetOneLRTask", 1, "/logic/util/GetOneLRTask");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetOneLRTask Input=LRTask

GetOneLRTask::GetOneLRTask(xmlNodePtr action)
{
	EnEx ee(FL, "GetOneLRTask::GetOneLRTask(xmlNodePtr action)");
	
}

GetOneLRTask::GetOneLRTask(const GetOneLRTask& c)
{
	EnEx ee(FL, "GetOneLRTask::GetOneLRTask(const GetOneLRTask& c)");

}

GetOneLRTask& GetOneLRTask::operator=(const GetOneLRTask& c)
{
	EnEx ee(FL, "GetOneLRTask::operator=(const GetOneLRTask& c)");

	return *this;
}

GetOneLRTask::~GetOneLRTask()
{
	EnEx ee(FL, "GetOneLRTask::~GetOneLRTask()");

}

void GetOneLRTask::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetOneLRTask::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetOneLRTask");

	LRTask local( XmlHelpers::FindChild( ioc.GetRequestRoot(), LRTask::Name()() ) );

	LongRunningTask& lrt = LongRunningTask::getInstance();
	LRTask& task = lrt.getTask( local.TaskID );
	// Check to see if the task is finished:
	if(task.TaskCurrent != task.TaskFinish){
		// Not finished, just send a description of the task:
		lrt.describeTask( ioc.getResponseRoot(), local.TaskID );
	} else {
		// Task is finished.  Check for a TaskReturn document and use it as our return document.
		if(task.TaskResponse.length() != 0){
			ioc.initializeResponseDocument( 
				xmlParseMemory( task.TaskResponse(), task.TaskResponse.length() ) );
		} else {
			// No task return document.  Just keep returning the task description
			lrt.describeTask( ioc.getResponseRoot(), local.TaskID );
		}
	}

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
