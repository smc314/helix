/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SaveSQLWork.h"
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
#include "SQLWork.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<SaveSQLWork> SaveSQLWork::reg("SaveSQLWork", 1, "/logic/admin/SaveSQLWork");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/SaveSQLWork Input=SQLWork

SaveSQLWork::SaveSQLWork(xmlNodePtr action)
{
	EnEx ee(FL, "SaveSQLWork::SaveSQLWork(xmlNodePtr action)");
	
}

SaveSQLWork::SaveSQLWork(const SaveSQLWork& c)
{
	EnEx ee(FL, "SaveSQLWork::SaveSQLWork(const SaveSQLWork& c)");

}

SaveSQLWork& SaveSQLWork::operator=(const SaveSQLWork& c)
{
	EnEx ee(FL, "SaveSQLWork::operator=(const SaveSQLWork& c)");

	return *this;
}

SaveSQLWork::~SaveSQLWork()
{
	EnEx ee(FL, "SaveSQLWork::~SaveSQLWork()");

}

void SaveSQLWork::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SaveSQLWork::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SaveSQLWork");

	SQLWork local( XmlHelpers::FindChild( ioc.GetRequestRoot(), SQLWork::Name()() ) );
	if(local.FileName.empty()){
		throw AnException(0, FL, "Can't save SQLWork file with empty filename.");
	}
	
	sptr<xmlDoc, xmlFreeDoc> doc = local.createXmlDoc();

	twine folder = (local.Type == "aci") ? "./sqlwork/aci/" : "./sqlwork/";
	twine fileName = folder + local.FileName;

	xmlSaveFile( fileName(), doc);

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
