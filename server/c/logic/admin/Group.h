/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef GROUP_H
#define GROUP_H

#include <vector>
using namespace std;

#include <twine.h>
#include <Date.h>
#include <xmlinc.h>
#include <sptr.h>
using namespace SLib;

#include "IOConn.h"
#include "OdbcObj.h"
#include "SqlDB.h"
using namespace Helix::Glob;

#include "Action.h"
#include "UserGroup.h"


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/admin/Group.sql.xml
  */
class Group
{
	public:

		/// All Data Members are public
		twine Description;
		twine Groupname;
		intptr_t id;
		intptr_t userid;


		/// Any Child Vectors will be defined here
		Action_svect ActionsForGroup;
		UserGroup_svect UsersForGroup;


		/// Standard Constructor
		Group();

		/// Standard Copy Constructor
		Group(const Group& c);

		/// Standard Assignment Operator
		Group& operator=(const Group& c);

		/// Standard Destructor
		virtual ~Group();

		/// Initialize this data object to have all empty or 0 values.
		Group& init();

		/// Call check_size() on all of our twine members.
		Group& checkSize();

		/// Construct from an XML Node
		Group(xmlNodePtr node);

		/// Read an XML Node to set our contents
		Group& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<Group* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<Group* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Group* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<Group* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Group.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add new group entries into our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into groups (name, description)
			values ( ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, Group& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, Group& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< Group* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, Group& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into groups (name, description) 			values ( ?, ? )";
		}

		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add user's to a group.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into usergroup (userid, groupid)
			values ( ?, ? )
		
		  * </pre>
		  */
		static void addUserToGroup(SqlDB& sqldb, Group& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void addUserToGroup(SqlDB& sqldb, twine& stmt, bool useInputs, Group& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void addUserToGroup(SqlDB& sqldb, vector< Group* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine addUserToGroup_prepSQL(IOConn& ioc, Group& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine addUserToGroup_getSQL() {
			return "insert into usergroup (userid, groupid) 			values ( ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to update existing group entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update groups
			set name = ?,
				description = ?
			where id = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& Groupname, twine& Description, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Groupname, twine& Description, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& Groupname, twine& Description, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update groups 			set name = ?, 				description = ? 			where id = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing group entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from groups
			where id = ?
		
		  * </pre>
		  */
		static void deleteByID(SqlDB& sqldb, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteByID_prepSQL(IOConn& ioc, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteByID_getSQL() {
			return "delete from groups 			where id = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete all users who were a member of this group.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from usergroup
			where groupid = ?
		
		  * </pre>
		  */
		static void deleteUsersForGroup(SqlDB& sqldb, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteUsersForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteUsersForGroup_prepSQL(IOConn& ioc, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteUsersForGroup_getSQL() {
			return "delete from usergroup 			where groupid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete all actions associated to this group.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from groupaction
			where groupid = ?
		
		  * </pre>
		  */
		static void deleteActionsForGroup(SqlDB& sqldb, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteActionsForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteActionsForGroup_prepSQL(IOConn& ioc, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteActionsForGroup_getSQL() {
			return "delete from groupaction 			where groupid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to remove user's to a group
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from usergroup
			where userid = ?
			and   groupid = ?
		
		  * </pre>
		  */
		static void removeUserFromGroup(SqlDB& sqldb, intptr_t userid, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void removeUserFromGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine removeUserFromGroup_prepSQL(IOConn& ioc, intptr_t userid, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine removeUserFromGroup_getSQL() {
			return "delete from usergroup 			where userid = ? 			and   groupid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all group entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, name, description
			from groups
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Groupname</li>
		  *   <li>Description</li>
		  * </ul>
		  */
		static vector<Group* >* selectAll(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Group* >* selectAll(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAll_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAll_getSQL() {
			return "select id, name, description 			from groups";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single group entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, name, description
			from groups
			where id = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Groupname</li>
		  *   <li>Description</li>
		  * </ul>
		  */
		static vector<Group* >* selectByID(SqlDB& sqldb, intptr_t id);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Group* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, intptr_t id);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select id, name, description 			from groups 			where id = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single group entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, name, description
			from groups
			where name = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Groupname</li>
		  *   <li>Description</li>
		  * </ul>
		  */
		static vector<Group* >* selectByGroupname(SqlDB& sqldb, twine& Groupname);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Group* >* selectByGroupname(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Groupname);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByGroupname_prepSQL(IOConn& ioc, twine& Groupname);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByGroupname_getSQL() {
			return "select id, name, description 			from groups 			where name = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all group entries for a given user in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, name, description
			from groups, usergroup
			where usergroup.userid = ?
			and   usergroup.groupid = groups.id
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Groupname</li>
		  *   <li>Description</li>
		  * </ul>
		  */
		static vector<Group* >* selectGroupsForUser(SqlDB& sqldb, intptr_t userid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Group* >* selectGroupsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectGroupsForUser_prepSQL(IOConn& ioc, intptr_t userid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectGroupsForUser_getSQL() {
			return "select id, name, description 			from groups, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groups.id";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the Group
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * Group_svect myVect = Group::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< Group* >, Group::deleteVector> Group_svect;

}}} // End Namespace stack

#endif // GROUP_H defined
