/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SESSIONLIST_H
#define SESSIONLIST_H

#include "SessionInfo.h"
#include "IOConn.h"

#include <Mutex.h>
#include <BlockingQueue.h>
using namespace SLib;

namespace Helix {
namespace Glob {


class SessionList {

	protected:
		map<twine, SessionInfo*> m_sessions; 
		Mutex* m_sessions_mutex;
		BlockingQueue<SessionInfo*> m_serialize_queue;
	
	private:
		/** Keep the constructor private so that there's only one instance of
		 * this object in memory during a run of the server.
		 */
		SessionList();

	public:

		static SessionList& getInstance();

		// Standard Destructor.
		~SessionList();
	
		BlockingQueue<SessionInfo*>& getSerializeQueue(){
			return m_serialize_queue;
		}
	
	
		SessionInfo& getSession(twine& sessionGUID);
		bool hasSession(twine& sessionGUID);
	
		SessionInfo& addSession(int user, twine username, twine fullname, twine dbname);

		void initFromDB( );
	
		void removeSession(IOConn& ioc, twine& sessionGUID);
	
		void expireSessions( Date& oldest, IOConn& ioc, twine& dbname);
	
		void loadUserProperties( SessionInfo& si, IOConn& ioc);

		/** This allows you to indicate that there are changes in session information
		 *  that need to be changed.  We'll get it onto the serialization queue so that
		 *  the changes will be written to disk.
		 */
		void Save(SessionInfo& si);

		/** Allows you to get a description of our current session list.  We
		 * create a new child of the xml node given and record our session information
		 * under it.
		 * 
		 */
		void describeSessions(xmlNodePtr node);
	
		/** Allows you to see a snapshot of our list of Sessions.  After this method
		 * returns, there is no guarantee that the session list will remain the same.
		 * 
		 */
		vector<SessionInfo*> getSessions();

		/**
		 * It generates an unique id.
		 * @return
		 */
		static twine generateUniqueId();

		/**
		 * It converts a byte array to hex a digits string
		 * @param bb - It's a byte array
		 * @return
		 */
		static twine bytesToHexString(char* bb);
	
};

}} // End Namespace Helix::Glob

#endif // SESSIONLIST_H Defined
