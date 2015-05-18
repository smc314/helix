/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetGroups.h"
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
ActionClassRegister<GetGroups> GetGroups::reg("GetGroups", 1, "/logic/admin/GetGroups");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetGroups Input=NULL

GetGroups::GetGroups(xmlNodePtr action)
{
	EnEx ee(FL, "GetGroups::GetGroups(xmlNodePtr action)");
	
}

GetGroups::GetGroups(const GetGroups& c)
{
	EnEx ee(FL, "GetGroups::GetGroups(const GetGroups& c)");

}

GetGroups& GetGroups::operator=(const GetGroups& c)
{
	EnEx ee(FL, "GetGroups::operator=(const GetGroups& c)");

	return *this;
}

GetGroups::~GetGroups()
{
	EnEx ee(FL, "GetGroups::~GetGroups()");

}

bool GetGroups::isLongRunning()
{
	EnEx ee(FL, "GetGroups::isLongRunning()");

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

twine GetGroups::lrTaskName()
{
	EnEx ee(FL, "GetGroups::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetGroups Request";
}


void GetGroups::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetGroups::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetGroups");

	SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
	Group_svect vect = Group::selectAll( sqldb );

	Group::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
