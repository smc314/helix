/* **************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include <AnException.h>
#include <EnEx.h>
#include <Log.h>
#include <XmlHelpers.h>
#include <Timer.h>
using namespace SLib;

#include "Row.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/Row.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine RowName = "Row";

Row::Row()
{
	EnEx ee(FL, "Row::Row()");

	init();

}

Row::Row(const Row& c)
{
	EnEx ee(FL, "Row::Row(const Row& c)");

	idx = c.idx;
	Cols = new vector<Col*>();
	for(size_t i = 0; i < c.Cols->size(); i++){
		Cols->push_back( new Col( *(c.Cols->at( i )) ) );
	}


}

Row& Row::operator=(const Row& c)
{
	EnEx ee(FL, "Row::operator=(const Row& c)");

	idx = c.idx;
	Cols = new vector<Col*>();
	for(size_t i = 0; i < c.Cols->size(); i++){
		Cols->push_back( new Col( *(c.Cols->at( i )) ) );
	}


	return *this;
}

Row::~Row()
{
	EnEx ee(FL, "Row::~Row()");

}

Row& Row::init()
{
	EnEx ee(FL, "Row::init()");

	idx = 0;
	Cols = new vector<Col*>();


	return *this;
}

Row& Row::checkSize()
{
	EnEx ee(FL, "Row::checkSize()");



	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Row::Row(xmlNodePtr node)
{
	EnEx ee(FL, "Row::Row(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Row& Row::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Row::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Row is NULL.");
	}

	idx = XmlHelpers::getIntAttr(node, "idx");
	Cols = Col::readXmlChildren( XmlHelpers::FindChild( node, "Cols") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Row::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Row::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Row::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Row", NULL);
	XmlHelpers::setIntAttr(child, "idx", idx);
	xmlNodePtr Cols_node = xmlNewChild(child, NULL, (const xmlChar*)"Cols", NULL);
	Col::createXmlChildren( Cols_node, Cols );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Row::createXmlDoc() const
{
	EnEx ee(FL, "Row::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Row", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	XmlHelpers::setIntAttr(child, "idx", idx);
	xmlNodePtr Cols_node = xmlNewChild(child, NULL, (const xmlChar*)"Cols", NULL);
	Col::createXmlChildren( Cols_node, Cols );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Row* >* Row::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Row::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Row::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Row* >, Row::deleteVector> ret = new vector<Row* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Row") == 0){
			ret->push_back( new Row(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Row::createXmlChildren(xmlNodePtr parent, vector<Row* >* vect)
{
	EnEx ee(FL, "Row::createXmlChildren(xmlNodePtr parent, vector<Row* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Row::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr Row::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Row* >* vect)
{
	EnEx ee(FL, "Row::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Row* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Row::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	Row::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Row::deleteVector(vector<Row* >* vect)
{
	EnEx ee(FL, "Row::deleteVector(vector<Row* >* vect)");

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
twine& Row::Name()
{
	return RowName;
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
void Row::unused(OdbcObj& odbc, Row& obj )
{
	EnEx ee(FL, "Row::unused()");

	twine stmt = "-- Empty on purpose";

	Row::unused(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Row::unused(OdbcObj& odbc, twine& stmt, bool useInputs, Row& obj )
{
	EnEx ee(FL, "Row::unused()");

	Timer selectTimer;

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into Row::unused is not connected.");
	}

	int sizeof_int = sizeof(intptr_t); // so that we can have an address of this variable
	// sizeof_float not required.

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	selectTimer.Start();
	{ // Used for scope for the timing object.
		EnEx eeExe("Row::unused()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.idx );
			odbc.BindInput(1, &(obj.idx), &sizeof_int, DB_INT);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for Row::unused");
		odbc.ExecStmt();
	}
	selectTimer.Finish();
	if(selectTimer.Duration() > 0.2){
		WARN(FL, "Statement took longer than 200ms to execute.");
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
twine Row::unused_prepSQL(IOConn& ioc, Row& obj )
{
	EnEx ee(FL, "Row::unused_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Empty on purpose";

	// Replace the idx parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.idx;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

