/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
#include "SessionList.h"
#include "SessionInfo.h"
using namespace Helix::Glob;

#include "ConnectToServer.h"
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

// This adds us to the global ActionClass Registry:
ActionClassRegister<ConnectToServer> ConnectToServer::reg("ConnectToServer", 1, "/logic/util/ConnectToServer");

// Used for auto generating the API on the javascript side:
// NOT USED HERE API=/logic/util/ConnectToServer Input=LogOn

ConnectToServer::ConnectToServer(xmlNodePtr action)
{
	EnEx ee(FL, "ConnectToServer::ConnectToServer(xmlNodePtr action)");
	
}

ConnectToServer::ConnectToServer(const ConnectToServer& c)
{
	EnEx ee(FL, "ConnectToServer::ConnectToServer(const ConnectToServer& c)");

}

ConnectToServer& ConnectToServer::operator=(const ConnectToServer& c)
{
	EnEx ee(FL, "ConnectToServer::operator=(const ConnectToServer& c)");

	return *this;
}

ConnectToServer::~ConnectToServer()
{

}

void ConnectToServer::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "ConnectToServer::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("ConnectToServer");

	// Pull up our input document and convert it into an object we can use:
	LogOn local( XmlHelpers::FindChild(ioc.GetRequestRoot(), LogOn::Name()()) );

	// Connect to the server
	INFO(FL, "Requested new logon with host(%s) port(%s) user(%s) pass(******)",
		local.Host(), local.Port(), local.User()  );

	// Find our session information so that we can store this new logon or
	// replace an existing logon record with the new password
	SessionInfo& si = ioc.getSessionInfo();
	
	// Lock the mutex because we're making changes to the DB connection:
	{ // mutex scope
		Lock theLock(si.dbConn_mutex);
		if(si.dbConn != NULL){
			// Remove the existing DB connection.
			si.setDBConn( NULL );
		}
	} // mutex is unlocked here

	// If that goes through just fine, then go ahead and record the
	// connection information in our current session.
	if(local.Alias.length() != 0){
		local.ConnName = local.Alias + " (" + local.User + "@" + local.Host + ":" + local.Port + ")";
	} else {
		local.ConnName = local.User + "@" + local.Host + ":" + local.Port;
	}

	si.userProperties[ local.ConnName ] = local.Pass;
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
