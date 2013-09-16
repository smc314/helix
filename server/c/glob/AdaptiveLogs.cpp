/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "AdaptiveLogs.h"
#include "TheMain.h"
using namespace Helix::Glob;

#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#	include <io.h>
#	include <sys/timeb.h>
#else
#	include <sys/time.h>
#	include <unistd.h>
#endif

// Use this to turn on/off printfs for entry to each method - this is our
// kludge answer to the age old question: how do you log the logger when you need to debug it?
// Ensure that RedirectStdout is commented out if you turn this on.
//#define LOGPRINT(a) printf(a)
#define LOGPRINT(a)


#include <xmlinc.h>
#include <AnException.h>
#include <Log.h>
#include <File.h>
#include <Tools.h>
#include <Thread.h>
#include <dptr.h>
#include <AutoXMLChar.h>
#include <XmlHelpers.h>
#include <EnEx.h>
#include <HttpClient.h>
using namespace SLib;

/** This queue is used for receiving logs from external sources.  No adaptive processing
 *  is done to them, as the senders should do that before forwarding the logs over the
 *  network.  This is usually populated by the SaveLogMsg Logic request, and whatever
 *  is written to this queue will be dumped into our log file directly.
 */
static MsgQueue<LogMsg*> external_logs;

static int AdaptiveLogs_Stdout_Pipe[2];
static int AdaptiveLogs_Stderr_Pipe[2];
void* AdaptiveLogs_Read_Stdout(void* v);
void* AdaptiveLogs_Read_Stderr(void* v);

AdaptiveLogs::AdaptiveLogs(MsgQueue<LogMsg*>& lq) : m_log_queue(lq)
{
	EnEx ee(FL, "AdaptiveLogs::AdaptiveLogs(MsgQueue<LogMsg*>& lq)");
	m_descr = "AdaptiveLogs Log Processor Thread";
	// Ensure that all SLib logging goes into the queue that
	// we are draining:
	Log::SetLazy(true);

	m_record_stats = false;
	m_paused = false;
	m_stdout_redirected = false;
	m_logForwarding = false;

	ReadConfig();
	Setup();
}

AdaptiveLogs::~AdaptiveLogs()
{
	EnEx ee(FL, "AdaptiveLogs::~AdaptiveLogs()");
	// Reset SLib::Log to non-lazy so messages don't go to the queue
	Log::SetLazy(false);

	// Drain any remaining logs (up to 100 messages)
	DrainLastLogs();

	// Close off our log file
	m_file->close();
	delete m_file;

	// Clear out our log parms config info:
	m_log_parms.clear();

	// that's it.
}

LogFile2& AdaptiveLogs::LogFile(void)
{
	if(m_file == NULL){
		throw AnException(0, FL, "Log file not available yet.");
	}
	return *m_file;
}

void AdaptiveLogs::Execute(void)
{
	EnEx ee(FL, "AdaptiveLogs::Execute()");
	LOGPRINT("AdaptiveLogs::Execute()\n");

	INFO(FL, "AdaptiveLogs Log Processor Thread starting");

	m_state = Threadable::Startup;

	try {
		// Start up our stdout and stderr drainers:
		Thread* stdoutDrain = new Thread();
		Thread* stderrDrain = new Thread();

		stdoutDrain->start( AdaptiveLogs_Read_Stdout, NULL );
		stderrDrain->start( AdaptiveLogs_Read_Stderr, NULL );

		unsigned int loopCount = 1;
		while(!m_shutdown) {
			while(!m_paused && !m_shutdown){
				// set our state
				m_state = Threadable::Running;

				LogMsg* lmi = m_log_queue.GetMsg();
				LogMsg* lme = external_logs.GetMsg();
				if(lmi != NULL || lme != NULL){
					if(lmi != NULL){
						ProcessMessage(lmi);
					} 
					if(lme != NULL){
						ProcessExternalMessage(lme);
					} 
				} else {
					try {
						m_file->flush();
					} catch( AnException& ){
						// catch and ignore any errors comming from the flush
					}
					m_state = Threadable::Sleeping;
					Tools::msleep(100); // 1/10th second sleep
					m_state = Threadable::Running;
				}

				if(loopCount % 100 == 0){
					m_record_stats = true; // record stats every 100 log messages.
				} else {
					m_record_stats = false;
				}
				loopCount ++;
			}
			if(m_paused){
				Tools::msleep(100); // 1/10th second sleep
			}
		}
		// once shutdown - tickle our drainers to stop working:
		printf(">STDOUT<>EOF<");
		fflush(stdout);
		fprintf(stderr, ">STDERR<>EOF<");
		fflush(stderr);
	} catch (AnException& e){
		Log::SetLazy(false);
		ERRORL(FL, "Caught exception during AdaptiveLogs::Execute()\n%s\n===\n%s", 
			e.Msg(), e.Stack());
		// once shutdown - tickle our drainers to stop working:
		printf(">STDOUT<>EOF<");
		fflush(stdout);
		fprintf(stderr, ">STDERR<>EOF<");
		fflush(stderr);
	} catch (std::exception& stde){
		Log::SetLazy(false);
		ERRORL(FL, "Caught std::exception during AdaptiveLogs::Execute()\n%s\n", stde.what());
		// once shutdown - tickle our drainers to stop working:
		printf(">STDOUT<>EOF<");
		fflush(stdout);
		fprintf(stderr, ">STDERR<>EOF<");
		fflush(stderr);
	} catch (...) {
		Log::SetLazy(false);
		ERRORL(FL,"Caught unknown exception AdaptiveLogs::Execute()");
		// once shutdown - tickle our drainers to stop working:
		printf(">STDOUT<>EOF<");
		fflush(stdout);
		fprintf(stderr, ">STDERR<>EOF<");
		fflush(stderr);
	}
}

void AdaptiveLogs::DrainLastLogs(void)
{
	EnEx ee(FL, "AdaptiveLogs::DrainLastLogs()");
	LOGPRINT("AdaptiveLogs::DrainLastLogs()\n");
	int count = 0;	
	try {
		while(count < 1000) { // only do up to 1000
			LogMsg* lm = m_log_queue.GetMsg();
			if(lm != NULL){
				ProcessMessage(lm);
				count++;
			} else {
				break; // nothing left in the queue
			}
		}
	} catch (AnException e){
		ERRORL(FL, "Caught exception during AdaptiveLogs::DrainLastLogs()\n"
			"%s\n", e.Msg());
	} catch (...) {
		ERRORL(FL,"Caught unknown exception AdaptiveLogs::DrainLastLogs()");
	}
}

void AdaptiveLogs::RefreshConfig(void)
{
	EnEx ee(FL, "AdaptiveLogs::RefreshConfig()");
	LOGPRINT("AdaptiveLogs::RefreshConfig()\n");

	// Shutdown the log file for a moment.
	WARN(FL, "AdaptiveLogs pausing logger to re-read configuration file.");
	m_paused = true; // pause processing of incomming messages.
	Tools::msleep(500); // Ensure that the pause is noticed.

	// Close the log file:
	m_file->close();
	delete m_file;
	m_file = NULL;
	WARN(FL, "AdaptiveLogs log file closed...Reading configuration.");

	// Re-read the config and re-setup our log file:
	m_log_parms.clear();
	ReadConfig();
	Setup();

	// Un-pause log message processing:
	m_paused = false;
	WARN(FL, "AdaptiveLogs configuration re-read, logging active again.");

}

void AdaptiveLogs::ReadConfig(void)
{
	EnEx ee(FL, "AdaptiveLogs::ReadConfig()");
	LOGPRINT("AdaptiveLogs::ReadConfig()\n");

	xmlNodePtr root;
	xmlNodePtr ad_log;
	AutoXMLChar tmp;

	root = xmlDocGetRootElement(TheMain::getInstance()->GetConfig());
	ad_log = XmlHelpers::FindChild(root, "AdaptiveLogs");
	if(ad_log == NULL){ // wasn't found
		DefaultSettings();
		return;
	}

	tmp = xmlGetProp(ad_log, (const xmlChar*)"filename");
	if(tmp() == NULL){
		m_file_name = "ihd.log";
	} else {
		m_file_name = tmp;
	}

	tmp = xmlGetProp(ad_log, (const xmlChar*)"buffer_size");
	if(tmp() == NULL){
		m_max_buffer_size = 1000;
	} else {
		m_max_buffer_size = atoi(tmp);
		if(m_max_buffer_size > 10000){  // ten thousand upper limit
			m_max_buffer_size = 10000;
		}
		if(m_max_buffer_size <= 0){
			m_max_buffer_size = 1000;
		}
	}

	tmp = xmlGetProp(ad_log, (const xmlChar*)"max_file_size");
	if(tmp() == NULL){
		m_max_file_size = 0; // unbounded
	} else {
		m_max_file_size = atoi(tmp);
		if(m_max_file_size > (100 * 1024000)){ // 100 Meg upper size
			m_max_file_size = 100 * 1024000;
		}
		if(m_max_file_size < 0){
			m_max_file_size = 52428800;  // 50 meg file chunks.
		}
	}

	// Find each log channel and provide defaults if not found
	FindAndSetChannel(ad_log, "Panic", true, true, 1000);
	FindAndSetChannel(ad_log, "Error", true, true, 100);
	FindAndSetChannel(ad_log, "Warn", true, true, 100);
	FindAndSetChannel(ad_log, "Info", true, true, 0);
	FindAndSetChannel(ad_log, "Debug", false, true, 0);
	FindAndSetChannel(ad_log, "Trace", false, false, 0);
	FindAndSetChannel(ad_log, "SqlTrace", false, false, 0);

	// Check for a log forwarding setup:
	xmlNodePtr forwarding = XmlHelpers::FindChild(ad_log, "LogForwarding");
	if(forwarding != NULL){
		m_logForwarding = XmlHelpers::getBoolAttr(forwarding, "onoff");
		m_logForwardHost.getAttribute(forwarding, "targethost");
		m_logForwardPort.getAttribute(forwarding, "targetport");
	}

}

void AdaptiveLogs::FindAndSetChannel(xmlNodePtr ad_log,
	const char* channel_name, 
	bool onoff,
	bool buffer_when_off, 
	int dump_when_hit)
{
	EnEx ee(FL, "AdaptiveLogs::FindAndSetChannel()");
	LOGPRINT("AdaptiveLogs::FindAndSetChannel()\n");

	xmlNodePtr log = NULL;
	AutoXMLChar tmp;
	AdaptiveLogParm alp;

	// Find the log channel
	log = XmlHelpers::FindChild(ad_log, channel_name);
	if(log == NULL){ // wasn't found
		alp.onoff = onoff;
		alp.buffer_when_off = buffer_when_off;
		alp.dump_when_hit = dump_when_hit;
		m_log_parms.push_back(alp);
		return;
	}

	tmp = xmlGetProp(log, (const xmlChar*)"onoff");
	if(tmp() == NULL){
		alp.onoff = onoff;
	} else if(strcmp(tmp, "ON") == 0){
		alp.onoff = true;
	} else {
		alp.onoff = false;
	}

	tmp = xmlGetProp(log, (const xmlChar*)"buffered_when_off");
	if(tmp() == NULL){
		alp.buffer_when_off = buffer_when_off;
	} else if(strcmp(tmp, "ON") == 0){
		alp.buffer_when_off = true;
	} else {
		alp.buffer_when_off = false;
	}

	tmp = xmlGetProp(log, (const xmlChar*)"dump_when_hit");
	if(tmp() == NULL){
		alp.dump_when_hit = dump_when_hit;
	} else {
		alp.dump_when_hit = atoi(tmp);
		if(alp.dump_when_hit > m_max_buffer_size){
			alp.dump_when_hit = m_max_buffer_size;
		}
		if(alp.dump_when_hit < 0){
			alp.dump_when_hit = 0;
		}
	}

	m_log_parms.push_back(alp);
}

void AdaptiveLogs::DefaultSettings(void)
{
	EnEx ee(FL, "AdaptiveLogs::DefaultSettings()");
	LOGPRINT("AdaptiveLogs::DefaultSettings()\n");

	// Default log settings:
	m_max_buffer_size = 1000;
	m_max_file_size = 0;
	m_file_name = "ihd.log";

	// Panic:
	AdaptiveLogParm panic;
	panic.onoff = true;
	panic.buffer_when_off = true;
	panic.dump_when_hit = 1000;
	m_log_parms.push_back(panic);

	// Error:
	AdaptiveLogParm error;
	error.onoff = true;
	error.buffer_when_off = true;
	error.dump_when_hit = 100;
	m_log_parms.push_back(error);

	// Warn:
	AdaptiveLogParm warn;
	warn.onoff = true;
	warn.buffer_when_off = true;
	warn.dump_when_hit = 100;
	m_log_parms.push_back(warn);

	// Info:
	AdaptiveLogParm info;
	info.onoff = true;
	info.buffer_when_off = true;
	info.dump_when_hit = 0;
	m_log_parms.push_back(info);

	// Debug:
	AdaptiveLogParm debug;
	debug.onoff = false;
	debug.buffer_when_off = true;
	debug.dump_when_hit = 0;
	m_log_parms.push_back(debug);

	// Trace:
	AdaptiveLogParm trace;
	trace.onoff = false;
	trace.buffer_when_off = false;
	trace.dump_when_hit = 0;
	m_log_parms.push_back(trace);

	// SqlTrace:
	AdaptiveLogParm sqlt;
	sqlt.onoff = false;
	sqlt.buffer_when_off = false;
	sqlt.dump_when_hit = 0;
	m_log_parms.push_back(sqlt);
}

void AdaptiveLogs::Setup(void)
{
	EnEx ee(FL, "AdaptiveLogs::Setup()");
	LOGPRINT("AdaptiveLogs::Setup()\n");

	if(m_log_parms.size() < 7){ // bad
		throw AnException(0, FL, "Log Parms size should always be "
			"at least 7.  It is (%d)", m_log_parms.size());
	}

	// Panic setup
	if(m_log_parms[0].onoff || m_log_parms[0].buffer_when_off){
		Log::SetPanic(true);
	} else {
		Log::SetPanic(false);
	}
	
	// Error setup
	if(m_log_parms[1].onoff || m_log_parms[1].buffer_when_off){
		Log::SetError(true);
	} else {
		Log::SetError(false);
	}
	
	// Warn setup
	if(m_log_parms[2].onoff || m_log_parms[2].buffer_when_off){
		Log::SetWarn(true);
	} else {
		Log::SetWarn(false);
	}
	
	// Info setup
	if(m_log_parms[3].onoff || m_log_parms[3].buffer_when_off){
		Log::SetInfo(true);
	} else {
		Log::SetInfo(false);
	}
	
	// Debug setup
	if(m_log_parms[4].onoff || m_log_parms[4].buffer_when_off){
		Log::SetDebug(true);
	} else {
		Log::SetDebug(false);
	}
	
	// Trace setup
	if(m_log_parms[5].onoff || m_log_parms[5].buffer_when_off){
		Log::SetTrace(true);
	} else {
		Log::SetTrace(false);
	}
	
	// SqlTrace setup
	if(m_log_parms[6].onoff || m_log_parms[6].buffer_when_off){
		Log::SetSqlTrace(true);
	} else {
		Log::SetSqlTrace(false);
	}

	// Other logs as added go here
	

	// Open up our log file:
	try {
		m_file = new LogFile2( m_file_name, m_max_file_size);
	} catch (AnException& e){
		// Something bad happened while trying to open our log file.
		m_file = NULL;
		m_shutdown = true;
		// Reset SLib::Log to non-lazy so messages don't go to the queue
		Log::SetLazy(false);

		PANIC(FL, "Exception raised opening log file: %s\n", e.Msg() );
		return; // do nothing else
	}

	m_max_id = m_file->getNewestMessageID();
	//RedirectStdout();
	
}

void AdaptiveLogs::RedirectStdout()
{
	EnEx ee("AdaptiveLogs::RedirectStdout()");
	LOGPRINT("AdaptiveLogs::RedirectStdout()\n");

	if(m_stdout_redirected){
		return; // don't do this more than once
	}

#ifdef _WIN32
	int stdout_fileno = _fileno(stdout);
	int stderr_fileno = _fileno(stderr);
#else
	int stdout_fileno = fileno(stdout);
	int stderr_fileno = fileno(stderr);
#endif
	int ret;

	// Redirect stdout to a pipe that we can read from:
#ifdef _WIN32
	if(_pipe(AdaptiveLogs_Stdout_Pipe, 4096, O_BINARY) == -1){
#else
	if(pipe(AdaptiveLogs_Stdout_Pipe) == -1){
#endif
		throw AnException(0, FL, "Error opening pipe for stdout.");
	}
#ifdef _WIN32
	ret = _dup2(AdaptiveLogs_Stdout_Pipe[1], stdout_fileno); // Redirect stdout to the pipe
#else
	ret = dup2(AdaptiveLogs_Stdout_Pipe[1], stdout_fileno); // Redirect stdout to the pipe
#endif
	if(ret < 0){
		throw AnException(0, FL, "Error redirecting stdout to the pipe.");
	}
#ifdef _WIN32
	_close(AdaptiveLogs_Stdout_Pipe[1]);
#else
	close(AdaptiveLogs_Stdout_Pipe[1]);
#endif
	// Anything send to stdout should now go down that pipe.

	// Redirect stderr to a pipe that we can read from:
#ifdef _WIN32
	if(_pipe(AdaptiveLogs_Stderr_Pipe, 4096, O_BINARY) == -1){
#else
	if(pipe(AdaptiveLogs_Stderr_Pipe) == -1){
#endif
		throw AnException(0, FL, "Error opening pipe for stderr.");
	}
#ifdef _WIN32
	ret = _dup2(AdaptiveLogs_Stderr_Pipe[1], stderr_fileno); // Redirect stderr to the pipe
#else
	ret = dup2(AdaptiveLogs_Stderr_Pipe[1], stderr_fileno); // Redirect stderr to the pipe
#endif
	if(ret < 0){
		throw AnException(0, FL, "Error redirecting stderr to the pipe.");
	}
#ifdef _WIN32
	_close(AdaptiveLogs_Stderr_Pipe[1]);
#else
	close(AdaptiveLogs_Stderr_Pipe[1]);
#endif
	// Anything send to stderr should now go down that pipe.

	m_stdout_redirected = true;
}

void* AdaptiveLogs_Read_Stdout(void* v)
{
	char buffer[4096];
	int bytes = 0;
	memset(buffer, 0, 4096);
	twine tmp;
#ifdef _WIN32
	while( (bytes = _read(AdaptiveLogs_Stdout_Pipe[0], buffer, 4095)) > 0){
#else
	while( (bytes = read(AdaptiveLogs_Stdout_Pipe[0], buffer, 4095)) > 0){
#endif
		tmp.set(buffer, bytes);
		vector<twine> lines = tmp.split("\n");
		for(int i = 0; i < (int)lines.size(); i++){
			DEBUG(FL, "[STDOUT] %s", lines[i]() );
		}
		if(strstr(buffer, ">STDOUT<>EOF<") != NULL){
			break; // we've been told to stop.
		}
		memset(buffer, 0, 4096);
	}
	return NULL;
}

void* AdaptiveLogs_Read_Stderr(void* v)
{
	char buffer[4096];
	int bytes = 0;
	memset(buffer, 0, 4096);
	twine tmp;
#ifdef _WIN32
	while( (bytes = _read(AdaptiveLogs_Stderr_Pipe[0], buffer, 4095)) > 0){
#else
	while( (bytes = read(AdaptiveLogs_Stderr_Pipe[0], buffer, 4095)) > 0){
#endif
		tmp.set(buffer, bytes);
		vector<twine> lines = tmp.split("\n");
		for(int i = 0; i < (int)lines.size(); i++){
			WARN(FL, "[STDERR] %s", lines[i]() );
		}
		if(strstr(buffer, ">STDERR<>EOF<") != NULL){
			break; // we've been told to stop.
		}
		memset(buffer, 0, 4096);
	}
	return NULL;
}

void AdaptiveLogs::ProcessMessage(LogMsg* lm)
{
	EnEx ee("AdaptiveLogs::ProcessMessage(LogMsg* lm)", m_record_stats);
	LOGPRINT("AdaptiveLogs::ProcessMessage(LogMsg* lm)\n");
	
	// Ensure the log message get's deleted if anything goes wrong.
	dptr < LogMsg > msg;
	msg = lm;	

	// find the parameters based on the channel
	if(msg->channel < 0 || msg->channel >= (int)m_log_parms.size()){
		// bad channel number on the log, throw it away.
		return;
	}

	AdaptiveLogParm& alp = m_log_parms[msg->channel];

	// If it's not on and not buffered, then throw it away
	if(alp.onoff == false && alp.buffer_when_off == false){
		return;
	}

	// if it's not on, but buffered, then add it to the buffer
	if(alp.onoff == false && alp.buffer_when_off == true){
		AddLogToBuffer(msg.release());
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

void AdaptiveLogs::ProcessExternalMessage(LogMsg* lm)
{
	EnEx ee("AdaptiveLogs::ProcessExternalMessage(LogMsg* lm)");
	LOGPRINT("AdaptiveLogs::ProcessExternalMessage(LogMsg* lm)\n");

	// Ensure the log message get's deleted if anything goes wrong.
	dptr < LogMsg > msg;
	msg = lm;	

	// Double-check the chanel.
	if(msg->channel < 0 || msg->channel >= (int)m_log_parms.size()){
		// bad channel number on the log, throw it away.
		return;
	}

	// Write the log message out.  All external messages are written.  No filtering.
	WriteLogMsg(msg);
}


void AdaptiveLogs::WriteLogMsg(LogMsg* lm)
{
	EnEx ee("AdaptiveLogs::WriteLogMsg(LogMsg* lm)");
	LOGPRINT("AdaptiveLogs::WriteLogMsg(LogMsg* lm)\n");

	try {
		m_log_stage.push_back( lm );
		m_file->writeMsg( &m_log_stage );
	} catch (AnException& e){
		printf("Caught exeption during write:\n%s\n%s\n", e.Msg(), e.Stack() );
		// If anything goes wrong writing this message to the log file, simply close
		// the log file and start a new one.
		try {
			m_file->createNewFile();			
			m_file->writeMsg( &m_log_stage );
		} catch(AnException& e2){
			printf("Badnews! 2nd exception caught trying to log:\n%s\n%s\n", e2.Msg(), e2.Stack() );
			try {
				m_file->close();
				delete m_file;
				m_file = new LogFile2( m_file_name, m_max_file_size);
			} catch (AnException& e3){
				printf("Panic! 3rd exception caught trying to log:\n%s\n%s\n", e3.Msg(), e3.Stack() );
				throw e3;
			}
		}
	}
	ClearStage();

	AddForwardMsg( lm );
}

void AdaptiveLogs::AddLogToBuffer(LogMsg* lm)
{
	EnEx ee("AdaptiveLogs::AddLogToBuffer(LogMsg* lm)");
	LOGPRINT("AdaptiveLogs::AddLogToBuffer(LogMsg* lm)\n");

	m_log_buffer.push_back(lm);
	if((int)m_log_buffer.size() > m_max_buffer_size){
		// delete the message on the front of the buffer.
		LogMsg* front = *(m_log_buffer.begin());
		delete front;
		m_log_buffer.pop_front();
	}
}

void AdaptiveLogs::BufferTail(int count)
{
	EnEx ee("AdaptiveLogs::BufferTail(int count)");
	LOGPRINT("AdaptiveLogs::BufferTail(int count)\n");
	int size, i;
	list < LogMsg* >::iterator it;

	ClearStage();
	size = (int)m_log_buffer.size();

	// if they want more than what we have, then just dump the whole thing
	if(count >= size){
		for(it = m_log_buffer.begin(); it != m_log_buffer.end(); it++){
			AddForwardMsg( *it );
			m_log_stage.push_back( *it );
		}
		return;
	}

	// if they want less than what we have, then only give 'em the last
	// ones that they asked for.

	// Set it to the starting point of what they want.
	it = m_log_buffer.begin();	
	for(i = 0; i < (size - count); i++) it++;

	// Write out all of the log messages asked for
	for(i = 0; i < count; i++){
		AddForwardMsg( *it );
		m_log_stage.push_back( *it );
		it++;
	}
}

void AdaptiveLogs::ClearBuffer(void)
{
	EnEx ee("AdaptiveLogs::ClearBuffer()");
	LOGPRINT("AdaptiveLogs::ClearBuffer()\n");
	
	while(!m_log_buffer.empty()){
		LogMsg* lm = *(m_log_buffer.begin());
		delete lm;
		m_log_buffer.pop_front();
	}
}

void AdaptiveLogs::ClearStage(void)
{
	EnEx ee("AdaptiveLogs::ClearStage()");
	LOGPRINT("AdaptiveLogs::ClearStage()\n");

	m_log_stage.clear();
}

MsgQueue<LogMsg*>& AdaptiveLogs::GetExternalLogQueue()
{
	return external_logs;
}

void AdaptiveLogs::InitForwardMsg()
{
	EnEx ee("AdaptiveLogs::InitForward()");
	LOGPRINT("AdaptiveLogs::InitForward()\n");
	if(!m_logForwarding){
		return;
	} else {
		m_forwardMsg = "<SaveLogMsg>";
	}
}

void AdaptiveLogs::AddForwardMsg(LogMsg* lm)
{
	EnEx ee("AdaptiveLogs::AddForwardMsg(LogMsg* lm)");
	LOGPRINT("AdaptiveLogs::AddForwardMsg(LogMsg* lm)\n");
	if(!m_logForwarding){
		return;
	}

	twine logxml = "<LogObj id=\"0\" file=\"%s\" line=\"%d\" tid=\"%ld\" timestamp_a=\"%d\""
		" timestamp_b=\"%d\" timestamp_c=\"\" channel=\"%d\" appName=\"%s\" machineName=\"%s\">"
		"<msg><![CDATA[%s]]></msg></LogObj>";

	twine xml; xml.format( logxml(),
		lm->file(), lm->line, lm->tid,
#ifdef _WIN32
		(int)lm->timestamp.time,
		(int)lm->timestamp.millitm,
#else
		(int)lm->timestamp.tv_sec,
		(int)lm->timestamp.tv_usec,
#endif
		lm->channel, lm->appName(), lm->machineName(), lm->msg.encode64()()
	);

	m_forwardMsg += xml;
}

void AdaptiveLogs::SendForwardMsg()
{
	EnEx ee("AdaptiveLogs::SendForwardMsg()");
	LOGPRINT("AdaptiveLogs::SendForwardMsg()\n");
	if(!m_logForwarding){
		return;
	}

	m_forwardMsg += "</SaveLogMsg>";

	twine url; url.format("http://%s:%s/logic/utils/SaveLogMsg", m_logForwardHost(), m_logForwardPort());
	HttpClient::PostPage( url(), m_forwardMsg(), m_forwardMsg.length() );

}
