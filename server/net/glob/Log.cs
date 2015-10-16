/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.CompilerServices;

namespace Helix.Glob
{
	public class Log
	{
		public static bool m_Panic = true;
		public static bool m_Error = true;
		public static bool m_Warn = true;
		public static bool m_Info = true;
		public static bool m_Debug = false;
		public static bool m_Trace = false;
		public static bool m_SqlTrace = false;
		public static bool m_Lazy = false;
		public static BlockingCollection<LogMsg> m_logQueue = null;

		public Log ()
		{
		}

		public static void SetPanic(bool tf){
			m_Panic = tf;
		}

		public static void SetError(bool tf){
			m_Error = tf;
		}

		public static void SetWarn(bool tf){
			m_Warn = tf;
		}

		public static void SetInfo(bool tf){
			m_Info = tf;
		}

		public static void SetDebug(bool tf){
			m_Debug = tf;
		}

		public static void SetTrace(bool tf){
			m_Trace = tf;
		}

		public static void SetSqlTrace(bool tf){
			m_SqlTrace = tf;
		}

		public static void SetLazy(bool tf){
			GetLogQueue (); // Calling this ensures that we have initialized the m_logQueue.
			m_Lazy = tf;
		}

		public static BlockingCollection<LogMsg> GetLogQueue(){
			if (m_logQueue == null) {
				m_logQueue = new BlockingCollection<LogMsg> ();
			}
			return m_logQueue;
		}

		public static void Panic(
			string message, 
			params object[] options)
		{
			if (!m_Panic) return; // Bail out.
			Persist( PrepareMsg( 0, message, options ) );
		}

		public static void Error(
			string message, 
			params object[] options)
		{
			if (!m_Error) return; // Bail out.
			Persist( PrepareMsg( 1, message, options ) );
		}

		public static void Warn(
			string message, 
			params object[] options)
		{
			if (!m_Warn) return; // Bail out.
			Persist( PrepareMsg( 2, message, options ) );
		}

		public static void Info(
			string message, 
			params object[] options)
		{
			if (!m_Info) return; // Bail out.
			Persist( PrepareMsg( 3, message, options ) );
		}

		public static void Debug(
			string message, 
			params object[] options)
		{
			if (!m_Debug) return; // Bail out.
			Persist( PrepareMsg( 4, message, options ) );
		}

		public static void Trace(
			string message, 
			params object[] options)
		{
			if (!m_Trace) return; // Bail out.
			Persist( PrepareMsg( 5, message, options ) );
		}

		public static void SqlTrace(
			string message, 
			params object[] options)
		{
			if (!m_SqlTrace) return; // Bail out.
			Persist( PrepareMsg( 6, message, options ) );
		}

		public static LogMsg PrepareMsg(int channel, string message, params object[] options)
		{
			LogMsg lm = new LogMsg ();
			lm.channel = channel;
			lm.msg = String.Format (message, options);
			if (lm.msg.Length == message.Length) {
				lm.msg_static = true;
			}
			StackTrace st = new StackTrace (new StackFrame (true));
			StackFrame sf = st.GetFrame (2); // 0 is us, 1 is the Panic,Debug,etc. method above, 2 is the original caller
			lm.file = sf.GetFileName ();
			lm.line = sf.GetFileLineNumber ();
			return lm;
		}

		public static void Persist(LogMsg msg)
		{
			if (m_Lazy == true) {
				GetLogQueue ().Add (msg);
				return;
			}
			string channelName = "";
			switch(msg.channel){
			case 0:
				channelName = "PANIC";
				break;
			case 1:
				channelName = "ERROR";
				break;
			case 2:
				channelName = "WARN";
				break;
			case 3:
				channelName = "INFO";
				break;
			case 4:
				channelName = "DEBUG";
				break;
			case 5:
				channelName = "TRACE";
				break;
			case 6:
				channelName = "SQLTRACE";
				break;
			}
			// If we're not lazy logging, then log to the console:
			Console.WriteLine ("{0:yyyy/MM/dd HH:mm:ss.fff}|{1}|{2}|{3}|{4}|{5}",
				msg.timestamp, // {0}
				msg.tid,       // {1}
				msg.file,      // {2}
				msg.line,      // {3}
				channelName,   // {4}
				msg.msg        // {5}
			);
		}

	}
}

