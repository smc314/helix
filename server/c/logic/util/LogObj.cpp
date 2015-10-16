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

#include "LogObj.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/util/LogObj.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine LogObjName = "LogObj";

LogObj::LogObj()
{
	EnEx ee(FL, "LogObj::LogObj()");

	init();

}

LogObj::LogObj(const LogObj& c)
{
	EnEx ee(FL, "LogObj::LogObj(const LogObj& c)");

	SUID = c.SUID;
	appName = c.appName;
	channel = c.channel;
	file = c.file;
	id = c.id;
	line = c.line;
	machineName = c.machineName;
	msg = c.msg;
	tid = c.tid;
	timestamp_a = c.timestamp_a;
	timestamp_b = c.timestamp_b;
	timestamp_c = c.timestamp_c;


}

LogObj& LogObj::operator=(const LogObj& c)
{
	EnEx ee(FL, "LogObj::operator=(const LogObj& c)");

	SUID = c.SUID;
	appName = c.appName;
	channel = c.channel;
	file = c.file;
	id = c.id;
	line = c.line;
	machineName = c.machineName;
	msg = c.msg;
	tid = c.tid;
	timestamp_a = c.timestamp_a;
	timestamp_b = c.timestamp_b;
	timestamp_c = c.timestamp_c;


	return *this;
}

LogObj::~LogObj()
{
	EnEx ee(FL, "LogObj::~LogObj()");

}

LogObj& LogObj::init()
{
	EnEx ee(FL, "LogObj::init()");

	SUID.erase();
	appName.erase();
	channel = 0;
	file.erase();
	id = 0;
	line = 0;
	machineName.erase();
	msg.erase();
	tid = 0;
	timestamp_a = 0;
	timestamp_b = 0;
	timestamp_c.erase();


	return *this;
}

LogObj& LogObj::checkSize()
{
	EnEx ee(FL, "LogObj::checkSize()");

	SUID.check_size();
	SUID.rtrim();
	appName.check_size();
	appName.rtrim();
	file.check_size();
	file.rtrim();
	machineName.check_size();
	machineName.rtrim();
	msg.check_size();
	msg.rtrim();
	timestamp_c.check_size();
	timestamp_c.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
LogObj::LogObj(xmlNodePtr node)
{
	EnEx ee(FL, "LogObj::LogObj(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
LogObj& LogObj::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "LogObj::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct LogObj is NULL.");
	}

	SUID.getAttribute(node, "SUID");
	appName.getAttribute(node, "appName");
	channel = XmlHelpers::getIntAttr(node, "channel");
	file.getAttribute(node, "file");
	id = XmlHelpers::getIntAttr(node, "id");
	line = XmlHelpers::getIntAttr(node, "line");
	machineName.getAttribute(node, "machineName");
	xmlNodePtr msg_child = XmlHelpers::FindChild(node, "msg"); if( msg_child != NULL) msg = XmlHelpers::getBase64(msg_child);
	tid = XmlHelpers::getIntAttr(node, "tid");
	timestamp_a = XmlHelpers::getIntAttr(node, "timestamp_a");
	timestamp_b = XmlHelpers::getIntAttr(node, "timestamp_b");
	timestamp_c.getAttribute(node, "timestamp_c");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr LogObj::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "LogObj::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogObj::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"LogObj", NULL);
	xmlSetProp(child, (const xmlChar*)"SUID", SUID);
	xmlSetProp(child, (const xmlChar*)"appName", appName);
	XmlHelpers::setIntAttr(child, "channel", channel);
	xmlSetProp(child, (const xmlChar*)"file", file);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "line", line);
	xmlSetProp(child, (const xmlChar*)"machineName", machineName);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"msg", NULL), msg);
	XmlHelpers::setIntAttr(child, "tid", tid);
	XmlHelpers::setIntAttr(child, "timestamp_a", timestamp_a);
	XmlHelpers::setIntAttr(child, "timestamp_b", timestamp_b);
	xmlSetProp(child, (const xmlChar*)"timestamp_c", timestamp_c);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr LogObj::createXmlDoc() const
{
	EnEx ee(FL, "LogObj::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"LogObj", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"SUID", SUID);
	xmlSetProp(child, (const xmlChar*)"appName", appName);
	XmlHelpers::setIntAttr(child, "channel", channel);
	xmlSetProp(child, (const xmlChar*)"file", file);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "line", line);
	xmlSetProp(child, (const xmlChar*)"machineName", machineName);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"msg", NULL), msg);
	XmlHelpers::setIntAttr(child, "tid", tid);
	XmlHelpers::setIntAttr(child, "timestamp_a", timestamp_a);
	XmlHelpers::setIntAttr(child, "timestamp_b", timestamp_b);
	xmlSetProp(child, (const xmlChar*)"timestamp_c", timestamp_c);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<LogObj* >* LogObj::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "LogObj::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogObj::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<LogObj* >, LogObj::deleteVector> ret = new vector<LogObj* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "LogObj") == 0){
			ret->push_back( new LogObj(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void LogObj::createXmlChildren(xmlNodePtr parent, vector<LogObj* >* vect)
{
	EnEx ee(FL, "LogObj::createXmlChildren(xmlNodePtr parent, vector<LogObj* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogObj::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr LogObj::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogObj* >* vect)
{
	EnEx ee(FL, "LogObj::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogObj* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogObj::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	LogObj::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void LogObj::deleteVector(vector<LogObj* >* vect)
{
	EnEx ee(FL, "LogObj::deleteVector(vector<LogObj* >* vect)");

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
twine& LogObj::Name()
{
	return LogObjName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This statement is merely here to define the data structure that is
			passed back and forth as a log message
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Nothing here
		 */
/*                                                                                        */
/* ************************************************************************************** */
void LogObj::unusedSqlStmt(OdbcObj& odbc, LogObj& obj )
{
	EnEx ee(FL, "LogObj::unusedSqlStmt()");

	twine stmt = "-- Nothing here";

	LogObj::unusedSqlStmt(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void LogObj::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, LogObj& obj )
{
	EnEx ee(FL, "LogObj::unusedSqlStmt()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into LogObj::unusedSqlStmt is not connected.");
	}

	int sizeof_int = sizeof(intptr_t); // so that we can have an address of this variable
	// sizeof_float not required.

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("LogObj::unusedSqlStmt()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.id );
			odbc.BindInput(1, &(obj.id), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.file() );
			odbc.BindInput(2, obj.file);
			DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.line );
			odbc.BindInput(3, &(obj.line), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.tid );
			odbc.BindInput(4, &(obj.tid), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.timestamp_a );
			odbc.BindInput(5, &(obj.timestamp_a), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 6, obj.timestamp_b );
			odbc.BindInput(6, &(obj.timestamp_b), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 7, obj.timestamp_c() );
			odbc.BindInput(7, obj.timestamp_c);
			DEBUG(FL, "Setting input (%d) to value: %d", 8, obj.channel );
			odbc.BindInput(8, &(obj.channel), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 9, obj.appName() );
			odbc.BindInput(9, obj.appName);
			DEBUG(FL, "Setting input (%d) to value: %s", 10, obj.SUID() );
			odbc.BindInput(10, obj.SUID);
			DEBUG(FL, "Setting input (%d) to value: %s", 11, obj.machineName() );
			odbc.BindInput(11, obj.machineName);
			DEBUG(FL, "Setting input (%d) to value: %s", 12, obj.msg() );
			odbc.BindInput(12, obj.msg);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for LogObj::unusedSqlStmt");
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
twine LogObj::unusedSqlStmt_prepSQL(IOConn& ioc, LogObj& obj )
{
	EnEx ee(FL, "LogObj::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the file parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.file );
	}

	// Replace the line parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.line;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the tid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.tid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the timestamp_a parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.timestamp_a;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the timestamp_b parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.timestamp_b;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the timestamp_c parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.timestamp_c );
	}

	// Replace the channel parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.channel;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the appName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.appName );
	}

	// Replace the SUID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.SUID );
	}

	// Replace the machineName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.machineName );
	}

	// Replace the msg parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.msg );
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

