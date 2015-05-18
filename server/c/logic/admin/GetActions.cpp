/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetActions.h"
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
#include "Action.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetActions> GetActions::reg("GetActions", 1, "/logic/admin/GetActions");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetActions Input=NULL

GetActions::GetActions(xmlNodePtr action)
{
	EnEx ee(FL, "GetActions::GetActions(xmlNodePtr action)");
	
}

GetActions::GetActions(const GetActions& c)
{
	EnEx ee(FL, "GetActions::GetActions(const GetActions& c)");

}

GetActions& GetActions::operator=(const GetActions& c)
{
	EnEx ee(FL, "GetActions::operator=(const GetActions& c)");

	return *this;
}

GetActions::~GetActions()
{
	EnEx ee(FL, "GetActions::~GetActions()");

}

bool GetActions::isLongRunning()
{
	EnEx ee(FL, "GetActions::isLongRunning()");

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

twine GetActions::lrTaskName()
{
	EnEx ee(FL, "GetActions::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetActions Request";
}


void GetActions::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetActions::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetActions");

	SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
	Action_svect vect = Action::selectAll( sqldb );

	Action::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
