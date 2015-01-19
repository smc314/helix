/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetScheduleItems.h"
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
ActionClassRegister<GetScheduleItems> GetScheduleItems::reg("GetScheduleItems", 1, "/logic/admin/GetScheduleItems");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetScheduleItems Input=NULL

GetScheduleItems::GetScheduleItems(xmlNodePtr action)
{
	EnEx ee(FL, "GetScheduleItems::GetScheduleItems(xmlNodePtr action)");
	
}

GetScheduleItems::GetScheduleItems(const GetScheduleItems& c)
{
	EnEx ee(FL, "GetScheduleItems::GetScheduleItems(const GetScheduleItems& c)");

}

GetScheduleItems& GetScheduleItems::operator=(const GetScheduleItems& c)
{
	EnEx ee(FL, "GetScheduleItems::operator=(const GetScheduleItems& c)");

	return *this;
}

GetScheduleItems::~GetScheduleItems()
{
	EnEx ee(FL, "GetScheduleItems::~GetScheduleItems()");

}

bool GetScheduleItems::isLongRunning()
{
	EnEx ee(FL, "GetScheduleItems::isLongRunning()");

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

twine GetScheduleItems::lrTaskName()
{
	EnEx ee(FL, "GetScheduleItems::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetScheduleItems Request";
}


void GetScheduleItems::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetScheduleItems::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetScheduleItems");

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixconfig" );
	
	SchedItem_svect vect = SchedItem::selectAll( sqldb );

	SchedItem::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
