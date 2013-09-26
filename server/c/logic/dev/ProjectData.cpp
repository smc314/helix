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

#include "ProjectData.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/ProjectData.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ProjectDataName = "ProjectData";

ProjectData::ProjectData()
{
	EnEx ee(FL, "ProjectData::ProjectData()");

	init();

}

ProjectData::ProjectData(const ProjectData& c)
{
	EnEx ee(FL, "ProjectData::ProjectData(const ProjectData& c)");

	ConnectionString = c.ConnectionString;
	DataName = c.DataName;
	DataType = c.DataType;
	Deployment = c.Deployment;
	Description = c.Description;
	DevTimePass = c.DevTimePass;
	DevTimeUser = c.DevTimeUser;
	Location = c.Location;
	ProjName = c.ProjName;
	ShortName = c.ShortName;
	guid = c.guid;
	projguid = c.projguid;
	Tables = new vector<ProjectTable*>();
	for(size_t i = 0; i < c.Tables->size(); i++){
		Tables->push_back( new ProjectTable( *(c.Tables->at( i )) ) );
	}


}

ProjectData& ProjectData::operator=(const ProjectData& c)
{
	EnEx ee(FL, "ProjectData::operator=(const ProjectData& c)");

	ConnectionString = c.ConnectionString;
	DataName = c.DataName;
	DataType = c.DataType;
	Deployment = c.Deployment;
	Description = c.Description;
	DevTimePass = c.DevTimePass;
	DevTimeUser = c.DevTimeUser;
	Location = c.Location;
	ProjName = c.ProjName;
	ShortName = c.ShortName;
	guid = c.guid;
	projguid = c.projguid;
	Tables = new vector<ProjectTable*>();
	for(size_t i = 0; i < c.Tables->size(); i++){
		Tables->push_back( new ProjectTable( *(c.Tables->at( i )) ) );
	}


	return *this;
}

ProjectData::~ProjectData()
{
	EnEx ee(FL, "ProjectData::~ProjectData()");

}

ProjectData& ProjectData::init()
{
	EnEx ee(FL, "ProjectData::init()");

	ConnectionString.erase();
	DataName.erase();
	DataType = 0;
	Deployment.erase();
	Description.erase();
	DevTimePass.erase();
	DevTimeUser.erase();
	Location.erase();
	ProjName.erase();
	ShortName.erase();
	guid.erase();
	projguid.erase();
	Tables = new vector<ProjectTable*>();


	return *this;
}

ProjectData& ProjectData::checkSize()
{
	EnEx ee(FL, "ProjectData::checkSize()");

	ConnectionString.check_size();
	ConnectionString.rtrim();
	DataName.check_size();
	DataName.rtrim();
	Deployment.check_size();
	Deployment.rtrim();
	Description.check_size();
	Description.rtrim();
	DevTimePass.check_size();
	DevTimePass.rtrim();
	DevTimeUser.check_size();
	DevTimeUser.rtrim();
	Location.check_size();
	Location.rtrim();
	ProjName.check_size();
	ProjName.rtrim();
	ShortName.check_size();
	ShortName.rtrim();
	guid.check_size();
	guid.rtrim();
	projguid.check_size();
	projguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
ProjectData::ProjectData(xmlNodePtr node)
{
	EnEx ee(FL, "ProjectData::ProjectData(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
ProjectData& ProjectData::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "ProjectData::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct ProjectData is NULL.");
	}

	ConnectionString.getAttribute(node, "ConnectionString");
	DataName.getAttribute(node, "DataName");
	DataType = XmlHelpers::getIntAttr(node, "DataType");
	Deployment.getAttribute(node, "Deployment");
	Description.getAttribute(node, "Description");
	DevTimePass.getAttribute(node, "DevTimePass");
	DevTimeUser.getAttribute(node, "DevTimeUser");
	Location.getAttribute(node, "Location");
	ProjName.getAttribute(node, "ProjName");
	ShortName.getAttribute(node, "ShortName");
	guid.getAttribute(node, "guid");
	projguid.getAttribute(node, "projguid");
	Tables = ProjectTable::readXmlChildren( XmlHelpers::FindChild( node, "Tables") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr ProjectData::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "ProjectData::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectData::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"ProjectData", NULL);
	xmlSetProp(child, (const xmlChar*)"ConnectionString", ConnectionString);
	xmlSetProp(child, (const xmlChar*)"DataName", DataName);
	XmlHelpers::setIntAttr(child, "DataType", DataType);
	xmlSetProp(child, (const xmlChar*)"Deployment", Deployment);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"DevTimePass", DevTimePass);
	xmlSetProp(child, (const xmlChar*)"DevTimeUser", DevTimeUser);
	xmlSetProp(child, (const xmlChar*)"Location", Location);
	xmlSetProp(child, (const xmlChar*)"ProjName", ProjName);
	xmlSetProp(child, (const xmlChar*)"ShortName", ShortName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projguid", projguid);
	xmlNodePtr Tables_node = xmlNewChild(child, NULL, (const xmlChar*)"Tables", NULL);
	ProjectTable::createXmlChildren( Tables_node, Tables );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr ProjectData::createXmlDoc() const
{
	EnEx ee(FL, "ProjectData::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"ProjectData", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"ConnectionString", ConnectionString);
	xmlSetProp(child, (const xmlChar*)"DataName", DataName);
	XmlHelpers::setIntAttr(child, "DataType", DataType);
	xmlSetProp(child, (const xmlChar*)"Deployment", Deployment);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"DevTimePass", DevTimePass);
	xmlSetProp(child, (const xmlChar*)"DevTimeUser", DevTimeUser);
	xmlSetProp(child, (const xmlChar*)"Location", Location);
	xmlSetProp(child, (const xmlChar*)"ProjName", ProjName);
	xmlSetProp(child, (const xmlChar*)"ShortName", ShortName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projguid", projguid);
	xmlNodePtr Tables_node = xmlNewChild(child, NULL, (const xmlChar*)"Tables", NULL);
	ProjectTable::createXmlChildren( Tables_node, Tables );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<ProjectData* >* ProjectData::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "ProjectData::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectData::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<ProjectData* >, ProjectData::deleteVector> ret = new vector<ProjectData* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "ProjectData") == 0){
			ret->push_back( new ProjectData(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void ProjectData::createXmlChildren(xmlNodePtr parent, vector<ProjectData* >* vect)
{
	EnEx ee(FL, "ProjectData::createXmlChildren(xmlNodePtr parent, vector<ProjectData* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to ProjectData::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void ProjectData::deleteVector(vector<ProjectData* >* vect)
{
	EnEx ee(FL, "ProjectData::deleteVector(vector<ProjectData* >* vect)");

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
twine& ProjectData::Name()
{
	return ProjectDataName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new project data entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into projdata (guid, projguid, DataName, Description, DataType, 
				ConnectionString, DevTimeUser, DevTimePass)
			values ( ?, ?, ?, ?, ?,
				?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void ProjectData::insert(SqlDB& sqldb, ProjectData& obj )
{
	EnEx ee(FL, "ProjectData::insert()");

	twine stmt = "insert into projdata (guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass) 			values ( ?, ?, ?, ?, ?, 				?, ?, ? )";

	ProjectData::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void ProjectData::insert(SqlDB& sqldb, twine& stmt, bool useInputs, ProjectData& obj )
{
	EnEx ee(FL, "ProjectData::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectData::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.projguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.projguid(), (int)obj.projguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.DataName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.DataName(), (int)obj.DataName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.Description(), (int)obj.Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, obj.DataType );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)obj.DataType) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, obj.ConnectionString() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, obj.ConnectionString(), (int)obj.ConnectionString.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 7, obj.DevTimeUser() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 7, obj.DevTimeUser(), (int)obj.DevTimeUser.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 8, obj.DevTimePass() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 8, obj.DevTimePass(), (int)obj.DevTimePass.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectData::insert");
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
void ProjectData::insert(SqlDB& sqldb, vector< ProjectData* >* v)
{
	EnEx ee(FL, "ProjectData::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into projdata (guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass) 			values ( ?, ?, ?, ?, ?, 				?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectData::insert()-BindExecStmt");

			// Begin our transaction here:
			DEBUG(FL, "Beginning the vector insert transaction" );
			twine beginSql = "begin transaction;";
			sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
			sqldb.check_err( sqlite3_step( db_begin ) );

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->guid(), (int)v->at( v_i )->guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->projguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->projguid(), (int)v->at( v_i )->projguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->DataName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->DataName(), (int)v->at( v_i )->DataName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->Description(), (int)v->at( v_i )->Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, v->at( v_i )->DataType );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)v->at( v_i )->DataType) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, v->at( v_i )->ConnectionString() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, v->at( v_i )->ConnectionString(), (int)v->at( v_i )->ConnectionString.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 7, v->at( v_i )->DevTimeUser() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 7, v->at( v_i )->DevTimeUser(), (int)v->at( v_i )->DevTimeUser.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 8, v->at( v_i )->DevTimePass() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 8, v->at( v_i )->DevTimePass(), (int)v->at( v_i )->DevTimePass.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for ProjectData::insert");
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
twine ProjectData::insert_prepSQL(IOConn& ioc, ProjectData& obj )
{
	EnEx ee(FL, "ProjectData::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into projdata (guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass) 			values ( ?, ?, ?, ?, ?, 				?, ?, ? )";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.guid );
	}

	// Replace the projguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.projguid );
	}

	// Replace the DataName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.DataName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Description );
	}

	// Replace the DataType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.DataType;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ConnectionString parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.ConnectionString );
	}

	// Replace the DevTimeUser parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.DevTimeUser );
	}

	// Replace the DevTimePass parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.DevTimePass );
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
			This updates the settings for a given project data entry in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update projdata
			set DataName = ?,
				Description = ?,
				DataType = ?,
				ConnectionString = ?,
				DevTimeUser = ?,
				DevTimePass = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void ProjectData::update(SqlDB& sqldb, twine& DataName, twine& Description, intptr_t DataType, twine& ConnectionString, twine& DevTimeUser, twine& DevTimePass, twine& guid )
{
	EnEx ee(FL, "ProjectData::update()");

	twine stmt = "update projdata 			set DataName = ?, 				Description = ?, 				DataType = ?, 				ConnectionString = ?, 				DevTimeUser = ?, 				DevTimePass = ? 			where guid = ?";

	ProjectData::update(sqldb, stmt, true, DataName, Description, DataType, ConnectionString, DevTimeUser, DevTimePass, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void ProjectData::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& DataName, twine& Description, intptr_t DataType, twine& ConnectionString, twine& DevTimeUser, twine& DevTimePass, twine& guid )
{
	EnEx ee(FL, "ProjectData::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectData::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, DataName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, DataName(), (int)DataName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Description(), (int)Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, DataType );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)DataType) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, ConnectionString() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, ConnectionString(), (int)ConnectionString.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, DevTimeUser() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, DevTimeUser(), (int)DevTimeUser.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 6, DevTimePass() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 6, DevTimePass(), (int)DevTimePass.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 7, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 7, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectData::update");
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
twine ProjectData::update_prepSQL(IOConn& ioc, twine& DataName, twine& Description, intptr_t DataType, twine& ConnectionString, twine& DevTimeUser, twine& DevTimePass, twine& guid )
{
	EnEx ee(FL, "ProjectData::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update projdata 			set DataName = ?, 				Description = ?, 				DataType = ?, 				ConnectionString = ?, 				DevTimeUser = ?, 				DevTimePass = ? 			where guid = ?";

	// Replace the DataName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, DataName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Description );
	}

	// Replace the DataType parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = DataType;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the ConnectionString parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, ConnectionString );
	}

	// Replace the DevTimeUser parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, DevTimeUser );
	}

	// Replace the DevTimePass parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, DevTimePass );
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
			This removes a project data entry by guid
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from projdata
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void ProjectData::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "ProjectData::deleteByID()");

	twine stmt = "delete from projdata 			where guid = ?";

	ProjectData::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void ProjectData::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "ProjectData::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectData::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectData::deleteByID");
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
twine ProjectData::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "ProjectData::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from projdata 			where guid = ?";

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
			This selects all project data entries for a given project
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projguid, DataName, Description, DataType, 
				ConnectionString, DevTimeUser, DevTimePass
			from projdata
			where projguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projguid
   * DataName
   * Description
   * DataType
   * ConnectionString
   * DevTimeUser
   * DevTimePass
 */
/* ************************************************************************************** */
vector<ProjectData* >* ProjectData::selectAllForProj(SqlDB& sqldb, twine& projguid)
{
	EnEx ee(FL, "ProjectData::selectAllForProj()");

	twine stmt = "select guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass 			from projdata 			where projguid = ?";

	return ProjectData::selectAllForProj(sqldb, stmt, true, projguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<ProjectData* >* ProjectData::selectAllForProj(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projguid)
{
	EnEx ee(FL, "ProjectData::selectAllForProj(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<ProjectData* >, ProjectData::deleteVector> ret = new vector<ProjectData* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, projguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, projguid(), (int)projguid.length(), SQLITE_STATIC) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectData::selectAllForProj()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectData::selectAllForProj");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			ProjectData* obj = new ProjectData( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->DataName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->DataType = sqlite3_column_int( db_stmt, 4);
			}
			if( 5 < colCount ){
				obj->ConnectionString.set( (const char*)sqlite3_column_text( db_stmt, 5), (size_t)sqlite3_column_bytes(db_stmt, 5) );
			}
			if( 6 < colCount ){
				obj->DevTimeUser.set( (const char*)sqlite3_column_text( db_stmt, 6), (size_t)sqlite3_column_bytes(db_stmt, 6) );
			}
			if( 7 < colCount ){
				obj->DevTimePass.set( (const char*)sqlite3_column_text( db_stmt, 7), (size_t)sqlite3_column_bytes(db_stmt, 7) );
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
twine ProjectData::selectAllForProj_prepSQL(IOConn& ioc, twine& projguid)
{
	EnEx ee(FL, "ProjectData::selectAllForProj_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass 			from projdata 			where projguid = ?";

	// Replace the projguid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, projguid );
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
			This selects a single project data entry by id
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projguid, DataName, Description, DataType, 
				ConnectionString, DevTimeUser, DevTimePass
			from projdata
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
vector<ProjectData* >* ProjectData::selectByID(SqlDB& sqldb, twine& guid)
{
	EnEx ee(FL, "ProjectData::selectByID()");

	twine stmt = "select guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass 			from projdata 			where guid = ?";

	return ProjectData::selectByID(sqldb, stmt, true, guid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<ProjectData* >* ProjectData::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid)
{
	EnEx ee(FL, "ProjectData::selectByID(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<ProjectData* >, ProjectData::deleteVector> ret = new vector<ProjectData* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("ProjectData::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for ProjectData::selectByID");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			ProjectData* obj = new ProjectData( );

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
twine ProjectData::selectByID_prepSQL(IOConn& ioc, twine& guid)
{
	EnEx ee(FL, "ProjectData::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass 			from projdata 			where guid = ?";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, guid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

