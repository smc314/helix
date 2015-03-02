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

#include "User.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/User.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine UserName = "User";

User::User()
{
	EnEx ee(FL, "User::User()");

	init();

}

User::User(const User& c)
{
	EnEx ee(FL, "User::User(const User& c)");

	Active = c.Active;
	AuthMechanism = c.AuthMechanism;
	EMail = c.EMail;
	FullName = c.FullName;
	Password = c.Password;
	Username = c.Username;
	groupid = c.groupid;
	id = c.id;
	AllowedActions = new vector<Action*>();
	for(size_t i = 0; i < c.AllowedActions->size(); i++){
		AllowedActions->push_back( new Action( *(c.AllowedActions->at( i )) ) );
	}
	GroupMembership = new vector<UserGroup*>();
	for(size_t i = 0; i < c.GroupMembership->size(); i++){
		GroupMembership->push_back( new UserGroup( *(c.GroupMembership->at( i )) ) );
	}


}

User& User::operator=(const User& c)
{
	EnEx ee(FL, "User::operator=(const User& c)");

	Active = c.Active;
	AuthMechanism = c.AuthMechanism;
	EMail = c.EMail;
	FullName = c.FullName;
	Password = c.Password;
	Username = c.Username;
	groupid = c.groupid;
	id = c.id;
	AllowedActions = new vector<Action*>();
	for(size_t i = 0; i < c.AllowedActions->size(); i++){
		AllowedActions->push_back( new Action( *(c.AllowedActions->at( i )) ) );
	}
	GroupMembership = new vector<UserGroup*>();
	for(size_t i = 0; i < c.GroupMembership->size(); i++){
		GroupMembership->push_back( new UserGroup( *(c.GroupMembership->at( i )) ) );
	}


	return *this;
}

User::~User()
{
	EnEx ee(FL, "User::~User()");

}

User& User::init()
{
	EnEx ee(FL, "User::init()");

	Active = 0;
	AuthMechanism = 0;
	EMail.erase();
	FullName.erase();
	Password.erase();
	Username.erase();
	groupid = 0;
	id = 0;
	AllowedActions = new vector<Action*>();
	GroupMembership = new vector<UserGroup*>();


	return *this;
}

User& User::checkSize()
{
	EnEx ee(FL, "User::checkSize()");

	EMail.check_size();
	EMail.rtrim();
	FullName.check_size();
	FullName.rtrim();
	Password.check_size();
	Password.rtrim();
	Username.check_size();
	Username.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
User::User(xmlNodePtr node)
{
	EnEx ee(FL, "User::User(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
User& User::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "User::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct User is NULL.");
	}

	Active = XmlHelpers::getIntAttr(node, "Active");
	AuthMechanism = XmlHelpers::getIntAttr(node, "AuthMechanism");
	EMail.getAttribute(node, "EMail");
	FullName.getAttribute(node, "FullName");
	Password.getAttribute(node, "Password");
	Username.getAttribute(node, "Username");
	groupid = XmlHelpers::getIntAttr(node, "groupid");
	id = XmlHelpers::getIntAttr(node, "id");
	AllowedActions = Action::readXmlChildren( XmlHelpers::FindChild( node, "AllowedActions") );
	GroupMembership = UserGroup::readXmlChildren( XmlHelpers::FindChild( node, "GroupMembership") );


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr User::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "User::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to User::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"User", NULL);
	XmlHelpers::setIntAttr(child, "Active", Active);
	XmlHelpers::setIntAttr(child, "AuthMechanism", AuthMechanism);
	xmlSetProp(child, (const xmlChar*)"EMail", EMail);
	xmlSetProp(child, (const xmlChar*)"FullName", FullName);
	xmlSetProp(child, (const xmlChar*)"Password", Password);
	xmlSetProp(child, (const xmlChar*)"Username", Username);
	XmlHelpers::setIntAttr(child, "groupid", groupid);
	XmlHelpers::setIntAttr(child, "id", id);
	xmlNodePtr AllowedActions_node = xmlNewChild(child, NULL, (const xmlChar*)"AllowedActions", NULL);
	Action::createXmlChildren( AllowedActions_node, AllowedActions );

	xmlNodePtr GroupMembership_node = xmlNewChild(child, NULL, (const xmlChar*)"GroupMembership", NULL);
	UserGroup::createXmlChildren( GroupMembership_node, GroupMembership );



	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr User::createXmlDoc() const
{
	EnEx ee(FL, "User::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"User", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	XmlHelpers::setIntAttr(child, "Active", Active);
	XmlHelpers::setIntAttr(child, "AuthMechanism", AuthMechanism);
	xmlSetProp(child, (const xmlChar*)"EMail", EMail);
	xmlSetProp(child, (const xmlChar*)"FullName", FullName);
	xmlSetProp(child, (const xmlChar*)"Password", Password);
	xmlSetProp(child, (const xmlChar*)"Username", Username);
	XmlHelpers::setIntAttr(child, "groupid", groupid);
	XmlHelpers::setIntAttr(child, "id", id);
	xmlNodePtr AllowedActions_node = xmlNewChild(child, NULL, (const xmlChar*)"AllowedActions", NULL);
	Action::createXmlChildren( AllowedActions_node, AllowedActions );

	xmlNodePtr GroupMembership_node = xmlNewChild(child, NULL, (const xmlChar*)"GroupMembership", NULL);
	UserGroup::createXmlChildren( GroupMembership_node, GroupMembership );



	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<User* >* User::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "User::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to User::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<User* >, User::deleteVector> ret = new vector<User* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "User") == 0){
			ret->push_back( new User(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void User::createXmlChildren(xmlNodePtr parent, vector<User* >* vect)
{
	EnEx ee(FL, "User::createXmlChildren(xmlNodePtr parent, vector<User* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to User::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr User::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<User* >* vect)
{
	EnEx ee(FL, "User::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<User* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to User::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	User::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void User::deleteVector(vector<User* >* vect)
{
	EnEx ee(FL, "User::deleteVector(vector<User* >* vect)");

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
twine& User::Name()
{
	return UserName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add new user entries into our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into user (user, fullname, email, active)
			values ( ?, ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::insert(SqlDB& sqldb, User& obj )
{
	EnEx ee(FL, "User::insert()");

	twine stmt = "insert into user (user, fullname, email, active) 			values ( ?, ?, ?, ? )";

	User::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::insert(SqlDB& sqldb, twine& stmt, bool useInputs, User& obj )
{
	EnEx ee(FL, "User::insert()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.Username() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.Username(), (int)obj.Username.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, obj.FullName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, obj.FullName(), (int)obj.FullName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.EMail() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.EMail(), (int)obj.EMail.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 4, obj.Active );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 4, (int)obj.Active) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::insert");
			sqldb.check_err( sqlite3_step( db_stmt ) );

			// Update the insert object to pick up the new autogen value:
			obj.id = sqlite3_last_insert_rowid( db );


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
void User::insert(SqlDB& sqldb, vector< User* >* v, bool useTransaction)
{
	EnEx ee(FL, "User::insert(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into user (user, fullname, email, active) 			values ( ?, ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::insert()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->Username() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->Username(), (int)v->at( v_i )->Username.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, v->at( v_i )->FullName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, v->at( v_i )->FullName(), (int)v->at( v_i )->FullName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->EMail() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->EMail(), (int)v->at( v_i )->EMail.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 4, v->at( v_i )->Active );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 4, (int)v->at( v_i )->Active) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for User::insert");
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
twine User::insert_prepSQL(IOConn& ioc, User& obj )
{
	EnEx ee(FL, "User::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into user (user, fullname, email, active) 			values ( ?, ?, ?, ? )";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Username parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Username );
	}

	// Replace the FullName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.FullName );
	}

	// Replace the EMail parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.EMail );
	}

	// Replace the Active parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Active;
		stmt.replace(idx, 1, tmp);
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
			values ( ?, ?)
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::addUserToGroup(SqlDB& sqldb, User& obj )
{
	EnEx ee(FL, "User::addUserToGroup()");

	twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ?)";

	User::addUserToGroup(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::addUserToGroup(SqlDB& sqldb, twine& stmt, bool useInputs, User& obj )
{
	EnEx ee(FL, "User::addUserToGroup()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::addUserToGroup()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)obj.id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.groupid) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::addUserToGroup");
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
void User::addUserToGroup(SqlDB& sqldb, vector< User* >* v, bool useTransaction)
{
	EnEx ee(FL, "User::addUserToGroup(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ?)";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::addUserToGroup()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, v->at( v_i )->id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)v->at( v_i )->id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->groupid) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for User::addUserToGroup");
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
twine User::addUserToGroup_prepSQL(IOConn& ioc, User& obj )
{
	EnEx ee(FL, "User::addUserToGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ?)";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the groupid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.groupid;
		stmt.replace(idx, 1, tmp);
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
			This is the statement that we use to add new userauth entries into our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into userauth (userid, authmechanism, password)
			values ( ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::insertAuth(SqlDB& sqldb, User& obj )
{
	EnEx ee(FL, "User::insertAuth()");

	twine stmt = "insert into userauth (userid, authmechanism, password) 			values ( ?, ?, ? )";

	User::insertAuth(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::insertAuth(SqlDB& sqldb, twine& stmt, bool useInputs, User& obj )
{
	EnEx ee(FL, "User::insertAuth()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::insertAuth()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)obj.id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.AuthMechanism );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.AuthMechanism) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, obj.Password() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, obj.Password(), (int)obj.Password.length(), SQLITE_STATIC) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::insertAuth");
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
void User::insertAuth(SqlDB& sqldb, vector< User* >* v, bool useTransaction)
{
	EnEx ee(FL, "User::insertAuth(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		twine stmt = "insert into userauth (userid, authmechanism, password) 			values ( ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::insertAuth()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, v->at( v_i )->id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)v->at( v_i )->id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->AuthMechanism );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->AuthMechanism) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, v->at( v_i )->Password() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, v->at( v_i )->Password(), (int)v->at( v_i )->Password.length(), SQLITE_STATIC) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for User::insertAuth");
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
twine User::insertAuth_prepSQL(IOConn& ioc, User& obj )
{
	EnEx ee(FL, "User::insertAuth_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into userauth (userid, authmechanism, password) 			values ( ?, ?, ? )";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the AuthMechanism parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.AuthMechanism;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Password parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Password );
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
			This is the statement that we use to update existing user entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update user
			set user = ?,
				fullname = ?,
				email = ?,
				active = ?
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::update(SqlDB& sqldb, twine& Username, twine& FullName, twine& EMail, intptr_t Active, intptr_t id )
{
	EnEx ee(FL, "User::update()");

	twine stmt = "update user 			set user = ?, 				fullname = ?, 				email = ?, 				active = ? 			where id = ?";

	User::update(sqldb, stmt, true, Username, FullName, EMail, Active, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Username, twine& FullName, twine& EMail, intptr_t Active, intptr_t id )
{
	EnEx ee(FL, "User::update()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, Username() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, Username(), (int)Username.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, FullName() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, FullName(), (int)FullName.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %s", 3, EMail() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 3, EMail(), (int)EMail.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 4, Active );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 4, (int)Active) );
				DEBUG(FL, "Setting input (%d) to value: %d", 5, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 5, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::update");
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
twine User::update_prepSQL(IOConn& ioc, twine& Username, twine& FullName, twine& EMail, intptr_t Active, intptr_t id )
{
	EnEx ee(FL, "User::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update user 			set user = ?, 				fullname = ?, 				email = ?, 				active = ? 			where id = ?";

	// Replace the Username parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Username );
	}

	// Replace the FullName parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, FullName );
	}

	// Replace the EMail parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, EMail );
	}

	// Replace the Active parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = Active;
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
/* This is an UPDATE method.  It is designed to run a single update                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to update existing userauth entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update userauth
			set authmechanism = ?,
				password = ?
			where userid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::updateAuth(SqlDB& sqldb, intptr_t AuthMechanism, twine& Password, intptr_t id )
{
	EnEx ee(FL, "User::updateAuth()");

	twine stmt = "update userauth 			set authmechanism = ?, 				password = ? 			where userid = ?";

	User::updateAuth(sqldb, stmt, true, AuthMechanism, Password, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::updateAuth(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t AuthMechanism, twine& Password, intptr_t id )
{
	EnEx ee(FL, "User::updateAuth()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::updateAuth()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, AuthMechanism );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)AuthMechanism) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Password() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Password(), (int)Password.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::updateAuth");
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
twine User::updateAuth_prepSQL(IOConn& ioc, intptr_t AuthMechanism, twine& Password, intptr_t id )
{
	EnEx ee(FL, "User::updateAuth_prepSQL()");

	size_t idx = 0;
	twine stmt = "update userauth 			set authmechanism = ?, 				password = ? 			where userid = ?";

	// Replace the AuthMechanism parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = AuthMechanism;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Password parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Password );
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
			This is the statement that we use to delete existing user entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from user
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::deleteByID(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "User::deleteByID()");

	twine stmt = "delete from user 			where id = ?";

	User::deleteByID(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "User::deleteByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::deleteByID");
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
twine User::deleteByID_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "User::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from user 			where id = ?";

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
			This is the statement that we use to delete existing userauth entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from userauth
			where userid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::deleteAuthByID(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "User::deleteAuthByID()");

	twine stmt = "delete from userauth 			where userid = ?";

	User::deleteAuthByID(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::deleteAuthByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "User::deleteAuthByID()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::deleteAuthByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::deleteAuthByID");
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
twine User::deleteAuthByID_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "User::deleteAuthByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from userauth 			where userid = ?";

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
			This is the statement that we use to delete existing usergroup entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from usergroup
			where userid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::deleteGroupsForUser(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "User::deleteGroupsForUser()");

	twine stmt = "delete from usergroup 			where userid = ?";

	User::deleteGroupsForUser(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::deleteGroupsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "User::deleteGroupsForUser()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::deleteGroupsForUser()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::deleteGroupsForUser");
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
twine User::deleteGroupsForUser_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "User::deleteGroupsForUser_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from usergroup 			where userid = ?";

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
			This is the statement that we use to delete existing useraction entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from useraction
			where userid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void User::deleteActionsForUser(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "User::deleteActionsForUser()");

	twine stmt = "delete from useraction 			where userid = ?";

	User::deleteActionsForUser(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void User::deleteActionsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "User::deleteActionsForUser()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		int sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable
		int sizeof_float = sizeof(float);      // so that we can have an address of this variable

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("User::deleteActionsForUser()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::deleteActionsForUser");
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
twine User::deleteActionsForUser_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "User::deleteActionsForUser_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from useraction 			where userid = ?";

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
			This is the statement that we use to pull up all user entries in our database
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, user, fullname, email, active
			from user
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Username
   * FullName
   * EMail
   * Active
 */
/* ************************************************************************************** */
vector<User* >* User::selectAll(SqlDB& sqldb)
{
	EnEx ee(FL, "User::selectAll()");

	twine stmt = "select id, user, fullname, email, active 			from user";

	return User::selectAll(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<User* >* User::selectAll(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "User::selectAll(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<User* >, User::deleteVector> ret = new vector<User* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("User::selectAll()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::selectAll");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			User* obj = new User( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Username.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->FullName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->EMail.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Active = sqlite3_column_int( db_stmt, 4);
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
twine User::selectAll_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "User::selectAll_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, user, fullname, email, active 			from user";

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
			This is the statement that we use to pull up a single user entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, user, fullname, email, active, authmechanism, password
			from user, userauth
			where user.id = ?
			and   user.id = userauth.userid
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Username
   * FullName
   * EMail
   * Active
   * AuthMechanism
   * Password
 */
/* ************************************************************************************** */
vector<User* >* User::selectByID(SqlDB& sqldb, intptr_t id)
{
	EnEx ee(FL, "User::selectByID()");

	twine stmt = "select id, user, fullname, email, active, authmechanism, password 			from user, userauth 			where user.id = ? 			and   user.id = userauth.userid";

	return User::selectByID(sqldb, stmt, true, id);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<User* >* User::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id)
{
	EnEx ee(FL, "User::selectByID(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<User* >, User::deleteVector> ret = new vector<User* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("User::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::selectByID");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			User* obj = new User( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Username.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->FullName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->EMail.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Active = sqlite3_column_int( db_stmt, 4);
			}
			if( 5 < colCount ){
				obj->AuthMechanism = sqlite3_column_int( db_stmt, 5);
			}
			if( 6 < colCount ){
				obj->Password.set( (const char*)sqlite3_column_text( db_stmt, 6), (size_t)sqlite3_column_bytes(db_stmt, 6) );
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
twine User::selectByID_prepSQL(IOConn& ioc, intptr_t id)
{
	EnEx ee(FL, "User::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, user, fullname, email, active, authmechanism, password 			from user, userauth 			where user.id = ? 			and   user.id = userauth.userid";

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
			This is the statement that we use to pull up a single user entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, user, fullname, email, active, authmechanism, password
			from user, userauth
			where user.user = ?
			and   user.id = userauth.userid
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Username
   * FullName
   * EMail
   * Active
   * AuthMechanism
   * Password
 */
/* ************************************************************************************** */
vector<User* >* User::selectByUsername(SqlDB& sqldb, twine& Username)
{
	EnEx ee(FL, "User::selectByUsername()");

	twine stmt = "select id, user, fullname, email, active, authmechanism, password 			from user, userauth 			where user.user = ? 			and   user.id = userauth.userid";

	return User::selectByUsername(sqldb, stmt, true, Username);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<User* >* User::selectByUsername(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Username)
{
	EnEx ee(FL, "User::selectByUsername(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<User* >, User::deleteVector> ret = new vector<User* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, Username() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, Username(), (int)Username.length(), SQLITE_STATIC) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("User::selectByUsername()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::selectByUsername");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			User* obj = new User( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Username.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->FullName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->EMail.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Active = sqlite3_column_int( db_stmt, 4);
			}
			if( 5 < colCount ){
				obj->AuthMechanism = sqlite3_column_int( db_stmt, 5);
			}
			if( 6 < colCount ){
				obj->Password.set( (const char*)sqlite3_column_text( db_stmt, 6), (size_t)sqlite3_column_bytes(db_stmt, 6) );
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
twine User::selectByUsername_prepSQL(IOConn& ioc, twine& Username)
{
	EnEx ee(FL, "User::selectByUsername_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, user, fullname, email, active, authmechanism, password 			from user, userauth 			where user.user = ? 			and   user.id = userauth.userid";

	// Replace the Username parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Username );
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
			This is the statement that we use to pull up all of the users that are in a given group.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, user, fullname, email, active
			from user, usergroup
			where usergroup.groupid = ?
			and   user.id = usergroup.userid
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Username
   * FullName
   * EMail
   * Active
 */
/* ************************************************************************************** */
vector<User* >* User::selectUsersForGroup(SqlDB& sqldb, intptr_t groupid)
{
	EnEx ee(FL, "User::selectUsersForGroup()");

	twine stmt = "select id, user, fullname, email, active 			from user, usergroup 			where usergroup.groupid = ? 			and   user.id = usergroup.userid";

	return User::selectUsersForGroup(sqldb, stmt, true, groupid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<User* >* User::selectUsersForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid)
{
	EnEx ee(FL, "User::selectUsersForGroup(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<User* >, User::deleteVector> ret = new vector<User* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)groupid) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("User::selectUsersForGroup()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for User::selectUsersForGroup");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			User* obj = new User( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Username.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->FullName.set( (const char*)sqlite3_column_text( db_stmt, 2), (size_t)sqlite3_column_bytes(db_stmt, 2) );
			}
			if( 3 < colCount ){
				obj->EMail.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
			}
			if( 4 < colCount ){
				obj->Active = sqlite3_column_int( db_stmt, 4);
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
twine User::selectUsersForGroup_prepSQL(IOConn& ioc, intptr_t groupid)
{
	EnEx ee(FL, "User::selectUsersForGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, user, fullname, email, active 			from user, usergroup 			where usergroup.groupid = ? 			and   user.id = usergroup.userid";

	// Replace the groupid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = groupid;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

