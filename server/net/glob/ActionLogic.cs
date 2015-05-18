/* ***************************************************************************

   Copyright (c): 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.IO;
using System.Xml;

namespace Helix.Glob
{
	/// <summary>
	/// Simple sample ActionLogic implementation that serves the html/index.html page.
	/// </summary>
	public class ActionLogic : ActionClass
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="Helix.Glob.ActionLogic"/> class.
		/// </summary>
		/// <param name="action">Action.</param>
		public ActionLogic (XmlElement action)
		{
			using (EnEx ee = new EnEx ("ActionLogic::ActionLogic(XmlElement action)")) {

				m_requires_session = true;

			}
		}

		/// <summary>
		/// We will serve the ../html/index.html page as a sample.
		/// </summary>
		/// <param name="ioc">Ioc.</param>
		public override void ExecuteRequest (IOConn ioc)
		{
			using (EnEx ee = new EnEx ("ActionLogic::ExecuteRequest(IOConn ioc)")) {

				// Send a simple welcome page back to the caller:
				String html = "../html/index.html";
				DateTime lastModified = File.GetLastWriteTime( html );
				Byte[] data = File.ReadAllBytes( html );

				ioc.SendReturn(data, html, lastModified, DateTime.Now );

				ioc.Close();
			}
		}
	}
}

