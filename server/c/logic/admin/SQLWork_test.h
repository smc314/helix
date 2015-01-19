/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SQLWORK_TEST_H
#define SQLWORK_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "SQLWork.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called SQLWork.
  */
class SQLWorkTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		SQLWorkTest(const SQLWorkTest& c) {}

		/// Assignment operator is private to prevent use
		SQLWorkTest& operator=(const SQLWorkTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< SQLWorkTest > reg;

	public:

		/// Standard Constructor
		SQLWorkTest();

		/// Standard Destructor
		virtual ~SQLWorkTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( SQLWork* first, SQLWork* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< SQLWork* >* first, vector< SQLWork* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/SQLWork.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the SQLWork.unused method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unused(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // SQLWORK_TEST_H defined
