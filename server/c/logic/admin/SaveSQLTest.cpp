/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SaveSQLTest.h"
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

// This adds us to the global ActionClass Registry:
ActionClassRegister<SaveSQLTest> SaveSQLTest::reg("SaveSQLTest", 1, "/logic/admin/SaveSQLTest");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/SaveSQLTest Input=SQLTests

SaveSQLTest::SaveSQLTest(xmlNodePtr action)
{
	EnEx ee(FL, "SaveSQLTest::SaveSQLTest(xmlNodePtr action)");
	
}

SaveSQLTest::SaveSQLTest(const SaveSQLTest& c)
{
	EnEx ee(FL, "SaveSQLTest::SaveSQLTest(const SaveSQLTest& c)");

}

SaveSQLTest& SaveSQLTest::operator=(const SaveSQLTest& c)
{
	EnEx ee(FL, "SaveSQLTest::operator=(const SaveSQLTest& c)");

	return *this;
}

SaveSQLTest::~SaveSQLTest()
{
	EnEx ee(FL, "SaveSQLTest::~SaveSQLTest()");

}

void SaveSQLTest::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SaveSQLTest::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SaveSQLTest");

	SQLTests local( XmlHelpers::FindChild( ioc.GetRequestRoot(), SQLTests::Name()() ) );
	sptr<xmlDoc, xmlFreeDoc> doc = local.createXmlDoc();
	twine fileName = "./test/" + local.TestGroupName;
	xmlSaveFile( fileName(), doc);

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
