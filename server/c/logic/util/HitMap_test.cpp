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

#include "HitMap_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/HitMap.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< HitMapTest > HitMapTest::reg( "HitMapTest", "/logic/util/HitMapTest" );

HitMapTest::HitMapTest()
{
	EnEx ee(FL, "HitMapTest::HitMapTest()");

}

HitMapTest::~HitMapTest()
{
	EnEx ee(FL, "HitMapTest::~HitMapTest()");

}

void HitMapTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "HitMapTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to HitMapTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "dummy" ){
			dummy( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to HitMapTest", testMethod() );
		}
	}
}

bool HitMapTest::compareObjects( HitMap* first, HitMap* second)
{
	EnEx ee(FL, "HitMapTest::compare( HitMap* first, HitMap* second)" );

	if(first->AverageCycles != second->AverageCycles) return false;
	if(first->MaxCycles != second->MaxCycles) return false;
	if(first->MethodName != second->MethodName) return false;
	if(first->MinCycles != second->MinCycles) return false;
	if(first->TotalCycles != second->TotalCycles) return false;
	if(first->TotalHits != second->TotalHits) return false;


	return true; // everything matches

}

bool HitMapTest::compareLists( vector< HitMap* >* first, vector< HitMap* >* second)
{
	EnEx ee(FL, "HitMapTest::compareLists( vector< HitMap* >* first, vector< HitMap* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!HitMapTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void HitMapTest::dummy(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "HitMapTest::dummy(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in HitMapTest::dummy test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	HitMap inputDO( XmlHelpers::FindChild( inputNode, HitMap::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = HitMap::dummy_prepSQL( ioc, inputDO);


	// Execute the statement
	HitMap::dummy(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

