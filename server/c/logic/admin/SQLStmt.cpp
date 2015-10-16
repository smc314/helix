/* **************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include <AnException.h>
#include <EnEx.h>
#include <Log.h>
#include <XmlHelpers.h>
using namespace SLib;

#include "SQLStmt.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/SQLStmt.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine SQLStmtName = "SQLStmt";

SQLStmt::SQLStmt()
{
	EnEx ee(FL, "SQLStmt::SQLStmt()");

	init();

}

SQLStmt::SQLStmt(const SQLStmt& c)
{
	EnEx ee(FL, "SQLStmt::SQLStmt(const SQLStmt& c)");

	Description = c.Description;
	Duration = c.Duration;
	StatementName = c.StatementName;
	expectErrors = c.expectErrors;
	expectedErrorMsg = c.expectedErrorMsg;
	expectedRows = c.expectedRows;
	ignoreErrors = c.ignoreErrors;
	isSelected = c.isSelected;
	issueCommit = c.issueCommit;
	issueRollback = c.issueRollback;
	newConnection = c.newConnection;
	status = c.status;
	statusMessage = c.statusMessage;
	stmt = c.stmt;
	verifyData = c.verifyData;
	MetaData = new vector<Col*>();
	for(size_t i = 0; i < c.MetaData->size(); i++){
		MetaData->push_back( new Col( *(c.MetaData->at( i )) ) );
	}
	MetaDataCheck = new vector<Col*>();
	for(size_t i = 0; i < c.MetaDataCheck->size(); i++){
		MetaDataCheck->push_back( new Col( *(c.MetaDataCheck->at( i )) ) );
	}
	Results = new vector<Row*>();
	for(size_t i = 0; i < c.Results->size(); i++){
		Results->push_back( new Row( *(c.Results->at( i )) ) );
	}
	ResultsCheck = new vector<Row*>();
	for(size_t i = 0; i < c.ResultsCheck->size(); i++){
		ResultsCheck->push_back( new Row( *(c.ResultsCheck->at( i )) ) );
	}


}

SQLStmt& SQLStmt::operator=(const SQLStmt& c)
{
	EnEx ee(FL, "SQLStmt::operator=(const SQLStmt& c)");

	Description = c.Description;
	Duration = c.Duration;
	StatementName = c.StatementName;
	expectErrors = c.expectErrors;
	expectedErrorMsg = c.expectedErrorMsg;
	expectedRows = c.expectedRows;
	ignoreErrors = c.ignoreErrors;
	isSelected = c.isSelected;
	issueCommit = c.issueCommit;
	issueRollback = c.issueRollback;
	newConnection = c.newConnection;
	status = c.status;
	statusMessage = c.statusMessage;
	stmt = c.stmt;
	verifyData = c.verifyData;
	MetaData = new vector<Col*>();
	for(size_t i = 0; i < c.MetaData->size(); i++){
		MetaData->push_back( new Col( *(c.MetaData->at( i )) ) );
	}
	MetaDataCheck = new vector<Col*>();
	for(size_t i = 0; i < c.MetaDataCheck->size(); i++){
		MetaDataCheck->push_back( new Col( *(c.MetaDataCheck->at( i )) ) );
	}
	Results = new vector<Row*>();
	for(size_t i = 0; i < c.Results->size(); i++){
		Results->push_back( new Row( *(c.Results->at( i )) ) );
	}
	ResultsCheck = new vector<Row*>();
	for(size_t i = 0; i < c.ResultsCheck->size(); i++){
		ResultsCheck->push_back( new Row( *(c.ResultsCheck->at( i )) ) );
	}


	return *this;
}

SQLStmt::~SQLStmt()
{
	EnEx ee(FL, "SQLStmt::~SQLStmt()");

}

SQLStmt& SQLStmt::init()
{
	EnEx ee(FL, "SQLStmt::init()");

	Description.erase();
	Duration = 0.0f;
	StatementName.erase();
	expectErrors = 0;
	expectedErrorMsg.erase();
	expectedRows = 0;
	ignoreErrors = 0;
	isSelected = 0;
	issueCommit = 0;
	issueRollback = 0;
	newConnection = 0;
	status = 0;
	statusMessage.erase();
	stmt.erase();
	verifyData = 0;
	MetaData = new vector<Col*>();
	MetaDataCheck = new vector<Col*>();
	Results = new vector<Row*>();
	ResultsCheck = new vector<Row*>();


	return *this;
}

SQLStmt& SQLStmt::checkSize()
{
	EnEx ee(FL, "SQLStmt::checkSize()");

	Description.check_size();
	Description.rtrim();
	StatementName.check_size();
	StatementName.rtrim();
	expectedErrorMsg.check_size();
	expectedErrorMsg.rtrim();
	statusMessage.check_size();
	statusMessage.rtrim();
	stmt.check_size();
	stmt.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
SQLStmt::SQLStmt(xmlNodePtr node)
{
	EnEx ee(FL, "SQLStmt::SQLStmt(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
SQLStmt& SQLStmt::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "SQLStmt::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct SQLStmt is NULL.");
	}

	Description.getAttribute(node, "Description");
	Duration = (float)XmlHelpers::getFloatAttr(node, "Duration");
	StatementName.getAttribute(node, "StatementName");
	expectErrors = XmlHelpers::getIntAttr(node, "expectErrors");
	expectedErrorMsg.getAttribute(node, "expectedErrorMsg");
	expectedRows = XmlHelpers::getIntAttr(node, "expectedRows");
	ignoreErrors = XmlHelpers::getIntAttr(node, "ignoreErrors");
	isSelected = XmlHelpers::getIntAttr(node, "isSelected");
	issueCommit = XmlHelpers::getIntAttr(node, "issueCommit");
	issueRollback = XmlHelpers::getIntAttr(node, "issueRollback");
	newConnection = XmlHelpers::getIntAttr(node, "newConnection");
	status = XmlHelpers::getIntAttr(node, "status");
	statusMessage.getAttribute(node, "statusMessage");
	xmlNodePtr stmt_child = XmlHelpers::FindChild(node, "stmt"); if( stmt_child != NULL) stmt = XmlHelpers::getBase64(stmt_child);
	verifyData = XmlHelpers::getIntAttr(node, "verifyData");
	MetaData = Col::readXmlChildren( XmlHelpers::FindChild( node, "MetaData") );
	MetaDataCheck = Col::readXmlChildren( XmlHelpers::FindChild( node, "MetaDataCheck") );
	Results = Row::readXmlChildren( XmlHelpers::FindChild( node, "Results") );
	ResultsCheck = Row::readXmlChildren( XmlHelpers::FindChild( node, "ResultsCheck") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr SQLStmt::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "SQLStmt::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStmt::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"SQLStmt", NULL);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	XmlHelpers::setFloatAttr(child, "Duration", Duration);
	xmlSetProp(child, (const xmlChar*)"StatementName", StatementName);
	XmlHelpers::setIntAttr(child, "expectErrors", expectErrors);
	xmlSetProp(child, (const xmlChar*)"expectedErrorMsg", expectedErrorMsg);
	XmlHelpers::setIntAttr(child, "expectedRows", expectedRows);
	XmlHelpers::setIntAttr(child, "ignoreErrors", ignoreErrors);
	XmlHelpers::setIntAttr(child, "isSelected", isSelected);
	XmlHelpers::setIntAttr(child, "issueCommit", issueCommit);
	XmlHelpers::setIntAttr(child, "issueRollback", issueRollback);
	XmlHelpers::setIntAttr(child, "newConnection", newConnection);
	XmlHelpers::setIntAttr(child, "status", status);
	xmlSetProp(child, (const xmlChar*)"statusMessage", statusMessage);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"stmt", NULL), stmt);
	XmlHelpers::setIntAttr(child, "verifyData", verifyData);
	xmlNodePtr MetaData_node = xmlNewChild(child, NULL, (const xmlChar*)"MetaData", NULL);
	Col::createXmlChildren( MetaData_node, MetaData );

	xmlNodePtr MetaDataCheck_node = xmlNewChild(child, NULL, (const xmlChar*)"MetaDataCheck", NULL);
	Col::createXmlChildren( MetaDataCheck_node, MetaDataCheck );

	xmlNodePtr Results_node = xmlNewChild(child, NULL, (const xmlChar*)"Results", NULL);
	Row::createXmlChildren( Results_node, Results );

	xmlNodePtr ResultsCheck_node = xmlNewChild(child, NULL, (const xmlChar*)"ResultsCheck", NULL);
	Row::createXmlChildren( ResultsCheck_node, ResultsCheck );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr SQLStmt::createXmlDoc() const
{
	EnEx ee(FL, "SQLStmt::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"SQLStmt", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	XmlHelpers::setFloatAttr(child, "Duration", Duration);
	xmlSetProp(child, (const xmlChar*)"StatementName", StatementName);
	XmlHelpers::setIntAttr(child, "expectErrors", expectErrors);
	xmlSetProp(child, (const xmlChar*)"expectedErrorMsg", expectedErrorMsg);
	XmlHelpers::setIntAttr(child, "expectedRows", expectedRows);
	XmlHelpers::setIntAttr(child, "ignoreErrors", ignoreErrors);
	XmlHelpers::setIntAttr(child, "isSelected", isSelected);
	XmlHelpers::setIntAttr(child, "issueCommit", issueCommit);
	XmlHelpers::setIntAttr(child, "issueRollback", issueRollback);
	XmlHelpers::setIntAttr(child, "newConnection", newConnection);
	XmlHelpers::setIntAttr(child, "status", status);
	xmlSetProp(child, (const xmlChar*)"statusMessage", statusMessage);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"stmt", NULL), stmt);
	XmlHelpers::setIntAttr(child, "verifyData", verifyData);
	xmlNodePtr MetaData_node = xmlNewChild(child, NULL, (const xmlChar*)"MetaData", NULL);
	Col::createXmlChildren( MetaData_node, MetaData );

	xmlNodePtr MetaDataCheck_node = xmlNewChild(child, NULL, (const xmlChar*)"MetaDataCheck", NULL);
	Col::createXmlChildren( MetaDataCheck_node, MetaDataCheck );

	xmlNodePtr Results_node = xmlNewChild(child, NULL, (const xmlChar*)"Results", NULL);
	Row::createXmlChildren( Results_node, Results );

	xmlNodePtr ResultsCheck_node = xmlNewChild(child, NULL, (const xmlChar*)"ResultsCheck", NULL);
	Row::createXmlChildren( ResultsCheck_node, ResultsCheck );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<SQLStmt* >* SQLStmt::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "SQLStmt::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStmt::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<SQLStmt* >, SQLStmt::deleteVector> ret = new vector<SQLStmt* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "SQLStmt") == 0){
			ret->push_back( new SQLStmt(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void SQLStmt::createXmlChildren(xmlNodePtr parent, vector<SQLStmt* >* vect)
{
	EnEx ee(FL, "SQLStmt::createXmlChildren(xmlNodePtr parent, vector<SQLStmt* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStmt::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr SQLStmt::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SQLStmt* >* vect)
{
	EnEx ee(FL, "SQLStmt::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SQLStmt* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStmt::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	SQLStmt::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void SQLStmt::deleteVector(vector<SQLStmt* >* vect)
{
	EnEx ee(FL, "SQLStmt::deleteVector(vector<SQLStmt* >* vect)");

	if(vect == NULL){
		return; // quick bail-out
	}

	for(size_t i = 0; i < vect->size(); i++){
		if( (*vect)[i] != NULL ){
			delete (*vect)[i];
		}
	}

	delete vect;

}

/* ********************************************************************** */
/* Return the name of our object.                                         */
/* ********************************************************************** */
twine& SQLStmt::Name()
{
	return SQLStmtName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is here to allow us to define the SQLTests data object.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Empty on purpose
		 */
/*                                                                                        */
/* ************************************************************************************** */
void SQLStmt::unused(OdbcObj& odbc, SQLStmt& obj )
{
	EnEx ee(FL, "SQLStmt::unused()");

	twine stmt = "-- Empty on purpose";

	SQLStmt::unused(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SQLStmt::unused(OdbcObj& odbc, twine& stmt, bool useInputs, SQLStmt& obj )
{
	EnEx ee(FL, "SQLStmt::unused()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into SQLStmt::unused is not connected.");
	}

	int sizeof_int = sizeof(intptr_t); // so that we can have an address of this variable
	int sizeof_float = sizeof(float);  // so that we can have an address of this variable

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("SQLStmt::unused()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.StatementName() );
			odbc.BindInput(1, obj.StatementName);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.Description() );
			odbc.BindInput(2, obj.Description);
			DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.stmt() );
			odbc.BindInput(3, obj.stmt);
			DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.newConnection );
			odbc.BindInput(4, &(obj.newConnection), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.ignoreErrors );
			odbc.BindInput(5, &(obj.ignoreErrors), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 6, obj.expectErrors );
			odbc.BindInput(6, &(obj.expectErrors), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 7, obj.expectedErrorMsg() );
			odbc.BindInput(7, obj.expectedErrorMsg);
			DEBUG(FL, "Setting input (%d) to value: %d", 8, obj.verifyData );
			odbc.BindInput(8, &(obj.verifyData), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 9, obj.expectedRows );
			odbc.BindInput(9, &(obj.expectedRows), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 10, obj.issueCommit );
			odbc.BindInput(10, &(obj.issueCommit), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 11, obj.issueRollback );
			odbc.BindInput(11, &(obj.issueRollback), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 12, obj.isSelected );
			odbc.BindInput(12, &(obj.isSelected), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 13, obj.status );
			odbc.BindInput(13, &(obj.status), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 14, obj.statusMessage() );
			odbc.BindInput(14, obj.statusMessage);
			DEBUG(FL, "Setting input (%d) to value: %f", 15, obj.Duration );
			odbc.BindInput(15, &(obj.Duration), &sizeof_float, DB_FLOAT);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for SQLStmt::unused");
		odbc.ExecStmt();
	}

	// That's it.
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine SQLStmt::unused_prepSQL(IOConn& ioc, SQLStmt& obj )
{
	EnEx ee(FL, "SQLStmt::unused_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Empty on purpose";

	// Replace the StatementName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.StatementName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Description );
	}

	// Replace the stmt parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.stmt );
	}

	// Replace the newConnection parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.newConnection;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ignoreErrors parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ignoreErrors;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the expectErrors parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.expectErrors;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the expectedErrorMsg parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.expectedErrorMsg );
	}

	// Replace the verifyData parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.verifyData;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the expectedRows parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.expectedRows;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the issueCommit parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.issueCommit;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the issueRollback parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.issueRollback;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the isSelected parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.isSelected;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the status parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.status;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the statusMessage parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.statusMessage );
	}

	// Replace the Duration parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Duration;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

