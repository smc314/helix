// /* ***************************************************************************
//
//    Copyright (c): 2014 Hericus Software, Inc.
//
//    License: The MIT License (MIT)
//
//    Authors: Steven M. Cherry
//
// *************************************************************************** */
//
//
using System;
using System.Collections;
using System.Collections.Generic;

namespace Helix.Glob
{
	public class LogFile2
	{
		public LogFile2 ()
		{

		}

		public LogFile2(String fileName, int maxFileSize)
		{

		}

		public void close()
		{

		}

		public void createNewFile()
		{

		}

		public void writeMsg(LogMsg msg)
		{
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

		public void writeMsg(List<LogMsg> messages)
		{
			foreach (LogMsg msg in messages) {
				writeMsg (msg);
			}
		}
	}
}

