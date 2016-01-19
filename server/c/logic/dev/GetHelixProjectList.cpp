/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetHelixProjectList.h"
using namespace Helix::Logic::dev;

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
#include "HelixProject.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetHelixProjectList> GetHelixProjectList::reg("GetHelixProjectList", 1, "/logic/dev/GetHelixProjectList");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/dev/GetHelixProjectList Input=NULL

GetHelixProjectList::GetHelixProjectList(xmlNodePtr action)
{
	EnEx ee(FL, "GetHelixProjectList::GetHelixProjectList(xmlNodePtr action)");
	
}

GetHelixProjectList::GetHelixProjectList(const GetHelixProjectList& c)
{
	EnEx ee(FL, "GetHelixProjectList::GetHelixProjectList(const GetHelixProjectList& c)");

}

GetHelixProjectList& GetHelixProjectList::operator=(const GetHelixProjectList& c)
{
	EnEx ee(FL, "GetHelixProjectList::operator=(const GetHelixProjectList& c)");

	return *this;
}

GetHelixProjectList::~GetHelixProjectList()
{
	EnEx ee(FL, "GetHelixProjectList::~GetHelixProjectList()");

}

bool GetHelixProjectList::isLongRunning()
{
	EnEx ee(FL, "GetHelixProjectList::isLongRunning()");

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

twine GetHelixProjectList::lrTaskName()
{
	EnEx ee(FL, "GetHelixProjectList::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetHelixProjectList Request";
}


void GetHelixProjectList::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetHelixProjectList::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetHelixProjectList");

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixdev" );
	HelixProject_svect vect = HelixProject::selectAll( sqldb );
	HelixProject::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
