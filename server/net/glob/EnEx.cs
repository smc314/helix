/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;

namespace Helix.Glob
{
	public class EnEx : IDisposable
	{
		public string m_msg;
		public bool m_disposed = false;

		public EnEx (string msg)
		{
			m_msg = msg;
			Log.Trace (msg + " - Entering");
		}

		public void Dispose(){
			Dispose (true);
			GC.SuppressFinalize (this);
		}

		protected virtual void Dispose(bool disposing){
			if (m_disposed) {
				return; // nothing to do.
			}

			if (disposing) {
				// Free any managed objects here
				Log.Trace (m_msg + " - Exiting");

				m_msg = null;
			}

			// Free any unmanaged objects here

			m_disposed = true;
		}

		~EnEx(){
			Dispose (false);
		}

	}
}

