/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "SessionList.h"
#include "SessionSerializer.h"
using namespace Helix::Glob;

#include "Session.h"
using namespace Helix::Logic::admin;

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
#include <Lock.h>
#include <File.h>
#include <XmlHelpers.h>
using namespace SLib;


static SessionList* m_sessionlist = NULL;

SessionList& SessionList::getInstance()
{
	EnEx ee(FL, "SessionList::getInstance()");

	if(m_sessionlist == NULL){
		m_sessionlist = new SessionList();
	}
	return *m_sessionlist;
}


SessionList::SessionList()
{
	EnEx ee(FL, "SessionList::SessionList()");

	m_sessions_mutex = new Mutex();
	initFromDB();
}

SessionList::~SessionList()
{
	EnEx ee(FL, "SessionList::~SessionList()");

	delete m_sessions_mutex;
}

SessionInfo& SessionList::getSession(twine& sessionGUID)
{
	EnEx ee(FL, "SessionList::getSession()");
	if(sessionGUID.length() == 0){
		throw AnException(0, FL, "Invalid sessionGUID");
	}
	Lock theLock(m_sessions_mutex);
	if(m_sessions.count(sessionGUID) > 0 ){
		SessionInfo *si = m_sessions[sessionGUID];

		// Update the fact that the session has been accessed
		// and serialize the update.
		si->lastaccess.SetCurrent();
		m_serialize_queue.push( si );

		// Then return the session
		return *si;
	} else {
		throw AnException(0, FL, "sessionGUID not found");
	}
}

bool SessionList::hasSession(twine& sessionGUID)
{
	EnEx ee(FL, "SessionList::hasSession()");
	if(sessionGUID.length() == 0){
		throw AnException(0, FL, "Invalid sessionGUID");
	}
	Lock theLock(m_sessions_mutex);
	if(m_sessions.count(sessionGUID) > 0 ){
		return true;
	} else {
		return false;
	}
}

void SessionList::Save(SessionInfo& si)
{
	EnEx ee(FL, "SessionList::Save(SessionInfo& si)");

	// Drop it onto the serialization queue to get the changes written
	// to the disk.
	m_serialize_queue.push( &si );

}

SessionInfo& SessionList::addSession(int user, twine username, twine fullname, twine dbname)
{
	EnEx ee(FL, "SessionList::addSession()");
	Lock theLock(m_sessions_mutex);

	// Only allow a max of 4000 sessions.
	if(m_sessions.size() >= 4000 ){
		// Find the oldest session and delete it:
		SessionInfo* oldest = NULL;
		map<twine, SessionInfo*>::iterator it;
		for(it = m_sessions.begin(); it != m_sessions.end(); it++){
			if(oldest == NULL){
				oldest = it->second;
			} else {
				if(it->second->created < oldest->created){
					oldest = it->second;
				}
			}
		}
		if(oldest != NULL){
			/*
			SessionSerializer::EnsureSessionDir();
			twine fileName = "./sessions/" + oldest->sessionGUID;
			File::Delete( fileName );
			*/
			SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
			Session::deleteByID(sqldb, oldest->sessionGUID);

			m_sessions.erase(oldest->sessionGUID);
			delete oldest;
		}
	}

	
	SessionInfo* si = new SessionInfo();
	si->userid = user;
	si->username = username;
	si->fullname = fullname;
	si->dbname = dbname;
	si->sessionGUID = generateUniqueId();
	
	// Always add the current user id as a userProperty that can be referenced by SQL
	twine userID;
	userID = (size_t)user;
	si->userProperties["CurrentUserID"] = userID;
	si->userProperties["CurrentUserName"] = username;
	si->userProperties["CurrentUserFullName"] = fullname;
	si->userProperties["CurrentUserDB"] = dbname;
	
	m_sessions[si->sessionGUID] = si;

	// Drop it on the queue to be serialized.
	m_serialize_queue.push( si );
	
	return *si;
}

void SessionList::initFromDB( )
{
	EnEx ee(FL, "SessionList::initFromDB()");
	Lock theLock(m_sessions_mutex);

	WARN(FL, "Initializing SessionList from our stored sessions.");

	// Ensure that our directory exists
	//SessionSerializer::EnsureSessionDir();
	
	SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
	Session_svect sessions = Session::selectAll(sqldb);
	for(size_t i = 0; i < sessions->size(); i++){
		SessionInfo* si = new SessionInfo( ) ;
		si->userid = (*sessions)[i]->Userid;
		si->created = (*sessions)[i]->Created;
		si->lastaccess = (*sessions)[i]->LastAccess;
		si->sessionGUID= (*sessions)[i]->guid;

		m_sessions[ si->sessionGUID ] = si;
	}

	/*
	vector<twine> files = File::listFiles("./sessions");	
	for(int i = 0; i < (int)files.size(); i++){
		twine fileName = "./sessions/" + files[i];
		sptr<xmlDoc, xmlFreeDoc> doc; doc = xmlParseFile( fileName() );
		if(doc == (xmlDocPtr)NULL){
			// Wasn't a valid xml file.  Log a warning about it and delete the file:
			WARN(FL, "File %s is invalid while loading sessions.  Deleting file.", fileName());
			File::Delete( fileName );
			continue;
		}

		// We have a valid document, decrypt it, re-animate it and add it to our sessions list.
		xmlNodePtr root = xmlDocGetRootElement(doc);
		if(strcmp( (const char*)(root->name), "Encrypted") == 0){
			// This is an encrypted session doc, decrypt it before reading it:
			MemBuf decryptedContents; decryptedContents.Decrypt( doc, TheMain::getInstance()->GetKeypair() );
			twine decString; decString.set( decryptedContents(), decryptedContents.length() );
			//INFO(FL, "Decrypted Session:\n%s", decString() );
			xmlDocPtr decdoc = xmlParseDoc((xmlChar*) decString() );
			if(decdoc == NULL){
				WARN(FL, "Error reading decrypted xml document from original (%s)", fileName() );
				continue;
			}
			doc = decdoc;
		}

		SessionInfo* si = new SessionInfo( doc );
		m_sessions[si->sessionGUID] = si;

	}
	*/

}

void SessionList::removeSession(IOConn& ioc, twine& sessionGUID)
{
	EnEx ee(FL, "SessionList::removeSession()");
	Lock theLock(m_sessions_mutex);

	DEBUG(FL, "Attempting to remove session (%s)", sessionGUID() );
	
	if(m_sessions.count(sessionGUID) > 0){
		try {
			SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );
			Session::deleteByID(sqldb, sessionGUID);

			/*
			SessionSerializer::EnsureSessionDir();
			twine fileName = "./sessions/" + sessionGUID;
			DEBUG(FL, "Removing session file (%s)", fileName() );
			File::Delete( fileName );
			*/

			delete m_sessions[sessionGUID];
			DEBUG(FL, "Removing session (%s) from session list", sessionGUID() );
			m_sessions.erase(sessionGUID);
		} catch (AnException& e){
			ERRORL(FL, "Error deactivating session: %s", e.Msg());
		}
	}
}

void SessionList::expireSessions( Date& oldest, IOConn& ioc, twine& dbname)
{
	EnEx ee(FL, "SessionList::expireSessions()");

	vector<SessionInfo*> sessions = getSessions();

	for(int i = 0; i < (int)sessions.size(); i++){
		SessionInfo* si = sessions[i];
		if(si->dbname == dbname && si->created < oldest ) {
			removeSession( ioc, si->sessionGUID );
		}
	}
}

void SessionList::loadUserProperties( SessionInfo& si, IOConn& ioc)
{
	EnEx ee(FL, "SessionList::loadUserProperties()");

	// Load the rest of the user properties from the database:
	try {
		//FIXME: decide on where these are stored/retrieved
		/*
		Document doc = Xml.newDocument("tmp");
		Element root = doc.getDocumentElement();
		User.selectPropertiesForUser(ioc, root, si.userid);

		ArrayList<Node> props = Xml.findChildren(root, "Property");
		for(int i = 0; i < props.size(); i++){
			Element s = (Element)props.get(i);
			twine name = s.getAttribute("name");
			twine value = s.getAttribute("value");
			if(name != null && value != null){
				si.userProperties.put(name, value);
			}
		}
		*/
		
	} catch (...){
		// skip the loading of user properties.
	}

}

void SessionList::describeSessions(xmlNodePtr node)
{
	EnEx ee(FL, "SessionList::describeSessions()");
	
	xmlNodePtr our_sessions = xmlNewChild(node, NULL, (const xmlChar*)"SessionList", NULL);

	vector<SessionInfo*> sessions = getSessions();
	
	for(int i = 0; i < (int)sessions.size(); i++){
		SessionInfo* si = sessions[i];
		xmlNodePtr session = xmlNewChild(our_sessions, NULL, (const xmlChar*)"SessionInfo", NULL);
		XmlHelpers::setIntAttr(session, "userid", si->userid );
		xmlSetProp(session, (const xmlChar*)"dbname", si->dbname );
		xmlSetProp(session, (const xmlChar*)"sessionGUID", si->sessionGUID );
		xmlSetProp(session, (const xmlChar*)"created", si->created );
		xmlSetProp(session, (const xmlChar*)"lastaccess", si->lastaccess );
	}

}

vector<SessionInfo*> SessionList::getSessions()
{
	EnEx ee(FL, "SessionList::loadUserProperties()");
	Lock theLock(m_sessions_mutex);

	vector<SessionInfo*> ret;
	
	if(m_sessions.size() != 0){
		map<twine, SessionInfo*>::iterator it;
		for(it = m_sessions.begin(); it != m_sessions.end(); it++){
			ret.push_back(it->second);
		}
	}

	return ret;
}

twine SessionList::generateUniqueId()
{
	return IOConn::genSessionID();
}

twine SessionList::bytesToHexString(char* bb)
{
	/* FIXME: rework this method
	twineBuffer buffer = new twineBuffer();
	int len = bb.length;
	for (int ii=0; ii < len; ii++) 
	{
		// convert a byte b to 2-char hex string with possible leading zero. 
		twine s2 = Integer.totwine( ( bb[ii] & 0xff ) + 0x100, 16 // radix 
			).substring( 1 );
		buffer.append(s2);
	}
	return buffer.totwine().toUpperCase();
	*/
	return twine(""); 
}

