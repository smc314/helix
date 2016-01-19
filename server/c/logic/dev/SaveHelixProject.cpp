/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SaveHelixProject.h"
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
ActionClassRegister<SaveHelixProject> SaveHelixProject::reg("SaveHelixProject", 1, "/logic/dev/SaveHelixProject");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/dev/SaveHelixProject Input=HelixProject

SaveHelixProject::SaveHelixProject(xmlNodePtr action)
{
	EnEx ee(FL, "SaveHelixProject::SaveHelixProject(xmlNodePtr action)");
	
}

SaveHelixProject::SaveHelixProject(const SaveHelixProject& c)
{
	EnEx ee(FL, "SaveHelixProject::SaveHelixProject(const SaveHelixProject& c)");

}

SaveHelixProject& SaveHelixProject::operator=(const SaveHelixProject& c)
{
	EnEx ee(FL, "SaveHelixProject::operator=(const SaveHelixProject& c)");

	return *this;
}

SaveHelixProject::~SaveHelixProject()
{
	EnEx ee(FL, "SaveHelixProject::~SaveHelixProject()");

}

bool SaveHelixProject::isLongRunning()
{
	EnEx ee(FL, "SaveHelixProject::isLongRunning()");

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

twine SaveHelixProject::lrTaskName()
{
	EnEx ee(FL, "SaveHelixProject::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "SaveHelixProject Request";
}

void SaveHelixProject::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SaveHelixProject::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SaveHelixProject");

	HelixProject local( XmlHelpers::FindChild( ioc.GetRequestRoot(), HelixProject::Name()() ) );

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixdev" );
	
	// Check to see whether this is a new project:
	if(local.guid == "NEW"){
		// Brand new project - generate GUID's all the way down the tree for the new items.
		local.guid = IOConn::genSessionID();
		for(size_t i = 0; i < local.Apps->size(); i++){
			local.Apps->at(i)->guid = IOConn::genSessionID();
			local.Apps->at(i)->projguid = local.guid;
		}
		for(size_t i = 0; i < local.Data->size(); i++){
			local.Data->at(i)->guid = IOConn::genSessionID();
			local.Data->at(i)->projguid = local.guid;
		}

		// Then run the inserts:
		HelixProject::insert( sqldb, local );
		Application::insert( sqldb, local.Apps );
		HelixProjectData::insert( sqldb, local.Data );
	} else {
		// Run the updates
		HelixProject::update( sqldb, 
			local.ProjName, 
			local.ShortName, 
			local.Description, 
			local.Deployment, 
			local.Location, 
			local.guid 
		);
		for(size_t i = 0; i < local.Apps->size(); i++){
			Application::update( sqldb, 
				local.Apps->at(i)->AppName,
				local.Apps->at(i)->Description,
				local.Apps->at(i)->PackageName,
				local.Apps->at(i)->guid
			);
		}
		for(size_t i = 0; i < local.Data->size(); i++){
			HelixProjectData::update( sqldb, 
				local.Data->at(i)->DataName,
				local.Data->at(i)->Description,
				local.Data->at(i)->DataType,
				local.Data->at(i)->ConnectionString,
				local.Data->at(i)->DevTimeUser,
				local.Data->at(i)->DevTimePass,
				local.Data->at(i)->guid
			);
		}
	}
		
	// Return the updated information back to the caller:
	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
