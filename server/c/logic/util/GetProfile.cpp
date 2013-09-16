/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "SessionList.h"
using namespace Helix::Glob;

#include "GetProfile.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
using namespace SLib;

// Adds us to the global ActionClass Registry:
ActionClassRegister<GetProfile> GetProfile::reg("GetProfile", 1, "/logic/util/GetProfile");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetProfile Input=NULL

GetProfile::GetProfile(xmlNodePtr action)
{
	EnEx ee(FL, "GetProfile::GetProfile(xmlNodePtr action)");
	
	m_requires_session = true;

}

GetProfile::GetProfile(const GetProfile& c)
{
	EnEx ee(FL, "GetProfile::GetProfile(const GetProfile& c)");

	m_requires_session = c.m_requires_session;
}

GetProfile& GetProfile::operator=(const GetProfile& c)
{
	EnEx ee(FL, "GetProfile::operator=(const GetProfile& c)");

	m_requires_session = c.m_requires_session;
	return *this;
}

GetProfile::~GetProfile()
{

}

void GetProfile::ExecuteRequest(IOConn& ioc)
{
	EnEx ee(FL, "GetProfile::ExecuteRequest(IOConn& ioc)", true);

	// Send our current profile information back to the client:
	ioc.initializeResponseDocument("GetProfile");
	ioc.addResponseMessage(TheMain::getInstance()->GetThreadList().DescribeThreads() );
	twine profile;
	EnEx::PrintGlobalHitMap(profile);
	ioc.addResponseMessage( profile );

	SessionList::getInstance().describeSessions( ioc.getResponseRoot() );

	ioc.SendReturn();
	ioc.Close();
}
