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

#include "SchedItem_test.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/util/SchedItem.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< SchedItemTest > SchedItemTest::reg( "SchedItemTest", "/logic/util/SchedItemTest" );

SchedItemTest::SchedItemTest()
{
	EnEx ee(FL, "SchedItemTest::SchedItemTest()");

}

SchedItemTest::~SchedItemTest()
{
	EnEx ee(FL, "SchedItemTest::~SchedItemTest()");

}

void SchedItemTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SchedItemTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SchedItemTest::runTests is NULL.");
	}

	vector< xmlNodePtr > tests = XmlHelpers::FindChildren( node, "Test" );
	for(size_t i = 0; i < tests.size(); i++){
		twine testMethod( tests[i], "method" );
		if( testMethod == "insert" ){
			insert( ioc, tests[i] );
		} else if( testMethod == "update" ){
			update( ioc, tests[i] );
		} else if( testMethod == "updateLastRun" ){
			updateLastRun( ioc, tests[i] );
		} else if( testMethod == "deleteByID" ){
			deleteByID( ioc, tests[i] );
		} else if( testMethod == "selectAll" ){
			selectAll( ioc, tests[i] );
		} else if( testMethod == "selectByID" ){
			selectByID( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to SchedItemTest", testMethod() );
		}
	}
}

bool SchedItemTest::compareObjects( SchedItem* first, SchedItem* second)
{
	EnEx ee(FL, "SchedItemTest::compare( SchedItem* first, SchedItem* second)" );

	if(first->InputDocument != second->InputDocument) return false;
	if(first->LastRun != second->LastRun) return false;
	if(first->RunAtTime != second->RunAtTime) return false;
	if(first->TaskName != second->TaskName) return false;
	if(first->TaskUrl != second->TaskUrl) return false;
	if(first->dowFriday != second->dowFriday) return false;
	if(first->dowMonday != second->dowMonday) return false;
	if(first->dowSaturday != second->dowSaturday) return false;
	if(first->dowSunday != second->dowSunday) return false;
	if(first->dowThursday != second->dowThursday) return false;
	if(first->dowTuesday != second->dowTuesday) return false;
	if(first->dowWednesday != second->dowWednesday) return false;
	if(first->id != second->id) return false;
	if(first->isActive != second->isActive) return false;
	if(first->runEvery != second->runEvery) return false;
	if(first->useInterval != second->useInterval) return false;


	return true; // everything matches

}

bool SchedItemTest::compareLists( vector< SchedItem* >* first, vector< SchedItem* >* second)
{
	EnEx ee(FL, "SchedItemTest::compareLists( vector< SchedItem* >* first, vector< SchedItem* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!SchedItemTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void SchedItemTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SchedItemTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SchedItemTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SchedItem inputDO( XmlHelpers::FindChild( inputNode, SchedItem::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	SchedItem::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void SchedItemTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SchedItemTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SchedItemTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SchedItem inputDO( XmlHelpers::FindChild( inputNode, SchedItem::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	SchedItem::update(sqldb, inputDO.TaskName, inputDO.TaskUrl, inputDO.InputDocument, inputDO.isActive, inputDO.runEvery, inputDO.LastRun, inputDO.useInterval, inputDO.RunAtTime, inputDO.dowSunday, inputDO.dowMonday, inputDO.dowTuesday, inputDO.dowWednesday, inputDO.dowThursday, inputDO.dowFriday, inputDO.dowSaturday, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void SchedItemTest::updateLastRun(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SchedItemTest::updateLastRun(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SchedItemTest::updateLastRun test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SchedItem inputDO( XmlHelpers::FindChild( inputNode, SchedItem::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	SchedItem::updateLastRun(sqldb, inputDO.LastRun, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void SchedItemTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SchedItemTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in SchedItemTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	SchedItem inputDO( XmlHelpers::FindChild( inputNode, SchedItem::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	SchedItem::deleteByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void SchedItemTest::selectAll(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SchedItemTest::selectAll(IOConn& ioc, xmlNodePtr node)");

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
	SchedItem inputDO( XmlHelpers::FindChild( inputNode, SchedItem::Name()() ) );

	// Pick up our list of output objects to be used for verification
	SchedItem_svect outputs = SchedItem::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	SchedItem_svect vect = SchedItem::selectAll(sqldb );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		SchedItem::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = SchedItemTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void SchedItemTest::selectByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "SchedItemTest::selectByID(IOConn& ioc, xmlNodePtr node)");

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
	SchedItem inputDO( XmlHelpers::FindChild( inputNode, SchedItem::Name()() ) );

	// Pick up our list of output objects to be used for verification
	SchedItem_svect outputs = SchedItem::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	SchedItem_svect vect = SchedItem::selectByID(sqldb, inputDO.id );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		SchedItem::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = SchedItemTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

