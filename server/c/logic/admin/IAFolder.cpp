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

#include "IAFolder.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/IAFolder.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine IAFolderName = "IAFolder";

IAFolder::IAFolder()
{
	EnEx ee(FL, "IAFolder::IAFolder()");

	init();

}

IAFolder::IAFolder(const IAFolder& c)
{
	EnEx ee(FL, "IAFolder::IAFolder(const IAFolder& c)");

	Description = c.Description;
	FolderName = c.FolderName;
	ParentFolder = c.ParentFolder;


}

IAFolder& IAFolder::operator=(const IAFolder& c)
{
	EnEx ee(FL, "IAFolder::operator=(const IAFolder& c)");

	Description = c.Description;
	FolderName = c.FolderName;
	ParentFolder = c.ParentFolder;


	return *this;
}

IAFolder::~IAFolder()
{
	EnEx ee(FL, "IAFolder::~IAFolder()");

}

IAFolder& IAFolder::init()
{
	EnEx ee(FL, "IAFolder::init()");

	Description.erase();
	FolderName.erase();
	ParentFolder.erase();


	return *this;
}

IAFolder& IAFolder::checkSize()
{
	EnEx ee(FL, "IAFolder::checkSize()");

	Description.check_size();
	Description.rtrim();
	FolderName.check_size();
	FolderName.rtrim();
	ParentFolder.check_size();
	ParentFolder.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
IAFolder::IAFolder(xmlNodePtr node)
{
	EnEx ee(FL, "IAFolder::IAFolder(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
IAFolder& IAFolder::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "IAFolder::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct IAFolder is NULL.");
	}

	Description.getAttribute(node, "Description");
	FolderName.getAttribute(node, "FolderName");
	ParentFolder.getAttribute(node, "ParentFolder");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr IAFolder::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "IAFolder::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFolder::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"IAFolder", NULL);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"FolderName", FolderName);
	xmlSetProp(child, (const xmlChar*)"ParentFolder", ParentFolder);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr IAFolder::createXmlDoc() const
{
	EnEx ee(FL, "IAFolder::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"IAFolder", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"FolderName", FolderName);
	xmlSetProp(child, (const xmlChar*)"ParentFolder", ParentFolder);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<IAFolder* >* IAFolder::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "IAFolder::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFolder::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<IAFolder* >, IAFolder::deleteVector> ret = new vector<IAFolder* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "IAFolder") == 0){
			ret->push_back( new IAFolder(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void IAFolder::createXmlChildren(xmlNodePtr parent, vector<IAFolder* >* vect)
{
	EnEx ee(FL, "IAFolder::createXmlChildren(xmlNodePtr parent, vector<IAFolder* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFolder::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr IAFolder::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<IAFolder* >* vect)
{
	EnEx ee(FL, "IAFolder::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<IAFolder* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFolder::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	IAFolder::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void IAFolder::deleteVector(vector<IAFolder* >* vect)
{
	EnEx ee(FL, "IAFolder::deleteVector(vector<IAFolder* >* vect)");

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
twine& IAFolder::Name()
{
	return IAFolderName;
}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This statement is merely here to define the data structure that is
			passed back and forth to define an installation plan
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Nothing here on purpose
			-- Note, the Output/Input designations below don't matter.  Output
			-- defaults to string as a type.  Inputs require you to specify the 
			-- data type.  So, for those object members where we care about the
			-- data type, we use Input.  All the others are strings and so we
			-- just use Output for less typing.
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * FolderName
   * Description
 */
/* ************************************************************************************** */
vector<IAFolder* >* IAFolder::unusedSqlStmt(OdbcObj& odbc, twine& ParentFolder)
{
	EnEx ee(FL, "IAFolder::unusedSqlStmt()");

	twine stmt = "-- Nothing here on purpose 			-- Note, the Output/Input designations below don't matter.  Output 			-- defaults to string as a type.  Inputs require you to specify the  			-- data type.  So, for those object members where we care about the 			-- data type, we use Input.  All the others are strings and so we 			-- just use Output for less typing.";

	return IAFolder::unusedSqlStmt(odbc, stmt, true, ParentFolder);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<IAFolder* >* IAFolder::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, twine& ParentFolder)
{
	EnEx ee(FL, "IAFolder::unusedSqlStmt(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into IAFolder::unusedSqlStmt is not connected.");
	}

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<IAFolder* >, IAFolder::deleteVector> ret = new vector<IAFolder* >();

	// Use a single local object to handle fetching the data:
	IAFolder local;

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_SELECT);

	if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, ParentFolder() );
			odbc.BindInput(1, ParentFolder);
	}

	selectTimer.Start();
	{ // Used for scope for the timing object.
		EnEx eeExe("IAFolder::unusedSqlStmt()-ExecStmt");

		// Execute the statement
		DEBUG(FL, "Executing the statement for IAFolder::unusedSqlStmt");
		odbc.ExecStmt();
	}
	selectTimer.Finish();
	if(selectTimer.Duration() > 0.2){
		WARN(FL, "Statement took longer than 200ms to execute.");
	}


	// Now that we've executed the statement, we'll know how many output columns we have.
	// Grab the column count so that we don't bind invalid output positions.
	int colCount = odbc.GetResultsetColumnCount();

	// Bind the outputs to our single local object.  We can then make copies of it to
	// fill our return vector.
	DEBUG(FL, "Binding outputs");
	if( 1 <= colCount ){
		DEBUG(FL, "Binding member %s", "FolderName");
		odbc.BindOutput(1, local.FolderName);
	}
	if( 2 <= colCount ){
		DEBUG(FL, "Binding member %s", "Description");
		odbc.BindOutput(2, local.Description);
	}

	int count;
	fetchTimer.Start();
	{ // Used for scope for the timing object.
		EnEx eeExe("IAFolder::unusedSqlStmt()-FetchLoop");
		DEBUG(FL, "Fetching data...");

		while( (count = odbc.FetchData()) != 0){
			// After a fetch, we need to check all of our data sizes:
			local.checkSize();

			IAFolder* obj = new IAFolder( local ); // make a copy of what's in local
			ret->push_back(obj); // add it to our return vector

			// Clean out the values in local:
			local.init();

		}
	}
	fetchTimer.Finish();
	if(fetchTimer.Duration() > 1.0){
		WARN(FL, "Statement took longer than 1000ms to fetch.");
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine IAFolder::unusedSqlStmt_prepSQL(IOConn& ioc, twine& ParentFolder)
{
	EnEx ee(FL, "IAFolder::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here on purpose 			-- Note, the Output/Input designations below don't matter.  Output 			-- defaults to string as a type.  Inputs require you to specify the  			-- data type.  So, for those object members where we care about the 			-- data type, we use Input.  All the others are strings and so we 			-- just use Output for less typing.";

	// Replace the ParentFolder parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ParentFolder );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

