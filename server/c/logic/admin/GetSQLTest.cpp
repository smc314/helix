/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetSQLTest.h"
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
#include "SQLTests.h"
#include "IAFile.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetSQLTest> GetSQLTest::reg("GetSQLTest", 1, "/logic/admin/GetSQLTest");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/GetSQLTest Input=IAFile

GetSQLTest::GetSQLTest(xmlNodePtr action)
{
	EnEx ee(FL, "GetSQLTest::GetSQLTest(xmlNodePtr action)");
	
}

GetSQLTest::GetSQLTest(const GetSQLTest& c)
{
	EnEx ee(FL, "GetSQLTest::GetSQLTest(const GetSQLTest& c)");

}

GetSQLTest& GetSQLTest::operator=(const GetSQLTest& c)
{
	EnEx ee(FL, "GetSQLTest::operator=(const GetSQLTest& c)");

	return *this;
}

GetSQLTest::~GetSQLTest()
{
	EnEx ee(FL, "GetSQLTest::~GetSQLTest()");

}

void GetSQLTest::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetSQLTest::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetSQLTest");

	IAFile local( XmlHelpers::FindChild( ioc.GetRequestRoot(), IAFile::Name()() ) );
	twine fileName = local.ParentFolder + local.FileName;
	sptr<xmlDoc, xmlFreeDoc> doc = xmlParseFile( fileName() );
	if(doc == NULL){
		throw AnException(0, FL, "Invalid XML document requested.");
	}
	xmlNodePtr root = xmlDocGetRootElement( doc );
	SQLTests tests( root );
	
	tests.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
