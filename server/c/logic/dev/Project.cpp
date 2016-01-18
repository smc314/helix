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

#include "Project.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/Project.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ProjectName = "Project";

Project::Project()
{
	EnEx ee(FL, "Project::Project()");

	init();

}

Project::Project(const Project& c)
{
	EnEx ee(FL, "Project::Project(const Project& c)");

	Deployment = c.Deployment;
	Description = c.Description;
	Location = c.Location;
	ProjName = c.ProjName;
	ShortName = c.ShortName;
	guid = c.guid;
	Apps = new vector<Application*>();
	for(size_t i = 0; i < c.Apps->size(); i++){
		Apps->push_back( new Application( *(c.Apps->at( i )) ) );
	}
	Data = new vector<ProjectData*>();
	for(size_t i = 0; i < c.Data->size(); i++){
		Data->push_back( new ProjectData( *(c.Data->at( i )) ) );
	}


}

Project& Project::operator=(const Project& c)
{
	EnEx ee(FL, "Project::operator=(const Project& c)");

	Deployment = c.Deployment;
	Description = c.Description;
	Location = c.Location;
	ProjName = c.ProjName;
	ShortName = c.ShortName;
	guid = c.guid;
	Apps = new vector<Application*>();
	for(size_t i = 0; i < c.Apps->size(); i++){
		Apps->push_back( new Application( *(c.Apps->at( i )) ) );
	}
	Data = new vector<ProjectData*>();
	for(size_t i = 0; i < c.Data->size(); i++){
		Data->push_back( new ProjectData( *(c.Data->at( i )) ) );
	}


	return *this;
}

Project::~Project()
{
	EnEx ee(FL, "Project::~Project()");

}

Project& Project::init()
{
	EnEx ee(FL, "Project::init()");

	Deployment.erase();
	Description.erase();
	Location.erase();
	ProjName.erase();
	ShortName.erase();
	guid.erase();
	Apps = new vector<Application*>();
	Data = new vector<ProjectData*>();


	return *this;
}

Project& Project::checkSize()
{
	EnEx ee(FL, "Project::checkSize()");

	Deployment.check_size();
	Deployment.rtrim();
	Description.check_size();
	Description.rtrim();
	Location.check_size();
	Location.rtrim();
	ProjName.check_size();
	ProjName.rtrim();
	ShortName.check_size();
	ShortName.rtrim();
	guid.check_size();
	guid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Project::Project(xmlNodePtr node)
{
	EnEx ee(FL, "Project::Project(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Project& Project::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Project::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Project is NULL.");
	}

	Deployment.getAttribute(node, "Deployment");
	Description.getAttribute(node, "Description");
	Location.getAttribute(node, "Location");
	ProjName.getAttribute(node, "ProjName");
	ShortName.getAttribute(node, "ShortName");
	guid.getAttribute(node, "guid");
	Apps = Application::readXmlChildren( XmlHelpers::FindChild( node, "Apps") );
	Data = ProjectData::readXmlChildren( XmlHelpers::FindChild( node, "Data") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Project::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Project::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Project::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Project", NULL);
	xmlSetProp(child, (const xmlChar*)"Deployment", Deployment);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"Location", Location);
	xmlSetProp(child, (const xmlChar*)"ProjName", ProjName);
	xmlSetProp(child, (const xmlChar*)"ShortName", ShortName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlNodePtr Apps_node = xmlNewChild(child, NULL, (const xmlChar*)"Apps", NULL);
	Application::createXmlChildren( Apps_node, Apps );

	xmlNodePtr Data_node = xmlNewChild(child, NULL, (const xmlChar*)"Data", NULL);
	ProjectData::createXmlChildren( Data_node, Data );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Project::createXmlDoc() const
{
	EnEx ee(FL, "Project::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Project", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Deployment", Deployment);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"Location", Location);
	xmlSetProp(child, (const xmlChar*)"ProjName", ProjName);
	xmlSetProp(child, (const xmlChar*)"ShortName", ShortName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlNodePtr Apps_node = xmlNewChild(child, NULL, (const xmlChar*)"Apps", NULL);
	Application::createXmlChildren( Apps_node, Apps );

	xmlNodePtr Data_node = xmlNewChild(child, NULL, (const xmlChar*)"Data", NULL);
	ProjectData::createXmlChildren( Data_node, Data );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Project* >* Project::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Project::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Project::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Project* >, Project::deleteVector> ret = new vector<Project* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Project") == 0){
			ret->push_back( new Project(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Project::createXmlChildren(xmlNodePtr parent, vector<Project* >* vect)
{
	EnEx ee(FL, "Project::createXmlChildren(xmlNodePtr parent, vector<Project* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Project::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr Project::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Project* >* vect)
{
	EnEx ee(FL, "Project::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Project* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Project::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	Project::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Project::deleteVector(vector<Project* >* vect)
{
	EnEx ee(FL, "Project::deleteVector(vector<Project* >* vect)");

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
twine& Project::Name()
{
	return ProjectName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new project entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into project (guid, ProjName, ShortName, Description, Deployment, Location )
			values ( ?, ?, ?, ?, ?, ?)
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Project::insert(SqlDB& sqldb, Project& obj )
{
	EnEx ee(FL, "Project::insert()");

	twine stmt = "insert into project (guid, ProjName, ShortName, Description, Deployment, Location ) 			values ( ?, ?, ?, ?, ?, ?)";

	Project::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Project::insert(SqlDB& sqldb, twine& stmt, bool useInputs, Project& obj )
{
	EnEx ee(FL, "Project::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Project::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.ProjName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.ProjName(), (int)obj.ProjName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.ShortName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.ShortName(), (int)obj.ShortName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.Description(), (int)obj.Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, obj.Deployment() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, obj.Deployment(), (int)obj.Deployment.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, obj.Location() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, obj.Location(), (int)obj.Location.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Project::insert");
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
void Project::insert(SqlDB& sqldb, vector< Project* >* v, bool useTransaction)
{
	EnEx ee(FL, "Project::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into project (guid, ProjName, ShortName, Description, Deployment, Location ) 			values ( ?, ?, ?, ?, ?, ?)";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Project::insert()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->ProjName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->ProjName(), (int)v->at( v_i )->ProjName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->ShortName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->ShortName(), (int)v->at( v_i )->ShortName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->Description(), (int)v->at( v_i )->Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, v->at( v_i )->Deployment() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, v->at( v_i )->Deployment(), (int)v->at( v_i )->Deployment.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, v->at( v_i )->Location() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, v->at( v_i )->Location(), (int)v->at( v_i )->Location.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Project::insert");
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
twine Project::insert_prepSQL(IOConn& ioc, Project& obj )
{
	EnEx ee(FL, "Project::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into project (guid, ProjName, ShortName, Description, Deployment, Location ) 			values ( ?, ?, ?, ?, ?, ?)";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the ProjName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ProjName );
	}

	// Replace the ShortName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ShortName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Description );
	}

	// Replace the Deployment parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Deployment );
	}

	// Replace the Location parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Location );
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
			This updates the settings for a given project in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update project
			set ProjName = ?,
				ShortName = ?,
				Description = ?,
				Deployment = ?,
				Location = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Project::update(SqlDB& sqldb, twine& ProjName, twine& ShortName, twine& Description, twine& Deployment, twine& Location, twine& guid )
{
	EnEx ee(FL, "Project::update()");

	twine stmt = "update project 			set ProjName = ?, 				ShortName = ?, 				Description = ?, 				Deployment = ?, 				Location = ? 			where guid = ?";

	Project::update(sqldb, stmt, true, ProjName, ShortName, Description, Deployment, Location, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Project::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& ProjName, twine& ShortName, twine& Description, twine& Deployment, twine& Location, twine& guid )
{
	EnEx ee(FL, "Project::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Project::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, ProjName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, ProjName(), (int)ProjName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, ShortName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, ShortName(), (int)ShortName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, Description(), (int)Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, Deployment() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, Deployment(), (int)Deployment.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, Location() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, Location(), (int)Location.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Project::update");
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
twine Project::update_prepSQL(IOConn& ioc, twine& ProjName, twine& ShortName, twine& Description, twine& Deployment, twine& Location, twine& guid )
{
	EnEx ee(FL, "Project::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update project 			set ProjName = ?, 				ShortName = ?, 				Description = ?, 				Deployment = ?, 				Location = ? 			where guid = ?";

	// Replace the ProjName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ProjName );
	}

	// Replace the ShortName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ShortName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Description );
	}

	// Replace the Deployment parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Deployment );
	}

	// Replace the Location parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Location );
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
			This removes a project by guid
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from project
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Project::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "Project::deleteByID()");

	twine stmt = "delete from project 			where guid = ?";

	Project::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Project::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "Project::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Project::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Project::deleteByID");
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
twine Project::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "Project::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from project 			where guid = ?";

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
			This selects all projects in the database
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, ProjName, ShortName, Description, Deployment, Location
			from project
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * ProjName
   * ShortName
   * Description
   * Deployment
   * Location
 */
/* ************************************************************************************** */
vector<Project* >* Project::selectAll(SqlDB& sqldb)
{
	EnEx ee(FL, "Project::selectAll()");

	twine stmt = "select guid, ProjName, ShortName, Description, Deployment, Location 			from project";

	return Project::selectAll(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Project* >* Project::selectAll(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "Project::selectAll(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Project* >, Project::deleteVector> ret = new vector<Project* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Project::selectAll()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Project::selectAll");
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
			Project* obj = new Project( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->ProjName.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->ShortName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Deployment.set( (const char*)sqlite3_column_text( db_stmt, 4), (size_t)sqlite3_column_bytes(db_stmt, 4) );
			}
			if( 5 < colCount ){
				obj->Location.set( (const char*)sqlite3_column_text( db_stmt, 5), (size_t)sqlite3_column_bytes(db_stmt, 5) );
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
twine Project::selectAll_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "Project::selectAll_prepSQL()");

	twine stmt = "select guid, ProjName, ShortName, Description, Deployment, Location 			from project";

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
			This selects a single project by id
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, ProjName, ShortName, Description, Deployment, Location
			from project
			where guid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * ProjName
   * ShortName
   * Description
   * Deployment
   * Location
 */
/* ************************************************************************************** */
vector<Project* >* Project::selectByID(SqlDB& sqldb, twine& guid)
{
	EnEx ee(FL, "Project::selectByID()");

	twine stmt = "select guid, ProjName, ShortName, Description, Deployment, Location 			from project 			where guid = ?";

	return Project::selectByID(sqldb, stmt, true, guid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Project* >* Project::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid)
{
	EnEx ee(FL, "Project::selectByID(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Project* >, Project::deleteVector> ret = new vector<Project* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Project::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Project::selectByID");
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
			Project* obj = new Project( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->ProjName.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->ShortName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Deployment.set( (const char*)sqlite3_column_text( db_stmt, 4), (size_t)sqlite3_column_bytes(db_stmt, 4) );
			}
			if( 5 < colCount ){
				obj->Location.set( (const char*)sqlite3_column_text( db_stmt, 5), (size_t)sqlite3_column_bytes(db_stmt, 5) );
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
twine Project::selectByID_prepSQL(IOConn& ioc, twine& guid)
{
	EnEx ee(FL, "Project::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, ProjName, ShortName, Description, Deployment, Location 			from project 			where guid = ?";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, guid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

