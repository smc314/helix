/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef TABLECOL_H
#define TABLECOL_H

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
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/TableCol.sql.xml
  */
class TableCol
{
	public:

		/// All Data Members are public
		twine ColName;
		twine ColType;
		twine guid;
		twine projtableguid;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		TableCol();

		/// Standard Copy Constructor
		TableCol(const TableCol& c);

		/// Standard Assignment Operator
		TableCol& operator=(const TableCol& c);

		/// Standard Destructor
		virtual ~TableCol();

		/// Initialize this data object to have all empty or 0 values.
		TableCol& init();

		/// Call check_size() on all of our twine members.
		TableCol& checkSize();

		/// Construct from an XML Node
		TableCol(xmlNodePtr node);

		/// Read an XML Node to set our contents
		TableCol& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<TableCol* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<TableCol* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<TableCol* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/TableCol.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new table column entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into projcol (guid, projtableguid, ColName, ColType )
			values ( ?, ?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, TableCol& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, TableCol& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< TableCol* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, TableCol& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into projcol (guid, projtableguid, ColName, ColType ) 			values ( ?, ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given table column in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update projcol
			set ColName = ?,
				ColType= ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& ColName, twine& ColType, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& ColName, twine& ColType, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& ColName, twine& ColType, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update projcol 			set ColName = ?, 				ColType= ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a table column by guid
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from projcol
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
			return "delete from projcol 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes all columns for a given table
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from projcol
			where projtableguid = ?
		
		  * </pre>
		  */
		static void deleteByTable(SqlDB& sqldb, twine& projtableguid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteByTable(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projtableguid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteByTable_prepSQL(IOConn& ioc, twine& projtableguid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteByTable_getSQL() {
			return "delete from projcol 			where projtableguid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all columns for a given table 
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, projtableguid, ColName, ColType
			from projcol
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>projtableguid</li>
		  *   <li>ColName</li>
		  *   <li>ColType</li>
		  * </ul>
		  */
		static vector<TableCol* >* selectAllForTable(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<TableCol* >* selectAllForTable(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForTable_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForTable_getSQL() {
			return "select guid, projtableguid, ColName, ColType 			from projcol";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the TableCol
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * TableCol_svect myVect = TableCol::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< TableCol* >, TableCol::deleteVector> TableCol_svect;

}}} // End Namespace stack

#endif // TABLECOL_H defined
