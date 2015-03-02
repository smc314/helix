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

#include "SQLStatement.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/util/SQLStatement.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine SQLStatementName = "SQLStatement";

SQLStatement::SQLStatement()
{
	EnEx ee(FL, "SQLStatement::SQLStatement()");

	init();

}

SQLStatement::SQLStatement(const SQLStatement& c)
{
	EnEx ee(FL, "SQLStatement::SQLStatement(const SQLStatement& c)");

	HostDB = c.HostDB;
	Sql = c.Sql;


}

SQLStatement& SQLStatement::operator=(const SQLStatement& c)
{
	EnEx ee(FL, "SQLStatement::operator=(const SQLStatement& c)");

	HostDB = c.HostDB;
	Sql = c.Sql;


	return *this;
}

SQLStatement::~SQLStatement()
{
	EnEx ee(FL, "SQLStatement::~SQLStatement()");

}

SQLStatement& SQLStatement::init()
{
	EnEx ee(FL, "SQLStatement::init()");

	HostDB.erase();
	Sql.erase();


	return *this;
}

SQLStatement& SQLStatement::checkSize()
{
	EnEx ee(FL, "SQLStatement::checkSize()");

	HostDB.check_size();
	HostDB.rtrim();
	Sql.check_size();
	Sql.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
SQLStatement::SQLStatement(xmlNodePtr node)
{
	EnEx ee(FL, "SQLStatement::SQLStatement(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
SQLStatement& SQLStatement::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "SQLStatement::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct SQLStatement is NULL.");
	}

	HostDB.getAttribute(node, "HostDB");
	Sql.getAttribute(node, "Sql");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr SQLStatement::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "SQLStatement::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStatement::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"SQLStatement", NULL);
	xmlSetProp(child, (const xmlChar*)"HostDB", HostDB);
	xmlSetProp(child, (const xmlChar*)"Sql", Sql);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr SQLStatement::createXmlDoc() const
{
	EnEx ee(FL, "SQLStatement::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"SQLStatement", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"HostDB", HostDB);
	xmlSetProp(child, (const xmlChar*)"Sql", Sql);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<SQLStatement* >* SQLStatement::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "SQLStatement::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStatement::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<SQLStatement* >, SQLStatement::deleteVector> ret = new vector<SQLStatement* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "SQLStatement") == 0){
			ret->push_back( new SQLStatement(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void SQLStatement::createXmlChildren(xmlNodePtr parent, vector<SQLStatement* >* vect)
{
	EnEx ee(FL, "SQLStatement::createXmlChildren(xmlNodePtr parent, vector<SQLStatement* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStatement::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr SQLStatement::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SQLStatement* >* vect)
{
	EnEx ee(FL, "SQLStatement::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SQLStatement* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLStatement::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	SQLStatement::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void SQLStatement::deleteVector(vector<SQLStatement* >* vect)
{
	EnEx ee(FL, "SQLStatement::deleteVector(vector<SQLStatement* >* vect)");

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
twine& SQLStatement::Name()
{
	return SQLStatementName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This statement is merely here to define the data structure that is
			passed back and forth to determine log on credentials.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Nothing here
		 */
/*                                                                                        */
/* ************************************************************************************** */
void SQLStatement::unusedSqlStmt(OdbcObj& odbc, SQLStatement& obj )
{
	EnEx ee(FL, "SQLStatement::unusedSqlStmt()");

	twine stmt = "-- Nothing here";

	SQLStatement::unusedSqlStmt(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SQLStatement::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, SQLStatement& obj )
{
	EnEx ee(FL, "SQLStatement::unusedSqlStmt()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into SQLStatement::unusedSqlStmt is not connected.");
	}

	int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
	int sizeof_float = sizeof(float);      // so that we can have an address of this variable

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("SQLStatement::unusedSqlStmt()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.Sql() );
			odbc.BindInput(1, obj.Sql);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.HostDB() );
			odbc.BindInput(2, obj.HostDB);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for SQLStatement::unusedSqlStmt");
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
twine SQLStatement::unusedSqlStmt_prepSQL(IOConn& ioc, SQLStatement& obj )
{
	EnEx ee(FL, "SQLStatement::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here";

	// Replace the Sql parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Sql );
	}

	// Replace the HostDB parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.HostDB );
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

