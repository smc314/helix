/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#ifndef TESTSTATS_H
#define TESTSTATS_H

#include <map>
using namespace std;

#include <twine.h>
#include <AnException.h>
using namespace SLib;

namespace Helix {
namespace Test {

/**
 * This class defines a collection of statistics that are captured about the tests throughout
 * the execution of the tests.
 */
class TestStats
{
	private:
		/** Keep the constructor private so that there's only one instance of this object
		 * in memory during a run of the test engine.
		 */
		TestStats();

	public:
		
		/** Use this method to get an instance of this class.
		 */
		static TestStats& getInstance();

		// Standard Destructor
		~TestStats();

		/// Test Count
		int TestCount;

		/// Test Success
		int TestSuccess;

		/// Test Failure
		int TestFailure;

}; // End TestStats class


} } // End namespace stack

#endif // TESTSTATS_H Defined
