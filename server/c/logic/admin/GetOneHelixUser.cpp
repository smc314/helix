/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetOneHelixUser.h"
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
using namespace Helix::Logic::admin;

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetOneHelixUser> GetOneHelixUser::reg("GetOneHelixUser", 1, "/logic/admin/GetOneHelixUser");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetOneHelixUser Input=HelixUser

GetOneHelixUser::GetOneHelixUser(xmlNodePtr action)
{
	EnEx ee(FL, "GetOneHelixUser::GetOneHelixUser(xmlNodePtr action)");
	
}

GetOneHelixUser::GetOneHelixUser(const GetOneHelixUser& c)
{
	EnEx ee(FL, "GetOneHelixUser::GetOneHelixUser(const GetOneHelixUser& c)");

}

GetOneHelixUser& GetOneHelixUser::operator=(const GetOneHelixUser& c)
{
	EnEx ee(FL, "GetOneHelixUser::operator=(const GetOneHelixUser& c)");

	return *this;
}

GetOneHelixUser::~GetOneHelixUser()
{
	EnEx ee(FL, "GetOneHelixUser::~GetOneHelixUser()");

}

bool GetOneHelixUser::isLongRunning()
{
	EnEx ee(FL, "GetOneHelixUser::isLongRunning()");

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

twine GetOneHelixUser::lrTaskName()
{
	EnEx ee(FL, "GetOneHelixUser::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetOneHelixUser Request";
}


void GetOneHelixUser::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetOneHelixUser::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetOneHelixUser");

	HelixUser local( XmlHelpers::FindChild( ioc.GetRequestRoot(), HelixUser::Name()() ) );

	SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
	HelixUser_svect vect = HelixUser::selectByID( sqldb, local.id );
	if(vect->size() == 0){
		throw AnException(0, FL, "Unknown user: %d", local.id);
	}

	// Pull up the existing groups for the user:
	(*vect)[0]->GroupMembership = UserGroup::selectGroupsForUser( sqldb, local.id );

	// Pull up the existing actions for the user:
	(*vect)[0]->AllowedActions = Action::selectActionsForUser( sqldb, local.id );

	HelixUser::createXmlChildren( ioc.getResponseRoot(), vect );

	// Pull up all the groups defined in the DB:
	Group::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllGroups",
		Group::selectAll( sqldb )
	);

	// Pull up all the actions defined in the DB:
	Action::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllActions",
		Action::selectAll( sqldb )
	);

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
