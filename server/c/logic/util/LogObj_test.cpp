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

#include "LogObj_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/LogObj.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< LogObjTest > LogObjTest::reg( "LogObjTest", "/logic/util/LogObjTest" );

LogObjTest::LogObjTest()
{
	EnEx ee(FL, "LogObjTest::LogObjTest()");

}

LogObjTest::~LogObjTest()
{
	EnEx ee(FL, "LogObjTest::~LogObjTest()");

}

void LogObjTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogObjTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogObjTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to LogObjTest", testMethod() );
		}
	}
}

bool LogObjTest::compareObjects( LogObj* first, LogObj* second)
{
	EnEx ee(FL, "LogObjTest::compare( LogObj* first, LogObj* second)" );

	if(first->SUID != second->SUID) return false;
	if(first->appName != second->appName) return false;
	if(first->channel != second->channel) return false;
	if(first->file != second->file) return false;
	if(first->id != second->id) return false;
	if(first->line != second->line) return false;
	if(first->machineName != second->machineName) return false;
	if(first->msg != second->msg) return false;
	if(first->tid != second->tid) return false;
	if(first->timestamp_a != second->timestamp_a) return false;
	if(first->timestamp_b != second->timestamp_b) return false;
	if(first->timestamp_c != second->timestamp_c) return false;


	return true; // everything matches

}

bool LogObjTest::compareLists( vector< LogObj* >* first, vector< LogObj* >* second)
{
	EnEx ee(FL, "LogObjTest::compareLists( vector< LogObj* >* first, vector< LogObj* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!LogObjTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void LogObjTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogObjTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in LogObjTest::unusedSqlStmt test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	LogObj inputDO( XmlHelpers::FindChild( inputNode, LogObj::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = LogObj::unusedSqlStmt_prepSQL( ioc, inputDO);


	// Execute the statement
	LogObj::unusedSqlStmt(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

