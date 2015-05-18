/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Threading;

namespace Helix.Glob
{

	/// <summary>
	/// This class represents a single log message.  All of the fields that
	/// we log are here as member variables.  This allows us to store log messages
	/// before writing them out to disk if that is what we want to do.
	/// </summary>
	public class LogMsg
	{
		public static string StaticAppName = null;
		public static string StaticMachineName = null;

		/// <summary>
		/// Standard Constructor
		/// </summary>
		public LogMsg ()
		{
			tid = Thread.CurrentThread.ManagedThreadId;
			SetTimestamp ();
			SetAppMachine ();

			id = 0;
			line = 0;
			channel = 0;
			appName = StaticAppName;
			machineName = StaticMachineName;
			msg_static = false;
		}

		/// <summary>
		/// Construct a log message with no application or transaction.
		/// </summary>
		/// <param name="f">File.</param>
		/// <param name="l">Line.</param>
		/// <param name="message">Message.</param>
		public LogMsg(string f, int l, string message)
		{
			tid = Thread.CurrentThread.ManagedThreadId;
			SetTimestamp ();
			SetAppMachine ();

			id = 0;
			file = f;
			line = l;
			channel = 0;
			msg = message;
			appName = StaticAppName;
			machineName = StaticMachineName;
			msg_static = false;
		}

		/// <summary>
		/// Construct a log message with just file and line.
		/// </summary>
		/// <param name="f">File.</param>
		/// <param name="l">Line.</param>
		public LogMsg(string f, int l)
		{
			tid = Thread.CurrentThread.ManagedThreadId;
			SetTimestamp ();
			SetAppMachine ();

			id = 0;
			file = f;
			line = l;
			channel = 0;
			appName = StaticAppName;
			machineName = StaticMachineName;
			msg_static = false;
		}

		/// <summary>
		/// A unique id for this log message
		/// </summary>
		public int id;

		/// <summary>
		/// Source File name of the log message
		/// </summary>
		public string file;

		/// <summary>
		/// Source File Line number of the log message
		/// </summary>
		public int line;

		/// <summary>
		/// Thread ID of the creator of this log message
		/// </summary>
		public int tid;

		/// <summary>
		/// Timestamp of the time of this log message
		/// </summary>
		public DateTime timestamp;

		/// <summary>
		/// A Specific log channel
		/// </summary>
		public int channel;

		/// <summary>
		/// An application name
		/// </summary>
		public string appName;

		/// <summary>
		/// A machine name for where the log originated
		/// </summary>
		public string machineName;

		/// <summary>
		/// An application specific unique id - usually like a session or connection token
		/// </summary>
		public string appSession;

		/// <summary>
		/// The actual log message
		/// </summary>
		public string msg;

		/// <summary>
		/// Whether this message is a static string or not.
		/// </summary>
		public bool msg_static;

		/// <summary>
		/// Sets the timestamp to right now.
		/// </summary>
		public void SetTimestamp()
		{
			timestamp = DateTime.Now;
		}

		/// <summary>
		/// Handles determining our application and machine name.
		/// </summary>
		public void SetAppMachine()
		{
			if (StaticMachineName == null) {
				StaticMachineName = System.Diagnostics.Process.GetCurrentProcess ().MachineName;
			}
			if (StaticAppName == null) {
				StaticAppName = System.Diagnostics.Process.GetCurrentProcess ().MainModule.ModuleName;
			}
		}

		/// <summary>
		/// Formats our timestamp in a standard way and returns it.
		/// </summary>
		/// <returns>The timestamp.</returns>
		public string GetTimestamp()
		{
			return String.Format ("{0:yyyy/MM/dd HH:mm:ss.fff}", timestamp);
		}
	}
}

