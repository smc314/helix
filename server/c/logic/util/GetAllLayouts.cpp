/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetAllLayouts.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here


// This adds us to the global ActionClass Registry:
ActionClassRegister<GetAllLayouts> GetAllLayouts::reg("GetAllLayouts", 1, "/logic/util/GetAllLayouts");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetAllLayouts Input=NULL

GetAllLayouts::GetAllLayouts(xmlNodePtr action)
{
	EnEx ee(FL, "GetAllLayouts::GetAllLayouts(xmlNodePtr action)");
	
}

GetAllLayouts::GetAllLayouts(const GetAllLayouts& c)
{
	EnEx ee(FL, "GetAllLayouts::GetAllLayouts(const GetAllLayouts& c)");

}

GetAllLayouts& GetAllLayouts::operator=(const GetAllLayouts& c)
{
	EnEx ee(FL, "GetAllLayouts::operator=(const GetAllLayouts& c)");

	return *this;
}

GetAllLayouts::~GetAllLayouts()
{

}

void GetAllLayouts::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetAllLayouts::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetAllLayouts");

	// Here are the directories where we search for layouts:
	// ascfg, dash, drvdep, ia, ldm, xfrmgr
	
	vector<twine> layouts;
	AddLayouts(layouts, "admin");
	AddLayouts(layouts, "dev");

	// Now take those and return them to the caller:
	for(int i = 0; i < (int)layouts.size(); i++){
		// Record this name
		xmlNodePtr child = xmlNewChild(ioc.getResponseRoot(), NULL, (const xmlChar*)"Layout", NULL);
		xmlSetProp(child, (const xmlChar*)"name", layouts[i]);
		xmlSetProp(child, (const xmlChar*)"id", layouts[i]);

	}

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}

void GetAllLayouts::AddLayouts(vector<twine>& list, twine dirName)
{
	EnEx ee(FL, "GetAllLayouts::AddLayouts(vector<twine>& list, twine dirName)");

	twine realDirName = "../../../qd/" + dirName + "/source/layouts/";
	vector<twine> tmp = File::listFiles(realDirName);
	for(int i = 0; i < (int)tmp.size(); i++){
		list.push_back( dirName + "/" + tmp[i] );
	}

}
