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

#include "Col_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/Col.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< ColTest > ColTest::reg( "ColTest", "/logic/admin/ColTest" );

ColTest::ColTest()
{
	EnEx ee(FL, "ColTest::ColTest()");

}

ColTest::~ColTest()
{
	EnEx ee(FL, "ColTest::~ColTest()");

}

void ColTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ColTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ColTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unused" ){
			unused( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to ColTest", testMethod() );
		}
	}
}

bool ColTest::compareObjects( Col* first, Col* second)
{
	EnEx ee(FL, "ColTest::compare( Col* first, Col* second)" );

	if(first->colName != second->colName) return false;
	if(first->dataValue != second->dataValue) return false;
	if(first->idx != second->idx) return false;
	if(first->typeName != second->typeName) return false;
	if(first->verifyData != second->verifyData) return false;


	return true; // everything matches

}

bool ColTest::compareLists( vector< Col* >* first, vector< Col* >* second)
{
	EnEx ee(FL, "ColTest::compareLists( vector< Col* >* first, vector< Col* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!ColTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void ColTest::unused(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ColTest::unused(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ColTest::unused test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Col inputDO( XmlHelpers::FindChild( inputNode, Col::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = Col::unused_prepSQL( ioc, inputDO);


	// Execute the statement
	Col::unused(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

