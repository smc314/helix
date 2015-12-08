/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TestMap.h"
#include "DynamicTest.h"
using namespace Helix::Test;

#include <EnEx.h>
#include <Log.h>
#include <Lock.h>
#include <AnException.h>
using namespace SLib;

static TestMap* m_testmap = NULL;

TestMap::TestMap(void)
{
	EnEx ee(FL, "TestMap::TestMap(void)");

	m_mut = new Mutex();
	clearMap();

}

TestMap::TestMap(const TestMap& c)
{
	EnEx ee(FL, "TestMap::TestMap(const TestMap& c)");

	// does nothing
}

TestMap& TestMap::operator=(const TestMap& c)
{
	EnEx ee(FL, "TestMap::operator=(const TestMap& c)");

	// does nothing
	return *this;
}

TestMap::~TestMap(void)
{
	EnEx ee(FL, "TestMap::~TestMap()");

	clearMap();
	delete m_mut;
}

TestMap& TestMap::getInstance()
{
	EnEx ee(FL, "TestMap::getInstance()");

	if(m_testmap == NULL){
		m_testmap = new TestMap();
	}
	return *m_testmap;
}

void TestMap::addTest(twine name, twine handler)
{
	EnEx ee(FL, "TestMap::addTest()");
	Lock theLock(m_mut);

	if(m_tests.count(name) > 0){
		m_tests.erase(name); // replace it.
	}
	m_tests[name] = handler;

}

void TestMap::clearMap() 
{
	EnEx ee(FL, "TestMap::clearMap()");
	Lock theLock(m_mut);

	m_tests.clear();
}

DynamicTest* TestMap::findTest(twine name)
{
	EnEx ee(FL, "TestMap::findAction()");
	Lock theLock(m_mut);
	
	if(m_tests.count(name) > 0){
		twine actionLogicHandler = m_tests[name];
		DynamicTest* ret = DynamicTestFactory::createInstance(actionLogicHandler, NULL);
		return ret;
	} else {
		return NULL;
	}
}

vector<pair<twine, twine> > TestMap::listHandlers()
{
	EnEx ee(FL, "TestMap::listHandlers()");
	Lock theLock(m_mut);

	vector<pair<twine, twine> > ret;
	map<twine, twine>::iterator it;
	for(it = m_tests.begin(); it != m_tests.end(); it++){
		pair<twine, twine> elem;
		elem.first = it->second;
		elem.second = it->first;
		ret.push_back( elem );		
	}

	return ret;
}
