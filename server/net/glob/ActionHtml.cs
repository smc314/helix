/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.IO;
using System.Xml;

namespace Helix.Glob
{
	/// <summary>
	/// This is the html specific variant of the Action Class.
	/// </summary>
	public class ActionHtml : ActionClass
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="Helix.Glob.ActionHtml"/> class.
		/// </summary>
		/// <param name="action">Action.</param>
		public ActionHtml (XmlElement action) : base ()
		{
			m_name = action.GetAttribute ("name");
			m_license_group = action.GetAttribute ("group");
			m_requires_session = true;

			if (String.IsNullOrEmpty (m_name)) {
				throw new Exception ("Action missing urlbase!");
			}
			if (String.IsNullOrEmpty (m_license_group)) {
				throw new Exception ("Action missing group");
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="Helix.Glob.ActionHtml"/> class.
		/// </summary>
		/// <param name="name">Name.</param>
		public ActionHtml(string name) : base()
		{
			m_name = name;
			m_license_group = "";
			m_requires_session = false;
		}

		/// <summary>
		/// Checks to see if we match the given URL and returns the degree to which we
		/// match the URL.  Higher values indicate better matches.
		/// </summary>
		/// <returns>The degree to which we match the given URL - higher values indicate
		/// better matches.</returns>
		/// <param name="target_url">Target URL.</param>
		public int matchesURL(string target_url)
		{
			if (target_url.StartsWith (m_name)) {
				return m_name.Length;
			} else {
				return 0;
			}
		}

		/// <summary>
		/// We handle serving the given URL request.
		/// </summary>
		/// <param name="ioc">Ioc.</param>
		public override void ExecuteRequest (IOConn ioc)
		{
			using (EnEx ee = new EnEx ("ActionHtml::ExecuteRequest()")) {
				// What's the page?
				string html_page = ioc.MsgTarget ();

				if (html_page == "/") {
					html_page = "/index.html";
				}

				string html = "..";
				DateTime expires = DateTime.Now.AddDays (1);

				try {
					// Check for a qd/page first:
					if(html_page.StartsWith("/qd/")){
						// Accomodate our unit testing applications:
						if(html_page.Contains("/test/html/layouts/")){
							html_page.Replace(
								"/test/html/layouts/",
								"/build/layouts/"
							);
						}
						html = "../../.." + html_page;
						// don't expire these pages, they change all the time
						expires.AddDays(-2);
					} else if( html_page.StartsWith("/qooxdoo_toolkit")){
						html = ".." + html_page;
						// these are static, expires is just fine.
						expires.AddYears(1);
					} else if(html_page.StartsWith("/qooxdoo-contrib")){
						html = ".." + html_page;
						// these are static, expires is just fine
						expires.AddYears(1);
					} else if(html_page.StartsWith("/3rdParty/qooxdoo")){
						html = "../../../.." + html_page;
						// these are static, expires is just fine
						expires.AddYears(1);
					} else if(html_page.StartsWith("/logfile")){
						html = "." + html_page.Substring(8);
						// don't expire these pages, let the last-modified checks work
						expires.AddDays(-2);
					} else if(html_page.StartsWith("/forwardtosupport/")){
						html = "." + html_page;
						// don't expire these pages, let the last-modified checks work
						expires.AddDays(-2);
					} else {
						// Load the page from our html folder:
						html = "../../../html" + html_page;
						// don't expire these pages, let the last-modified checks work
						expires.AddDays(-2);
					}

					HttpConn hioc = (HttpConn)ioc;
					DateTime ims = hioc.GetIfModifiedSince();
					DateTime lastModified = File.GetLastWriteTime( html );

					if(lastModified <= ims){
						Log.Debug("Url {0} LastMod ({1}) < IfModSince ({2}) - Sending Not Modified",
							html_page, lastModified, ims );

						hioc.SendNotModified();
					} else {
						// Send the data
						Byte[] data = File.ReadAllBytes( html );

						Log.Debug("Serving ({0}) from ({1}) with size ({2})", html_page, html, data.Length );
						ioc.SendReturn(data, html, lastModified, expires );

					}
					ioc.Close();

				} catch (Exception){
					Log.Info ("Sending NotFound for request({0})", html_page);
					ioc.SendNotFound ();
					ioc.Close ();
				}
			}
		}
	}
}

