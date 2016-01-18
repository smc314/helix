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

#include "DOChild.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/DOChild.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine DOChildName = "DOChild";

DOChild::DOChild()
{
	EnEx ee(FL, "DOChild::DOChild()");

	init();

}

DOChild::DOChild(const DOChild& c)
{
	EnEx ee(FL, "DOChild::DOChild(const DOChild& c)");

	VectorName = c.VectorName;
	VectorType = c.VectorType;
	doguid = c.doguid;
	guid = c.guid;


}

DOChild& DOChild::operator=(const DOChild& c)
{
	EnEx ee(FL, "DOChild::operator=(const DOChild& c)");

	VectorName = c.VectorName;
	VectorType = c.VectorType;
	doguid = c.doguid;
	guid = c.guid;


	return *this;
}

DOChild::~DOChild()
{
	EnEx ee(FL, "DOChild::~DOChild()");

}

DOChild& DOChild::init()
{
	EnEx ee(FL, "DOChild::init()");

	VectorName.erase();
	VectorType.erase();
	doguid.erase();
	guid.erase();


	return *this;
}

DOChild& DOChild::checkSize()
{
	EnEx ee(FL, "DOChild::checkSize()");

	VectorName.check_size();
	VectorName.rtrim();
	VectorType.check_size();
	VectorType.rtrim();
	doguid.check_size();
	doguid.rtrim();
	guid.check_size();
	guid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
DOChild::DOChild(xmlNodePtr node)
{
	EnEx ee(FL, "DOChild::DOChild(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
DOChild& DOChild::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "DOChild::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct DOChild is NULL.");
	}

	VectorName.getAttribute(node, "VectorName");
	VectorType.getAttribute(node, "VectorType");
	doguid.getAttribute(node, "doguid");
	guid.getAttribute(node, "guid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr DOChild::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "DOChild::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOChild::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"DOChild", NULL);
	xmlSetProp(child, (const xmlChar*)"VectorName", VectorName);
	xmlSetProp(child, (const xmlChar*)"VectorType", VectorType);
	xmlSetProp(child, (const xmlChar*)"doguid", doguid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr DOChild::createXmlDoc() const
{
	EnEx ee(FL, "DOChild::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"DOChild", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"VectorName", VectorName);
	xmlSetProp(child, (const xmlChar*)"VectorType", VectorType);
	xmlSetProp(child, (const xmlChar*)"doguid", doguid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<DOChild* >* DOChild::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "DOChild::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOChild::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<DOChild* >, DOChild::deleteVector> ret = new vector<DOChild* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "DOChild") == 0){
			ret->push_back( new DOChild(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void DOChild::createXmlChildren(xmlNodePtr parent, vector<DOChild* >* vect)
{
	EnEx ee(FL, "DOChild::createXmlChildren(xmlNodePtr parent, vector<DOChild* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOChild::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr DOChild::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<DOChild* >* vect)
{
	EnEx ee(FL, "DOChild::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<DOChild* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOChild::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	DOChild::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void DOChild::deleteVector(vector<DOChild* >* vect)
{
	EnEx ee(FL, "DOChild::deleteVector(vector<DOChild* >* vect)");

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
twine& DOChild::Name()
{
	return DOChildName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new data object child entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into dochildvect (guid, doguid, VectorName, VectorType)
			values ( ?, ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOChild::insert(SqlDB& sqldb, DOChild& obj )
{
	EnEx ee(FL, "DOChild::insert()");

	twine stmt = "insert into dochildvect (guid, doguid, VectorName, VectorType) 			values ( ?, ?, ?, ? )";

	DOChild::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOChild::insert(SqlDB& sqldb, twine& stmt, bool useInputs, DOChild& obj )
{
	EnEx ee(FL, "DOChild::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOChild::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.doguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.doguid(), (int)obj.doguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.VectorName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.VectorName(), (int)obj.VectorName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.VectorType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.VectorType(), (int)obj.VectorType.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOChild::insert");
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
void DOChild::insert(SqlDB& sqldb, vector< DOChild* >* v, bool useTransaction)
{
	EnEx ee(FL, "DOChild::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into dochildvect (guid, doguid, VectorName, VectorType) 			values ( ?, ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOChild::insert()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->doguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->doguid(), (int)v->at( v_i )->doguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->VectorName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->VectorName(), (int)v->at( v_i )->VectorName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->VectorType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->VectorType(), (int)v->at( v_i )->VectorType.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for DOChild::insert");
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
twine DOChild::insert_prepSQL(IOConn& ioc, DOChild& obj )
{
	EnEx ee(FL, "DOChild::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into dochildvect (guid, doguid, VectorName, VectorType) 			values ( ?, ?, ?, ? )";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the doguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.doguid );
	}

	// Replace the VectorName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.VectorName );
	}

	// Replace the VectorType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.VectorType );
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
			This updates the settings for a given data object child in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update dochildvect
			set VectorName = ?,
				VectorType = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOChild::update(SqlDB& sqldb, twine& VectorName, twine& VectorType, twine& guid )
{
	EnEx ee(FL, "DOChild::update()");

	twine stmt = "update dochildvect 			set VectorName = ?, 				VectorType = ? 			where guid = ?";

	DOChild::update(sqldb, stmt, true, VectorName, VectorType, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOChild::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& VectorName, twine& VectorType, twine& guid )
{
	EnEx ee(FL, "DOChild::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOChild::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, VectorName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, VectorName(), (int)VectorName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, VectorType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, VectorType(), (int)VectorType.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOChild::update");
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
twine DOChild::update_prepSQL(IOConn& ioc, twine& VectorName, twine& VectorType, twine& guid )
{
	EnEx ee(FL, "DOChild::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update dochildvect 			set VectorName = ?, 				VectorType = ? 			where guid = ?";

	// Replace the VectorName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, VectorName );
	}

	// Replace the VectorType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, VectorType );
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
			This removes a data object child by id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from dochildvect
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOChild::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "DOChild::deleteByID()");

	twine stmt = "delete from dochildvect 			where guid = ?";

	DOChild::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOChild::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "DOChild::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOChild::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOChild::deleteByID");
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
twine DOChild::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "DOChild::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from dochildvect 			where guid = ?";

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
			This removes all data object children for the given data object id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from dochildvect
			where doguid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOChild::deleteByDOID(SqlDB& sqldb, twine& doguid )
{
	EnEx ee(FL, "DOChild::deleteByDOID()");

	twine stmt = "delete from dochildvect 			where doguid = ?";

	DOChild::deleteByDOID(sqldb, stmt, true, doguid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOChild::deleteByDOID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid )
{
	EnEx ee(FL, "DOChild::deleteByDOID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOChild::deleteByDOID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, doguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, doguid(), (int)doguid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOChild::deleteByDOID");
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
twine DOChild::deleteByDOID_prepSQL(IOConn& ioc, twine& doguid )
{
	EnEx ee(FL, "DOChild::deleteByDOID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from dochildvect 			where doguid = ?";

	// Replace the doguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, doguid );
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
			This selects all data objects children for a given data object
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, doguid, VectorName, VectorType
			from dochildvect
			where doguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * doguid
   * VectorName
   * VectorType
 */
/* ************************************************************************************** */
vector<DOChild* >* DOChild::selectAllForDO(SqlDB& sqldb, twine& doguid)
{
	EnEx ee(FL, "DOChild::selectAllForDO()");

	twine stmt = "select guid, doguid, VectorName, VectorType 			from dochildvect 			where doguid = ?";

	return DOChild::selectAllForDO(sqldb, stmt, true, doguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<DOChild* >* DOChild::selectAllForDO(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid)
{
	EnEx ee(FL, "DOChild::selectAllForDO(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<DOChild* >, DOChild::deleteVector> ret = new vector<DOChild* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, doguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, doguid(), (int)doguid.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOChild::selectAllForDO()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOChild::selectAllForDO");
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
			DOChild* obj = new DOChild( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->doguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->VectorName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->VectorType.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
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
twine DOChild::selectAllForDO_prepSQL(IOConn& ioc, twine& doguid)
{
	EnEx ee(FL, "DOChild::selectAllForDO_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, doguid, VectorName, VectorType 			from dochildvect 			where doguid = ?";

	// Replace the doguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, doguid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

