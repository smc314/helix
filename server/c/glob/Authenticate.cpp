/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
#include "Authenticate.h"
using namespace Helix::Glob;

#include "Statics.h"
using namespace Helix::Logic::util;

#include "HelixUser.h"
#include "Action.h"
using namespace Helix::Logic::admin;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here

// This adds us to the global ActionClass Registry:
ActionClassRegister<Authenticate> Authenticate::reg("Authenticate", 1, "/Authenticate");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/Authenticate Input=NULL

Authenticate::Authenticate(xmlNodePtr action)
{
	EnEx ee(FL, "Authenticate::Authenticate(xmlNodePtr action)");
	
}

Authenticate::Authenticate(const Authenticate& c)
{
	EnEx ee(FL, "Authenticate::Authenticate(const Authenticate& c)");

}

Authenticate& Authenticate::operator=(const Authenticate& c)
{
	EnEx ee(FL, "Authenticate::operator=(const Authenticate& c)");

	return *this;
}

Authenticate::~Authenticate()
{
	EnEx ee(FL, "Authenticate::~Authenticate()");

}

bool Authenticate::isLongRunning()
{
	EnEx ee(FL, "Authenticate::isLongRunning()");

	// If we are a long running transaction, we need to return true here.  This will trigger
	// special logic that causes an immediate return to the caller, and for us to be executed
	// via the internal server queue - rather than executed in-line on the http thread.

	// Most of the time our server logic classes are _NOT_ long running.  But in the rare
	// case when they are, simply return true here.
	// return true;

	// This is the default.  And in fact, if this method returns false, it's better to just
	// delete this whole method to save confusion.  Our super-class already returns false for us.
	return false;
}

twine Authenticate::lrTaskName()
{
	EnEx ee(FL, "Authenticate::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "Authenticate Request";
}


void Authenticate::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "Authenticate::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("Authenticate");

	// Example of reading input and using it to select from the odbc driver:
	// OdbcTable local( XmlHelpers::FindChild( ioc.GetRequestRoot(), OdbcTable::Name()() ) );
	//
	// OdbcObj& odbc = *ioc.getDBConnection();
	//
	// twine stmt = OdbcTable::selectConfig_prepSQL(ioc, local.Name1);
	// OdbcTable_svect vect = OdbcTable::selectConfig(odbc, stmt, false, local.Name1);

	// Example of a simple select to return an unfiltered list of data:
	// OdbcObj& odbc = *ioc.getDBConnection();
	// 
	// OdbcTable_svect vect = OdbcTable::selectMdiCfgLst(odbc);

	// Example of accessing a local configuration database
	// SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixdev" );
	//
	// LocalProject_svect vect = LocalProject::selectAll( sqldb );

	// Returning data in one of the above vectors back to the client is as
	// easy as doing this:
	// 
	// OdbcObj::createXmlChildren( ioc.getResponseRoot(), vect );
	// or
	// LocalProject::createXmlChildren( ioc.getResponseRoot(), vect );

	///////////////////////////////////////////////////////////////////
	// LONG RUNNING TASK Notes
	///////////////////////////////////////////////////////////////////
	// If we are a long running transaction, our execution looks very similar to the above.
	// With a few exceptions.  Once you figure out what the start and finish markers look like,
	// then make this call:
	// ioc.updateLRTask( start, start, finish, "Starting Authenticate Process" );
	//
	// As you progress through this long task, keep making calls like this:
	// ioc.updateLRTask( start, current, finish, "Doing something interesting" );
	//
	// When you are done, don't do anything special.  Just make the ioc.SendReturn(); call
	// as below.  Note, you'll still send return data using the ioc.getResponseRoot() as above.
	///////////////////////////////////////////////////////////////////


	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}

SessionInfo& Authenticate::authenticateUser( IOConn* ioc )
{
	EnEx ee(FL, "Authenticate::authenticateUser(IOConn* ioc)");

	xmlNodePtr root = ioc->GetRequestRoot();
	twine UserName;
	twine Password;
	UserName.getAttribute( root, "user" );
	Password.getAttribute( root, "pass" );

	if(UserName.empty()){
		throw AnException(0, FL, "Authentication missing or empty user name.");
	}
	if(Password.empty()){
		throw AnException(0, FL, "Authentication missing or empty password.");
	}

	if(verifyUserNameAndPassword( ioc, UserName, Password ) == true ){
		return ioc->getSessionInfo();
	} else {
		throw AnException(0, FL, "Authentication failed.");
	}
}

bool Authenticate::authorizeUserAction( IOConn* ioc )
{
	EnEx ee(FL, "Authenticate::authorizeUserAction(IOConn* ioc)");

	xmlNodePtr root = xmlDocGetRootElement( TheMain::getInstance()->GetConfig() );
	xmlNodePtr security = XmlHelpers::FindChild( root, "Security");
	if(security == NULL){
		WARN(FL, "Missing Security node in config file.");
		return false; // Nothing allowed when empty
	}

	if(XmlHelpers::getBoolAttr(security, "enabled") == false){
		DEBUG(FL, "Authenticate::authorizeUserAction - All Security has been disabled.  Everything allowed.");
		return true;
	}

	xmlNodePtr authorization = XmlHelpers::FindChild( security, "Authorization");
	if(authorization == NULL){
		WARN(FL, "Missing Authorization node under Security node in config file.");
		return false; // nothing allowed when empty
	}

	if(XmlHelpers::getBoolAttr(authorization, "enabled") == false){
		DEBUG(FL, "Authenticate::authorizeUserAction - Authorization has been disabled. Returning true.");
		return true;
	}

	twine storedin;
	storedin.getAttribute( security, "storedin" );
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( storedin );
	SessionInfo& si = ioc->getSessionInfo();
	intptr_t userid = si.userid;
	twine msgTarget = ioc->MsgTarget();
	Action_svect actionuser = Action::checkActionForUser(sqldb, userid, msgTarget );
	if(actionuser->size() > 0){
		// User is authorized directly to perform this action.
		return true;
	}

	Action_svect actiongroup = Action::checkActionForUserByGroup(sqldb, userid, msgTarget );
	if(actiongroup->size() > 0){
		// User is authorized via group membership to perform this action.
		return true;
	}

	// If the user is not directly or through group membership authorized, then return false
	return false;
}

bool Authenticate::verifyUserNameAndPassword(IOConn* ioc, const twine& UserName, const twine& Password)
{
	EnEx ee(FL, "Authenticate::verifyUserNameAndPassword(const twine& UserName const twine& Password)");

	xmlNodePtr root = xmlDocGetRootElement( TheMain::getInstance()->GetConfig() );
	xmlNodePtr security = XmlHelpers::FindChild( root, "Security");
	if(security == NULL){
		WARN(FL, "Missing Security node in config file.");
		return false; // Nothing allowed when empty
	}

	if(XmlHelpers::getBoolAttr(security, "enabled") == false){
		DEBUG(FL, "Authenticate::verifyUserNameAndPassword - All Security has been disabled.  Everything allowed.");
		return true;
	}

	xmlNodePtr authentication = XmlHelpers::FindChild( security, "Authentication");
	if(authentication == NULL){
		WARN(FL, "Missing Authentication node under Security node in config file.");
		return false; // nothing allowed when empty
	}

	if(XmlHelpers::getBoolAttr(authentication, "enabled") == false){
		DEBUG(FL, "Authenticate::verifyUserNameAndPassword - Authentication has been disabled. Returning true.");
		return true;
	}

	twine storedin;
	storedin.getAttribute( security, "storedin" );

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( storedin );
	HelixUser_svect users = HelixUser::selectByUsername( sqldb, (twine&)UserName );

	// Now verify the user we found against the requested password
	if(users->size() == 0){
		// User was not found in the database
		DEBUG(FL, "User (%s) was not found in our database.", UserName() );
		return false;
	}

	if((*users)[0]->Active != 1){
		DEBUG(FL, "User (%s) exists, but is marked as in-active.", UserName() );
		return false;
	}

	if((*users)[0]->AuthMechanism == 0){ // Plain text password compare
		if((*users)[0]->Password == Password){
			// User was found and passwords match - update session info if found
			DEBUG(FL, "User (%s) exists, and passwords match.  Granting Authentication Successful.", UserName());
			if(ioc != NULL){
				SessionInfo& si = ioc->getSessionInfo();
				si.userid = (*users)[0]->id;
				si.username = (*users)[0]->Username;
				si.fullname = (*users)[0]->FullName;
			}
			return true;
		} else {
			// User passwords don't match
			DEBUG(FL, "User (%s) exists, but passwords don't match.", UserName() );
			return false;
		}
	} else if((*users)[0]->AuthMechanism == 1){ // Encrypted password compare
		// Encrypt the password provided so we can compare it:
		MemBuf passmem = Password;
		sptr<xmlDoc, xmlFreeDoc> passdoc = passmem.Encrypt( TheMain::getInstance()->GetKeypair() );
		twine passenc = XmlHelpers::docToString( passdoc );

		if((*users)[0]->Password == passenc){
			// User was found and passwords match - update session info if found
			DEBUG(FL, "User (%s) exists, and encrypted passwords match.  Granting Authentication Successful.", UserName());
			if(ioc != NULL){
				SessionInfo& si = ioc->getSessionInfo();
				si.userid = (*users)[0]->id;
				si.username = (*users)[0]->Username;
				si.fullname = (*users)[0]->FullName;
			}
			return true;
		} else {
			// User passwords don't match
			DEBUG(FL, "User (%s) exists, but encrypted passwords don't match.", UserName() );
			return false;
		}
	} else {
		DEBUG(FL, "User (%s) exists, but authmechanism (%d) is invalid.", UserName(), (*users)[0]->AuthMechanism );
		return false;
	}

}




