/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "UserProperties.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "SessionList.h"
#include "SessionInfo.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<UserProperties> UserProperties::reg("UserProperties", 1, "/UserProperties");

// Used for auto generating the API on the javascript side:
// NOT USED HERE API=/UserProperties Input=NULL

UserProperties::UserProperties(xmlNodePtr action)
{
	EnEx ee(FL, "UserProperties::UserProperties(xmlNodePtr action)");
	
}

UserProperties::UserProperties(const UserProperties& c)
{
	EnEx ee(FL, "UserProperties::UserProperties(const UserProperties& c)");

}

UserProperties& UserProperties::operator=(const UserProperties& c)
{
	EnEx ee(FL, "UserProperties::operator=(const UserProperties& c)");

	return *this;
}

UserProperties::~UserProperties()
{

}

void UserProperties::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "UserProperties::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("UserProperties");

	// Pull out the normal user-properties from the session.
	SessionInfo& si = ioc.getSessionInfo();

	// Walk the properties to be deleted:
	vector<xmlNodePtr> dels = XmlHelpers::FindChildren( ioc.GetRequestRoot(), "DelProperty");
	for(int i = 0; i < (int)dels.size(); i++){
		twine name; name.getAttribute(dels[i], "name");
		if(si.userProperties.count(name) > 0){
			si.userProperties.erase(name);
		}
	}

	// Walk the properties to be added:
	vector<xmlNodePtr> adds = XmlHelpers::FindChildren( ioc.GetRequestRoot(), "SetProperty");
	for(int i = 0; i < (int)adds.size(); i++){
		twine name; name.getAttribute(adds[i], "name");
		twine value; value.getAttribute(adds[i], "value");
		si.userProperties[name] = value;
	}

	// Walk all of the user properties and send them back:
	xmlNodePtr root = ioc.getResponseRoot();
	map<twine, twine>::iterator it;
	for(it = si.userProperties.begin(); it != si.userProperties.end(); it++){
		xmlNodePtr elem = xmlNewChild(root, NULL, (const xmlChar*)"Property", NULL);
		xmlSetProp(elem, (const xmlChar*)"name", it->first);
		xmlSetProp(elem, (const xmlChar*)"value", it->second);
	}

	// Save all of the changes to the session.
	si.Save();

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
