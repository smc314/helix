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

#include "User_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/User.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< UserTest > UserTest::reg( "UserTest", "/logic/admin/UserTest" );

UserTest::UserTest()
{
	EnEx ee(FL, "UserTest::UserTest()");

}

UserTest::~UserTest()
{
	EnEx ee(FL, "UserTest::~UserTest()");

}

void UserTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to UserTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "insert" ){
			insert( ioc, tests[i] );
		} else if( testMethod == "insertAuth" ){
			insertAuth( ioc, tests[i] );
		} else if( testMethod == "update" ){
			update( ioc, tests[i] );
		} else if( testMethod == "updateAuth" ){
			updateAuth( ioc, tests[i] );
		} else if( testMethod == "deleteByID" ){
			deleteByID( ioc, tests[i] );
		} else if( testMethod == "deleteAuthByID" ){
			deleteAuthByID( ioc, tests[i] );
		} else if( testMethod == "selectAll" ){
			selectAll( ioc, tests[i] );
		} else if( testMethod == "selectByID" ){
			selectByID( ioc, tests[i] );
		} else if( testMethod == "selectByUsername" ){
			selectByUsername( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to UserTest", testMethod() );
		}
	}
}

bool UserTest::compareObjects( User* first, User* second)
{
	EnEx ee(FL, "UserTest::compare( User* first, User* second)" );

	if(first->Active != second->Active) return false;
	if(first->AuthMechanism != second->AuthMechanism) return false;
	if(first->EMail != second->EMail) return false;
	if(first->FullName != second->FullName) return false;
	if(first->Password != second->Password) return false;
	if(first->Username != second->Username) return false;
	if(first->id != second->id) return false;


	return true; // everything matches

}

bool UserTest::compareLists( vector< User* >* first, vector< User* >* second)
{
	EnEx ee(FL, "UserTest::compareLists( vector< User* >* first, vector< User* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!UserTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void UserTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	User::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserTest::insertAuth(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::insertAuth(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserTest::insertAuth test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	User::insertAuth(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	User::update(sqldb, inputDO.Username, inputDO.FullName, inputDO.EMail, inputDO.Active, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserTest::updateAuth(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::updateAuth(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserTest::updateAuth test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	User::updateAuth(sqldb, inputDO.AuthMechanism, inputDO.Password, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	User::deleteByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserTest::deleteAuthByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::deleteAuthByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserTest::deleteAuthByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	User::deleteAuthByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserTest::selectAll(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::selectAll(IOConn& ioc, xmlNodePtr node)");

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
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Pick up our list of output objects to be used for verification
	User_svect outputs = User::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	User_svect vect = User::selectAll(sqldb );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		User::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = UserTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void UserTest::selectByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::selectByID(IOConn& ioc, xmlNodePtr node)");

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
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Pick up our list of output objects to be used for verification
	User_svect outputs = User::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	User_svect vect = User::selectByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		User::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = UserTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void UserTest::selectByUsername(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserTest::selectByUsername(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectByUsername test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectByUsername test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	User inputDO( XmlHelpers::FindChild( inputNode, User::Name()() ) );

	// Pick up our list of output objects to be used for verification
	User_svect outputs = User::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	User_svect vect = User::selectByUsername(sqldb, inputDO.Username );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		User::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = UserTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

