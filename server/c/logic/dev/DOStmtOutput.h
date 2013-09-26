/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef DOSTMTOUTPUT_H
#define DOSTMTOUTPUT_H

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
  * ../logic/dev/DOStmtOutput.sql.xml
  */
class DOStmtOutput
{
	public:

		/// All Data Members are public
		twine VarName;
		twine VarType;
		twine dostmtguid;
		twine guid;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		DOStmtOutput();

		/// Standard Copy Constructor
		DOStmtOutput(const DOStmtOutput& c);

		/// Standard Assignment Operator
		DOStmtOutput& operator=(const DOStmtOutput& c);

		/// Standard Destructor
		virtual ~DOStmtOutput();

		/// Initialize this data object to have all empty or 0 values.
		DOStmtOutput& init();

		/// Call check_size() on all of our twine members.
		DOStmtOutput& checkSize();

		/// Construct from an XML Node
		DOStmtOutput(xmlNodePtr node);

		/// Read an XML Node to set our contents
		DOStmtOutput& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<DOStmtOutput* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<DOStmtOutput* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<DOStmtOutput* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/DOStmtOutput.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new data object statement output entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into dostmtoutput (guid, dostmtguid, VarName, VarType)
			values ( ?, ?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, DOStmtOutput& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, DOStmtOutput& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< DOStmtOutput* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, DOStmtOutput& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into dostmtoutput (guid, dostmtguid, VarName, VarType) 			values ( ?, ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given data object statement output in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update dostmtoutput
			set VarName = ?,
				VarType = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& VarName, twine& VarType, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& VarName, twine& VarType, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& VarName, twine& VarType, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update dostmtoutput 			set VarName = ?, 				VarType = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a data object statement output by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from dostmtoutput
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
			return "delete from dostmtoutput 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes all data object statement outputs for a given data object statement
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from dostmtoutput
			where dostmtguid = ?
		
		  * </pre>
		  */
		static void deleteByStmtID(SqlDB& sqldb, twine& dostmtguid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteByStmtID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& dostmtguid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteByStmtID_prepSQL(IOConn& ioc, twine& dostmtguid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteByStmtID_getSQL() {
			return "delete from dostmtoutput 			where dostmtguid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all data object statement outputs for a given data object stmt
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, dostmtguid, VarName, VarType
			from dostmtoutput
			where dostmtguid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>dostmtguid</li>
		  *   <li>VarName</li>
		  *   <li>VarType</li>
		  * </ul>
		  */
		static vector<DOStmtOutput* >* selectAllForDOStmt(SqlDB& sqldb, twine& dostmtguid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<DOStmtOutput* >* selectAllForDOStmt(SqlDB& sqldb, twine& stmt, bool useInputs, twine& dostmtguid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForDOStmt_prepSQL(IOConn& ioc, twine& dostmtguid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForDOStmt_getSQL() {
			return "select guid, dostmtguid, VarName, VarType 			from dostmtoutput 			where dostmtguid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the DOStmtOutput
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * DOStmtOutput_svect myVect = DOStmtOutput::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< DOStmtOutput* >, DOStmtOutput::deleteVector> DOStmtOutput_svect;

}}} // End Namespace stack

#endif // DOSTMTOUTPUT_H defined
