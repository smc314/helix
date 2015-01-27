/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "SessionSerializer.h"
#include "SessionList.h"
#include "TheMain.h"
using namespace Helix::Glob;

#include "Session.h"
using namespace Helix::Logic::admin;

#ifdef _WIN32
#include <direct.h>
#endif

#include <xmlinc.h>
#include <AnException.h>
#include <dptr.h>
#include <sptr.h>
#include <BlockingQueue.h>
#include <EnEx.h>
#include <Tools.h>
#include <File.h>
#include <MemBuf.h>
using namespace SLib;

SessionSerializer::SessionSerializer()
{
	EnEx ee(FL, "SessionSerializer::SessionSerializer()");

	m_descr.format( "SessionSerializer (idle) Thread");

}

SessionSerializer::SessionSerializer(const SessionSerializer& c) : Threadable(c)
{
	EnEx ee(FL, "SessionSerializer::SessionSerializer(const SessionSerializer& c)");
	m_descr = c.m_descr;

}

SessionSerializer& SessionSerializer::operator=(const SessionSerializer& c)
{
	EnEx ee(FL, "SessionSerializer::operator=(const SessionSerializer& c)");
	m_descr = c.m_descr;

	return *this;
}

SessionSerializer::~SessionSerializer()
{
	EnEx ee(FL, "SessionSerializer::~SessionSerializer()");

}

void SessionSerializer::Execute(void)
{
	EnEx ee(FL, "SessionSerializer::Execute()");
	
	INFO(FL, "Execute starting: %s", m_descr());

	m_state = Threadable::Startup;
	BlockingQueue<SessionInfo*>& si_queue = SessionList::getInstance().getSerializeQueue();
	TheMain* the_main = TheMain::getInstance();

	while(!m_shutdown && !the_main->isShutdown()){
		try {
			// set our state
			m_state = Threadable::Sleeping; // We usually go to sleep waiting on the queue
			m_descr = "SessionSerializer (idle) Thread";
			SessionInfo* si = si_queue.pop();
			m_state = Threadable::Running;
			if(si != NULL){
				// Process it.
				m_descr = "SessionSerializer (working) Thread";
				ProcessSessionInfo(si);
			}
		} catch (AnException e){
			ERRORL(FL, "Caught exception during SessionSerializer::Execute().\n%s", 
				e.Msg());
		} catch (...) {
			ERRORL(FL, "Caught unknown exception in SessionSerializer::Execute.");
		}
	}

	INFO(FL, "Execute finished");

}

void SessionSerializer::ProcessSessionInfo(SessionInfo* si)
{
	EnEx ee(FL, "SessionSerializer::ProcessSessionInfo(SessionInfo* si)", true);

	try {
		SqlDB& sqldb = TheMain::getInstance()->GetConfigDB( );

		Session_svect sessions = Session::selectByID( sqldb, si->sessionGUID);
		if(sessions->size() == 0){
			// Brand new session - do an insert:
			Session s;
			s.guid = si->sessionGUID;
			s.Userid = si->userid;
			s.Created = si->created;
			s.LastAccess = si->lastaccess;
			s.Active = 1;
			Session::insert( sqldb, s );
		} else {
			// Existing session - do an update:
			Session::update( sqldb, si->userid, si->created, si->lastaccess, 1, si->sessionGUID );
		}

		/*
		// Make sure our sessions directory exists:
		EnsureSessionDir();

		// Serialize the session info into an xml document:
		sptr<xmlDoc, xmlFreeDoc> doc = si->createXmlDoc();

		// Serialize the xml document into a memory buffer:
		MemBuf docContents = XmlHelpers::docToString( doc );

		// Encrypt that memory buffer out to an XML file that will be saved:
		sptr<xmlDoc, xmlFreeDoc> edoc = docContents.Encrypt( TheMain::getInstance()->GetKeypair() );
		
		// Save the encrypted file:
		twine fileName = "./sessions/" + si->sessionGUID;
		xmlSaveFile( fileName(), edoc );
		*/

	} catch (AnException& e){
		ERRORL(FL, "Caught exception during ProcessSessionInfo()\n%s", e.Msg());
	} catch (...) {
		ERRORL(FL, "Caught unknown exception in ProcessSessionInfo().");
	}

}

void SessionSerializer::EnsureSessionDir()
{
	EnEx ee(FL, "SessionSerializer::EnsureSessionDir()");

	try {
		vector<twine> folders = File::listFolders(".");
		bool foundDir = false;
		for(int i = 0; i < (int)folders.size(); i++){
			if(folders[i] == "sessions"){
				foundDir = true;
				break;
			}
		}
		if(!foundDir){
			// Create the sessions folder:
#ifdef _WIN32
			int ret = _mkdir("sessions");
#else
			int ret = mkdir("sessions", 0777);
#endif
			if(ret != 0){
				throw AnException(0, FL, "Error creating our sessions directory.");
			}
		}

	} catch (AnException& e){
		ERRORL(FL, "Caught exception during EnsureSessionDir()\n%s", e.Msg());
	}
}
