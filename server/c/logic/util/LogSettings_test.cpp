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

#include "LogSettings_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/LogSettings.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< LogSettingsTest > LogSettingsTest::reg( "LogSettingsTest", "/logic/util/LogSettingsTest" );

LogSettingsTest::LogSettingsTest()
{
	EnEx ee(FL, "LogSettingsTest::LogSettingsTest()");

}

LogSettingsTest::~LogSettingsTest()
{
	EnEx ee(FL, "LogSettingsTest::~LogSettingsTest()");

}

void LogSettingsTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogSettingsTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogSettingsTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to LogSettingsTest", testMethod() );
		}
	}
}

bool LogSettingsTest::compareObjects( LogSettings* first, LogSettings* second)
{
	EnEx ee(FL, "LogSettingsTest::compare( LogSettings* first, LogSettings* second)" );

	if(first->BufferSize != second->BufferSize) return false;
	if(first->LogFile != second->LogFile) return false;
	if(first->MaxSize != second->MaxSize) return false;
	if(first->debug != second->debug) return false;
	if(first->debugCapture != second->debugCapture) return false;
	if(first->debugDump != second->debugDump) return false;
	if(first->error != second->error) return false;
	if(first->errorCapture != second->errorCapture) return false;
	if(first->errorDump != second->errorDump) return false;
	if(first->info != second->info) return false;
	if(first->infoCapture != second->infoCapture) return false;
	if(first->infoDump != second->infoDump) return false;
	if(first->panic != second->panic) return false;
	if(first->panicCapture != second->panicCapture) return false;
	if(first->panicDump != second->panicDump) return false;
	if(first->sql != second->sql) return false;
	if(first->sqlCapture != second->sqlCapture) return false;
	if(first->sqlDump != second->sqlDump) return false;
	if(first->trace != second->trace) return false;
	if(first->traceCapture != second->traceCapture) return false;
	if(first->traceDump != second->traceDump) return false;
	if(first->warn != second->warn) return false;
	if(first->warnCapture != second->warnCapture) return false;
	if(first->warnDump != second->warnDump) return false;


	return true; // everything matches

}

bool LogSettingsTest::compareLists( vector< LogSettings* >* first, vector< LogSettings* >* second)
{
	EnEx ee(FL, "LogSettingsTest::compareLists( vector< LogSettings* >* first, vector< LogSettings* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!LogSettingsTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void LogSettingsTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogSettingsTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in LogSettingsTest::unusedSqlStmt test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	LogSettings inputDO( XmlHelpers::FindChild( inputNode, LogSettings::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = LogSettings::unusedSqlStmt_prepSQL( ioc, inputDO);


	// Execute the statement
	LogSettings::unusedSqlStmt(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

