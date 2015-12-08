/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef TESTMAP_H
#define TESTMAP_H

#include <map>
#include <vector>
using namespace std;

#include <twine.h>
#include <Mutex.h>
using namespace SLib;

namespace Helix {
namespace Test {

// Forward declaration to avoid circular references
class DynamicTest;

class TestMap {
	
	public:
		static TestMap& getInstance(void);
	
		/** Add a test to our map by passing in the name and handler information directly.
		 *  We will update our records with the appropriate details.
		 */
		void addTest(twine name, twine handler);
	
		/** Allows the caller to clear out our test maps for re-loading
		 */
		void clearMap(void);

		/** Finds the appropriate test, based on the test type.
		 * If nothing appropriate is found, we return null.
		 */
		DynamicTest* findTest(twine type);

		/** Returns a list of all of the test class names that we know about.
		  */
		vector<pair<twine, twine> > listHandlers();

		virtual ~TestMap();

	protected:
		/// Maps action type to class name that will handle it.
		map<twine, twine> m_tests;

		Mutex* m_mut;
	
	private:
		/** Keep the constructor private so that there's only one instance of
		 * this object in memory during a run of the server.
		 */
		TestMap();
		TestMap(const TestMap& c);
		TestMap& operator=(const TestMap& c);
	
};

}} // End Namespace Helix::Glob

#endif // TESTMAP_H defined
