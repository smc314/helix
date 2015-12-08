/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#ifndef TESTCACHE_H
#define TESTCACHE_H

#include <map>
using namespace std;

#include <twine.h>
#include <AnException.h>
using namespace SLib;

namespace Helix {
namespace Test {

/**
 * This class defines a cache of settings that are used at runtime by the testing
 * framework.  This is a singleton and can be accessed throughout the test code.
 *
 */
class TestCache
{
	private:
		/** Keep the constructor private so that there's only one instance of this object
		 * in memory during a run of the test engine.
		 */
		TestCache();

	public:
		
		/** Use this method to get an instance of this class.
		 */
		static TestCache& getInstance();

		/** Shortcut for TestCache.getInstance().GetCacheItem()
		 */
		static twine& get(const twine& lookupkey);

		/** Shortcut for TestCache.getInstance().GetCacheItem()
		 */
		static int getInt(const twine& lookupkey);

		/** Shortcut for TestCache.getInstance().GetCacheItem()
		 */
		static bool getBool(const twine& lookupkey);

		// Standard Destructor
		~TestCache();

		/// Tests for presence of the item in our cache.
		bool HasCacheItem(const twine& lookupkey);

		/// Returns the item requested from our cache
		twine& GetCacheItem(const twine& lookupkey);

		/// Adds the given item to our cache or replaces it if already present
		void AddCacheItem(const twine& lookupkey, const twine& value);

		/// Replaces all ${...} strings in a value by looking up the names in our cache.
		twine& ReplaceVars(twine& value);

	protected:

		/// This is our cache of strings
		map<twine, twine> m_cache;


}; // End TestCache class


} } // End namespace stack

#endif // TESTCACHE_H Defined
