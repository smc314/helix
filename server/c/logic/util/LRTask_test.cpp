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

#include "LRTask_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/LRTask.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< LRTaskTest > LRTaskTest::reg( "LRTaskTest", "/logic/util/LRTaskTest" );

LRTaskTest::LRTaskTest()
{
	EnEx ee(FL, "LRTaskTest::LRTaskTest()");

}

LRTaskTest::~LRTaskTest()
{
	EnEx ee(FL, "LRTaskTest::~LRTaskTest()");

}

void LRTaskTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LRTaskTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LRTaskTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to LRTaskTest", testMethod() );
		}
	}
}

bool LRTaskTest::compareObjects( LRTask* first, LRTask* second)
{
	EnEx ee(FL, "LRTaskTest::compare( LRTask* first, LRTask* second)" );

	if(first->TaskCurrent != second->TaskCurrent) return false;
	if(first->TaskFinish != second->TaskFinish) return false;
	if(first->TaskID != second->TaskID) return false;
	if(first->TaskMsg != second->TaskMsg) return false;
	if(first->TaskName != second->TaskName) return false;
	if(first->TaskResponse != second->TaskResponse) return false;
	if(first->TaskStart != second->TaskStart) return false;


	return true; // everything matches

}

bool LRTaskTest::compareLists( vector< LRTask* >* first, vector< LRTask* >* second)
{
	EnEx ee(FL, "LRTaskTest::compareLists( vector< LRTask* >* first, vector< LRTask* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!LRTaskTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void LRTaskTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LRTaskTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in LRTaskTest::unusedSqlStmt test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	LRTask inputDO( XmlHelpers::FindChild( inputNode, LRTask::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = LRTask::unusedSqlStmt_prepSQL( ioc, inputDO);


	// Execute the statement
	LRTask::unusedSqlStmt(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

