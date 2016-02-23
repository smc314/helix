/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "UpdateHelixUser.h"
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
#include "Group.h"
#include "Action.h"


// This adds us to the global ActionClass Registry:
ActionClassRegister<UpdateHelixUser> UpdateHelixUser::reg("UpdateHelixUser", 1, 
	"/logic/admin/InsertHelixUser",
	"/logic/admin/UpdateHelixUser"
);

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/InsertHelixUser Input=HelixUser
// LOGICCODEGEN API=/logic/admin/UpdateHelixUser Input=HelixUser

UpdateHelixUser::UpdateHelixUser(xmlNodePtr action)
{
	EnEx ee(FL, "UpdateHelixUser::UpdateHelixUser(xmlNodePtr action)");
	
}

UpdateHelixUser::UpdateHelixUser(const UpdateHelixUser& c)
{
	EnEx ee(FL, "UpdateHelixUser::UpdateHelixUser(const UpdateHelixUser& c)");

}

UpdateHelixUser& UpdateHelixUser::operator=(const UpdateHelixUser& c)
{
	EnEx ee(FL, "UpdateHelixUser::operator=(const UpdateHelixUser& c)");

	return *this;
}

UpdateHelixUser::~UpdateHelixUser()
{
	EnEx ee(FL, "UpdateHelixUser::~UpdateHelixUser()");

}

bool UpdateHelixUser::isLongRunning()
{
	EnEx ee(FL, "UpdateHelixUser::isLongRunning()");

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

twine UpdateHelixUser::lrTaskName()
{
	EnEx ee(FL, "UpdateHelixUser::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "UpdateHelixUser Request";
}


void UpdateHelixUser::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "UpdateHelixUser::ExecuteRequest(IOConn& ioc)", true);

	// How were we called?
	bool doingInsert = false;
	if(strcmp((const char*)ioc.GetRequestRoot()->name, "InsertHelixUser") == 0){
		doingInsert = true;
	}

	// Set up the response document name
	if(doingInsert){
		ioc.initializeResponseDocument("InsertHelixUser");
	} else {
		ioc.initializeResponseDocument("UpdateHelixUser");
	}

	HelixUser local( XmlHelpers::FindChild( ioc.GetRequestRoot(), HelixUser::Name()() ) );
	if(local.Username.empty()){
		throw AnException(0, FL, "HelixUser must have a valid name.");
	}

	SqlDB& db = TheMain::getInstance()->GetConfigDB( );

	SqlDBTransaction trans(db); // Transaction will be rolled back when this object goes out of scope

	if(doingInsert){
		HelixUser::insert( db, local );
		HelixUser::insertAuth( db, local );
	} else {
		HelixUser::update( db, local.Username, local.FullName, local.EMail, local.Active, local.id );
		HelixUser::updateAuth( db, local.AuthMechanism, local.Password, local.id );
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
	HelixUser::deleteActionsForUser( db, local.id );

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
