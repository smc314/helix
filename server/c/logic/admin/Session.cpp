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

#include "Session.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/Session.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine SessionName = "Session";

Session::Session()
{
	EnEx ee(FL, "Session::Session()");

	init();

}

Session::Session(const Session& c)
{
	EnEx ee(FL, "Session::Session(const Session& c)");

	Active = c.Active;
	Created = c.Created;
	LastAccess = c.LastAccess;
	Userid = c.Userid;
	guid = c.guid;


}

Session& Session::operator=(const Session& c)
{
	EnEx ee(FL, "Session::operator=(const Session& c)");

	Active = c.Active;
	Created = c.Created;
	LastAccess = c.LastAccess;
	Userid = c.Userid;
	guid = c.guid;


	return *this;
}

Session::~Session()
{
	EnEx ee(FL, "Session::~Session()");

}

Session& Session::init()
{
	EnEx ee(FL, "Session::init()");

	Active = 0;
	Userid = 0;
	guid.erase();


	return *this;
}

Session& Session::checkSize()
{
	EnEx ee(FL, "Session::checkSize()");

	guid.check_size();
	guid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Session::Session(xmlNodePtr node)
{
	EnEx ee(FL, "Session::Session(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Session& Session::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Session::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Session is NULL.");
	}

	Active = XmlHelpers::getIntAttr(node, "Active");
	Created.SetValue( xmlGetProp(node, (const xmlChar*)"Created") );
	LastAccess.SetValue( xmlGetProp(node, (const xmlChar*)"LastAccess") );
	Userid = XmlHelpers::getIntAttr(node, "Userid");
	guid.getAttribute(node, "guid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Session::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Session::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Session::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Session", NULL);
	XmlHelpers::setIntAttr(child, "Active", Active);
	XmlHelpers::setDateAttr(child, "Created", Created);
	XmlHelpers::setDateAttr(child, "LastAccess", LastAccess);
	XmlHelpers::setIntAttr(child, "Userid", Userid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Session::createXmlDoc() const
{
	EnEx ee(FL, "Session::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Session", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	XmlHelpers::setIntAttr(child, "Active", Active);
	XmlHelpers::setDateAttr(child, "Created", Created);
	XmlHelpers::setDateAttr(child, "LastAccess", LastAccess);
	XmlHelpers::setIntAttr(child, "Userid", Userid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Session* >* Session::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Session::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Session::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Session* >, Session::deleteVector> ret = new vector<Session* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Session") == 0){
			ret->push_back( new Session(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Session::createXmlChildren(xmlNodePtr parent, vector<Session* >* vect)
{
	EnEx ee(FL, "Session::createXmlChildren(xmlNodePtr parent, vector<Session* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Session::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Session::deleteVector(vector<Session* >* vect)
{
	EnEx ee(FL, "Session::deleteVector(vector<Session* >* vect)");

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
twine& Session::Name()
{
	return SessionName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add new sesion entries into our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into session (guid, userid, created, lastaccess, active)
			values ( ?, ?, ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Session::insert(SqlDB& sqldb, Session& obj )
{
	EnEx ee(FL, "Session::insert()");

	twine stmt = "insert into session (guid, userid, created, lastaccess, active) 			values ( ?, ?, ?, ?, ? )";

	Session::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Session::insert(SqlDB& sqldb, twine& stmt, bool useInputs, Session& obj )
{
	EnEx ee(FL, "Session::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Session::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.Userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.Userid) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.Created.GetValue() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.Created.GetValue(), 20, SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.LastAccess.GetValue() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.LastAccess.GetValue(), 20, SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.Active );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)obj.Active) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Session::insert");
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
void Session::insert(SqlDB& sqldb, vector< Session* >* v)
{
	EnEx ee(FL, "Session::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into session (guid, userid, created, lastaccess, active) 			values ( ?, ?, ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Session::insert()-BindExecStmt");

			// Begin our transaction here:
			DEBUG(FL, "Beginning the vector insert transaction" );
			twine beginSql = "begin transaction;";
			sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
			sqldb.check_err( sqlite3_step( db_begin ) );

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->guid(), (int)v->at( v_i )->guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->Userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->Userid) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->Created.GetValue() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->Created.GetValue(), 20, SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->LastAccess.GetValue() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->LastAccess.GetValue(), 20, SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, v->at( v_i )->Active );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)v->at( v_i )->Active) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Session::insert");
				sqldb.check_err( sqlite3_step( db_stmt ) );


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
twine Session::insert_prepSQL(IOConn& ioc, Session& obj )
{
	EnEx ee(FL, "Session::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into session (guid, userid, created, lastaccess, active) 			values ( ?, ?, ?, ?, ? )";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the Userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Created parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Created );
	}

	// Replace the LastAccess parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.LastAccess );
	}

	// Replace the Active parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Active;
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
			This is the statement that we use to update existing session entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update session
			set userid = ?,
				created = ?,
				lastaccess = ?,
				active = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Session::update(SqlDB& sqldb, intptr_t Userid, Date& Created, Date& LastAccess, intptr_t Active, twine& guid )
{
	EnEx ee(FL, "Session::update()");

	twine stmt = "update session 			set userid = ?, 				created = ?, 				lastaccess = ?, 				active = ? 			where guid = ?";

	Session::update(sqldb, stmt, true, Userid, Created, LastAccess, Active, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Session::update(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t Userid, Date& Created, Date& LastAccess, intptr_t Active, twine& guid )
{
	EnEx ee(FL, "Session::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Session::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, Userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)Userid) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Created.GetValue() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Created.GetValue(), 20, SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, LastAccess.GetValue() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, LastAccess.GetValue(), 20, SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 4, Active );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 4, (int)Active) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Session::update");
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
twine Session::update_prepSQL(IOConn& ioc, intptr_t Userid, Date& Created, Date& LastAccess, intptr_t Active, twine& guid )
{
	EnEx ee(FL, "Session::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update session 			set userid = ?, 				created = ?, 				lastaccess = ?, 				active = ? 			where guid = ?";

	// Replace the Userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = Userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Created parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Created );
	}

	// Replace the LastAccess parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, LastAccess );
	}

	// Replace the Active parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = Active;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to delete existing user session in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from session
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Session::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "Session::deleteByID()");

	twine stmt = "delete from session 			where guid = ?";

	Session::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Session::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "Session::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("Session::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Session::deleteByID");
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
twine Session::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "Session::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from session 			where guid = ?";

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
			This is the statement that we use to pull up all session entries in our database
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, userid, created, lastaccess, active
			from session
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * Userid
   * Created
   * LastAccess
   * Active
 */
/* ************************************************************************************** */
vector<Session* >* Session::selectAll(SqlDB& sqldb)
{
	EnEx ee(FL, "Session::selectAll()");

	twine stmt = "select guid, userid, created, lastaccess, active 			from session";

	return Session::selectAll(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Session* >* Session::selectAll(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "Session::selectAll(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Session* >, Session::deleteVector> ret = new vector<Session* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("Session::selectAll()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Session::selectAll");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			Session* obj = new Session( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->Userid = sqlite3_column_int( db_stmt, 1);
			}
			if( 2 < colCount ){
				obj->Created.SetValue( (const char*)sqlite3_column_text( db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->LastAccess.SetValue( (const char*)sqlite3_column_text( db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Active = sqlite3_column_int( db_stmt, 4);
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
twine Session::selectAll_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "Session::selectAll_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, userid, created, lastaccess, active 			from session";

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
			This is the statement that we use to pull up a single session entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, userid, created, lastaccess, active
			from session
			where guid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * Userid
   * Created
   * LastAccess
   * Active
 */
/* ************************************************************************************** */
vector<Session* >* Session::selectByID(SqlDB& sqldb, twine& guid)
{
	EnEx ee(FL, "Session::selectByID()");

	twine stmt = "select guid, userid, created, lastaccess, active 			from session 			where guid = ?";

	return Session::selectByID(sqldb, stmt, true, guid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Session* >* Session::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid)
{
	EnEx ee(FL, "Session::selectByID(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Session* >, Session::deleteVector> ret = new vector<Session* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("Session::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Session::selectByID");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			Session* obj = new Session( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->Userid = sqlite3_column_int( db_stmt, 1);
			}
			if( 2 < colCount ){
				obj->Created.SetValue( (const char*)sqlite3_column_text( db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->LastAccess.SetValue( (const char*)sqlite3_column_text( db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Active = sqlite3_column_int( db_stmt, 4);
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
twine Session::selectByID_prepSQL(IOConn& ioc, twine& guid)
{
	EnEx ee(FL, "Session::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, userid, created, lastaccess, active 			from session 			where guid = ?";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, guid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

