/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef IOCONN_H
#define IOCONN_H

#include <vector>
using namespace std;

#include <twine.h>
#include <xmlinc.h>
#include <AnException.h>
#include <Date.h>
#include <Mutex.h>
using namespace SLib;

namespace Helix {
namespace Glob {

class TheMain;

}} // End the namespaces

#include "ConnectionPool.h"
#include "OdbcObj.h"
#include "SessionInfo.h"

namespace Helix {
namespace Glob {

/** 
  * This class defines the interface for any indiviaul IO connection that
  * we need to handle.  It is created by the IOInbound class that is actively
  * listening for inbound connections, and it contains the entire contens of
  * a single message that needs to be processed.  It knows how to pull
  * the message contents from the specific IO mechanism that it was created for,
  * and represent that message to the server in a standard way for processing.
  *
  * @author Steven M. Cherry
  * @copyright 2011 Steven M. Cherry
  */
class IOConn
{
	public:
		/// Standard constructor.
		IOConn();

		virtual ~IOConn();

		/** This allows the processing logic to query the connection to
		 * find out what message target should be used to process it.
		 */
		virtual twine MsgTarget(void) = 0;

		/** If the message processing setup decides that the user's request
		 * needs to be re-routed then this is how it will signal us to do so.
		 */
		virtual void overrideMsgTarget(const twine newTarget);

		/** This will retrieve the Session ID from the inbound message.  If
		 * there is no session id on the inbound message, this will return null.
		 */
		virtual twine getSessionID();

		/** This will set a new session id in the response document.  The client
		 * will use this for all further communications with the server.
		 */
		virtual void setSessionID(const twine newSession);

		/** This will generate a new session id and return it as a twine.
		 */
		static twine genSessionID();

		/** When GetMsg is called the IOConn object is responsible
		 * for presenting the contents of the inbound message to the
		 * caller as an XML document.  This allows the processing mechanisms
		 * to be standardized to xML and not have to worry about the specifics
		 * of the communications protocol.
		 */
		virtual xmlDocPtr GetMsg(void) = 0;

		/** This returns the root element of the input Request message.
		 */
		virtual xmlNodePtr GetRequestRoot(void) = 0;

		/** This will parse our connection names in a standard way to pick out the Host, Port,
		  * and User information.
		  */
		static void parseConnName(twine& connName, twine& Host, twine& Port, twine& User);

		/** Since the IOConn object represents the life of the request, this is
		 * also the place where you can ask for a database connection to do
		 * any work that would be required by this request.
		 */
		OdbcObj* getDBConnection(void);
	
		/** This is the standard way of looking up our session information.  It
		 * handles the case where our session does not exist by creating one properly
		 * and registering it with the SessionList.
		 */
		SessionInfo& getSessionInfo(void);
	
		/** This returns the name of our database pool, so that callers may see which
		 * DBName we are using to access the database.
		 */
		twine getDBName(void);

		/** This allows the processing logic to start an XML document that will
		 * be used as the response document.  We then have many interfaces that you
		 * can use to access/update this document before it is sent.
		 */
		virtual xmlDocPtr initializeResponseDocument(const char* rootName);

		/** This allows the processing logic to give us a complete XML document as the
		 * response content.
		 */
		virtual xmlDocPtr initializeResponseDocument(xmlDocPtr resp);

		/** Returns the root element of the response document.  If the response
		 * document has not yet been initialized, this will initialize it.
		 */
		virtual xmlNodePtr getResponseRoot(void);

		/** Sets a flag in the response indicating whether or not the contents have been
		  * filtered.
		  */
		virtual void setResponseFiltered(bool tf);

		/** Allows you to add an error message to the response document.  This keeps the
		 * layout of error responses consistent and ensures the client can react to them
		 * appropriately.
		 */
		virtual void addResponseError(twine msg, AnException* e);

		/** Allows you to add a simple text message to the response document.
		 */
		virtual void addResponseMessage(twine msg);

		/** SendReturn is used by the processing logic to send the return response
		 * back to the original caller.  The IOConn object is responsible for knowing
		 * how to do this.
		 */
		virtual void SendReturn(void) = 0;

		/** This version of SendReturn is used to send back binary data
		 * that is not an XML document to the caller.
		 */
		virtual void SendReturn(unsigned char* data, int dataLen, twine fileName, 
			Date lastModified, Date expires) = 0;


		virtual void SendReturn(twine& filePath, twine& fileName, Date lastModified,
			Date expires) = 0;

		/** SendError is sued by the processing logic to send an error return response back to
		 * the original caller.
		 */
		virtual void SendError(void) = 0;

		/** If the requested msg target does not exist, use this to send back an
		 * appropriate "not found" message.
		 */
		virtual void SendNotFound(void) = 0;

		/** Releases the DB Connection back to the pool.
		 */
		void ReleaseDB(void);


		/** Use this if you only want to complete the response to the user, but
		 * don't want to shut down the DB connection.
		 */
		virtual void finishResponse(void);

		/** This is used to indicate that this connection has been fully processed
		 * by the server.
		 */
		virtual void Close(void);

		/** Indicates whether we have sent the response or not.  This is triggered
		 * by the call to finishResponse either directly or indirectly via the
		 * Close method.
		 */
		virtual bool hasResponded(void) { return m_has_responded; }

		/** Sets our long running task ID
		  */
		void lrTaskID( const twine& taskID );

		/** Gets our long running task ID
		  */
		const twine& lrTaskID( );

		/** Updates our long running task ID with information about where we are.
		  */
		void updateLRTask(intptr_t start, intptr_t current, intptr_t finish, const twine& msg);

	protected:

		/** Checks the session id to see if it is valid.  Throws a RedirectRequired,
		 * or simple Exception if something went wrong.
		 */
		void checkSessionID(void);

		/** There's a certain hard-coded list of message targets that are allowed
		 * without a session.
		 */
		bool allowedWOSession(void);

		/// Our response document
		xmlDocPtr m_resp_doc;

		/// Our Database Connection, if any
		OdbcObj* m_db;

		/// Our DB Connection mutex, if any
		Mutex* m_db_mutex;

		/// If we need to overrid the user's selected URL, this is where the overrid is stored
		twine m_override_target;

		bool m_has_responded;		

		/// We'll have one of these if we are created as a long running task:
		twine m_lr_taskid;


};

}} // End Namespace Helix::Glob

#endif // IOCONN_H Defined
