/* **************************************************************************

   Copyright (c): 2008 - 2013 GT Software, Inc.

   License: Restricted

   Authors: Steven M. Cherry, Stephen D. Sager

************************************************************************** */

#include <AnException.h>
#include <EnEx.h>
#include <Log.h>
#include <XmlHelpers.h>
using namespace SLib;

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SQLTests_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/SQLTests.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< SQLTestsTest > SQLTestsTest::reg( "SQLTestsTest", "/logic/admin/SQLTestsTest" );

SQLTestsTest::SQLTestsTest()
{
	EnEx ee(FL, "SQLTestsTest::SQLTestsTest()");

}

SQLTestsTest::~SQLTestsTest()
{
	EnEx ee(FL, "SQLTestsTest::~SQLTestsTest()");

}

void SQLTestsTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLTestsTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLTestsTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unused" ){
			unused( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to SQLTestsTest", testMethod() );
		}
	}
}

bool SQLTestsTest::compareObjects( SQLTests* first, SQLTests* second)
{
	EnEx ee(FL, "SQLTestsTest::compare( SQLTests* first, SQLTests* second)" );

	if(first->TestGroupName != second->TestGroupName) return false;
	if(first->host != second->host) return false;
	if(first->pass != second->pass) return false;
	if(first->port != second->port) return false;
	if(first->user != second->user) return false;


	return true; // everything matches

}

bool SQLTestsTest::compareLists( vector< SQLTests* >* first, vector< SQLTests* >* second)
{
	EnEx ee(FL, "SQLTestsTest::compareLists( vector< SQLTests* >* first, vector< SQLTests* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!SQLTestsTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void SQLTestsTest::unused(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLTestsTest::unused(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SQLTestsTest::unused test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SQLTests inputDO( XmlHelpers::FindChild( inputNode, SQLTests::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = SQLTests::unused_prepSQL( ioc, inputDO);


	// Execute the statement
	SQLTests::unused(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

