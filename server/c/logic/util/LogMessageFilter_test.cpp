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

#include "LogMessageFilter_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/LogMessageFilter.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< LogMessageFilterTest > LogMessageFilterTest::reg( "LogMessageFilterTest", "/logic/util/LogMessageFilterTest" );

LogMessageFilterTest::LogMessageFilterTest()
{
	EnEx ee(FL, "LogMessageFilterTest::LogMessageFilterTest()");

}

LogMessageFilterTest::~LogMessageFilterTest()
{
	EnEx ee(FL, "LogMessageFilterTest::~LogMessageFilterTest()");

}

void LogMessageFilterTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogMessageFilterTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogMessageFilterTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to LogMessageFilterTest", testMethod() );
		}
	}
}

bool LogMessageFilterTest::compareObjects( LogMessageFilter* first, LogMessageFilter* second)
{
	EnEx ee(FL, "LogMessageFilterTest::compare( LogMessageFilter* first, LogMessageFilter* second)" );

	if(first->AppName != second->AppName) return false;
	if(first->Debug != second->Debug) return false;
	if(first->DispApp != second->DispApp) return false;
	if(first->DispChannel != second->DispChannel) return false;
	if(first->DispDate != second->DispDate) return false;
	if(first->DispFile != second->DispFile) return false;
	if(first->DispId != second->DispId) return false;
	if(first->DispLine != second->DispLine) return false;
	if(first->DispMachine != second->DispMachine) return false;
	if(first->DispThread != second->DispThread) return false;
	if(first->Error != second->Error) return false;
	if(first->FilterMatchCount != second->FilterMatchCount) return false;
	if(first->FindByDate != second->FindByDate) return false;
	if(first->FindByID != second->FindByID) return false;
	if(first->FindByMsg != second->FindByMsg) return false;
	if(first->FirstRow != second->FirstRow) return false;
	if(first->Forward != second->Forward) return false;
	if(first->GetMax != second->GetMax) return false;
	if(first->Info != second->Info) return false;
	if(first->LastRow != second->LastRow) return false;
	if(first->LogFile != second->LogFile) return false;
	if(first->LogFileNewestID != second->LogFileNewestID) return false;
	if(first->LogFileOldestID != second->LogFileOldestID) return false;
	if(first->MachineName != second->MachineName) return false;
	if(first->Message != second->Message) return false;
	if(first->Panic != second->Panic) return false;
	if(first->SUID != second->SUID) return false;
	if(first->ShowColApplication != second->ShowColApplication) return false;
	if(first->ShowColChannel != second->ShowColChannel) return false;
	if(first->ShowColDate != second->ShowColDate) return false;
	if(first->ShowColFile != second->ShowColFile) return false;
	if(first->ShowColID != second->ShowColID) return false;
	if(first->ShowColIcon != second->ShowColIcon) return false;
	if(first->ShowColLine != second->ShowColLine) return false;
	if(first->ShowColMachine != second->ShowColMachine) return false;
	if(first->ShowColMessage != second->ShowColMessage) return false;
	if(first->ShowColSUID != second->ShowColSUID) return false;
	if(first->ShowColThread != second->ShowColThread) return false;
	if(first->SqlTrace != second->SqlTrace) return false;
	if(first->StartId != second->StartId) return false;
	if(first->ThreadID != second->ThreadID) return false;
	if(first->Trace != second->Trace) return false;
	if(first->Warn != second->Warn) return false;


	return true; // everything matches

}

bool LogMessageFilterTest::compareLists( vector< LogMessageFilter* >* first, vector< LogMessageFilter* >* second)
{
	EnEx ee(FL, "LogMessageFilterTest::compareLists( vector< LogMessageFilter* >* first, vector< LogMessageFilter* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!LogMessageFilterTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void LogMessageFilterTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "LogMessageFilterTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in LogMessageFilterTest::unusedSqlStmt test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	LogMessageFilter inputDO( XmlHelpers::FindChild( inputNode, LogMessageFilter::Name()() ) );

	// Get a connection to our database
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare the statement
	twine stmt = LogMessageFilter::unusedSqlStmt_prepSQL( ioc, inputDO);


	// Execute the statement
	LogMessageFilter::unusedSqlStmt(odbc, stmt, false, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

