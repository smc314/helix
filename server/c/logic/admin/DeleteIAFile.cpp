/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "DeleteIAFile.h"
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
ActionClassRegister<DeleteIAFile> DeleteIAFile::reg("DeleteIAFile", 1, "/logic/admin/DeleteIAFile");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/DeleteIAFile Input=IAFile

DeleteIAFile::DeleteIAFile(xmlNodePtr action)
{
	EnEx ee(FL, "DeleteIAFile::DeleteIAFile(xmlNodePtr action)");
	
}

DeleteIAFile::DeleteIAFile(const DeleteIAFile& c)
{
	EnEx ee(FL, "DeleteIAFile::DeleteIAFile(const DeleteIAFile& c)");

}

DeleteIAFile& DeleteIAFile::operator=(const DeleteIAFile& c)
{
	EnEx ee(FL, "DeleteIAFile::operator=(const DeleteIAFile& c)");

	return *this;
}

DeleteIAFile::~DeleteIAFile()
{
	EnEx ee(FL, "DeleteIAFile::~DeleteIAFile()");

}

bool DeleteIAFile::isLongRunning()
{
	EnEx ee(FL, "DeleteIAFile::isLongRunning()");

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

twine DeleteIAFile::lrTaskName()
{
	EnEx ee(FL, "DeleteIAFile::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "DeleteIAFile Request";
}


void DeleteIAFile::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "DeleteIAFile::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("DeleteIAFile");

	IAFile local( XmlHelpers::FindChild( ioc.GetRequestRoot(), IAFile::Name()() ) );
	twine fullName = local.ParentFolder + local.FileName;
	File::EnsurePath( fullName );
	if(File::Exists( fullName) ){
		File::Delete( fullName );
	}

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
