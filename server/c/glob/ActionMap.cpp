/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "ActionMap.h"
#include "ActionClass.h"
#include "ActionHtml.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Log.h>
#include <Lock.h>
#include <AnException.h>
using namespace SLib;

static ActionMap* m_actionmap = NULL;


ActionMap::ActionMap(void)
{
	EnEx ee(FL, "ActionMap::ActionMap(void)");

	m_mut = new Mutex();
	clearMap();

}


ActionMap::ActionMap(const ActionMap& c)
{
	EnEx ee(FL, "ActionMap::ActionMap(const ActionMap& c)");

	// does nothing
}

ActionMap& ActionMap::operator=(const ActionMap& c)
{
	EnEx ee(FL, "ActionMap::operator=(const ActionMap& c)");

	// does nothing
	return *this;
}

ActionMap::~ActionMap(void)
{
	EnEx ee(FL, "ActionMap::~ActionMap()");

	clearMap();
	delete m_mut;
}

ActionMap& ActionMap::getInstance()
{
	EnEx ee(FL, "ActionMap::getInstance()");

	if(m_actionmap == NULL){
		m_actionmap = new ActionMap();
	}
	return *m_actionmap;
}

void ActionMap::addLogicAction(twine name, twine handler)
{
	EnEx ee(FL, "ActionMap::addAction()");
	Lock theLock(m_mut);

	if(m_logics.count(name) > 0){
		m_logics.erase(name); // replace it.
	}
	m_logics[name] = handler;

}

void ActionMap::addHtmlAction(twine name, twine handler)
{
	EnEx ee(FL, "ActionMap::addAction()");
	Lock theLock(m_mut);

	ActionHtml* ah = new ActionHtml(name);
	ah->m_delete_required = false;
	m_html.push_back(ah);

}

void ActionMap::addAction(xmlNodePtr action)
{
	EnEx ee(FL, "ActionMap::addAction()");
	Lock theLock(m_mut);

	if(strcmp((const char*)action->name, "Action") != 0){
		throw AnException(0, FL, "Unknown node handed to addAction: %s", action->name );
	}
	twine type;
	type.getAttribute(action, "type");
	if(type.empty()){
		throw AnException(0, FL, "Action does not have a type!");
	}
	
	if(type == "logic"){
		twine name;
		twine handler;
		name.getAttribute(action, "name");
		handler.getAttribute(action, "handler");
		if(m_logics.count(name) > 0){
			m_logics.erase(name); // replace it.
		}
		m_logics[name] = handler;
	} else if(type == "html"){
		ActionHtml* ah = new ActionHtml(action);
		ah->m_delete_required = false;
		m_html.push_back(ah);
	} else {
		throw AnException(0, FL, "Unknown Action type: %s", type() );
	}

}

void ActionMap::clearMap() 
{
	EnEx ee(FL, "ActionMap::clearMap()");
	Lock theLock(m_mut);

	for(int i = 0; i < (int)m_html.size(); i++){
		delete m_html[i];
	}

	m_logics.clear();
	m_html.clear();
}

ActionClass* ActionMap::findAction(twine name)
{
	EnEx ee(FL, "ActionMap::findAction()");
	Lock theLock(m_mut);
	
	if(m_logics.count(name) > 0){
		twine actionLogicHandler = m_logics[name];
		ActionClass* ret = ActionClassFactory::createInstance(actionLogicHandler, NULL);
		ret->m_delete_required = true;
		return ret;
	} else {
		int max = 0;
		int max_index = -1;
		// Find the best match for this target url
		for(int i = 0; i < (int)m_html.size(); i++){
			int match_quality = m_html[i]->matchesURL(name);
			if(match_quality > max){
				max = match_quality;
				max_index = i;
			}
		}
		if(max_index != -1){
			return m_html[max_index];
		} else {
			return NULL;
		}
	}
	
}

vector<pair<twine, twine> > ActionMap::listHandlers()
{
	EnEx ee(FL, "ActionMap::listHandlers()");
	Lock theLock(m_mut);

	vector<pair<twine, twine> > ret;
	map<twine, twine>::iterator it;
	for(it = m_logics.begin(); it != m_logics.end(); it++){
		pair<twine, twine> elem;
		elem.first = it->second;
		elem.second = it->first;
		ret.push_back( elem );		
	}

	return ret;
}
