/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetProject.h"
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
ActionClassRegister<GetProject> GetProject::reg("GetProject", 1, "/logic/dev/GetProject");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/dev/GetProject Input=Project

GetProject::GetProject(xmlNodePtr action)
{
	EnEx ee(FL, "GetProject::GetProject(xmlNodePtr action)");
	
}

GetProject::GetProject(const GetProject& c)
{
	EnEx ee(FL, "GetProject::GetProject(const GetProject& c)");

}

GetProject& GetProject::operator=(const GetProject& c)
{
	EnEx ee(FL, "GetProject::operator=(const GetProject& c)");

	return *this;
}

GetProject::~GetProject()
{
	EnEx ee(FL, "GetProject::~GetProject()");

}

bool GetProject::isLongRunning()
{
	EnEx ee(FL, "GetProject::isLongRunning()");

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

twine GetProject::lrTaskName()
{
	EnEx ee(FL, "GetProject::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "GetProject Request";
}


void GetProject::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetProject::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetProject");

	Project local( XmlHelpers::FindChild( ioc.GetRequestRoot(), Project::Name()() ) );
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixdev" );
	Project_svect vect = Project::selectByID( sqldb, local.guid );
	if(vect->size() == 0){
		throw AnException(0, FL, "Did not find the requested project: %s", local.ProjName() );
	}

	// Load the Apps and Data children:
	vect->at(0)->Apps = Application::selectAllForProject( sqldb, local.guid );
	vect->at(0)->Data = ProjectData::selectAllForProj( sqldb, local.guid );
	
	// Add that data to the response
	Project::createXmlChildren( ioc.getResponseRoot(), vect );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
