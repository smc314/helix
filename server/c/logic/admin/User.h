/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef USER_H
#define USER_H

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
  * ../logic/admin/User.sql.xml
  */
class User
{
	public:

		/// All Data Members are public
		intptr_t Active;
		intptr_t AuthMechanism;
		twine EMail;
		twine FullName;
		twine Password;
		twine Username;
		intptr_t id;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		User();

		/// Standard Copy Constructor
		User(const User& c);

		/// Standard Assignment Operator
		User& operator=(const User& c);

		/// Standard Destructor
		virtual ~User();

		/// Initialize this data object to have all empty or 0 values.
		User& init();

		/// Call check_size() on all of our twine members.
		User& checkSize();

		/// Construct from an XML Node
		User(xmlNodePtr node);

		/// Read an XML Node to set our contents
		User& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<User* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<User* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<User* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/User.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add new user entries into our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into user (user, fullname, email, active)
			values ( ?, ?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, User& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, User& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< User* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, User& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into user (user, fullname, email, active) 			values ( ?, ?, ?, ? )";
		}

		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add new userauth entries into our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into userauth (userid, authmechanism, password)
			values ( ?, ?, ? )
		
		  * </pre>
		  */
		static void insertAuth(SqlDB& sqldb, User& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insertAuth(SqlDB& sqldb, twine& stmt, bool useInputs, User& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insertAuth(SqlDB& sqldb, vector< User* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insertAuth_prepSQL(IOConn& ioc, User& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insertAuth_getSQL() {
			return "insert into userauth (userid, authmechanism, password) 			values ( ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to update existing user entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update user
			set Username = ?,
				FullName = ?,
				EMail = ?,
				Active = ?
			where id = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& Username, twine& FullName, twine& EMail, intptr_t Active, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Username, twine& FullName, twine& EMail, intptr_t Active, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& Username, twine& FullName, twine& EMail, intptr_t Active, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update user 			set Username = ?, 				FullName = ?, 				EMail = ?, 				Active = ? 			where id = ?";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to update existing userauth entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update userauth
			set authmechanism = ?,
				password = ?
			where userid = ?
		
		  * </pre>
		  */
		static void updateAuth(SqlDB& sqldb, intptr_t AuthMechanism, twine& Password, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void updateAuth(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t AuthMechanism, twine& Password, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine updateAuth_prepSQL(IOConn& ioc, intptr_t AuthMechanism, twine& Password, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine updateAuth_getSQL() {
			return "update userauth 			set authmechanism = ?, 				password = ? 			where userid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing user entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from user
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
			return "delete from user 			where id = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing userauth entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from userauth
			where userid = ?
		
		  * </pre>
		  */
		static void deleteAuthByID(SqlDB& sqldb, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteAuthByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteAuthByID_prepSQL(IOConn& ioc, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteAuthByID_getSQL() {
			return "delete from userauth 			where userid = ?";
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
			select id, user, fullname, email, active
			from user
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Username</li>
		  *   <li>FullName</li>
		  *   <li>EMail</li>
		  *   <li>Active</li>
		  * </ul>
		  */
		static vector<User* >* selectAll(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<User* >* selectAll(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAll_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAll_getSQL() {
			return "select id, user, fullname, email, active 			from user";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single user entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, user, fullname, email, active, authmechanism, password
			from user, userauth
			where user.id = ?
			and   user.id = userauth.userid
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Username</li>
		  *   <li>FullName</li>
		  *   <li>EMail</li>
		  *   <li>Active</li>
		  *   <li>AuthMechanism</li>
		  *   <li>Password</li>
		  * </ul>
		  */
		static vector<User* >* selectByID(SqlDB& sqldb, intptr_t id);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<User* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, intptr_t id);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select id, user, fullname, email, active, authmechanism, password 			from user, userauth 			where user.id = ? 			and   user.id = userauth.userid";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single user entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, user, fullname, email, active, authmechanism, password
			from user, userauth
			where user.user = ?
			and   user.id = userauth.userid
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>Username</li>
		  *   <li>FullName</li>
		  *   <li>EMail</li>
		  *   <li>Active</li>
		  *   <li>AuthMechanism</li>
		  *   <li>Password</li>
		  * </ul>
		  */
		static vector<User* >* selectByUsername(SqlDB& sqldb, twine& Username);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<User* >* selectByUsername(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Username);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByUsername_prepSQL(IOConn& ioc, twine& Username);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByUsername_getSQL() {
			return "select id, user, fullname, email, active, authmechanism, password 			from user, userauth 			where user.user = ? 			and   user.id = userauth.userid";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the User
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * User_svect myVect = User::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< User* >, User::deleteVector> User_svect;

}}} // End Namespace stack

#endif // USER_H defined
