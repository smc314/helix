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

#include "ProjectTable.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/ProjectTable.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ProjectTableName = "ProjectTable";

ProjectTable::ProjectTable()
{
	EnEx ee(FL, "ProjectTable::ProjectTable()");

	init();

}

ProjectTable::ProjectTable(const ProjectTable& c)
{
	EnEx ee(FL, "ProjectTable::ProjectTable(const ProjectTable& c)");

	DataName = c.DataName;
	Description = c.Description;
	TableName = c.TableName;
	guid = c.guid;
	projdataguid = c.projdataguid;
	projguid = c.projguid;
	Columns = new vector<TableCol*>();
	for(size_t i = 0; i < c.Columns->size(); i++){
		Columns->push_back( new TableCol( *(c.Columns->at( i )) ) );
	}


}

ProjectTable& ProjectTable::operator=(const ProjectTable& c)
{
	EnEx ee(FL, "ProjectTable::operator=(const ProjectTable& c)");

	DataName = c.DataName;
	Description = c.Description;
	TableName = c.TableName;
	guid = c.guid;
	projdataguid = c.projdataguid;
	projguid = c.projguid;
	Columns = new vector<TableCol*>();
	for(size_t i = 0; i < c.Columns->size(); i++){
		Columns->push_back( new TableCol( *(c.Columns->at( i )) ) );
	}


	return *this;
}

ProjectTable::~ProjectTable()
{
	EnEx ee(FL, "ProjectTable::~ProjectTable()");

}

ProjectTable& ProjectTable::init()
{
	EnEx ee(FL, "ProjectTable::init()");

	DataName.erase();
	Description.erase();
	TableName.erase();
	guid.erase();
	projdataguid.erase();
	projguid.erase();
	Columns = new vector<TableCol*>();


	return *this;
}

ProjectTable& ProjectTable::checkSize()
{
	EnEx ee(FL, "ProjectTable::checkSize()");

	DataName.check_size();
	DataName.rtrim();
	Description.check_size();
	Description.rtrim();
	TableName.check_size();
	TableName.rtrim();
	guid.check_size();
	guid.rtrim();
	projdataguid.check_size();
	projdataguid.rtrim();
	projguid.check_size();
	projguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
ProjectTable::ProjectTable(xmlNodePtr node)
{
	EnEx ee(FL, "ProjectTable::ProjectTable(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
ProjectTable& ProjectTable::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "ProjectTable::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct ProjectTable is NULL.");
	}

	DataName.getAttribute(node, "DataName");
	Description.getAttribute(node, "Description");
	TableName.getAttribute(node, "TableName");
	guid.getAttribute(node, "guid");
	projdataguid.getAttribute(node, "projdataguid");
	projguid.getAttribute(node, "projguid");
	Columns = TableCol::readXmlChildren( XmlHelpers::FindChild( node, "Columns") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr ProjectTable::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "ProjectTable::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectTable::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"ProjectTable", NULL);
	xmlSetProp(child, (const xmlChar*)"DataName", DataName);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"TableName", TableName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projdataguid", projdataguid);
	xmlSetProp(child, (const xmlChar*)"projguid", projguid);
	xmlNodePtr Columns_node = xmlNewChild(child, NULL, (const xmlChar*)"Columns", NULL);
	TableCol::createXmlChildren( Columns_node, Columns );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr ProjectTable::createXmlDoc() const
{
	EnEx ee(FL, "ProjectTable::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"ProjectTable", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"DataName", DataName);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"TableName", TableName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projdataguid", projdataguid);
	xmlSetProp(child, (const xmlChar*)"projguid", projguid);
	xmlNodePtr Columns_node = xmlNewChild(child, NULL, (const xmlChar*)"Columns", NULL);
	TableCol::createXmlChildren( Columns_node, Columns );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<ProjectTable* >* ProjectTable::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "ProjectTable::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectTable::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<ProjectTable* >, ProjectTable::deleteVector> ret = new vector<ProjectTable* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "ProjectTable") == 0){
			ret->push_back( new ProjectTable(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void ProjectTable::createXmlChildren(xmlNodePtr parent, vector<ProjectTable* >* vect)
{
	EnEx ee(FL, "ProjectTable::createXmlChildren(xmlNodePtr parent, vector<ProjectTable* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectTable::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr ProjectTable::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<ProjectTable* >* vect)
{
	EnEx ee(FL, "ProjectTable::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<ProjectTable* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectTable::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	ProjectTable::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void ProjectTable::deleteVector(vector<ProjectTable* >* vect)
{
	EnEx ee(FL, "ProjectTable::deleteVector(vector<ProjectTable* >* vect)");

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
twine& ProjectTable::Name()
{
	return ProjectTableName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new project table entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into projtable (guid, projdataguid, TableName, Description)
			values ( ?, ?, ?, ?)
		 */
/*                                                                                        */
/* ************************************************************************************** */
void ProjectTable::insert(SqlDB& sqldb, ProjectTable& obj )
{
	EnEx ee(FL, "ProjectTable::insert()");

	twine stmt = "insert into projtable (guid, projdataguid, TableName, Description) 			values ( ?, ?, ?, ?)";

	ProjectTable::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void ProjectTable::insert(SqlDB& sqldb, twine& stmt, bool useInputs, ProjectTable& obj )
{
	EnEx ee(FL, "ProjectTable::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectTable::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.projdataguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.projdataguid(), (int)obj.projdataguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.TableName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.TableName(), (int)obj.TableName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.Description(), (int)obj.Description.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectTable::insert");
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
void ProjectTable::insert(SqlDB& sqldb, vector< ProjectTable* >* v, bool useTransaction)
{
	EnEx ee(FL, "ProjectTable::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into projtable (guid, projdataguid, TableName, Description) 			values ( ?, ?, ?, ?)";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectTable::insert()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->projdataguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->projdataguid(), (int)v->at( v_i )->projdataguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->TableName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->TableName(), (int)v->at( v_i )->TableName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->Description(), (int)v->at( v_i )->Description.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for ProjectTable::insert");
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
twine ProjectTable::insert_prepSQL(IOConn& ioc, ProjectTable& obj )
{
	EnEx ee(FL, "ProjectTable::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into projtable (guid, projdataguid, TableName, Description) 			values ( ?, ?, ?, ?)";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the projdataguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.projdataguid );
	}

	// Replace the TableName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.TableName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Description );
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
			This updates the settings for a given project table in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update projtable
			set TableName = ?,
				Description = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void ProjectTable::update(SqlDB& sqldb, twine& TableName, twine& Description, twine& guid )
{
	EnEx ee(FL, "ProjectTable::update()");

	twine stmt = "update projtable 			set TableName = ?, 				Description = ? 			where guid = ?";

	ProjectTable::update(sqldb, stmt, true, TableName, Description, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void ProjectTable::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& TableName, twine& Description, twine& guid )
{
	EnEx ee(FL, "ProjectTable::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectTable::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, TableName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, TableName(), (int)TableName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Description(), (int)Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectTable::update");
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
twine ProjectTable::update_prepSQL(IOConn& ioc, twine& TableName, twine& Description, twine& guid )
{
	EnEx ee(FL, "ProjectTable::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update projtable 			set TableName = ?, 				Description = ? 			where guid = ?";

	// Replace the TableName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, TableName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Description );
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
			This removes a project table by guid
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from projtable
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void ProjectTable::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "ProjectTable::deleteByID()");

	twine stmt = "delete from projtable 			where guid = ?";

	ProjectTable::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void ProjectTable::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "ProjectTable::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectTable::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectTable::deleteByID");
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
twine ProjectTable::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "ProjectTable::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from projtable 			where guid = ?";

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
			This selects all project tables in the database for a given project
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select projtable.guid, project.guid, projdata.guid, projdata.DataName, TableName, projtable.Description
			from project, projdata, projtable
			where project.guid = projdata.projguid
			and   projdata.guid = projtabl.projdataguid
			order by projdata.DataName, TableName
			where project.guid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projguid
   * projdataguid
   * DataName
   * TableName
   * Description
 */
/* ************************************************************************************** */
vector<ProjectTable* >* ProjectTable::selectAllForProject(SqlDB& sqldb, twine& projguid)
{
	EnEx ee(FL, "ProjectTable::selectAllForProject()");

	twine stmt = "select projtable.guid, project.guid, projdata.guid, projdata.DataName, TableName, projtable.Description 			from project, projdata, projtable 			where project.guid = projdata.projguid 			and   projdata.guid = projtabl.projdataguid 			order by projdata.DataName, TableName 			where project.guid = ?";

	return ProjectTable::selectAllForProject(sqldb, stmt, true, projguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<ProjectTable* >* ProjectTable::selectAllForProject(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projguid)
{
	EnEx ee(FL, "ProjectTable::selectAllForProject(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<ProjectTable* >, ProjectTable::deleteVector> ret = new vector<ProjectTable* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, projguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, projguid(), (int)projguid.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectTable::selectAllForProject()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectTable::selectAllForProject");
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
			ProjectTable* obj = new ProjectTable( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->projdataguid.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->DataName.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->TableName.set( (const char*)sqlite3_column_text( db_stmt, 4), (size_t)sqlite3_column_bytes(db_stmt, 4) );
			}
			if( 5 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 5), (size_t)sqlite3_column_bytes(db_stmt, 5) );
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
twine ProjectTable::selectAllForProject_prepSQL(IOConn& ioc, twine& projguid)
{
	EnEx ee(FL, "ProjectTable::selectAllForProject_prepSQL()");

	size_t idx = 0;
	twine stmt = "select projtable.guid, project.guid, projdata.guid, projdata.DataName, TableName, projtable.Description 			from project, projdata, projtable 			where project.guid = projdata.projguid 			and   projdata.guid = projtabl.projdataguid 			order by projdata.DataName, TableName 			where project.guid = ?";

	// Replace the projguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, projguid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

