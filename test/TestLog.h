/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#ifndef TESTLOG_H
#define TESTLOG_H

#include <map>
using namespace std;

#include <twine.h>
#include <AnException.h>
using namespace SLib;

namespace Helix {
namespace Test {

/**
 * This class defines a collection of logging functions for the test to use to output information
 * to the user.
 */
class TestLog
{
	private:
		/** Keep the constructor private so that there's only one instance of this object
		 * in memory during a run of the test engine.
		 */
		TestLog();

	public:
		
		/** Use this method to get an instance of this class.
		 */
		static TestLog& getInstance();

		// Standard Destructor
		~TestLog();

		static void LogTest(bool in, bool fail, const twine& methodName);
		static void LogStep(const twine& message);
		static void LogError(const twine& message);
		static void LogHtml(const twine& message);

		// Whether to log everything
		bool LogAll;

		// Whether to log tests
		bool LogTests;

		// Whether to log steps
		bool LogSteps;

		// Whether to log Errors
		bool LogErrors;

		// Whether to log Html
		bool LogHtmls;

}; // End TestLog class


} } // End namespace stack

#endif // TESTLOG_H Defined
