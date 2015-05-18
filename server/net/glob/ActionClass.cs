/* ***************************************************************************

   Copyright (c): 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;

namespace Helix.Glob
{
	/// <summary>
	/// The parent class for all of our logic actions that the server supports.
	/// </summary>
	public abstract class ActionClass
	{
		public string m_name;
		public string m_license_group;
		public bool m_requires_session;
		public bool m_delete_required;


		public ActionClass ()
		{
		}

		/// <summary>
		/// Must be implemented by children - this will do the work of actually executing
		/// the logic represented by this task.
		/// </summary>
		/// <param name="ioc">Ioc.</param>
		public abstract void ExecuteRequest (IOConn ioc);

		/// <summary>
		/// Returns whether or not this task is a long running task.  Long running
		/// tasks will return immediately to the caller and place themselves in a 
		/// background queue that the caller can then poll until the task is done.
		/// </summary>
		/// <returns><c>true</c>, if the task is long running, <c>false</c> otherwise.</returns>
		public bool isLongRunning ()
		{
			return false;  // The default is to return false
		}

		/// <summary>
		/// Returns the name of this task.
		/// </summary>
		/// <returns>The task name.</returns>
		public string lrTaskName()
		{
			return "Action Class - Generic Task Name";
		}

	}
}

