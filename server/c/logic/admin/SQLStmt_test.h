/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SQLSTMT_TEST_H
#define SQLSTMT_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "SQLStmt.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called SQLStmt.
  */
class SQLStmtTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		SQLStmtTest(const SQLStmtTest& c) {}

		/// Assignment operator is private to prevent use
		SQLStmtTest& operator=(const SQLStmtTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< SQLStmtTest > reg;

	public:

		/// Standard Constructor
		SQLStmtTest();

		/// Standard Destructor
		virtual ~SQLStmtTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( SQLStmt* first, SQLStmt* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< SQLStmt* >* first, vector< SQLStmt* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/SQLStmt.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the SQLStmt.unused method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unused(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // SQLSTMT_TEST_H defined
