/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SQLSTATEMENT_TEST_H
#define SQLSTATEMENT_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "SQLStatement.h"
using namespace Helix::Logic::util;


namespace Helix {
namespace Logic {
namespace util {

/** This is a generated data object test class that is used for testing the data
  * object called SQLStatement.
  */
class SQLStatementTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		SQLStatementTest(const SQLStatementTest& c) {}

		/// Assignment operator is private to prevent use
		SQLStatementTest& operator=(const SQLStatementTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< SQLStatementTest > reg;

	public:

		/// Standard Constructor
		SQLStatementTest();

		/// Standard Destructor
		virtual ~SQLStatementTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( SQLStatement* first, SQLStatement* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< SQLStatement* >* first, vector< SQLStatement* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/SQLStatement.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the SQLStatement.unusedSqlStmt method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unusedSqlStmt(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // SQLSTATEMENT_TEST_H defined
