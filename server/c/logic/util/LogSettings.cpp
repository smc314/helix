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

#include "LogSettings.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/util/LogSettings.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine LogSettingsName = "LogSettings";

LogSettings::LogSettings()
{
	EnEx ee(FL, "LogSettings::LogSettings()");

	init();

}

LogSettings::LogSettings(const LogSettings& c)
{
	EnEx ee(FL, "LogSettings::LogSettings(const LogSettings& c)");

	BufferSize = c.BufferSize;
	LogFile = c.LogFile;
	MaxSize = c.MaxSize;
	debug = c.debug;
	debugCapture = c.debugCapture;
	debugDump = c.debugDump;
	error = c.error;
	errorCapture = c.errorCapture;
	errorDump = c.errorDump;
	info = c.info;
	infoCapture = c.infoCapture;
	infoDump = c.infoDump;
	panic = c.panic;
	panicCapture = c.panicCapture;
	panicDump = c.panicDump;
	sql = c.sql;
	sqlCapture = c.sqlCapture;
	sqlDump = c.sqlDump;
	trace = c.trace;
	traceCapture = c.traceCapture;
	traceDump = c.traceDump;
	warn = c.warn;
	warnCapture = c.warnCapture;
	warnDump = c.warnDump;


}

LogSettings& LogSettings::operator=(const LogSettings& c)
{
	EnEx ee(FL, "LogSettings::operator=(const LogSettings& c)");

	BufferSize = c.BufferSize;
	LogFile = c.LogFile;
	MaxSize = c.MaxSize;
	debug = c.debug;
	debugCapture = c.debugCapture;
	debugDump = c.debugDump;
	error = c.error;
	errorCapture = c.errorCapture;
	errorDump = c.errorDump;
	info = c.info;
	infoCapture = c.infoCapture;
	infoDump = c.infoDump;
	panic = c.panic;
	panicCapture = c.panicCapture;
	panicDump = c.panicDump;
	sql = c.sql;
	sqlCapture = c.sqlCapture;
	sqlDump = c.sqlDump;
	trace = c.trace;
	traceCapture = c.traceCapture;
	traceDump = c.traceDump;
	warn = c.warn;
	warnCapture = c.warnCapture;
	warnDump = c.warnDump;


	return *this;
}

LogSettings::~LogSettings()
{
	EnEx ee(FL, "LogSettings::~LogSettings()");

}

LogSettings& LogSettings::init()
{
	EnEx ee(FL, "LogSettings::init()");

	BufferSize = 0;
	LogFile.erase();
	MaxSize = 0;
	debug = 0;
	debugCapture = 0;
	debugDump = 0;
	error = 0;
	errorCapture = 0;
	errorDump = 0;
	info = 0;
	infoCapture = 0;
	infoDump = 0;
	panic = 0;
	panicCapture = 0;
	panicDump = 0;
	sql = 0;
	sqlCapture = 0;
	sqlDump = 0;
	trace = 0;
	traceCapture = 0;
	traceDump = 0;
	warn = 0;
	warnCapture = 0;
	warnDump = 0;


	return *this;
}

LogSettings& LogSettings::checkSize()
{
	EnEx ee(FL, "LogSettings::checkSize()");

	LogFile.check_size();
	LogFile.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
LogSettings::LogSettings(xmlNodePtr node)
{
	EnEx ee(FL, "LogSettings::LogSettings(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
LogSettings& LogSettings::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "LogSettings::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct LogSettings is NULL.");
	}

	BufferSize = XmlHelpers::getIntAttr(node, "BufferSize");
	LogFile.getAttribute(node, "LogFile");
	MaxSize = XmlHelpers::getIntAttr(node, "MaxSize");
	debug = XmlHelpers::getIntAttr(node, "debug");
	debugCapture = XmlHelpers::getIntAttr(node, "debugCapture");
	debugDump = XmlHelpers::getIntAttr(node, "debugDump");
	error = XmlHelpers::getIntAttr(node, "error");
	errorCapture = XmlHelpers::getIntAttr(node, "errorCapture");
	errorDump = XmlHelpers::getIntAttr(node, "errorDump");
	info = XmlHelpers::getIntAttr(node, "info");
	infoCapture = XmlHelpers::getIntAttr(node, "infoCapture");
	infoDump = XmlHelpers::getIntAttr(node, "infoDump");
	panic = XmlHelpers::getIntAttr(node, "panic");
	panicCapture = XmlHelpers::getIntAttr(node, "panicCapture");
	panicDump = XmlHelpers::getIntAttr(node, "panicDump");
	sql = XmlHelpers::getIntAttr(node, "sql");
	sqlCapture = XmlHelpers::getIntAttr(node, "sqlCapture");
	sqlDump = XmlHelpers::getIntAttr(node, "sqlDump");
	trace = XmlHelpers::getIntAttr(node, "trace");
	traceCapture = XmlHelpers::getIntAttr(node, "traceCapture");
	traceDump = XmlHelpers::getIntAttr(node, "traceDump");
	warn = XmlHelpers::getIntAttr(node, "warn");
	warnCapture = XmlHelpers::getIntAttr(node, "warnCapture");
	warnDump = XmlHelpers::getIntAttr(node, "warnDump");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr LogSettings::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "LogSettings::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogSettings::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"LogSettings", NULL);
	XmlHelpers::setIntAttr(child, "BufferSize", BufferSize);
	xmlSetProp(child, (const xmlChar*)"LogFile", LogFile);
	XmlHelpers::setIntAttr(child, "MaxSize", MaxSize);
	XmlHelpers::setIntAttr(child, "debug", debug);
	XmlHelpers::setIntAttr(child, "debugCapture", debugCapture);
	XmlHelpers::setIntAttr(child, "debugDump", debugDump);
	XmlHelpers::setIntAttr(child, "error", error);
	XmlHelpers::setIntAttr(child, "errorCapture", errorCapture);
	XmlHelpers::setIntAttr(child, "errorDump", errorDump);
	XmlHelpers::setIntAttr(child, "info", info);
	XmlHelpers::setIntAttr(child, "infoCapture", infoCapture);
	XmlHelpers::setIntAttr(child, "infoDump", infoDump);
	XmlHelpers::setIntAttr(child, "panic", panic);
	XmlHelpers::setIntAttr(child, "panicCapture", panicCapture);
	XmlHelpers::setIntAttr(child, "panicDump", panicDump);
	XmlHelpers::setIntAttr(child, "sql", sql);
	XmlHelpers::setIntAttr(child, "sqlCapture", sqlCapture);
	XmlHelpers::setIntAttr(child, "sqlDump", sqlDump);
	XmlHelpers::setIntAttr(child, "trace", trace);
	XmlHelpers::setIntAttr(child, "traceCapture", traceCapture);
	XmlHelpers::setIntAttr(child, "traceDump", traceDump);
	XmlHelpers::setIntAttr(child, "warn", warn);
	XmlHelpers::setIntAttr(child, "warnCapture", warnCapture);
	XmlHelpers::setIntAttr(child, "warnDump", warnDump);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr LogSettings::createXmlDoc() const
{
	EnEx ee(FL, "LogSettings::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"LogSettings", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	XmlHelpers::setIntAttr(child, "BufferSize", BufferSize);
	xmlSetProp(child, (const xmlChar*)"LogFile", LogFile);
	XmlHelpers::setIntAttr(child, "MaxSize", MaxSize);
	XmlHelpers::setIntAttr(child, "debug", debug);
	XmlHelpers::setIntAttr(child, "debugCapture", debugCapture);
	XmlHelpers::setIntAttr(child, "debugDump", debugDump);
	XmlHelpers::setIntAttr(child, "error", error);
	XmlHelpers::setIntAttr(child, "errorCapture", errorCapture);
	XmlHelpers::setIntAttr(child, "errorDump", errorDump);
	XmlHelpers::setIntAttr(child, "info", info);
	XmlHelpers::setIntAttr(child, "infoCapture", infoCapture);
	XmlHelpers::setIntAttr(child, "infoDump", infoDump);
	XmlHelpers::setIntAttr(child, "panic", panic);
	XmlHelpers::setIntAttr(child, "panicCapture", panicCapture);
	XmlHelpers::setIntAttr(child, "panicDump", panicDump);
	XmlHelpers::setIntAttr(child, "sql", sql);
	XmlHelpers::setIntAttr(child, "sqlCapture", sqlCapture);
	XmlHelpers::setIntAttr(child, "sqlDump", sqlDump);
	XmlHelpers::setIntAttr(child, "trace", trace);
	XmlHelpers::setIntAttr(child, "traceCapture", traceCapture);
	XmlHelpers::setIntAttr(child, "traceDump", traceDump);
	XmlHelpers::setIntAttr(child, "warn", warn);
	XmlHelpers::setIntAttr(child, "warnCapture", warnCapture);
	XmlHelpers::setIntAttr(child, "warnDump", warnDump);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<LogSettings* >* LogSettings::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "LogSettings::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogSettings::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<LogSettings* >, LogSettings::deleteVector> ret = new vector<LogSettings* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "LogSettings") == 0){
			ret->push_back( new LogSettings(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void LogSettings::createXmlChildren(xmlNodePtr parent, vector<LogSettings* >* vect)
{
	EnEx ee(FL, "LogSettings::createXmlChildren(xmlNodePtr parent, vector<LogSettings* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogSettings::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr LogSettings::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogSettings* >* vect)
{
	EnEx ee(FL, "LogSettings::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogSettings* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogSettings::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	LogSettings::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void LogSettings::deleteVector(vector<LogSettings* >* vect)
{
	EnEx ee(FL, "LogSettings::deleteVector(vector<LogSettings* >* vect)");

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
twine& LogSettings::Name()
{
	return LogSettingsName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This statement is merely here to define the data structure that is
			passed back and forth to specify log file settings.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Nothing here
		 */
/*                                                                                        */
/* ************************************************************************************** */
void LogSettings::unusedSqlStmt(OdbcObj& odbc, LogSettings& obj )
{
	EnEx ee(FL, "LogSettings::unusedSqlStmt()");

	twine stmt = "-- Nothing here";

	LogSettings::unusedSqlStmt(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void LogSettings::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, LogSettings& obj )
{
	EnEx ee(FL, "LogSettings::unusedSqlStmt()");

	Timer selectTimer;

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into LogSettings::unusedSqlStmt is not connected.");
	}

	int sizeof_int = sizeof(intptr_t); // so that we can have an address of this variable
	// sizeof_float not required.

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	selectTimer.Start();
	{ // Used for scope for the timing object.
		EnEx eeExe("LogSettings::unusedSqlStmt()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.LogFile() );
			odbc.BindInput(1, obj.LogFile);
			DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.MaxSize );
			odbc.BindInput(2, &(obj.MaxSize), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.BufferSize );
			odbc.BindInput(3, &(obj.BufferSize), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.panic );
			odbc.BindInput(4, &(obj.panic), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.panicCapture );
			odbc.BindInput(5, &(obj.panicCapture), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 6, obj.panicDump );
			odbc.BindInput(6, &(obj.panicDump), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 7, obj.error );
			odbc.BindInput(7, &(obj.error), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 8, obj.errorCapture );
			odbc.BindInput(8, &(obj.errorCapture), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 9, obj.errorDump );
			odbc.BindInput(9, &(obj.errorDump), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 10, obj.warn );
			odbc.BindInput(10, &(obj.warn), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 11, obj.warnCapture );
			odbc.BindInput(11, &(obj.warnCapture), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 12, obj.warnDump );
			odbc.BindInput(12, &(obj.warnDump), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 13, obj.info );
			odbc.BindInput(13, &(obj.info), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 14, obj.infoCapture );
			odbc.BindInput(14, &(obj.infoCapture), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 15, obj.infoDump );
			odbc.BindInput(15, &(obj.infoDump), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 16, obj.debug );
			odbc.BindInput(16, &(obj.debug), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 17, obj.debugCapture );
			odbc.BindInput(17, &(obj.debugCapture), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 18, obj.debugDump );
			odbc.BindInput(18, &(obj.debugDump), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 19, obj.trace );
			odbc.BindInput(19, &(obj.trace), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 20, obj.traceCapture );
			odbc.BindInput(20, &(obj.traceCapture), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 21, obj.traceDump );
			odbc.BindInput(21, &(obj.traceDump), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 22, obj.sql );
			odbc.BindInput(22, &(obj.sql), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 23, obj.sqlCapture );
			odbc.BindInput(23, &(obj.sqlCapture), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 24, obj.sqlDump );
			odbc.BindInput(24, &(obj.sqlDump), &sizeof_int, DB_INT);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for LogSettings::unusedSqlStmt");
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
twine LogSettings::unusedSqlStmt_prepSQL(IOConn& ioc, LogSettings& obj )
{
	EnEx ee(FL, "LogSettings::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here";

	// Replace the LogFile parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.LogFile );
	}

	// Replace the MaxSize parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.MaxSize;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the BufferSize parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.BufferSize;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the panic parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.panic;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the panicCapture parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.panicCapture;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the panicDump parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.panicDump;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the error parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.error;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the errorCapture parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.errorCapture;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the errorDump parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.errorDump;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the warn parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.warn;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the warnCapture parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.warnCapture;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the warnDump parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.warnDump;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the info parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.info;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the infoCapture parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.infoCapture;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the infoDump parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.infoDump;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the debug parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.debug;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the debugCapture parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.debugCapture;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the debugDump parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.debugDump;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the trace parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.trace;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the traceCapture parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.traceCapture;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the traceDump parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.traceDump;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the sql parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.sql;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the sqlCapture parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.sqlCapture;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the sqlDump parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.sqlDump;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

