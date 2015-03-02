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

#include "SQLWork.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/SQLWork.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine SQLWorkName = "SQLWork";

SQLWork::SQLWork()
{
	EnEx ee(FL, "SQLWork::SQLWork()");

	init();

}

SQLWork::SQLWork(const SQLWork& c)
{
	EnEx ee(FL, "SQLWork::SQLWork(const SQLWork& c)");

	AciInMap = c.AciInMap;
	AciOutMap = c.AciOutMap;
	AciService = c.AciService;
	BuildSql = c.BuildSql;
	Code = c.Code;
	ConvertSql = c.ConvertSql;
	Description = c.Description;
	FileName = c.FileName;
	HostDB = c.HostDB;
	Owner = c.Owner;
	Pfkey = c.Pfkey;
	Sql = c.Sql;
	Type = c.Type;


}

SQLWork& SQLWork::operator=(const SQLWork& c)
{
	EnEx ee(FL, "SQLWork::operator=(const SQLWork& c)");

	AciInMap = c.AciInMap;
	AciOutMap = c.AciOutMap;
	AciService = c.AciService;
	BuildSql = c.BuildSql;
	Code = c.Code;
	ConvertSql = c.ConvertSql;
	Description = c.Description;
	FileName = c.FileName;
	HostDB = c.HostDB;
	Owner = c.Owner;
	Pfkey = c.Pfkey;
	Sql = c.Sql;
	Type = c.Type;


	return *this;
}

SQLWork::~SQLWork()
{
	EnEx ee(FL, "SQLWork::~SQLWork()");

}

SQLWork& SQLWork::init()
{
	EnEx ee(FL, "SQLWork::init()");

	AciInMap.erase();
	AciOutMap.erase();
	AciService.erase();
	BuildSql.erase();
	Code.erase();
	ConvertSql.erase();
	Description.erase();
	FileName.erase();
	HostDB.erase();
	Owner.erase();
	Pfkey.erase();
	Sql.erase();
	Type.erase();


	return *this;
}

SQLWork& SQLWork::checkSize()
{
	EnEx ee(FL, "SQLWork::checkSize()");

	AciInMap.check_size();
	AciInMap.rtrim();
	AciOutMap.check_size();
	AciOutMap.rtrim();
	AciService.check_size();
	AciService.rtrim();
	BuildSql.check_size();
	BuildSql.rtrim();
	Code.check_size();
	Code.rtrim();
	ConvertSql.check_size();
	ConvertSql.rtrim();
	Description.check_size();
	Description.rtrim();
	FileName.check_size();
	FileName.rtrim();
	HostDB.check_size();
	HostDB.rtrim();
	Owner.check_size();
	Owner.rtrim();
	Pfkey.check_size();
	Pfkey.rtrim();
	Sql.check_size();
	Sql.rtrim();
	Type.check_size();
	Type.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
SQLWork::SQLWork(xmlNodePtr node)
{
	EnEx ee(FL, "SQLWork::SQLWork(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
SQLWork& SQLWork::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "SQLWork::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct SQLWork is NULL.");
	}

	AciInMap.getAttribute(node, "AciInMap");
	AciOutMap.getAttribute(node, "AciOutMap");
	AciService.getAttribute(node, "AciService");
	xmlNodePtr BuildSql_child = XmlHelpers::FindChild(node, "BuildSql"); if( BuildSql_child != NULL) BuildSql = XmlHelpers::getBase64(BuildSql_child);
	xmlNodePtr Code_child = XmlHelpers::FindChild(node, "Code"); if( Code_child != NULL) Code = XmlHelpers::getBase64(Code_child);
	xmlNodePtr ConvertSql_child = XmlHelpers::FindChild(node, "ConvertSql"); if( ConvertSql_child != NULL) ConvertSql = XmlHelpers::getBase64(ConvertSql_child);
	Description.getAttribute(node, "Description");
	FileName.getAttribute(node, "FileName");
	HostDB.getAttribute(node, "HostDB");
	Owner.getAttribute(node, "Owner");
	Pfkey.getAttribute(node, "Pfkey");
	xmlNodePtr Sql_child = XmlHelpers::FindChild(node, "Sql"); if( Sql_child != NULL) Sql = XmlHelpers::getBase64(Sql_child);
	Type.getAttribute(node, "Type");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr SQLWork::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "SQLWork::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLWork::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"SQLWork", NULL);
	xmlSetProp(child, (const xmlChar*)"AciInMap", AciInMap);
	xmlSetProp(child, (const xmlChar*)"AciOutMap", AciOutMap);
	xmlSetProp(child, (const xmlChar*)"AciService", AciService);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"BuildSql", NULL), BuildSql);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"Code", NULL), Code);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"ConvertSql", NULL), ConvertSql);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"FileName", FileName);
	xmlSetProp(child, (const xmlChar*)"HostDB", HostDB);
	xmlSetProp(child, (const xmlChar*)"Owner", Owner);
	xmlSetProp(child, (const xmlChar*)"Pfkey", Pfkey);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"Sql", NULL), Sql);
	xmlSetProp(child, (const xmlChar*)"Type", Type);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr SQLWork::createXmlDoc() const
{
	EnEx ee(FL, "SQLWork::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"SQLWork", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"AciInMap", AciInMap);
	xmlSetProp(child, (const xmlChar*)"AciOutMap", AciOutMap);
	xmlSetProp(child, (const xmlChar*)"AciService", AciService);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"BuildSql", NULL), BuildSql);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"Code", NULL), Code);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"ConvertSql", NULL), ConvertSql);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"FileName", FileName);
	xmlSetProp(child, (const xmlChar*)"HostDB", HostDB);
	xmlSetProp(child, (const xmlChar*)"Owner", Owner);
	xmlSetProp(child, (const xmlChar*)"Pfkey", Pfkey);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"Sql", NULL), Sql);
	xmlSetProp(child, (const xmlChar*)"Type", Type);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<SQLWork* >* SQLWork::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "SQLWork::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLWork::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<SQLWork* >, SQLWork::deleteVector> ret = new vector<SQLWork* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "SQLWork") == 0){
			ret->push_back( new SQLWork(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void SQLWork::createXmlChildren(xmlNodePtr parent, vector<SQLWork* >* vect)
{
	EnEx ee(FL, "SQLWork::createXmlChildren(xmlNodePtr parent, vector<SQLWork* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLWork::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr SQLWork::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SQLWork* >* vect)
{
	EnEx ee(FL, "SQLWork::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SQLWork* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SQLWork::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	SQLWork::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void SQLWork::deleteVector(vector<SQLWork* >* vect)
{
	EnEx ee(FL, "SQLWork::deleteVector(vector<SQLWork* >* vect)");

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
twine& SQLWork::Name()
{
	return SQLWorkName;
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
void SQLWork::unused(OdbcObj& odbc, SQLWork& obj )
{
	EnEx ee(FL, "SQLWork::unused()");

	twine stmt = "-- Empty on purpose";

	SQLWork::unused(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SQLWork::unused(OdbcObj& odbc, twine& stmt, bool useInputs, SQLWork& obj )
{
	EnEx ee(FL, "SQLWork::unused()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into SQLWork::unused is not connected.");
	}

	int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
	int sizeof_float = sizeof(float);      // so that we can have an address of this variable

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("SQLWork::unused()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.FileName() );
			odbc.BindInput(1, obj.FileName);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.Description() );
			odbc.BindInput(2, obj.Description);
			DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.HostDB() );
			odbc.BindInput(3, obj.HostDB);
			DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.Sql() );
			odbc.BindInput(4, obj.Sql);
			DEBUG(FL, "Setting input (%d) to value: %s", 5, obj.Type() );
			odbc.BindInput(5, obj.Type);
			DEBUG(FL, "Setting input (%d) to value: %s", 6, obj.AciService() );
			odbc.BindInput(6, obj.AciService);
			DEBUG(FL, "Setting input (%d) to value: %s", 7, obj.AciInMap() );
			odbc.BindInput(7, obj.AciInMap);
			DEBUG(FL, "Setting input (%d) to value: %s", 8, obj.AciOutMap() );
			odbc.BindInput(8, obj.AciOutMap);
			DEBUG(FL, "Setting input (%d) to value: %s", 9, obj.BuildSql() );
			odbc.BindInput(9, obj.BuildSql);
			DEBUG(FL, "Setting input (%d) to value: %s", 10, obj.ConvertSql() );
			odbc.BindInput(10, obj.ConvertSql);
			DEBUG(FL, "Setting input (%d) to value: %s", 11, obj.Code() );
			odbc.BindInput(11, obj.Code);
			DEBUG(FL, "Setting input (%d) to value: %s", 12, obj.Owner() );
			odbc.BindInput(12, obj.Owner);
			DEBUG(FL, "Setting input (%d) to value: %s", 13, obj.Pfkey() );
			odbc.BindInput(13, obj.Pfkey);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for SQLWork::unused");
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
twine SQLWork::unused_prepSQL(IOConn& ioc, SQLWork& obj )
{
	EnEx ee(FL, "SQLWork::unused_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Empty on purpose";

	// Replace the FileName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.FileName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Description );
	}

	// Replace the HostDB parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.HostDB );
	}

	// Replace the Sql parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Sql );
	}

	// Replace the Type parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Type );
	}

	// Replace the AciService parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.AciService );
	}

	// Replace the AciInMap parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.AciInMap );
	}

	// Replace the AciOutMap parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.AciOutMap );
	}

	// Replace the BuildSql parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.BuildSql );
	}

	// Replace the ConvertSql parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ConvertSql );
	}

	// Replace the Code parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Code );
	}

	// Replace the Owner parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Owner );
	}

	// Replace the Pfkey parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Pfkey );
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

