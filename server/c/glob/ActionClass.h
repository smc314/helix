/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ACTIONCLASS_H
#define ACTIONCLASS_H

#include <twine.h>
#include <xmlinc.h>
using namespace SLib;

#include "IOConn.h"
#include "ActionMap.h"

namespace Helix {
namespace Glob {


class ActionClass 
{

	public:
		twine m_name;
		twine m_license_group;
		bool m_requires_session;
		bool m_delete_required;

		virtual ~ActionClass();

		virtual void ExecuteRequest(IOConn& ioc) = 0;

		virtual bool isLongRunning();
		virtual twine lrTaskName();

};

template<typename T> ActionClass* createT(xmlNodePtr node) { return new T(node); }
typedef std::map<twine, ActionClass*(*)(xmlNodePtr) > map_type;	

class ActionClassFactory 
{
	public:

		static ActionClass* createInstance(twine className, xmlNodePtr node);

	protected:
		static map_type* getMap();

};

template<typename T>
class ActionClassRegister : ActionClassFactory
{
	public:
		ActionClassRegister(twine className, int type = 0, twine act1 = "", twine act2 = "", twine act3 = ""){
			(*(getMap()))[className] = &createT<T>;
			if(type != 0){
				if(type == 1){ // Logics
					if(!act1.empty()){
						ActionMap::getInstance().addLogicAction(act1, className);
					}
					if(!act2.empty()){
						ActionMap::getInstance().addLogicAction(act2, className);
					}
					if(!act3.empty()){
						ActionMap::getInstance().addLogicAction(act3, className);
					}
				} else if(type == 2) { // Html's
					if(!act1.empty()){
						ActionMap::getInstance().addHtmlAction(act1, className);
					}
					if(!act2.empty()){
						ActionMap::getInstance().addHtmlAction(act2, className);
					}
					if(!act3.empty()){
						ActionMap::getInstance().addHtmlAction(act3, className);
					}
				}
			}
		}
};


}} // End Namespace Helix::Glob

#endif // ACTIONCLASS_H Defined
