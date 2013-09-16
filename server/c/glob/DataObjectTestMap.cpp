/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "DataObjectTestMap.h"
#include "DataObjectTestClass.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Log.h>
#include <Lock.h>
#include <AnException.h>
using namespace SLib;

static DataObjectTestMap* m_dotestmap = NULL;


DataObjectTestMap::DataObjectTestMap(void)
{
	EnEx ee(FL, "DataObjectTestMap::DataObjectTestMap(void)");

	m_mut = new Mutex();
	clearMap();

}


DataObjectTestMap::DataObjectTestMap(const DataObjectTestMap& c)
{
	EnEx ee(FL, "DataObjectTestMap::DataObjectTestMap(const DataObjectTestMap& c)");

	// does nothing
}

DataObjectTestMap& DataObjectTestMap::operator=(const DataObjectTestMap& c)
{
	EnEx ee(FL, "DataObjectTestMap::operator=(const DataObjectTestMap& c)");

	// does nothing
	return *this;
}

DataObjectTestMap::~DataObjectTestMap(void)
{
	EnEx ee(FL, "DataObjectTestMap::~DataObjectTestMap()");

	clearMap();
	delete m_mut;
}

DataObjectTestMap& DataObjectTestMap::getInstance()
{
	EnEx ee(FL, "DataObjectTestMap::getInstance()");

	if(m_dotestmap == NULL){
		m_dotestmap = new DataObjectTestMap();
	}
	return *m_dotestmap;
}

void DataObjectTestMap::addDataObjectTest(twine name, twine handler)
{
	EnEx ee(FL, "DataObjectTestMap::addDataObjectTest()");
	Lock theLock(m_mut);

	if(m_tests.count(name) > 0){
		m_tests.erase(name); // replace it.
	}
	m_tests[name] = handler;

}

void DataObjectTestMap::clearMap() 
{
	EnEx ee(FL, "DataObjectTestMap::clearMap()");
	Lock theLock(m_mut);

	m_tests.clear();
}

DataObjectTestClass* DataObjectTestMap::findDOTest(twine name)
{
	EnEx ee(FL, "DataObjectTestMap::findAction()");
	Lock theLock(m_mut);
	
	if(m_tests.count(name) > 0){
		twine doTestHandler = m_tests[name];
		DataObjectTestClass* ret = DataObjectTestClassFactory::createInstance(doTestHandler);
		return ret;
	} else {
		return NULL;
	}
	
}

vector<pair<twine, twine> > DataObjectTestMap::listHandlers()
{
	EnEx ee(FL, "DataObjectTestMap::listHandlers()");
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
