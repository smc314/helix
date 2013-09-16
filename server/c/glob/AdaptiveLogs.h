/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ADAPTIVELOGS_H
#define ADAPTIVELOGS_H

#include <stdio.h>
#include <stdlib.h>

#include "Threadable.h"

#include <vector>
#include <utility>
using namespace std;

#include <xmlinc.h>
#include <MsgQueue.h>
#include <Log.h>
#include <twine.h>
#include <LogFile2.h>
using namespace SLib;

namespace Helix {
namespace Glob {


/**
  * This class is used to represent logging parameters that the user can
  * set via our config file.
  *
  * @author Steven M. Cherry
  */
class AdaptiveLogParm
{
	public:
		bool onoff;
		bool buffer_when_off;
		int  dump_when_hit;
};

/**
  * This class is responsible for implementing all of our adaptive logging
  * rules and functionality.  It is launched at initialization on a thread
  * and it is supposed to drain the SLib::Log queue, and decide what actually
  * will be written out to the disk.
  * <P>
  * We use the AdaptiveLogs tag in the config file for our setup
  * and we implement a number of things.
  * <P>
  * This class exists so that all of our logging control mechanisms may be
  * implemented in one place and none of the rest of our code set has to worry
  * about them.
  *
  * @author Steven M. Cherry
  */
class AdaptiveLogs : public Threadable
{
	private:
		/// copy constructor is private to prevent use
		AdaptiveLogs(const AdaptiveLogs& c) : 
			Threadable(c), m_log_queue(c.m_log_queue) {}

		/// assignmet operator is private to prevent use
		AdaptiveLogs& operator=(const AdaptiveLogs& c) { return *this;}

	public:

		/**
		  * Our standard constructor.
		  * @param m This is the pointer to the global TheMain object.
		  * @param lq This is the SLib::Log queue reference that we
		  *           will use.
		  */
		AdaptiveLogs(MsgQueue<LogMsg*>& lq);

		/// Standard destructor
		virtual ~AdaptiveLogs();

		/**
		  * We implement the Execute method.
		  */
		virtual void Execute(void);

		/** Allows the caller to access our External Log queue, which is used to
		 * write log messages from external applications into our own log file.
		 */
		static MsgQueue<LogMsg*>& GetExternalLogQueue();

		/** This method will tell us to re-read our configuration information from
		 * our global configuration document.  We will temporarily suspend writing
		 * to the log file while this is taking place.  Log messages will continue
		 * to be logged to the buffer just fine, so nothing will be lost.
		 */
		void RefreshConfig(void);

		/** This will return our log file interface.
		  */
		LogFile2& LogFile(void);

	private:
		/**
		  * This method drains up to 100 messages from the log queue.
		  * it is used by our destructor to help flush the log queue
		  * prior to us shutting down.
		  */
		void DrainLastLogs(void);

		/**
		  * This method is responsible for reading our configuration
		  * information from the config file document held by TheMain.
		  * We will populate the m_log_parms structure with it's
		  * information.
		  */
		void ReadConfig(void);
		
		/**
		  * This method is used when we can't find a log settings
		  * node in the config file.  This sets everything up with
		  * default values so that logging can continue.
		  */
		void DefaultSettings(void);

		/**
		  * This method handles the settings for one log channel.
		  * It will search the given xml node for the named log channel
		  * and use that to set the log information.  If the named
		  * channel is not found as an xml node, then the given defaults
		  * will be used to set the log info instead.
		  */
		void FindAndSetChannel(xmlNodePtr node, const char* channel,
			bool onoff_default, bool buffer_when_off_default,
			int dump_when_hit_default);

		/**
		  * This method is responsible for reading our m_log_parms
		  * structure and setting up the SLib::Log parameters.  If
		  * any of our logs are both onoff == false and 
		  * buffer_when_off == false, then we will turn the actual
		  * SLib::Log channel offf.  There's no need for it at that
		  * point.  Everything else that has either onoff == true
		  * or buffer_when_off == true will be turned on.
		  */
		void Setup(void);

		/** This method handles re-directing stdout and stderr to pipes
		 * so that we can then read from them and capture their contents
		 * to our logs.  This is not so much so that programmers can use
		 * printf instead of DEBUG, but for 3rdParty or Java code that we
		 * execute.  That way other code won't have to change to adapt
		 * our logging system.  They can just write to stdout and stderr
		 * as usual.
		 */
		void RedirectStdout(void);

		/**
		  * This method handles the decision of whether or not to
		  * physically write the log message to disk, just store it
		  * in our log buffer, or throw it away.  It takes ownership
		  * of the given LogMsg object and handles destruction or
		  * preservation of the memory as appropriate.
		  */
		void ProcessMessage(LogMsg* lm);

		/**
		 * This method handles writing external log messages to our
		 * log file.  We only check to ensure that the log message
		 * is sane before writing to the file.  We do no filtering
		 * or buffering of these messages.  They all get written
		 * directly to the log file.
		 */
		void ProcessExternalMessage(LogMsg* lm);

		/**
		  * This method is responsible for formatting and writing
		  * a single log message out to the disk.
		  */
		void WriteLogMsg(LogMsg* lm);

		/**
		  * This method adds a log message to the end of our buffer.
		  * If the buffer size gets beyond our max buffer size, then
		  * we will pop off the first message and delete it.
		  */
		void AddLogToBuffer(LogMsg* lm);

		/**
		  * This method writes out the last count messages in our 
		  * buffer to the log in the order that they are in the buffer.
		  */
		void BufferTail(int count);

		/**
		  * This method will delete everything that is in our log
		  * buffer.  This is typically used immediately after a
		  * BufferTail call, since the buffer information is now
		  * old and out of synch with what's on disk.
		  */
		void ClearBuffer(void);

		/**
		  * This initializes our log forwarding message.
		  */
		void InitForwardMsg();

		/**
		  * This adds a log message to our forwarding message.
		  */
		void AddForwardMsg(LogMsg* lm);

		/**
		  * This uses HttpClient to send our log messages to the forwarding target.
		  */
		void SendForwardMsg();

		/** This ensures that our staging area is cleaned out properly.
		  */
		void ClearStage();

		/// File name that we log to
		twine m_file_name;

		/// LogFile that we use.
		LogFile2* m_file;

		/// Largest message id in use:
		int m_max_id;

		/// Max size of the current log file:
		int m_max_file_size;

		/// Max size of our log buffer
		int m_max_buffer_size;

		/// SLib::Log queue that we drain
		MsgQueue<LogMsg*>& m_log_queue;

		/// Log parameters
		vector < AdaptiveLogParm > m_log_parms;

		/// Our log buffer of previous messages
		list < LogMsg* > m_log_buffer;

		/// Our staging area for writing messages to disk:
		vector< LogMsg* > m_log_stage;

		/// Indicates whether we record our statistics in the global counter pool.
		bool m_record_stats;

		/// Indicates whether we are paused at the moment (happens when refreshing our config file).
		bool m_paused;

		/// Indicates whether we have redirected stdout and stderr
		bool m_stdout_redirected;

		/// Inidicates whether we forward our logs to somewhere else - in addition to writing to our file.
		bool m_logForwarding;

		/// If log forwarding is on, this is the host to which we send logs
		twine m_logForwardHost;

		/// If log forwarding is on, this is the port to which we send logs
		twine m_logForwardPort;

		/// This is the message of logs that we build up while getting ready to forward logs.
		twine m_forwardMsg;

};

}} // End Namespace Helix::Glob

#endif // ADAPTIVELOGS_H Defined
