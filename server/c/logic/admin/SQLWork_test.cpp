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

#include "SQLWork_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/SQLWork.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< SQLWorkTest > SQLWorkTest::reg( "SQLWorkTest", "/logic/admin/SQLWorkTest" );

SQLWorkTest::SQLWorkTest()
{
	EnEx ee(FL, "SQLWorkTest::SQLWorkTest()");

}

SQLWorkTest::~SQLWorkTest()
{
	EnEx ee(FL, "SQLWorkTest::~SQLWorkTest()");

}

void SQLWorkTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLWorkTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLWorkTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unused" ){
			unused( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to SQLWorkTest", testMethod() );
		}
	}
}

bool SQLWorkTest::compareObjects( SQLWork* first, SQLWork* second)
{
	EnEx ee(FL, "SQLWorkTest::compare( SQLWork* first, SQLWork* second)" );

	if(first->AciInMap != second->AciInMap) return false;
	if(first->AciOutMap != second->AciOutMap) return false;
	if(first->AciService != second->AciService) return false;
	if(first->BuildSql != second->BuildSql) return false;
	if(first->Code != second->Code) return false;
	if(first->ConvertSql != second->ConvertSql) return false;
	if(first->Description != second->Description) return false;
	if(first->FileName != second->FileName) return false;
	if(first->HostDB != second->HostDB) return false;
	if(first->Owner != second->Owner) return false;
	if(first->Pfkey != second->Pfkey) return false;
	if(first->Sql != second->Sql) return false;
	if(first->Type != second->Type) return false;


	return true; // everything matches

}

bool SQLWorkTest::compareLists( vector< SQLWork* >* first, vector< SQLWork* >* second)
{
	EnEx ee(FL, "SQLWorkTest::compareLists( vector< SQLWork* >* first, vector< SQLWork* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!SQLWorkTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void SQLWorkTest::unused(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SQLWorkTest::unused(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SQLWorkTest::unused test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SQLWork inputDO( XmlHelpers::FindChild( inputNode, SQLWork::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = SQLWork::unused_prepSQL( ioc, inputDO);


	// Execute the statement
	SQLWork::unused(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

