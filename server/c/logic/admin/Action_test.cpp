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

#include "Action_test.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/admin/Action.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< ActionTest > ActionTest::reg( "ActionTest", "/logic/admin/ActionTest" );

ActionTest::ActionTest()
{
	EnEx ee(FL, "ActionTest::ActionTest()");

}

ActionTest::~ActionTest()
{
	EnEx ee(FL, "ActionTest::~ActionTest()");

}

void ActionTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ActionTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "insert" ){
			insert( ioc, tests[i] );
		} else if( testMethod == "addUserToAction" ){
			addUserToAction( ioc, tests[i] );
		} else if( testMethod == "addGroupToAction" ){
			addGroupToAction( ioc, tests[i] );
		} else if( testMethod == "update" ){
			update( ioc, tests[i] );
		} else if( testMethod == "deleteByID" ){
			deleteByID( ioc, tests[i] );
		} else if( testMethod == "removeUserFromAction" ){
			removeUserFromAction( ioc, tests[i] );
		} else if( testMethod == "removeGroupFromAction" ){
			removeGroupFromAction( ioc, tests[i] );
		} else if( testMethod == "selectAll" ){
			selectAll( ioc, tests[i] );
		} else if( testMethod == "selectByID" ){
			selectByID( ioc, tests[i] );
		} else if( testMethod == "selectByPath" ){
			selectByPath( ioc, tests[i] );
		} else if( testMethod == "selectActionsForUser" ){
			selectActionsForUser( ioc, tests[i] );
		} else if( testMethod == "selectActionsForUserByGroup" ){
			selectActionsForUserByGroup( ioc, tests[i] );
		} else if( testMethod == "checkActionForUser" ){
			checkActionForUser( ioc, tests[i] );
		} else if( testMethod == "checkActionForUserByGroup" ){
			checkActionForUserByGroup( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to ActionTest", testMethod() );
		}
	}
}

bool ActionTest::compareObjects( Action* first, Action* second)
{
	EnEx ee(FL, "ActionTest::compare( Action* first, Action* second)" );

	if(first->Allow != second->Allow) return false;
	if(first->OKWOSession != second->OKWOSession) return false;
	if(first->Path != second->Path) return false;
	if(first->groupid != second->groupid) return false;
	if(first->id != second->id) return false;
	if(first->userid != second->userid) return false;


	return true; // everything matches

}

bool ActionTest::compareLists( vector< Action* >* first, vector< Action* >* second)
{
	EnEx ee(FL, "ActionTest::compareLists( vector< Action* >* first, vector< Action* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!ActionTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void ActionTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ActionTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Action::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ActionTest::addUserToAction(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::addUserToAction(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ActionTest::addUserToAction test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Action::addUserToAction(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ActionTest::addGroupToAction(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::addGroupToAction(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ActionTest::addGroupToAction test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Action::addGroupToAction(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ActionTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ActionTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Action::update(sqldb, inputDO.Path, inputDO.OKWOSession, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ActionTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ActionTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Action::deleteByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ActionTest::removeUserFromAction(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::removeUserFromAction(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ActionTest::removeUserFromAction test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Action::removeUserFromAction(sqldb, inputDO.userid, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ActionTest::removeGroupFromAction(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::removeGroupFromAction(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ActionTest::removeGroupFromAction test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	Action::removeGroupFromAction(sqldb, inputDO.groupid, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ActionTest::selectAll(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::selectAll(IOConn& ioc, xmlNodePtr node)");

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
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Action_svect outputs = Action::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Action_svect vect = Action::selectAll(sqldb );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Action::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ActionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void ActionTest::selectByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::selectByID(IOConn& ioc, xmlNodePtr node)");

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
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Action_svect outputs = Action::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Action_svect vect = Action::selectByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Action::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ActionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void ActionTest::selectByPath(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::selectByPath(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectByPath test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectByPath test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Action_svect outputs = Action::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Action_svect vect = Action::selectByPath(sqldb, inputDO.Path );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Action::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ActionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void ActionTest::selectActionsForUser(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::selectActionsForUser(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectActionsForUser test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectActionsForUser test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Action_svect outputs = Action::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Action_svect vect = Action::selectActionsForUser(sqldb, inputDO.userid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Action::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ActionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void ActionTest::selectActionsForUserByGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::selectActionsForUserByGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectActionsForUserByGroup test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectActionsForUserByGroup test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Action_svect outputs = Action::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Action_svect vect = Action::selectActionsForUserByGroup(sqldb, inputDO.userid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Action::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ActionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void ActionTest::checkActionForUser(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::checkActionForUser(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in checkActionForUser test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in checkActionForUser test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Action_svect outputs = Action::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Action_svect vect = Action::checkActionForUser(sqldb, inputDO.userid, inputDO.Path );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Action::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ActionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void ActionTest::checkActionForUserByGroup(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ActionTest::checkActionForUserByGroup(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in checkActionForUserByGroup test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in checkActionForUserByGroup test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	Action inputDO( XmlHelpers::FindChild( inputNode, Action::Name()() ) );

	// Pick up our list of output objects to be used for verification
	Action_svect outputs = Action::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	Action_svect vect = Action::checkActionForUserByGroup(sqldb, inputDO.userid, inputDO.Path );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		Action::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ActionTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

