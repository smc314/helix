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

#include "Session_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/Session.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< SessionTest > SessionTest::reg( "SessionTest", "/logic/admin/SessionTest" );

SessionTest::SessionTest()
{
	EnEx ee(FL, "SessionTest::SessionTest()");

}

SessionTest::~SessionTest()
{
	EnEx ee(FL, "SessionTest::~SessionTest()");

}

void SessionTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SessionTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SessionTest::runTests is NULL.");
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
		} else if( testMethod == "selectAll" ){
			selectAll( ioc, tests[i] );
		} else if( testMethod == "selectByID" ){
			selectByID( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to SessionTest", testMethod() );
		}
	}
}

bool SessionTest::compareObjects( Session* first, Session* second)
{
	EnEx ee(FL, "SessionTest::compare( Session* first, Session* second)" );

	if(first->Active != second->Active) return false;
	if(!(first->Created == second->Created)) return false;
	if(!(first->LastAccess == second->LastAccess)) return false;
	if(first->Userid != second->Userid) return false;
	if(first->guid != second->guid) return false;


	return true; // everything matches

}

bool SessionTest::compareLists( vector< Session* >* first, vector< Session* >* second)
{
	EnEx ee(FL, "SessionTest::compareLists( vector< Session* >* first, vector< Session* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!SessionTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void SessionTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SessionTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SessionTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Session inputDO( XmlHelpers::FindChild( inputNode, Session::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Session::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void SessionTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SessionTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SessionTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Session inputDO( XmlHelpers::FindChild( inputNode, Session::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Session::update(sqldb, inputDO.Userid, inputDO.Created, inputDO.LastAccess, inputDO.Active, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void SessionTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SessionTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SessionTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Session inputDO( XmlHelpers::FindChild( inputNode, Session::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Session::deleteByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void SessionTest::selectAll(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SessionTest::selectAll(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectAll test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectAll test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Session inputDO( XmlHelpers::FindChild( inputNode, Session::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Session_svect outputs = Session::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Session_svect vect = Session::selectAll(sqldb );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Session::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = SessionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void SessionTest::selectByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SessionTest::selectByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectByID test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectByID test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Session inputDO( XmlHelpers::FindChild( inputNode, Session::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Session_svect outputs = Session::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Session_svect vect = Session::selectByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Session::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = SessionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

