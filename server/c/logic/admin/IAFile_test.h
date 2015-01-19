/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef IAFILE_TEST_H
#define IAFILE_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "IAFile.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called IAFile.
  */
class IAFileTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		IAFileTest(const IAFileTest& c) {}

		/// Assignment operator is private to prevent use
		IAFileTest& operator=(const IAFileTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< IAFileTest > reg;

	public:

		/// Standard Constructor
		IAFileTest();

		/// Standard Destructor
		virtual ~IAFileTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( IAFile* first, IAFile* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< IAFile* >* first, vector< IAFile* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/IAFile.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the IAFile.unusedSqlStmt method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unusedSqlStmt(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // IAFILE_TEST_H defined
