/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef LOGOBJ_H
#define LOGOBJ_H

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
  * ../logic/util/LogObj.sql.xml
  */
class LogObj
{
	public:

		/// All Data Members are public
		twine SUID;
		twine appName;
		intptr_t channel;
		twine file;
		intptr_t id;
		intptr_t line;
		twine machineName;
		twine msg;
		intptr_t tid;
		intptr_t timestamp_a;
		intptr_t timestamp_b;
		twine timestamp_c;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		LogObj();

		/// Standard Copy Constructor
		LogObj(const LogObj& c);

		/// Standard Assignment Operator
		LogObj& operator=(const LogObj& c);

		/// Standard Destructor
		virtual ~LogObj();

		/// Initialize this data object to have all empty or 0 values.
		LogObj& init();

		/// Call check_size() on all of our twine members.
		LogObj& checkSize();

		/// Construct from an XML Node
		LogObj(xmlNodePtr node);

		/// Read an XML Node to set our contents
		LogObj& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<LogObj* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<LogObj* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogObj* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<LogObj* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/LogObj.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This statement is merely here to define the data structure that is
			passed back and forth as a log message
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Nothing here
		
		  * </pre>
		  */
		static void unusedSqlStmt(OdbcObj& odbc, LogObj& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, LogObj& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unusedSqlStmt_prepSQL(IOConn& ioc, LogObj& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unusedSqlStmt_getSQL() {
			return "-- Nothing here";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the LogObj
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * LogObj_svect myVect = LogObj::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< LogObj* >, LogObj::deleteVector> LogObj_svect;

}}} // End Namespace stack

#endif // LOGOBJ_H defined
