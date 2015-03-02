/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetUsers.h"
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
#include "User.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetUsers> GetUsers::reg("GetUsers", 1, "/logic/admin/GetUsers");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetUsers Input=NULL

GetUsers::GetUsers(xmlNodePtr action)
{
	EnEx ee(FL, "GetUsers::GetUsers(xmlNodePtr action)");
	
}

GetUsers::GetUsers(const GetUsers& c)
{
	EnEx ee(FL, "GetUsers::GetUsers(const GetUsers& c)");

}

GetUsers& GetUsers::operator=(const GetUsers& c)
{
	EnEx ee(FL, "GetUsers::operator=(const GetUsers& c)");

	return *this;
}

GetUsers::~GetUsers()
{
	EnEx ee(FL, "GetUsers::~GetUsers()");

}

bool GetUsers::isLongRunning()
{
	EnEx ee(FL, "GetUsers::isLongRunning()");

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

twine GetUsers::lrTaskName()
{
	EnEx ee(FL, "GetUsers::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetUsers Request";
}


void GetUsers::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetUsers::ExecuteRequest(IOConn& ioc)", true);

	// Example of accessing a local configuration database
	SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
	User_svect vect = User::selectAll( sqldb );

	User::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
