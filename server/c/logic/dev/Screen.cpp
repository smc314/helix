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

#include "Screen.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/Screen.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ScreenName = "Screen";

Screen::Screen()
{
	EnEx ee(FL, "Screen::Screen()");

	init();

}

Screen::Screen(const Screen& c)
{
	EnEx ee(FL, "Screen::Screen(const Screen& c)");

	ScrnName = c.ScrnName;
	guid = c.guid;
	projappguid = c.projappguid;


}

Screen& Screen::operator=(const Screen& c)
{
	EnEx ee(FL, "Screen::operator=(const Screen& c)");

	ScrnName = c.ScrnName;
	guid = c.guid;
	projappguid = c.projappguid;


	return *this;
}

Screen::~Screen()
{
	EnEx ee(FL, "Screen::~Screen()");

}

Screen& Screen::init()
{
	EnEx ee(FL, "Screen::init()");

	ScrnName.erase();
	guid.erase();
	projappguid.erase();


	return *this;
}

Screen& Screen::checkSize()
{
	EnEx ee(FL, "Screen::checkSize()");

	ScrnName.check_size();
	ScrnName.rtrim();
	guid.check_size();
	guid.rtrim();
	projappguid.check_size();
	projappguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Screen::Screen(xmlNodePtr node)
{
	EnEx ee(FL, "Screen::Screen(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Screen& Screen::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Screen::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Screen is NULL.");
	}

	ScrnName.getAttribute(node, "ScrnName");
	guid.getAttribute(node, "guid");
	projappguid.getAttribute(node, "projappguid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Screen::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Screen::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Screen::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Screen", NULL);
	xmlSetProp(child, (const xmlChar*)"ScrnName", ScrnName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projappguid", projappguid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Screen::createXmlDoc() const
{
	EnEx ee(FL, "Screen::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Screen", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"ScrnName", ScrnName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projappguid", projappguid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Screen* >* Screen::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Screen::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Screen::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Screen* >, Screen::deleteVector> ret = new vector<Screen* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Screen") == 0){
			ret->push_back( new Screen(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Screen::createXmlChildren(xmlNodePtr parent, vector<Screen* >* vect)
{
	EnEx ee(FL, "Screen::createXmlChildren(xmlNodePtr parent, vector<Screen* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Screen::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr Screen::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Screen* >* vect)
{
	EnEx ee(FL, "Screen::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Screen* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Screen::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	Screen::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Screen::deleteVector(vector<Screen* >* vect)
{
	EnEx ee(FL, "Screen::deleteVector(vector<Screen* >* vect)");

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
twine& Screen::Name()
{
	return ScreenName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new screen entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into screen (guid, projappguid, ScreenName)
			values ( ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Screen::insert(SqlDB& sqldb, Screen& obj )
{
	EnEx ee(FL, "Screen::insert()");

	twine stmt = "insert into screen (guid, projappguid, ScreenName) 			values ( ?, ?, ? )";

	Screen::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Screen::insert(SqlDB& sqldb, twine& stmt, bool useInputs, Screen& obj )
{
	EnEx ee(FL, "Screen::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Screen::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.projappguid(), (int)obj.projappguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.ScrnName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.ScrnName(), (int)obj.ScrnName.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Screen::insert");
			sqldb.check_err( sqlite3_step( db_stmt ) );


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
void Screen::insert(SqlDB& sqldb, vector< Screen* >* v, bool useTransaction)
{
	EnEx ee(FL, "Screen::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into screen (guid, projappguid, ScreenName) 			values ( ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Screen::insert()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->guid(), (int)v->at( v_i )->guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->projappguid(), (int)v->at( v_i )->projappguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->ScrnName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->ScrnName(), (int)v->at( v_i )->ScrnName.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Screen::insert");
				sqldb.check_err( sqlite3_step( db_stmt ) );


				// Reset the statement so that we can bind/execute again:
				sqlite3_reset( db_stmt );
			} // loop through all of the inputs

			// Commit our transaction here:
			if(useTransaction){
				DEBUG(FL, "Committing the vector insert transaction" );
				twine commitSql = "commit transaction;";
				sqldb.check_err( sqlite3_prepare( db, commitSql(), (int)commitSql.length(), &db_commit, NULL ) );
				sqldb.check_err( sqlite3_step( db_commit ) );
			}

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
twine Screen::insert_prepSQL(IOConn& ioc, Screen& obj )
{
	EnEx ee(FL, "Screen::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into screen (guid, projappguid, ScreenName) 			values ( ?, ?, ? )";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the projappguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.projappguid );
	}

	// Replace the ScrnName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ScrnName );
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
			This updates the settings for a given screen in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update screen
			set ScreenName = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Screen::update(SqlDB& sqldb, twine& ScrnName, twine& guid )
{
	EnEx ee(FL, "Screen::update()");

	twine stmt = "update screen 			set ScreenName = ? 			where guid = ?";

	Screen::update(sqldb, stmt, true, ScrnName, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Screen::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& ScrnName, twine& guid )
{
	EnEx ee(FL, "Screen::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Screen::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, ScrnName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, ScrnName(), (int)ScrnName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Screen::update");
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
twine Screen::update_prepSQL(IOConn& ioc, twine& ScrnName, twine& guid )
{
	EnEx ee(FL, "Screen::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update screen 			set ScreenName = ? 			where guid = ?";

	// Replace the ScrnName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ScrnName );
	}

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, guid );
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
			This removes a screen by id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from screen
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Screen::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "Screen::deleteByID()");

	twine stmt = "delete from screen 			where guid = ?";

	Screen::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Screen::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "Screen::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Screen::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Screen::deleteByID");
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
twine Screen::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "Screen::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from screen 			where guid = ?";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, guid );
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
			This selects all screens for a given application
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projappguid, ScreenName
			from screen
			where projappguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projappguid
   * ScrnName
 */
/* ************************************************************************************** */
vector<Screen* >* Screen::selectAllForApp(SqlDB& sqldb, twine& projappguid)
{
	EnEx ee(FL, "Screen::selectAllForApp()");

	twine stmt = "select guid, projappguid, ScreenName 			from screen 			where projappguid = ?";

	return Screen::selectAllForApp(sqldb, stmt, true, projappguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Screen* >* Screen::selectAllForApp(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projappguid)
{
	EnEx ee(FL, "Screen::selectAllForApp(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Screen* >, Screen::deleteVector> ret = new vector<Screen* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, projappguid(), (int)projappguid.length(), SQLITE_STATIC) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("Screen::selectAllForApp()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Screen::selectAllForApp");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			Screen* obj = new Screen( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projappguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->ScrnName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
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
twine Screen::selectAllForApp_prepSQL(IOConn& ioc, twine& projappguid)
{
	EnEx ee(FL, "Screen::selectAllForApp_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projappguid, ScreenName 			from screen 			where projappguid = ?";

	// Replace the projappguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, projappguid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

