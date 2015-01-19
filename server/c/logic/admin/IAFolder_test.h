/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef IAFOLDER_TEST_H
#define IAFOLDER_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "IAFolder.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called IAFolder.
  */
class IAFolderTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		IAFolderTest(const IAFolderTest& c) {}

		/// Assignment operator is private to prevent use
		IAFolderTest& operator=(const IAFolderTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< IAFolderTest > reg;

	public:

		/// Standard Constructor
		IAFolderTest();

		/// Standard Destructor
		virtual ~IAFolderTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( IAFolder* first, IAFolder* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< IAFolder* >* first, vector< IAFolder* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/IAFolder.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the IAFolder.unusedSqlStmt method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unusedSqlStmt(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // IAFOLDER_TEST_H defined
