/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef COL_TEST_H
#define COL_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "Col.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called Col.
  */
class ColTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		ColTest(const ColTest& c) {}

		/// Assignment operator is private to prevent use
		ColTest& operator=(const ColTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< ColTest > reg;

	public:

		/// Standard Constructor
		ColTest();

		/// Standard Destructor
		virtual ~ColTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( Col* first, Col* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< Col* >* first, vector< Col* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Col.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the Col.unused method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void unused(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // COL_TEST_H defined
