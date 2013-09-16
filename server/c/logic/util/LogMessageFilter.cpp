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

#include "LogMessageFilter.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/util/LogMessageFilter.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine LogMessageFilterName = "LogMessageFilter";

LogMessageFilter::LogMessageFilter()
{
	EnEx ee(FL, "LogMessageFilter::LogMessageFilter()");

	init();

}

LogMessageFilter::LogMessageFilter(const LogMessageFilter& c)
{
	EnEx ee(FL, "LogMessageFilter::LogMessageFilter(const LogMessageFilter& c)");

	AppName = c.AppName;
	Debug = c.Debug;
	DispApp = c.DispApp;
	DispChannel = c.DispChannel;
	DispDate = c.DispDate;
	DispFile = c.DispFile;
	DispId = c.DispId;
	DispLine = c.DispLine;
	DispMachine = c.DispMachine;
	DispThread = c.DispThread;
	Error = c.Error;
	FilterMatchCount = c.FilterMatchCount;
	FindByDate = c.FindByDate;
	FindByID = c.FindByID;
	FindByMsg = c.FindByMsg;
	FirstRow = c.FirstRow;
	Forward = c.Forward;
	GetMax = c.GetMax;
	Info = c.Info;
	LastRow = c.LastRow;
	LogFile = c.LogFile;
	LogFileNewestID = c.LogFileNewestID;
	LogFileOldestID = c.LogFileOldestID;
	MachineName = c.MachineName;
	Message = c.Message;
	Panic = c.Panic;
	SUID = c.SUID;
	ShowColApplication = c.ShowColApplication;
	ShowColChannel = c.ShowColChannel;
	ShowColDate = c.ShowColDate;
	ShowColFile = c.ShowColFile;
	ShowColID = c.ShowColID;
	ShowColIcon = c.ShowColIcon;
	ShowColLine = c.ShowColLine;
	ShowColMachine = c.ShowColMachine;
	ShowColMessage = c.ShowColMessage;
	ShowColSUID = c.ShowColSUID;
	ShowColThread = c.ShowColThread;
	SqlTrace = c.SqlTrace;
	StartId = c.StartId;
	ThreadID = c.ThreadID;
	Trace = c.Trace;
	Warn = c.Warn;


}

LogMessageFilter& LogMessageFilter::operator=(const LogMessageFilter& c)
{
	EnEx ee(FL, "LogMessageFilter::operator=(const LogMessageFilter& c)");

	AppName = c.AppName;
	Debug = c.Debug;
	DispApp = c.DispApp;
	DispChannel = c.DispChannel;
	DispDate = c.DispDate;
	DispFile = c.DispFile;
	DispId = c.DispId;
	DispLine = c.DispLine;
	DispMachine = c.DispMachine;
	DispThread = c.DispThread;
	Error = c.Error;
	FilterMatchCount = c.FilterMatchCount;
	FindByDate = c.FindByDate;
	FindByID = c.FindByID;
	FindByMsg = c.FindByMsg;
	FirstRow = c.FirstRow;
	Forward = c.Forward;
	GetMax = c.GetMax;
	Info = c.Info;
	LastRow = c.LastRow;
	LogFile = c.LogFile;
	LogFileNewestID = c.LogFileNewestID;
	LogFileOldestID = c.LogFileOldestID;
	MachineName = c.MachineName;
	Message = c.Message;
	Panic = c.Panic;
	SUID = c.SUID;
	ShowColApplication = c.ShowColApplication;
	ShowColChannel = c.ShowColChannel;
	ShowColDate = c.ShowColDate;
	ShowColFile = c.ShowColFile;
	ShowColID = c.ShowColID;
	ShowColIcon = c.ShowColIcon;
	ShowColLine = c.ShowColLine;
	ShowColMachine = c.ShowColMachine;
	ShowColMessage = c.ShowColMessage;
	ShowColSUID = c.ShowColSUID;
	ShowColThread = c.ShowColThread;
	SqlTrace = c.SqlTrace;
	StartId = c.StartId;
	ThreadID = c.ThreadID;
	Trace = c.Trace;
	Warn = c.Warn;


	return *this;
}

LogMessageFilter::~LogMessageFilter()
{
	EnEx ee(FL, "LogMessageFilter::~LogMessageFilter()");

}

LogMessageFilter& LogMessageFilter::init()
{
	EnEx ee(FL, "LogMessageFilter::init()");

	AppName.erase();
	Debug = 0;
	DispApp = 0;
	DispChannel = 0;
	DispDate = 0;
	DispFile = 0;
	DispId = 0;
	DispLine = 0;
	DispMachine = 0;
	DispThread = 0;
	Error = 0;
	FilterMatchCount = 0;
	FindByDate.erase();
	FindByID = 0;
	FindByMsg.erase();
	FirstRow = 0;
	Forward = 0;
	GetMax = 0;
	Info = 0;
	LastRow = 0;
	LogFile.erase();
	LogFileNewestID = 0;
	LogFileOldestID = 0;
	MachineName.erase();
	Message.erase();
	Panic = 0;
	SUID.erase();
	ShowColApplication = 0;
	ShowColChannel = 0;
	ShowColDate = 0;
	ShowColFile = 0;
	ShowColID = 0;
	ShowColIcon = 0;
	ShowColLine = 0;
	ShowColMachine = 0;
	ShowColMessage = 0;
	ShowColSUID = 0;
	ShowColThread = 0;
	SqlTrace = 0;
	StartId = 0;
	ThreadID = 0;
	Trace = 0;
	Warn = 0;


	return *this;
}

LogMessageFilter& LogMessageFilter::checkSize()
{
	EnEx ee(FL, "LogMessageFilter::checkSize()");

	AppName.check_size();
	AppName.rtrim();
	FindByDate.check_size();
	FindByDate.rtrim();
	FindByMsg.check_size();
	FindByMsg.rtrim();
	LogFile.check_size();
	LogFile.rtrim();
	MachineName.check_size();
	MachineName.rtrim();
	Message.check_size();
	Message.rtrim();
	SUID.check_size();
	SUID.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
LogMessageFilter::LogMessageFilter(xmlNodePtr node)
{
	EnEx ee(FL, "LogMessageFilter::LogMessageFilter(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
LogMessageFilter& LogMessageFilter::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "LogMessageFilter::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct LogMessageFilter is NULL.");
	}

	AppName.getAttribute(node, "AppName");
	Debug = XmlHelpers::getIntAttr(node, "Debug");
	DispApp = XmlHelpers::getIntAttr(node, "DispApp");
	DispChannel = XmlHelpers::getIntAttr(node, "DispChannel");
	DispDate = XmlHelpers::getIntAttr(node, "DispDate");
	DispFile = XmlHelpers::getIntAttr(node, "DispFile");
	DispId = XmlHelpers::getIntAttr(node, "DispId");
	DispLine = XmlHelpers::getIntAttr(node, "DispLine");
	DispMachine = XmlHelpers::getIntAttr(node, "DispMachine");
	DispThread = XmlHelpers::getIntAttr(node, "DispThread");
	Error = XmlHelpers::getIntAttr(node, "Error");
	FilterMatchCount = XmlHelpers::getIntAttr(node, "FilterMatchCount");
	FindByDate.getAttribute(node, "FindByDate");
	FindByID = XmlHelpers::getIntAttr(node, "FindByID");
	FindByMsg.getAttribute(node, "FindByMsg");
	FirstRow = XmlHelpers::getIntAttr(node, "FirstRow");
	Forward = XmlHelpers::getIntAttr(node, "Forward");
	GetMax = XmlHelpers::getIntAttr(node, "GetMax");
	Info = XmlHelpers::getIntAttr(node, "Info");
	LastRow = XmlHelpers::getIntAttr(node, "LastRow");
	LogFile.getAttribute(node, "LogFile");
	LogFileNewestID = XmlHelpers::getIntAttr(node, "LogFileNewestID");
	LogFileOldestID = XmlHelpers::getIntAttr(node, "LogFileOldestID");
	MachineName.getAttribute(node, "MachineName");
	Message.getAttribute(node, "Message");
	Panic = XmlHelpers::getIntAttr(node, "Panic");
	SUID.getAttribute(node, "SUID");
	ShowColApplication = XmlHelpers::getIntAttr(node, "ShowColApplication");
	ShowColChannel = XmlHelpers::getIntAttr(node, "ShowColChannel");
	ShowColDate = XmlHelpers::getIntAttr(node, "ShowColDate");
	ShowColFile = XmlHelpers::getIntAttr(node, "ShowColFile");
	ShowColID = XmlHelpers::getIntAttr(node, "ShowColID");
	ShowColIcon = XmlHelpers::getIntAttr(node, "ShowColIcon");
	ShowColLine = XmlHelpers::getIntAttr(node, "ShowColLine");
	ShowColMachine = XmlHelpers::getIntAttr(node, "ShowColMachine");
	ShowColMessage = XmlHelpers::getIntAttr(node, "ShowColMessage");
	ShowColSUID = XmlHelpers::getIntAttr(node, "ShowColSUID");
	ShowColThread = XmlHelpers::getIntAttr(node, "ShowColThread");
	SqlTrace = XmlHelpers::getIntAttr(node, "SqlTrace");
	StartId = XmlHelpers::getIntAttr(node, "StartId");
	ThreadID = XmlHelpers::getIntAttr(node, "ThreadID");
	Trace = XmlHelpers::getIntAttr(node, "Trace");
	Warn = XmlHelpers::getIntAttr(node, "Warn");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr LogMessageFilter::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "LogMessageFilter::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogMessageFilter::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"LogMessageFilter", NULL);
	xmlSetProp(child, (const xmlChar*)"AppName", AppName);
	XmlHelpers::setIntAttr(child, "Debug", Debug);
	XmlHelpers::setIntAttr(child, "DispApp", DispApp);
	XmlHelpers::setIntAttr(child, "DispChannel", DispChannel);
	XmlHelpers::setIntAttr(child, "DispDate", DispDate);
	XmlHelpers::setIntAttr(child, "DispFile", DispFile);
	XmlHelpers::setIntAttr(child, "DispId", DispId);
	XmlHelpers::setIntAttr(child, "DispLine", DispLine);
	XmlHelpers::setIntAttr(child, "DispMachine", DispMachine);
	XmlHelpers::setIntAttr(child, "DispThread", DispThread);
	XmlHelpers::setIntAttr(child, "Error", Error);
	XmlHelpers::setIntAttr(child, "FilterMatchCount", FilterMatchCount);
	xmlSetProp(child, (const xmlChar*)"FindByDate", FindByDate);
	XmlHelpers::setIntAttr(child, "FindByID", FindByID);
	xmlSetProp(child, (const xmlChar*)"FindByMsg", FindByMsg);
	XmlHelpers::setIntAttr(child, "FirstRow", FirstRow);
	XmlHelpers::setIntAttr(child, "Forward", Forward);
	XmlHelpers::setIntAttr(child, "GetMax", GetMax);
	XmlHelpers::setIntAttr(child, "Info", Info);
	XmlHelpers::setIntAttr(child, "LastRow", LastRow);
	xmlSetProp(child, (const xmlChar*)"LogFile", LogFile);
	XmlHelpers::setIntAttr(child, "LogFileNewestID", LogFileNewestID);
	XmlHelpers::setIntAttr(child, "LogFileOldestID", LogFileOldestID);
	xmlSetProp(child, (const xmlChar*)"MachineName", MachineName);
	xmlSetProp(child, (const xmlChar*)"Message", Message);
	XmlHelpers::setIntAttr(child, "Panic", Panic);
	xmlSetProp(child, (const xmlChar*)"SUID", SUID);
	XmlHelpers::setIntAttr(child, "ShowColApplication", ShowColApplication);
	XmlHelpers::setIntAttr(child, "ShowColChannel", ShowColChannel);
	XmlHelpers::setIntAttr(child, "ShowColDate", ShowColDate);
	XmlHelpers::setIntAttr(child, "ShowColFile", ShowColFile);
	XmlHelpers::setIntAttr(child, "ShowColID", ShowColID);
	XmlHelpers::setIntAttr(child, "ShowColIcon", ShowColIcon);
	XmlHelpers::setIntAttr(child, "ShowColLine", ShowColLine);
	XmlHelpers::setIntAttr(child, "ShowColMachine", ShowColMachine);
	XmlHelpers::setIntAttr(child, "ShowColMessage", ShowColMessage);
	XmlHelpers::setIntAttr(child, "ShowColSUID", ShowColSUID);
	XmlHelpers::setIntAttr(child, "ShowColThread", ShowColThread);
	XmlHelpers::setIntAttr(child, "SqlTrace", SqlTrace);
	XmlHelpers::setIntAttr(child, "StartId", StartId);
	XmlHelpers::setIntAttr(child, "ThreadID", ThreadID);
	XmlHelpers::setIntAttr(child, "Trace", Trace);
	XmlHelpers::setIntAttr(child, "Warn", Warn);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr LogMessageFilter::createXmlDoc() const
{
	EnEx ee(FL, "LogMessageFilter::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"LogMessageFilter", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"AppName", AppName);
	XmlHelpers::setIntAttr(child, "Debug", Debug);
	XmlHelpers::setIntAttr(child, "DispApp", DispApp);
	XmlHelpers::setIntAttr(child, "DispChannel", DispChannel);
	XmlHelpers::setIntAttr(child, "DispDate", DispDate);
	XmlHelpers::setIntAttr(child, "DispFile", DispFile);
	XmlHelpers::setIntAttr(child, "DispId", DispId);
	XmlHelpers::setIntAttr(child, "DispLine", DispLine);
	XmlHelpers::setIntAttr(child, "DispMachine", DispMachine);
	XmlHelpers::setIntAttr(child, "DispThread", DispThread);
	XmlHelpers::setIntAttr(child, "Error", Error);
	XmlHelpers::setIntAttr(child, "FilterMatchCount", FilterMatchCount);
	xmlSetProp(child, (const xmlChar*)"FindByDate", FindByDate);
	XmlHelpers::setIntAttr(child, "FindByID", FindByID);
	xmlSetProp(child, (const xmlChar*)"FindByMsg", FindByMsg);
	XmlHelpers::setIntAttr(child, "FirstRow", FirstRow);
	XmlHelpers::setIntAttr(child, "Forward", Forward);
	XmlHelpers::setIntAttr(child, "GetMax", GetMax);
	XmlHelpers::setIntAttr(child, "Info", Info);
	XmlHelpers::setIntAttr(child, "LastRow", LastRow);
	xmlSetProp(child, (const xmlChar*)"LogFile", LogFile);
	XmlHelpers::setIntAttr(child, "LogFileNewestID", LogFileNewestID);
	XmlHelpers::setIntAttr(child, "LogFileOldestID", LogFileOldestID);
	xmlSetProp(child, (const xmlChar*)"MachineName", MachineName);
	xmlSetProp(child, (const xmlChar*)"Message", Message);
	XmlHelpers::setIntAttr(child, "Panic", Panic);
	xmlSetProp(child, (const xmlChar*)"SUID", SUID);
	XmlHelpers::setIntAttr(child, "ShowColApplication", ShowColApplication);
	XmlHelpers::setIntAttr(child, "ShowColChannel", ShowColChannel);
	XmlHelpers::setIntAttr(child, "ShowColDate", ShowColDate);
	XmlHelpers::setIntAttr(child, "ShowColFile", ShowColFile);
	XmlHelpers::setIntAttr(child, "ShowColID", ShowColID);
	XmlHelpers::setIntAttr(child, "ShowColIcon", ShowColIcon);
	XmlHelpers::setIntAttr(child, "ShowColLine", ShowColLine);
	XmlHelpers::setIntAttr(child, "ShowColMachine", ShowColMachine);
	XmlHelpers::setIntAttr(child, "ShowColMessage", ShowColMessage);
	XmlHelpers::setIntAttr(child, "ShowColSUID", ShowColSUID);
	XmlHelpers::setIntAttr(child, "ShowColThread", ShowColThread);
	XmlHelpers::setIntAttr(child, "SqlTrace", SqlTrace);
	XmlHelpers::setIntAttr(child, "StartId", StartId);
	XmlHelpers::setIntAttr(child, "ThreadID", ThreadID);
	XmlHelpers::setIntAttr(child, "Trace", Trace);
	XmlHelpers::setIntAttr(child, "Warn", Warn);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<LogMessageFilter* >* LogMessageFilter::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "LogMessageFilter::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogMessageFilter::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<LogMessageFilter* >, LogMessageFilter::deleteVector> ret = new vector<LogMessageFilter* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "LogMessageFilter") == 0){
			ret->push_back( new LogMessageFilter(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void LogMessageFilter::createXmlChildren(xmlNodePtr parent, vector<LogMessageFilter* >* vect)
{
	EnEx ee(FL, "LogMessageFilter::createXmlChildren(xmlNodePtr parent, vector<LogMessageFilter* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LogMessageFilter::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void LogMessageFilter::deleteVector(vector<LogMessageFilter* >* vect)
{
	EnEx ee(FL, "LogMessageFilter::deleteVector(vector<LogMessageFilter* >* vect)");

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
twine& LogMessageFilter::Name()
{
	return LogMessageFilterName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This statement is merely here to define the data structure that is
			passed back and forth to determine log filtering settings.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Nothing here
		 */
/*                                                                                        */
/* ************************************************************************************** */
void LogMessageFilter::unusedSqlStmt(OdbcObj& odbc, LogMessageFilter& obj )
{
	EnEx ee(FL, "LogMessageFilter::unusedSqlStmt()");

	twine stmt = "-- Nothing here";

	LogMessageFilter::unusedSqlStmt(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void LogMessageFilter::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, LogMessageFilter& obj )
{
	EnEx ee(FL, "LogMessageFilter::unusedSqlStmt()");

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into LogMessageFilter::unusedSqlStmt is not connected.");
	}

	int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
	int sizeof_float = sizeof(float);      // so that we can have an address of this variable

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	{ // Used for scope for the timing object.
		EnEx eeExe("LogMessageFilter::unusedSqlStmt()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.LogFile() );
			odbc.BindInput(1, obj.LogFile);
			DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.StartId );
			odbc.BindInput(2, &(obj.StartId), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.Forward );
			odbc.BindInput(3, &(obj.Forward), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.GetMax );
			odbc.BindInput(4, &(obj.GetMax), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 5, obj.MachineName() );
			odbc.BindInput(5, obj.MachineName);
			DEBUG(FL, "Setting input (%d) to value: %s", 6, obj.AppName() );
			odbc.BindInput(6, obj.AppName);
			DEBUG(FL, "Setting input (%d) to value: %d", 7, obj.ThreadID );
			odbc.BindInput(7, &(obj.ThreadID), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 8, obj.SUID() );
			odbc.BindInput(8, obj.SUID);
			DEBUG(FL, "Setting input (%d) to value: %s", 9, obj.Message() );
			odbc.BindInput(9, obj.Message);
			DEBUG(FL, "Setting input (%d) to value: %d", 10, obj.Panic );
			odbc.BindInput(10, &(obj.Panic), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 11, obj.Error );
			odbc.BindInput(11, &(obj.Error), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 12, obj.Warn );
			odbc.BindInput(12, &(obj.Warn), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 13, obj.Info );
			odbc.BindInput(13, &(obj.Info), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 14, obj.Debug );
			odbc.BindInput(14, &(obj.Debug), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 15, obj.Trace );
			odbc.BindInput(15, &(obj.Trace), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 16, obj.SqlTrace );
			odbc.BindInput(16, &(obj.SqlTrace), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 17, obj.DispId );
			odbc.BindInput(17, &(obj.DispId), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 18, obj.DispDate );
			odbc.BindInput(18, &(obj.DispDate), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 19, obj.DispMachine );
			odbc.BindInput(19, &(obj.DispMachine), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 20, obj.DispApp );
			odbc.BindInput(20, &(obj.DispApp), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 21, obj.DispThread );
			odbc.BindInput(21, &(obj.DispThread), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 22, obj.DispFile );
			odbc.BindInput(22, &(obj.DispFile), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 23, obj.DispLine );
			odbc.BindInput(23, &(obj.DispLine), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 24, obj.DispChannel );
			odbc.BindInput(24, &(obj.DispChannel), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 25, obj.ShowColIcon );
			odbc.BindInput(25, &(obj.ShowColIcon), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 26, obj.ShowColID );
			odbc.BindInput(26, &(obj.ShowColID), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 27, obj.ShowColDate );
			odbc.BindInput(27, &(obj.ShowColDate), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 28, obj.ShowColMachine );
			odbc.BindInput(28, &(obj.ShowColMachine), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 29, obj.ShowColApplication );
			odbc.BindInput(29, &(obj.ShowColApplication), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 30, obj.ShowColThread );
			odbc.BindInput(30, &(obj.ShowColThread), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 31, obj.ShowColSUID );
			odbc.BindInput(31, &(obj.ShowColSUID), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 32, obj.ShowColFile );
			odbc.BindInput(32, &(obj.ShowColFile), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 33, obj.ShowColLine );
			odbc.BindInput(33, &(obj.ShowColLine), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 34, obj.ShowColChannel );
			odbc.BindInput(34, &(obj.ShowColChannel), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 35, obj.ShowColMessage );
			odbc.BindInput(35, &(obj.ShowColMessage), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 36, obj.FirstRow );
			odbc.BindInput(36, &(obj.FirstRow), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 37, obj.LastRow );
			odbc.BindInput(37, &(obj.LastRow), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 38, obj.LogFileOldestID );
			odbc.BindInput(38, &(obj.LogFileOldestID), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 39, obj.LogFileNewestID );
			odbc.BindInput(39, &(obj.LogFileNewestID), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 40, obj.FilterMatchCount );
			odbc.BindInput(40, &(obj.FilterMatchCount), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 41, obj.FindByID );
			odbc.BindInput(41, &(obj.FindByID), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 42, obj.FindByDate() );
			odbc.BindInput(42, obj.FindByDate);
			DEBUG(FL, "Setting input (%d) to value: %s", 43, obj.FindByMsg() );
			odbc.BindInput(43, obj.FindByMsg);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for LogMessageFilter::unusedSqlStmt");
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
twine LogMessageFilter::unusedSqlStmt_prepSQL(IOConn& ioc, LogMessageFilter& obj )
{
	EnEx ee(FL, "LogMessageFilter::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here";

	// Replace the LogFile parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.LogFile );
	}

	// Replace the StartId parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.StartId;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Forward parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Forward;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the GetMax parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.GetMax;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the MachineName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.MachineName );
	}

	// Replace the AppName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.AppName );
	}

	// Replace the ThreadID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ThreadID;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the SUID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.SUID );
	}

	// Replace the Message parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Message );
	}

	// Replace the Panic parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Panic;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Error parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Error;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Warn parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Warn;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Info parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Info;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Debug parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Debug;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Trace parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Trace;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the SqlTrace parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.SqlTrace;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispId parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispId;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispDate parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispDate;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispMachine parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispMachine;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispApp parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispApp;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispThread parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispThread;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispFile parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispFile;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispLine parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispLine;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the DispChannel parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DispChannel;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColIcon parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColIcon;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColID;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColDate parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColDate;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColMachine parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColMachine;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColApplication parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColApplication;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColThread parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColThread;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColSUID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColSUID;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColFile parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColFile;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColLine parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColLine;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColChannel parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColChannel;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ShowColMessage parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.ShowColMessage;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the FirstRow parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.FirstRow;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the LastRow parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.LastRow;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the LogFileOldestID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.LogFileOldestID;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the LogFileNewestID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.LogFileNewestID;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the FilterMatchCount parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.FilterMatchCount;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the FindByID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.FindByID;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the FindByDate parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.FindByDate );
	}

	// Replace the FindByMsg parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.FindByMsg );
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

