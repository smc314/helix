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

#include "DOStmtOutput.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/DOStmtOutput.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine DOStmtOutputName = "DOStmtOutput";

DOStmtOutput::DOStmtOutput()
{
	EnEx ee(FL, "DOStmtOutput::DOStmtOutput()");

	init();

}

DOStmtOutput::DOStmtOutput(const DOStmtOutput& c)
{
	EnEx ee(FL, "DOStmtOutput::DOStmtOutput(const DOStmtOutput& c)");

	VarName = c.VarName;
	VarType = c.VarType;
	dostmtguid = c.dostmtguid;
	guid = c.guid;


}

DOStmtOutput& DOStmtOutput::operator=(const DOStmtOutput& c)
{
	EnEx ee(FL, "DOStmtOutput::operator=(const DOStmtOutput& c)");

	VarName = c.VarName;
	VarType = c.VarType;
	dostmtguid = c.dostmtguid;
	guid = c.guid;


	return *this;
}

DOStmtOutput::~DOStmtOutput()
{
	EnEx ee(FL, "DOStmtOutput::~DOStmtOutput()");

}

DOStmtOutput& DOStmtOutput::init()
{
	EnEx ee(FL, "DOStmtOutput::init()");

	VarName.erase();
	VarType.erase();
	dostmtguid.erase();
	guid.erase();


	return *this;
}

DOStmtOutput& DOStmtOutput::checkSize()
{
	EnEx ee(FL, "DOStmtOutput::checkSize()");

	VarName.check_size();
	VarName.rtrim();
	VarType.check_size();
	VarType.rtrim();
	dostmtguid.check_size();
	dostmtguid.rtrim();
	guid.check_size();
	guid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
DOStmtOutput::DOStmtOutput(xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtOutput::DOStmtOutput(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
DOStmtOutput& DOStmtOutput::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "DOStmtOutput::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct DOStmtOutput is NULL.");
	}

	VarName.getAttribute(node, "VarName");
	VarType.getAttribute(node, "VarType");
	dostmtguid.getAttribute(node, "dostmtguid");
	guid.getAttribute(node, "guid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr DOStmtOutput::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "DOStmtOutput::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmtOutput::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"DOStmtOutput", NULL);
	xmlSetProp(child, (const xmlChar*)"VarName", VarName);
	xmlSetProp(child, (const xmlChar*)"VarType", VarType);
	xmlSetProp(child, (const xmlChar*)"dostmtguid", dostmtguid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr DOStmtOutput::createXmlDoc() const
{
	EnEx ee(FL, "DOStmtOutput::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"DOStmtOutput", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"VarName", VarName);
	xmlSetProp(child, (const xmlChar*)"VarType", VarType);
	xmlSetProp(child, (const xmlChar*)"dostmtguid", dostmtguid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<DOStmtOutput* >* DOStmtOutput::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "DOStmtOutput::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmtOutput::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<DOStmtOutput* >, DOStmtOutput::deleteVector> ret = new vector<DOStmtOutput* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "DOStmtOutput") == 0){
			ret->push_back( new DOStmtOutput(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void DOStmtOutput::createXmlChildren(xmlNodePtr parent, vector<DOStmtOutput* >* vect)
{
	EnEx ee(FL, "DOStmtOutput::createXmlChildren(xmlNodePtr parent, vector<DOStmtOutput* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmtOutput::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void DOStmtOutput::deleteVector(vector<DOStmtOutput* >* vect)
{
	EnEx ee(FL, "DOStmtOutput::deleteVector(vector<DOStmtOutput* >* vect)");

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
twine& DOStmtOutput::Name()
{
	return DOStmtOutputName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new data object statement output entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into dostmtoutput (guid, dostmtguid, VarName, VarType)
			values ( ?, ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmtOutput::insert(SqlDB& sqldb, DOStmtOutput& obj )
{
	EnEx ee(FL, "DOStmtOutput::insert()");

	twine stmt = "insert into dostmtoutput (guid, dostmtguid, VarName, VarType) 			values ( ?, ?, ?, ? )";

	DOStmtOutput::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmtOutput::insert(SqlDB& sqldb, twine& stmt, bool useInputs, DOStmtOutput& obj )
{
	EnEx ee(FL, "DOStmtOutput::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmtOutput::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.dostmtguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.dostmtguid(), (int)obj.dostmtguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.VarName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.VarName(), (int)obj.VarName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.VarType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.VarType(), (int)obj.VarType.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmtOutput::insert");
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
void DOStmtOutput::insert(SqlDB& sqldb, vector< DOStmtOutput* >* v)
{
	EnEx ee(FL, "DOStmtOutput::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into dostmtoutput (guid, dostmtguid, VarName, VarType) 			values ( ?, ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmtOutput::insert()-BindExecStmt");

			// Begin our transaction here:
			DEBUG(FL, "Beginning the vector insert transaction" );
			twine beginSql = "begin transaction;";
			sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
			sqldb.check_err( sqlite3_step( db_begin ) );

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->guid(), (int)v->at( v_i )->guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->dostmtguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->dostmtguid(), (int)v->at( v_i )->dostmtguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->VarName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->VarName(), (int)v->at( v_i )->VarName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->VarType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->VarType(), (int)v->at( v_i )->VarType.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for DOStmtOutput::insert");
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
twine DOStmtOutput::insert_prepSQL(IOConn& ioc, DOStmtOutput& obj )
{
	EnEx ee(FL, "DOStmtOutput::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into dostmtoutput (guid, dostmtguid, VarName, VarType) 			values ( ?, ?, ?, ? )";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the dostmtguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.dostmtguid );
	}

	// Replace the VarName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.VarName );
	}

	// Replace the VarType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.VarType );
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
			This updates the settings for a given data object statement output in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update dostmtoutput
			set VarName = ?,
				VarType = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmtOutput::update(SqlDB& sqldb, twine& VarName, twine& VarType, twine& guid )
{
	EnEx ee(FL, "DOStmtOutput::update()");

	twine stmt = "update dostmtoutput 			set VarName = ?, 				VarType = ? 			where guid = ?";

	DOStmtOutput::update(sqldb, stmt, true, VarName, VarType, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmtOutput::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& VarName, twine& VarType, twine& guid )
{
	EnEx ee(FL, "DOStmtOutput::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmtOutput::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, VarName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, VarName(), (int)VarName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, VarType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, VarType(), (int)VarType.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmtOutput::update");
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
twine DOStmtOutput::update_prepSQL(IOConn& ioc, twine& VarName, twine& VarType, twine& guid )
{
	EnEx ee(FL, "DOStmtOutput::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update dostmtoutput 			set VarName = ?, 				VarType = ? 			where guid = ?";

	// Replace the VarName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, VarName );
	}

	// Replace the VarType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, VarType );
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
			This removes a data object statement output by id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from dostmtoutput
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmtOutput::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "DOStmtOutput::deleteByID()");

	twine stmt = "delete from dostmtoutput 			where guid = ?";

	DOStmtOutput::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmtOutput::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "DOStmtOutput::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmtOutput::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmtOutput::deleteByID");
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
twine DOStmtOutput::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "DOStmtOutput::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from dostmtoutput 			where guid = ?";

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
			This removes all data object statement outputs for a given data object statement
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from dostmtoutput
			where dostmtguid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmtOutput::deleteByStmtID(SqlDB& sqldb, twine& dostmtguid )
{
	EnEx ee(FL, "DOStmtOutput::deleteByStmtID()");

	twine stmt = "delete from dostmtoutput 			where dostmtguid = ?";

	DOStmtOutput::deleteByStmtID(sqldb, stmt, true, dostmtguid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmtOutput::deleteByStmtID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& dostmtguid )
{
	EnEx ee(FL, "DOStmtOutput::deleteByStmtID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmtOutput::deleteByStmtID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, dostmtguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, dostmtguid(), (int)dostmtguid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmtOutput::deleteByStmtID");
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
twine DOStmtOutput::deleteByStmtID_prepSQL(IOConn& ioc, twine& dostmtguid )
{
	EnEx ee(FL, "DOStmtOutput::deleteByStmtID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from dostmtoutput 			where dostmtguid = ?";

	// Replace the dostmtguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, dostmtguid );
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
			This selects all data object statement outputs for a given data object stmt
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, dostmtguid, VarName, VarType
			from dostmtoutput
			where dostmtguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * dostmtguid
   * VarName
   * VarType
 */
/* ************************************************************************************** */
vector<DOStmtOutput* >* DOStmtOutput::selectAllForDOStmt(SqlDB& sqldb, twine& dostmtguid)
{
	EnEx ee(FL, "DOStmtOutput::selectAllForDOStmt()");

	twine stmt = "select guid, dostmtguid, VarName, VarType 			from dostmtoutput 			where dostmtguid = ?";

	return DOStmtOutput::selectAllForDOStmt(sqldb, stmt, true, dostmtguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<DOStmtOutput* >* DOStmtOutput::selectAllForDOStmt(SqlDB& sqldb, twine& stmt, bool useInputs, twine& dostmtguid)
{
	EnEx ee(FL, "DOStmtOutput::selectAllForDOStmt(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<DOStmtOutput* >, DOStmtOutput::deleteVector> ret = new vector<DOStmtOutput* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, dostmtguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, dostmtguid(), (int)dostmtguid.length(), SQLITE_STATIC) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmtOutput::selectAllForDOStmt()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmtOutput::selectAllForDOStmt");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			DOStmtOutput* obj = new DOStmtOutput( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->dostmtguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->VarName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->VarType.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
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
twine DOStmtOutput::selectAllForDOStmt_prepSQL(IOConn& ioc, twine& dostmtguid)
{
	EnEx ee(FL, "DOStmtOutput::selectAllForDOStmt_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, dostmtguid, VarName, VarType 			from dostmtoutput 			where dostmtguid = ?";

	// Replace the dostmtguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, dostmtguid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

