/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef LOGON_TEST_H
#define LOGON_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "LogOn.h"
using namespace Helix::Logic::util;


namespace Helix {
namespace Logic {
namespace util {

/** This is a generated data object test class that is used for testing the data
  * object called LogOn.
  */
class LogOnTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		LogOnTest(const LogOnTest& c) {}

		/// Assignment operator is private to prevent use
		LogOnTest& operator=(const LogOnTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< LogOnTest > reg;

	public:

		/// Standard Constructor
		LogOnTest();

		/// Standard Destructor
		virtual ~LogOnTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( LogOn* first, LogOn* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< LogOn* >* first, vector< LogOn* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/LogOn.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the LogOn.unusedSqlStmt method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unusedSqlStmt(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // LOGON_TEST_H defined
