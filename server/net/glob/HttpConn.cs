/* ***************************************************************************

   Copyright (c): 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Xml;
using System.Net;
using System.IO;
using System.IO.Compression;
using System.Text;


namespace Helix.Glob
{
	public class HttpConn : IOConn
	{
		public HttpConn (HttpListenerContext httpContext, int compressionThreshold, bool keepalive) : base()
		{
			using (EnEx ee = new EnEx ("HttpCon::HttpConn()")) {
				m_httpContext = httpContext;
				m_compressionThreshold = compressionThreshold;
				m_keepalive = keepalive;
				m_doc = null;
				m_doc_loaded = false;
				m_sessionid = "";
				m_sessionid_loaded = false;
				m_use_ssl = false;
				m_httpDomain = "";
				m_sessionCookie = "";
				m_compression_ok = false;
				if (m_compressionThreshold != 0) { // don't even check if it's not turned on.
					string enc = m_httpContext.Request.Headers ["Accept-Encoding"];
					if (!String.IsNullOrEmpty (enc)) {
						if (enc.Contains ("gzip")) {
							m_compression_ok = true;
						}
					}
				}
			}
		}

		/** This allows the processing logic to query the connection
		  * to find out what message target should be used to process
		  * it.
		  */
		public override string MsgTarget()
		{
			using (EnEx ee = new EnEx ("HttpCon::MsgTarget()")) {
				if (!String.IsNullOrEmpty (m_override_target)) {
					return m_override_target;
				} else {
					return m_httpContext.Request.Url.AbsolutePath;
				}
			}
		}

		/** This will retrieve the Session ID from the inbound message.  If
		 * there is no session id on the inbound message, this will return null.
		 */
		public override string getSessionID()
		{
			using (EnEx ee = new EnEx ("HttpCon::getSessionID()")) {
				if (m_sessionid_loaded) {
					return m_sessionid;
				}
				m_sessionid_loaded = true; // whether we find it or not, we've now looked for it once.

				// Check for it first in our cookies:
				string sessionCookieValue = null;
				foreach(Cookie c in m_httpContext.Request.Cookies){
					if (c.Name == "HelixSessionID") {
						sessionCookieValue = c.Value;
						break;
					}
				}

				if (!string.IsNullOrEmpty (sessionCookieValue)) {
					Log.Debug ("Setting sessionID from cookie: {0}", sessionCookieValue);
					m_sessionid = sessionCookieValue;
				} else {
					Log.Debug ("cookie not found. try it our parent's way.");
					m_sessionid = base.getSessionID ();
				}

				return m_sessionid;
			}
		}

		/** This will set a new session id in the response document.  The client will
		 * use this for all further communications with the server.
		 */
		public override void setSessionID(string newSession)
		{
			using (EnEx ee = new EnEx ("HttpCon::setSessionID(string newSession)")) {
				m_sessionid = newSession;
				m_sessionid_loaded = true;

				// Put it in the Response XML document:
				base.setSessionID (newSession);

				DateTime expires = DateTime.Now; // FIXME: getSessionInfo().created;
				m_sessionCookie = String.Format ("Set-Cookie: HelixSessionID={0}; path=/; expires={1:ddd, d MMMM yyyy HH:mm:ss GMT};\r\n",
					m_sessionid, expires);

			}
		}

		/** When GetMsg is called, the IOConn object is responsible
		  * for presenting the contents of the inbound message to
		  * the caller as an XML document.  This allows the processing
		  * mechanisms to be standardized to XML and not have to worry
		  * about the specifics of the communications protocol.
		  */
		public override XmlDocument GetMsg()
		{
			using (EnEx ee = new EnEx ("HttpCon::GetMsg()")) {
				if (!m_doc_loaded) {
					try {
						if (m_httpContext.Request.HttpMethod == "GET") {
							// Get's don't have a body
							m_doc_loaded = true;
							m_doc = null;
						} else {
							m_doc = new XmlDocument();
							m_doc.Load( m_httpContext.Request.InputStream );
							m_doc_loaded = true;
							Log.Debug("{0}", m_resp_doc.OuterXml );
						}
					} catch (Exception e) {
						Log.Warn ("Exception reading input doc:\n{0}", e.Message);
						m_doc = null;
						m_doc_loaded = true;
					}
				}
				return m_doc;
			}
		}

		/** This returns the root element of the input Request message.
		 */
		public override XmlElement GetRequestRoot()
		{
			using (EnEx ee = new EnEx ("HttpCon::GetRequestRoot()")) {
				XmlDocument doc = GetMsg ();
				if (doc == null) {
					throw new Exception ("No input request document found.");
				}
				return doc.DocumentElement;
			}
		}

		void WriteDataResponse(byte[] data, string mimeType)
		{
			using (EnEx ee = new EnEx ("HttpCon::GetRequestRoot()")) {
				bool isCompressed = MimeTypeMap.IsMimeCompressed (mimeType);

				Log.Debug("Compression ({0}) DataLen ({1}) Threshold ({2}) MimeType ({3})",
					m_compression_ok ? "true" : "false", data.Length, m_compressionThreshold, mimeType );
				if(m_compression_ok && data.Length >= m_compressionThreshold && isCompressed == false){
					byte[] compData = CompressData( data );
					Log.Debug("Sending back compressed data of size({0})", compData.Length);
					m_httpContext.Response.ContentLength64 = compData.Length;
					m_httpContext.Response.AddHeader ("Content-Encoding", "gzip");
					m_httpContext.Response.OutputStream.Write (compData, 0, compData.Length);
					m_httpContext.Response.OutputStream.Close();
					m_httpContext.Response.Close();
				} else {
					Log.Debug("Sending back un-compressed data of size({0})", data.Length);
					m_httpContext.Response.ContentLength64 = data.Length;
					m_httpContext.Response.OutputStream.Write (data, 0, data.Length);
					m_httpContext.Response.OutputStream.Close();
					m_httpContext.Response.Close();
				}
			}
		}

		public static byte[] CompressData( byte[] raw )
		{
			using (EnEx ee = new EnEx ("HttpCon::SendReturn()")) {
				using(MemoryStream memory = new MemoryStream()){
					using(GZipStream gzip = new GZipStream(memory, CompressionMode.Compress, true)){
						gzip.Write (raw, 0, raw.Length);
					}
					return memory.ToArray ();
				}
			}
		}

		/** SendReturn is used by the processing logic to send the
		  * return response back to the original caller.  The IOConn
		  * object is responsible for knowing how to do this, and if
		  * no response is actually necessary, IOConn is responsible
		  * for silently eating the message at this point.
		  */
		public override void SendReturn()
		{
			using (EnEx ee = new EnEx ("HttpCon::SendReturn()")) {
				if(m_resp_doc == null){
					initializeResponseDocument("Response");
				}
				try {
					string respString = m_resp_doc.OuterXml;
					Log.Debug("Response:\n{0}", respString );
					m_httpContext.Response.StatusCode = 200;
					m_httpContext.Response.AddHeader("Content-Type", "application/xml" );
					if(m_keepalive == false){
						m_httpContext.Response.AddHeader("Connection", "close");
					}
					if(m_sessionCookie.Length != 0){
						Cookie sessionCookie = new Cookie("HelixSessionID", m_sessionid);
						sessionCookie.Expires = DateTime.Now.AddYears(10); // FIXME: getSessionInfo().created + 10 years
						m_httpContext.Response.AppendCookie( sessionCookie );
					}
					WriteDataResponse( Encoding.UTF8.GetBytes( respString ), "text/xml" );

				} catch (Exception e){
					Log.Warn("Error sending response document: {0}", e.Message );
				}
			}
		}

		/** This version of SendReturn is used to send back binary data
		 * that is not an XML document to the caller.  This is used for
		 * serving static HTML pages, e.g.
		 */
		public override void SendReturn(byte[] data, string fileName, DateTime lastModified, 
			DateTime expires)
		{
			using (EnEx ee = new EnEx ("HttpCon::SendReturn(byte[] data, int dataLen, string fileName, DateTime lastModified, DateTime expires)")) {
				try {
					string mimeType = MimeTypeMap.GetMimeType( Path.GetExtension( fileName ) );
					m_httpContext.Response.StatusCode = 200;
					m_httpContext.Response.AddHeader("Last-Modified", FormatLastModified(lastModified));
					m_httpContext.Response.AddHeader("Content-Type", mimeType );
					if(m_keepalive == false){
						m_httpContext.Response.AddHeader("Connection", "close");
					}
					if(m_sessionCookie.Length != 0){
						Cookie sessionCookie = new Cookie("HelixSessionID", m_sessionid);
						sessionCookie.Expires = DateTime.Now.AddYears(10); // FIXME: getSessionInfo().created + 10 years
						m_httpContext.Response.AppendCookie( sessionCookie );
					}
					WriteDataResponse( data, mimeType );

				} catch (Exception e){
					Log.Warn("Error sending response document: {0}", e.Message );
				}
			}
		}

		public static string FormatLastModified(DateTime lastModified)
		{
			return String.Format ("{0:ddd, d MMMM yyyy HH:mm:ss GMT}", lastModified);
		}

		/** This version of SendReturn is used to send back binary data
		 * for files that are too large to read in all at once and send back.
		 */
		public override void SendReturn(string filePath, string fileName, DateTime lastModified, DateTime expires)
		{
			using (EnEx ee = new EnEx ("HttpCon::SendReturn(string filePath, string fileName, DateTime lastModified, DateTime expires)")) {
				try {
					string mimeType = MimeTypeMap.GetMimeType( Path.GetExtension( fileName ) );
					m_httpContext.Response.StatusCode = 200;
					m_httpContext.Response.AddHeader("Last-Modified", FormatLastModified(lastModified));
					m_httpContext.Response.AddHeader("Content-Type", mimeType );
					// This will prompt the user's browser to open the file-save-as dialog
					m_httpContext.Response.AddHeader("Content-Disposition:", String.Format("attachment; filename={0}", fileName) );
					if(m_keepalive == false){
						m_httpContext.Response.AddHeader("Connection", "close");
					}
					if(m_sessionCookie.Length != 0){
						Cookie sessionCookie = new Cookie("HelixSessionID", m_sessionid);
						sessionCookie.Expires = DateTime.Now.AddYears(10); // FIXME: getSessionInfo().created + 10 years
						m_httpContext.Response.AppendCookie( sessionCookie );
					}
					FileInfo fi = new FileInfo(fileName);
					m_httpContext.Response.ContentLength64 = fi.Length;
					using(FileStream fs = fi.OpenRead()){
						byte[] buff = new byte[4096000];
						int bytesRead = 0;
						while( (bytesRead = fs.Read(buff, 0, buff.Length)) != 0) {
							m_httpContext.Response.OutputStream.Write(buff, 0, bytesRead);
						}
					}
					m_httpContext.Response.OutputStream.Close();
					m_httpContext.Response.Close();

				} catch (Exception e){
					Log.Warn("Error sending response document: {0}", e.Message );
				}
			}
		}

		/** SendError is used by the processing logic to send an error
		  * return response back to the original caller.  The IOConn
		  * object is responsible for knowing how to do this, and if
		  * no response is actually necessary, IOConn is responsible
		  * for silently eating the message at this point.
		  */
		public override void SendError()
		{
			using (EnEx ee = new EnEx ("HttpCon::SendError()")) {
				SendReturn ();
			}
		}

		public override void SendNotFound()
		{
			using (EnEx ee = new EnEx ("HttpCon::SendNotFound()")) {
				try {
					m_httpContext.Response.StatusCode = 404;
					if(m_keepalive == false){
						m_httpContext.Response.AddHeader("Connection", "close");
					}
					m_httpContext.Response.OutputStream.Close();
					m_httpContext.Response.Close();

				} catch (Exception e){
					Log.Warn("Error sending not found response: {0}", e.Message );
				}
			}
		}

		public virtual void SendNotModified()
		{
			using (EnEx ee = new EnEx ("HttpCon::SendNotModified()")) {
				try {
					m_httpContext.Response.StatusCode = 304;
					if(m_keepalive == false){
						m_httpContext.Response.AddHeader("Connection", "close");
					}
					m_httpContext.Response.OutputStream.Close();
					m_httpContext.Response.Close();

				} catch (Exception e){
					Log.Warn("Error sending not modified response: {0}", e.Message );
				}
			}
		}

		public virtual void SendRedirect( string redirectTarget )
		{
			using (EnEx ee = new EnEx ("HttpCon::SendRedirect(string redirectTarget)")) {
				try {
					m_httpContext.Response.StatusCode = 301;
					m_httpContext.Response.AddHeader("Location", redirectTarget);
					if(m_keepalive == false){
						m_httpContext.Response.AddHeader("Connection", "close");
					}
					m_httpContext.Response.OutputStream.Close();
					m_httpContext.Response.Close();

				} catch (Exception e){
					Log.Warn("Error sending redirect response: {0}", e.Message );
				}
			}
		}

		public string getHttpDomain()
		{
			using (EnEx ee = new EnEx ("HttpCon::getHttpDomain()")) {
				return m_httpDomain;
			}
		}

		public static string GetMimeType(string fileName)
		{
			using (EnEx ee = new EnEx ("HttpCon::GetMimeType(string fileName)")) {
				return MimeTypeMap.GetMimeType (Path.GetExtension (fileName));
			}
		}

		public DateTime GetIfModifiedSince()
		{
			using (EnEx ee = new EnEx ("HttpCon::GetIfModifiedSince()")) {
				string ims = m_httpContext.Request.Headers ["If-Modified-Since"];
				if (String.IsNullOrEmpty (ims)) {
					return DateTime.Now.AddYears (-20);
				} else {
					return DateTime.Parse (ims);
				}
			}
		}


		/** Whether or not our connections are secure */
		protected bool m_use_ssl;

		/** Which http domain to use in cookies */
		protected string m_httpDomain;

		/// The message that we read from the soap connection.
		protected XmlDocument m_doc;
		protected bool m_doc_loaded;

		protected string m_sessionid;
		protected bool m_sessionid_loaded;

		protected bool m_compression_ok;
		protected int m_compressionThreshold;

		protected bool m_keepalive;

		protected string m_sessionCookie;

		protected HttpListenerContext m_httpContext;


	}
}

