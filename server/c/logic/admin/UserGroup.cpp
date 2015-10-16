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

#include "UserGroup.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/UserGroup.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine UserGroupName = "UserGroup";

UserGroup::UserGroup()
{
	EnEx ee(FL, "UserGroup::UserGroup()");

	init();

}

UserGroup::UserGroup(const UserGroup& c)
{
	EnEx ee(FL, "UserGroup::UserGroup(const UserGroup& c)");

	Groupname = c.Groupname;
	Username = c.Username;
	groupid = c.groupid;
	userid = c.userid;


}

UserGroup& UserGroup::operator=(const UserGroup& c)
{
	EnEx ee(FL, "UserGroup::operator=(const UserGroup& c)");

	Groupname = c.Groupname;
	Username = c.Username;
	groupid = c.groupid;
	userid = c.userid;


	return *this;
}

UserGroup::~UserGroup()
{
	EnEx ee(FL, "UserGroup::~UserGroup()");

}

UserGroup& UserGroup::init()
{
	EnEx ee(FL, "UserGroup::init()");

	Groupname.erase();
	Username.erase();
	groupid = 0;
	userid = 0;


	return *this;
}

UserGroup& UserGroup::checkSize()
{
	EnEx ee(FL, "UserGroup::checkSize()");

	Groupname.check_size();
	Groupname.rtrim();
	Username.check_size();
	Username.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
UserGroup::UserGroup(xmlNodePtr node)
{
	EnEx ee(FL, "UserGroup::UserGroup(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
UserGroup& UserGroup::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "UserGroup::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct UserGroup is NULL.");
	}

	Groupname.getAttribute(node, "Groupname");
	Username.getAttribute(node, "Username");
	groupid = XmlHelpers::getIntAttr(node, "groupid");
	userid = XmlHelpers::getIntAttr(node, "userid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr UserGroup::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "UserGroup::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to UserGroup::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"UserGroup", NULL);
	xmlSetProp(child, (const xmlChar*)"Groupname", Groupname);
	xmlSetProp(child, (const xmlChar*)"Username", Username);
	XmlHelpers::setIntAttr(child, "groupid", groupid);
	XmlHelpers::setIntAttr(child, "userid", userid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr UserGroup::createXmlDoc() const
{
	EnEx ee(FL, "UserGroup::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"UserGroup", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	xmlSetProp(child, (const xmlChar*)"Groupname", Groupname);
	xmlSetProp(child, (const xmlChar*)"Username", Username);
	XmlHelpers::setIntAttr(child, "groupid", groupid);
	XmlHelpers::setIntAttr(child, "userid", userid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<UserGroup* >* UserGroup::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "UserGroup::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to UserGroup::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<UserGroup* >, UserGroup::deleteVector> ret = new vector<UserGroup* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "UserGroup") == 0){
			ret->push_back( new UserGroup(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void UserGroup::createXmlChildren(xmlNodePtr parent, vector<UserGroup* >* vect)
{
	EnEx ee(FL, "UserGroup::createXmlChildren(xmlNodePtr parent, vector<UserGroup* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to UserGroup::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr UserGroup::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<UserGroup* >* vect)
{
	EnEx ee(FL, "UserGroup::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<UserGroup* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to UserGroup::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	UserGroup::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void UserGroup::deleteVector(vector<UserGroup* >* vect)
{
	EnEx ee(FL, "UserGroup::deleteVector(vector<UserGroup* >* vect)");

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
twine& UserGroup::Name()
{
	return UserGroupName;
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
void UserGroup::addUserGroup(SqlDB& sqldb, UserGroup& obj )
{
	EnEx ee(FL, "UserGroup::addUserGroup()");

	twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ?)";

	UserGroup::addUserGroup(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void UserGroup::addUserGroup(SqlDB& sqldb, twine& stmt, bool useInputs, UserGroup& obj )
{
	EnEx ee(FL, "UserGroup::addUserGroup()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("UserGroup::addUserGroup()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)obj.userid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.groupid) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for UserGroup::addUserGroup");
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
void UserGroup::addUserGroup(SqlDB& sqldb, vector< UserGroup* >* v, bool useTransaction)
{
	EnEx ee(FL, "UserGroup::addUserGroup(SqlDB& sqldb, vector<*>* v)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ?)";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("UserGroup::addUserGroup()-BindExecStmt");

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
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->groupid) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for UserGroup::addUserGroup");
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
twine UserGroup::addUserGroup_prepSQL(IOConn& ioc, UserGroup& obj )
{
	EnEx ee(FL, "UserGroup::addUserGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into usergroup (userid, groupid) 			values ( ?, ?)";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.userid;
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
void UserGroup::deleteGroupsForUser(SqlDB& sqldb, intptr_t userid )
{
	EnEx ee(FL, "UserGroup::deleteGroupsForUser()");

	twine stmt = "delete from usergroup 			where userid = ?";

	UserGroup::deleteGroupsForUser(sqldb, stmt, true, userid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void UserGroup::deleteGroupsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid )
{
	EnEx ee(FL, "UserGroup::deleteGroupsForUser()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("UserGroup::deleteGroupsForUser()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for UserGroup::deleteGroupsForUser");
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
twine UserGroup::deleteGroupsForUser_prepSQL(IOConn& ioc, intptr_t userid )
{
	EnEx ee(FL, "UserGroup::deleteGroupsForUser_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from usergroup 			where userid = ?";

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
			where groupid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void UserGroup::deleteUsersForGroup(SqlDB& sqldb, intptr_t groupid )
{
	EnEx ee(FL, "UserGroup::deleteUsersForGroup()");

	twine stmt = "delete from usergroup 			where groupid = ?";

	UserGroup::deleteUsersForGroup(sqldb, stmt, true, groupid );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void UserGroup::deleteUsersForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid )
{
	EnEx ee(FL, "UserGroup::deleteUsersForGroup()");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		{ // Used for scope for the timing object.
			EnEx eeExe("UserGroup::deleteUsersForGroup()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)groupid) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for UserGroup::deleteUsersForGroup");
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
twine UserGroup::deleteUsersForGroup_prepSQL(IOConn& ioc, intptr_t groupid )
{
	EnEx ee(FL, "UserGroup::deleteUsersForGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from usergroup 			where groupid = ?";

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
			select user.id, user.user, groups.id, groups.name
			from user, usergroup, groups
			where user.id = usergroup.userid
			and   usergroup.groupid = groups.id
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * userid
   * Username
   * groupid
   * Groupname
 */
/* ************************************************************************************** */
vector<UserGroup* >* UserGroup::selectAll(SqlDB& sqldb)
{
	EnEx ee(FL, "UserGroup::selectAll()");

	twine stmt = "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id";

	return UserGroup::selectAll(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<UserGroup* >* UserGroup::selectAll(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "UserGroup::selectAll(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<UserGroup* >, UserGroup::deleteVector> ret = new vector<UserGroup* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("UserGroup::selectAll()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for UserGroup::selectAll");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			UserGroup* obj = new UserGroup( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->userid = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Username.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->groupid = sqlite3_column_int( db_stmt, 2);
			}
			if( 3 < colCount ){
				obj->Groupname.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
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
twine UserGroup::selectAll_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "UserGroup::selectAll_prepSQL()");

	twine stmt = "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id";

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
			select user.id, user.user, groups.id, groups.name
			from user, usergroup, groups
			where user.id = usergroup.userid
			and   usergroup.groupid = groups.id
			and   groups.id = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * userid
   * Username
   * groupid
   * Groupname
 */
/* ************************************************************************************** */
vector<UserGroup* >* UserGroup::selectUsersForGroup(SqlDB& sqldb, intptr_t groupid)
{
	EnEx ee(FL, "UserGroup::selectUsersForGroup()");

	twine stmt = "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id 			and   groups.id = ?";

	return UserGroup::selectUsersForGroup(sqldb, stmt, true, groupid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<UserGroup* >* UserGroup::selectUsersForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid)
{
	EnEx ee(FL, "UserGroup::selectUsersForGroup(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<UserGroup* >, UserGroup::deleteVector> ret = new vector<UserGroup* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)groupid) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("UserGroup::selectUsersForGroup()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for UserGroup::selectUsersForGroup");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			UserGroup* obj = new UserGroup( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->userid = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Username.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->groupid = sqlite3_column_int( db_stmt, 2);
			}
			if( 3 < colCount ){
				obj->Groupname.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
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
twine UserGroup::selectUsersForGroup_prepSQL(IOConn& ioc, intptr_t groupid)
{
	EnEx ee(FL, "UserGroup::selectUsersForGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id 			and   groups.id = ?";

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

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up all of the groups for a given user.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select user.id, user.user, groups.id, groups.name
			from user, usergroup, groups
			where user.id = usergroup.userid
			and   usergroup.groupid = groups.id
			and   user.id = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * userid
   * Username
   * groupid
   * Groupname
 */
/* ************************************************************************************** */
vector<UserGroup* >* UserGroup::selectGroupsForUser(SqlDB& sqldb, intptr_t userid)
{
	EnEx ee(FL, "UserGroup::selectGroupsForUser()");

	twine stmt = "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id 			and   user.id = ?";

	return UserGroup::selectGroupsForUser(sqldb, stmt, true, userid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<UserGroup* >* UserGroup::selectGroupsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid)
{
	EnEx ee(FL, "UserGroup::selectGroupsForUser(twine& stmt, bool useInputs)");

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<UserGroup* >, UserGroup::deleteVector> ret = new vector<UserGroup* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
		}

		{ // Used for scope for the timing object.
			EnEx eeExe("UserGroup::selectGroupsForUser()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for UserGroup::selectGroupsForUser");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		while( count != 0 ){
			// Create the new object for this row
			UserGroup* obj = new UserGroup( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->userid = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Username.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->groupid = sqlite3_column_int( db_stmt, 2);
			}
			if( 3 < colCount ){
				obj->Groupname.set( (const char*)sqlite3_column_text( db_stmt, 3), (size_t)sqlite3_column_bytes(db_stmt, 3) );
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
twine UserGroup::selectGroupsForUser_prepSQL(IOConn& ioc, intptr_t userid)
{
	EnEx ee(FL, "UserGroup::selectGroupsForUser_prepSQL()");

	size_t idx = 0;
	twine stmt = "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id 			and   user.id = ?";

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

