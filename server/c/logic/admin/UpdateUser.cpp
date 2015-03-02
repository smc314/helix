/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "UpdateUser.h"
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
#include "Group.h"
#include "Action.h"


// This adds us to the global ActionClass Registry:
ActionClassRegister<UpdateUser> UpdateUser::reg("UpdateUser", 1, 
	"/logic/admin/InsertUser",
	"/logic/admin/UpdateUser"
);

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/InsertUser Input=User
// LOGICCODEGEN API=/logic/admin/UpdateUser Input=User

UpdateUser::UpdateUser(xmlNodePtr action)
{
	EnEx ee(FL, "UpdateUser::UpdateUser(xmlNodePtr action)");
	
}

UpdateUser::UpdateUser(const UpdateUser& c)
{
	EnEx ee(FL, "UpdateUser::UpdateUser(const UpdateUser& c)");

}

UpdateUser& UpdateUser::operator=(const UpdateUser& c)
{
	EnEx ee(FL, "UpdateUser::operator=(const UpdateUser& c)");

	return *this;
}

UpdateUser::~UpdateUser()
{
	EnEx ee(FL, "UpdateUser::~UpdateUser()");

}

bool UpdateUser::isLongRunning()
{
	EnEx ee(FL, "UpdateUser::isLongRunning()");

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

twine UpdateUser::lrTaskName()
{
	EnEx ee(FL, "UpdateUser::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "UpdateUser Request";
}


void UpdateUser::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "UpdateUser::ExecuteRequest(IOConn& ioc)", true);

	// How were we called?
	bool doingInsert = false;
	if(strcmp((const char*)ioc.GetRequestRoot()->name, "InsertUser") == 0){
		doingInsert = true;
	}

	// Set up the response document name
	if(doingInsert){
		ioc.initializeResponseDocument("InsertUser");
	} else {
		ioc.initializeResponseDocument("UpdateUser");
	}

	User local( XmlHelpers::FindChild( ioc.GetRequestRoot(), User::Name()() ) );
	if(local.Username.empty()){
		throw AnException(0, FL, "User must have a valid name.");
	}

	SqlDB& db = TheMain::getInstance()->GetConfigDB( );

	SqlDBTransaction trans(db); // Transaction will be rolled back when this object goes out of scope

	if(doingInsert){
		User::insert( db, local );
		User::insertAuth( db, local );
	} else {
		User::update( db, local.Username, local.FullName, local.EMail, local.Active, local.id );
		User::updateAuth( db, local.AuthMechanism, local.Password, local.id );
	}
	// Pick up the new user ID for the groups and actions
	for(size_t i = 0; i < local.GroupMembership->size(); i ++){
		local.GroupMembership->at( i )->userid = local.id;
	}
	for(size_t i = 0; i < local.AllowedActions->size(); i ++){
		local.AllowedActions->at( i )->userid = local.id;
	}

	// Now get the usergroup and useraction entries correct:
	UserGroup::deleteGroupsForUser( db, local.id );
	User::deleteActionsForUser( db, local.id );

	UserGroup::addUserGroup( db, local.GroupMembership, false ); // No new transaction for these inserts
	Action::addUserToAction( db, local.AllowedActions, false ); // No new transaction for these inserts

	// Commit the transaction
	trans.Commit();

	// Pull up groups and actions defined in the DB:
	Group::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllGroups", Group::selectAll( db ) );
	Action::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllActions", Action::selectAll( db ) );

	// Send the updated user back to the caller
	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
