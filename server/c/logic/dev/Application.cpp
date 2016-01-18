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

#include "Application.h"
using namespace Helix::Logic::dev;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/dev/Application.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ApplicationName = "Application";

Application::Application()
{
	EnEx ee(FL, "Application::Application()");

	init();

}

Application::Application(const Application& c)
{
	EnEx ee(FL, "Application::Application(const Application& c)");

	AppName = c.AppName;
	Description = c.Description;
	PackageName = c.PackageName;
	guid = c.guid;
	projguid = c.projguid;
	Apis = new vector<Api*>();
	for(size_t i = 0; i < c.Apis->size(); i++){
		Apis->push_back( new Api( *(c.Apis->at( i )) ) );
	}
	DataObjects = new vector<DObject*>();
	for(size_t i = 0; i < c.DataObjects->size(); i++){
		DataObjects->push_back( new DObject( *(c.DataObjects->at( i )) ) );
	}
	Screens = new vector<Screen*>();
	for(size_t i = 0; i < c.Screens->size(); i++){
		Screens->push_back( new Screen( *(c.Screens->at( i )) ) );
	}


}

Application& Application::operator=(const Application& c)
{
	EnEx ee(FL, "Application::operator=(const Application& c)");

	AppName = c.AppName;
	Description = c.Description;
	PackageName = c.PackageName;
	guid = c.guid;
	projguid = c.projguid;
	Apis = new vector<Api*>();
	for(size_t i = 0; i < c.Apis->size(); i++){
		Apis->push_back( new Api( *(c.Apis->at( i )) ) );
	}
	DataObjects = new vector<DObject*>();
	for(size_t i = 0; i < c.DataObjects->size(); i++){
		DataObjects->push_back( new DObject( *(c.DataObjects->at( i )) ) );
	}
	Screens = new vector<Screen*>();
	for(size_t i = 0; i < c.Screens->size(); i++){
		Screens->push_back( new Screen( *(c.Screens->at( i )) ) );
	}


	return *this;
}

Application::~Application()
{
	EnEx ee(FL, "Application::~Application()");

}

Application& Application::init()
{
	EnEx ee(FL, "Application::init()");

	AppName.erase();
	Description.erase();
	PackageName.erase();
	guid.erase();
	projguid.erase();
	Apis = new vector<Api*>();
	DataObjects = new vector<DObject*>();
	Screens = new vector<Screen*>();


	return *this;
}

Application& Application::checkSize()
{
	EnEx ee(FL, "Application::checkSize()");

	AppName.check_size();
	AppName.rtrim();
	Description.check_size();
	Description.rtrim();
	PackageName.check_size();
	PackageName.rtrim();
	guid.check_size();
	guid.rtrim();
	projguid.check_size();
	projguid.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Application::Application(xmlNodePtr node)
{
	EnEx ee(FL, "Application::Application(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Application& Application::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Application::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Application is NULL.");
	}

	AppName.getAttribute(node, "AppName");
	Description.getAttribute(node, "Description");
	PackageName.getAttribute(node, "PackageName");
	guid.getAttribute(node, "guid");
	projguid.getAttribute(node, "projguid");
	Apis = Api::readXmlChildren( XmlHelpers::FindChild( node, "Apis") );
	DataObjects = DObject::readXmlChildren( XmlHelpers::FindChild( node, "DataObjects") );
	Screens = Screen::readXmlChildren( XmlHelpers::FindChild( node, "Screens") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Application::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Application::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Application::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Application", NULL);
	xmlSetProp(child, (const xmlChar*)"AppName", AppName);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"PackageName", PackageName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projguid", projguid);
	xmlNodePtr Apis_node = xmlNewChild(child, NULL, (const xmlChar*)"Apis", NULL);
	Api::createXmlChildren( Apis_node, Apis );

	xmlNodePtr DataObjects_node = xmlNewChild(child, NULL, (const xmlChar*)"DataObjects", NULL);
	DObject::createXmlChildren( DataObjects_node, DataObjects );

	xmlNodePtr Screens_node = xmlNewChild(child, NULL, (const xmlChar*)"Screens", NULL);
	Screen::createXmlChildren( Screens_node, Screens );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Application::createXmlDoc() const
{
	EnEx ee(FL, "Application::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Application", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"AppName", AppName);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"PackageName", PackageName);
	xmlSetProp(child, (const xmlChar*)"guid", guid);
	xmlSetProp(child, (const xmlChar*)"projguid", projguid);
	xmlNodePtr Apis_node = xmlNewChild(child, NULL, (const xmlChar*)"Apis", NULL);
	Api::createXmlChildren( Apis_node, Apis );

	xmlNodePtr DataObjects_node = xmlNewChild(child, NULL, (const xmlChar*)"DataObjects", NULL);
	DObject::createXmlChildren( DataObjects_node, DataObjects );

	xmlNodePtr Screens_node = xmlNewChild(child, NULL, (const xmlChar*)"Screens", NULL);
	Screen::createXmlChildren( Screens_node, Screens );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Application* >* Application::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Application::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Application::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Application* >, Application::deleteVector> ret = new vector<Application* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Application") == 0){
			ret->push_back( new Application(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Application::createXmlChildren(xmlNodePtr parent, vector<Application* >* vect)
{
	EnEx ee(FL, "Application::createXmlChildren(xmlNodePtr parent, vector<Application* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Application::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr Application::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Application* >* vect)
{
	EnEx ee(FL, "Application::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Application* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Application::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	Application::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Application::deleteVector(vector<Application* >* vect)
{
	EnEx ee(FL, "Application::deleteVector(vector<Application* >* vect)");

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
twine& Application::Name()
{
	return ApplicationName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This adds a new project application entry to our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into projapp (guid, projguid, AppName, Description, PackageName)
			values ( ?, ?, ?, ?, ?)
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Application::insert(SqlDB& sqldb, Application& obj )
{
	EnEx ee(FL, "Application::insert()");

	twine stmt = "insert into projapp (guid, projguid, AppName, Description, PackageName) 			values ( ?, ?, ?, ?, ?)";

	Application::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Application::insert(SqlDB& sqldb, twine& stmt, bool useInputs, Application& obj )
{
	EnEx ee(FL, "Application::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Application::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.guid(), (int)obj.guid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.projguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.projguid(), (int)obj.projguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.AppName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.AppName(), (int)obj.AppName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, obj.Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, obj.Description(), (int)obj.Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, obj.PackageName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, obj.PackageName(), (int)obj.PackageName.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Application::insert");
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
void Application::insert(SqlDB& sqldb, vector< Application* >* v, bool useTransaction)
{
	EnEx ee(FL, "Application::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into projapp (guid, projguid, AppName, Description, PackageName) 			values ( ?, ?, ?, ?, ?)";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Application::insert()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->projguid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->projguid(), (int)v->at( v_i )->projguid.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->AppName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->AppName(), (int)v->at( v_i )->AppName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, v->at( v_i )->Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, v->at( v_i )->Description(), (int)v->at( v_i )->Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 5, v->at( v_i )->PackageName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 5, v->at( v_i )->PackageName(), (int)v->at( v_i )->PackageName.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Application::insert");
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
twine Application::insert_prepSQL(IOConn& ioc, Application& obj )
{
	EnEx ee(FL, "Application::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into projapp (guid, projguid, AppName, Description, PackageName) 			values ( ?, ?, ?, ?, ?)";

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

	// Replace the AppName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.AppName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Description );
	}

	// Replace the PackageName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.PackageName );
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
			This updates the settings for a given project application in the database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update projapp
			set AppName = ?,
				Description = ?,
				PackageName = ?
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Application::update(SqlDB& sqldb, twine& AppName, twine& Description, twine& PackageName, twine& guid )
{
	EnEx ee(FL, "Application::update()");

	twine stmt = "update projapp 			set AppName = ?, 				Description = ?, 				PackageName = ? 			where guid = ?";

	Application::update(sqldb, stmt, true, AppName, Description, PackageName, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Application::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& AppName, twine& Description, twine& PackageName, twine& guid )
{
	EnEx ee(FL, "Application::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Application::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, AppName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, AppName(), (int)AppName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Description(), (int)Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, PackageName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, PackageName(), (int)PackageName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 4, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 4, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Application::update");
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
twine Application::update_prepSQL(IOConn& ioc, twine& AppName, twine& Description, twine& PackageName, twine& guid )
{
	EnEx ee(FL, "Application::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update projapp 			set AppName = ?, 				Description = ?, 				PackageName = ? 			where guid = ?";

	// Replace the AppName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, AppName );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Description );
	}

	// Replace the PackageName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, PackageName );
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
			This removes a project application by id
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from projapp
			where guid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Application::deleteByID(SqlDB& sqldb, twine& guid )
{
	EnEx ee(FL, "Application::deleteByID()");

	twine stmt = "delete from projapp 			where guid = ?";

	Application::deleteByID(sqldb, stmt, true, guid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Application::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid )
{
	EnEx ee(FL, "Application::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Application::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, guid() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, guid(), (int)guid.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Application::deleteByID");
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
twine Application::deleteByID_prepSQL(IOConn& ioc, twine& guid )
{
	EnEx ee(FL, "Application::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from projapp 			where guid = ?";

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
			This selects all project applications for a given project
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projguid, AppName, Description, PackageName
			from projapp
			where projguid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projguid
   * AppName
   * Description
   * PackageName
 */
/* ************************************************************************************** */
vector<Application* >* Application::selectAllForProject(SqlDB& sqldb, twine& projguid)
{
	EnEx ee(FL, "Application::selectAllForProject()");

	twine stmt = "select guid, projguid, AppName, Description, PackageName 			from projapp 			where projguid = ?";

	return Application::selectAllForProject(sqldb, stmt, true, projguid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Application* >* Application::selectAllForProject(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projguid)
{
	EnEx ee(FL, "Application::selectAllForProject(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Application* >, Application::deleteVector> ret = new vector<Application* >();

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
			EnEx eeExe("Application::selectAllForProject()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Application::selectAllForProject");
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
			Application* obj = new Application( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->AppName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->PackageName.set( (const char*)sqlite3_column_text( db_stmt, 4), (size_t)sqlite3_column_bytes(db_stmt, 4) );
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
twine Application::selectAllForProject_prepSQL(IOConn& ioc, twine& projguid)
{
	EnEx ee(FL, "Application::selectAllForProject_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projguid, AppName, Description, PackageName 			from projapp 			where projguid = ?";

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
			This selects a single project application by id
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select guid, projguid, AppName, Description, PackageName
			from projapp
			where guid = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * guid
   * projguid
   * AppName
   * Description
   * PackageName
 */
/* ************************************************************************************** */
vector<Application* >* Application::selectByID(SqlDB& sqldb, twine& guid)
{
	EnEx ee(FL, "Application::selectByID()");

	twine stmt = "select guid, projguid, AppName, Description, PackageName 			from projapp 			where guid = ?";

	return Application::selectByID(sqldb, stmt, true, guid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Application* >* Application::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid)
{
	EnEx ee(FL, "Application::selectByID(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Application* >, Application::deleteVector> ret = new vector<Application* >();

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
			EnEx eeExe("Application::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Application::selectByID");
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
			Application* obj = new Application( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->guid.set( (const char*)sqlite3_column_text( db_stmt, 0), (size_t)sqlite3_column_bytes(db_stmt, 0) );
			}
			if( 1 < colCount ){
				obj->projguid.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->AppName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->PackageName.set( (const char*)sqlite3_column_text( db_stmt, 4), (size_t)sqlite3_column_bytes(db_stmt, 4) );
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
twine Application::selectByID_prepSQL(IOConn& ioc, twine& guid)
{
	EnEx ee(FL, "Application::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select guid, projguid, AppName, Description, PackageName 			from projapp 			where guid = ?";

	// Replace the guid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, guid );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

