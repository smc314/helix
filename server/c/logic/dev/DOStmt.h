/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef DOSTMT_H
#define DOSTMT_H

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

#include "DOStmtInput.h"
#include "DOStmtOutput.h"


namespace Helix {
namespace Logic {
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/DOStmt.sql.xml
  */
class DOStmt
{
	public:

		/// All Data Members are public
		twine Comment;
		twine Sql;
		twine StmtName;
		twine StmtType;
		twine doguid;
		twine guid;
		twine projdataguid;


		/// Any Child Vectors will be defined here
		DOStmtInput_svect DOStmtInputs;
		DOStmtOutput_svect DOStmtOutputs;


		/// Standard Constructor
		DOStmt();

		/// Standard Copy Constructor
		DOStmt(const DOStmt& c);

		/// Standard Assignment Operator
		DOStmt& operator=(const DOStmt& c);

		/// Standard Destructor
		virtual ~DOStmt();

		/// Initialize this data object to have all empty or 0 values.
		DOStmt& init();

		/// Call check_size() on all of our twine members.
		DOStmt& checkSize();

		/// Construct from an XML Node
		DOStmt(xmlNodePtr node);

		/// Read an XML Node to set our contents
		DOStmt& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<DOStmt* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<DOStmt* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<DOStmt* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<DOStmt* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/DOStmt.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new data object statement entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into dostmt (guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql)
			values ( ?, ?, ?, ?, ?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, DOStmt& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, DOStmt& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< DOStmt* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, DOStmt& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into dostmt (guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql) 			values ( ?, ?, ?, ?, ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given data object statement in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update dostmt
			set StmtName = ?,
				StmtType = ?,
				projdataguid = ?,
				Comment = ?,
				Sql = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& StmtName, twine& StmtType, twine& projdataguid, twine& Comment, twine& Sql, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& StmtName, twine& StmtType, twine& projdataguid, twine& Comment, twine& Sql, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& StmtName, twine& StmtType, twine& projdataguid, twine& Comment, twine& Sql, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update dostmt 			set StmtName = ?, 				StmtType = ?, 				projdataguid = ?, 				Comment = ?, 				Sql = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a data object statement by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from dostmt
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
			return "delete from dostmt 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes all data object statements for a given data object
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from dostmt
			where doguid = ?
		
		  * </pre>
		  */
		static void deleteByDOID(SqlDB& sqldb, twine& doguid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteByDOID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteByDOID_prepSQL(IOConn& ioc, twine& doguid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteByDOID_getSQL() {
			return "delete from dostmt 			where doguid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all data object statements for a given data object
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql
			from dostmt
			where doguid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>doguid</li>
		  *   <li>StmtName</li>
		  *   <li>StmtType</li>
		  *   <li>projdataguid</li>
		  *   <li>Comment</li>
		  *   <li>Sql</li>
		  * </ul>
		  */
		static vector<DOStmt* >* selectAllForDO(SqlDB& sqldb, twine& doguid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<DOStmt* >* selectAllForDO(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForDO_prepSQL(IOConn& ioc, twine& doguid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForDO_getSQL() {
			return "select guid, doguid, StmtName, StmtType, projdataguid, Comment, Sql 			from dostmt 			where doguid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the DOStmt
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * DOStmt_svect myVect = DOStmt::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< DOStmt* >, DOStmt::deleteVector> DOStmt_svect;

}}} // End Namespace stack

#endif // DOSTMT_H defined
