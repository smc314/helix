/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "UpdateGroup.h"
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
#include "HelixUser.h"
#include "Action.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<UpdateGroup> UpdateGroup::reg("UpdateGroup", 1, 
	"/logic/admin/InsertGroup",
	"/logic/admin/UpdateGroup"
);

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/InsertGroup Input=Group
// LOGICCODEGEN API=/logic/admin/UpdateGroup Input=Group

UpdateGroup::UpdateGroup(xmlNodePtr action)
{
	EnEx ee(FL, "UpdateGroup::UpdateGroup(xmlNodePtr action)");
	
}

UpdateGroup::UpdateGroup(const UpdateGroup& c)
{
	EnEx ee(FL, "UpdateGroup::UpdateGroup(const UpdateGroup& c)");

}

UpdateGroup& UpdateGroup::operator=(const UpdateGroup& c)
{
	EnEx ee(FL, "UpdateGroup::operator=(const UpdateGroup& c)");

	return *this;
}

UpdateGroup::~UpdateGroup()
{
	EnEx ee(FL, "UpdateGroup::~UpdateGroup()");

}

bool UpdateGroup::isLongRunning()
{
	EnEx ee(FL, "UpdateGroup::isLongRunning()");

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

twine UpdateGroup::lrTaskName()
{
	EnEx ee(FL, "UpdateGroup::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "UpdateGroup Request";
}


void UpdateGroup::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "UpdateGroup::ExecuteRequest(IOConn& ioc)", true);

	// How were we called?
	bool doingInsert = false;
	if(strcmp((const char*)ioc.GetRequestRoot()->name, "InsertGroup") == 0){
		doingInsert = true;
	}

	// Set up the response document name
	if(doingInsert){
		ioc.initializeResponseDocument("InsertGroup");
	} else {
		ioc.initializeResponseDocument("UpdateGroup");
	}

	// Pick up the input object from the request document
	Group local( XmlHelpers::FindChild( ioc.GetRequestRoot(), Group::Name()() ) );

	// Do any type of input validation here
	if(local.Groupname.empty()){
		throw AnException(0, FL, "Group must have a valid name.");
	}

	// Read from our configuration database - change this to get data from elsewhere
	SqlDB& db = TheMain::getInstance()->GetConfigDB( );

	// Example of a doing this through an odbc connection
	// OdbcObj& db = *ioc.getDBConnection();

	// Start a transaction in case we need to handle delete's of multiple records
	SqlDBTransaction trans(db); // Transaction will be rolled back when this object goes out of scope

	// Example of doing a transaction through an odbc connection
	// Transaction trans(db); // Transaction will be rolled back when this object goes out of scope

	if(doingInsert){
		Group::insert( db, local );
	} else {
		Group::update( db, local.Groupname, local.Description, local.id );
	}

	// Ensure the group id is on all of our child objects for the users and actions:
	for(size_t i = 0; i < local.UsersForGroup->size(); i++){
		local.UsersForGroup->at( i )->groupid = local.id;
	}
	for(size_t i = 0; i < local.ActionsForGroup->size(); i++){
		local.ActionsForGroup->at( i )->groupid = local.id;
	}

	// Now get the usergroup and groupaction entries correct:
	Group::deleteUsersForGroup(db, local.id); // Removes all users who used to be in this group
	Group::deleteActionsForGroup(db, local.id); // Removes all actions that used to be in this group

	UserGroup::addUserGroup( db, local.UsersForGroup, false); // No new transaction for the array insert
	Action::addGroupToAction( db, local.ActionsForGroup, false); // No new transaction for the array insert

	// Commit the transaction:
	trans.Commit();

	// Pull up users and actions defined in the DB:
	HelixUser::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllUsers", HelixUser::selectAll( db ) );
	Action::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllActions", Action::selectAll( db ) );

	// Send the updated object back to the caller
	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
