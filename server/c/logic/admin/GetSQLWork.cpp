/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetSQLWork.h"
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
ActionClassRegister<GetSQLWork> GetSQLWork::reg("GetSQLWork", 1, "/logic/admin/GetSQLWork");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetSQLWork Input=SQLWork

GetSQLWork::GetSQLWork(xmlNodePtr action)
{
	EnEx ee(FL, "GetSQLWork::GetSQLWork(xmlNodePtr action)");
	
}

GetSQLWork::GetSQLWork(const GetSQLWork& c)
{
	EnEx ee(FL, "GetSQLWork::GetSQLWork(const GetSQLWork& c)");

}

GetSQLWork& GetSQLWork::operator=(const GetSQLWork& c)
{
	EnEx ee(FL, "GetSQLWork::operator=(const GetSQLWork& c)");

	return *this;
}

GetSQLWork::~GetSQLWork()
{
	EnEx ee(FL, "GetSQLWork::~GetSQLWork()");

}

void GetSQLWork::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetSQLWork::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetSQLWork");

	SQLWork local( XmlHelpers::FindChild( ioc.GetRequestRoot(), SQLWork::Name()() ) );
	
	twine folder = (local.Type == "aci") ? "./sqlwork/aci/" : "./sqlwork/";
	twine fileName = folder + local.FileName;

	sptr<xmlDoc, xmlFreeDoc> doc = xmlParseFile( fileName() );
	
	if(doc == NULL){
		throw AnException(0, FL, "Invalid XML document requested.");
	}
	
	xmlNodePtr root = xmlDocGetRootElement( doc );
	SQLWork work( root );
	work.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
