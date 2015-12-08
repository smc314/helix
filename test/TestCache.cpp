/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#include <EnEx.h>
#include <Log.h>
#include <Date.h>
#include <AnException.h>
using namespace SLib;

#include "TestCache.h"
using namespace Helix::Test;

static TestCache* m_testcache = NULL;

TestCache::TestCache()
{
	EnEx ee(FL, "TestCache::TestCache()");

}

TestCache& TestCache::getInstance()
{
	EnEx ee(FL, "TestCache::getInstance()");

	if(m_testcache == NULL){
		m_testcache = new TestCache();
	}
	return *m_testcache;
}

TestCache::~TestCache()
{
	EnEx ee(FL, "TestCache::~TestCache()");

}

bool TestCache::HasCacheItem(const twine& lookupkey)
{
	EnEx ee(FL, "TestCache::HasCacheItem()");

	if(m_cache.count(lookupkey) > 0){
		return true;
	} else {
		return false;
	}
}

twine& TestCache::GetCacheItem(const twine& lookupkey)
{
	EnEx ee(FL, "TestCache::GetCacheItem()");

	if(m_cache.count(lookupkey) > 0){
		return m_cache[ lookupkey ];
	} else {
		throw AnException(0, FL, "Item (%s) not found in TestCache", lookupkey() );
	}
}

void TestCache::AddCacheItem(const twine& lookupkey, const twine& value)
{
	EnEx ee(FL, "TestCache::AddCacheItem()");

	m_cache[ lookupkey ] = value;
}

twine& TestCache::get(const twine& lookupkey)
{
	return TestCache::getInstance().GetCacheItem(lookupkey);
}

int TestCache::getInt(const twine& lookupkey)
{
	twine value = TestCache::getInstance().GetCacheItem(lookupkey);
	return (int)value.get_int();
}

bool TestCache::getBool(const twine& lookupkey)
{
	twine value = TestCache::getInstance().GetCacheItem(lookupkey);
	twine uValue = value; // make a copy
	uValue.ucase();
	if(uValue == "TRUE" ||
		uValue == "YES" ||
		uValue == "ON" ||
		uValue == "1"
	){
		return true;
	} else {
		return false;
	}
}

twine& CheckAndReplace(twine& value, const twine& checkFor, const twine& replaceWith)
{
	size_t pos = value.find(checkFor);
	if(pos != TWINE_NOT_FOUND){
		value.replace(pos, checkFor.size(), replaceWith);
	}
	return value;
}

twine& TestCache::ReplaceVars(twine& value)
{
	EnEx ee(FL, "TestCache::ReplaceVars(const twine& value)");

	Date now;

	// First handle some special cases:
	CheckAndReplace(value, "${Date}", now.GetValue( "%Y/%m/%d") );
	CheckAndReplace(value, "${FileTime}", now.GetValue( "%Y%m%d%H%M%S" ) );

	// Now replace any cache references:
	size_t idx1, idx2;
	idx1 = value.find("${");
	while(idx1 != TWINE_NOT_FOUND){
		idx2 = value.find("}", idx1 + 2);
		if(idx2 == TWINE_NOT_FOUND){
			break;
		}
		twine key = value.substr(idx1 + 2, idx2 - idx1 - 2);
		if(HasCacheItem(key)){
			value.replace(idx1, idx2-idx1+1, GetCacheItem(key) );
			CheckAndReplace(value, "${Date}", now.GetValue( "%Y/%m/%d") );
			CheckAndReplace(value, "${FileTime}", now.GetValue( "%Y%m%d%H%M%S" ) );
		} else {
			break;
		}

		idx1 = value.find("${");
	}
	
	return value;
}

