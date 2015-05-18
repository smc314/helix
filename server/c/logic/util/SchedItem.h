/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SCHEDITEM_H
#define SCHEDITEM_H

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
namespace util {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/util/SchedItem.sql.xml
  */
class SchedItem
{
	public:

		/// All Data Members are public
		twine InputDocument;
		twine LastRun;
		twine RunAtTime;
		twine TaskName;
		twine TaskUrl;
		intptr_t dowFriday;
		intptr_t dowMonday;
		intptr_t dowSaturday;
		intptr_t dowSunday;
		intptr_t dowThursday;
		intptr_t dowTuesday;
		intptr_t dowWednesday;
		intptr_t id;
		intptr_t isActive;
		intptr_t runEvery;
		intptr_t useInterval;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		SchedItem();

		/// Standard Copy Constructor
		SchedItem(const SchedItem& c);

		/// Standard Assignment Operator
		SchedItem& operator=(const SchedItem& c);

		/// Standard Destructor
		virtual ~SchedItem();

		/// Initialize this data object to have all empty or 0 values.
		SchedItem& init();

		/// Call check_size() on all of our twine members.
		SchedItem& checkSize();

		/// Construct from an XML Node
		SchedItem(xmlNodePtr node);

		/// Read an XML Node to set our contents
		SchedItem& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<SchedItem* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<SchedItem* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SchedItem* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<SchedItem* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/SchedItem.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to add new schedule entries into our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into schedule (TaskName, TaskUrl, InputDocument, isActive, runEvery, 
				LastRun, useInterval, RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday,
				dowThursday, dowFriday, dowSaturday)
			values ( ?, ?, ?, ?, ?, 
				?, ?, ?, ?, ?, ?, ?,
				?, ?, ?)
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, SchedItem& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, SchedItem& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< SchedItem* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, SchedItem& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into schedule (TaskName, TaskUrl, InputDocument, isActive, runEvery,  				LastRun, useInterval, RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, 				dowThursday, dowFriday, dowSaturday) 			values ( ?, ?, ?, ?, ?,  				?, ?, ?, ?, ?, ?, ?, 				?, ?, ?)";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to update existing schedule entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update schedule
			set TaskName = ?,
				TaskUrl = ?,
				InputDocument = ?,
				isActive = ?,
				runEvery = ?,
				LastRun = ?,
				useInterval = ?,
				RunAtTime = ?,
				dowSunday = ?,
				dowMonday = ?,
				dowTuesday = ?,
				dowWednesday = ?,
				dowThursday = ?,
				dowFriday = ?,
				dowSaturday = ?
			where id = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& TaskName, twine& TaskUrl, twine& InputDocument, intptr_t isActive, intptr_t runEvery, twine& LastRun, intptr_t useInterval, twine& RunAtTime, intptr_t dowSunday, intptr_t dowMonday, intptr_t dowTuesday, intptr_t dowWednesday, intptr_t dowThursday, intptr_t dowFriday, intptr_t dowSaturday, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& TaskName, twine& TaskUrl, twine& InputDocument, intptr_t isActive, intptr_t runEvery, twine& LastRun, intptr_t useInterval, twine& RunAtTime, intptr_t dowSunday, intptr_t dowMonday, intptr_t dowTuesday, intptr_t dowWednesday, intptr_t dowThursday, intptr_t dowFriday, intptr_t dowSaturday, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& TaskName, twine& TaskUrl, twine& InputDocument, intptr_t isActive, intptr_t runEvery, twine& LastRun, intptr_t useInterval, twine& RunAtTime, intptr_t dowSunday, intptr_t dowMonday, intptr_t dowTuesday, intptr_t dowWednesday, intptr_t dowThursday, intptr_t dowFriday, intptr_t dowSaturday, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update schedule 			set TaskName = ?, 				TaskUrl = ?, 				InputDocument = ?, 				isActive = ?, 				runEvery = ?, 				LastRun = ?, 				useInterval = ?, 				RunAtTime = ?, 				dowSunday = ?, 				dowMonday = ?, 				dowTuesday = ?, 				dowWednesday = ?, 				dowThursday = ?, 				dowFriday = ?, 				dowSaturday = ? 			where id = ?";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to update the LastRun timestamp for a schedule entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update schedule
			set LastRun = ?
			where id = ?
		
		  * </pre>
		  */
		static void updateLastRun(SqlDB& sqldb, twine& LastRun, intptr_t id );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void updateLastRun(SqlDB& sqldb, twine& stmt, bool useInputs, twine& LastRun, intptr_t id );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine updateLastRun_prepSQL(IOConn& ioc, twine& LastRun, intptr_t id );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine updateLastRun_getSQL() {
			return "update schedule 			set LastRun = ? 			where id = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to delete existing schedule entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from schedule
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
			return "delete from schedule 			where id = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up all schedule entries in our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval,
				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday,
				dowSaturday
			from schedule
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>TaskName</li>
		  *   <li>TaskUrl</li>
		  *   <li>InputDocument</li>
		  *   <li>isActive</li>
		  *   <li>runEvery</li>
		  *   <li>LastRun</li>
		  *   <li>useInterval</li>
		  *   <li>RunAtTime</li>
		  *   <li>dowSunday</li>
		  *   <li>dowMonday</li>
		  *   <li>dowTuesday</li>
		  *   <li>dowWednesday</li>
		  *   <li>dowThursday</li>
		  *   <li>dowFriday</li>
		  *   <li>dowSaturday</li>
		  * </ul>
		  */
		static vector<SchedItem* >* selectAll(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<SchedItem* >* selectAll(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAll_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAll_getSQL() {
			return "select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval, 				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, 				dowSaturday 			from schedule";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is the statement that we use to pull up a single schedule entry in our database.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval,
				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday,
				dowSaturday
			from schedule
			where id = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>id</li>
		  *   <li>TaskName</li>
		  *   <li>TaskUrl</li>
		  *   <li>InputDocument</li>
		  *   <li>isActive</li>
		  *   <li>runEvery</li>
		  *   <li>LastRun</li>
		  *   <li>useInterval</li>
		  *   <li>RunAtTime</li>
		  *   <li>dowSunday</li>
		  *   <li>dowMonday</li>
		  *   <li>dowTuesday</li>
		  *   <li>dowWednesday</li>
		  *   <li>dowThursday</li>
		  *   <li>dowFriday</li>
		  *   <li>dowSaturday</li>
		  * </ul>
		  */
		static vector<SchedItem* >* selectByID(SqlDB& sqldb, intptr_t id);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<SchedItem* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, intptr_t id);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select id, TaskName, TaskUrl, InputDocument, isActive, runEvery, LastRun, useInterval, 				RunAtTime, dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, 				dowSaturday 			from schedule 			where id = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the SchedItem
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * SchedItem_svect myVect = SchedItem::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< SchedItem* >, SchedItem::deleteVector> SchedItem_svect;

}}} // End Namespace stack

#endif // SCHEDITEM_H defined
