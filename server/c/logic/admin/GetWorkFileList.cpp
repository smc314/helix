/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetWorkFileList.h"
using namespace Helix::Logic::admin;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "IAFolder.h"
#include "IAFile.h"


// This adds us to the global ActionClass Registry:
ActionClassRegister<GetWorkFileList> GetWorkFileList::reg("GetWorkFileList", 1, "/logic/admin/GetWorkFileList");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetWorkFileList Input=IAFolder

GetWorkFileList::GetWorkFileList(xmlNodePtr action)
{
	EnEx ee(FL, "GetWorkFileList::GetWorkFileList(xmlNodePtr action)");
	
}

GetWorkFileList::GetWorkFileList(const GetWorkFileList& c)
{
	EnEx ee(FL, "GetWorkFileList::GetWorkFileList(const GetWorkFileList& c)");

}

GetWorkFileList& GetWorkFileList::operator=(const GetWorkFileList& c)
{
	EnEx ee(FL, "GetWorkFileList::operator=(const GetWorkFileList& c)");

	return *this;
}

GetWorkFileList::~GetWorkFileList()
{

}

void GetWorkFileList::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetWorkFileList::ExecuteRequest(IOConn& ioc)", true);
	
	// Pull up our input document and convert it into an object we can use:
	IAFolder local( XmlHelpers::FindChild(ioc.GetRequestRoot(), IAFolder::Name()()) );
	
	// Set up the response document name
	ioc.initializeResponseDocument("GetWorkFileList");
	xmlNodePtr root = ioc.getResponseRoot();
	
	// Make sure parent folder exists
	File::EnsurePath(local.ParentFolder + "/");
	
	// Get list of files form parent folder
	vector<twine> files = File::listFiles(local.ParentFolder);
	for(int i = 0; i < (int)files.size(); i++){
		IAFile file;
		file.ParentFolder = local.ParentFolder;
		file.FileName = files[i];

		// Add it to our return
		file.createXmlNode( root );
	}

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
