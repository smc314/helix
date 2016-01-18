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

#include "Api.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/Api.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ApiName = "Api";

Api::Api()
{
	EnEx ee(FL, "Api::Api()");

	init();

}

Api::Api(const Api& c)
{
	EnEx ee(FL, "Api::Api(const Api& c)");

	ApiShortName = c.ApiShortName;
	guid = c.guid;
	projappguid = c.projappguid;


}

Api& Api::operator=(const Api& c)
{
	EnEx ee(FL, "Api::operator=(const Api& c)");

	ApiShortName = c.ApiShortName;
	guid = c.guid;
	projappguid = c.projappguid;


	return *this;
}

Api::~Api()
{
	EnEx ee(FL, "Api::~Api()");

}

Api& Api::init()
{
	EnEx ee(FL, "Api::init()");

	ApiShortName.erase();
	guid.erase();
	projappguid.erase();


	return *this;
}

Api& Api::checkSize()
{
	EnEx ee(FL, "Api::checkSize()");

	ApiShortName.check_size();
	ApiShortName.rtrim();
	guid.check_size();
	guid.rtrim();
	projappguid.check_size();
	projappguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Api::Api(xmlNodePtr node)
{
	EnEx ee(FL, "Api::Api(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Api& Api::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Api::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Api is NULL.");
	}

	ApiShortName.getAttribute(node, "ApiShortName");
	guid.getAttribute(node, "guid");
	projappguid.getAttribute(node, "projappguid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Api::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Api::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Api::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Api", NULL);
	xmlSetProp(child, (const xmlChar*)"ApiShortName", ApiShortName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projappguid", projappguid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Api::createXmlDoc() const
{
	EnEx ee(FL, "Api::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Api", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"ApiShortName", ApiShortName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projappguid", projappguid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Api* >* Api::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Api::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Api::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Api* >, Api::deleteVector> ret = new vector<Api* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Api") == 0){
			ret->push_back( new Api(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Api::createXmlChildren(xmlNodePtr parent, vector<Api* >* vect)
{
	EnEx ee(FL, "Api::createXmlChildren(xmlNodePtr parent, vector<Api* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Api::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr Api::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Api* >* vect)
{
	EnEx ee(FL, "Api::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Api* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Api::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	Api::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Api::deleteVector(vector<Api* >* vect)
{
	EnEx ee(FL, "Api::deleteVector(vector<Api* >* vect)");

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
twine& Api::Name()
{
	return ApiName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new Api entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into api (guid, projappguid, ApiName)
			values ( ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Api::insert(SqlDB& sqldb, Api& obj )
{
	EnEx ee(FL, "Api::insert()");

	twine stmt = "insert into api (guid, projappguid, ApiName) 			values ( ?, ?, ? )";

	Api::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Api::insert(SqlDB& sqldb, twine& stmt, bool useInputs, Api& obj )
{
	EnEx ee(FL, "Api::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Api::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.projappguid(), (int)obj.projappguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.ApiShortName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.ApiShortName(), (int)obj.ApiShortName.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Api::insert");
			sqldb.check_err( sqlite3_step( db_stmt ) );


		} // End the Timing scope
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
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
/* This is the version that accepts an array of inputs and ensures that they are all      */
/* written to the database with a single transaction                                      */
/* ************************************************************************************** */
void Api::insert(SqlDB& sqldb, vector< Api* >* v, bool useTransaction)
{
	EnEx ee(FL, "Api::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into api (guid, projappguid, ApiName) 			values ( ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Api::insert()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->ApiShortName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->ApiShortName(), (int)v->at( v_i )->ApiShortName.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Api::insert");
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
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.4){
			WARN(FL, "Array Insert took longer than 400ms to execute.");
		}

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
twine Api::insert_prepSQL(IOConn& ioc, Api& obj )
{
	EnEx ee(FL, "Api::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into api (guid, projappguid, ApiName) 			values ( ?, ?, ? )";

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

	// Replace the ApiShortName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ApiShortName );
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
			This updates the settings for a given api in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update api
			set ApiName = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Api::update(SqlDB& sqldb, twine& ApiShortName, twine& guid )
{
	EnEx ee(FL, "Api::update()");

	twine stmt = "update api 			set ApiName = ? 			where guid = ?";

	Api::update(sqldb, stmt, true, ApiShortName, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Api::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& ApiShortName, twine& guid )
{
	EnEx ee(FL, "Api::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Api::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, ApiShortName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, ApiShortName(), (int)ApiShortName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Api::update");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
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
twine Api::update_prepSQL(IOConn& ioc, twine& ApiShortName, twine& guid )
{
	EnEx ee(FL, "Api::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update api 			set ApiName = ? 			where guid = ?";

	// Replace the ApiShortName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ApiShortName );
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
			This removes a api by id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from api
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Api::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "Api::deleteByID()");

	twine stmt = "delete from api 			where guid = ?";

	Api::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Api::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "Api::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Api::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Api::deleteByID");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
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
twine Api::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "Api::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from api 			where guid = ?";

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
			This selects all api's for a given application
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projappguid, ApiName
			from api
			where projappguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projappguid
   * ApiShortName
 */
/* ************************************************************************************** */
vector<Api* >* Api::selectAllForApp(SqlDB& sqldb, twine& projappguid)
{
	EnEx ee(FL, "Api::selectAllForApp()");

	twine stmt = "select guid, projappguid, ApiName 			from api 			where projappguid = ?";

	return Api::selectAllForApp(sqldb, stmt, true, projappguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Api* >* Api::selectAllForApp(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projappguid)
{
	EnEx ee(FL, "Api::selectAllForApp(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Api* >, Api::deleteVector> ret = new vector<Api* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, projappguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, projappguid(), (int)projappguid.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Api::selectAllForApp()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Api::selectAllForApp");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Api* obj = new Api( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projappguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->ApiShortName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
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
twine Api::selectAllForApp_prepSQL(IOConn& ioc, twine& projappguid)
{
	EnEx ee(FL, "Api::selectAllForApp_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projappguid, ApiName 			from api 			where projappguid = ?";

	// Replace the projappguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, projappguid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

