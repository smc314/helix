/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetIAFileDetails.h"
using namespace Helix::Logic::admin;

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
ActionClassRegister<GetIAFileDetails> GetIAFileDetails::reg("GetIAFileDetails", 1, "/logic/admin/GetIAFileDetails");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetIAFileDetails Input=IAFile

GetIAFileDetails::GetIAFileDetails(xmlNodePtr action)
{
	EnEx ee(FL, "GetIAFileDetails::GetIAFileDetails(xmlNodePtr action)");
	
}

GetIAFileDetails::GetIAFileDetails(const GetIAFileDetails& c)
{
	EnEx ee(FL, "GetIAFileDetails::GetIAFileDetails(const GetIAFileDetails& c)");

}

GetIAFileDetails& GetIAFileDetails::operator=(const GetIAFileDetails& c)
{
	EnEx ee(FL, "GetIAFileDetails::operator=(const GetIAFileDetails& c)");

	return *this;
}

GetIAFileDetails::~GetIAFileDetails()
{

}

void GetIAFileDetails::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetIAFileDetails::ExecuteRequest(IOConn& ioc)", true);

	// Pull up our input document and convert it into an object we can use:
	IAFile local( XmlHelpers::FindChild(ioc.GetRequestRoot(), IAFile::Name()()) );
	
	// Set up the response document name
	ioc.initializeResponseDocument("GetIAFileDetails");
	
	twine fileName = local.ParentFolder + local.FileName;
	File iaFile(fileName);
	twine contents = iaFile.readContentsAsTwine();
			
	local.FileContents = contents;
	
	// Wrap the whole thing up into our xml response
	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
