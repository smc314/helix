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

#include "ProjectTable_test.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/dev/ProjectTable.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< ProjectTableTest > ProjectTableTest::reg( "ProjectTableTest", "/logic/dev/ProjectTableTest" );

ProjectTableTest::ProjectTableTest()
{
	EnEx ee(FL, "ProjectTableTest::ProjectTableTest()");

}

ProjectTableTest::~ProjectTableTest()
{
	EnEx ee(FL, "ProjectTableTest::~ProjectTableTest()");

}

void ProjectTableTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectTableTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectTableTest::runTests is NULL.");
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
		} else if( testMethod == "selectAllForProject" ){
			selectAllForProject( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to ProjectTableTest", testMethod() );
		}
	}
}

bool ProjectTableTest::compareObjects( ProjectTable* first, ProjectTable* second)
{
	EnEx ee(FL, "ProjectTableTest::compare( ProjectTable* first, ProjectTable* second)" );

	if(first->DataName != second->DataName) return false;
	if(first->Description != second->Description) return false;
	if(first->TableName != second->TableName) return false;
	if(first->guid != second->guid) return false;
	if(first->projdataguid != second->projdataguid) return false;
	if(first->projguid != second->projguid) return false;


	return true; // everything matches

}

bool ProjectTableTest::compareLists( vector< ProjectTable* >* first, vector< ProjectTable* >* second)
{
	EnEx ee(FL, "ProjectTableTest::compareLists( vector< ProjectTable* >* first, vector< ProjectTable* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!ProjectTableTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void ProjectTableTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectTableTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ProjectTableTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	ProjectTable inputDO( XmlHelpers::FindChild( inputNode, ProjectTable::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	ProjectTable::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ProjectTableTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectTableTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ProjectTableTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	ProjectTable inputDO( XmlHelpers::FindChild( inputNode, ProjectTable::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	ProjectTable::update(sqldb, inputDO.TableName, inputDO.Description, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ProjectTableTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectTableTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ProjectTableTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	ProjectTable inputDO( XmlHelpers::FindChild( inputNode, ProjectTable::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	ProjectTable::deleteByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ProjectTableTest::selectAllForProject(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectTableTest::selectAllForProject(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectAllForProject test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectAllForProject test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	ProjectTable inputDO( XmlHelpers::FindChild( inputNode, ProjectTable::Name()() ) );

	// Pick up our list of output objects to be used for verification
	ProjectTable_svect outputs = ProjectTable::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	ProjectTable_svect vect = ProjectTable::selectAllForProject(sqldb, inputDO.projguid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		ProjectTable::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ProjectTableTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

