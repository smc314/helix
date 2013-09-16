/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "ActionLogic.h"
using namespace Helix::Glob;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
using namespace SLib;

// Adds us to the global ActionClass Registry:
ActionClassRegister<ActionLogic> ActionLogic::reg("ActionLogic");

ActionLogic::ActionLogic(xmlNodePtr action)
{
	EnEx ee(FL, "ActionLogic::ActionLogic(xmlNodePtr action)");
	
	m_requires_session = true;

}

ActionLogic::ActionLogic(const ActionLogic& c)
{
	EnEx ee(FL, "ActionLogic::ActionLogic(const ActionLogic& c)");

	m_requires_session = c.m_requires_session;
}

ActionLogic& ActionLogic::operator=(const ActionLogic& c)
{
	EnEx ee(FL, "ActionLogic::operator=(const ActionLogic& c)");

	m_requires_session = c.m_requires_session;
	return *this;
}

ActionLogic::~ActionLogic()
{

}

void ActionLogic::ExecuteRequest(IOConn& ioc)
{
	EnEx ee(FL, "ActionLogic::ExecuteRequest(IOConn& ioc)", true);

	// Send a simple welcome page back to the caller:
	File index("../html/index.html");
	dptr<unsigned char> data;
	data = index.readContents();

	Date expires;
	ioc.SendReturn(data, index.size(), index.name(), index.lastModified(), expires);
	ioc.Close();
}
