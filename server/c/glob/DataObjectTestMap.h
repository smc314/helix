/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef DATAOBJECTTESTMAP_H
#define DATAOBJECTTESTMAP_H

#include <map>
#include <vector>
using namespace std;

#include <twine.h>
#include <Mutex.h>
using namespace SLib;

namespace Helix {
namespace Glob {


class DLLEXPORT DataObjectTestClass;

class DLLEXPORT DataObjectTestMap {
	
	public:
		static DataObjectTestMap& getInstance(void);
	
		/** Add an action to our map by passing in the name and handler information directly.
		 *  We will update our records with the appropriate details.
		 */
		void addDataObjectTest(twine name, twine handler);
	
		/** Allows the caller to clear out our action maps for re-loading
		 * 
		 */
		void clearMap(void);

		/** Finds the appropriate action, based on the action name.  We search for Logic
		 * actions first, and then HTML actions.  If nothing appropriate is found, we
		 * return null.
		 * 
		 */
		DataObjectTestClass* findDOTest(twine name);

		/** Returns a list of all of the class names that we know about.
		  * 
		  */
		vector<pair<twine, twine> > listHandlers();

		virtual ~DataObjectTestMap();

	protected:
		/// Maps test name to class name that will handle it.
		map<twine, twine> m_tests;

		Mutex* m_mut;
	
	private:
		/** Keep the constructor private so that there's only one instance of
		 * this object in memory during a run of the server.
		 */
		DataObjectTestMap();
		DataObjectTestMap(const DataObjectTestMap& c);
		DataObjectTestMap& operator=(const DataObjectTestMap& c);

	
	
};

}} // End Namespace Helix::Glob

#endif // DATAOBJECTTESTMAP_H defined
