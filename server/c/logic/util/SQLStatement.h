/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SQLSTATEMENT_H
#define SQLSTATEMENT_H

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
  * ../logic/util/SQLStatement.sql.xml
  */
class SQLStatement
{
	public:

		/// All Data Members are public
		twine HostDB;
		twine Sql;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		SQLStatement();

		/// Standard Copy Constructor
		SQLStatement(const SQLStatement& c);

		/// Standard Assignment Operator
		SQLStatement& operator=(const SQLStatement& c);

		/// Standard Destructor
		virtual ~SQLStatement();

		/// Initialize this data object to have all empty or 0 values.
		SQLStatement& init();

		/// Call check_size() on all of our twine members.
		SQLStatement& checkSize();

		/// Construct from an XML Node
		SQLStatement(xmlNodePtr node);

		/// Read an XML Node to set our contents
		SQLStatement& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<SQLStatement* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<SQLStatement* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<SQLStatement* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<SQLStatement* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/SQLStatement.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This statement is merely here to define the data structure that is
			passed back and forth to determine log on credentials.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Nothing here
		
		  * </pre>
		  */
		static void unusedSqlStmt(OdbcObj& odbc, SQLStatement& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, SQLStatement& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unusedSqlStmt_prepSQL(IOConn& ioc, SQLStatement& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unusedSqlStmt_getSQL() {
			return "-- Nothing here";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the SQLStatement
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * SQLStatement_svect myVect = SQLStatement::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< SQLStatement* >, SQLStatement::deleteVector> SQLStatement_svect;

}}} // End Namespace stack

#endif // SQLSTATEMENT_H defined
