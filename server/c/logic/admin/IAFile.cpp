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

#include "IAFile.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/IAFile.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine IAFileName = "IAFile";

IAFile::IAFile()
{
	EnEx ee(FL, "IAFile::IAFile()");

	init();

}

IAFile::IAFile(const IAFile& c)
{
	EnEx ee(FL, "IAFile::IAFile(const IAFile& c)");

	Description = c.Description;
	FileContents = c.FileContents;
	FileName = c.FileName;
	FileSize = c.FileSize;
	MoveDest = c.MoveDest;
	MoveSource = c.MoveSource;
	ParentFolder = c.ParentFolder;
	ReturnCode = c.ReturnCode;
	Status = c.Status;
	Step = c.Step;
	TargetFolder = c.TargetFolder;
	Title = c.Title;
	Type = c.Type;
	isVSE = c.isVSE;
	isZOS = c.isZOS;


}

IAFile& IAFile::operator=(const IAFile& c)
{
	EnEx ee(FL, "IAFile::operator=(const IAFile& c)");

	Description = c.Description;
	FileContents = c.FileContents;
	FileName = c.FileName;
	FileSize = c.FileSize;
	MoveDest = c.MoveDest;
	MoveSource = c.MoveSource;
	ParentFolder = c.ParentFolder;
	ReturnCode = c.ReturnCode;
	Status = c.Status;
	Step = c.Step;
	TargetFolder = c.TargetFolder;
	Title = c.Title;
	Type = c.Type;
	isVSE = c.isVSE;
	isZOS = c.isZOS;


	return *this;
}

IAFile::~IAFile()
{
	EnEx ee(FL, "IAFile::~IAFile()");

}

IAFile& IAFile::init()
{
	EnEx ee(FL, "IAFile::init()");

	Description.erase();
	FileContents.erase();
	FileName.erase();
	FileSize = 0;
	MoveDest.erase();
	MoveSource.erase();
	ParentFolder.erase();
	ReturnCode = 0;
	Status.erase();
	Step.erase();
	TargetFolder.erase();
	Title.erase();
	Type.erase();
	isVSE = 0;
	isZOS = 0;


	return *this;
}

IAFile& IAFile::checkSize()
{
	EnEx ee(FL, "IAFile::checkSize()");

	Description.check_size();
	Description.rtrim();
	FileContents.check_size();
	FileContents.rtrim();
	FileName.check_size();
	FileName.rtrim();
	MoveDest.check_size();
	MoveDest.rtrim();
	MoveSource.check_size();
	MoveSource.rtrim();
	ParentFolder.check_size();
	ParentFolder.rtrim();
	Status.check_size();
	Status.rtrim();
	Step.check_size();
	Step.rtrim();
	TargetFolder.check_size();
	TargetFolder.rtrim();
	Title.check_size();
	Title.rtrim();
	Type.check_size();
	Type.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
IAFile::IAFile(xmlNodePtr node)
{
	EnEx ee(FL, "IAFile::IAFile(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
IAFile& IAFile::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "IAFile::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct IAFile is NULL.");
	}

	Description.getAttribute(node, "Description");
	xmlNodePtr FileContents_child = XmlHelpers::FindChild(node, "FileContents"); if( FileContents_child != NULL) FileContents = XmlHelpers::getBase64(FileContents_child);
	FileName.getAttribute(node, "FileName");
	FileSize = XmlHelpers::getIntAttr(node, "FileSize");
	MoveDest.getAttribute(node, "MoveDest");
	MoveSource.getAttribute(node, "MoveSource");
	ParentFolder.getAttribute(node, "ParentFolder");
	ReturnCode = XmlHelpers::getIntAttr(node, "ReturnCode");
	Status.getAttribute(node, "Status");
	Step.getAttribute(node, "Step");
	TargetFolder.getAttribute(node, "TargetFolder");
	Title.getAttribute(node, "Title");
	Type.getAttribute(node, "Type");
	isVSE = XmlHelpers::getIntAttr(node, "isVSE");
	isZOS = XmlHelpers::getIntAttr(node, "isZOS");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr IAFile::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "IAFile::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFile::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"IAFile", NULL);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"FileContents", NULL), FileContents);
	xmlSetProp(child, (const xmlChar*)"FileName", FileName);
	XmlHelpers::setIntAttr(child, "FileSize", FileSize);
	xmlSetProp(child, (const xmlChar*)"MoveDest", MoveDest);
	xmlSetProp(child, (const xmlChar*)"MoveSource", MoveSource);
	xmlSetProp(child, (const xmlChar*)"ParentFolder", ParentFolder);
	XmlHelpers::setIntAttr(child, "ReturnCode", ReturnCode);
	xmlSetProp(child, (const xmlChar*)"Status", Status);
	xmlSetProp(child, (const xmlChar*)"Step", Step);
	xmlSetProp(child, (const xmlChar*)"TargetFolder", TargetFolder);
	xmlSetProp(child, (const xmlChar*)"Title", Title);
	xmlSetProp(child, (const xmlChar*)"Type", Type);
	XmlHelpers::setIntAttr(child, "isVSE", isVSE);
	XmlHelpers::setIntAttr(child, "isZOS", isZOS);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr IAFile::createXmlDoc() const
{
	EnEx ee(FL, "IAFile::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"IAFile", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"FileContents", NULL), FileContents);
	xmlSetProp(child, (const xmlChar*)"FileName", FileName);
	XmlHelpers::setIntAttr(child, "FileSize", FileSize);
	xmlSetProp(child, (const xmlChar*)"MoveDest", MoveDest);
	xmlSetProp(child, (const xmlChar*)"MoveSource", MoveSource);
	xmlSetProp(child, (const xmlChar*)"ParentFolder", ParentFolder);
	XmlHelpers::setIntAttr(child, "ReturnCode", ReturnCode);
	xmlSetProp(child, (const xmlChar*)"Status", Status);
	xmlSetProp(child, (const xmlChar*)"Step", Step);
	xmlSetProp(child, (const xmlChar*)"TargetFolder", TargetFolder);
	xmlSetProp(child, (const xmlChar*)"Title", Title);
	xmlSetProp(child, (const xmlChar*)"Type", Type);
	XmlHelpers::setIntAttr(child, "isVSE", isVSE);
	XmlHelpers::setIntAttr(child, "isZOS", isZOS);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<IAFile* >* IAFile::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "IAFile::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFile::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<IAFile* >, IAFile::deleteVector> ret = new vector<IAFile* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "IAFile") == 0){
			ret->push_back( new IAFile(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void IAFile::createXmlChildren(xmlNodePtr parent, vector<IAFile* >* vect)
{
	EnEx ee(FL, "IAFile::createXmlChildren(xmlNodePtr parent, vector<IAFile* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFile::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr IAFile::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<IAFile* >* vect)
{
	EnEx ee(FL, "IAFile::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<IAFile* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to IAFile::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	IAFile::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void IAFile::deleteVector(vector<IAFile* >* vect)
{
	EnEx ee(FL, "IAFile::deleteVector(vector<IAFile* >* vect)");

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
twine& IAFile::Name()
{
	return IAFileName;
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
   * ParentFolder
   * FileName
   * Description
   * Step
   * Type
   * Title
   * Status
   * ReturnCode
   * MoveSource
   * MoveDest
   * FileContents
   * TargetFolder
 */
/* ************************************************************************************** */
vector<IAFile* >* IAFile::unusedSqlStmt(OdbcObj& odbc, intptr_t isZOS, intptr_t isVSE, intptr_t FileSize)
{
	EnEx ee(FL, "IAFile::unusedSqlStmt()");

	twine stmt = "-- Nothing here on purpose 			-- Note, the Output/Input designations below don't matter.  Output 			-- defaults to string as a type.  Inputs require you to specify the  			-- data type.  So, for those object members where we care about the 			-- data type, we use Input.  All the others are strings and so we 			-- just use Output for less typing.";

	return IAFile::unusedSqlStmt(odbc, stmt, true, isZOS, isVSE, FileSize);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<IAFile* >* IAFile::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, intptr_t isZOS, intptr_t isVSE, intptr_t FileSize)
{
	EnEx ee(FL, "IAFile::unusedSqlStmt(twine& stmt, bool useInputs)");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into IAFile::unusedSqlStmt is not connected.");
	}

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<IAFile* >, IAFile::deleteVector> ret = new vector<IAFile* >();

	// Use a single local object to handle fetching the data:
	IAFile local;
	int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
	int sizeof_float = sizeof(float); // so that we can have an address of this variable

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_SELECT);

	if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %d", 1, isZOS );
			odbc.BindInput(1, &isZOS, &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 2, isVSE );
			odbc.BindInput(2, &isVSE, &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 3, FileSize );
			odbc.BindInput(3, &FileSize, &sizeof_int, DB_INT);
	}

	{ // Used for scope for the timing object.
		EnEx eeExe("IAFile::unusedSqlStmt()-ExecStmt");

		// Execute the statement
		DEBUG(FL, "Executing the statement for IAFile::unusedSqlStmt");
		odbc.ExecStmt();
	}

	// Now that we've executed the statement, we'll know how many output columns we have.
	// Grab the column count so that we don't bind invalid output positions.
	int colCount = odbc.GetResultsetColumnCount();

	// Bind the outputs to our single local object.  We can then make copies of it to
	// fill our return vector.
	DEBUG(FL, "Binding outputs");
	if( 1 <= colCount ){
		DEBUG(FL, "Binding member %s", "ParentFolder");
		odbc.BindOutput(1, local.ParentFolder);
	}
	if( 2 <= colCount ){
		DEBUG(FL, "Binding member %s", "FileName");
		odbc.BindOutput(2, local.FileName);
	}
	if( 3 <= colCount ){
		DEBUG(FL, "Binding member %s", "Description");
		odbc.BindOutput(3, local.Description);
	}
	if( 4 <= colCount ){
		DEBUG(FL, "Binding member %s", "Step");
		odbc.BindOutput(4, local.Step);
	}
	if( 5 <= colCount ){
		DEBUG(FL, "Binding member %s", "Type");
		odbc.BindOutput(5, local.Type);
	}
	if( 6 <= colCount ){
		DEBUG(FL, "Binding member %s", "Title");
		odbc.BindOutput(6, local.Title);
	}
	if( 7 <= colCount ){
		DEBUG(FL, "Binding member %s", "Status");
		odbc.BindOutput(7, local.Status);
	}
	if( 8 <= colCount ){
		DEBUG(FL, "Binding member %s", "ReturnCode");
		odbc.BindOutput(8, &(local.ReturnCode), &sizeof_int, DB_INT);
	}
	if( 9 <= colCount ){
		DEBUG(FL, "Binding member %s", "MoveSource");
		odbc.BindOutput(9, local.MoveSource);
	}
	if( 10 <= colCount ){
		DEBUG(FL, "Binding member %s", "MoveDest");
		odbc.BindOutput(10, local.MoveDest);
	}
	if( 11 <= colCount ){
		DEBUG(FL, "Binding member %s", "FileContents");
		odbc.BindOutput(11, local.FileContents);
	}
	if( 12 <= colCount ){
		DEBUG(FL, "Binding member %s", "TargetFolder");
		odbc.BindOutput(12, local.TargetFolder);
	}

	int count;
	{ // Used for scope for the timing object.
		EnEx eeExe("IAFile::unusedSqlStmt()-FetchLoop");
		DEBUG(FL, "Fetching data...");

		while( (count = odbc.FetchData()) != 0){
			// After a fetch, we need to check all of our data sizes:
			local.checkSize();

			IAFile* obj = new IAFile( local ); // make a copy of what's in local
			ret->push_back(obj); // add it to our return vector

			// Clean out the values in local:
			local.init();

		}
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
twine IAFile::unusedSqlStmt_prepSQL(IOConn& ioc, intptr_t isZOS, intptr_t isVSE, intptr_t FileSize)
{
	EnEx ee(FL, "IAFile::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here on purpose 			-- Note, the Output/Input designations below don't matter.  Output 			-- defaults to string as a type.  Inputs require you to specify the  			-- data type.  So, for those object members where we care about the 			-- data type, we use Input.  All the others are strings and so we 			-- just use Output for less typing.";

	// Replace the isZOS parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = isZOS;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the isVSE parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = isVSE;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the FileSize parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = FileSize;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

