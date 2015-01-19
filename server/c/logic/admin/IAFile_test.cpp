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

#include "IAFile_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/IAFile.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< IAFileTest > IAFileTest::reg( "IAFileTest", "/logic/admin/IAFileTest" );

IAFileTest::IAFileTest()
{
	EnEx ee(FL, "IAFileTest::IAFileTest()");

}

IAFileTest::~IAFileTest()
{
	EnEx ee(FL, "IAFileTest::~IAFileTest()");

}

void IAFileTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "IAFileTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFileTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "unusedSqlStmt" ){
			unusedSqlStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to IAFileTest", testMethod() );
		}
	}
}

bool IAFileTest::compareObjects( IAFile* first, IAFile* second)
{
	EnEx ee(FL, "IAFileTest::compare( IAFile* first, IAFile* second)" );

	if(first->Description != second->Description) return false;
	if(first->FileContents != second->FileContents) return false;
	if(first->FileName != second->FileName) return false;
	if(first->FileSize != second->FileSize) return false;
	if(first->MoveDest != second->MoveDest) return false;
	if(first->MoveSource != second->MoveSource) return false;
	if(first->ParentFolder != second->ParentFolder) return false;
	if(first->ReturnCode != second->ReturnCode) return false;
	if(first->Status != second->Status) return false;
	if(first->Step != second->Step) return false;
	if(first->TargetFolder != second->TargetFolder) return false;
	if(first->Title != second->Title) return false;
	if(first->Type != second->Type) return false;
	if(first->isVSE != second->isVSE) return false;
	if(first->isZOS != second->isZOS) return false;


	return true; // everything matches

}

bool IAFileTest::compareLists( vector< IAFile* >* first, vector< IAFile* >* second)
{
	EnEx ee(FL, "IAFileTest::compareLists( vector< IAFile* >* first, vector< IAFile* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!IAFileTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void IAFileTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "IAFileTest::unusedSqlStmt(IOConn& ioc, xmlNodePtr node)");

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
	IAFile inputDO( XmlHelpers::FindChild( inputNode, IAFile::Name()() ) );

	// Pick up our list of output objects to be used for verification
	IAFile_svect outputs = IAFile::readXmlChildren( outputNode );

	// Get a connection to our database:
	OdbcObj& odbc = *ioc.getDBConnection();

	// Prepare and execute the statement
	twine stmt = IAFile::unusedSqlStmt_prepSQL( ioc, inputDO.isZOS, inputDO.isVSE, inputDO.FileSize );
	IAFile_svect vect = IAFile::unusedSqlStmt( odbc, stmt, false, inputDO.isZOS, inputDO.isVSE, inputDO.FileSize );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		IAFile::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = IAFileTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

