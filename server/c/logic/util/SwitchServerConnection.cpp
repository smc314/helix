/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SwitchServerConnection.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <Lock.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "LogOn.h"
#include "SessionList.h"
#include "SessionInfo.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<SwitchServerConnection> SwitchServerConnection::reg("SwitchServerConnection", 1, "/logic/util/SwitchServerConnection");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/SwitchServerConnection Input=LogOn

SwitchServerConnection::SwitchServerConnection(xmlNodePtr action)
{
	EnEx ee(FL, "SwitchServerConnection::SwitchServerConnection(xmlNodePtr action)");
	
}

SwitchServerConnection::SwitchServerConnection(const SwitchServerConnection& c)
{
	EnEx ee(FL, "SwitchServerConnection::SwitchServerConnection(const SwitchServerConnection& c)");

}

SwitchServerConnection& SwitchServerConnection::operator=(const SwitchServerConnection& c)
{
	EnEx ee(FL, "SwitchServerConnection::operator=(const SwitchServerConnection& c)");

	return *this;
}

SwitchServerConnection::~SwitchServerConnection()
{

}

void SwitchServerConnection::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SwitchServerConnection::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SwitchServerConnection");

	// Pull up our input document and convert it into an object we can use:
	LogOn local( XmlHelpers::FindChild(ioc.GetRequestRoot(), LogOn::Name()()) );

	// Connect to the server
	INFO(FL, "Requested switching logon to (%s)", local.ConnName());

	// Find our session information so that we can store this new logon or
	// replace an existing logon record with the new password
	SessionInfo& si = ioc.getSessionInfo();

	// Ensure that we have a password for this connection:
	if(si.userProperties.count(local.ConnName) == 0){
		throw AnException(0, FL, "We have no history of connecting to %s", local.ConnName() );
	}

	// Lock the mutex because we're making changes to the DB connection:
	{ // mutex scope
		Lock theLock(si.dbConn_mutex);
		if(si.dbConn != NULL){
			// Remove the existing DB connection.
			si.setDBConn( NULL );
		}
	} // mutex is unlocked here

	// Record the change to our user properties
	si.userProperties[ "CurrentConnection" ] = local.ConnName;
	si.Save();

	// Now ask the IOConn to acquire the DB connection for us:
	OdbcObj* odbc = ioc.getDBConnection();

	// Convert the whole response back to XML
	xmlNodePtr root = ioc.getResponseRoot();
	local.createXmlNode( root );

	// Add a message about how many rows we found
	twine tmp;
	tmp.format("Connection Successful.");
	ioc.addResponseMessage(tmp);


	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
