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

#include "Col.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/Col.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ColName = "Col";

Col::Col()
{
	EnEx ee(FL, "Col::Col()");

	init();

}

Col::Col(const Col& c)
{
	EnEx ee(FL, "Col::Col(const Col& c)");

	colName = c.colName;
	dataValue = c.dataValue;
	idx = c.idx;
	typeName = c.typeName;
	verifyData = c.verifyData;


}

Col& Col::operator=(const Col& c)
{
	EnEx ee(FL, "Col::operator=(const Col& c)");

	colName = c.colName;
	dataValue = c.dataValue;
	idx = c.idx;
	typeName = c.typeName;
	verifyData = c.verifyData;


	return *this;
}

Col::~Col()
{
	EnEx ee(FL, "Col::~Col()");

}

Col& Col::init()
{
	EnEx ee(FL, "Col::init()");

	colName.erase();
	dataValue.erase();
	idx = 0;
	typeName.erase();
	verifyData = 0;


	return *this;
}

Col& Col::checkSize()
{
	EnEx ee(FL, "Col::checkSize()");

	colName.check_size();
	colName.rtrim();
	dataValue.check_size();
	dataValue.rtrim();
	typeName.check_size();
	typeName.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Col::Col(xmlNodePtr node)
{
	EnEx ee(FL, "Col::Col(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Col& Col::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Col::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Col is NULL.");
	}

	colName.getAttribute(node, "colName");
	dataValue.getAttribute(node, "dataValue");
	idx = XmlHelpers::getIntAttr(node, "idx");
	typeName.getAttribute(node, "typeName");
	verifyData = XmlHelpers::getIntAttr(node, "verifyData");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Col::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Col::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Col::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Col", NULL);
	xmlSetProp(child, (const xmlChar*)"colName", colName);
	xmlSetProp(child, (const xmlChar*)"dataValue", dataValue);
	XmlHelpers::setIntAttr(child, "idx", idx);
	xmlSetProp(child, (const xmlChar*)"typeName", typeName);
	XmlHelpers::setIntAttr(child, "verifyData", verifyData);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Col::createXmlDoc() const
{
	EnEx ee(FL, "Col::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Col", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"colName", colName);
	xmlSetProp(child, (const xmlChar*)"dataValue", dataValue);
	XmlHelpers::setIntAttr(child, "idx", idx);
	xmlSetProp(child, (const xmlChar*)"typeName", typeName);
	XmlHelpers::setIntAttr(child, "verifyData", verifyData);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Col* >* Col::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Col::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Col::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Col* >, Col::deleteVector> ret = new vector<Col* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Col") == 0){
			ret->push_back( new Col(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Col::createXmlChildren(xmlNodePtr parent, vector<Col* >* vect)
{
	EnEx ee(FL, "Col::createXmlChildren(xmlNodePtr parent, vector<Col* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Col::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Col::deleteVector(vector<Col* >* vect)
{
	EnEx ee(FL, "Col::deleteVector(vector<Col* >* vect)");

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
twine& Col::Name()
{
	return ColName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is here to allow us to define the data object.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Empty on purpose
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Col::unused(OdbcObj& odbc, Col& obj )
{
	EnEx ee(FL, "Col::unused()");

	twine stmt = "-- Empty on purpose";

	Col::unused(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Col::unused(OdbcObj& odbc, twine& stmt, bool useInputs, Col& obj )
{
	EnEx ee(FL, "Col::unused()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into Col::unused is not connected.");
	}

	int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
	int sizeof_float = sizeof(float);      // so that we can have an address of this variable

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("Col::unused()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.idx );
			odbc.BindInput(1, &(obj.idx), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.colName() );
			odbc.BindInput(2, obj.colName);
			DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.verifyData );
			odbc.BindInput(3, &(obj.verifyData), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.typeName() );
			odbc.BindInput(4, obj.typeName);
			DEBUG(FL, "Setting input (%d) to value: %s", 5, obj.dataValue() );
			odbc.BindInput(5, obj.dataValue);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for Col::unused");
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
twine Col::unused_prepSQL(IOConn& ioc, Col& obj )
{
	EnEx ee(FL, "Col::unused_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Empty on purpose";

	// Replace the idx parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.idx;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the colName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.colName );
	}

	// Replace the verifyData parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.verifyData;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the typeName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.typeName );
	}

	// Replace the dataValue parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.dataValue );
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

