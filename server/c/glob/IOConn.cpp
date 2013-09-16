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
using namespace Helix::Glob;

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
	m_db_mutex = NULL;
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
	if(msgTarget.startsWith("/helixLogin/") ||
		msgTarget == "/js/helix.js" ||
		msgTarget == "helix.png" ||
		msgTarget == "/favicon.ico"
	){
		return true;
	} else {
		return false;
	}
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

OdbcObj* IOConn::getDBConnection()
{
	EnEx ee(FL, "IOConn::getDBConnection()");

	// Do we already have it?
	if(m_db != NULL){
		return m_db;
	}

	// Otherwise, get it from the session.
	SessionInfo& si = getSessionInfo();

	if(si.userProperties.count("CurrentConnection") == 0){
		throw AnException(0, FL, "Current session has not chosen a DB Connection yet.");
	}

	// Lock the dbConn mutex before doing anything with the dbConn:
	m_db_mutex = si.dbConn_mutex;
	m_db_mutex->lock();

	if(si.dbConn == NULL){
		// They've set the details, but we haven't connected successfully yet.
		twine connName = si.userProperties[ "CurrentConnection" ];
		twine Pass = si.userProperties[ connName ];

		// the connection name can have the format of either:
		// user@host:port
		//  - or -
		// alias (user@host:port)
		
		twine Host;
		twine Port;
		twine User;
		IOConn::parseConnName(connName, Host, Port, User);

		twine connStr = "DRIVER={Odbc Driver Name};"
			"SRV=" + Host + "/" + Port + "/lds;"
			"UID=" + User + ";PWD=" + Pass + ";";
		try {
			si.setDBConn( new OdbcObj( User, Pass, connStr ) );
		} catch (AnException& e){
			// Unlock the mutex because we were not successful in connecting
			// to the requested server.
			m_db_mutex->unlock();
			m_db_mutex = NULL;
			throw; // re-throw the exception to allow it to bubble up.
		}
	}

	// We now have the database connection, and the mutex to lock
	// it for only our use.
	m_db = si.dbConn;
	
	//Make sure that auto commit is set to true
	si.dbConn->SetAutoCommit(true);

	return m_db;

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
		m_db->Rollback();

		// UnLock the db mutex so that others can use it.
		m_db_mutex->unlock();
		m_db_mutex = NULL;
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

