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

#include "TableCol.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/TableCol.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine TableColName = "TableCol";

TableCol::TableCol()
{
	EnEx ee(FL, "TableCol::TableCol()");

	init();

}

TableCol::TableCol(const TableCol& c)
{
	EnEx ee(FL, "TableCol::TableCol(const TableCol& c)");

	ColName = c.ColName;
	ColType = c.ColType;
	guid = c.guid;
	projtableguid = c.projtableguid;


}

TableCol& TableCol::operator=(const TableCol& c)
{
	EnEx ee(FL, "TableCol::operator=(const TableCol& c)");

	ColName = c.ColName;
	ColType = c.ColType;
	guid = c.guid;
	projtableguid = c.projtableguid;


	return *this;
}

TableCol::~TableCol()
{
	EnEx ee(FL, "TableCol::~TableCol()");

}

TableCol& TableCol::init()
{
	EnEx ee(FL, "TableCol::init()");

	ColName.erase();
	ColType.erase();
	guid.erase();
	projtableguid.erase();


	return *this;
}

TableCol& TableCol::checkSize()
{
	EnEx ee(FL, "TableCol::checkSize()");

	ColName.check_size();
	ColName.rtrim();
	ColType.check_size();
	ColType.rtrim();
	guid.check_size();
	guid.rtrim();
	projtableguid.check_size();
	projtableguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
TableCol::TableCol(xmlNodePtr node)
{
	EnEx ee(FL, "TableCol::TableCol(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
TableCol& TableCol::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "TableCol::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct TableCol is NULL.");
	}

	ColName.getAttribute(node, "ColName");
	ColType.getAttribute(node, "ColType");
	guid.getAttribute(node, "guid");
	projtableguid.getAttribute(node, "projtableguid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr TableCol::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "TableCol::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to TableCol::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"TableCol", NULL);
	xmlSetProp(child, (const xmlChar*)"ColName", ColName);
	xmlSetProp(child, (const xmlChar*)"ColType", ColType);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projtableguid", projtableguid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr TableCol::createXmlDoc() const
{
	EnEx ee(FL, "TableCol::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"TableCol", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"ColName", ColName);
	xmlSetProp(child, (const xmlChar*)"ColType", ColType);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projtableguid", projtableguid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<TableCol* >* TableCol::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "TableCol::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to TableCol::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<TableCol* >, TableCol::deleteVector> ret = new vector<TableCol* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "TableCol") == 0){
			ret->push_back( new TableCol(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void TableCol::createXmlChildren(xmlNodePtr parent, vector<TableCol* >* vect)
{
	EnEx ee(FL, "TableCol::createXmlChildren(xmlNodePtr parent, vector<TableCol* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to TableCol::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr TableCol::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<TableCol* >* vect)
{
	EnEx ee(FL, "TableCol::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<TableCol* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to TableCol::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	TableCol::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void TableCol::deleteVector(vector<TableCol* >* vect)
{
	EnEx ee(FL, "TableCol::deleteVector(vector<TableCol* >* vect)");

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
twine& TableCol::Name()
{
	return TableColName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new table column entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into projcol (guid, projtableguid, ColName, ColType )
			values ( ?, ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void TableCol::insert(SqlDB& sqldb, TableCol& obj )
{
	EnEx ee(FL, "TableCol::insert()");

	twine stmt = "insert into projcol (guid, projtableguid, ColName, ColType ) 			values ( ?, ?, ?, ? )";

	TableCol::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void TableCol::insert(SqlDB& sqldb, twine& stmt, bool useInputs, TableCol& obj )
{
	EnEx ee(FL, "TableCol::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("TableCol::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.projtableguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.projtableguid(), (int)obj.projtableguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.ColName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.ColName(), (int)obj.ColName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.ColType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.ColType(), (int)obj.ColType.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for TableCol::insert");
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
void TableCol::insert(SqlDB& sqldb, vector< TableCol* >* v, bool useTransaction)
{
	EnEx ee(FL, "TableCol::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into projcol (guid, projtableguid, ColName, ColType ) 			values ( ?, ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("TableCol::insert()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->projtableguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->projtableguid(), (int)v->at( v_i )->projtableguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->ColName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->ColName(), (int)v->at( v_i )->ColName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->ColType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->ColType(), (int)v->at( v_i )->ColType.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for TableCol::insert");
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
twine TableCol::insert_prepSQL(IOConn& ioc, TableCol& obj )
{
	EnEx ee(FL, "TableCol::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into projcol (guid, projtableguid, ColName, ColType ) 			values ( ?, ?, ?, ? )";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the projtableguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.projtableguid );
	}

	// Replace the ColName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ColName );
	}

	// Replace the ColType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ColType );
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
			This updates the settings for a given table column in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update projcol
			set ColName = ?,
				ColType= ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void TableCol::update(SqlDB& sqldb, twine& ColName, twine& ColType, twine& guid )
{
	EnEx ee(FL, "TableCol::update()");

	twine stmt = "update projcol 			set ColName = ?, 				ColType= ? 			where guid = ?";

	TableCol::update(sqldb, stmt, true, ColName, ColType, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void TableCol::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& ColName, twine& ColType, twine& guid )
{
	EnEx ee(FL, "TableCol::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("TableCol::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, ColName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, ColName(), (int)ColName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, ColType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, ColType(), (int)ColType.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for TableCol::update");
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
twine TableCol::update_prepSQL(IOConn& ioc, twine& ColName, twine& ColType, twine& guid )
{
	EnEx ee(FL, "TableCol::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update projcol 			set ColName = ?, 				ColType= ? 			where guid = ?";

	// Replace the ColName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ColName );
	}

	// Replace the ColType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ColType );
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
			This removes a table column by guid
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from projcol
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void TableCol::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "TableCol::deleteByID()");

	twine stmt = "delete from projcol 			where guid = ?";

	TableCol::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void TableCol::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "TableCol::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("TableCol::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for TableCol::deleteByID");
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
twine TableCol::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "TableCol::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from projcol 			where guid = ?";

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
			This removes all columns for a given table
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from projcol
			where projtableguid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void TableCol::deleteByTable(SqlDB& sqldb, twine& projtableguid )
{
	EnEx ee(FL, "TableCol::deleteByTable()");

	twine stmt = "delete from projcol 			where projtableguid = ?";

	TableCol::deleteByTable(sqldb, stmt, true, projtableguid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void TableCol::deleteByTable(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projtableguid )
{
	EnEx ee(FL, "TableCol::deleteByTable()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("TableCol::deleteByTable()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, projtableguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, projtableguid(), (int)projtableguid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for TableCol::deleteByTable");
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
twine TableCol::deleteByTable_prepSQL(IOConn& ioc, twine& projtableguid )
{
	EnEx ee(FL, "TableCol::deleteByTable_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from projcol 			where projtableguid = ?";

	// Replace the projtableguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, projtableguid );
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
			This selects all columns for a given table 
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projtableguid, ColName, ColType
			from projcol
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projtableguid
   * ColName
   * ColType
 */
/* ************************************************************************************** */
vector<TableCol* >* TableCol::selectAllForTable(SqlDB& sqldb)
{
	EnEx ee(FL, "TableCol::selectAllForTable()");

	twine stmt = "select guid, projtableguid, ColName, ColType 			from projcol";

	return TableCol::selectAllForTable(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<TableCol* >* TableCol::selectAllForTable(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "TableCol::selectAllForTable(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<TableCol* >, TableCol::deleteVector> ret = new vector<TableCol* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("TableCol::selectAllForTable()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for TableCol::selectAllForTable");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			TableCol* obj = new TableCol( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projtableguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->ColName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->ColType.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
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
twine TableCol::selectAllForTable_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "TableCol::selectAllForTable_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projtableguid, ColName, ColType 			from projcol";

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

