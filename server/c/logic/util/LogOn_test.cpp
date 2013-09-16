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

#include "LogOn_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/LogOn.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< LogOnTest > LogOnTest::reg( "LogOnTest", "/logic/util/LogOnTest" );

LogOnTest::LogOnTest()
{
	EnEx ee(FL, "LogOnTest::LogOnTest()");

}

LogOnTest::~LogOnTest()
{
	EnEx ee(FL, "LogOnTest::~LogOnTest()");

}

void LogOnTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogOnTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogOnTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to LogOnTest", testMethod() );
		}
	}
}

bool LogOnTest::compareObjects( LogOn* first, LogOn* second)
{
	EnEx ee(FL, "LogOnTest::compare( LogOn* first, LogOn* second)" );

	if(first->Alias != second->Alias) return false;
	if(first->ConnName != second->ConnName) return false;
	if(first->Host != second->Host) return false;
	if(first->Pass != second->Pass) return false;
	if(first->Port != second->Port) return false;
	if(first->User != second->User) return false;


	return true; // everything matches

}

bool LogOnTest::compareLists( vector< LogOn* >* first, vector< LogOn* >* second)
{
	EnEx ee(FL, "LogOnTest::compareLists( vector< LogOn* >* first, vector< LogOn* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!LogOnTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void LogOnTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogOnTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in unusedSqlStmt test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in unusedSqlStmt test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	LogOn inputDO( XmlHelpers::FindChild( inputNode, LogOn::Name()() ) );

	// Pick up our list of output objects to be used for verification
	LogOn_svect outputs = LogOn::readXmlChildren( outputNode );

	// Get a connection to our database:
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare and execute the statement
	twine stmt = LogOn::unusedSqlStmt_prepSQL( ioc, inputDO.Host, inputDO.Port, inputDO.User, inputDO.Pass, inputDO.Alias );
	LogOn_svect vect = LogOn::unusedSqlStmt( odbc, stmt, false, inputDO.Host, inputDO.Port, inputDO.User, inputDO.Pass, inputDO.Alias );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		LogOn::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = LogOnTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

