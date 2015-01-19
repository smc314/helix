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

#include "SQLTests.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/SQLTests.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine SQLTestsName = "SQLTests";

SQLTests::SQLTests()
{
	EnEx ee(FL, "SQLTests::SQLTests()");

	init();

}

SQLTests::SQLTests(const SQLTests& c)
{
	EnEx ee(FL, "SQLTests::SQLTests(const SQLTests& c)");

	TestGroupName = c.TestGroupName;
	host = c.host;
	pass = c.pass;
	port = c.port;
	user = c.user;
	SQLStatements = new vector<SQLStmt*>();
	for(size_t i = 0; i < c.SQLStatements->size(); i++){
		SQLStatements->push_back( new SQLStmt( *(c.SQLStatements->at( i )) ) );
	}


}

SQLTests& SQLTests::operator=(const SQLTests& c)
{
	EnEx ee(FL, "SQLTests::operator=(const SQLTests& c)");

	TestGroupName = c.TestGroupName;
	host = c.host;
	pass = c.pass;
	port = c.port;
	user = c.user;
	SQLStatements = new vector<SQLStmt*>();
	for(size_t i = 0; i < c.SQLStatements->size(); i++){
		SQLStatements->push_back( new SQLStmt( *(c.SQLStatements->at( i )) ) );
	}


	return *this;
}

SQLTests::~SQLTests()
{
	EnEx ee(FL, "SQLTests::~SQLTests()");

}

SQLTests& SQLTests::init()
{
	EnEx ee(FL, "SQLTests::init()");

	TestGroupName.erase();
	host.erase();
	pass.erase();
	port.erase();
	user.erase();
	SQLStatements = new vector<SQLStmt*>();


	return *this;
}

SQLTests& SQLTests::checkSize()
{
	EnEx ee(FL, "SQLTests::checkSize()");

	TestGroupName.check_size();
	TestGroupName.rtrim();
	host.check_size();
	host.rtrim();
	pass.check_size();
	pass.rtrim();
	port.check_size();
	port.rtrim();
	user.check_size();
	user.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
SQLTests::SQLTests(xmlNodePtr node)
{
	EnEx ee(FL, "SQLTests::SQLTests(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
SQLTests& SQLTests::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "SQLTests::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct SQLTests is NULL.");
	}

	TestGroupName.getAttribute(node, "TestGroupName");
	host.getAttribute(node, "host");
	pass.getAttribute(node, "pass");
	port.getAttribute(node, "port");
	user.getAttribute(node, "user");
	SQLStatements = SQLStmt::readXmlChildren( XmlHelpers::FindChild( node, "SQLStatements") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr SQLTests::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "SQLTests::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLTests::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"SQLTests", NULL);
	xmlSetProp(child, (const xmlChar*)"TestGroupName", TestGroupName);
	xmlSetProp(child, (const xmlChar*)"host", host);
	xmlSetProp(child, (const xmlChar*)"pass", pass);
	xmlSetProp(child, (const xmlChar*)"port", port);
	xmlSetProp(child, (const xmlChar*)"user", user);
	xmlNodePtr SQLStatements_node = xmlNewChild(child, NULL, (const xmlChar*)"SQLStatements", NULL);
	SQLStmt::createXmlChildren( SQLStatements_node, SQLStatements );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr SQLTests::createXmlDoc() const
{
	EnEx ee(FL, "SQLTests::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"SQLTests", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"TestGroupName", TestGroupName);
	xmlSetProp(child, (const xmlChar*)"host", host);
	xmlSetProp(child, (const xmlChar*)"pass", pass);
	xmlSetProp(child, (const xmlChar*)"port", port);
	xmlSetProp(child, (const xmlChar*)"user", user);
	xmlNodePtr SQLStatements_node = xmlNewChild(child, NULL, (const xmlChar*)"SQLStatements", NULL);
	SQLStmt::createXmlChildren( SQLStatements_node, SQLStatements );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<SQLTests* >* SQLTests::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "SQLTests::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLTests::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<SQLTests* >, SQLTests::deleteVector> ret = new vector<SQLTests* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "SQLTests") == 0){
			ret->push_back( new SQLTests(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void SQLTests::createXmlChildren(xmlNodePtr parent, vector<SQLTests* >* vect)
{
	EnEx ee(FL, "SQLTests::createXmlChildren(xmlNodePtr parent, vector<SQLTests* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLTests::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void SQLTests::deleteVector(vector<SQLTests* >* vect)
{
	EnEx ee(FL, "SQLTests::deleteVector(vector<SQLTests* >* vect)");

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
twine& SQLTests::Name()
{
	return SQLTestsName;
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
void SQLTests::unused(OdbcObj& odbc, SQLTests& obj )
{
	EnEx ee(FL, "SQLTests::unused()");

	twine stmt = "-- Empty on purpose";

	SQLTests::unused(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SQLTests::unused(OdbcObj& odbc, twine& stmt, bool useInputs, SQLTests& obj )
{
	EnEx ee(FL, "SQLTests::unused()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into SQLTests::unused is not connected.");
	}

	int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
	int sizeof_float = sizeof(float);      // so that we can have an address of this variable

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("SQLTests::unused()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.TestGroupName() );
			odbc.BindInput(1, obj.TestGroupName);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.user() );
			odbc.BindInput(2, obj.user);
			DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.pass() );
			odbc.BindInput(3, obj.pass);
			DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.host() );
			odbc.BindInput(4, obj.host);
			DEBUG(FL, "Setting input (%d) to value: %s", 5, obj.port() );
			odbc.BindInput(5, obj.port);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for SQLTests::unused");
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
twine SQLTests::unused_prepSQL(IOConn& ioc, SQLTests& obj )
{
	EnEx ee(FL, "SQLTests::unused_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Empty on purpose";

	// Replace the TestGroupName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TestGroupName );
	}

	// Replace the user parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.user );
	}

	// Replace the pass parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.pass );
	}

	// Replace the host parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.host );
	}

	// Replace the port parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.port );
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

