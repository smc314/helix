/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SCHEDITEM_TEST_H
#define SCHEDITEM_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "SchedItem.h"
using namespace Helix::Logic::util;


namespace Helix {
namespace Logic {
namespace util {

/** This is a generated data object test class that is used for testing the data
  * object called SchedItem.
  */
class SchedItemTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		SchedItemTest(const SchedItemTest& c) {}

		/// Assignment operator is private to prevent use
		SchedItemTest& operator=(const SchedItemTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< SchedItemTest > reg;

	public:

		/// Standard Constructor
		SchedItemTest();

		/// Standard Destructor
		virtual ~SchedItemTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( SchedItem* first, SchedItem* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< SchedItem* >* first, vector< SchedItem* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/SchedItem.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the SchedItem.insert method.  We will use our list of output
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
		void updateLastRun(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the " + doName + "." + methodName + " method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void deleteByID(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the SchedItem.selectAll method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectAll(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the SchedItem.selectByID method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectByID(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // SCHEDITEM_TEST_H defined
