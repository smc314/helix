/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SQLSTMT_H
#define SQLSTMT_H

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

#include "Col.h"
#include "Col.h"
#include "Row.h"
#include "Row.h"


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/admin/SQLStmt.sql.xml
  */
class SQLStmt
{
	public:

		/// All Data Members are public
		twine Description;
		float Duration;
		twine StatementName;
		intptr_t expectErrors;
		twine expectedErrorMsg;
		intptr_t expectedRows;
		intptr_t ignoreErrors;
		intptr_t isSelected;
		intptr_t issueCommit;
		intptr_t issueRollback;
		intptr_t newConnection;
		intptr_t status;
		twine statusMessage;
		twine stmt;
		intptr_t verifyData;


		/// Any Child Vectors will be defined here
		Col_svect MetaData;
		Col_svect MetaDataCheck;
		Row_svect Results;
		Row_svect ResultsCheck;


		/// Standard Constructor
		SQLStmt();

		/// Standard Copy Constructor
		SQLStmt(const SQLStmt& c);

		/// Standard Assignment Operator
		SQLStmt& operator=(const SQLStmt& c);

		/// Standard Destructor
		virtual ~SQLStmt();

		/// Initialize this data object to have all empty or 0 values.
		SQLStmt& init();

		/// Call check_size() on all of our twine members.
		SQLStmt& checkSize();

		/// Construct from an XML Node
		SQLStmt(xmlNodePtr node);

		/// Read an XML Node to set our contents
		SQLStmt& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<SQLStmt* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<SQLStmt* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<SQLStmt* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/SQLStmt.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is here to allow us to define the SQLTests data object.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Empty on purpose
		
		  * </pre>
		  */
		static void unused(OdbcObj& odbc, SQLStmt& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unused(OdbcObj& odbc, twine& stmt, bool useInputs, SQLStmt& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unused_prepSQL(IOConn& ioc, SQLStmt& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unused_getSQL() {
			return "-- Empty on purpose";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the SQLStmt
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * SQLStmt_svect myVect = SQLStmt::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< SQLStmt* >, SQLStmt::deleteVector> SQLStmt_svect;

}}} // End Namespace stack

#endif // SQLSTMT_H defined
