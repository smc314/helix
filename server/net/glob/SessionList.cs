/* ***************************************************************************

   Copyright (c): 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.IO;
using System.Threading;
using System.Xml;

namespace Helix.Glob
{
	public class SessionList
	{
		private SessionList ()
		{
			using (EnEx ee = new EnEx ("SessionList::SessionList()")) {
				m_sessions_mutex = new Mutex ();
				initFromDB ();
			}
		}

		public static SessionList getInstance()
		{
			using (EnEx ee = new EnEx ("SessionList::getInstance()")) {
				if (m_instance == null) {
					m_instance = new SessionList ();
				}
				return m_instance;
			}
		}

		public BlockingCollection<SessionInfo> getSerializeQueue()
		{
			return m_seralize_queue;
		}

		public SessionInfo getSession(string sessionGUID)
		{
			using (EnEx ee = new EnEx ("SessionList::getSession(string sessionGUID)")) {
				if (String.IsNullOrEmpty (sessionGUID)) {
					throw new Exception ("Invalid sessionGUID");
				}
				lock (m_sessions_mutex) {
					if (m_sessions.ContainsKey (sessionGUID)) {
						SessionInfo si = m_sessions [sessionGUID];

						// Update the fact that the session has been accessed
						// and serialize the update.
						si.lastaccess.SetCurrent ();
						m_serialize_queue.Add (si);

						// then return the session
						return si;
					} else {
						throw new Exception ("sessionGUID not found");
					}
				}
			}
		}

		public bool hasSession(string sessionGUID)
		{
			using (EnEx ee = new EnEx ("SessionList::hasSession(string sessionGUID)")) {
				if(String.IsNullOrEmpty(sessionGUID)){
					throw new Exception("Invalid sessionGUID");
				}
				lock (m_sessions_mutex) {
					if (m_sessions.ContainsKey (sessionGUID) ) {
						return true;
					} else {
						return false;
					}
				}
			}
		}

		public SessionInfo addSession(int user, string username, string fullname, string dbname)
		{
			using (EnEx ee = new EnEx ("SessionList::addSession(int user, string username, string fullname, string dbname)")) {
				lock(m_sessions_mutex){
					// Only allow a max of 4000 sessions.
					if(m_sessions.Count >= 4000 ){
						// Find the oldest session and delete it:
						SessionInfo oldest = null;
						foreach(KeyValuePair<String, SessionInfo> pair in m_sessions){
							if(oldest == null){
								oldest = pair.Value;
							} else {
								if(pair.Value.created < oldest.created){
									oldest = pair.Value;
								}
							}
						}
						if(oldest != null){
							SessionSerializer.EnsureSessionDir();
							string fileName = "./sessions/" + oldest.sessionGUID;
							File.Delete( fileName );

							m_sessions.Remove(oldest.sessionGUID);
						}
					}


					SessionInfo si = new SessionInfo();
					si.userid = user;
					si.username = username;
					si.fullname = fullname;
					si.dbname = dbname;
					si.sessionGUID = generateUniqueId();

					// Always add the current user id as a userProperty that can be referenced by SQL
					string userID;
					userID = user.ToString();
					si.userProperties["CurrentUserID"] = userID;
					si.userProperties["CurrentUserName"] = username;
					si.userProperties["CurrentUserFullName"] = fullname;
					si.userProperties["CurrentUserDB"] = dbname;

					m_sessions[si.sessionGUID] = si;

					// Drop it on the queue to be serialized.
					m_serialize_queue.Add( si );

					return si;
				}
			}
		}

		public void initFromDB()
		{
			using (EnEx ee = new EnEx ("SessionList::initFromDB()")) {
				lock(m_sessions_mutex){
					Log.Warn("Initializing SessionList from our stored sessions.");

					// Ensure that our directory exists
					SessionSerializer.EnsureSessionDir();

					IEnumerable<string> files = Directory.EnumerateFiles ("./sessions");
					foreach(string file in files){
						string fileName = "./sessions/" + file;
						XmlDocument doc = new XmlDocument ();
						try {
							doc.Load (fileName);
						} catch (Exception e){
							// Wasn't a valid xml file.  Log a warning about it and delete the file:
							Log.Warn("File {0} is invalid while loading sessions.  Deleting file.", fileName);
							File.Delete( fileName );
							continue;
						}

						// We have a valid document, decrypt it, re-animate it and add it to our sessions list.
						XmlElement root = doc.DocumentElement;
						if(root.Name == "Encrypted"){
							// This is an encrypted session doc, decrypt it before reading it:
							//MemBuf decryptedContents; decryptedContents.Decrypt( doc, TheMain::getInstance()->GetKeypair() );
							//twine decString; decString.set( decryptedContents(), decryptedContents.length() );
							//INFO(FL, "Decrypted Session:\n%s", decString() );
							//xmlDocPtr decdoc = xmlParseDoc((xmlChar*) decString() );
							//if(decdoc == NULL){
							//	WARN(FL, "Error reading decrypted xml document from original (%s)", fileName() );
							//	continue;
							//}
							//doc = decdoc;
						}

						SessionInfo si = new SessionInfo( doc );
						m_sessions[si.sessionGUID] = si;

					}
				}
			}
		}

		public void removeSession(IOConn ioc, string sessionGUID)
		{
			using (EnEx ee = new EnEx ("SessionList::removeSession(IOConn ioc, string sessionGUID)")) {
				lock(m_sessions_mutex){
					Log.Debug("Attempting to remove session ({0})", sessionGUID );

					if(m_sessions.ContainsKey(sessionGUID)0){
						try {
							SessionSerializer.EnsureSessionDir();
							string fileName = "./sessions/" + sessionGUID;
							Log.Debug("Removing session file ({0})", fileName );
							File.Delete( fileName );

							Log.Debug("Removing session ({0}) from session list", sessionGUID );
							m_sessions.Remove(sessionGUID);

						} catch (Exception e){
							Log.Error("Error deactivating session: {0}", e.Message);
						}
					}
				}
			}
		}

		public void expireSessions(DateTime oldest, IOConn ioc, string dbname)
		{
			using (EnEx ee = new EnEx ("SessionList::expireSessions(DateTime oldest, IOConn ioc, string dbname)")) {
				foreach(SessionInfo si in getSessions()){
					if(si.dbname == dbname && si.created < oldest ) {
						removeSession( ioc, si.sessionGUID );
					}
				}
			}
		}

		public void loadUserProperties(SessionInfo si, IOConn ioc)
		{
			using (EnEx ee = new EnEx ("SessionList::loadUserProperties(SessionInfo si, IOConn ioc)")) {

			}
		}

		public void Save(SessionInfo si)
		{
			using (EnEx ee = new EnEx ("SessionList::Save(SessionInfo si)")) {

			}
		}

		public void describeSessions(XmlElement node)
		{
			using (EnEx ee = new EnEx ("SessionList::describeSessions(XmlElement node)")) {
				XmlElement our_sessions = node.OwnerDocument.CreateElement ("SessionList");
				node.AppendChild (our_sessions);

				foreach(SessionInfo si in getSessions()){
					XmlElement session = node.OwnerDocument.CreateElement ("SessionInfo");
					our_sessions.AppendChild (SessionInfo);

					session.SetAttribute ("userid", si.userid.ToString ());
					session.SetAttribute ("dbname", si.dbname );
					session.SetAttribute ("sessionGUID", si.sessionGUID );
					session.SetAttribute ("created", si.created.ToString() );
					session.SetAttribute ("lastaccess", si.lastaccess.ToString() );
				}
			}
		}

		public List<SessionInfo> getSessions()
		{
			using (EnEx ee = new EnEx ("SessionList::getSessions()")) {

			}
		}

		public string generateUniqueId()
		{
			using (EnEx ee = new EnEx ("SessionList::generateUniqueId()")) {

			}
		}

		public string bytesToHexString(byte[] bytes)
		{
			using (EnEx ee = new EnEx ("SessionList::bytesToHexString(byte[] bytes)")) {

			}
		}

		public static SessionList m_instance;
		protected Dictionary<string, SessionInfo> m_sessions;
		protected Mutex m_sessions_mutex;
		protected BlockingCollection<SessionInfo> m_serialize_queue;


	}
}

