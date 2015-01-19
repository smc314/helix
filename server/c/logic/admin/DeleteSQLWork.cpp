/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "DeleteSQLWork.h"
using namespace Helix::Logic::admin;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "SQLWork.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<DeleteSQLWork> DeleteSQLWork::reg("DeleteSQLWork", 1, "/logic/admin/DeleteSQLWork");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/DeleteSQLWork Input=SQLWork

DeleteSQLWork::DeleteSQLWork(xmlNodePtr action)
{
	EnEx ee(FL, "DeleteSQLWork::DeleteSQLWork(xmlNodePtr action)");
	
}

DeleteSQLWork::DeleteSQLWork(const DeleteSQLWork& c)
{
	EnEx ee(FL, "DeleteSQLWork::DeleteSQLWork(const DeleteSQLWork& c)");

}

DeleteSQLWork& DeleteSQLWork::operator=(const DeleteSQLWork& c)
{
	EnEx ee(FL, "DeleteSQLWork::operator=(const DeleteSQLWork& c)");

	return *this;
}

DeleteSQLWork::~DeleteSQLWork()
{

}

void DeleteSQLWork::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "DeleteSQLWork::ExecuteRequest(IOConn& ioc)", true);
	
	// Pull up our input document and convert it into an object we can use:
	SQLWork local( XmlHelpers::FindChild(ioc.GetRequestRoot(), SQLWork::Name()()) );
	
	// Set up the response document name
	ioc.initializeResponseDocument("DeleteSQLWork");
	
	twine folder = (local.Type == "aci") ? "./sqlwork/aci/" : "./sqlwork/";
	twine fileName = folder + local.FileName;
	
	if (File::Exists(fileName)) {
		File::Delete(fileName);
	}
	
	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
