/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "DeleteGroup.h"
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
#include "Group.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<DeleteGroup> DeleteGroup::reg("DeleteGroup", 1, "/logic/admin/DeleteGroup");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/DeleteGroup Input=Group

DeleteGroup::DeleteGroup(xmlNodePtr action)
{
	EnEx ee(FL, "DeleteGroup::DeleteGroup(xmlNodePtr action)");
	
}

DeleteGroup::DeleteGroup(const DeleteGroup& c)
{
	EnEx ee(FL, "DeleteGroup::DeleteGroup(const DeleteGroup& c)");

}

DeleteGroup& DeleteGroup::operator=(const DeleteGroup& c)
{
	EnEx ee(FL, "DeleteGroup::operator=(const DeleteGroup& c)");

	return *this;
}

DeleteGroup::~DeleteGroup()
{
	EnEx ee(FL, "DeleteGroup::~DeleteGroup()");

}

bool DeleteGroup::isLongRunning()
{
	EnEx ee(FL, "DeleteGroup::isLongRunning()");

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

twine DeleteGroup::lrTaskName()
{
	EnEx ee(FL, "DeleteGroup::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "DeleteGroup Request";
}


void DeleteGroup::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "DeleteGroup::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("DeleteGroup");

	// Pick up the input object from the request document
	Group local( XmlHelpers::FindChild( ioc.GetRequestRoot(), Group::Name()() ) );

	// Read from our configuration database - change this to get data from elsewhere
	SqlDB& db = TheMain::getInstance()->GetConfigDB( );

	// Example of a doing this through an odbc connection
	// OdbcObj& db = *ioc.getDBConnection();

	// Start a transaction in case we need to handle delete's of multiple records
	SqlDBTransaction trans(db); // Transaction will be rolled back when this object goes out of scope

	// Example of doing a transaction through an odbc connection
	// Transaction trans(db); // Transaction will be rolled back when this object goes out of scope

	// Delete the requested object - adjust this to use the correct inputs and delete call
	Group::deleteByID( db, local.id );

	// Delete any other related records here
	UserGroup::deleteUsersForGroup( db, local.id );
	Group::deleteActionsForGroup( db, local.id );

	// Commit the transaction:
	trans.Commit();

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
