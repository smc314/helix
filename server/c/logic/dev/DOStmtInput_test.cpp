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

#include "DOStmtInput_test.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/dev/DOStmtInput.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< DOStmtInputTest > DOStmtInputTest::reg( "DOStmtInputTest", "/logic/dev/DOStmtInputTest" );

DOStmtInputTest::DOStmtInputTest()
{
	EnEx ee(FL, "DOStmtInputTest::DOStmtInputTest()");

}

DOStmtInputTest::~DOStmtInputTest()
{
	EnEx ee(FL, "DOStmtInputTest::~DOStmtInputTest()");

}

void DOStmtInputTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtInputTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmtInputTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "insert" ){
			insert( ioc, tests[i] );
		} else if( testMethod == "update" ){
			update( ioc, tests[i] );
		} else if( testMethod == "deleteByID" ){
			deleteByID( ioc, tests[i] );
		} else if( testMethod == "deleteByStmtID" ){
			deleteByStmtID( ioc, tests[i] );
		} else if( testMethod == "selectAllForDOStmt" ){
			selectAllForDOStmt( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to DOStmtInputTest", testMethod() );
		}
	}
}

bool DOStmtInputTest::compareObjects( DOStmtInput* first, DOStmtInput* second)
{
	EnEx ee(FL, "DOStmtInputTest::compare( DOStmtInput* first, DOStmtInput* second)" );

	if(first->VarName != second->VarName) return false;
	if(first->VarType != second->VarType) return false;
	if(first->dostmtguid != second->dostmtguid) return false;
	if(first->guid != second->guid) return false;


	return true; // everything matches

}

bool DOStmtInputTest::compareLists( vector< DOStmtInput* >* first, vector< DOStmtInput* >* second)
{
	EnEx ee(FL, "DOStmtInputTest::compareLists( vector< DOStmtInput* >* first, vector< DOStmtInput* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!DOStmtInputTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void DOStmtInputTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtInputTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtInputTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmtInput inputDO( XmlHelpers::FindChild( inputNode, DOStmtInput::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmtInput::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtInputTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtInputTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtInputTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmtInput inputDO( XmlHelpers::FindChild( inputNode, DOStmtInput::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmtInput::update(sqldb, inputDO.VarName, inputDO.VarType, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtInputTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtInputTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtInputTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmtInput inputDO( XmlHelpers::FindChild( inputNode, DOStmtInput::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmtInput::deleteByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtInputTest::deleteByStmtID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtInputTest::deleteByStmtID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtInputTest::deleteByStmtID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmtInput inputDO( XmlHelpers::FindChild( inputNode, DOStmtInput::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmtInput::deleteByStmtID(sqldb, inputDO.dostmtguid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtInputTest::selectAllForDOStmt(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtInputTest::selectAllForDOStmt(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectAllForDOStmt test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectAllForDOStmt test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	DOStmtInput inputDO( XmlHelpers::FindChild( inputNode, DOStmtInput::Name()() ) );

	// Pick up our list of output objects to be used for verification
	DOStmtInput_svect outputs = DOStmtInput::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	DOStmtInput_svect vect = DOStmtInput::selectAllForDOStmt(sqldb, inputDO.dostmtguid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		DOStmtInput::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = DOStmtInputTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

