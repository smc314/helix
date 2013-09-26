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

#include "DObject.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/DObject.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine DObjectName = "DObject";

DObject::DObject()
{
	EnEx ee(FL, "DObject::DObject()");

	init();

}

DObject::DObject(const DObject& c)
{
	EnEx ee(FL, "DObject::DObject(const DObject& c)");

	DataObjectName = c.DataObjectName;
	guid = c.guid;
	projappguid = c.projappguid;
	DOChildren = new vector<DOChild*>();
	for(size_t i = 0; i < c.DOChildren->size(); i++){
		DOChildren->push_back( new DOChild( *(c.DOChildren->at( i )) ) );
	}
	DOStmts = new vector<DOStmt*>();
	for(size_t i = 0; i < c.DOStmts->size(); i++){
		DOStmts->push_back( new DOStmt( *(c.DOStmts->at( i )) ) );
	}


}

DObject& DObject::operator=(const DObject& c)
{
	EnEx ee(FL, "DObject::operator=(const DObject& c)");

	DataObjectName = c.DataObjectName;
	guid = c.guid;
	projappguid = c.projappguid;
	DOChildren = new vector<DOChild*>();
	for(size_t i = 0; i < c.DOChildren->size(); i++){
		DOChildren->push_back( new DOChild( *(c.DOChildren->at( i )) ) );
	}
	DOStmts = new vector<DOStmt*>();
	for(size_t i = 0; i < c.DOStmts->size(); i++){
		DOStmts->push_back( new DOStmt( *(c.DOStmts->at( i )) ) );
	}


	return *this;
}

DObject::~DObject()
{
	EnEx ee(FL, "DObject::~DObject()");

}

DObject& DObject::init()
{
	EnEx ee(FL, "DObject::init()");

	DataObjectName.erase();
	guid.erase();
	projappguid.erase();
	DOChildren = new vector<DOChild*>();
	DOStmts = new vector<DOStmt*>();


	return *this;
}

DObject& DObject::checkSize()
{
	EnEx ee(FL, "DObject::checkSize()");

	DataObjectName.check_size();
	DataObjectName.rtrim();
	guid.check_size();
	guid.rtrim();
	projappguid.check_size();
	projappguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
DObject::DObject(xmlNodePtr node)
{
	EnEx ee(FL, "DObject::DObject(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
DObject& DObject::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "DObject::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct DObject is NULL.");
	}

	DataObjectName.getAttribute(node, "DataObjectName");
	guid.getAttribute(node, "guid");
	projappguid.getAttribute(node, "projappguid");
	DOChildren = DOChild::readXmlChildren( XmlHelpers::FindChild( node, "DOChildren") );
	DOStmts = DOStmt::readXmlChildren( XmlHelpers::FindChild( node, "DOStmts") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr DObject::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "DObject::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DObject::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"DObject", NULL);
	xmlSetProp(child, (const xmlChar*)"DataObjectName", DataObjectName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projappguid", projappguid);
	xmlNodePtr DOChildren_node = xmlNewChild(child, NULL, (const xmlChar*)"DOChildren", NULL);
	DOChild::createXmlChildren( DOChildren_node, DOChildren );

	xmlNodePtr DOStmts_node = xmlNewChild(child, NULL, (const xmlChar*)"DOStmts", NULL);
	DOStmt::createXmlChildren( DOStmts_node, DOStmts );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr DObject::createXmlDoc() const
{
	EnEx ee(FL, "DObject::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"DObject", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"DataObjectName", DataObjectName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projappguid", projappguid);
	xmlNodePtr DOChildren_node = xmlNewChild(child, NULL, (const xmlChar*)"DOChildren", NULL);
	DOChild::createXmlChildren( DOChildren_node, DOChildren );

	xmlNodePtr DOStmts_node = xmlNewChild(child, NULL, (const xmlChar*)"DOStmts", NULL);
	DOStmt::createXmlChildren( DOStmts_node, DOStmts );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<DObject* >* DObject::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "DObject::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DObject::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<DObject* >, DObject::deleteVector> ret = new vector<DObject* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "DObject") == 0){
			ret->push_back( new DObject(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void DObject::createXmlChildren(xmlNodePtr parent, vector<DObject* >* vect)
{
	EnEx ee(FL, "DObject::createXmlChildren(xmlNodePtr parent, vector<DObject* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DObject::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void DObject::deleteVector(vector<DObject* >* vect)
{
	EnEx ee(FL, "DObject::deleteVector(vector<DObject* >* vect)");

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
twine& DObject::Name()
{
	return DObjectName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new data object entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into dataobject (guid, projappguid, DataObjectName)
			values ( ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DObject::insert(SqlDB& sqldb, DObject& obj )
{
	EnEx ee(FL, "DObject::insert()");

	twine stmt = "insert into dataobject (guid, projappguid, DataObjectName) 			values ( ?, ?, ? )";

	DObject::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DObject::insert(SqlDB& sqldb, twine& stmt, bool useInputs, DObject& obj )
{
	EnEx ee(FL, "DObject::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DObject::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.projappguid(), (int)obj.projappguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.DataObjectName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.DataObjectName(), (int)obj.DataObjectName.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DObject::insert");
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
void DObject::insert(SqlDB& sqldb, vector< DObject* >* v)
{
	EnEx ee(FL, "DObject::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into dataobject (guid, projappguid, DataObjectName) 			values ( ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DObject::insert()-BindExecStmt");

			// Begin our transaction here:
			DEBUG(FL, "Beginning the vector insert transaction" );
			twine beginSql = "begin transaction;";
			sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
			sqldb.check_err( sqlite3_step( db_begin ) );

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->guid(), (int)v->at( v_i )->guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->projappguid(), (int)v->at( v_i )->projappguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->DataObjectName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->DataObjectName(), (int)v->at( v_i )->DataObjectName.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for DObject::insert");
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
twine DObject::insert_prepSQL(IOConn& ioc, DObject& obj )
{
	EnEx ee(FL, "DObject::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into dataobject (guid, projappguid, DataObjectName) 			values ( ?, ?, ? )";

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

	// Replace the DataObjectName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.DataObjectName );
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
			This updates the settings for a given data object in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update dataobject
			set DataObjectName = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DObject::update(SqlDB& sqldb, twine& DataObjectName, twine& guid )
{
	EnEx ee(FL, "DObject::update()");

	twine stmt = "update dataobject 			set DataObjectName = ? 			where guid = ?";

	DObject::update(sqldb, stmt, true, DataObjectName, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DObject::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& DataObjectName, twine& guid )
{
	EnEx ee(FL, "DObject::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DObject::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, DataObjectName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, DataObjectName(), (int)DataObjectName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DObject::update");
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
twine DObject::update_prepSQL(IOConn& ioc, twine& DataObjectName, twine& guid )
{
	EnEx ee(FL, "DObject::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update dataobject 			set DataObjectName = ? 			where guid = ?";

	// Replace the DataObjectName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, DataObjectName );
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
			This removes a data object by id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from dataobject
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DObject::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "DObject::deleteByID()");

	twine stmt = "delete from dataobject 			where guid = ?";

	DObject::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DObject::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "DObject::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DObject::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DObject::deleteByID");
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
twine DObject::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "DObject::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from dataobject 			where guid = ?";

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
			This selects all data objects for a given application
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projappguid, DataObjectName
			from dataobject
			where projappguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projappguid
   * DataObjectName
 */
/* ************************************************************************************** */
vector<DObject* >* DObject::selectAllForApp(SqlDB& sqldb, twine& projappguid)
{
	EnEx ee(FL, "DObject::selectAllForApp()");

	twine stmt = "select guid, projappguid, DataObjectName 			from dataobject 			where projappguid = ?";

	return DObject::selectAllForApp(sqldb, stmt, true, projappguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<DObject* >* DObject::selectAllForApp(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projappguid)
{
	EnEx ee(FL, "DObject::selectAllForApp(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<DObject* >, DObject::deleteVector> ret = new vector<DObject* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, projappguid(), (int)projappguid.length(), SQLITE_STATIC) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("DObject::selectAllForApp()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for DObject::selectAllForApp");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			DObject* obj = new DObject( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projappguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->DataObjectName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
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
twine DObject::selectAllForApp_prepSQL(IOConn& ioc, twine& projappguid)
{
	EnEx ee(FL, "DObject::selectAllForApp_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projappguid, DataObjectName 			from dataobject 			where projappguid = ?";

	// Replace the projappguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, projappguid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

