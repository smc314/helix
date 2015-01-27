/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SESSION_H
#define SESSION_H

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
  * ../logic/admin/Session.sql.xml
  */
class Session
{
	public:

		/// All Data Members are public
		intptr_t Active;
		Date Created;
		Date LastAccess;
		intptr_t Userid;
		twine guid;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		Session();

		/// Standard Copy Constructor
		Session(const Session& c);

		/// Standard Assignment Operator
		Session& operator=(const Session& c);

		/// Standard Destructor
		virtual ~Session();

		/// Initialize this data object to have all empty or 0 values.
		Session& init();

		/// Call check_size() on all of our twine members.
		Session& checkSize();

		/// Construct from an XML Node
		Session(xmlNodePtr node);

		/// Read an XML Node to set our contents
		Session& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<Session* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<Session* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<Session* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Session.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add new sesion entries into our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into session (guid, userid, created, lastaccess, active)
			values ( ?, ?, ?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, Session& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, Session& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< Session* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, Session& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into session (guid, userid, created, lastaccess, active) 			values ( ?, ?, ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to update existing session entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update session
			set userid = ?,
				created = ?,
				lastaccess = ?,
				active = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, intptr_t Userid, Date& Created, Date& LastAccess, intptr_t Active, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t Userid, Date& Created, Date& LastAccess, intptr_t Active, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, intptr_t Userid, Date& Created, Date& LastAccess, intptr_t Active, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update session 			set userid = ?, 				created = ?, 				lastaccess = ?, 				active = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing user session in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from session
			where guid = ?
		
		  * </pre>
		  */
		static void deleteByID(SqlDB& sqldb, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteByID_prepSQL(IOConn& ioc, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteByID_getSQL() {
			return "delete from session 			where guid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all session entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, userid, created, lastaccess, active
			from session
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>Userid</li>
		  *   <li>Created</li>
		  *   <li>LastAccess</li>
		  *   <li>Active</li>
		  * </ul>
		  */
		static vector<Session* >* selectAll(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Session* >* selectAll(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAll_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAll_getSQL() {
			return "select guid, userid, created, lastaccess, active 			from session";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single session entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, userid, created, lastaccess, active
			from session
			where guid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>Userid</li>
		  *   <li>Created</li>
		  *   <li>LastAccess</li>
		  *   <li>Active</li>
		  * </ul>
		  */
		static vector<Session* >* selectByID(SqlDB& sqldb, twine& guid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Session* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, twine& guid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select guid, userid, created, lastaccess, active 			from session 			where guid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the Session
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * Session_svect myVect = Session::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< Session* >, Session::deleteVector> Session_svect;

}}} // End Namespace stack

#endif // SESSION_H defined
