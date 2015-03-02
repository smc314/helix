/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef ACTION_H
#define ACTION_H

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
  * ../logic/admin/Action.sql.xml
  */
class Action
{
	public:

		/// All Data Members are public
		intptr_t Allow;
		intptr_t OKWOSession;
		twine Path;
		intptr_t groupid;
		intptr_t id;
		intptr_t userid;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		Action();

		/// Standard Copy Constructor
		Action(const Action& c);

		/// Standard Assignment Operator
		Action& operator=(const Action& c);

		/// Standard Destructor
		virtual ~Action();

		/// Initialize this data object to have all empty or 0 values.
		Action& init();

		/// Call check_size() on all of our twine members.
		Action& checkSize();

		/// Construct from an XML Node
		Action(xmlNodePtr node);

		/// Read an XML Node to set our contents
		Action& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<Action* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<Action* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Action* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<Action* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Action.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add new action entries into our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into action (path, okwosession)
			values ( ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, Action& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, Action& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< Action* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, Action& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into action (path, okwosession) 			values ( ?, ? )";
		}

		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add user's to an action.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into useraction (userid, actionid, allow)
			values ( ?, ?, ? )
		
		  * </pre>
		  */
		static void addUserToAction(SqlDB& sqldb, Action& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void addUserToAction(SqlDB& sqldb, twine& stmt, bool useInputs, Action& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void addUserToAction(SqlDB& sqldb, vector< Action* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine addUserToAction_prepSQL(IOConn& ioc, Action& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine addUserToAction_getSQL() {
			return "insert into useraction (userid, actionid, allow) 			values ( ?, ?, ? )";
		}

		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add group's to an action.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into groupaction (groupid, actionid, allow)
			values ( ?, ?, ? )
		
		  * </pre>
		  */
		static void addGroupToAction(SqlDB& sqldb, Action& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void addGroupToAction(SqlDB& sqldb, twine& stmt, bool useInputs, Action& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void addGroupToAction(SqlDB& sqldb, vector< Action* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine addGroupToAction_prepSQL(IOConn& ioc, Action& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine addGroupToAction_getSQL() {
			return "insert into groupaction (groupid, actionid, allow) 			values ( ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to update existing action entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update action
			set path = ?,
				okwosession = ?
			where id = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& Path, intptr_t OKWOSession, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Path, intptr_t OKWOSession, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& Path, intptr_t OKWOSession, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update action 			set path = ?, 				okwosession = ? 			where id = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing action entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from action
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
			return "delete from action 			where id = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to remove user's from an action
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from useraction
			where userid = ?
			and   actionid = ?
		
		  * </pre>
		  */
		static void removeUserFromAction(SqlDB& sqldb, intptr_t userid, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void removeUserFromAction(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine removeUserFromAction_prepSQL(IOConn& ioc, intptr_t userid, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine removeUserFromAction_getSQL() {
			return "delete from useraction 			where userid = ? 			and   actionid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to remove group's from an action
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from groupaction
			where groupid = ?
			and   actionid = ?
		
		  * </pre>
		  */
		static void removeGroupFromAction(SqlDB& sqldb, intptr_t groupid, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void removeGroupFromAction(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine removeGroupFromAction_prepSQL(IOConn& ioc, intptr_t groupid, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine removeGroupFromAction_getSQL() {
			return "delete from groupaction 			where groupid = ? 			and   actionid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all action entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* selectAll(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* selectAll(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAll_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAll_getSQL() {
			return "select id, path, okwosession 			from action";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single action entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action
			where id = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* selectByID(SqlDB& sqldb, intptr_t id);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, intptr_t id);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select id, path, okwosession 			from action 			where id = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single action entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action
			where path = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* selectByPath(SqlDB& sqldb, twine& Path);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* selectByPath(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Path);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByPath_prepSQL(IOConn& ioc, twine& Path);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByPath_getSQL() {
			return "select id, path, okwosession 			from action 			where path = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all action entries for a given user in our database
			based on direct permissions.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action, useraction
			where useraction.userid = ?
			and   useraction.actionid = action.id
			and   useraction.allow = 1
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* selectActionsForUser(SqlDB& sqldb, intptr_t userid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* selectActionsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectActionsForUser_prepSQL(IOConn& ioc, intptr_t userid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectActionsForUser_getSQL() {
			return "select id, path, okwosession 			from action, useraction 			where useraction.userid = ? 			and   useraction.actionid = action.id 			and   useraction.allow = 1";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all action entries for a given group in our database
			based on direct permissions.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action, groupaction
			where groupaction.groupid = ?
			and   groupaction.actionid = action.id
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* selectActionsForGroup(SqlDB& sqldb, intptr_t groupid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* selectActionsForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectActionsForGroup_prepSQL(IOConn& ioc, intptr_t groupid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectActionsForGroup_getSQL() {
			return "select id, path, okwosession 			from action, groupaction 			where groupaction.groupid = ? 			and   groupaction.actionid = action.id";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all action entries for a given user in our database
			based on their group membership permissions.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action, groupaction, usergroup
			where usergroup.userid = ?
			and   usergroup.groupid = groupaction.groupid
			and   groupaction.actionid = action.id
			and   groupaction.allow = 1
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* selectActionsForUserByGroup(SqlDB& sqldb, intptr_t userid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* selectActionsForUserByGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectActionsForUserByGroup_prepSQL(IOConn& ioc, intptr_t userid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectActionsForUserByGroup_getSQL() {
			return "select id, path, okwosession 			from action, groupaction, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groupaction.groupid 			and   groupaction.actionid = action.id 			and   groupaction.allow = 1";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to check whether a given user has direct permissions
			to invoke a given action.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action, useraction
			where useraction.userid = ?
			and   useraction.actionid = action.id
			and   useraction.allow = 1
			and   action.path = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* checkActionForUser(SqlDB& sqldb, intptr_t userid, twine& Path);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* checkActionForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, twine& Path);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine checkActionForUser_prepSQL(IOConn& ioc, intptr_t userid, twine& Path);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine checkActionForUser_getSQL() {
			return "select id, path, okwosession 			from action, useraction 			where useraction.userid = ? 			and   useraction.actionid = action.id 			and   useraction.allow = 1 			and   action.path = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we to check whether a given user has group permissions
			to invoke a given action.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, path, okwosession
			from action, groupaction, usergroup
			where usergroup.userid = ?
			and   usergroup.groupid = groupaction.groupid
			and   groupaction.actionid = action.id
			and   groupaction.allow = 1
			and   action.path = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Path</li>
		  *   <li>OKWOSession</li>
		  * </ul>
		  */
		static vector<Action* >* checkActionForUserByGroup(SqlDB& sqldb, intptr_t userid, twine& Path);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Action* >* checkActionForUserByGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, twine& Path);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine checkActionForUserByGroup_prepSQL(IOConn& ioc, intptr_t userid, twine& Path);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine checkActionForUserByGroup_getSQL() {
			return "select id, path, okwosession 			from action, groupaction, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groupaction.groupid 			and   groupaction.actionid = action.id 			and   groupaction.allow = 1 			and   action.path = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the Action
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * Action_svect myVect = Action::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< Action* >, Action::deleteVector> Action_svect;

}}} // End Namespace stack

#endif // ACTION_H defined
