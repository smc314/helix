/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SystemProperties.h"
#include "Statics.h"
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
ActionClassRegister<SystemProperties> SystemProperties::reg("SystemProperties", 1, "/SystemProperties");

// Used for auto generating the API on the javascript side:
// NOT USED HERE API=/SystemProperties Input=NULL

SystemProperties::SystemProperties(xmlNodePtr action)
{
	EnEx ee(FL, "SystemProperties::SystemProperties(xmlNodePtr action)");
	
}

SystemProperties::SystemProperties(const SystemProperties& c)
{
	EnEx ee(FL, "SystemProperties::SystemProperties(const SystemProperties& c)");

}

SystemProperties& SystemProperties::operator=(const SystemProperties& c)
{
	EnEx ee(FL, "SystemProperties::operator=(const SystemProperties& c)");

	return *this;
}

SystemProperties::~SystemProperties()
{

}

void SystemProperties::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SystemProperties::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SystemProperties");

	SessionInfo& si = ioc.getSessionInfo();

	xmlNodePtr root = ioc.getResponseRoot();

	// Add a series of properties from a couple of calls to the server and the driver
	// that are useful on the client to display various information.
	xmlNodePtr elem = xmlNewChild(root, NULL, (const xmlChar*)"SystemProperty", NULL);
	xmlSetProp(elem, (const xmlChar*)"name", (const xmlChar*)"HelixVersion");
	xmlSetProp(elem, (const xmlChar*)"value", (const xmlChar*)TheMain::getInstance()->ServerVersion());

	elem = xmlNewChild(root, NULL, (const xmlChar*)"SystemProperty", NULL);
	xmlSetProp(elem, (const xmlChar*)"name", (const xmlChar*)"HelixBuiltOn");
	xmlSetProp(elem, (const xmlChar*)"value", (const xmlChar*)TheMain::getInstance()->ServerBuiltOn());

	elem = xmlNewChild(root, NULL, (const xmlChar*)"SystemProperty", NULL);
	xmlSetProp(elem, (const xmlChar*)"name", (const xmlChar*)"AreWeHomeBase");
	XmlHelpers::setBoolAttr(elem, "value", Statics::areWeHomeBase() );

	elem = xmlNewChild(root, NULL, (const xmlChar*)"SystemProperty", NULL);
	xmlSetProp(elem, (const xmlChar*)"name", (const xmlChar*)"Username");
	xmlSetProp(elem, (const xmlChar*)"value", (const xmlChar*)si.username());

	elem = xmlNewChild(root, NULL, (const xmlChar*)"SystemProperty", NULL);
	xmlSetProp(elem, (const xmlChar*)"name", (const xmlChar*)"Fullname");
	xmlSetProp(elem, (const xmlChar*)"value", (const xmlChar*)si.fullname());

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
