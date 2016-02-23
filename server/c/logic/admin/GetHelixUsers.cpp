/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetHelixUsers.h"
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
#include "HelixUser.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetHelixUsers> GetHelixUsers::reg("GetHelixUsers", 1, "/logic/admin/GetHelixUsers");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetHelixUsers Input=NULL

GetHelixUsers::GetHelixUsers(xmlNodePtr action)
{
	EnEx ee(FL, "GetHelixUsers::GetHelixUsers(xmlNodePtr action)");
	
}

GetHelixUsers::GetHelixUsers(const GetHelixUsers& c)
{
	EnEx ee(FL, "GetHelixUsers::GetHelixUsers(const GetHelixUsers& c)");

}

GetHelixUsers& GetHelixUsers::operator=(const GetHelixUsers& c)
{
	EnEx ee(FL, "GetHelixUsers::operator=(const GetHelixUsers& c)");

	return *this;
}

GetHelixUsers::~GetHelixUsers()
{
	EnEx ee(FL, "GetHelixUsers::~GetHelixUsers()");

}

bool GetHelixUsers::isLongRunning()
{
	EnEx ee(FL, "GetHelixUsers::isLongRunning()");

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

twine GetHelixUsers::lrTaskName()
{
	EnEx ee(FL, "GetHelixUsers::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetHelixUsers Request";
}


void GetHelixUsers::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetHelixUsers::ExecuteRequest(IOConn& ioc)", true);

	// Example of accessing a local configuration database
	SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
	HelixUser_svect vect = HelixUser::selectAll( sqldb );

	HelixUser::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
