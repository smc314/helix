/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetOneScheduleItem.h"
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
ActionClassRegister<GetOneScheduleItem> GetOneScheduleItem::reg("GetOneScheduleItem", 1, "/logic/admin/GetOneScheduleItem");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetOneScheduleItem Input=SchedItem

GetOneScheduleItem::GetOneScheduleItem(xmlNodePtr action)
{
	EnEx ee(FL, "GetOneScheduleItem::GetOneScheduleItem(xmlNodePtr action)");
	
}

GetOneScheduleItem::GetOneScheduleItem(const GetOneScheduleItem& c)
{
	EnEx ee(FL, "GetOneScheduleItem::GetOneScheduleItem(const GetOneScheduleItem& c)");

}

GetOneScheduleItem& GetOneScheduleItem::operator=(const GetOneScheduleItem& c)
{
	EnEx ee(FL, "GetOneScheduleItem::operator=(const GetOneScheduleItem& c)");

	return *this;
}

GetOneScheduleItem::~GetOneScheduleItem()
{
	EnEx ee(FL, "GetOneScheduleItem::~GetOneScheduleItem()");

}

bool GetOneScheduleItem::isLongRunning()
{
	EnEx ee(FL, "GetOneScheduleItem::isLongRunning()");

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

twine GetOneScheduleItem::lrTaskName()
{
	EnEx ee(FL, "GetOneScheduleItem::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetOneScheduleItem Request";
}


void GetOneScheduleItem::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetOneScheduleItem::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetOneScheduleItem");

	SchedItem local( XmlHelpers::FindChild( ioc.GetRequestRoot(), SchedItem::Name()() ) );
	SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
	
	SchedItem_svect vect = SchedItem::selectByID( sqldb, local.id );

	SchedItem::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
