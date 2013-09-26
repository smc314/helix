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

#include "DOStmt_test.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/dev/DOStmt.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< DOStmtTest > DOStmtTest::reg( "DOStmtTest", "/logic/dev/DOStmtTest" );

DOStmtTest::DOStmtTest()
{
	EnEx ee(FL, "DOStmtTest::DOStmtTest()");

}

DOStmtTest::~DOStmtTest()
{
	EnEx ee(FL, "DOStmtTest::~DOStmtTest()");

}

void DOStmtTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmtTest::runTests is NULL.");
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
		} else if( testMethod == "deleteByDOID" ){
			deleteByDOID( ioc, tests[i] );
		} else if( testMethod == "selectAllForDO" ){
			selectAllForDO( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to DOStmtTest", testMethod() );
		}
	}
}

bool DOStmtTest::compareObjects( DOStmt* first, DOStmt* second)
{
	EnEx ee(FL, "DOStmtTest::compare( DOStmt* first, DOStmt* second)" );

	if(first->Comment != second->Comment) return false;
	if(first->Sql != second->Sql) return false;
	if(first->StmtName != second->StmtName) return false;
	if(first->StmtType != second->StmtType) return false;
	if(first->doguid != second->doguid) return false;
	if(first->guid != second->guid) return false;
	if(first->projdataguid != second->projdataguid) return false;


	return true; // everything matches

}

bool DOStmtTest::compareLists( vector< DOStmt* >* first, vector< DOStmt* >* second)
{
	EnEx ee(FL, "DOStmtTest::compareLists( vector< DOStmt* >* first, vector< DOStmt* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!DOStmtTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void DOStmtTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmt inputDO( XmlHelpers::FindChild( inputNode, DOStmt::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmt::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmt inputDO( XmlHelpers::FindChild( inputNode, DOStmt::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmt::update(sqldb, inputDO.StmtName, inputDO.StmtType, inputDO.projdataguid, inputDO.Comment, inputDO.Sql, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmt inputDO( XmlHelpers::FindChild( inputNode, DOStmt::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmt::deleteByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtTest::deleteByDOID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtTest::deleteByDOID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOStmtTest::deleteByDOID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOStmt inputDO( XmlHelpers::FindChild( inputNode, DOStmt::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOStmt::deleteByDOID(sqldb, inputDO.doguid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOStmtTest::selectAllForDO(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtTest::selectAllForDO(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectAllForDO test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectAllForDO test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	DOStmt inputDO( XmlHelpers::FindChild( inputNode, DOStmt::Name()() ) );

	// Pick up our list of output objects to be used for verification
	DOStmt_svect outputs = DOStmt::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	DOStmt_svect vect = DOStmt::selectAllForDO(sqldb, inputDO.doguid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		DOStmt::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = DOStmtTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

