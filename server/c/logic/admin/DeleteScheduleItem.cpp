/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "DeleteScheduleItem.h"
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
ActionClassRegister<DeleteScheduleItem> DeleteScheduleItem::reg("DeleteScheduleItem", 1, "/logic/admin/DeleteScheduleItem");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/DeleteScheduleItem Input=SchedItem

DeleteScheduleItem::DeleteScheduleItem(xmlNodePtr action)
{
	EnEx ee(FL, "DeleteScheduleItem::DeleteScheduleItem(xmlNodePtr action)");
	
}

DeleteScheduleItem::DeleteScheduleItem(const DeleteScheduleItem& c)
{
	EnEx ee(FL, "DeleteScheduleItem::DeleteScheduleItem(const DeleteScheduleItem& c)");

}

DeleteScheduleItem& DeleteScheduleItem::operator=(const DeleteScheduleItem& c)
{
	EnEx ee(FL, "DeleteScheduleItem::operator=(const DeleteScheduleItem& c)");

	return *this;
}

DeleteScheduleItem::~DeleteScheduleItem()
{
	EnEx ee(FL, "DeleteScheduleItem::~DeleteScheduleItem()");

}

bool DeleteScheduleItem::isLongRunning()
{
	EnEx ee(FL, "DeleteScheduleItem::isLongRunning()");

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

twine DeleteScheduleItem::lrTaskName()
{
	EnEx ee(FL, "DeleteScheduleItem::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "DeleteScheduleItem Request";
}


void DeleteScheduleItem::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "DeleteScheduleItem::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("DeleteScheduleItem");

	SchedItem local( XmlHelpers::FindChild( ioc.GetRequestRoot(), SchedItem::Name()() ) );

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixconfig" );
	
	SchedItem::deleteByID( sqldb, local.id );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
