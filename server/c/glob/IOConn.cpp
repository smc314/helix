/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "IOConn.h"
#include "TheMain.h"
#include "SessionList.h"
#include "SessionInfo.h"
#include "LongRunningTask.h"
#include "Authenticate.h"
#include "SqlDB.h"
using namespace Helix::Glob;

#include "Action.h"
using namespace Helix::Logic::admin;

#include <EnEx.h>
#include <xmlinc.h>
#include <AutoXMLChar.h>
#include <XmlHelpers.h>
using namespace SLib;

#ifdef _WIN32
#include <rpc.h> // for UUID creation
#else
#include <uuid/uuid.h>
#endif

IOConn::IOConn()
{
	EnEx ee(FL, "IOConn::IOConn()");

	m_resp_doc = NULL;
	m_db = NULL;
	m_override_target = "";
	m_has_responded = false;
	m_lr_taskid = "";
}

IOConn::~IOConn()
{
	EnEx ee(FL, "IOConn::~IOConn()");

	if(m_resp_doc != NULL){
		xmlFreeDoc(m_resp_doc);
		m_resp_doc = NULL;
	}
	ReleaseDB();
}

void IOConn::overrideMsgTarget(const twine newTarget)
{
	EnEx ee(FL, "IOConn::overrideMsgTarget()");
	m_override_target = newTarget;
}

twine IOConn::getSessionID()
{
	EnEx ee(FL, "IOConn::getSessionID()");

	/* In a pure xml implementation of the connection, the session information
	 * is stored in a section of the XML message that looks like this:
	 * <RequestDoc...>
	 *   <Session id="EncryptedGUID">
	 *   </Session>
	 * </RequestDoc>
	 */
	twine ret;
	xmlDocPtr msg = GetMsg();
	if(msg == NULL) return "";
	xmlNodePtr root = xmlDocGetRootElement(msg);
	xmlNodePtr session = XmlHelpers::FindChild(root, "Session");
	if(session == NULL) return "";
	ret.getAttribute(session, "id");
	return ret;

}

void IOConn::setSessionID(const twine newSession)
{
	EnEx ee(FL, "IOConn::setSessionID(const twine newSession)");

	// Request:
	xmlNodePtr root = xmlDocGetRootElement( GetMsg() );
	xmlNodePtr session = xmlNewChild(root, NULL, (const xmlChar*)"Session", NULL);
	xmlSetProp(session, (const xmlChar*)"id", newSession);

	// Response:
	root = getResponseRoot();
	session = xmlNewChild(root, NULL, (const xmlChar*)"Session", NULL);
	xmlSetProp(session, (const xmlChar*)"id", newSession);

}

twine IOConn::genSessionID()
{
	EnEx ee(FL, "IOConn::genSessionID()");

#ifdef _WIN32
	// First generate the uuid
	UUID u;
	UuidCreate( &u );

	// Then convert it to a string that we can use:
	RPC_CSTR uStr;
	UuidToString( &u, &uStr );
	
	twine ret( (char*)uStr );
	RpcStringFree( &uStr );
#else
	uuid_t u;
	twine ret;
	ret.reserve(36);
	uuid_generate(u);
	uuid_unparse(u, ret.data());
	ret.check_size();
#endif

	return ret;
}

bool IOConn::allowedWOSession(void)
{
	EnEx ee(FL, "IOConn::allowedWOSession()");

	twine msgTarget = MsgTarget();
	xmlNodePtr root = xmlDocGetRootElement( TheMain::getInstance()->GetConfig() );
	xmlNodePtr security = XmlHelpers::FindChild( root, "Security");
	if(security == NULL){
		WARN(FL, "Missing Security node in config file.");
		return false; // nothing allowed when empty.
	}

	xmlNodePtr awol = XmlHelpers::FindChild( security, "AllowedWOLogin");
	if(awol == NULL){
		WARN(FL, "Missing AllowedWOLogin node uder Security node in config file.");
		return false; // nothing allowed when empty
	}

	vector<xmlNodePtr> paths = XmlHelpers::FindChildren( awol, "Path" );
	for(size_t i = 0; i < paths.size(); i++){
		twine startswith;
		startswith.getAttribute( paths[i], "startswith" );
		if(msgTarget.startsWith( startswith )){
			return true; // explictly allowed.
		}
	}

	// Also check the database setup for the given target
	twine storedin;
	storedin.getAttribute( security, "storedin" );
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( storedin );
	Action_svect actions = Action::selectByPath(sqldb, msgTarget );
	if(actions->size() != 0){
		if((*actions)[0]->OKWOSession == 1){
			return true; // allowed without a session by the database configuration
		}
	}

	// If we get to here - it didn't match anything that is allowed
	return false;
}

xmlDocPtr IOConn::initializeResponseDocument(const char* rootName)
{
	EnEx ee(FL, "IOConn::initializeResponseDocument(const char* rootName)");

	if(m_resp_doc == NULL){
		m_resp_doc = xmlNewDoc((const xmlChar*)"1.0");
		m_resp_doc->children = xmlNewDocNode(m_resp_doc, NULL, (const xmlChar*)rootName, NULL);
	} else {
		xmlNodePtr root = xmlDocGetRootElement(m_resp_doc);
		xmlNodeSetName(root, (const xmlChar*)rootName);
	}
	return m_resp_doc;
}

xmlDocPtr IOConn::initializeResponseDocument(xmlDocPtr resp)
{
	EnEx ee(FL, "IOConn::initializeResponseDocument(xmlDocPtr resp)");

	if(resp != NULL){
		if(m_resp_doc != NULL && m_resp_doc != resp){
			xmlFreeDoc(m_resp_doc);
		}
		m_resp_doc = resp;
	}
	return m_resp_doc;
}

xmlNodePtr IOConn::getResponseRoot(void)
{
	EnEx ee(FL, "IOConn::getResponseRoot()");

	if(m_resp_doc == NULL){
		initializeResponseDocument("Response");
	}
	return xmlDocGetRootElement(m_resp_doc);

}

void IOConn::setResponseFiltered(bool tf)
{
	EnEx ee(FL, "IOConn::setResponseFiltered(bool tf)");

	xmlNodePtr root = getResponseRoot();
	if(tf){
		xmlSetProp(root, (const xmlChar*)"filtered", (const xmlChar*)"true");
	} else {
		xmlSetProp(root, (const xmlChar*)"filtered", (const xmlChar*)"false");
	}

}

void IOConn::addResponseError(twine msg, AnException* e)
{
	EnEx ee(FL, "IOConn::addResponseError()");

	if(m_resp_doc == NULL){
		initializeResponseDocument("Response");
	}

	xmlNodePtr root = xmlDocGetRootElement(m_resp_doc);
	xmlSetProp(root, (const xmlChar*)"haserror", (const xmlChar*)"true");
	
	xmlNodePtr errors = XmlHelpers::FindChild(root, "Errors");
	if(errors == NULL){
		errors = xmlNewChild(root, NULL, (const xmlChar*)"Errors", NULL);
	}
	xmlNodePtr error = xmlNewChild(errors, NULL, (const xmlChar*)"Error", NULL);
	if(e != NULL){
		xmlSetProp(error, (const xmlChar*)"msg", (const xmlChar*)e->Msg());
	} else {
		xmlSetProp(error, (const xmlChar*)"msg", msg);
	}

}

void IOConn::addResponseMessage(twine msg)
{
	EnEx ee(FL, "IOConn::addResponseMessage()");

	if(m_resp_doc == NULL){
		initializeResponseDocument("Response");
	}

	xmlNodePtr root = xmlDocGetRootElement(m_resp_doc);
	xmlNodePtr messages = XmlHelpers::FindChild(root, "Messages");
	if(messages == NULL){
		messages = xmlNewChild(root, NULL, (const xmlChar*)"Messages", NULL);
	}
	xmlNodePtr message = xmlNewChild(messages, NULL, (const xmlChar*)"Message", NULL);
	XmlHelpers::setCDATASection(message, msg);

}

void IOConn::parseConnName(twine& connName, twine& Host, twine& Port, twine& User)
{
	EnEx ee(FL, "IOConn::parseConnName()");

	// the connection name can have the format of either:
	// user@host:port
	//  - or -
	// alias (user@host:port)
	
	if(connName.find( "(" ) != TWINE_NOT_FOUND ) {
		// we have an alias format
		size_t idx1 = connName.find("(");
		size_t idx2 = connName.find(")");
		if(idx2 == TWINE_NOT_FOUND){
			throw AnException(0, FL, "Invalid connection name format (%s)", connName() );
		}
		idx1++;
		twine tmpConn = connName.substr( idx1, idx2-idx1 );

		// Now do it the old way:
		vector<twine> splits1 = tmpConn.split("@");
		vector<twine> splits2 = splits1[1].split(":");
		Host = splits2[0];
		Port = splits2[1];
		User = splits1[0];

	} else {
		vector<twine> splits1 = connName.split("@");
		vector<twine> splits2 = splits1[1].split(":");
		Host = splits2[0];
		Port = splits2[1];
		User = splits1[0];
	}
}

bool IOConn::verifyUserAction()
{
	EnEx ee(FL, "IOConn::verifyUserAction()");

	xmlNodePtr root = xmlDocGetRootElement( TheMain::getInstance()->GetConfig() );
	xmlNodePtr security = XmlHelpers::FindChild( root, "Security");
	if(security == NULL){
		WARN(FL, "Missing Security node in config file.");
		return false; // nothing allowed when empty.
	}

	if(XmlHelpers::getBoolAttr(security, "enabled") == false){
		DEBUG(FL, "Security has been disabled.  Everything allowed.");
		return true;
	}

	// First check if this can be used directly without verification
	if(allowedWOSession()){
		// It's a start-session Authenticate request.  We don't need to check anything for this.
		return true;
	}

	xmlNodePtr authentication = XmlHelpers::FindChild( security, "Authentication");
	if(authentication== NULL){
		WARN(FL, "Missing Authentication node uder Security node in config file.");
		return false; // nothing allowed when empty
	}

	if(XmlHelpers::getBoolAttr(authentication, "enabled")) {

		// Now ensure that the user has been authenticated and has a valid session
		if(!checkSessionID()){
			// Session is bad
			INFO(FL, "IOConn session is not valid or does not exist.");

			// Check to see if there is authentication information in the document
			try {
				SessionInfo& si = Authenticate::authenticateUser( this );
				setSessionID( si.sessionGUID );
			} catch (AnException& e){
				INFO(FL, "Missing or invalid authentication information.");
				twine redirectLocation;
				redirectLocation.getAttribute( authentication, "loginapp" );
				SendRedirect( redirectLocation );
				Close();
				return false;
			}
		}
	}

	xmlNodePtr authorization = XmlHelpers::FindChild( security, "Authorization");
	if(authorization== NULL){
		WARN(FL, "Missing Authorization node uder Security node in config file.");
		return false; // nothing allowed when empty
	}

	// Finally check to see if the user is authorized to perform this function
	if(XmlHelpers::getBoolAttr(authorization, "enabled")){
		if(!verifyUser()){
			// User is not allowed to perform this action
			SessionInfo& si = getSessionInfo();
			WARN(FL, "User (%s) (%s) is not allowed to invoke (%s)", si.username(), si.fullname(),
				MsgTarget()() );
			SendForbidden();
			Close();
			return false;
		}
	}

	// If everything goes well - signal the a-ok.
	return true;
}

OdbcObj* IOConn::getDBConnection()
{
	EnEx ee(FL, "IOConn::getDBConnection()");

	// If we don't already have one - get a connection from our pool
	if(m_db == NULL){
		m_db = &TheMain::getInstance()->GetOdbcConnection( "writing" ); // FIXME: shouldn't be hard-coded
	}

	//Make sure that auto commit is set to true
	m_db->odbc->SetAutoCommit(true);

	// Return the odbc connection:
	return m_db->odbc;
}

bool IOConn::checkSessionID()
{
	EnEx ee(FL, "IOConn::checkSessionID()");

	SessionList& sl = SessionList::getInstance();
	twine sID = getSessionID();
	if(sID.length() == 0 || sl.hasSession(sID) == false ){
		return false; // not a good session
	} else {
		return true; // Session is fine.
	}
}

bool IOConn::verifyUser()
{
	EnEx ee(FL, "IOConn::verifyUser()");

	return Authenticate::authorizeUserAction( this );
}

SessionInfo& IOConn::getSessionInfo()
{
	EnEx ee(FL, "IOConn::getSessionInfo()");

	SessionList& sl = SessionList::getInstance();
	twine sID = getSessionID();
	if(sID.length() == 0 || sl.hasSession(sID) == false ){
		// No Session ID, or session id does not exist.  Either way, add a new
		// one that will get sent back with the next response
		SessionInfo& newSI = sl.addSession(0, "user", "Full Name", "dbname");
		setSessionID( newSI.sessionGUID );
		sID = newSI.sessionGUID;
	}

	return sl.getSession( sID );
}

void IOConn::ReleaseDB(void)
{
	EnEx ee(FL, "IOConn::ReleaseDB()");

	if(m_db != NULL){
		// Ensure that every time we release a DB, we do a rollback to tell the
		// server we're not doing anything else with it.
		try {
			m_db->odbc->Rollback();
		} catch(AnException& e){
			// We don't care about exceptions here
		}

		// Release it back to the pool
		m_db->release();
		m_db = NULL;
	}
}

void IOConn::Close(void)
{
	EnEx ee(FL, "IOConn::Close()");

	finishResponse();
	ReleaseDB();
}

void IOConn::finishResponse(void)
{
	EnEx ee(FL, "IOConn::finishResponse()");

	m_has_responded = true;

}

void IOConn::lrTaskID( const twine& taskID )
{
	EnEx ee(FL, "IOConn::lrTaskID(const twine& taskID)");

	m_lr_taskid = taskID;
}

const twine& IOConn::lrTaskID()
{
	EnEx ee(FL, "IOConn::lrTaskID()");

	return m_lr_taskid;
}

void IOConn::updateLRTask(intptr_t start, intptr_t current, intptr_t finish, const twine& msg)
{
	EnEx ee(FL, "IOConn::updateLRTask()");

	if(m_lr_taskid.length() == 0){
		return; // nothing to do
	}
	if(LongRunningTask::getInstance().hasTask( m_lr_taskid ) ){
		try {
			LongRunningTask::getInstance().updateTask( m_lr_taskid, start, current, finish, msg );
		} catch (AnException& e){
			// ignore this.
		}
	}
}

