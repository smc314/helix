/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "IOAdapter.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Log.h>
using namespace SLib;

IOAdapter::IOAdapter()
{
	EnEx ee(FL, "IOAdapter::IOAdapter()");


}

IOAdapter::IOAdapter(const IOAdapter& c)
{
	EnEx ee(FL, "IOAdapter::IOAdapter(const IOAdapter& c)");


}

IOAdapter& IOAdapter::operator=(const IOAdapter& c)
{
	EnEx ee(FL, "IOAdapter::operator=(const IOAdapter& c)");


	return *this;
}

IOAdapter::~IOAdapter()
{
	EnEx ee(FL, "IOAdapter::~IOAdapter()");


}

void IOAdapter::Execute(void)
{
	EnEx ee(FL, "IOAdapter::Execute()");

}

static iomap_type* _IOAdapterFactoryMap = NULL;

IOAdapter* IOAdapterFactory::createInstance(const twine& className) 
{
	iomap_type::iterator it = getMap()->find(className);
	if(it == getMap()->end() ){
		DEBUG(FL, "IOAdapterFactory::createInstance( %s ) - can't find class for name.", className() );
		DEBUG(FL, "Map size is %d", getMap()->size() );
		throw AnException(0, FL, "IOAdapterFactory::createInstance( %s ) - can't find class for name.",
			className() );
	}
	return it->second();
}

iomap_type* IOAdapterFactory::getMap()
{
	if(_IOAdapterFactoryMap == NULL){
		_IOAdapterFactoryMap = new iomap_type;
	}
	return _IOAdapterFactoryMap;
}

