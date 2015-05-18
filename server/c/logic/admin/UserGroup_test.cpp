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

#include "UserGroup_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/UserGroup.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< UserGroupTest > UserGroupTest::reg( "UserGroupTest", "/logic/admin/UserGroupTest" );

UserGroupTest::UserGroupTest()
{
	EnEx ee(FL, "UserGroupTest::UserGroupTest()");

}

UserGroupTest::~UserGroupTest()
{
	EnEx ee(FL, "UserGroupTest::~UserGroupTest()");

}

void UserGroupTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserGroupTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to UserGroupTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "addUserGroup" ){
			addUserGroup( ioc, tests[i] );
		} else if( testMethod == "deleteGroupsForUser" ){
			deleteGroupsForUser( ioc, tests[i] );
		} else if( testMethod == "deleteUsersForGroup" ){
			deleteUsersForGroup( ioc, tests[i] );
		} else if( testMethod == "selectAll" ){
			selectAll( ioc, tests[i] );
		} else if( testMethod == "selectUsersForGroup" ){
			selectUsersForGroup( ioc, tests[i] );
		} else if( testMethod == "selectGroupsForUser" ){
			selectGroupsForUser( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to UserGroupTest", testMethod() );
		}
	}
}

bool UserGroupTest::compareObjects( UserGroup* first, UserGroup* second)
{
	EnEx ee(FL, "UserGroupTest::compare( UserGroup* first, UserGroup* second)" );

	if(first->Groupname != second->Groupname) return false;
	if(first->Username != second->Username) return false;
	if(first->groupid != second->groupid) return false;
	if(first->userid != second->userid) return false;


	return true; // everything matches

}

bool UserGroupTest::compareLists( vector< UserGroup* >* first, vector< UserGroup* >* second)
{
	EnEx ee(FL, "UserGroupTest::compareLists( vector< UserGroup* >* first, vector< UserGroup* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!UserGroupTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void UserGroupTest::addUserGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserGroupTest::addUserGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserGroupTest::addUserGroup test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	UserGroup inputDO( XmlHelpers::FindChild( inputNode, UserGroup::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	UserGroup::addUserGroup(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserGroupTest::deleteGroupsForUser(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserGroupTest::deleteGroupsForUser(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserGroupTest::deleteGroupsForUser test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	UserGroup inputDO( XmlHelpers::FindChild( inputNode, UserGroup::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	UserGroup::deleteGroupsForUser(sqldb, inputDO.userid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserGroupTest::deleteUsersForGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserGroupTest::deleteUsersForGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in UserGroupTest::deleteUsersForGroup test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	UserGroup inputDO( XmlHelpers::FindChild( inputNode, UserGroup::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	UserGroup::deleteUsersForGroup(sqldb, inputDO.groupid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void UserGroupTest::selectAll(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserGroupTest::selectAll(IOConn& ioc, xmlNodePtr node)");

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
	UserGroup inputDO( XmlHelpers::FindChild( inputNode, UserGroup::Name()() ) );

	// Pick up our list of output objects to be used for verification
	UserGroup_svect outputs = UserGroup::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	UserGroup_svect vect = UserGroup::selectAll(sqldb );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		UserGroup::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = UserGroupTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void UserGroupTest::selectUsersForGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserGroupTest::selectUsersForGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectUsersForGroup test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectUsersForGroup test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	UserGroup inputDO( XmlHelpers::FindChild( inputNode, UserGroup::Name()() ) );

	// Pick up our list of output objects to be used for verification
	UserGroup_svect outputs = UserGroup::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	UserGroup_svect vect = UserGroup::selectUsersForGroup(sqldb, inputDO.groupid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		UserGroup::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = UserGroupTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void UserGroupTest::selectGroupsForUser(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "UserGroupTest::selectGroupsForUser(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectGroupsForUser test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectGroupsForUser test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	UserGroup inputDO( XmlHelpers::FindChild( inputNode, UserGroup::Name()() ) );

	// Pick up our list of output objects to be used for verification
	UserGroup_svect outputs = UserGroup::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	UserGroup_svect vect = UserGroup::selectGroupsForUser(sqldb, inputDO.userid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		UserGroup::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = UserGroupTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

