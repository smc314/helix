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

#include "Row_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/Row.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< RowTest > RowTest::reg( "RowTest", "/logic/admin/RowTest" );

RowTest::RowTest()
{
	EnEx ee(FL, "RowTest::RowTest()");

}

RowTest::~RowTest()
{
	EnEx ee(FL, "RowTest::~RowTest()");

}

void RowTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "RowTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to RowTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unused" ){
			unused( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to RowTest", testMethod() );
		}
	}
}

bool RowTest::compareObjects( Row* first, Row* second)
{
	EnEx ee(FL, "RowTest::compare( Row* first, Row* second)" );

	if(first->idx != second->idx) return false;


	return true; // everything matches

}

bool RowTest::compareLists( vector< Row* >* first, vector< Row* >* second)
{
	EnEx ee(FL, "RowTest::compareLists( vector< Row* >* first, vector< Row* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!RowTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void RowTest::unused(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "RowTest::unused(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in RowTest::unused test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Row inputDO( XmlHelpers::FindChild( inputNode, Row::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = Row::unused_prepSQL( ioc, inputDO);


	// Execute the statement
	Row::unused(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

