/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef LOGMESSAGEFILTER_H
#define LOGMESSAGEFILTER_H

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
  * ../logic/util/LogMessageFilter.sql.xml
  */
class LogMessageFilter
{
	public:

		/// All Data Members are public
		twine AppName;
		intptr_t Debug;
		intptr_t DispApp;
		intptr_t DispChannel;
		intptr_t DispDate;
		intptr_t DispFile;
		intptr_t DispId;
		intptr_t DispLine;
		intptr_t DispMachine;
		intptr_t DispThread;
		intptr_t Error;
		intptr_t FilterMatchCount;
		twine FindByDate;
		intptr_t FindByID;
		twine FindByMsg;
		intptr_t FirstRow;
		intptr_t Forward;
		intptr_t GetMax;
		intptr_t Info;
		intptr_t LastRow;
		twine LogFile;
		intptr_t LogFileNewestID;
		intptr_t LogFileOldestID;
		twine MachineName;
		twine Message;
		intptr_t Panic;
		twine SUID;
		intptr_t ShowColApplication;
		intptr_t ShowColChannel;
		intptr_t ShowColDate;
		intptr_t ShowColFile;
		intptr_t ShowColID;
		intptr_t ShowColIcon;
		intptr_t ShowColLine;
		intptr_t ShowColMachine;
		intptr_t ShowColMessage;
		intptr_t ShowColSUID;
		intptr_t ShowColThread;
		intptr_t SqlTrace;
		intptr_t StartId;
		intptr_t ThreadID;
		intptr_t Trace;
		intptr_t Warn;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		LogMessageFilter();

		/// Standard Copy Constructor
		LogMessageFilter(const LogMessageFilter& c);

		/// Standard Assignment Operator
		LogMessageFilter& operator=(const LogMessageFilter& c);

		/// Standard Destructor
		virtual ~LogMessageFilter();

		/// Initialize this data object to have all empty or 0 values.
		LogMessageFilter& init();

		/// Call check_size() on all of our twine members.
		LogMessageFilter& checkSize();

		/// Construct from an XML Node
		LogMessageFilter(xmlNodePtr node);

		/// Read an XML Node to set our contents
		LogMessageFilter& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<LogMessageFilter* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<LogMessageFilter* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<LogMessageFilter* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<LogMessageFilter* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/LogMessageFilter.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This statement is merely here to define the data structure that is
			passed back and forth to determine log filtering settings.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Nothing here
		
		  * </pre>
		  */
		static void unusedSqlStmt(OdbcObj& odbc, LogMessageFilter& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, LogMessageFilter& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unusedSqlStmt_prepSQL(IOConn& ioc, LogMessageFilter& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unusedSqlStmt_getSQL() {
			return "-- Nothing here";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the LogMessageFilter
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * LogMessageFilter_svect myVect = LogMessageFilter::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< LogMessageFilter* >, LogMessageFilter::deleteVector> LogMessageFilter_svect;

}}} // End Namespace stack

#endif // LOGMESSAGEFILTER_H defined
