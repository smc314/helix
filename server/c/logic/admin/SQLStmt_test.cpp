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

#include "SQLStmt_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/SQLStmt.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< SQLStmtTest > SQLStmtTest::reg( "SQLStmtTest", "/logic/admin/SQLStmtTest" );

SQLStmtTest::SQLStmtTest()
{
	EnEx ee(FL, "SQLStmtTest::SQLStmtTest()");

}

SQLStmtTest::~SQLStmtTest()
{
	EnEx ee(FL, "SQLStmtTest::~SQLStmtTest()");

}

void SQLStmtTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLStmtTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStmtTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unused" ){
			unused( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to SQLStmtTest", testMethod() );
		}
	}
}

bool SQLStmtTest::compareObjects( SQLStmt* first, SQLStmt* second)
{
	EnEx ee(FL, "SQLStmtTest::compare( SQLStmt* first, SQLStmt* second)" );

	if(first->Description != second->Description) return false;
	if(first->Duration != second->Duration) return false;
	if(first->StatementName != second->StatementName) return false;
	if(first->expectErrors != second->expectErrors) return false;
	if(first->expectedErrorMsg != second->expectedErrorMsg) return false;
	if(first->expectedRows != second->expectedRows) return false;
	if(first->ignoreErrors != second->ignoreErrors) return false;
	if(first->isSelected != second->isSelected) return false;
	if(first->issueCommit != second->issueCommit) return false;
	if(first->issueRollback != second->issueRollback) return false;
	if(first->newConnection != second->newConnection) return false;
	if(first->status != second->status) return false;
	if(first->statusMessage != second->statusMessage) return false;
	if(first->stmt != second->stmt) return false;
	if(first->verifyData != second->verifyData) return false;


	return true; // everything matches

}

bool SQLStmtTest::compareLists( vector< SQLStmt* >* first, vector< SQLStmt* >* second)
{
	EnEx ee(FL, "SQLStmtTest::compareLists( vector< SQLStmt* >* first, vector< SQLStmt* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!SQLStmtTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void SQLStmtTest::unused(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLStmtTest::unused(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SQLStmtTest::unused test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SQLStmt inputDO( XmlHelpers::FindChild( inputNode, SQLStmt::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = SQLStmt::unused_prepSQL( ioc, inputDO);


	// Execute the statement
	SQLStmt::unused(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

