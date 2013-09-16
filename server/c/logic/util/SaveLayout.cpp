/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SaveLayout.h"
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
ActionClassRegister<SaveLayout> SaveLayout::reg("SaveLayout", 1, "/logic/util/SaveLayout");

// Used for auto generating the API on the javascript side:
// NOT USED HERE API=/logic/util/SaveLayout Input=Something

SaveLayout::SaveLayout(xmlNodePtr action)
{
	EnEx ee(FL, "SaveLayout::SaveLayout(xmlNodePtr action)");
	
}

SaveLayout::SaveLayout(const SaveLayout& c)
{
	EnEx ee(FL, "SaveLayout::SaveLayout(const SaveLayout& c)");

}

SaveLayout& SaveLayout::operator=(const SaveLayout& c)
{
	EnEx ee(FL, "SaveLayout::operator=(const SaveLayout& c)");

	return *this;
}

SaveLayout::~SaveLayout()
{

}

void SaveLayout::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SaveLayout::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SaveLayout");

	xmlNodePtr root = ioc.GetRequestRoot();
	twine file(root, "filename");

	// The name is in the short form of package/file, split this up so that we can save to
	// the real file name properly.
	vector<twine> splits = file.split("/");
	twine realName = "../qd/" + splits[0] + "/source/layouts/" + splits[1];

	INFO(FL, "Saving layout (%s) to file (%s)", file(), realName());
	int bytes = xmlSaveFile( realName(), ioc.GetMsg() );
	if(bytes == -1){
		throw AnException(0, FL, "Error saving layout %s", realName());
	}

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
