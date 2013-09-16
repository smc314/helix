/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "DataObjectTestClass.h"
using namespace Helix::Glob;

static test_class_map_type* _DataObjectTestClassFactoryMap = NULL;

DataObjectTestClass* DataObjectTestClassFactory::createInstance(twine className) 
{
	test_class_map_type::iterator it = getMap()->find(className);
	if(it == getMap()->end()){
		DEBUG(FL, "DataObjectTestClassFactory::createInstance( %s ) - no class found", className() );
		DEBUG(FL, "DataObjectTestClassFactory::map size: %d", getMap()->size() );
		throw AnException(0, FL, "DataObjectTestClassFactory::createInstance( %s ) - no class found", className() );
	}
	return it->second();

}

test_class_map_type* DataObjectTestClassFactory::getMap()
{
	if(_DataObjectTestClassFactoryMap == NULL){
		_DataObjectTestClassFactoryMap = new test_class_map_type;
	}
	return _DataObjectTestClassFactoryMap;
}

DataObjectTestClass::~DataObjectTestClass()
{

}

void DataObjectTestClass::setRecordMode( bool tf )
{
	m_recordMode = tf;
}
