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

#include "Group_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/Group.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< GroupTest > GroupTest::reg( "GroupTest", "/logic/admin/GroupTest" );

GroupTest::GroupTest()
{
	EnEx ee(FL, "GroupTest::GroupTest()");

}

GroupTest::~GroupTest()
{
	EnEx ee(FL, "GroupTest::~GroupTest()");

}

void GroupTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to GroupTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "insert" ){
			insert( ioc, tests[i] );
		} else if( testMethod == "addUserToGroup" ){
			addUserToGroup( ioc, tests[i] );
		} else if( testMethod == "update" ){
			update( ioc, tests[i] );
		} else if( testMethod == "deleteByID" ){
			deleteByID( ioc, tests[i] );
		} else if( testMethod == "deleteUsersForGroup" ){
			deleteUsersForGroup( ioc, tests[i] );
		} else if( testMethod == "deleteActionsForGroup" ){
			deleteActionsForGroup( ioc, tests[i] );
		} else if( testMethod == "removeUserFromGroup" ){
			removeUserFromGroup( ioc, tests[i] );
		} else if( testMethod == "selectAll" ){
			selectAll( ioc, tests[i] );
		} else if( testMethod == "selectByID" ){
			selectByID( ioc, tests[i] );
		} else if( testMethod == "selectByGroupname" ){
			selectByGroupname( ioc, tests[i] );
		} else if( testMethod == "selectGroupsForUser" ){
			selectGroupsForUser( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to GroupTest", testMethod() );
		}
	}
}

bool GroupTest::compareObjects( Group* first, Group* second)
{
	EnEx ee(FL, "GroupTest::compare( Group* first, Group* second)" );

	if(first->Description != second->Description) return false;
	if(first->Groupname != second->Groupname) return false;
	if(first->id != second->id) return false;
	if(first->userid != second->userid) return false;


	return true; // everything matches

}

bool GroupTest::compareLists( vector< Group* >* first, vector< Group* >* second)
{
	EnEx ee(FL, "GroupTest::compareLists( vector< Group* >* first, vector< Group* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!GroupTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void GroupTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in GroupTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Group::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void GroupTest::addUserToGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::addUserToGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in GroupTest::addUserToGroup test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Group::addUserToGroup(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void GroupTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in GroupTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Group::update(sqldb, inputDO.Groupname, inputDO.Description, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void GroupTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in GroupTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Group::deleteByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void GroupTest::deleteUsersForGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::deleteUsersForGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in GroupTest::deleteUsersForGroup test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Group::deleteUsersForGroup(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void GroupTest::deleteActionsForGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::deleteActionsForGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in GroupTest::deleteActionsForGroup test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Group::deleteActionsForGroup(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void GroupTest::removeUserFromGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::removeUserFromGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in GroupTest::removeUserFromGroup test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Group::removeUserFromGroup(sqldb, inputDO.userid, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void GroupTest::selectAll(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::selectAll(IOConn& ioc, xmlNodePtr node)");

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
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Group_svect outputs = Group::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Group_svect vect = Group::selectAll(sqldb );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Group::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = GroupTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void GroupTest::selectByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::selectByID(IOConn& ioc, xmlNodePtr node)");

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
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Group_svect outputs = Group::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Group_svect vect = Group::selectByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Group::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = GroupTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void GroupTest::selectByGroupname(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::selectByGroupname(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectByGroupname test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectByGroupname test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Group_svect outputs = Group::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Group_svect vect = Group::selectByGroupname(sqldb, inputDO.Groupname );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Group::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = GroupTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void GroupTest::selectGroupsForUser(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "GroupTest::selectGroupsForUser(IOConn& ioc, xmlNodePtr node)");

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
	Group inputDO( XmlHelpers::FindChild( inputNode, Group::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Group_svect outputs = Group::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Group_svect vect = Group::selectGroupsForUser(sqldb, inputDO.userid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Group::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = GroupTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

