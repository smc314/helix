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

#include "IAFolder_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/IAFolder.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< IAFolderTest > IAFolderTest::reg( "IAFolderTest", "/logic/admin/IAFolderTest" );

IAFolderTest::IAFolderTest()
{
	EnEx ee(FL, "IAFolderTest::IAFolderTest()");

}

IAFolderTest::~IAFolderTest()
{
	EnEx ee(FL, "IAFolderTest::~IAFolderTest()");

}

void IAFolderTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "IAFolderTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFolderTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to IAFolderTest", testMethod() );
		}
	}
}

bool IAFolderTest::compareObjects( IAFolder* first, IAFolder* second)
{
	EnEx ee(FL, "IAFolderTest::compare( IAFolder* first, IAFolder* second)" );

	if(first->Description != second->Description) return false;
	if(first->FolderName != second->FolderName) return false;
	if(first->ParentFolder != second->ParentFolder) return false;


	return true; // everything matches

}

bool IAFolderTest::compareLists( vector< IAFolder* >* first, vector< IAFolder* >* second)
{
	EnEx ee(FL, "IAFolderTest::compareLists( vector< IAFolder* >* first, vector< IAFolder* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!IAFolderTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void IAFolderTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "IAFolderTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

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
	IAFolder inputDO( XmlHelpers::FindChild( inputNode, IAFolder::Name()() ) );

	// Pick up our list of output objects to be used for verification
	IAFolder_svect outputs = IAFolder::readXmlChildren( outputNode );

	// Get a connection to our database:
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare and execute the statement
	twine stmt = IAFolder::unusedSqlStmt_prepSQL( ioc, inputDO.ParentFolder );
	IAFolder_svect vect = IAFolder::unusedSqlStmt( odbc, stmt, false, inputDO.ParentFolder );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		IAFolder::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = IAFolderTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

