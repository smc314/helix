/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef LOGSETTINGS_H
#define LOGSETTINGS_H

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
  * ../logic/util/LogSettings.sql.xml
  */
class LogSettings
{
	public:

		/// All Data Members are public
		intptr_t BufferSize;
		twine LogFile;
		intptr_t MaxSize;
		intptr_t debug;
		intptr_t debugCapture;
		intptr_t debugDump;
		intptr_t error;
		intptr_t errorCapture;
		intptr_t errorDump;
		intptr_t info;
		intptr_t infoCapture;
		intptr_t infoDump;
		intptr_t panic;
		intptr_t panicCapture;
		intptr_t panicDump;
		intptr_t sql;
		intptr_t sqlCapture;
		intptr_t sqlDump;
		intptr_t trace;
		intptr_t traceCapture;
		intptr_t traceDump;
		intptr_t warn;
		intptr_t warnCapture;
		intptr_t warnDump;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		LogSettings();

		/// Standard Copy Constructor
		LogSettings(const LogSettings& c);

		/// Standard Assignment Operator
		LogSettings& operator=(const LogSettings& c);

		/// Standard Destructor
		virtual ~LogSettings();

		/// Initialize this data object to have all empty or 0 values.
		LogSettings& init();

		/// Call check_size() on all of our twine members.
		LogSettings& checkSize();

		/// Construct from an XML Node
		LogSettings(xmlNodePtr node);

		/// Read an XML Node to set our contents
		LogSettings& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<LogSettings* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<LogSettings* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<LogSettings* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/LogSettings.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This statement is merely here to define the data structure that is
			passed back and forth to specify log file settings.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Nothing here
		
		  * </pre>
		  */
		static void unusedSqlStmt(OdbcObj& odbc, LogSettings& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, LogSettings& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unusedSqlStmt_prepSQL(IOConn& ioc, LogSettings& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unusedSqlStmt_getSQL() {
			return "-- Nothing here";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the LogSettings
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * LogSettings_svect myVect = LogSettings::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< LogSettings* >, LogSettings::deleteVector> LogSettings_svect;

}}} // End Namespace stack

#endif // LOGSETTINGS_H defined
