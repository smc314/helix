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

#include "SQLStatement_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/SQLStatement.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< SQLStatementTest > SQLStatementTest::reg( "SQLStatementTest", "/logic/util/SQLStatementTest" );

SQLStatementTest::SQLStatementTest()
{
	EnEx ee(FL, "SQLStatementTest::SQLStatementTest()");

}

SQLStatementTest::~SQLStatementTest()
{
	EnEx ee(FL, "SQLStatementTest::~SQLStatementTest()");

}

void SQLStatementTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLStatementTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStatementTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to SQLStatementTest", testMethod() );
		}
	}
}

bool SQLStatementTest::compareObjects( SQLStatement* first, SQLStatement* second)
{
	EnEx ee(FL, "SQLStatementTest::compare( SQLStatement* first, SQLStatement* second)" );

	if(first->HostDB != second->HostDB) return false;
	if(first->Sql != second->Sql) return false;


	return true; // everything matches

}

bool SQLStatementTest::compareLists( vector< SQLStatement* >* first, vector< SQLStatement* >* second)
{
	EnEx ee(FL, "SQLStatementTest::compareLists( vector< SQLStatement* >* first, vector< SQLStatement* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!SQLStatementTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void SQLStatementTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLStatementTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SQLStatementTest::unusedSqlStmt test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SQLStatement inputDO( XmlHelpers::FindChild( inputNode, SQLStatement::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = SQLStatement::unusedSqlStmt_prepSQL( ioc, inputDO);


	// Execute the statement
	SQLStatement::unusedSqlStmt(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

