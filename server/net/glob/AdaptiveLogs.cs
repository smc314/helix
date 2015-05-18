/* ***************************************************************************

   Copyright (c): 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Xml;


namespace Helix.Glob
{

	/// <summary>
	/// This class is used to represent logging parameters that the user can
	/// set via our config file.
	///
	/// @author Steven M. Cherry
	/// </summary>
	public class AdaptiveLogParm
	{
		public bool onoff;
		public bool buffer_when_off;
		public int  dump_when_hit;
	}

	/// <summary>
	/// This class is responsible for implementing all of our adaptive logging
	/// rules and functionality.  It is launched at initialization on a thread
	/// and it is supposed to drain the SLib::Log queue, and decide what actually
	/// will be written out to the disk.
	/// <P>
	/// We use the AdaptiveLogs tag in the config file for our setup
	/// and we implement a number of things.
	/// <P>
	/// This class exists so that all of our logging control mechanisms may be
	/// implemented in one place and none of the rest of our code set has to worry
	/// about them.
	///
	/// @author Steven M. Cherry
	/// </summary>
	public class AdaptiveLogs : Threadable
	{
		/// <summary>
		///  
		/// </summary>
		public AdaptiveLogs ()
		{
			using (EnEx ee = new EnEx ("AdaptiveLogs::AdaptiveLogs()")) {
				// Ensure that all logging goes into the queue that we will drain
				Log.SetLazy (true);

				m_record_stats = false;
				m_paused = false;
				m_logForwarding = false;

				ReadConfig();
				Setup();
			}
		}

		public LogFile2 LogFile()
		{
			return m_file;
		}

		public void LogPrint(string message, params object[] options)
		{
			if (!m_enable_logprint)
				return;

			Console.WriteLine (message, options);
		}

		public override void Execute()
		{
			LogPrint ("AdaptiveLogs::Execute()");
			using (EnEx ee = new EnEx ("AdaptiveLogs::Execute()")) {
				Log.Info ("AdaptiveLogs Log Processor Thread starting");

				try {
					uint loopCount = 1;
					while(!m_shutdown){
						while(!m_paused && !m_shutdown){
							LogMsg lmi = Log.GetLogQueue().Take();
							if(lmi != null){
								ProcessMessage(lmi);
							}

							if(loopCount % 100 == 0){
								m_record_stats = true; // record stats every 100 log messages.
							} else {
								m_record_stats = false;
							}
							loopCount ++;
						}
						if(m_paused){
							System.Threading.Thread.Sleep(100); // 1/10th second sleep
						}
					}

				} catch (Exception e){
					Log.SetLazy (false);
					Log.Error ("Caught exception during AdaptiveLogs::Execute()\n{0}\n===\n{1}",
						e.Message, e.StackTrace);
				}
			}
		}

		public void DrainLastLogs()
		{
			LogPrint ("AdaptiveLogs::DrainLastLogs()");
			using (EnEx ee = new EnEx ("AdaptiveLogs::DrainLastLogs()")) {
				int count = 0;
				try {
					while(count < 1000){ // only do up to 1000
						LogMsg lm;
						if( Log.GetLogQueue().TryTake( out lm ) ){
							ProcessMessage( lm );
							count++;
						} else {
							break; // nothing left in the queue
						}
					}
				} catch(Exception e){
					Log.Error ("Caught exception during AdaptiveLogs::DrainLastLogs()\n{0}\n===\n{1}",
						e.Message, e.StackTrace);
				}
			}
		}

		public void RefreshConfig()
		{
			LogPrint ("AdaptiveLogs::RefreshConfig()");
			using (EnEx ee = new EnEx ("AdaptiveLogs::RefreshConfig")) {
				// Shutdown the log file for a moment
				m_paused = true; // Pause processing of incomming messages.
				Log.Warn ("AdaptiveLogs pausing logger to re-read configuration file.");
				System.Threading.Thread.Sleep (500);  // Ensure that the pause is noticed.

				// Close the log file
				// FIXME: implement
				Log.Warn ("AdaptiveLogs log file closed...Reading configuration.");

				// Re-read the config and re-setup our log file:
				m_log_parms.Clear ();
				ReadConfig ();
				Setup ();

				// Un-pause log message processing:
				m_paused = false;
				Log.Warn ("AdaptiveLogs configuration re-read, logging active again.");
			}
		}

		public void ReadConfig()
		{
			LogPrint ("AdaptiveLogs::ReadConfig()");
			using (EnEx ee = new EnEx ("AdaptiveLogs::ReadConfig()")) {
				XmlElement root = TheMain.GetInstance ().GetConfig ().DocumentElement;
				XmlElement ad_log = XmlHelpers.FindChild (root, "AdaptiveLogs");
				if (ad_log == null) { // wasn't found
					DefaultSettings ();
					return;
				}

				if (ad_log.HasAttribute ("filename")) {
					m_file_name = ad_log.GetAttribute ("filename");
				} else {
					m_file_name = "helix.log";
				}

				m_max_buffer_size = XmlHelpers.getIntAttr (ad_log, "buffer_size", 1000, 10, 10000);
				m_max_file_size = XmlHelpers.getIntAttr (ad_log, "max_file_size", 
					52428800, // default = 50 meg file chunks
					1024000, // min = 1meg
					1024000 * 100 // max = 100meg
				);

				// Find each log channel and provide defaults if not found
				FindAndSetChannel (ad_log, "Panic", true, true, 1000);
				FindAndSetChannel (ad_log, "Error", true, true, 100);
				FindAndSetChannel (ad_log, "Warn", true, true, 50);
				FindAndSetChannel (ad_log, "Info", true, true, 0);
				FindAndSetChannel (ad_log, "Debug", false, true, 0);
				FindAndSetChannel (ad_log, "Trace", false, false, 0);
				FindAndSetChannel (ad_log, "SqlTrace", false, false, 0);

				// Check for a log forwarding setup
				XmlElement forwarding = XmlHelpers.FindChild (ad_log, "LogForwarding");
				if (forwarding != null) {
					m_logForwarding = XmlHelpers.getBoolAttr (forwarding, "onoff");
					m_logForwardHost = forwarding.GetAttribute ("targethost");
					m_logForwardPort = forwarding.GetAttribute ("targetport");
				}
			}
		}

		public void FindAndSetChannel(XmlElement ad_log, string channel_name, bool onoff, bool buffer_when_off, int dump_when_hit)
		{
			LogPrint ("AdaptiveLogs::FindAndSetChannel()");
			using(EnEx ee = new EnEx("AdaptiveLogs::FindAndSetChannel()")){
				XmlElement log;
				AdaptiveLogParm alp = new AdaptiveLogParm();

				// Find the log channel
				log = XmlHelpers.FindChild(ad_log, channel_name);
				if(log == null){ // wasn't found
					alp.onoff = onoff;
					alp.buffer_when_off = buffer_when_off;
					alp.dump_when_hit = dump_when_hit;
					m_log_parms.Add (alp);
					return;
				}

				alp.onoff = XmlHelpers.getBoolAttr (log, "onoff", onoff);
				alp.buffer_when_off = XmlHelpers.getBoolAttr (log, "buffered_when_off", buffer_when_off);
				alp.dump_when_hit = XmlHelpers.getIntAttr (log, "dump_when_hit", dump_when_hit, 0, m_max_buffer_size);

				m_log_parms.Add(alp);
			}
		}

		public void DefaultSettings()
		{
			LogPrint ("AdaptiveLogs::DefaultSettings()");
			using (EnEx ee = new EnEx ("AdaptiveLogs::DefaultSettings()")) {
				// Default log settings:
				m_max_buffer_size = 1000;
				m_max_file_size = 0;
				m_file_name = "helix.log";

				// Panic:
				AdaptiveLogParm panic = new AdaptiveLogParm();
				panic.onoff = true;
				panic.buffer_when_off = true;
				panic.dump_when_hit = 1000;
				m_log_parms.Add(panic);

				// Error:
				AdaptiveLogParm error = new AdaptiveLogParm();
				error.onoff = true;
				error.buffer_when_off = true;
				error.dump_when_hit = 100;
				m_log_parms.Add(error);

				// Warn:
				AdaptiveLogParm warn = new AdaptiveLogParm();
				warn.onoff = true;
				warn.buffer_when_off = true;
				warn.dump_when_hit = 100;
				m_log_parms.Add(warn);

				// Info:
				AdaptiveLogParm info = new AdaptiveLogParm();
				info.onoff = true;
				info.buffer_when_off = true;
				info.dump_when_hit = 0;
				m_log_parms.Add(info);

				// Debug:
				AdaptiveLogParm debug = new AdaptiveLogParm();
				debug.onoff = false;
				debug.buffer_when_off = true;
				debug.dump_when_hit = 0;
				m_log_parms.Add(debug);

				// Trace:
				AdaptiveLogParm trace = new AdaptiveLogParm();
				trace.onoff = false;
				trace.buffer_when_off = false;
				trace.dump_when_hit = 0;
				m_log_parms.Add(trace);

				// SqlTrace:
				AdaptiveLogParm sqlt = new AdaptiveLogParm();
				sqlt.onoff = false;
				sqlt.buffer_when_off = false;
				sqlt.dump_when_hit = 0;
				m_log_parms.Add(sqlt);

			}
		}

		public void Setup()
		{
			LogPrint ("AdaptiveLogs::Setup()");
			using (EnEx ee = new EnEx ("AdaptiveLogs::Setup()")) {
				if(m_log_parms.Count < 7){ // bad
					throw new Exception(
						String.Format("Log Parms size should always be at least 7.  It is ({0})", m_log_parms.Count ) 
					);
				}

				// Panic setup
				if(m_log_parms[0].onoff || m_log_parms[0].buffer_when_off){
					Log.SetPanic(true);
				} else {
					Log.SetPanic(false);
				}

				// Error setup
				if(m_log_parms[1].onoff || m_log_parms[1].buffer_when_off){
					Log.SetError(true);
				} else {
					Log.SetError(false);
				}

				// Warn setup
				if(m_log_parms[2].onoff || m_log_parms[2].buffer_when_off){
					Log.SetWarn(true);
				} else {
					Log.SetWarn(false);
				}

				// Info setup
				if(m_log_parms[3].onoff || m_log_parms[3].buffer_when_off){
					Log.SetInfo(true);
				} else {
					Log.SetInfo(false);
				}

				// Debug setup
				if(m_log_parms[4].onoff || m_log_parms[4].buffer_when_off){
					Log.SetDebug(true);
				} else {
					Log.SetDebug(false);
				}

				// Trace setup
				if(m_log_parms[5].onoff || m_log_parms[5].buffer_when_off){
					Log.SetTrace(true);
				} else {
					Log.SetTrace(false);
				}

				// SqlTrace setup
				if(m_log_parms[6].onoff || m_log_parms[6].buffer_when_off){
					Log.SetSqlTrace(true);
				} else {
					Log.SetSqlTrace(false);
				}

				// Other logs as added go here


				// Open up our log file:
				try {
					m_file = new LogFile2( m_file_name, m_max_file_size );
				} catch (Exception e){
					// Something bad happened while trying to open our log file.
					m_file = null;
					m_shutdown = true;
					// Reset SLib::Log to non-lazy so messages don't go to the queue
					Log.SetLazy(false);

					Log.Panic("Exception raised opening log file: %s\n", e.Message );
					return; // do nothing else
				}

				//m_max_id = m_file->getNewestMessageID();
			}
		}

		public void ProcessMessage(LogMsg msg)
		{
			LogPrint ("AdaptiveLogs::ProcessMessage(LogMsg lm)");
			using (EnEx ee = new EnEx ("AdaptiveLogs::ProcessMessage(LogMsg lm)")) {

				// find the parameters based on the channel
				if(msg.channel < 0 || msg.channel >= m_log_parms.Count){
					// bad channel number on the log, throw it away.
					return;
				}

				AdaptiveLogParm alp = m_log_parms[msg.channel];

				// If it's not on and not buffered, then throw it away
				if(alp.onoff == false && alp.buffer_when_off == false){
					return;
				}

				// if it's not on, but buffered, then add it to the buffer
				if(alp.onoff == false && alp.buffer_when_off == true){
					AddLogToBuffer(msg);
					return;
				}

				// if it's on:
				if(alp.onoff){
					// Initialize our forwarding message
					InitForwardMsg();

					// tail the buffer by dump_when_hit
					BufferTail(alp.dump_when_hit);

					// Write the log message out
					WriteLogMsg(msg);

					// Empty the buffer, 'cause they're all out of order now.
					ClearBuffer();

					// Send our forwarding message
					SendForwardMsg();
				}
			} 
		}

		public void WriteLogMsg(LogMsg lm)
		{
			LogPrint("AdaptiveLogs::WriteLogMsg(LogMsg* lm)");
			using(EnEx ee = new EnEx("AdaptiveLogs::WriteLogMsg(LogMsg* lm)")){

				try {
					m_log_stage.Add( lm );
					m_file.writeMsg( m_log_stage );

				} catch (Exception e){
					Console.Write("Caught exeption during write:\n{0}\n{1}\n", e.Message, e.StackTrace );
					// If anything goes wrong writing this message to the log file, simply close
					// the log file and start a new one.
					try {
						m_file.createNewFile();			
						m_file.writeMsg( m_log_stage );
					} catch(Exception e2){
						Console.Write("Badnews! 2nd exception caught trying to log:\n{0}\n{1}\n", e2.Message, e2.StackTrace );
						try {
							m_file.close();
							m_file = new LogFile2( m_file_name, m_max_file_size);
						} catch (Exception e3){
							Console.Write("Panic! 3rd exception caught trying to log:\n{0}\n{1}\n", e3.Message, e3.StackTrace );
							throw e3;
						}
					}
				}
				ClearStage();

				AddForwardMsg( lm );
			}
		}

		public void AddLogToBuffer(LogMsg lm)
		{
			LogPrint("AdaptiveLogs::AddLogToBuffer(LogMsg* lm)");
			using(EnEx ee = new EnEx("AdaptiveLogs::AddLogToBuffer(LogMsg* lm)")){
				m_log_buffer.Add(lm);
				if(m_log_buffer.Count > m_max_buffer_size){
					// delete the message on the front of the buffer.
					m_log_buffer.RemoveAt(0);
				}
			}
		}

		public void BufferTail(int count)
		{
			LogPrint("AdaptiveLogs::BufferTail(int count)");
			using(EnEx ee = new EnEx("AdaptiveLogs::BufferTail(int count)")){
				int i;

				ClearStage();
				int size = (int)m_log_buffer.Count;

				// if they want more than what we have, then just dump the whole thing
				if(count >= size){
					foreach(LogMsg msg in m_log_buffer){
						AddForwardMsg( msg );
						m_log_stage.Add( msg );
					}
					return;
				}

				// if they want less than what we have, then only give 'em the last
				// ones that they asked for.

				i = 0;
				foreach (LogMsg msg in m_log_buffer) {
					if (i < (size - count)) {
						i++;
						continue; // skip over the ones at the beginning
					}
					// once we've skipped the ones at the beginning, start recording
					// messages in order from the end.
					AddForwardMsg (msg);
					m_log_stage.Add (msg);
				}
			}
		}

		void ClearBuffer()
		{
			LogPrint("AdaptiveLogs::ClearBuffer()");
			using(EnEx ee = new EnEx("AdaptiveLogs::ClearBuffer()") ){
				m_log_buffer.Clear();
			}
		}

		void ClearStage()
		{
			LogPrint("AdaptiveLogs::ClearStage()");
			using(EnEx ee = new EnEx("AdaptiveLogs::ClearStage()")){
				m_log_stage.Clear();
			}
		}

		BlockingCollection<LogMsg> GetExternalLogQueue()
		{
			return m_external_logs;
		}

		void InitForwardMsg()
		{
			LogPrint("AdaptiveLogs::InitForward()");
			using(EnEx ee = new EnEx("AdaptiveLogs::InitForward()")){
				if(!m_logForwarding){
					return;
				} else {
					m_forwardMsg = "<SaveLogMsg>";
				}
			}
		}

		void AddForwardMsg(LogMsg lm)
		{
			LogPrint("AdaptiveLogs::AddForwardMsg(LogMsg* lm)");
			using(EnEx ee = new EnEx("AdaptiveLogs::AddForwardMsg(LogMsg* lm)")){
				if(!m_logForwarding){
					return;
				}

				string logxml = "<LogObj id=\"0\" file=\"{0}\" line=\"{1}\" tid=\"{2}\" timestamp_a=\"{3}\"" +
					" timestamp_b=\"{4}\" timestamp_c=\"\" channel=\"{5}\" appName=\"{6}\" machineName=\"{7}\">" +
					"<msg><![CDATA[{8}]]></msg></LogObj>";

				var msgBytes = System.Text.Encoding.UTF8.GetBytes( lm.msg );
				string xml = String.Format( logxml,
					lm.file, lm.line, lm.tid,
					lm.timestamp.ToFileTime(),
					lm.timestamp.Millisecond,
					lm.channel, lm.appName, lm.machineName, System.Convert.ToBase64String(msgBytes)
				);

				m_forwardMsg += xml;
			}
		}

		void SendForwardMsg()
		{
			LogPrint("AdaptiveLogs::SendForwardMsg()");
			using (EnEx ee = new EnEx ("AdaptiveLogs::SendForwardMsg()")) {
				if (!m_logForwarding) {
					return;
				}

				m_forwardMsg += "</SaveLogMsg>";

				string url = String.Format ("http://{0}:{1}/logic/utils/SaveLogMsg", m_logForwardHost, m_logForwardPort );
				//HttpClient.PostPage (url, m_forwardMsg, m_forwardMsg.Length);
			}
		}

		/* Use this to turn on/off console writelines for entry to each method.  -- this is
		 * our kludge answer to the age old question: how do you log the logger when you need
		 * to debug it?
		 */
		private bool m_enable_logprint = false;


		/// File name that we log to
		private string m_file_name;

		/// LogFile that we use
		private LogFile2 m_file;

		/// Largest message id in use:
		int m_max_id;

		/// Max size of current log file:
		int m_max_file_size;

		/// Max size of our log buffer
		int m_max_buffer_size;

		/// SLib::Log queue that we drain
		BlockingCollection<LogMsg> m_log_queue;

		BlockingCollection<LogMsg> m_external_logs;

		/// Log parameters
		List < AdaptiveLogParm > m_log_parms;

		/// Our log buffer of previous messages
		List < LogMsg > m_log_buffer;

		/// Our staging area for writing messages to disk:
		List< LogMsg > m_log_stage;

		/// Indicates whether we record our statistics in the global counter pool.
		bool m_record_stats;

		/// Indicates whether we are paused at the moment (happens when refreshing our config file).
		volatile bool m_paused;

		/// Indicates whether we have redirected stdout and stderr
		bool m_stdout_redirected;

		/// Inidicates whether we forward our logs to somewhere else - in addition to writing to our file.
		bool m_logForwarding;

		/// If log forwarding is on, this is the host to which we send logs
		string m_logForwardHost;

		/// If log forwarding is on, this is the port to which we send logs
		string m_logForwardPort;

		/// This is the message of logs that we build up while getting ready to forward logs.
		string m_forwardMsg;


	}
}

