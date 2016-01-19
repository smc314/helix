/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef DATAOBJECTTESTCLASS_H
#define DATAOBJECTTESTCLASS_H

#include <twine.h>
#include <xmlinc.h>
using namespace SLib;

#include "IOConn.h"
#include "DataObjectTestMap.h"

namespace Helix {
namespace Glob {


class DLLEXPORT DataObjectTestClass 
{

	public:
		/// Are we running in record mode or not?
		bool m_recordMode;

		virtual ~DataObjectTestClass();
		virtual void setRecordMode( bool tf );
		virtual void runTests(IOConn& ioc, xmlNodePtr node) = 0;

};

template<typename T> DataObjectTestClass* createTestClass() { return new T(); }
typedef std::map<twine, DataObjectTestClass*(*)() > test_class_map_type;	

class DLLEXPORT DataObjectTestClassFactory 
{
	public:

		static DataObjectTestClass* createInstance(twine className);

	protected:
		static test_class_map_type* getMap();

};

template<typename T>
class DLLEXPORT DataObjectTestClassRegister : DataObjectTestClassFactory
{
	public:
		DataObjectTestClassRegister(twine className, twine act1 = ""){
			(*(getMap()))[className] = &createTestClass<T>;
			DataObjectTestMap::getInstance().addDataObjectTest(act1, className);
		}
};


}} // End Namespace Helix::Glob

#endif // DATAOBJECTTESTCLASS_H Defined
