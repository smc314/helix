/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetOneGroup.h"
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
#include "User.h"
#include "Action.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetOneGroup> GetOneGroup::reg("GetOneGroup", 1, "/logic/admin/GetOneGroup");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetOneGroup Input=Group

GetOneGroup::GetOneGroup(xmlNodePtr action)
{
	EnEx ee(FL, "GetOneGroup::GetOneGroup(xmlNodePtr action)");
	
}

GetOneGroup::GetOneGroup(const GetOneGroup& c)
{
	EnEx ee(FL, "GetOneGroup::GetOneGroup(const GetOneGroup& c)");

}

GetOneGroup& GetOneGroup::operator=(const GetOneGroup& c)
{
	EnEx ee(FL, "GetOneGroup::operator=(const GetOneGroup& c)");

	return *this;
}

GetOneGroup::~GetOneGroup()
{
	EnEx ee(FL, "GetOneGroup::~GetOneGroup()");

}

bool GetOneGroup::isLongRunning()
{
	EnEx ee(FL, "GetOneGroup::isLongRunning()");

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

twine GetOneGroup::lrTaskName()
{
	EnEx ee(FL, "GetOneGroup::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetOneGroup Request";
}


void GetOneGroup::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetOneGroup::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetOneGroup");

	// Pick up the input object from the request document
	Group local( XmlHelpers::FindChild( ioc.GetRequestRoot(), Group::Name()() ) );

	// Read from our configuration database - change this to get data from elsewhere
	SqlDB& db = TheMain::getInstance()->GetConfigDB( );

	// Example of a doing this through an odbc connection
	// OdbcObj& db = *ioc.getDBConnection();

	Group_svect vect = Group::selectByID( db, local.id );
	if(vect->size() == 0){
		throw AnException(0, FL, "Unknown Group object: %d", local.id);
	}

	// Get a reference to the first object in the vector for easy access
	Group& ret = *(*vect)[0];

	// If anything else needs to be added to the object like child vectors, calculations, 
	// or anything like that, do it here
	ret.UsersForGroup = UserGroup::selectUsersForGroup(db, local.id);
	ret.ActionsForGroup = Action::selectActionsForGroup(db, local.id);

	// Add the selected object to the response document
	ret.createXmlNode( ioc.getResponseRoot() );

	// Also pull up all of the users defined in the DB:
	User::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllUsers",
		User::selectAll( db )
	);

	// Also pull up all of the actions defined in the DB:
	Action::createXmlChildAndGrandchildren( ioc.getResponseRoot(), "AllActions",
		Action::selectAll( db )
	);

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
