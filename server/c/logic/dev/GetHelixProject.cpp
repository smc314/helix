/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetHelixProject.h"
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
ActionClassRegister<GetHelixProject> GetHelixProject::reg("GetHelixProject", 1, "/logic/dev/GetHelixProject");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/dev/GetHelixProject Input=HelixProject

GetHelixProject::GetHelixProject(xmlNodePtr action)
{
	EnEx ee(FL, "GetHelixProject::GetHelixProject(xmlNodePtr action)");
	
}

GetHelixProject::GetHelixProject(const GetHelixProject& c)
{
	EnEx ee(FL, "GetHelixProject::GetHelixProject(const GetHelixProject& c)");

}

GetHelixProject& GetHelixProject::operator=(const GetHelixProject& c)
{
	EnEx ee(FL, "GetHelixProject::operator=(const GetHelixProject& c)");

	return *this;
}

GetHelixProject::~GetHelixProject()
{
	EnEx ee(FL, "GetHelixProject::~GetHelixProject()");

}

bool GetHelixProject::isLongRunning()
{
	EnEx ee(FL, "GetHelixProject::isLongRunning()");

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

twine GetHelixProject::lrTaskName()
{
	EnEx ee(FL, "GetHelixProject::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetHelixProject Request";
}


void GetHelixProject::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetHelixProject::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetHelixProject");

	HelixProject local( XmlHelpers::FindChild( ioc.GetRequestRoot(), HelixProject::Name()() ) );
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixdev" );
	HelixProject_svect vect = HelixProject::selectByID( sqldb, local.guid );
	if(vect->size() == 0){
		throw AnException(0, FL, "Did not find the requested project: %s", local.ProjName() );
	}

	// Load the Apps and Data children:
	vect->at(0)->Apps = Application::selectAllForProject( sqldb, local.guid );
	vect->at(0)->Data = HelixProjectData::selectAllForProj( sqldb, local.guid );
	
	// Add that data to the response
	HelixProject::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
