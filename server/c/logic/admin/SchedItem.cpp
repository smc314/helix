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

#include "SchedItem.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/SchedItem.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine SchedItemName = "SchedItem";

SchedItem::SchedItem()
{
	EnEx ee(FL, "SchedItem::SchedItem()");

	init();

}

SchedItem::SchedItem(const SchedItem& c)
{
	EnEx ee(FL, "SchedItem::SchedItem(const SchedItem& c)");

	InputDocument = c.InputDocument;
	LastRun = c.LastRun;
	RunAtTime = c.RunAtTime;
	TaskName = c.TaskName;
	TaskUrl = c.TaskUrl;
	dowFriday = c.dowFriday;
	dowMonday = c.dowMonday;
	dowSaturday = c.dowSaturday;
	dowSunday = c.dowSunday;
	dowThursday = c.dowThursday;
	dowTuesday = c.dowTuesday;
	dowWednesday = c.dowWednesday;
	id = c.id;
	isActive = c.isActive;
	runEvery = c.runEvery;
	useInterval = c.useInterval;


}

SchedItem& SchedItem::operator=(const SchedItem& c)
{
	EnEx ee(FL, "SchedItem::operator=(const SchedItem& c)");

	InputDocument = c.InputDocument;
	LastRun = c.LastRun;
	RunAtTime = c.RunAtTime;
	TaskName = c.TaskName;
	TaskUrl = c.TaskUrl;
	dowFriday = c.dowFriday;
	dowMonday = c.dowMonday;
	dowSaturday = c.dowSaturday;
	dowSunday = c.dowSunday;
	dowThursday = c.dowThursday;
	dowTuesday = c.dowTuesday;
	dowWednesday = c.dowWednesday;
	id = c.id;
	isActive = c.isActive;
	runEvery = c.runEvery;
	useInterval = c.useInterval;


	return *this;
}

SchedItem::~SchedItem()
{
	EnEx ee(FL, "SchedItem::~SchedItem()");

}

SchedItem& SchedItem::init()
{
	EnEx ee(FL, "SchedItem::init()");

	InputDocument.erase();
	LastRun.erase();
	RunAtTime.erase();
	TaskName.erase();
	TaskUrl.erase();
	dowFriday = 0;
	dowMonday = 0;
	dowSaturday = 0;
	dowSunday = 0;
	dowThursday = 0;
	dowTuesday = 0;
	dowWednesday = 0;
	id = 0;
	isActive = 0;
	runEvery = 0;
	useInterval = 0;


	return *this;
}

SchedItem& SchedItem::checkSize()
{
	EnEx ee(FL, "SchedItem::checkSize()");

	InputDocument.check_size();
	InputDocument.rtrim();
	LastRun.check_size();
	LastRun.rtrim();
	RunAtTime.check_size();
	RunAtTime.rtrim();
	TaskName.check_size();
	TaskName.rtrim();
	TaskUrl.check_size();
	TaskUrl.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
SchedItem::SchedItem(xmlNodePtr node)
{
	EnEx ee(FL, "SchedItem::SchedItem(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
SchedItem& SchedItem::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "SchedItem::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct SchedItem is NULL.");
	}

	InputDocument.getAttribute(node, "InputDocument");
	LastRun.getAttribute(node, "LastRun");
	RunAtTime.getAttribute(node, "RunAtTime");
	TaskName.getAttribute(node, "TaskName");
	TaskUrl.getAttribute(node, "TaskUrl");
	dowFriday = XmlHelpers::getIntAttr(node, "dowFriday");
	dowMonday = XmlHelpers::getIntAttr(node, "dowMonday");
	dowSaturday = XmlHelpers::getIntAttr(node, "dowSaturday");
	dowSunday = XmlHelpers::getIntAttr(node, "dowSunday");
	dowThursday = XmlHelpers::getIntAttr(node, "dowThursday");
	dowTuesday = XmlHelpers::getIntAttr(node, "dowTuesday");
	dowWednesday = XmlHelpers::getIntAttr(node, "dowWednesday");
	id = XmlHelpers::getIntAttr(node, "id");
	isActive = XmlHelpers::getIntAttr(node, "isActive");
	runEvery = XmlHelpers::getIntAttr(node, "runEvery");
	useInterval = XmlHelpers::getIntAttr(node, "useInterval");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr SchedItem::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "SchedItem::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SchedItem::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"SchedItem", NULL);
	xmlSetProp(child, (const xmlChar*)"InputDocument", InputDocument);
	xmlSetProp(child, (const xmlChar*)"LastRun", LastRun);
	xmlSetProp(child, (const xmlChar*)"RunAtTime", RunAtTime);
	xmlSetProp(child, (const xmlChar*)"TaskName", TaskName);
	xmlSetProp(child, (const xmlChar*)"TaskUrl", TaskUrl);
	XmlHelpers::setIntAttr(child, "dowFriday", dowFriday);
	XmlHelpers::setIntAttr(child, "dowMonday", dowMonday);
	XmlHelpers::setIntAttr(child, "dowSaturday", dowSaturday);
	XmlHelpers::setIntAttr(child, "dowSunday", dowSunday);
	XmlHelpers::setIntAttr(child, "dowThursday", dowThursday);
	XmlHelpers::setIntAttr(child, "dowTuesday", dowTuesday);
	XmlHelpers::setIntAttr(child, "dowWednesday", dowWednesday);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "isActive", isActive);
	XmlHelpers::setIntAttr(child, "runEvery", runEvery);
	XmlHelpers::setIntAttr(child, "useInterval", useInterval);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr SchedItem::createXmlDoc() const
{
	EnEx ee(FL, "SchedItem::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"SchedItem", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"InputDocument", InputDocument);
	xmlSetProp(child, (const xmlChar*)"LastRun", LastRun);
	xmlSetProp(child, (const xmlChar*)"RunAtTime", RunAtTime);
	xmlSetProp(child, (const xmlChar*)"TaskName", TaskName);
	xmlSetProp(child, (const xmlChar*)"TaskUrl", TaskUrl);
	XmlHelpers::setIntAttr(child, "dowFriday", dowFriday);
	XmlHelpers::setIntAttr(child, "dowMonday", dowMonday);
	XmlHelpers::setIntAttr(child, "dowSaturday", dowSaturday);
	XmlHelpers::setIntAttr(child, "dowSunday", dowSunday);
	XmlHelpers::setIntAttr(child, "dowThursday", dowThursday);
	XmlHelpers::setIntAttr(child, "dowTuesday", dowTuesday);
	XmlHelpers::setIntAttr(child, "dowWednesday", dowWednesday);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "isActive", isActive);
	XmlHelpers::setIntAttr(child, "runEvery", runEvery);
	XmlHelpers::setIntAttr(child, "useInterval", useInterval);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<SchedItem* >* SchedItem::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "SchedItem::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SchedItem::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<SchedItem* >, SchedItem::deleteVector> ret = new vector<SchedItem* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "SchedItem") == 0){
			ret->push_back( new SchedItem(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void SchedItem::createXmlChildren(xmlNodePtr parent, vector<SchedItem* >* vect)
{
	EnEx ee(FL, "SchedItem::createXmlChildren(xmlNodePtr parent, vector<SchedItem* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to SchedItem::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void SchedItem::deleteVector(vector<SchedItem* >* vect)
{
	EnEx ee(FL, "SchedItem::deleteVector(vector<SchedItem* >* vect)");

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
twine& SchedItem::Name()
{
	return SchedItemName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add new schedule entries into our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into schedule (TaskName, TaskUrl, InputDocument, isActive, runEvery, 
				LastRun, useInterval, RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday,
				dowThursday, dowFriday, dowSaturday)
			values ( ?, ?, ?, ?, ?, 
				?, ?, ?, ?, ?, ?, ?,
				?, ?, ?)
		 */
/*                                                                                        */
/* ************************************************************************************** */
void SchedItem::insert(SqlDB& sqldb, SchedItem& obj )
{
	EnEx ee(FL, "SchedItem::insert()");

	twine stmt = "insert into schedule (TaskName, TaskUrl, InputDocument, isActive, runEvery,  				LastRun, useInterval, RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, 				dowThursday, dowFriday, dowSaturday) 			values ( ?, ?, ?, ?, ?,  				?, ?, ?, ?, ?, ?, ?, 				?, ?, ?)";

	SchedItem::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SchedItem::insert(SqlDB& sqldb, twine& stmt, bool useInputs, SchedItem& obj )
{
	EnEx ee(FL, "SchedItem::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("SchedItem::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.TaskName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.TaskName(), (int)obj.TaskName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.TaskUrl() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.TaskUrl(), (int)obj.TaskUrl.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.InputDocument() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.InputDocument(), (int)obj.InputDocument.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.isActive );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 4, (int)obj.isActive) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.runEvery );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)obj.runEvery) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, obj.LastRun() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, obj.LastRun(), (int)obj.LastRun.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 7, obj.useInterval );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 7, (int)obj.useInterval) );
				DEBUG(FL, "Setting input (%d) to value: %s", 8, obj.RunAtTime() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 8, obj.RunAtTime(), (int)obj.RunAtTime.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 9, obj.dowSunday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 9, (int)obj.dowSunday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 10, obj.dowMonday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 10, (int)obj.dowMonday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 11, obj.dowTuesday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 11, (int)obj.dowTuesday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 12, obj.dowWednesday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 12, (int)obj.dowWednesday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 13, obj.dowThursday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 13, (int)obj.dowThursday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 14, obj.dowFriday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 14, (int)obj.dowFriday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 15, obj.dowSaturday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 15, (int)obj.dowSaturday) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for SchedItem::insert");
			sqldb.check_err( sqlite3_step( db_stmt ) );

			// Update the insert object to pick up the new autogen value:
			obj.id = sqlite3_last_insert_rowid( db );


		} // End the Timing scope

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This is the version that accepts an array of inputs and ensures that they are all      */
/* written to the database with a single transaction                                      */
/* ************************************************************************************** */
void SchedItem::insert(SqlDB& sqldb, vector< SchedItem* >* v)
{
	EnEx ee(FL, "SchedItem::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into schedule (TaskName, TaskUrl, InputDocument, isActive, runEvery,  				LastRun, useInterval, RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, 				dowThursday, dowFriday, dowSaturday) 			values ( ?, ?, ?, ?, ?,  				?, ?, ?, ?, ?, ?, ?, 				?, ?, ?)";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("SchedItem::insert()-BindExecStmt");

			// Begin our transaction here:
			DEBUG(FL, "Beginning the vector insert transaction" );
			twine beginSql = "begin transaction;";
			sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
			sqldb.check_err( sqlite3_step( db_begin ) );

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->TaskName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->TaskName(), (int)v->at( v_i )->TaskName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->TaskUrl() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->TaskUrl(), (int)v->at( v_i )->TaskUrl.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->InputDocument() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->InputDocument(), (int)v->at( v_i )->InputDocument.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 4, v->at( v_i )->isActive );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 4, (int)v->at( v_i )->isActive) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, v->at( v_i )->runEvery );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)v->at( v_i )->runEvery) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, v->at( v_i )->LastRun() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, v->at( v_i )->LastRun(), (int)v->at( v_i )->LastRun.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 7, v->at( v_i )->useInterval );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 7, (int)v->at( v_i )->useInterval) );
				DEBUG(FL, "Setting input (%d) to value: %s", 8, v->at( v_i )->RunAtTime() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 8, v->at( v_i )->RunAtTime(), (int)v->at( v_i )->RunAtTime.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 9, v->at( v_i )->dowSunday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 9, (int)v->at( v_i )->dowSunday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 10, v->at( v_i )->dowMonday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 10, (int)v->at( v_i )->dowMonday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 11, v->at( v_i )->dowTuesday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 11, (int)v->at( v_i )->dowTuesday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 12, v->at( v_i )->dowWednesday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 12, (int)v->at( v_i )->dowWednesday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 13, v->at( v_i )->dowThursday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 13, (int)v->at( v_i )->dowThursday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 14, v->at( v_i )->dowFriday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 14, (int)v->at( v_i )->dowFriday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 15, v->at( v_i )->dowSaturday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 15, (int)v->at( v_i )->dowSaturday) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for SchedItem::insert");
				sqldb.check_err( sqlite3_step( db_stmt ) );

				// Update the insert object to pick up the new autogen value:
				v->at( v_i )->id = sqlite3_last_insert_rowid( db );


				// Reset the statement so that we can bind/execute again:
				sqlite3_reset( db_stmt );
			} // loop through all of the inputs

			// Commit our transaction here:
			DEBUG(FL, "Committing the vector insert transaction" );
			twine commitSql = "commit transaction;";
			sqldb.check_err( sqlite3_prepare( db, commitSql(), (int)commitSql.length(), &db_commit, NULL ) );
			sqldb.check_err( sqlite3_step( db_commit ) );

		} // End the Timing scope

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		if(db_begin != NULL){
			sqlite3_finalize( db_begin );
		}
		if(db_commit != NULL){
			sqlite3_finalize( db_commit );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	if(db_begin != NULL){
		sqlite3_finalize( db_begin );
	}
	if(db_commit != NULL){
		sqlite3_finalize( db_commit );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine SchedItem::insert_prepSQL(IOConn& ioc, SchedItem& obj )
{
	EnEx ee(FL, "SchedItem::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into schedule (TaskName, TaskUrl, InputDocument, isActive, runEvery,  				LastRun, useInterval, RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, 				dowThursday, dowFriday, dowSaturday) 			values ( ?, ?, ?, ?, ?,  				?, ?, ?, ?, ?, ?, ?, 				?, ?, ?)";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the TaskName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TaskName );
	}

	// Replace the TaskUrl parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TaskUrl );
	}

	// Replace the InputDocument parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.InputDocument );
	}

	// Replace the isActive parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.isActive;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the runEvery parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.runEvery;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the LastRun parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.LastRun );
	}

	// Replace the useInterval parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.useInterval;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the RunAtTime parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.RunAtTime );
	}

	// Replace the dowSunday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.dowSunday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowMonday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.dowMonday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowTuesday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.dowTuesday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowWednesday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.dowWednesday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowThursday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.dowThursday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowFriday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.dowFriday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowSaturday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.dowSaturday;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an UPDATE method.  It is designed to run a single update                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to update existing schedule entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update schedule
			set TaskName = ?,
				TaskUrl = ?,
				InputDocument = ?,
				isActive = ?,
				runEvery = ?,
				LastRun = ?,
				useInterval = ?,
				RunAtTime = ?,
				dowSunday = ?,
				dowMonday = ?,
				dowTuesday = ?,
				dowWednesday = ?,
				dowThursday = ?,
				dowFriday = ?,
				dowSaturday = ?
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void SchedItem::update(SqlDB& sqldb, twine& TaskName, twine& TaskUrl, twine& InputDocument, intptr_t isActive, intptr_t runEvery, twine& LastRun, intptr_t useInterval, twine& RunAtTime, intptr_t dowSunday, intptr_t dowMonday, intptr_t dowTuesday, intptr_t dowWednesday, intptr_t dowThursday, intptr_t dowFriday, intptr_t dowSaturday, intptr_t id )
{
	EnEx ee(FL, "SchedItem::update()");

	twine stmt = "update schedule 			set TaskName = ?, 				TaskUrl = ?, 				InputDocument = ?, 				isActive = ?, 				runEvery = ?, 				LastRun = ?, 				useInterval = ?, 				RunAtTime = ?, 				dowSunday = ?, 				dowMonday = ?, 				dowTuesday = ?, 				dowWednesday = ?, 				dowThursday = ?, 				dowFriday = ?, 				dowSaturday = ? 			where id = ?";

	SchedItem::update(sqldb, stmt, true, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval, RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, dowSaturday, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SchedItem::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& TaskName, twine& TaskUrl, twine& InputDocument, intptr_t isActive, intptr_t runEvery, twine& LastRun, intptr_t useInterval, twine& RunAtTime, intptr_t dowSunday, intptr_t dowMonday, intptr_t dowTuesday, intptr_t dowWednesday, intptr_t dowThursday, intptr_t dowFriday, intptr_t dowSaturday, intptr_t id )
{
	EnEx ee(FL, "SchedItem::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("SchedItem::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, TaskName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, TaskName(), (int)TaskName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, TaskUrl() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, TaskUrl(), (int)TaskUrl.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, InputDocument() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, InputDocument(), (int)InputDocument.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 4, isActive );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 4, (int)isActive) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, runEvery );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)runEvery) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, LastRun() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, LastRun(), (int)LastRun.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 7, useInterval );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 7, (int)useInterval) );
				DEBUG(FL, "Setting input (%d) to value: %s", 8, RunAtTime() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 8, RunAtTime(), (int)RunAtTime.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 9, dowSunday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 9, (int)dowSunday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 10, dowMonday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 10, (int)dowMonday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 11, dowTuesday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 11, (int)dowTuesday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 12, dowWednesday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 12, (int)dowWednesday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 13, dowThursday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 13, (int)dowThursday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 14, dowFriday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 14, (int)dowFriday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 15, dowSaturday );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 15, (int)dowSaturday) );
				DEBUG(FL, "Setting input (%d) to value: %d", 16, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 16, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for SchedItem::update");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine SchedItem::update_prepSQL(IOConn& ioc, twine& TaskName, twine& TaskUrl, twine& InputDocument, intptr_t isActive, intptr_t runEvery, twine& LastRun, intptr_t useInterval, twine& RunAtTime, intptr_t dowSunday, intptr_t dowMonday, intptr_t dowTuesday, intptr_t dowWednesday, intptr_t dowThursday, intptr_t dowFriday, intptr_t dowSaturday, intptr_t id )
{
	EnEx ee(FL, "SchedItem::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update schedule 			set TaskName = ?, 				TaskUrl = ?, 				InputDocument = ?, 				isActive = ?, 				runEvery = ?, 				LastRun = ?, 				useInterval = ?, 				RunAtTime = ?, 				dowSunday = ?, 				dowMonday = ?, 				dowTuesday = ?, 				dowWednesday = ?, 				dowThursday = ?, 				dowFriday = ?, 				dowSaturday = ? 			where id = ?";

	// Replace the TaskName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, TaskName );
	}

	// Replace the TaskUrl parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, TaskUrl );
	}

	// Replace the InputDocument parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, InputDocument );
	}

	// Replace the isActive parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = isActive;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the runEvery parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = runEvery;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the LastRun parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, LastRun );
	}

	// Replace the useInterval parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = useInterval;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the RunAtTime parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, RunAtTime );
	}

	// Replace the dowSunday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = dowSunday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowMonday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = dowMonday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowTuesday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = dowTuesday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowWednesday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = dowWednesday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowThursday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = dowThursday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowFriday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = dowFriday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the dowSaturday parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = dowSaturday;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an UPDATE method.  It is designed to run a single update                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to update the LastRun timestamp for a schedule entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update schedule
			set LastRun = ?
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void SchedItem::updateLastRun(SqlDB& sqldb, twine& LastRun, intptr_t id )
{
	EnEx ee(FL, "SchedItem::updateLastRun()");

	twine stmt = "update schedule 			set LastRun = ? 			where id = ?";

	SchedItem::updateLastRun(sqldb, stmt, true, LastRun, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SchedItem::updateLastRun(SqlDB& sqldb, twine& stmt, bool useInputs, twine& LastRun, intptr_t id )
{
	EnEx ee(FL, "SchedItem::updateLastRun()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("SchedItem::updateLastRun()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, LastRun() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, LastRun(), (int)LastRun.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for SchedItem::updateLastRun");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine SchedItem::updateLastRun_prepSQL(IOConn& ioc, twine& LastRun, intptr_t id )
{
	EnEx ee(FL, "SchedItem::updateLastRun_prepSQL()");

	size_t idx = 0;
	twine stmt = "update schedule 			set LastRun = ? 			where id = ?";

	// Replace the LastRun parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, LastRun );
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an DELETE method.  It is designed to run a single delete                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to delete existing schedule entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from schedule
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void SchedItem::deleteByID(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "SchedItem::deleteByID()");

	twine stmt = "delete from schedule 			where id = ?";

	SchedItem::deleteByID(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void SchedItem::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "SchedItem::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("SchedItem::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for SchedItem::deleteByID");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine SchedItem::deleteByID_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "SchedItem::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from schedule 			where id = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up all schedule entries in our database
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval,
				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday,
				dowSaturday
			from schedule
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * TaskName
   * TaskUrl
   * InputDocument
   * isActive
   * runEvery
   * LastRun
   * useInterval
   * RunAtTime
   * dowSunday
   * dowMonday
   * dowTuesday
   * dowWednesday
   * dowThursday
   * dowFriday
   * dowSaturday
 */
/* ************************************************************************************** */
vector<SchedItem* >* SchedItem::selectAll(SqlDB& sqldb)
{
	EnEx ee(FL, "SchedItem::selectAll()");

	twine stmt = "select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval, 				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, 				dowSaturday 			from schedule";

	return SchedItem::selectAll(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<SchedItem* >* SchedItem::selectAll(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "SchedItem::selectAll(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<SchedItem* >, SchedItem::deleteVector> ret = new vector<SchedItem* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("SchedItem::selectAll()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for SchedItem::selectAll");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			SchedItem* obj = new SchedItem( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->TaskName.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->TaskUrl.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->InputDocument.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->isActive = sqlite3_column_int( db_stmt, 4);
			}
			if( 5 < colCount ){
				obj->runEvery = sqlite3_column_int( db_stmt, 5);
			}
			if( 6 < colCount ){
				obj->LastRun.set( (const char*)sqlite3_column_text( db_stmt, 6), (size_t)sqlite3_column_bytes(db_stmt, 6) );
			}
			if( 7 < colCount ){
				obj->useInterval = sqlite3_column_int( db_stmt, 7);
			}
			if( 8 < colCount ){
				obj->RunAtTime.set( (const char*)sqlite3_column_text( db_stmt, 8), (size_t)sqlite3_column_bytes(db_stmt, 8) );
			}
			if( 9 < colCount ){
				obj->dowSunday = sqlite3_column_int( db_stmt, 9);
			}
			if( 10 < colCount ){
				obj->dowMonday = sqlite3_column_int( db_stmt, 10);
			}
			if( 11 < colCount ){
				obj->dowTuesday = sqlite3_column_int( db_stmt, 11);
			}
			if( 12 < colCount ){
				obj->dowWednesday = sqlite3_column_int( db_stmt, 12);
			}
			if( 13 < colCount ){
				obj->dowThursday = sqlite3_column_int( db_stmt, 13);
			}
			if( 14 < colCount ){
				obj->dowFriday = sqlite3_column_int( db_stmt, 14);
			}
			if( 15 < colCount ){
				obj->dowSaturday = sqlite3_column_int( db_stmt, 15);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine SchedItem::selectAll_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "SchedItem::selectAll_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval, 				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, 				dowSaturday 			from schedule";

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up a single schedule entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval,
				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday,
				dowSaturday
			from schedule
			where id = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * TaskName
   * TaskUrl
   * InputDocument
   * isActive
   * runEvery
   * LastRun
   * useInterval
   * RunAtTime
   * dowSunday
   * dowMonday
   * dowTuesday
   * dowWednesday
   * dowThursday
   * dowFriday
   * dowSaturday
 */
/* ************************************************************************************** */
vector<SchedItem* >* SchedItem::selectByID(SqlDB& sqldb, intptr_t id)
{
	EnEx ee(FL, "SchedItem::selectByID()");

	twine stmt = "select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval, 				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, 				dowSaturday 			from schedule 			where id = ?";

	return SchedItem::selectByID(sqldb, stmt, true, id);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<SchedItem* >* SchedItem::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id)
{
	EnEx ee(FL, "SchedItem::selectByID(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<SchedItem* >, SchedItem::deleteVector> ret = new vector<SchedItem* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("SchedItem::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for SchedItem::selectByID");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			SchedItem* obj = new SchedItem( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->TaskName.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->TaskUrl.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->InputDocument.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->isActive = sqlite3_column_int( db_stmt, 4);
			}
			if( 5 < colCount ){
				obj->runEvery = sqlite3_column_int( db_stmt, 5);
			}
			if( 6 < colCount ){
				obj->LastRun.set( (const char*)sqlite3_column_text( db_stmt, 6), (size_t)sqlite3_column_bytes(db_stmt, 6) );
			}
			if( 7 < colCount ){
				obj->useInterval = sqlite3_column_int( db_stmt, 7);
			}
			if( 8 < colCount ){
				obj->RunAtTime.set( (const char*)sqlite3_column_text( db_stmt, 8), (size_t)sqlite3_column_bytes(db_stmt, 8) );
			}
			if( 9 < colCount ){
				obj->dowSunday = sqlite3_column_int( db_stmt, 9);
			}
			if( 10 < colCount ){
				obj->dowMonday = sqlite3_column_int( db_stmt, 10);
			}
			if( 11 < colCount ){
				obj->dowTuesday = sqlite3_column_int( db_stmt, 11);
			}
			if( 12 < colCount ){
				obj->dowWednesday = sqlite3_column_int( db_stmt, 12);
			}
			if( 13 < colCount ){
				obj->dowThursday = sqlite3_column_int( db_stmt, 13);
			}
			if( 14 < colCount ){
				obj->dowFriday = sqlite3_column_int( db_stmt, 14);
			}
			if( 15 < colCount ){
				obj->dowSaturday = sqlite3_column_int( db_stmt, 15);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine SchedItem::selectByID_prepSQL(IOConn& ioc, intptr_t id)
{
	EnEx ee(FL, "SchedItem::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval, 				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, 				dowSaturday 			from schedule 			where id = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

