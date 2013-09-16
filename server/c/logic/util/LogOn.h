/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef LOGON_H
#define LOGON_H

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
  * ../logic/util/LogOn.sql.xml
  */
class LogOn
{
	public:

		/// All Data Members are public
		twine Alias;
		twine ConnName;
		twine Host;
		twine Pass;
		twine Port;
		twine User;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		LogOn();

		/// Standard Copy Constructor
		LogOn(const LogOn& c);

		/// Standard Assignment Operator
		LogOn& operator=(const LogOn& c);

		/// Standard Destructor
		virtual ~LogOn();

		/// Initialize this data object to have all empty or 0 values.
		LogOn& init();

		/// Call check_size() on all of our twine members.
		LogOn& checkSize();

		/// Construct from an XML Node
		LogOn(xmlNodePtr node);

		/// Read an XML Node to set our contents
		LogOn& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<LogOn* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<LogOn* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<LogOn* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/LogOn.sql.xml */
		/* ******************************************************************************** */


		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
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
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>Host</li>
		  *   <li>Port</li>
		  *   <li>User</li>
		  *   <li>Pass</li>
		  *   <li>ConnName</li>
		  *   <li>Alias</li>
		  * </ul>
		  */
		static vector<LogOn* >* unusedSqlStmt(OdbcObj& odbc, twine& Host, twine& Port, twine& User, twine& Pass, twine& Alias);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<LogOn* >* unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, twine& Host, twine& Port, twine& User, twine& Pass, twine& Alias);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unusedSqlStmt_prepSQL(IOConn& ioc, twine& Host, twine& Port, twine& User, twine& Pass, twine& Alias);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unusedSqlStmt_getSQL() {
			return "-- Nothing here";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the LogOn
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * LogOn_svect myVect = LogOn::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< LogOn* >, LogOn::deleteVector> LogOn_svect;

}}} // End Namespace stack

#endif // LOGON_H defined
