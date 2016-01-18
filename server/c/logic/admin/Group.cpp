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

#include "Group.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/Group.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine GroupName = "Group";

Group::Group()
{
	EnEx ee(FL, "Group::Group()");

	init();

}

Group::Group(const Group& c)
{
	EnEx ee(FL, "Group::Group(const Group& c)");

	Description = c.Description;
	Groupname = c.Groupname;
	id = c.id;
	userid = c.userid;
	ActionsForGroup = new vector<Action*>();
	for(size_t i = 0; i < c.ActionsForGroup->size(); i++){
		ActionsForGroup->push_back( new Action( *(c.ActionsForGroup->at( i )) ) );
	}
	UsersForGroup = new vector<UserGroup*>();
	for(size_t i = 0; i < c.UsersForGroup->size(); i++){
		UsersForGroup->push_back( new UserGroup( *(c.UsersForGroup->at( i )) ) );
	}


}

Group& Group::operator=(const Group& c)
{
	EnEx ee(FL, "Group::operator=(const Group& c)");

	Description = c.Description;
	Groupname = c.Groupname;
	id = c.id;
	userid = c.userid;
	ActionsForGroup = new vector<Action*>();
	for(size_t i = 0; i < c.ActionsForGroup->size(); i++){
		ActionsForGroup->push_back( new Action( *(c.ActionsForGroup->at( i )) ) );
	}
	UsersForGroup = new vector<UserGroup*>();
	for(size_t i = 0; i < c.UsersForGroup->size(); i++){
		UsersForGroup->push_back( new UserGroup( *(c.UsersForGroup->at( i )) ) );
	}


	return *this;
}

Group::~Group()
{
	EnEx ee(FL, "Group::~Group()");

}

Group& Group::init()
{
	EnEx ee(FL, "Group::init()");

	Description.erase();
	Groupname.erase();
	id = 0;
	userid = 0;
	ActionsForGroup = new vector<Action*>();
	UsersForGroup = new vector<UserGroup*>();


	return *this;
}

Group& Group::checkSize()
{
	EnEx ee(FL, "Group::checkSize()");

	Description.check_size();
	Description.rtrim();
	Groupname.check_size();
	Groupname.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Group::Group(xmlNodePtr node)
{
	EnEx ee(FL, "Group::Group(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Group& Group::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Group::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Group is NULL.");
	}

	Description.getAttribute(node, "Description");
	Groupname.getAttribute(node, "Groupname");
	id = XmlHelpers::getIntAttr(node, "id");
	userid = XmlHelpers::getIntAttr(node, "userid");
	ActionsForGroup = Action::readXmlChildren( XmlHelpers::FindChild( node, "ActionsForGroup") );
	UsersForGroup = UserGroup::readXmlChildren( XmlHelpers::FindChild( node, "UsersForGroup") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Group::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Group::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Group::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Group", NULL);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"Groupname", Groupname);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "userid", userid);
	xmlNodePtr ActionsForGroup_node = xmlNewChild(child, NULL, (const xmlChar*)"ActionsForGroup", NULL);
	Action::createXmlChildren( ActionsForGroup_node, ActionsForGroup );

	xmlNodePtr UsersForGroup_node = xmlNewChild(child, NULL, (const xmlChar*)"UsersForGroup", NULL);
	UserGroup::createXmlChildren( UsersForGroup_node, UsersForGroup );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Group::createXmlDoc() const
{
	EnEx ee(FL, "Group::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Group", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Description", Description);
	xmlSetProp(child, (const xmlChar*)"Groupname", Groupname);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "userid", userid);
	xmlNodePtr ActionsForGroup_node = xmlNewChild(child, NULL, (const xmlChar*)"ActionsForGroup", NULL);
	Action::createXmlChildren( ActionsForGroup_node, ActionsForGroup );

	xmlNodePtr UsersForGroup_node = xmlNewChild(child, NULL, (const xmlChar*)"UsersForGroup", NULL);
	UserGroup::createXmlChildren( UsersForGroup_node, UsersForGroup );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Group* >* Group::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Group::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Group::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Group* >, Group::deleteVector> ret = new vector<Group* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Group") == 0){
			ret->push_back( new Group(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Group::createXmlChildren(xmlNodePtr parent, vector<Group* >* vect)
{
	EnEx ee(FL, "Group::createXmlChildren(xmlNodePtr parent, vector<Group* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Group::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr Group::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Group* >* vect)
{
	EnEx ee(FL, "Group::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Group* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Group::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	Group::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Group::deleteVector(vector<Group* >* vect)
{
	EnEx ee(FL, "Group::deleteVector(vector<Group* >* vect)");

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
twine& Group::Name()
{
	return GroupName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add new group entries into our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into groups (name, description)
			values ( ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Group::insert(SqlDB& sqldb, Group& obj )
{
	EnEx ee(FL, "Group::insert()");

	twine stmt = "insert into groups (name, description) 			values ( ?, ? )";

	Group::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Group::insert(SqlDB& sqldb, twine& stmt, bool useInputs, Group& obj )
{
	EnEx ee(FL, "Group::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.Groupname() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.Groupname(), (int)obj.Groupname.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.Description(), (int)obj.Description.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::insert");
			sqldb.check_err( sqlite3_step( db_stmt ) );

			// Update the insert object to pick up the new autogen value:
			obj.id = sqlite3_last_insert_rowid( db );


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
void Group::insert(SqlDB& sqldb, vector< Group* >* v, bool useTransaction)
{
	EnEx ee(FL, "Group::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into groups (name, description) 			values ( ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::insert()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->Groupname() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->Groupname(), (int)v->at( v_i )->Groupname.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->Description(), (int)v->at( v_i )->Description.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Group::insert");
				sqldb.check_err( sqlite3_step( db_stmt ) );

				// Update the insert object to pick up the new autogen value:
				v->at( v_i )->id = sqlite3_last_insert_rowid( db );


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
twine Group::insert_prepSQL(IOConn& ioc, Group& obj )
{
	EnEx ee(FL, "Group::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into groups (name, description) 			values ( ?, ? )";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Groupname parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Groupname );
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
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add user's to a group.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into usergroup (userid, groupid)
			values ( ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Group::addUserToGroup(SqlDB& sqldb, Group& obj )
{
	EnEx ee(FL, "Group::addUserToGroup()");

	twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ? )";

	Group::addUserToGroup(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Group::addUserToGroup(SqlDB& sqldb, twine& stmt, bool useInputs, Group& obj )
{
	EnEx ee(FL, "Group::addUserToGroup()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::addUserToGroup()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)obj.userid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::addUserToGroup");
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
void Group::addUserToGroup(SqlDB& sqldb, vector< Group* >* v, bool useTransaction)
{
	EnEx ee(FL, "Group::addUserToGroup(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::addUserToGroup()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, v->at( v_i )->userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)v->at( v_i )->userid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->id) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Group::addUserToGroup");
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
twine Group::addUserToGroup_prepSQL(IOConn& ioc, Group& obj )
{
	EnEx ee(FL, "Group::addUserToGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ? )";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to update existing group entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update groups
			set name = ?,
				description = ?
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Group::update(SqlDB& sqldb, twine& Groupname, twine& Description, intptr_t id )
{
	EnEx ee(FL, "Group::update()");

	twine stmt = "update groups 			set name = ?, 				description = ? 			where id = ?";

	Group::update(sqldb, stmt, true, Groupname, Description, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Group::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Groupname, twine& Description, intptr_t id )
{
	EnEx ee(FL, "Group::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, Groupname() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, Groupname(), (int)Groupname.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Description() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Description(), (int)Description.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::update");
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
twine Group::update_prepSQL(IOConn& ioc, twine& Groupname, twine& Description, intptr_t id )
{
	EnEx ee(FL, "Group::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update groups 			set name = ?, 				description = ? 			where id = ?";

	// Replace the Groupname parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Groupname );
	}

	// Replace the Description parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Description );
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to delete existing group entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from groups
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Group::deleteByID(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "Group::deleteByID()");

	twine stmt = "delete from groups 			where id = ?";

	Group::deleteByID(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Group::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "Group::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::deleteByID");
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
twine Group::deleteByID_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "Group::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from groups 			where id = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to delete all users who were a member of this group.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from usergroup
			where groupid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Group::deleteUsersForGroup(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "Group::deleteUsersForGroup()");

	twine stmt = "delete from usergroup 			where groupid = ?";

	Group::deleteUsersForGroup(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Group::deleteUsersForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "Group::deleteUsersForGroup()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::deleteUsersForGroup()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::deleteUsersForGroup");
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
twine Group::deleteUsersForGroup_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "Group::deleteUsersForGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from usergroup 			where groupid = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to delete all actions associated to this group.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from groupaction
			where groupid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Group::deleteActionsForGroup(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "Group::deleteActionsForGroup()");

	twine stmt = "delete from groupaction 			where groupid = ?";

	Group::deleteActionsForGroup(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Group::deleteActionsForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "Group::deleteActionsForGroup()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::deleteActionsForGroup()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::deleteActionsForGroup");
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
twine Group::deleteActionsForGroup_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "Group::deleteActionsForGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from groupaction 			where groupid = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to remove user's to a group
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from usergroup
			where userid = ?
			and   groupid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Group::removeUserFromGroup(SqlDB& sqldb, intptr_t userid, intptr_t id )
{
	EnEx ee(FL, "Group::removeUserFromGroup()");

	twine stmt = "delete from usergroup 			where userid = ? 			and   groupid = ?";

	Group::removeUserFromGroup(sqldb, stmt, true, userid, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Group::removeUserFromGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, intptr_t id )
{
	EnEx ee(FL, "Group::removeUserFromGroup()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::removeUserFromGroup()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::removeUserFromGroup");
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
twine Group::removeUserFromGroup_prepSQL(IOConn& ioc, intptr_t userid, intptr_t id )
{
	EnEx ee(FL, "Group::removeUserFromGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from usergroup 			where userid = ? 			and   groupid = ?";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to pull up all group entries in our database
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, name, description
			from groups
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Groupname
   * Description
 */
/* ************************************************************************************** */
vector<Group* >* Group::selectAll(SqlDB& sqldb)
{
	EnEx ee(FL, "Group::selectAll()");

	twine stmt = "select id, name, description 			from groups";

	return Group::selectAll(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Group* >* Group::selectAll(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "Group::selectAll(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Group* >, Group::deleteVector> ret = new vector<Group* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::selectAll()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::selectAll");
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
			Group* obj = new Group( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Groupname.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
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
twine Group::selectAll_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "Group::selectAll_prepSQL()");

	twine stmt = "select id, name, description 			from groups";

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
			This is the statement that we use to pull up a single group entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, name, description
			from groups
			where id = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Groupname
   * Description
 */
/* ************************************************************************************** */
vector<Group* >* Group::selectByID(SqlDB& sqldb, intptr_t id)
{
	EnEx ee(FL, "Group::selectByID()");

	twine stmt = "select id, name, description 			from groups 			where id = ?";

	return Group::selectByID(sqldb, stmt, true, id);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Group* >* Group::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id)
{
	EnEx ee(FL, "Group::selectByID(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Group* >, Group::deleteVector> ret = new vector<Group* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::selectByID");
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
			Group* obj = new Group( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Groupname.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
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
twine Group::selectByID_prepSQL(IOConn& ioc, intptr_t id)
{
	EnEx ee(FL, "Group::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, name, description 			from groups 			where id = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to pull up a single group entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, name, description
			from groups
			where name = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Groupname
   * Description
 */
/* ************************************************************************************** */
vector<Group* >* Group::selectByGroupname(SqlDB& sqldb, twine& Groupname)
{
	EnEx ee(FL, "Group::selectByGroupname()");

	twine stmt = "select id, name, description 			from groups 			where name = ?";

	return Group::selectByGroupname(sqldb, stmt, true, Groupname);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Group* >* Group::selectByGroupname(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Groupname)
{
	EnEx ee(FL, "Group::selectByGroupname(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Group* >, Group::deleteVector> ret = new vector<Group* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, Groupname() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, Groupname(), (int)Groupname.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::selectByGroupname()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::selectByGroupname");
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
			Group* obj = new Group( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Groupname.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
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
twine Group::selectByGroupname_prepSQL(IOConn& ioc, twine& Groupname)
{
	EnEx ee(FL, "Group::selectByGroupname_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, name, description 			from groups 			where name = ?";

	// Replace the Groupname parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Groupname );
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
			This is the statement that we use to pull up all group entries for a given user in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, name, description
			from groups, usergroup
			where usergroup.userid = ?
			and   usergroup.groupid = groups.id
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Groupname
   * Description
 */
/* ************************************************************************************** */
vector<Group* >* Group::selectGroupsForUser(SqlDB& sqldb, intptr_t userid)
{
	EnEx ee(FL, "Group::selectGroupsForUser()");

	twine stmt = "select id, name, description 			from groups, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groups.id";

	return Group::selectGroupsForUser(sqldb, stmt, true, userid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Group* >* Group::selectGroupsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid)
{
	EnEx ee(FL, "Group::selectGroupsForUser(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Group* >, Group::deleteVector> ret = new vector<Group* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Group::selectGroupsForUser()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Group::selectGroupsForUser");
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
			Group* obj = new Group( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Groupname.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->Description.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
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
twine Group::selectGroupsForUser_prepSQL(IOConn& ioc, intptr_t userid)
{
	EnEx ee(FL, "Group::selectGroupsForUser_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, name, description 			from groups, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groups.id";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = userid;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

