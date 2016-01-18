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

#include "LRTask.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/util/LRTask.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine LRTaskName = "LRTask";

LRTask::LRTask()
{
	EnEx ee(FL, "LRTask::LRTask()");

	init();

}

LRTask::LRTask(const LRTask& c)
{
	EnEx ee(FL, "LRTask::LRTask(const LRTask& c)");

	TaskCurrent = c.TaskCurrent;
	TaskFinish = c.TaskFinish;
	TaskID = c.TaskID;
	TaskMsg = c.TaskMsg;
	TaskName = c.TaskName;
	TaskResponse = c.TaskResponse;
	TaskStart = c.TaskStart;


}

LRTask& LRTask::operator=(const LRTask& c)
{
	EnEx ee(FL, "LRTask::operator=(const LRTask& c)");

	TaskCurrent = c.TaskCurrent;
	TaskFinish = c.TaskFinish;
	TaskID = c.TaskID;
	TaskMsg = c.TaskMsg;
	TaskName = c.TaskName;
	TaskResponse = c.TaskResponse;
	TaskStart = c.TaskStart;


	return *this;
}

LRTask::~LRTask()
{
	EnEx ee(FL, "LRTask::~LRTask()");

}

LRTask& LRTask::init()
{
	EnEx ee(FL, "LRTask::init()");

	TaskCurrent = 0;
	TaskFinish = 0;
	TaskID.erase();
	TaskMsg.erase();
	TaskName.erase();
	TaskResponse.erase();
	TaskStart = 0;


	return *this;
}

LRTask& LRTask::checkSize()
{
	EnEx ee(FL, "LRTask::checkSize()");

	TaskID.check_size();
	TaskID.rtrim();
	TaskMsg.check_size();
	TaskMsg.rtrim();
	TaskName.check_size();
	TaskName.rtrim();
	TaskResponse.check_size();
	TaskResponse.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
LRTask::LRTask(xmlNodePtr node)
{
	EnEx ee(FL, "LRTask::LRTask(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
LRTask& LRTask::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "LRTask::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct LRTask is NULL.");
	}

	TaskCurrent = XmlHelpers::getIntAttr(node, "TaskCurrent");
	TaskFinish = XmlHelpers::getIntAttr(node, "TaskFinish");
	TaskID.getAttribute(node, "TaskID");
	TaskMsg.getAttribute(node, "TaskMsg");
	TaskName.getAttribute(node, "TaskName");
	xmlNodePtr TaskResponse_child = XmlHelpers::FindChild(node, "TaskResponse"); if( TaskResponse_child != NULL) TaskResponse = XmlHelpers::getBase64(TaskResponse_child);
	TaskStart = XmlHelpers::getIntAttr(node, "TaskStart");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr LRTask::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "LRTask::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LRTask::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"LRTask", NULL);
	XmlHelpers::setIntAttr(child, "TaskCurrent", TaskCurrent);
	XmlHelpers::setIntAttr(child, "TaskFinish", TaskFinish);
	xmlSetProp(child, (const xmlChar*)"TaskID", TaskID);
	xmlSetProp(child, (const xmlChar*)"TaskMsg", TaskMsg);
	xmlSetProp(child, (const xmlChar*)"TaskName", TaskName);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"TaskResponse", NULL), TaskResponse);
	XmlHelpers::setIntAttr(child, "TaskStart", TaskStart);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr LRTask::createXmlDoc() const
{
	EnEx ee(FL, "LRTask::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"LRTask", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	XmlHelpers::setIntAttr(child, "TaskCurrent", TaskCurrent);
	XmlHelpers::setIntAttr(child, "TaskFinish", TaskFinish);
	xmlSetProp(child, (const xmlChar*)"TaskID", TaskID);
	xmlSetProp(child, (const xmlChar*)"TaskMsg", TaskMsg);
	xmlSetProp(child, (const xmlChar*)"TaskName", TaskName);
	XmlHelpers::setBase64(xmlNewChild(child, NULL, (const xmlChar*)"TaskResponse", NULL), TaskResponse);
	XmlHelpers::setIntAttr(child, "TaskStart", TaskStart);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<LRTask* >* LRTask::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "LRTask::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LRTask::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<LRTask* >, LRTask::deleteVector> ret = new vector<LRTask* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "LRTask") == 0){
			ret->push_back( new LRTask(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void LRTask::createXmlChildren(xmlNodePtr parent, vector<LRTask* >* vect)
{
	EnEx ee(FL, "LRTask::createXmlChildren(xmlNodePtr parent, vector<LRTask* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LRTask::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr LRTask::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LRTask* >* vect)
{
	EnEx ee(FL, "LRTask::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LRTask* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to LRTask::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	LRTask::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void LRTask::deleteVector(vector<LRTask* >* vect)
{
	EnEx ee(FL, "LRTask::deleteVector(vector<LRTask* >* vect)");

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
twine& LRTask::Name()
{
	return LRTaskName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This statement is merely here to define the data structure that is
			passed back and forth to request state of Long running tasks.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			-- Nothing here
		 */
/*                                                                                        */
/* ************************************************************************************** */
void LRTask::unusedSqlStmt(OdbcObj& odbc, LRTask& obj )
{
	EnEx ee(FL, "LRTask::unusedSqlStmt()");

	twine stmt = "-- Nothing here";

	LRTask::unusedSqlStmt(odbc, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void LRTask::unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, LRTask& obj )
{
	EnEx ee(FL, "LRTask::unusedSqlStmt()");

	Timer selectTimer;

	if(odbc.isConnected() == 0){
		throw AnException(0, FL, "OdbcObj passed into LRTask::unusedSqlStmt is not connected.");
	}

	int sizeof_int = sizeof(intptr_t); // so that we can have an address of this variable
	// sizeof_float not required.

	SQLTRACE(FL, "Using SQL: %s", stmt() );
	odbc.SetStmt(stmt, SQL_TYPE_UPDATE);

	selectTimer.Start();
	{ // Used for scope for the timing object.
		EnEx eeExe("LRTask::unusedSqlStmt()-BindExecStmt");

		// Bind the inputs
		if(useInputs){
			DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.TaskID() );
			odbc.BindInput(1, obj.TaskID);
			DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.TaskName() );
			odbc.BindInput(2, obj.TaskName);
			DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.TaskStart );
			odbc.BindInput(3, &(obj.TaskStart), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.TaskFinish );
			odbc.BindInput(4, &(obj.TaskFinish), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.TaskCurrent );
			odbc.BindInput(5, &(obj.TaskCurrent), &sizeof_int, DB_INT);
			DEBUG(FL, "Setting input (%d) to value: %s", 6, obj.TaskMsg() );
			odbc.BindInput(6, obj.TaskMsg);
			DEBUG(FL, "Setting input (%d) to value: %s", 7, obj.TaskResponse() );
			odbc.BindInput(7, obj.TaskResponse);

		} // if(useInputs)

		// Execute the statement
		DEBUG(FL, "Executing the statement for LRTask::unusedSqlStmt");
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
twine LRTask::unusedSqlStmt_prepSQL(IOConn& ioc, LRTask& obj )
{
	EnEx ee(FL, "LRTask::unusedSqlStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "-- Nothing here";

	// Replace the TaskID parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TaskID );
	}

	// Replace the TaskName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TaskName );
	}

	// Replace the TaskStart parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.TaskStart;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the TaskFinish parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.TaskFinish;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the TaskCurrent parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.TaskCurrent;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the TaskMsg parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TaskMsg );
	}

	// Replace the TaskResponse parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TaskResponse );
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

