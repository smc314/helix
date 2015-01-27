/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef USER_TEST_H
#define USER_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "User.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called User.
  */
class UserTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		UserTest(const UserTest& c) {}

		/// Assignment operator is private to prevent use
		UserTest& operator=(const UserTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< UserTest > reg;

	public:

		/// Standard Constructor
		UserTest();

		/// Standard Destructor
		virtual ~UserTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( User* first, User* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< User* >* first, vector< User* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/User.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the User.insert method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void insert(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the User.insertAuth method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void insertAuth(IOConn& ioc, xmlNodePtr node);

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
		void updateAuth(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the " + doName + "." + methodName + " method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void deleteByID(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the " + doName + "." + methodName + " method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void deleteAuthByID(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the User.selectAll method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectAll(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the User.selectByID method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectByID(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the User.selectByUsername method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectByUsername(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // USER_TEST_H defined
