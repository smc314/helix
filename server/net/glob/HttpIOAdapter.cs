/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Xml;
using System.Net;
using System.Threading;

namespace Helix.Glob
{
	public class HttpState
	{
		public HttpListener listener;
		public Semaphore sem;
	}

	public class HttpIOAdapter : IOAdapter
	{
		public static int HttpIOAdapter_compressionThreshold;
		public static bool HttpIOAdapter_keepalive;

		public HttpIOAdapter ()
		{
			m_name = "HttpIOAdapter";
			m_port = 8082;
			m_local_ip = "";
			m_use_secure = false;
			m_sslCert = "";
			m_httpDomain = "";
			m_compressionThreshold = 1024;
			m_threads = 10;
			m_keepalive = "no";

			HttpIOAdapter_compressionThreshold = m_compressionThreshold;
			HttpIOAdapter_keepalive = m_keepalive == "yes" ? true : false;
		}

		public override void Init (XmlElement node)
		{
			m_name = node.GetAttribute ("name");
			if (String.IsNullOrEmpty (m_name)) {
				throw new Exception ("Missing name attribute on HTTP IOAdapter node.");
			}

			m_port = XmlHelpers.getIntAttr (node, "listen_port", 8082, 0, 32767);
			m_local_ip = node.GetAttribute ("listen_ip");
			m_use_secure = XmlHelpers.getBoolAttr (node, "sslcert");
			m_compressionThreshold = XmlHelpers.getIntAttr (node, "compressionThreshold");
			m_threads = XmlHelpers.getIntAttr (node, "threads", 10, 1, 100);
			m_httpDomain = node.GetAttribute ("httpdomain");
			m_keepalive = node.GetAttribute ("keepalive");
			if (String.IsNullOrEmpty (m_keepalive)) {
				m_keepalive = "no";
			}
			HttpIOAdapter_compressionThreshold = m_compressionThreshold;
			HttpIOAdapter_keepalive = m_keepalive == "yes" ? true : false;
			ActionMap.getInstance ().addHtmlAction ("/", "ActionHtml"); // Add the default page handler
		}

		public override void Execute ()
		{
			using (EnEx ee = new EnEx ("HttpIOAdapter::Execute()")) {
				m_listener = new HttpListener ();
				string prefix;
				if (m_use_secure) {
					prefix = "https://";
				} else {
					prefix = "http://";
				}
				if (!String.IsNullOrEmpty(m_httpDomain)) {
					prefix += m_httpDomain;
				} else {
					prefix += "*";
				}
				prefix += ":" + m_port + "/";

				Log.Info ("Setting up HttpIOAdapter({0}) with prefix({1})", m_name, prefix);

				m_listener.Prefixes.Add (prefix);
				m_listener.Start ();
				Semaphore sem = new Semaphore (m_threads, m_threads);
				while (TheMain.GetInstance ().isShutdown () == false) {
					if (sem.WaitOne (500)) { // wait for an available thread.
						// Semaphore was signaled - there's an avaialble listen thread spot
						if (TheMain.GetInstance ().isShutdown ()) {  // double-check just in case
							break; // exit loop if shutdown was triggered while we were waiting.
						}
						HttpState state = new HttpState ();
						state.listener = m_listener;
						state.sem = sem;
						m_listener.BeginGetContext (new AsyncCallback (HandleInbound), state);
					} else {
						// Semaphore wait timed out - loop again and check the shutdown flag
					}
				}
				m_listener.Stop ();
			}
		}

		public static void HandleInbound(IAsyncResult result)
		{
			HttpState state = (HttpState)result.AsyncState;
			// Call EndGetContext to complete the asyc operation
			HttpListenerContext context = state.listener.EndGetContext (result); 
			HttpListenerRequest request = context.Request;
			try {
				// Log details of the inbound HTTP request:
				if(Log.m_Debug ){ // don't bother building this debug message unless debugging is turned on.
					string http_req_info = String.Format("Http Request Info:\n" +
						"\tMethod: [{0}]\n" +
						"\tURI: [{1}]\n" +
						"\tHTTP Version: [{2}]\n" +
						"\tQuery String: [{3}]\n" +
						"\tReport IP: [{4}]\n" +
						"\tReport Port: [{5}]\n" +
						"Incomming HTTP Headers:\n",
						request.HttpMethod,
						request.Url.ToString(),
						request.ProtocolVersion.ToString(),
						request.QueryString.ToString(),
						request.RemoteEndPoint.Address.ToString(),
						request.RemoteEndPoint.Port.ToString()
					);


					foreach( String name in  request.Headers.AllKeys){
						String value = request.Headers[ name ];
						string tmp = String.Format("\t[{0}]: [{1}]\n", name, value );
						http_req_info += tmp;
					}

					Log.Debug("{0}", http_req_info );
				}

				HttpConn ioc = new HttpConn(context, HttpIOAdapter_compressionThreshold, HttpIOAdapter_keepalive);
				try {
					ActionClass handler = ActionMap.getInstance().findAction( ioc.MsgTarget() );
					if(handler == null){
						ioc.SendNotFound();
						return;
					}
					if(handler.isLongRunning()){
						// Clone the input document and setup the internal connection

						// Setup the long running task and return that immediately to tell the click to check back

						// Now drop the internal connection off for full processing.

					} else {
						// Execute the request directly
						handler.ExecuteRequest( ioc );
					}
				} catch (Exception e){
					Log.Error("Caught exception during handling of http inbound.  Aborting.\n{0}", e.Message );
					ioc.addResponseError( "Caught exception during handling of http inbound.", e);
					ioc.SendError();
				} finally {
					ioc.Close();
				}

			}catch(Exception e){
				Log.Error("Caught exception during outer handling of http inbound.  Aborting.\n{0}", e.Message );
			}finally{
				// Indicate to the semaphore that we are done with our processing, and another
				// listen/process thread can be started up.
				state.sem.Release (); 
			}
		}

		/// Our adapter name
		protected string m_name;

		/// our port number to listen on
		protected int m_port;

		/// Our local ip to listen on
		protected string m_local_ip;

		/// Whether we should use a secure listener or not.
		protected bool m_use_secure;

		/// Which httpDomain (if any) should be used when setting up cookies.
		protected string m_httpDomain;

		/// Where is the ssl certificate that we should use
		protected string m_sslCert;

		/// At what point should we start compressing return data?
		protected int m_compressionThreshold;

		/// How many threads should we let mongoose startup?
		protected int m_threads;

		/// Whether or not we have keepalive enabled.
		protected string m_keepalive;

		/// Our Listener
		protected HttpListener m_listener;
	}
}

