/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "CloseConnection.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here


// This adds us to the global ActionClass Registry:
ActionClassRegister<CloseConnection> CloseConnection::reg("CloseConnection", 1, "/logic/util/CloseConnection");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/CloseConnection Input=NULL

CloseConnection::CloseConnection(xmlNodePtr action)
{
	EnEx ee(FL, "CloseConnection::CloseConnection(xmlNodePtr action)");
	
}

CloseConnection::CloseConnection(const CloseConnection& c)
{
	EnEx ee(FL, "CloseConnection::CloseConnection(const CloseConnection& c)");

}

CloseConnection& CloseConnection::operator=(const CloseConnection& c)
{
	EnEx ee(FL, "CloseConnection::operator=(const CloseConnection& c)");

	return *this;
}

CloseConnection::~CloseConnection()
{

}

void CloseConnection::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "CloseConnection::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("CloseConnection");

	// Find our session information so that we can close the DB connection.
	SessionInfo& si = ioc.getSessionInfo();

	// Set the connection to NULL, this will delete the OdbcObj itself
	si.setDBConn( NULL );

	// Delete the "CurrentConnection" key, because there is none.
	si.userProperties.erase( "CurrentConnection" );

	// Save the changes
	si.Save();

	// Add a message about closing the connection
	twine tmp;
	tmp.format("Connection successfully closed.");
	ioc.addResponseMessage(tmp);

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
