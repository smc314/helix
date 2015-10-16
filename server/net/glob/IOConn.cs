/* ***************************************************************************

   Copyright (c): 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Xml;
using System.Threading;
using System.Collections;
using System.Collections.Generic;

namespace Helix.Glob
{
	/// <summary>
	/// This class defines the interface for any indiviaul IO connection that
	/// we need to handle.  It is created by the IOInbound class that is actively
	/// listening for inbound connections, and it contains the entire contens of
	/// a single message that needs to be processed.  It knows how to pull
	/// the message contents from the specific IO mechanism that it was created for,
	/// and represent that message to the server in a standard way for processing.
	///
	/// @author Steven M. Cherry
	/// @copyright 2011 Steven M. Cherry
	/// </summary>
	public abstract class IOConn
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="Helix.Glob.IOConn"/> class.
		/// </summary>
		public IOConn ()
		{
			using (EnEx ee = new EnEx ("IOConn::IOConn()")) {
				m_resp_doc = null;
				m_db = null;
				m_db_mutex = null;
				m_override_target = "";
				m_has_responded = false;
				m_lr_taskid = "";

			}
		}

		protected void checkSessionID()
		{
			using (EnEx ee = new EnEx ("IOConn::checkSessionID()")) {

			}
		}

		protected bool allowedWOSession()
		{
			using (EnEx ee = new EnEx ("IOConn::allowedWOSession()")) {
				string msgTarget = MsgTarget ();
				if (msgTarget.StartsWith ("/helixlogin/") ||
				    msgTarget == "/js/helix.js" ||
				    msgTarget == "helix.png" ||
				    msgTarget == "/favicon.ico") {
					return true;
				} else {
					return false;
				}
			}
		}

		/** This allows the processing logic to query the connection to
		 * find out what message target should be used to process it.
		 */
		public abstract string MsgTarget();

		/** If the message processing setup decides that the user's request
		 * needs to be re-routed then this is how it will signal us to do so.
		 */
		public virtual void overrideMsgTarget(string newTarget)
		{
			using (EnEx ee = new EnEx ("IOConn::overrideMsgTarget()")) {
				m_override_target = newTarget;
			}
		}

		/** This will retrieve the Session ID from the inbound message.  If
		 * there is no session id on the inbound message, this will return null.
		 */
		public virtual string getSessionID()
		{
			using (EnEx ee = new EnEx ("IOConn::getSessionID()")) {
				/* In a pure xml implementation of the connection, the session information
				 * is stored in a section of the XML message that looks like this:
				 * <RequestDoc...>
				 *   <Session id="EncryptedGUID">
				 *   </Session>
				 * </RequestDoc>
				 */
				XmlDocument msg = GetMsg();
				if(msg == null) return "";
				XmlElement root = msg.DocumentElement;
				XmlElement session = XmlHelpers.FindChild(root, "Session");
				if(session == null) return "";
				return session.GetAttribute("id");
			}
		}

		/** This will set a new session id in the response document.  The client
		 * will use this for all further communications with the server.
		 */
		public virtual void setSessionID(string newSession)
		{
			using (EnEx ee = new EnEx ("IOConn::setSessionID(string newSession")) {
				// Request:
				XmlElement root = GetMsg ().DocumentElement;
				XmlElement session = root.OwnerDocument.CreateElement ("Session");
				root.AppendChild (session);
				session.SetAttribute ("id", newSession);

				// Response:
				root = getResponseRoot();
				session = root.OwnerDocument.CreateElement ("Session");
				root.AppendChild (session);
				session.SetAttribute ("id", newSession);
			}
		}

		/** This will generate a new session id and return it as a twine.
		 */
		public static string genSessionID()
		{
			using (EnEx ee = new EnEx ("IOConn::genSessionID()")) {
				return System.Guid.NewGuid ().ToString ();
			}
		}

		/** When GetMsg is called the IOConn object is responsible
		 * for presenting the contents of the inbound message to the
		 * caller as an XML document.  This allows the processing mechanisms
		 * to be standardized to xML and not have to worry about the specifics
		 * of the communications protocol.
		 */
		public abstract XmlDocument GetMsg();

		/** This returns the root element of the input Request message.
		 */
		public abstract XmlElement GetRequestRoot();

		/** This will parse our connection names in a standard way to pick out the Host, Port,
		  * and User information.
		  */
		public static void parseConnName(string connName, out string Host, out string Port, out string User)
		{
			using (EnEx ee = new EnEx ("IOConn::parseConnName()")) {
				// the connection name can have the format of either:
				// user@host:port
				//  - or -
				// alias (user@host:port)

				if(connName.IndexOf( "(" ) != -1 ) {
					// we have an alias format
					int idx1 = connName.IndexOf("(");
					int idx2 = connName.IndexOf(")");
					if(idx2 == -1){
						throw new Exception( String.Format("Invalid connection name format ({0})", connName) );
					}
					idx1++;
					string tmpConn = connName.Substring( idx1, idx2-idx1 );

					// Now do it the old way:
					string[] splits1 = tmpConn.Split('@');
					string[] splits2 = splits1[1].Split(':');
					Host = splits2[0];
					Port = splits2[1];
					User = splits1[0];

				} else {
					string[] splits1 = connName.Split('@');
					string[] splits2 = splits1[1].Split(':');
					Host = splits2[0];
					Port = splits2[1];
					User = splits1[0];
				}
			}
		}

		/** Since the IOConn object represents the life of the request, this is
		 * also the place where you can ask for a database connection to do
		 * any work that would be required by this request.
		 */
		public OdbcObj getDBConnection()
		{
			using (EnEx ee = new EnEx ("IOConn::getDBConnection()")) {
				return m_db; // FIXME: fix this.
			}
		}

		/** This is the standard way of looking up our session information.  It
		 * handles the case where our session does not exist by creating one properly
		 * and registering it with the SessionList.
		 */
		public SessionInfo getSessionInfo()
		{
			using (EnEx ee = new EnEx ("IOConn::getSessionInfo()")) {
				SessionList sl = SessionList.getInstance();
				string sID = getSessionID();
				if(sID.Length == 0 || sl.hasSession(sID) == false ){
					// No Session ID, or session id does not exist.  Either way, add a new
					// one that will get sent back with the next response
					SessionInfo newSI = sl.addSession(0, "user", "Full Name", "dbname");
					setSessionID( newSI.sessionGUID );
					sID = newSI.sessionGUID;
				}

				return sl.getSession( sID );
			}
		}

		/** This returns the name of our database pool, so that callers may see which
		 * DBName we are using to access the database.
		 */
		public string getDBName()
		{
			using (EnEx ee = new EnEx ("IOConn::getDBName()")) {
				return "unknown";
			}
		}

		/** This allows the processing logic to start an XML document that will
		 * be used as the response document.  We then have many interfaces that you
		 * can use to access/update this document before it is sent.
		 */
		public virtual XmlDocument initializeResponseDocument(string rootName)
		{
			using (EnEx ee = new EnEx ("IOConn::initializeResponseDocument(string rootName)")) {
				m_resp_doc = new XmlDocument ();
				XmlElement root = m_resp_doc.CreateElement (rootName);
				m_resp_doc.AppendChild (root);
				return m_resp_doc;
			}
		}

		/** This allows the processing logic to give us a complete XML document as the
		 * response content.
		 */
		public virtual XmlDocument initializeResponseDocument(XmlDocument resp)
		{
			using (EnEx ee = new EnEx ("IOConn::initializeResponseDocument(XmlDocument resp)")) {
				m_resp_doc = resp;
				return m_resp_doc;
			}
		}

		/** Returns the root element of the response document.  If the response
		 * document has not yet been initialized, this will initialize it.
		 */
		public virtual XmlElement getResponseRoot()
		{
			using (EnEx ee = new EnEx ("IOConn::getResponseRoot()")) {
				if (m_resp_doc == null) {
					initializeResponseDocument ("Response");
				}
				return m_resp_doc.DocumentElement;
			}
		}

		/** Sets a flag in the response indicating whether or not the contents have been
		  * filtered.
		  */
		public virtual void setResponseFiltered(bool tf)
		{
			using (EnEx ee = new EnEx ("IOConn::setResponseFiltered(bool tf)")) {
				getResponseRoot ().SetAttribute ("filtered", tf ? "true" : "false");
			}
		}

		/** Allows you to add an error message to the response document.  This keeps the
		 * layout of error responses consistent and ensures the client can react to them
		 * appropriately.
		 */
		public virtual void addResponseError(string msg, Exception e = null)
		{
			using (EnEx ee = new EnEx ("IOConn::addResponseError(string msg, Exception e)")) {
				XmlElement root = getResponseRoot ();
				root.SetAttribute ("haserror", "true");
				XmlElement errors = XmlHelpers.FindChild (root, "Errors");
				if (errors == null) {
					errors = root.OwnerDocument.CreateElement ("Errors");
					root.AppendChild (errors);
				}
				XmlElement error = root.OwnerDocument.CreateElement ("Error");
				errors.AppendChild (error);
				if (e != null) {
					error.SetAttribute ("msg", e.Message);
				} else {
					error.SetAttribute ("msg", msg);
				}
			}
		}

		/** Allows you to add a simple text message to the response document.
		 */
		public virtual void addResponseMessage(string msg)
		{
			using (EnEx ee = new EnEx ("IOConn::addResponseMessage(string msg)")) {
				XmlElement root = getResponseRoot ();
				XmlElement messages = XmlHelpers.FindChild (root, "Messages");
				if (messages == null) {
					messages = root.OwnerDocument.CreateElement ("Messages");
					root.AppendChild (messages);
				}
				XmlElement message = root.OwnerDocument.CreateElement ("Message");
				XmlHelpers.setCDATASection (message, msg);
			}
		}

		/** SendReturn is used by the processing logic to send the return response
		 * back to the original caller.  The IOConn object is responsible for knowing
		 * how to do this.
		 */
		public abstract void SendReturn ();

		/** This version of SendReturn is used to send back binary data
		 * that is not an XML document to the caller.
		 */
		public abstract void SendReturn(byte[] data, string fileName, 
			DateTime lastModified, DateTime expires);


		/** This version of SendReturn is used to send back binary data
		 * that is in a file that should be loaded by the IOConn and sent to the
		 * caller.  This is typically used for files larger than should be loaded 
		 * into memory all at once.  This way the IOConn can buffer the data without
		 * overloading system memory.
		 */
		public abstract void SendReturn(string filePath, string fileName, DateTime lastModified,
			DateTime expires);

		/** SendError is sued by the processing logic to send an error return response back to
		 * the original caller.
		 */
		public abstract void SendError();

		/** If the requested msg target does not exist, use this to send back an
		 * appropriate "not found" message.
		 */
		public abstract void SendNotFound();

		/** Releases the DB Connection back to the pool.
		 */
		public void ReleaseDB()
		{
			using (EnEx ee = new EnEx ("IOConn::ReleaseDB()")) {
				//FIXME: Implement
			}
		}

		/** Use this if you only want to complete the response to the user, but
		 * don't want to shut down the DB connection.
		 */
		public virtual void finishResponse()
		{
			using (EnEx ee = new EnEx ("IOConn::finishResponse()")) {
				m_has_responded = true;
			}
		}

		/** This is used to indicate that this connection has been fully processed
		 * by the server.
		 */
		public virtual void Close()
		{
			using (EnEx ee = new EnEx ("IOConn::Close()")) {
				finishResponse ();
				ReleaseDB ();
			}
		}

		/** Indicates whether we have sent the response or not.  This is triggered
		 * by the call to finishResponse either directly or indirectly via the
		 * Close method.
		 */
		public virtual bool hasResponded() 
		{ 
			return m_has_responded; 
		}

		/** Sets our long running task ID
		  */
		public void lrTaskID( string taskID )
		{
			m_lr_taskid = taskID;
		}

		/** Gets our long running task ID
		  */
		public string lrTaskID( )
		{
			return m_lr_taskid;
		}

		/** Updates our long running task ID with information about where we are.
		  */
		public void updateLRTask(int start, int current, int finish, string msg)
		{
			using (EnEx ee = new EnEx ("IOConn::updateLRTask()")) {
				if (String.IsNullOrEmpty (m_lr_taskid)) {
					return; // nothing to do
				}
				if (LongRunningTask.getInstance ().hasTask (m_lr_taskid)) {
					try {
						LongRunningTask.getInstance ().updateTask (m_lr_taskid, start, current, finish, msg);
					} catch (Exception) {
						// ignore this
					}
				}
			}
		}


		/// Our response document
		protected XmlDocument m_resp_doc;

		/// Our Database connection, if any
		protected OdbcObj m_db;

		/// Our DB Connection mutex, if any
		protected Mutex m_db_mutex;

		/// If we need to override the user's selected URL, this is where the override is stored
		protected string m_override_target;

		/// Have we responded yet?
		protected bool m_has_responded;

		/// We'll have one of these if we are created as a long running task
		protected string m_lr_taskid;

	}
}

