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

#include "ProjectData_test.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object test class that is used for testing a      */
/* data object.  This class was generated based on the settings in the file:  */
/* ../logic/dev/ProjectData.sql.xml */
/* ************************************************************************** */

// This adds us to the global data object test class registry
DataObjectTestClassRegister< ProjectDataTest > ProjectDataTest::reg( "ProjectDataTest", "/logic/dev/ProjectDataTest" );

ProjectDataTest::ProjectDataTest()
{
	EnEx ee(FL, "ProjectDataTest::ProjectDataTest()");

}

ProjectDataTest::~ProjectDataTest()
{
	EnEx ee(FL, "ProjectDataTest::~ProjectDataTest()");

}

void ProjectDataTest::runTests(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectDataTest::runTests(IOConn& ioc, xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectDataTest::runTests is NULL.");
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
		} else if( testMethod == "selectAllForProj" ){
			selectAllForProj( ioc, tests[i] );
		} else if( testMethod == "selectByID" ){
			selectByID( ioc, tests[i] );

		} else {
			WARN(FL, "Unknown test method (%s) given to ProjectDataTest", testMethod() );
		}
	}
}

bool ProjectDataTest::compareObjects( ProjectData* first, ProjectData* second)
{
	EnEx ee(FL, "ProjectDataTest::compare( ProjectData* first, ProjectData* second)" );

	if(first->ConnectionString != second->ConnectionString) return false;
	if(first->DataName != second->DataName) return false;
	if(first->DataType != second->DataType) return false;
	if(first->Deployment != second->Deployment) return false;
	if(first->Description != second->Description) return false;
	if(first->DevTimePass != second->DevTimePass) return false;
	if(first->DevTimeUser != second->DevTimeUser) return false;
	if(first->Location != second->Location) return false;
	if(first->ProjName != second->ProjName) return false;
	if(first->ShortName != second->ShortName) return false;
	if(first->guid != second->guid) return false;
	if(first->projguid != second->projguid) return false;


	return true; // everything matches

}

bool ProjectDataTest::compareLists( vector< ProjectData* >* first, vector< ProjectData* >* second)
{
	EnEx ee(FL, "ProjectDataTest::compareLists( vector< ProjectData* >* first, vector< ProjectData* >* second)" );

	// If the sizes don't match, then return false
	if(first->size() != second->size()){
		return false;
	}

	// Loop through and check each pair of objects
	for(size_t i = 0; i < first->size(); i++){
		if(!ProjectDataTest::compareObjects( first->at( i ), second->at( i ) ) ){
			return false;
		}
	}

	// If they all match, return true
	return true;
}

void ProjectDataTest::insert(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectDataTest::insert(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ProjectDataTest::insert test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	ProjectData inputDO( XmlHelpers::FindChild( inputNode, ProjectData::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	ProjectData::insert(sqldb, inputDO );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ProjectDataTest::update(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectDataTest::update(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ProjectDataTest::update test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	ProjectData inputDO( XmlHelpers::FindChild( inputNode, ProjectData::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	ProjectData::update(sqldb, inputDO.DataName, inputDO.Description, inputDO.DataType, inputDO.ConnectionString, inputDO.DevTimeUser, inputDO.DevTimePass, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ProjectDataTest::deleteByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectDataTest::deleteByID(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in ProjectDataTest::deleteByID test.");
	}

	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object:
	ProjectData inputDO( XmlHelpers::FindChild( inputNode, ProjectData::Name()() ) );

	// Get a connection to our database
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");



	// Execute the statement
	ProjectData::deleteByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then there is nothing to save in our output node.
	} else {
		XmlHelpers::setBoolAttr( resultsNode, "success", true );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", 0 );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", 0 );
	}
}

void ProjectDataTest::selectAllForProj(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectDataTest::selectAllForProj(IOConn& ioc, xmlNodePtr node)");

	xmlNodePtr inputNode = XmlHelpers::FindChild( node, "Input" );
	xmlNodePtr outputNode = XmlHelpers::FindChild( node, "Output" );
	xmlNodePtr resultsNode = XmlHelpers::FindChild( node, "Results" );
	if(inputNode == NULL){
		throw AnException(0, FL, "No input node found in selectAllForProj test.");
	}
	if(outputNode == NULL){
		throw AnException(0, FL, "No output node found in selectAllForProj test.");
	}
	if(resultsNode == NULL){
		// Add it in:
		resultsNode = xmlNewChild( node, NULL, (const xmlChar*)"Results", NULL);
	}

	// Pick up our input data object
	ProjectData inputDO( XmlHelpers::FindChild( inputNode, ProjectData::Name()() ) );

	// Pick up our list of output objects to be used for verification
	ProjectData_svect outputs = ProjectData::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	ProjectData_svect vect = ProjectData::selectAllForProj(sqldb, inputDO.projguid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		ProjectData::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ProjectDataTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

void ProjectDataTest::selectByID(IOConn& ioc, xmlNodePtr node)
{
	EnEx ee(FL, "ProjectDataTest::selectByID(IOConn& ioc, xmlNodePtr node)");

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
	ProjectData inputDO( XmlHelpers::FindChild( inputNode, ProjectData::Name()() ) );

	// Pick up our list of output objects to be used for verification
	ProjectData_svect outputs = ProjectData::readXmlChildren( outputNode );

	// Get a connection to our database:
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB("hubconfig");

	// Execute the statement:
	ProjectData_svect vect = ProjectData::selectByID(sqldb, inputDO.guid );

	if(m_recordMode){
		// If we are recording, then save our results to the output node.
		ProjectData::createXmlChildren( outputNode, vect );
	} else {
		// If we are not recording, then compare the live results to any saved results
		bool matches = ProjectDataTest::compareLists( outputs, vect );
		XmlHelpers::setBoolAttr( resultsNode, "success", matches );
		XmlHelpers::setIntAttr( resultsNode, "savedResults", outputs->size() );
		XmlHelpers::setIntAttr( resultsNode, "liveResults", vect->size() );
	}

}

