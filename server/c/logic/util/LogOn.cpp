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

#include "LogOn.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/util/LogOn.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine LogOnName = "LogOn";

LogOn::LogOn()
{
	EnEx ee(FL, "LogOn::LogOn()");

	init();

}

LogOn::LogOn(const LogOn& c)
{
	EnEx ee(FL, "LogOn::LogOn(const LogOn& c)");

	Alias = c.Alias;
	ConnName = c.ConnName;
	Host = c.Host;
	Pass = c.Pass;
	Port = c.Port;
	User = c.User;


}

LogOn& LogOn::operator=(const LogOn& c)
{
	EnEx ee(FL, "LogOn::operator=(const LogOn& c)");

	Alias = c.Alias;
	ConnName = c.ConnName;
	Host = c.Host;
	Pass = c.Pass;
	Port = c.Port;
	User = c.User;


	return *this;
}

LogOn::~LogOn()
{
	EnEx ee(FL, "LogOn::~LogOn()");

}

LogOn& LogOn::init()
{
	EnEx ee(FL, "LogOn::init()");

	Alias.erase();
	ConnName.erase();
	Host.erase();
	Pass.erase();
	Port.erase();
	User.erase();


	return *this;
}

LogOn& LogOn::checkSize()
{
	EnEx ee(FL, "LogOn::checkSize()");

	Alias.check_size();
	Alias.rtrim();
	ConnName.check_size();
	ConnName.rtrim();
	Host.check_size();
	Host.rtrim();
	Pass.check_size();
	Pass.rtrim();
	Port.check_size();
	Port.rtrim();
	User.check_size();
	User.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
LogOn::LogOn(xmlNodePtr node)
{
	EnEx ee(FL, "LogOn::LogOn(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
LogOn& LogOn::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "LogOn::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct LogOn is NULL.");
	}

	Alias.getAttribute(node, "Alias");
	ConnName.getAttribute(node, "ConnName");
	Host.getAttribute(node, "Host");
	Pass.getAttribute(node, "Pass");
	Port.getAttribute(node, "Port");
	User.getAttribute(node, "User");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr LogOn::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "LogOn::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogOn::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"LogOn", NULL);
	xmlSetProp(child, (const xmlChar*)"Alias", Alias);
	xmlSetProp(child, (const xmlChar*)"ConnName", ConnName);
	xmlSetProp(child, (const xmlChar*)"Host", Host);
	xmlSetProp(child, (const xmlChar*)"Pass", Pass);
	xmlSetProp(child, (const xmlChar*)"Port", Port);
	xmlSetProp(child, (const xmlChar*)"User", User);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr LogOn::createXmlDoc() const
{
	EnEx ee(FL, "LogOn::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"LogOn", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Alias", Alias);
	xmlSetProp(child, (const xmlChar*)"ConnName", ConnName);
	xmlSetProp(child, (const xmlChar*)"Host", Host);
	xmlSetProp(child, (const xmlChar*)"Pass", Pass);
	xmlSetProp(child, (const xmlChar*)"Port", Port);
	xmlSetProp(child, (const xmlChar*)"User", User);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<LogOn* >* LogOn::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "LogOn::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogOn::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<LogOn* >, LogOn::deleteVector> ret = new vector<LogOn* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "LogOn") == 0){
			ret->push_back( new LogOn(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void LogOn::createXmlChildren(xmlNodePtr parent, vector<LogOn* >* vect)
{
	EnEx ee(FL, "LogOn::createXmlChildren(xmlNodePtr parent, vector<LogOn* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogOn::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr LogOn::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogOn* >* vect)
{
	EnEx ee(FL, "LogOn::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogOn* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogOn::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	LogOn::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void LogOn::deleteVector(vector<LogOn* >* vect)
{
	EnEx ee(FL, "LogOn::deleteVector(vector<LogOn* >* vect)");

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
twine& LogOn::Name()
{
	return LogOnName;
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
			passed back and forth to determine log on credentials.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Nothing here
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * Host
   * Port
   * User
   * Pass
   * ConnName
   * Alias
 */
/* ************************************************************************************** */
vector<LogOn* >* LogOn::unusedSqlStmt(OdbcObj& odbc, twine& Host, twine& Port, twine& User, twine& Pass, twine& Alias)
{
	EnEx ee(FL, "LogOn::unusedSqlStmt()");

	twine stmt = "-- Nothing here";

	return LogOn::unusedSqlStmt(odbc, stmt, true, Host, Port, User, Pass, Alias);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<LogOn* >* LogOn::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, twine& Host, twine& Port, twine& User, twine& Pass, twine& Alias)
{
	EnEx ee(FL, "LogOn::unusedSqlStmt(twine& stmt, bool useInputs)");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into LogOn::unusedSqlStmt is not connected.");
	}

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<LogOn* >, LogOn::deleteVector> ret = new vector<LogOn* >();

	// Use a single local object to handle fetching the data:
	LogOn local;

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_SELECT);

	if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, Host() );
			odbc.BindInput(1, Host);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, Port() );
			odbc.BindInput(2, Port);
			DEBUG(FL, "Setting input (%d) to value: %s", 3, User() );
			odbc.BindInput(3, User);
			DEBUG(FL, "Setting input (%d) to value: %s", 4, Pass() );
			odbc.BindInput(4, Pass);
			DEBUG(FL, "Setting input (%d) to value: %s", 5, Alias() );
			odbc.BindInput(5, Alias);
	}

	{ // Used for scope for the timing object.
		EnEx eeExe("LogOn::unusedSqlStmt()-ExecStmt");

		// Execute the statement
		DEBUG(FL, "Executing the statement for LogOn::unusedSqlStmt");
		odbc.ExecStmt();
	}

	// Now that we've executed the statement, we'll know how many output columns we have.
	// Grab the column count so that we don't bind invalid output positions.
	int colCount = odbc.GetResultsetColumnCount();

	// Bind the outputs to our single local object.  We can then make copies of it to
	// fill our return vector.
	DEBUG(FL, "Binding outputs");
	if( 1 <= colCount ){
		DEBUG(FL, "Binding member %s", "Host");
		odbc.BindOutput(1, local.Host);
	}
	if( 2 <= colCount ){
		DEBUG(FL, "Binding member %s", "Port");
		odbc.BindOutput(2, local.Port);
	}
	if( 3 <= colCount ){
		DEBUG(FL, "Binding member %s", "User");
		odbc.BindOutput(3, local.User);
	}
	if( 4 <= colCount ){
		DEBUG(FL, "Binding member %s", "Pass");
		odbc.BindOutput(4, local.Pass);
	}
	if( 5 <= colCount ){
		DEBUG(FL, "Binding member %s", "ConnName");
		odbc.BindOutput(5, local.ConnName);
	}
	if( 6 <= colCount ){
		DEBUG(FL, "Binding member %s", "Alias");
		odbc.BindOutput(6, local.Alias);
	}

	int count;
	{ // Used for scope for the timing object.
		EnEx eeExe("LogOn::unusedSqlStmt()-FetchLoop");
		DEBUG(FL, "Fetching data...");

		while( (count = odbc.FetchData()) != 0){
			// After a fetch, we need to check all of our data sizes:
			local.checkSize();

			LogOn* obj = new LogOn( local ); // make a copy of what's in local
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
twine LogOn::unusedSqlStmt_prepSQL(IOConn& ioc, twine& Host, twine& Port, twine& User, twine& Pass, twine& Alias)
{
	EnEx ee(FL, "LogOn::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here";

	// Replace the Host parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Host );
	}

	// Replace the Port parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Port );
	}

	// Replace the User parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, User );
	}

	// Replace the Pass parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Pass );
	}

	// Replace the Alias parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Alias );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

