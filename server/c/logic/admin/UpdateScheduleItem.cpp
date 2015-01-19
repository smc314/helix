/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
#include "Schedule.h"
using namespace Helix::Glob;

#include "UpdateScheduleItem.h"
using namespace Helix::Logic::admin;

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
#include "SchedItem.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<UpdateScheduleItem> UpdateScheduleItem::reg("UpdateScheduleItem", 1, 
	"/logic/admin/InsertScheduleItem",
	"/logic/admin/UpdateScheduleItem"
);

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/InsertScheduleItem Input=SchedItem
// LOGICCODEGEN API=/logic/admin/UpdateScheduleItem Input=SchedItem

UpdateScheduleItem::UpdateScheduleItem(xmlNodePtr action)
{
	EnEx ee(FL, "UpdateScheduleItem::UpdateScheduleItem(xmlNodePtr action)");
	
}

UpdateScheduleItem::UpdateScheduleItem(const UpdateScheduleItem& c)
{
	EnEx ee(FL, "UpdateScheduleItem::UpdateScheduleItem(const UpdateScheduleItem& c)");

}

UpdateScheduleItem& UpdateScheduleItem::operator=(const UpdateScheduleItem& c)
{
	EnEx ee(FL, "UpdateScheduleItem::operator=(const UpdateScheduleItem& c)");

	return *this;
}

UpdateScheduleItem::~UpdateScheduleItem()
{
	EnEx ee(FL, "UpdateScheduleItem::~UpdateScheduleItem()");

}

bool UpdateScheduleItem::isLongRunning()
{
	EnEx ee(FL, "UpdateScheduleItem::isLongRunning()");

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

twine UpdateScheduleItem::lrTaskName()
{
	EnEx ee(FL, "UpdateScheduleItem::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "UpdateScheduleItem Request";
}


void UpdateScheduleItem::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "UpdateScheduleItem::ExecuteRequest(IOConn& ioc)", true);

	// How were we called?
	bool doingInsert = false;
	if(strcmp((const char*)ioc.GetRequestRoot()->name, "InsertScheduleItem") == 0){
		doingInsert = true;
	}

	// Set up the response document name
	if(doingInsert){
		ioc.initializeResponseDocument("InsertScheduleItem");
	} else {
		ioc.initializeResponseDocument("UpdateScheduleItem");
	}

	SchedItem local( XmlHelpers::FindChild( ioc.GetRequestRoot(), SchedItem::Name()() ) );
	if(local.TaskName.empty()){
		throw AnException(0, FL, "ScheduleItem must have a valid Task Name.");
	}
	if(local.TaskUrl.empty()){
		throw AnException(0, FL, "ScheduleItem must have a valid Task URL.");
	}

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixconfig" );

	if(doingInsert){
		SchedItem::insert(sqldb, local);
	} else {
		SchedItem::update(sqldb, local.TaskName, local.TaskUrl, local.InputDocument, local.isActive, 
			local.runEvery, local.LastRun, local.useInterval, local.RunAtTime, local.dowSunday,
			local.dowMonday, local.dowTuesday, local.dowWednesday, local.dowThursday, local.dowFriday,
			local.dowSaturday, local.id );
	}

	// Reach out to the scheduler and tell it that some configuration items have changed
	Schedule::getInstance().LoadSchedule();	
	
	// Add the newly saved/updated object to the response document
	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
