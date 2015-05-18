/* **************************************************************************

   Copyright (c): 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef ACTION_TEST_H
#define ACTION_TEST_H

#include "IOConn.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include "Action.h"
using namespace Helix::Logic::admin;


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object test class that is used for testing the data
  * object called Action.
  */
class ActionTest : public DataObjectTestClass
{
	private:
		/// Copy constructor is private to prevent use
		ActionTest(const ActionTest& c) {}

		/// Assignment operator is private to prevent use
		ActionTest& operator=(const ActionTest& c) { return *this; }

		/// Registers us with the global factory map
		static DataObjectTestClassRegister< ActionTest > reg;

	public:

		/// Standard Constructor
		ActionTest();

		/// Standard Destructor
		virtual ~ActionTest();

		/// Runs the tests contained in the given xmlNode
		virtual void runTests( IOConn& ioc, xmlNodePtr node );

		/// Compare two objects to see if they are the same
		static bool compareObjects( Action* first, Action* second);

		/// Compare two lists of objects to see if they are the same
		static bool compareLists( vector< Action* >* first, vector< Action* >* second);

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Action.sql.xml */
		/* ******************************************************************************** */

		/** This method will use our input XML document to prepare for and test
		  * the Action.insert method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void insert(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.addUserToAction method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void addUserToAction(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.addGroupToAction method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void addGroupToAction(IOConn& ioc, xmlNodePtr node);

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
		  * the " + doName + "." + methodName + " method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void removeUserFromAction(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the " + doName + "." + methodName + " method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void removeGroupFromAction(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.selectAll method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectAll(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.selectByID method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectByID(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.selectByPath method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectByPath(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.selectActionsForUser method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectActionsForUser(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.selectActionsForGroup method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectActionsForGroup(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.selectActionsForUserByGroup method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void selectActionsForUserByGroup(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.checkActionForUser method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void checkActionForUser(IOConn& ioc, xmlNodePtr node);

		/** This method will use our input XML document to prepare for and test
		  * the Action.checkActionForUserByGroup method.  We will use our list of output
		  * xml documents to verify the output of this method.  If the list of ourput
		  * documents is empty, we will simply ensure that no exceptions are thrown using
		  * the given XML input document.
		  */
		void checkActionForUserByGroup(IOConn& ioc, xmlNodePtr node);


};

}}} // End Namespace stack

#endif // ACTION_TEST_H defined
