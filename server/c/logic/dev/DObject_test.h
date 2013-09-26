/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef DOBJECT_TEST_H
#define DOBJECT_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "DObject.h"
using namespace Helix::Logic::dev;


namespace Helix {
namespace Logic {
namespace dev {

/** This is a generated data object test class that is used for testing the data
  * object called DObject.
  */
class DObjectTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		DObjectTest(const DObjectTest& c) {}

		/// Assignment operator is private to prevent use
		DObjectTest& operator=(const DObjectTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< DObjectTest > reg;

	public:

		/// Standard Constructor
		DObjectTest();

		/// Standard Destructor
		virtual ~DObjectTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( DObject* first, DObject* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< DObject* >* first, vector< DObject* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/DObject.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the DObject.insert method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void insert(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the " + doName + "." + methodName + " method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void update(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the " + doName + "." + methodName + " method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void deleteByID(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the DObject.selectAllForApp method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectAllForApp(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // DOBJECT_TEST_H defined
