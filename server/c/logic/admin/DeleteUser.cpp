/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "DeleteUser.h"
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
ActionClassRegister<DeleteUser> DeleteUser::reg("DeleteUser", 1, "/logic/admin/DeleteUser");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/DeleteUser Input=User

DeleteUser::DeleteUser(xmlNodePtr action)
{
	EnEx ee(FL, "DeleteUser::DeleteUser(xmlNodePtr action)");
	
}

DeleteUser::DeleteUser(const DeleteUser& c)
{
	EnEx ee(FL, "DeleteUser::DeleteUser(const DeleteUser& c)");

}

DeleteUser& DeleteUser::operator=(const DeleteUser& c)
{
	EnEx ee(FL, "DeleteUser::operator=(const DeleteUser& c)");

	return *this;
}

DeleteUser::~DeleteUser()
{
	EnEx ee(FL, "DeleteUser::~DeleteUser()");

}

bool DeleteUser::isLongRunning()
{
	EnEx ee(FL, "DeleteUser::isLongRunning()");

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

twine DeleteUser::lrTaskName()
{
	EnEx ee(FL, "DeleteUser::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "DeleteUser Request";
}


void DeleteUser::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "DeleteUser::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("DeleteUser");

	// Pick up the input object from the request document
	User local( XmlHelpers::FindChild( ioc.GetRequestRoot(), User::Name()() ) );

	// Read from our configuration database - change this to get data from elsewhere
	SqlDB& db = TheMain::getInstance()->GetConfigDB( );

	// Example of a doing this through an odbc connection
	// OdbcObj& db = *ioc.getDBConnection();

	// Start a transaction in case we need to handle delete's of multiple records
	SqlDBTransaction trans(db); // Transaction will be rolled back when this object goes out of scope

	// Example of doing a transaction through an odbc connection
	// Transaction trans(db); // Transaction will be rolled back when this object goes out of scope

	// Delete the requested object - adjust this to use the correct inputs and delete call
	User::deleteByID( db, local.id );

	// Delete any other related records here
	User::deleteAuthByID( db, local.id );
	UserGroup::deleteGroupsForUser( db, local.id);
	User::deleteActionsForUser( db, local.id);

	// Commit the transaction:
	trans.Commit();

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
