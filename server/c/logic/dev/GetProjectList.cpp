/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetProjectList.h"
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
#include "Project.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetProjectList> GetProjectList::reg("GetProjectList", 1, "/logic/dev/GetProjectList");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/dev/GetProjectList Input=NULL

GetProjectList::GetProjectList(xmlNodePtr action)
{
	EnEx ee(FL, "GetProjectList::GetProjectList(xmlNodePtr action)");
	
}

GetProjectList::GetProjectList(const GetProjectList& c)
{
	EnEx ee(FL, "GetProjectList::GetProjectList(const GetProjectList& c)");

}

GetProjectList& GetProjectList::operator=(const GetProjectList& c)
{
	EnEx ee(FL, "GetProjectList::operator=(const GetProjectList& c)");

	return *this;
}

GetProjectList::~GetProjectList()
{
	EnEx ee(FL, "GetProjectList::~GetProjectList()");

}

bool GetProjectList::isLongRunning()
{
	EnEx ee(FL, "GetProjectList::isLongRunning()");

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

twine GetProjectList::lrTaskName()
{
	EnEx ee(FL, "GetProjectList::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetProjectList Request";
}


void GetProjectList::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetProjectList::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetProjectList");

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixdev" );
	Project_svect vect = Project::selectAll( sqldb );
	Project::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
