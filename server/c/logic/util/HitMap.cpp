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

#include "HitMap.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/util/HitMap.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine HitMapName = "HitMap";

HitMap::HitMap()
{
	EnEx ee(FL, "HitMap::HitMap()");

	init();

}

HitMap::HitMap(const HitMap& c)
{
	EnEx ee(FL, "HitMap::HitMap(const HitMap& c)");

	AverageCycles = c.AverageCycles;
	MaxCycles = c.MaxCycles;
	MethodName = c.MethodName;
	MinCycles = c.MinCycles;
	TotalCycles = c.TotalCycles;
	TotalHits = c.TotalHits;


}

HitMap& HitMap::operator=(const HitMap& c)
{
	EnEx ee(FL, "HitMap::operator=(const HitMap& c)");

	AverageCycles = c.AverageCycles;
	MaxCycles = c.MaxCycles;
	MethodName = c.MethodName;
	MinCycles = c.MinCycles;
	TotalCycles = c.TotalCycles;
	TotalHits = c.TotalHits;


	return *this;
}

HitMap::~HitMap()
{
	EnEx ee(FL, "HitMap::~HitMap()");

}

HitMap& HitMap::init()
{
	EnEx ee(FL, "HitMap::init()");

	AverageCycles = 0;
	MaxCycles = 0;
	MethodName.erase();
	MinCycles = 0;
	TotalCycles = 0;
	TotalHits = 0;


	return *this;
}

HitMap& HitMap::checkSize()
{
	EnEx ee(FL, "HitMap::checkSize()");

	MethodName.check_size();
	MethodName.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
HitMap::HitMap(xmlNodePtr node)
{
	EnEx ee(FL, "HitMap::HitMap(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
HitMap& HitMap::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "HitMap::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct HitMap is NULL.");
	}

	AverageCycles = XmlHelpers::getIntAttr(node, "AverageCycles");
	MaxCycles = XmlHelpers::getIntAttr(node, "MaxCycles");
	MethodName.getAttribute(node, "MethodName");
	MinCycles = XmlHelpers::getIntAttr(node, "MinCycles");
	TotalCycles = XmlHelpers::getIntAttr(node, "TotalCycles");
	TotalHits = XmlHelpers::getIntAttr(node, "TotalHits");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr HitMap::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "HitMap::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to HitMap::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"HitMap", NULL);
	XmlHelpers::setIntAttr(child, "AverageCycles", AverageCycles);
	XmlHelpers::setIntAttr(child, "MaxCycles", MaxCycles);
	xmlSetProp(child, (const xmlChar*)"MethodName", MethodName);
	XmlHelpers::setIntAttr(child, "MinCycles", MinCycles);
	XmlHelpers::setIntAttr(child, "TotalCycles", TotalCycles);
	XmlHelpers::setIntAttr(child, "TotalHits", TotalHits);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr HitMap::createXmlDoc() const
{
	EnEx ee(FL, "HitMap::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"HitMap", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	XmlHelpers::setIntAttr(child, "AverageCycles", AverageCycles);
	XmlHelpers::setIntAttr(child, "MaxCycles", MaxCycles);
	xmlSetProp(child, (const xmlChar*)"MethodName", MethodName);
	XmlHelpers::setIntAttr(child, "MinCycles", MinCycles);
	XmlHelpers::setIntAttr(child, "TotalCycles", TotalCycles);
	XmlHelpers::setIntAttr(child, "TotalHits", TotalHits);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<HitMap* >* HitMap::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "HitMap::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to HitMap::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<HitMap* >, HitMap::deleteVector> ret = new vector<HitMap* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "HitMap") == 0){
			ret->push_back( new HitMap(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void HitMap::createXmlChildren(xmlNodePtr parent, vector<HitMap* >* vect)
{
	EnEx ee(FL, "HitMap::createXmlChildren(xmlNodePtr parent, vector<HitMap* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to HitMap::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr HitMap::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<HitMap* >* vect)
{
	EnEx ee(FL, "HitMap::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<HitMap* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to HitMap::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	HitMap::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void HitMap::deleteVector(vector<HitMap* >* vect)
{
	EnEx ee(FL, "HitMap::deleteVector(vector<HitMap* >* vect)");

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
twine& HitMap::Name()
{
	return HitMapName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is a dummy statement used to define our data object.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- empty on purpose
		 */
/*                                                                                        */
/* ************************************************************************************** */
void HitMap::dummy(OdbcObj& odbc, HitMap& obj )
{
	EnEx ee(FL, "HitMap::dummy()");

	twine stmt = "-- empty on purpose";

	HitMap::dummy(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void HitMap::dummy(OdbcObj& odbc, twine& stmt, bool useInputs, HitMap& obj )
{
	EnEx ee(FL, "HitMap::dummy()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into HitMap::dummy is not connected.");
	}

	int sizeof_int = sizeof(intptr_t); // so that we can have an address of this variable
	// sizeof_float not required.

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("HitMap::dummy()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.MethodName() );
			odbc.BindInput(1, obj.MethodName);
			DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.TotalHits );
			odbc.BindInput(2, &(obj.TotalHits), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.AverageCycles );
			odbc.BindInput(3, &(obj.AverageCycles), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.MinCycles );
			odbc.BindInput(4, &(obj.MinCycles), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.MaxCycles );
			odbc.BindInput(5, &(obj.MaxCycles), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 6, obj.TotalCycles );
			odbc.BindInput(6, &(obj.TotalCycles), &sizeof_int, DB_INT);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for HitMap::dummy");
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
twine HitMap::dummy_prepSQL(IOConn& ioc, HitMap& obj )
{
	EnEx ee(FL, "HitMap::dummy_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- empty on purpose";

	// Replace the MethodName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.MethodName );
	}

	// Replace the TotalHits parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.TotalHits;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the AverageCycles parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.AverageCycles;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the MinCycles parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.MinCycles;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the MaxCycles parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.MaxCycles;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the TotalCycles parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.TotalCycles;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

