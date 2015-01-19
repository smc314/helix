/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef ROW_TEST_H
#define ROW_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "Row.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called Row.
  */
class RowTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		RowTest(const RowTest& c) {}

		/// Assignment operator is private to prevent use
		RowTest& operator=(const RowTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< RowTest > reg;

	public:

		/// Standard Constructor
		RowTest();

		/// Standard Destructor
		virtual ~RowTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( Row* first, Row* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< Row* >* first, vector< Row* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Row.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the Row.unused method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unused(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // ROW_TEST_H defined
