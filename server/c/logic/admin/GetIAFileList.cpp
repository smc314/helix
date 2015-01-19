/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetIAFileList.h"
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
ActionClassRegister<GetIAFileList> GetIAFileList::reg("GetIAFileList", 1, "/logic/admin/GetIAFileList");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetIAFileList Input=IAFolder

GetIAFileList::GetIAFileList(xmlNodePtr action)
{
	EnEx ee(FL, "GetIAFileList::GetIAFileList(xmlNodePtr action)");
	
}

GetIAFileList::GetIAFileList(const GetIAFileList& c)
{
	EnEx ee(FL, "GetIAFileList::GetIAFileList(const GetIAFileList& c)");

}

GetIAFileList& GetIAFileList::operator=(const GetIAFileList& c)
{
	EnEx ee(FL, "GetIAFileList::operator=(const GetIAFileList& c)");

	return *this;
}

GetIAFileList::~GetIAFileList()
{

}

void GetIAFileList::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetIAFileList::ExecuteRequest(IOConn& ioc)", true);
	
	// Pull up our input document and convert it into an object we can use:
	IAFolder local( XmlHelpers::FindChild(ioc.GetRequestRoot(), IAFolder::Name()()) );
	
	// Set up the response document name
	ioc.initializeResponseDocument("GetIAFileList");
	xmlNodePtr root = ioc.getResponseRoot();
	
	// Pull up our list of plans from the documents in the ./ia/ directory
	vector<twine> folders = File::listFolders(local.ParentFolder);
	for(int i = 0; i < (int)folders.size(); i++){
		if(folders[i].endsWith(".")) { continue;}
		IAFolder folder;
		folder.ParentFolder = local.ParentFolder + folders[i] + "/";
		folder.FolderName = folders[i];

		// Add it to our return
		folder.createXmlNode( root );
	}
	
	// Pull up our list of plans from the documents in the ./ia/ directory
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
