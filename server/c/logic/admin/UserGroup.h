/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef USERGROUP_H
#define USERGROUP_H

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



namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/admin/UserGroup.sql.xml
  */
class UserGroup
{
	public:

		/// All Data Members are public
		twine Groupname;
		twine Username;
		intptr_t groupid;
		intptr_t userid;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		UserGroup();

		/// Standard Copy Constructor
		UserGroup(const UserGroup& c);

		/// Standard Assignment Operator
		UserGroup& operator=(const UserGroup& c);

		/// Standard Destructor
		virtual ~UserGroup();

		/// Initialize this data object to have all empty or 0 values.
		UserGroup& init();

		/// Call check_size() on all of our twine members.
		UserGroup& checkSize();

		/// Construct from an XML Node
		UserGroup(xmlNodePtr node);

		/// Read an XML Node to set our contents
		UserGroup& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<UserGroup* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<UserGroup* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<UserGroup* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<UserGroup* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/UserGroup.sql.xml */
		/* ******************************************************************************** */


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
			values ( ?, ?)
		
		  * </pre>
		  */
		static void addUserGroup(SqlDB& sqldb, UserGroup& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void addUserGroup(SqlDB& sqldb, twine& stmt, bool useInputs, UserGroup& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void addUserGroup(SqlDB& sqldb, vector< UserGroup* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine addUserGroup_prepSQL(IOConn& ioc, UserGroup& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine addUserGroup_getSQL() {
			return "insert into usergroup (userid, groupid) 			values ( ?, ?)";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing usergroup entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from usergroup
			where userid = ?
		
		  * </pre>
		  */
		static void deleteGroupsForUser(SqlDB& sqldb, intptr_t userid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteGroupsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteGroupsForUser_prepSQL(IOConn& ioc, intptr_t userid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteGroupsForUser_getSQL() {
			return "delete from usergroup 			where userid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing usergroup entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from usergroup
			where groupid = ?
		
		  * </pre>
		  */
		static void deleteUsersForGroup(SqlDB& sqldb, intptr_t groupid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteUsersForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteUsersForGroup_prepSQL(IOConn& ioc, intptr_t groupid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteUsersForGroup_getSQL() {
			return "delete from usergroup 			where groupid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all user entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select user.id, user.user, groups.id, groups.name
			from user, usergroup, groups
			where user.id = usergroup.userid
			and   usergroup.groupid = groups.id
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>userid</li>
		  *   <li>Username</li>
		  *   <li>groupid</li>
		  *   <li>Groupname</li>
		  * </ul>
		  */
		static vector<UserGroup* >* selectAll(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<UserGroup* >* selectAll(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAll_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAll_getSQL() {
			return "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all of the users that are in a given group.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select user.id, user.user, groups.id, groups.name
			from user, usergroup, groups
			where user.id = usergroup.userid
			and   usergroup.groupid = groups.id
			and   groups.id = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>userid</li>
		  *   <li>Username</li>
		  *   <li>groupid</li>
		  *   <li>Groupname</li>
		  * </ul>
		  */
		static vector<UserGroup* >* selectUsersForGroup(SqlDB& sqldb, intptr_t groupid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<UserGroup* >* selectUsersForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectUsersForGroup_prepSQL(IOConn& ioc, intptr_t groupid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectUsersForGroup_getSQL() {
			return "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id 			and   groups.id = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all of the groups for a given user.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select user.id, user.user, groups.id, groups.name
			from user, usergroup, groups
			where user.id = usergroup.userid
			and   usergroup.groupid = groups.id
			and   user.id = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>userid</li>
		  *   <li>Username</li>
		  *   <li>groupid</li>
		  *   <li>Groupname</li>
		  * </ul>
		  */
		static vector<UserGroup* >* selectGroupsForUser(SqlDB& sqldb, intptr_t userid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<UserGroup* >* selectGroupsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectGroupsForUser_prepSQL(IOConn& ioc, intptr_t userid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectGroupsForUser_getSQL() {
			return "select user.id, user.user, groups.id, groups.name 			from user, usergroup, groups 			where user.id = usergroup.userid 			and   usergroup.groupid = groups.id 			and   user.id = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the UserGroup
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * UserGroup_svect myVect = UserGroup::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< UserGroup* >, UserGroup::deleteVector> UserGroup_svect;

}}} // End Namespace stack

#endif // USERGROUP_H defined
