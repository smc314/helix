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

#include "DOStmt.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/DOStmt.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine DOStmtName = "DOStmt";

DOStmt::DOStmt()
{
	EnEx ee(FL, "DOStmt::DOStmt()");

	init();

}

DOStmt::DOStmt(const DOStmt& c)
{
	EnEx ee(FL, "DOStmt::DOStmt(const DOStmt& c)");

	Comment = c.Comment;
	Sql = c.Sql;
	StmtName = c.StmtName;
	StmtType = c.StmtType;
	doguid = c.doguid;
	guid = c.guid;
	projdataguid = c.projdataguid;
	DOStmtInputs = new vector<DOStmtInput*>();
	for(size_t i = 0; i < c.DOStmtInputs->size(); i++){
		DOStmtInputs->push_back( new DOStmtInput( *(c.DOStmtInputs->at( i )) ) );
	}
	DOStmtOutputs = new vector<DOStmtOutput*>();
	for(size_t i = 0; i < c.DOStmtOutputs->size(); i++){
		DOStmtOutputs->push_back( new DOStmtOutput( *(c.DOStmtOutputs->at( i )) ) );
	}


}

DOStmt& DOStmt::operator=(const DOStmt& c)
{
	EnEx ee(FL, "DOStmt::operator=(const DOStmt& c)");

	Comment = c.Comment;
	Sql = c.Sql;
	StmtName = c.StmtName;
	StmtType = c.StmtType;
	doguid = c.doguid;
	guid = c.guid;
	projdataguid = c.projdataguid;
	DOStmtInputs = new vector<DOStmtInput*>();
	for(size_t i = 0; i < c.DOStmtInputs->size(); i++){
		DOStmtInputs->push_back( new DOStmtInput( *(c.DOStmtInputs->at( i )) ) );
	}
	DOStmtOutputs = new vector<DOStmtOutput*>();
	for(size_t i = 0; i < c.DOStmtOutputs->size(); i++){
		DOStmtOutputs->push_back( new DOStmtOutput( *(c.DOStmtOutputs->at( i )) ) );
	}


	return *this;
}

DOStmt::~DOStmt()
{
	EnEx ee(FL, "DOStmt::~DOStmt()");

}

DOStmt& DOStmt::init()
{
	EnEx ee(FL, "DOStmt::init()");

	Comment.erase();
	Sql.erase();
	StmtName.erase();
	StmtType.erase();
	doguid.erase();
	guid.erase();
	projdataguid.erase();
	DOStmtInputs = new vector<DOStmtInput*>();
	DOStmtOutputs = new vector<DOStmtOutput*>();


	return *this;
}

DOStmt& DOStmt::checkSize()
{
	EnEx ee(FL, "DOStmt::checkSize()");

	Comment.check_size();
	Comment.rtrim();
	Sql.check_size();
	Sql.rtrim();
	StmtName.check_size();
	StmtName.rtrim();
	StmtType.check_size();
	StmtType.rtrim();
	doguid.check_size();
	doguid.rtrim();
	guid.check_size();
	guid.rtrim();
	projdataguid.check_size();
	projdataguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
DOStmt::DOStmt(xmlNodePtr node)
{
	EnEx ee(FL, "DOStmt::DOStmt(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
DOStmt& DOStmt::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "DOStmt::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct DOStmt is NULL.");
	}

	Comment.getAttribute(node, "Comment");
	Sql.getAttribute(node, "Sql");
	StmtName.getAttribute(node, "StmtName");
	StmtType.getAttribute(node, "StmtType");
	doguid.getAttribute(node, "doguid");
	guid.getAttribute(node, "guid");
	projdataguid.getAttribute(node, "projdataguid");
	DOStmtInputs = DOStmtInput::readXmlChildren( XmlHelpers::FindChild( node, "DOStmtInputs") );
	DOStmtOutputs = DOStmtOutput::readXmlChildren( XmlHelpers::FindChild( node, "DOStmtOutputs") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr DOStmt::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "DOStmt::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmt::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"DOStmt", NULL);
	xmlSetProp(child, (const xmlChar*)"Comment", Comment);
	xmlSetProp(child, (const xmlChar*)"Sql", Sql);
	xmlSetProp(child, (const xmlChar*)"StmtName", StmtName);
	xmlSetProp(child, (const xmlChar*)"StmtType", StmtType);
	xmlSetProp(child, (const xmlChar*)"doguid", doguid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projdataguid", projdataguid);
	xmlNodePtr DOStmtInputs_node = xmlNewChild(child, NULL, (const xmlChar*)"DOStmtInputs", NULL);
	DOStmtInput::createXmlChildren( DOStmtInputs_node, DOStmtInputs );

	xmlNodePtr DOStmtOutputs_node = xmlNewChild(child, NULL, (const xmlChar*)"DOStmtOutputs", NULL);
	DOStmtOutput::createXmlChildren( DOStmtOutputs_node, DOStmtOutputs );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr DOStmt::createXmlDoc() const
{
	EnEx ee(FL, "DOStmt::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"DOStmt", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Comment", Comment);
	xmlSetProp(child, (const xmlChar*)"Sql", Sql);
	xmlSetProp(child, (const xmlChar*)"StmtName", StmtName);
	xmlSetProp(child, (const xmlChar*)"StmtType", StmtType);
	xmlSetProp(child, (const xmlChar*)"doguid", doguid);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projdataguid", projdataguid);
	xmlNodePtr DOStmtInputs_node = xmlNewChild(child, NULL, (const xmlChar*)"DOStmtInputs", NULL);
	DOStmtInput::createXmlChildren( DOStmtInputs_node, DOStmtInputs );

	xmlNodePtr DOStmtOutputs_node = xmlNewChild(child, NULL, (const xmlChar*)"DOStmtOutputs", NULL);
	DOStmtOutput::createXmlChildren( DOStmtOutputs_node, DOStmtOutputs );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<DOStmt* >* DOStmt::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "DOStmt::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmt::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<DOStmt* >, DOStmt::deleteVector> ret = new vector<DOStmt* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "DOStmt") == 0){
			ret->push_back( new DOStmt(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void DOStmt::createXmlChildren(xmlNodePtr parent, vector<DOStmt* >* vect)
{
	EnEx ee(FL, "DOStmt::createXmlChildren(xmlNodePtr parent, vector<DOStmt* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmt::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr DOStmt::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<DOStmt* >* vect)
{
	EnEx ee(FL, "DOStmt::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<DOStmt* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to DOStmt::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	DOStmt::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void DOStmt::deleteVector(vector<DOStmt* >* vect)
{
	EnEx ee(FL, "DOStmt::deleteVector(vector<DOStmt* >* vect)");

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
twine& DOStmt::Name()
{
	return DOStmtName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new data object statement entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into dostmt (guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql)
			values ( ?, ?, ?, ?, ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmt::insert(SqlDB& sqldb, DOStmt& obj )
{
	EnEx ee(FL, "DOStmt::insert()");

	twine stmt = "insert into dostmt (guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql) 			values ( ?, ?, ?, ?, ?, ?, ? )";

	DOStmt::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmt::insert(SqlDB& sqldb, twine& stmt, bool useInputs, DOStmt& obj )
{
	EnEx ee(FL, "DOStmt::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmt::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.doguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.doguid(), (int)obj.doguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.StmtName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.StmtName(), (int)obj.StmtName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.StmtType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.StmtType(), (int)obj.StmtType.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, obj.projdataguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, obj.projdataguid(), (int)obj.projdataguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, obj.Comment() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, obj.Comment(), (int)obj.Comment.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 7, obj.Sql() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 7, obj.Sql(), (int)obj.Sql.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmt::insert");
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
void DOStmt::insert(SqlDB& sqldb, vector< DOStmt* >* v, bool useTransaction)
{
	EnEx ee(FL, "DOStmt::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into dostmt (guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql) 			values ( ?, ?, ?, ?, ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmt::insert()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->StmtName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->StmtName(), (int)v->at( v_i )->StmtName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->StmtType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->StmtType(), (int)v->at( v_i )->StmtType.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, v->at( v_i )->projdataguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, v->at( v_i )->projdataguid(), (int)v->at( v_i )->projdataguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, v->at( v_i )->Comment() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, v->at( v_i )->Comment(), (int)v->at( v_i )->Comment.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 7, v->at( v_i )->Sql() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 7, v->at( v_i )->Sql(), (int)v->at( v_i )->Sql.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for DOStmt::insert");
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
twine DOStmt::insert_prepSQL(IOConn& ioc, DOStmt& obj )
{
	EnEx ee(FL, "DOStmt::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into dostmt (guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql) 			values ( ?, ?, ?, ?, ?, ?, ? )";

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

	// Replace the StmtName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.StmtName );
	}

	// Replace the StmtType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.StmtType );
	}

	// Replace the projdataguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.projdataguid );
	}

	// Replace the Comment parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Comment );
	}

	// Replace the Sql parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Sql );
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
			This updates the settings for a given data object statement in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update dostmt
			set StmtName = ?,
				StmtType = ?,
				projdataguid = ?,
				Comment = ?,
				Sql = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmt::update(SqlDB& sqldb, twine& StmtName, twine& StmtType, twine& projdataguid, twine& Comment, twine& Sql, twine& guid )
{
	EnEx ee(FL, "DOStmt::update()");

	twine stmt = "update dostmt 			set StmtName = ?, 				StmtType = ?, 				projdataguid = ?, 				Comment = ?, 				Sql = ? 			where guid = ?";

	DOStmt::update(sqldb, stmt, true, StmtName, StmtType, projdataguid, Comment, Sql, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmt::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& StmtName, twine& StmtType, twine& projdataguid, twine& Comment, twine& Sql, twine& guid )
{
	EnEx ee(FL, "DOStmt::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmt::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, StmtName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, StmtName(), (int)StmtName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, StmtType() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, StmtType(), (int)StmtType.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, projdataguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, projdataguid(), (int)projdataguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, Comment() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, Comment(), (int)Comment.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, Sql() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, Sql(), (int)Sql.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmt::update");
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
twine DOStmt::update_prepSQL(IOConn& ioc, twine& StmtName, twine& StmtType, twine& projdataguid, twine& Comment, twine& Sql, twine& guid )
{
	EnEx ee(FL, "DOStmt::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update dostmt 			set StmtName = ?, 				StmtType = ?, 				projdataguid = ?, 				Comment = ?, 				Sql = ? 			where guid = ?";

	// Replace the StmtName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, StmtName );
	}

	// Replace the StmtType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, StmtType );
	}

	// Replace the projdataguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, projdataguid );
	}

	// Replace the Comment parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Comment );
	}

	// Replace the Sql parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Sql );
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
			This removes a data object statement by id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from dostmt
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmt::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "DOStmt::deleteByID()");

	twine stmt = "delete from dostmt 			where guid = ?";

	DOStmt::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmt::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "DOStmt::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmt::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmt::deleteByID");
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
twine DOStmt::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "DOStmt::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from dostmt 			where guid = ?";

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
			This removes all data object statements for a given data object
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from dostmt
			where doguid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void DOStmt::deleteByDOID(SqlDB& sqldb, twine& doguid )
{
	EnEx ee(FL, "DOStmt::deleteByDOID()");

	twine stmt = "delete from dostmt 			where doguid = ?";

	DOStmt::deleteByDOID(sqldb, stmt, true, doguid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void DOStmt::deleteByDOID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid )
{
	EnEx ee(FL, "DOStmt::deleteByDOID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("DOStmt::deleteByDOID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, doguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, doguid(), (int)doguid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmt::deleteByDOID");
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
twine DOStmt::deleteByDOID_prepSQL(IOConn& ioc, twine& doguid )
{
	EnEx ee(FL, "DOStmt::deleteByDOID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from dostmt 			where doguid = ?";

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
			This selects all data object statements for a given data object
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql
			from dostmt
			where doguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * doguid
   * StmtName
   * StmtType
   * projdataguid
   * Comment
   * Sql
 */
/* ************************************************************************************** */
vector<DOStmt* >* DOStmt::selectAllForDO(SqlDB& sqldb, twine& doguid)
{
	EnEx ee(FL, "DOStmt::selectAllForDO()");

	twine stmt = "select guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql 			from dostmt 			where doguid = ?";

	return DOStmt::selectAllForDO(sqldb, stmt, true, doguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<DOStmt* >* DOStmt::selectAllForDO(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid)
{
	EnEx ee(FL, "DOStmt::selectAllForDO(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<DOStmt* >, DOStmt::deleteVector> ret = new vector<DOStmt* >();

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
			EnEx eeExe("DOStmt::selectAllForDO()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for DOStmt::selectAllForDO");
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
			DOStmt* obj = new DOStmt( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->doguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->StmtName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->StmtType.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->projdataguid.set( (const char*)sqlite3_column_text( db_stmt, 4), (size_t)sqlite3_column_bytes(db_stmt, 4) );
			}
			if( 5 < colCount ){
				obj->Comment.set( (const char*)sqlite3_column_text( db_stmt, 5), (size_t)sqlite3_column_bytes(db_stmt, 5) );
			}
			if( 6 < colCount ){
				obj->Sql.set( (const char*)sqlite3_column_text( db_stmt, 6), (size_t)sqlite3_column_bytes(db_stmt, 6) );
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
twine DOStmt::selectAllForDO_prepSQL(IOConn& ioc, twine& doguid)
{
	EnEx ee(FL, "DOStmt::selectAllForDO_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql 			from dostmt 			where doguid = ?";

	// Replace the doguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, doguid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

