/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "ActionClass.h"
using namespace Helix::Glob;

static map_type* _ActionClassFactoryMap = NULL;

ActionClass* ActionClassFactory::createInstance(twine className, xmlNodePtr node) 
{
	map_type::iterator it = getMap()->find(className);
	if(it == getMap()->end()){
		DEBUG(FL, "ActionClassFactory::createInstance( %s , node) - no class found", className() );
		DEBUG(FL, "ActionClassFactory::map size: %d", getMap()->size() );
		throw AnException(0, FL, "ActionClassFactory::createInstance( %s , node) - no class found", className() );
	}
	return it->second(node);

}

map_type* ActionClassFactory::getMap()
{
	if(_ActionClassFactoryMap == NULL){
		_ActionClassFactoryMap = new map_type;
	}
	return _ActionClassFactoryMap;
}

ActionClass::~ActionClass()
{

}

bool ActionClass::isLongRunning()
{
	return false; // the default is to return false.
}

twine ActionClass::lrTaskName()
{
	return "Action Class - Generic Task Name";
}
