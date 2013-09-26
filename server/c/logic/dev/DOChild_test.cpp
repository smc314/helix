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

#include "DOChild_test.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/dev/DOChild.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< DOChildTest > DOChildTest::reg( "DOChildTest", "/logic/dev/DOChildTest" );

DOChildTest::DOChildTest()
{
	EnEx ee(FL, "DOChildTest::DOChildTest()");

}

DOChildTest::~DOChildTest()
{
	EnEx ee(FL, "DOChildTest::~DOChildTest()");

}

void DOChildTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOChildTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOChildTest::runTests is NULL.");
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
			WARN(FL, "Unknown test method (%s) given to DOChildTest", testMethod() );
		}
	}
}

bool DOChildTest::compareObjects( DOChild* first, DOChild* second)
{
	EnEx ee(FL, "DOChildTest::compare( DOChild* first, DOChild* second)" );

	if(first->VectorName != second->VectorName) return false;
	if(first->VectorType != second->VectorType) return false;
	if(first->doguid != second->doguid) return false;
	if(first->guid != second->guid) return false;


	return true; // everything matches

}

bool DOChildTest::compareLists( vector< DOChild* >* first, vector< DOChild* >* second)
{
	EnEx ee(FL, "DOChildTest::compareLists( vector< DOChild* >* first, vector< DOChild* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!DOChildTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void DOChildTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOChildTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOChildTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOChild inputDO( XmlHelpers::FindChild( inputNode, DOChild::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOChild::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOChildTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOChildTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOChildTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOChild inputDO( XmlHelpers::FindChild( inputNode, DOChild::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOChild::update(sqldb, inputDO.VectorName, inputDO.VectorType, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOChildTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOChildTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOChildTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOChild inputDO( XmlHelpers::FindChild( inputNode, DOChild::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOChild::deleteByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOChildTest::deleteByDOID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOChildTest::deleteByDOID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in DOChildTest::deleteByDOID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	DOChild inputDO( XmlHelpers::FindChild( inputNode, DOChild::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	DOChild::deleteByDOID(sqldb, inputDO.doguid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void DOChildTest::selectAllForDO(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "DOChildTest::selectAllForDO(IOConn& ioc, xmlNodePtr node)");

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
	DOChild inputDO( XmlHelpers::FindChild( inputNode, DOChild::Name()() ) );

	// Pick up our list of output objects to be used for verification
	DOChild_svect outputs = DOChild::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	DOChild_svect vect = DOChild::selectAllForDO(sqldb, inputDO.doguid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		DOChild::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = DOChildTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

