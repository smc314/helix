/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SaveIAFile.h"
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
#include "IAFile.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<SaveIAFile> SaveIAFile::reg("SaveIAFile", 1, "/logic/admin/SaveIAFile");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/SaveIAFile Input=IAFile

SaveIAFile::SaveIAFile(xmlNodePtr action)
{
	EnEx ee(FL, "SaveIAFile::SaveIAFile(xmlNodePtr action)");
	
}

SaveIAFile::SaveIAFile(const SaveIAFile& c)
{
	EnEx ee(FL, "SaveIAFile::SaveIAFile(const SaveIAFile& c)");

}

SaveIAFile& SaveIAFile::operator=(const SaveIAFile& c)
{
	EnEx ee(FL, "SaveIAFile::operator=(const SaveIAFile& c)");

	return *this;
}

SaveIAFile::~SaveIAFile()
{
	EnEx ee(FL, "SaveIAFile::~SaveIAFile()");

}

void SaveIAFile::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SaveIAFile::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SaveIAFile");

	IAFile local( XmlHelpers::FindChild( ioc.GetRequestRoot(), IAFile::Name()() ) );
	twine fullName = local.ParentFolder + local.FileName;
	File::EnsurePath( fullName );
	if(File::Exists( fullName) ){
		File::Delete( fullName );
	}
	File::writeToFile( fullName, local.FileContents );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
