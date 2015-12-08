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

#include "DynamicTest.h"
#include "TestLog.h"
using namespace Helix::Test;

DynamicTest::DynamicTest()
{
	EnEx ee(FL, "DynamicTest::DynamicTest()");

	m_testPassed = false;
	m_shouldWork = true;
	m_stopOnFailure = false;
	m_name = "unknown generic test";
	m_testNode = NULL;
}

DynamicTest::DynamicTest(xmlNodePtr testNode)
{
	EnEx ee(FL, "DynamicTest::DynamicTest(xmlNodePtr testNode)");

	m_testNode = testNode; // Save this for future reference.
	m_testPassed = false;
	m_name.getAttribute(m_testNode, "name");
	m_type = testNode->name;
	m_stopOnFailure = XmlHelpers::getBoolAttr(m_testNode, "stopOnFailure");
	twine expect(m_testNode, "expect");
	if(expect == "success"){
		m_shouldWork = true;
	} else {
		m_shouldWork = false;
	}

	xmlNodePtr node;
	node = XmlHelpers::FindChild(m_testNode, "FunctionalAreas");
	if(node != NULL){
		twine tmp = XmlHelpers::getTextNodeValue(node);
		tmp.rtrim();
		if(tmp.length() > 0){
			m_functionalAreas = tmp.split(",");
		}
	}
	node = XmlHelpers::FindChild(m_testNode, "Provides");
	if(node != NULL){
		twine tmp = XmlHelpers::getTextNodeValue(node);
		tmp.rtrim();
		if(tmp.length() > 0){
			m_provides = tmp.split(",");
		}
	}
	node = XmlHelpers::FindChild(m_testNode, "Requires");
	if(node != NULL){
		twine tmp = XmlHelpers::getTextNodeValue(node);
		tmp.rtrim();
		if(tmp.length() > 0){
			m_requires = tmp.split(",");
		}
	}
}

DynamicTest::~DynamicTest()
{
	EnEx ee(FL, "DynamicTest::~DynamicTest()");

}

const twine& DynamicTest::Name()
{
	return m_name;
}

const twine& DynamicTest::Type()
{
	return m_type;
}

xmlNodePtr DynamicTest::Node()
{
	return m_testNode;
}

void DynamicTest::Passed(bool tf)
{
	m_testPassed = tf;
}

bool DynamicTest::Passed()
{
	return m_testPassed;
}

bool DynamicTest::ShouldWork()
{
	return m_shouldWork;
}

const vector<twine>& DynamicTest::FunctionalAreas()
{
	return m_functionalAreas;
}

const vector<twine>& DynamicTest::Provides()
{
	return m_provides;
}

const vector<twine>& DynamicTest::Requires()
{
	return m_requires;
}

void DynamicTest::Run()
{
	EnEx ee(FL, "DynamicTest::Run()");

	throw AnException(0, FL, "Method must be overridden in child classes.");
}

void DynamicTest::WriteLine(const twine& message)
{
	EnEx ee(FL, "DynamicTest::WriteLine(const twine& message)");

	twine outputMessage = m_type + "[" + m_name + "]: " + message;
	printf("%s\n", outputMessage());
}

void DynamicTest::Describe()
{
	EnEx ee(FL, "DynamicTest::Describe()");

	WriteLine("Test Description");
	WriteLine("Functional Areas:");
	for(size_t i = 0; i < m_functionalAreas.size(); i++){
		WriteLine("\t" + m_functionalAreas[i]);
	}
	if(m_provides.size() != 0){
		WriteLine("Provides:");
		for(size_t i = 0; i < m_provides.size(); i++){
			WriteLine("\t" + m_provides[i]);
		}
	} else {
		WriteLine("Provides - none");
	}

	if(m_requires.size() != 0){
		WriteLine("Requires:");
		for(size_t i = 0; i < m_requires.size(); i++){
			WriteLine("\t" + m_requires[i]);
		}
	} else {
		WriteLine("Requires - none");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// Functions for the DynamicTestFactory and DynamicTestRegister
/////////////////////////////////////////////////////////////////////////////////////////

static map_type* _DynamicTestFactoryMap = NULL;

DynamicTest* DynamicTestFactory::createInstance(twine className, xmlNodePtr node)
{
	map_type::iterator it = getMap()->find(className);
	if(it == getMap()->end()){
		printf("DynamicTestFactory::createInstance(%s, node) - no class found\n", className() );
		printf("DynamicTestFactory::map size: %lu\n", getMap()->size() );
		return NULL;
	}
	return it->second(node);
}

map_type* DynamicTestFactory::getMap()
{
	if(_DynamicTestFactoryMap == NULL){
		_DynamicTestFactoryMap = new map_type;
	}
	return _DynamicTestFactoryMap;
}
