/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include <xmlinc.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifndef _WIN32
#	include <dlfcn.h>   // for dlopen, etc.
#endif

#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/des.h>

#ifdef _WIN32
extern "C"
{
#include <openssl/applink.c>
}
#endif

#include "TheMain.h"
#include "AdaptiveLogs.h"
#include "Schedule.h"
#include "MsgProcScaler.h"
#include "IOAdapter.h"
#include "SessionSerializer.h"
#include "MySqlDbInit.h"
#include "SqlServerDbInit.h"
#include "ActionMap.h"
using namespace Helix::Glob;

#include <twine.h>
#include <Log.h>
#include <File.h>
#include <Lock.h>
#include <AutoXMLChar.h>
#include <EnEx.h>
#include <MemBuf.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

static TheMain* _globalTheMain = NULL;
static const char* _globalServerVersion = "314.314.314.314";
static const char* _globalServerBuiltOn = "BUILD_DATE";

TheMain::TheMain(char *p_config_file_name)
{
	EnEx ee(FL, "TheMain::TheMain()");

	if(_globalTheMain != NULL){
		throw AnException(0, FL, "TheMain has already been created.  Use getInstance() instead.");
	}

	m_keypair = NULL;

	// Turn all logs on for the moment.  Our AdaptiveLogs will adjust
	// this later when it starts up
	Log::SetPanic(true);
	Log::SetError(true);
	Log::SetWarn(true);
	Log::SetInfo(true);
	Log::SetDebug(true);
	Log::SetTrace(true);
	Log::SetSqlTrace(true);


	// Before launching any threads, or doing any 
	// xml stuff, init the XML parser
	DEBUG(FL, "Initializing XML Library.");
	xmlInitParser();

	// These are for xslt setup
	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	// This is xpath initiatlization
	xmlXPathInit();

	DEBUG(FL, "Initializing XML Library - Done.");

	if(p_config_file_name != NULL){
		m_config_file_name = p_config_file_name;
	} else {
		FindConfigFile();
	}

	try {
		LoadConfig();
	} catch (AnException& e){
		ERRORL(FL, "Exception caught loading config: %s", e.Msg());
	} catch (...){
		ERRORL(FL, "Unknown Exception caught loading config");
	}
	//Log::SetLazy(true);
	
	FindKeys();	

	m_transaction_mut = new Mutex();
	m_transaction_id = 0;

	m_is_shutdown_reconfig = false;
	m_shutdown_done = false;
	m_threads = NULL;

	// Tell everyone that we exist now.
	_globalTheMain = this;
}

TheMain::~TheMain()
{
	EnEx ee(FL, "TheMain::~TheMain()");

	if(m_config){
		xmlFreeDoc(m_config);
		m_config = NULL;
	}

}

TheMain* TheMain::getInstance(void)
{
	// Commented out to avoid the logs becomming too chatty
	//EnEx ee(FL, "TheMain::getInstance()");

	if(_globalTheMain == NULL){
		throw AnException(0, FL, "TheMain has not yet been initialized.");
	}
	return _globalTheMain;

}

ThreadList& TheMain::GetThreadList(void)
{
	if(m_threads == NULL){
		WARN(FL, "Thread list is NULL, creating on the fly - this may not be what you want.");
		m_threads = new ThreadList();
	}
	return *m_threads;
}

void TheMain::Execute(void)
{
	EnEx ee(FL, "TheMain::Execute()");

	// Keep looping while the shutdown is only for re-configuration
	// purposes.  If it's not, then allow the loop to end.
	do {

		InternalExecute();

		// If we are re-configuring, then release and re-read
		// our configuration file.
		if(m_is_shutdown_reconfig && m_config){
			xmlFreeDoc(m_config);
			m_config = NULL;
			LoadConfig();
		}

	} while(m_is_shutdown_reconfig);

}

void TheMain::InternalExecute(void)
{
	EnEx ee (FL, "TheMain::InternalExecute()");

	INFO(FL, "TheMain Starting execution.");

	try {
		m_shutdown = false;
		m_is_shutdown_reconfig = false;

		// create the thread list:
		INFO(FL, "Creating thread list");
		m_threads = new ThreadList();

		// Start draining and writing logs
		InitLogs();

		LoadLogics(); // Do this before InitStorageDB

		InitStorageDB();

		// Create and launch any IOAdapters that we have defined
		// so that we can listen for incomming messages.  The scheduler
		// is started here as well.
		LaunchIOAdapters();

		// Start up our message processing thread to handle passing
		// messages to ActionClass implementors.
		LaunchMsgProcScaler();

		INFO(FL, "TheMain::Execute everything started.  "
			"Waiting for shutdown notice.");

		int uptime = 0;
		int oneMinute = 0;
		// wait for someone to tell us to stop
		while(!m_shutdown){
			Tools::ssleep(1); // 1 second nap

			// tracks the number of seconds (roughly) 
			// that we've been up.
			uptime++; 
			oneMinute ++;
			if(oneMinute == 600){
				// Dump interesting things to to the log file every 10 minutes
				DumpStateToLogs();
				oneMinute = 0;
			}
		}

	} catch (AnException e){
		PANIC(FL, "Something broke: %s", e.Msg());
	} catch (...){
		PANIC(FL, "Something unknown broke.");
	}

	try {
		INFO(FL, "Shutting down all threads");
		DumpStateToLogs();

		ShutdownThreads();

		ShutdownDatabase();

		ShutdownLogger();
		// logging goes to stdout at this point.
		
		delete m_threads;
		m_threads = NULL;

		//xsltCleanupGlobals();
		xmlCleanupParser();

		m_shutdown_done = true;

	} catch (AnException e){
		PANIC(FL, "Something broke during shutdown: %s", e.Msg());
	} catch (...){
		PANIC(FL, "Something unknown broke during shutdown");
	}

}

void TheMain::Shutdown(void)
{
	EnEx ee(FL, "TheMain::Shutdown()");

	m_shutdown = true;
}

bool TheMain::isShutdown(void)
{
	if(m_shutdown ){
		return true;
	} else {
		return false;
	}
}

bool TheMain::isShutdownDone(void)
{
	return m_shutdown_done;
}

void TheMain::DumpStateToLogs(void)
{
	EnEx ee(FL, "TheMain::DumpStateToLogs(void)");

	try {
		// Dump the current thread list:
		INFO(FL, "Current Thread List:\n%s", GetThreadList().DescribeThreads()() );

		// Dump the current stats:
		INFO(FL, "Current Stats:\nFIXME");

		// Dump the current profiling information:
		twine output;
		EnEx::PrintGlobalHitMap(output);
		INFO(FL, "Current Global Hit Map:\n%s", output() );

	} catch (AnException& e){
		ERRORL(FL, "Error dumping state to logs: %s", e.Msg() );

	}

}

xmlDocPtr TheMain::GetConfig(void)
{
	EnEx ee(FL, "TheMain::GetConfig()");
	return m_config;
}

void TheMain::SaveConfig(void)
{
	EnEx ee(FL, "TheMain::SaveConfig()");

	xmlSaveFile(m_config_file_name(), m_config);
}


void TheMain::FindConfigFile(void)
{
	EnEx ee(FL, "TheMain::FindConfigFile()");

	// check for /etc/helix.xml
	int ret;
#ifdef _WIN32
	struct _stat st;
#else
	struct stat st;
#endif

#ifndef _WIN32
	// Only check this location on non-windows
	ret = stat("/etc/helix.xml", &st);
	if(ret == 0){
		// file was found.  good to go
		INFO(FL, "Setting config file name: /etc/helix.xml");
		m_config_file_name = "/etc/helix.xml";
		return;
	}
#endif

	// Last check ./helix.xml
#ifdef _WIN32
	ret = _stat("./helix.xml", &st);
#else
	ret = stat("./helix.xml", &st);
#endif
	if(ret == 0){
		// file was found.  good to go
		INFO(FL, "Setting config file name: ./helix.xml");
		m_config_file_name = "./helix.xml";
		return;
	}

	ERRORL(FL, "Helix Config file not found.  Generating Default");
	GenConfig();
}
		
void TheMain::LoadConfig(void)
{
	EnEx ee(FL, "TheMain::LoadConfig()");

	xmlNodePtr root;
	m_config = xmlParseFile(m_config_file_name());
	if(!m_config){
		ERRORL(FL, "Error parsing config file.");
		throw AnException(0, FL, "Error parsing config file (%s)",
			m_config_file_name());
	}
	
	root = xmlDocGetRootElement(m_config);
	if(root == NULL){
		ERRORL(FL, "Config File has no root element.");
		throw AnException(0, FL, "Config file (%s) has no root node", m_config_file_name());
	}

	if(strncmp( (const char*)(root->name), "HelixConfig", 13) != 0){
		ERRORL(FL, "Config File is not HelixConfig");
		xmlFreeDoc(m_config);
		m_config = NULL;
		throw AnException(0, FL, "Config file (%s) is not a HelixConfig document", m_config_file_name());
	}

	// Config is good.  Read our information
	m_system_name.getAttribute(root, "name");
	if(m_system_name.empty()){
		ERRORL(FL, "No System Name defined. Defaulting to SYS1");
		m_system_name = "SYS1";
	}

	CheckUpgrades();

}

void TheMain::CheckUpgrades()
{
	EnEx ee(FL, "TheMain::CheckUpgrades()");

	// Any type of upgrade changes in the config file will be addressed here:


}

void TheMain::GenConfig(void)
{
	EnEx ee(FL, "TheMain::GenConfig()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"HelixConfig", NULL);

	xmlNodePtr root = xmlDocGetRootElement(doc);
	xmlSetProp(root, (const xmlChar*)"name", (const xmlChar*)"SYS1");

	// Adaptive Logging
	xmlNodePtr al = xmlNewChild(root, NULL, (const xmlChar*)"AdaptiveLogs",
		NULL);
	xmlSetProp(al, (const xmlChar*)"filename", (const xmlChar*)"helix.log");
	xmlSetProp(al, (const xmlChar*)"buffer_size", (const xmlChar*)"1000");
	xmlSetProp(al, (const xmlChar*)"max_file_size", (const xmlChar*)"52428800");

	xmlNodePtr panic = xmlNewChild(al, NULL, (const xmlChar*)"Panic", NULL);
	xmlSetProp(panic, (const xmlChar*)"onoff", (const xmlChar*)"ON");
	xmlSetProp(panic, (const xmlChar*)"buffered_when_off", (const xmlChar*)"ON");
	xmlSetProp(panic, (const xmlChar*)"dump_when_hit", (const xmlChar*)"1000");

	xmlNodePtr error = xmlNewChild(al, NULL, (const xmlChar*)"Error", NULL);
	xmlSetProp(error, (const xmlChar*)"onoff", (const xmlChar*)"ON");
	xmlSetProp(error, (const xmlChar*)"buffered_when_off", (const xmlChar*)"ON");
	xmlSetProp(error, (const xmlChar*)"dump_when_hit", (const xmlChar*)"100");

	xmlNodePtr warn = xmlNewChild(al, NULL, (const xmlChar*)"Warn", NULL);
	xmlSetProp(warn, (const xmlChar*)"onoff", (const xmlChar*)"ON");
	xmlSetProp(warn, (const xmlChar*)"buffered_when_off", (const xmlChar*)"ON");
	xmlSetProp(warn, (const xmlChar*)"dump_when_hit", (const xmlChar*)"100");

	xmlNodePtr info = xmlNewChild(al, NULL, (const xmlChar*)"Info", NULL);
	xmlSetProp(info, (const xmlChar*)"onoff", (const xmlChar*)"Of");
	xmlSetProp(info, (const xmlChar*)"buffered_when_off", (const xmlChar*)"ON");
	xmlSetProp(info, (const xmlChar*)"dump_when_hit", (const xmlChar*)"0");

	xmlNodePtr debug = xmlNewChild(al, NULL, (const xmlChar*)"Debug", NULL);
	xmlSetProp(debug, (const xmlChar*)"onoff", (const xmlChar*)"Of");
	xmlSetProp(debug, (const xmlChar*)"buffered_when_off", (const xmlChar*)"ON");
	xmlSetProp(debug, (const xmlChar*)"dump_when_hit", (const xmlChar*)"0");

	xmlNodePtr trace = xmlNewChild(al, NULL, (const xmlChar*)"Trace", NULL);
	xmlSetProp(trace, (const xmlChar*)"onoff", (const xmlChar*)"Of");
	xmlSetProp(trace, (const xmlChar*)"buffered_when_off", (const xmlChar*)"Of");
	xmlSetProp(trace, (const xmlChar*)"dump_when_hit", (const xmlChar*)"0");

	xmlNodePtr sqlt = xmlNewChild(al, NULL, (const xmlChar*)"SqlTrace", NULL);
	xmlSetProp(sqlt, (const xmlChar*)"onoff", (const xmlChar*)"Of");
	xmlSetProp(sqlt, (const xmlChar*)"buffered_when_off", (const xmlChar*)"Of");
	xmlSetProp(sqlt, (const xmlChar*)"dump_when_hit", (const xmlChar*)"0");

	xmlNodePtr forw = xmlNewChild(al, NULL, (const xmlChar*)"LogForwarding", NULL);
	xmlSetProp(forw, (const xmlChar*)"onoff", (const xmlChar*)"Of");
	xmlSetProp(forw, (const xmlChar*)"targethost", (const xmlChar*)"vixw2k8dev");
	xmlSetProp(forw, (const xmlChar*)"targetport", (const xmlChar*)"8082");

	// IOAdapters node:
	xmlNodePtr ioadapters = xmlNewChild(root, NULL, (const xmlChar*)"IOAdapters", NULL);
	xmlNodePtr ioadapter = xmlNewChild(ioadapters, NULL, (const xmlChar*)"IOAdapter", NULL);
	xmlSetProp(ioadapter, (const xmlChar*)"name", (const xmlChar*)"Http");
	xmlSetProp(ioadapter, (const xmlChar*)"class", (const xmlChar*)"HttpIOAdapter");
	xmlSetProp(ioadapter, (const xmlChar*)"listen_port", (const xmlChar*)"8082");
	xmlSetProp(ioadapter, (const xmlChar*)"listen_ip", (const xmlChar*)"");
	xmlSetProp(ioadapter, (const xmlChar*)"secure", (const xmlChar*)"false");
	xmlSetProp(ioadapter, (const xmlChar*)"httpdomain", (const xmlChar*)"");
	xmlSetProp(ioadapter, (const xmlChar*)"sslcert", (const xmlChar*)"");
	xmlSetProp(ioadapter, (const xmlChar*)"compressionThreshold", (const xmlChar*)"512");
	xmlSetProp(ioadapter, (const xmlChar*)"threads", (const xmlChar*)"10");
	xmlSetProp(ioadapter, (const xmlChar*)"keepalive", (const xmlChar*)"no");

	// Logics node
	xmlNodePtr logics = xmlNewChild(root, NULL, (const xmlChar*)"Logics", NULL);
	xmlNodePtr logic = xmlNewChild(logics, NULL, (const xmlChar*)"Logic", NULL);
	xmlSetProp(logic, (const xmlChar*)"name", (const xmlChar*)"ExtraLogic");
	xmlSetProp(logic, (const xmlChar*)"library", (const xmlChar*)"sharedLibraryName.so");
	xmlSetProp(logic, (const xmlChar*)"active", (const xmlChar*)"false");
	
	// Storage node
	xmlNodePtr storage = xmlNewChild(root, NULL, (const xmlChar*)"Storage", NULL);
	xmlNodePtr db = xmlNewChild(storage, NULL, (const xmlChar*)"DB", NULL);
	xmlSetProp(storage, (const xmlChar*)"config", (const xmlChar*)"helixconfig");
	xmlSetProp(db, (const xmlChar*)"name", (const xmlChar*)"helixconfig");
	xmlSetProp(db, (const xmlChar*)"layout", (const xmlChar*)"helix.db.xml");
	xmlSetProp(db, (const xmlChar*)"type", (const xmlChar*)"SqlDB");

	// Security node
	xmlNodePtr security = xmlNewChild(root, NULL, (const xmlChar*)"Security", NULL);
	xmlNodePtr authentication = xmlNewChild(security, NULL, (const xmlChar*)"Authentication", NULL);
	xmlNodePtr authorization = xmlNewChild(security, NULL, (const xmlChar*)"Authorization", NULL);
	xmlNodePtr allowed = xmlNewChild(security, NULL, (const xmlChar*)"AllowedWOLogin", NULL);
	xmlNodePtr allow1 = xmlNewChild(allowed, NULL, (const xmlChar*)"Path", NULL);
	xmlNodePtr allow2 = xmlNewChild(allowed, NULL, (const xmlChar*)"Path", NULL);
	xmlSetProp(security, (const xmlChar*)"storedin", (const xmlChar*)"helixconfig");
	xmlSetProp(security, (const xmlChar*)"enabled", (const xmlChar*)"true");
	xmlSetProp(authentication, (const xmlChar*)"enabled", (const xmlChar*)"true");
	xmlSetProp(authentication, (const xmlChar*)"loginapp", (const xmlChar*)"/HelixLogin/index.html");
	xmlSetProp(authorization, (const xmlChar*)"enabled", (const xmlChar*)"true");
	xmlSetProp(allow1, (const xmlChar*)"startswith", (const xmlChar*)"/HelixLogin/");
	xmlSetProp(allow2, (const xmlChar*)"startswith", (const xmlChar*)"/favicon.ico");
	xmlSetProp(allow2, (const xmlChar*)"startswith", (const xmlChar*)"/admin");
	xmlSetProp(allow2, (const xmlChar*)"startswith", (const xmlChar*)"/dev");

	// Now save the file
	m_config_file_name = "./helix.xml";
	xmlSaveFile(m_config_file_name(), doc);

	xmlFreeDoc(doc);

}
	

void TheMain::InitLogs(void)
{
	EnEx ee(FL, "TheMain::InitLogs()");

	// Start our log handler on it's own thread if we are configured to do so:
	xmlNodePtr root = xmlDocGetRootElement(m_config);
	xmlNodePtr al = XmlHelpers::FindChild( root, "AdaptiveLogs" );
	if(XmlHelpers::getBoolAttr( al, "disabled" ) == false ){
		pair < Thread*, Threadable* >p;
		p.first = new Thread();
		m_logger = new AdaptiveLogs(SLib::Log::GetLogQueue()); // remember this for later.
		p.second = m_logger;
		p.first->start(Threadable::Start, p.second);
		m_our_threads.push_back(p);
	}

	printf("Adaptive logger started...\n");

	// Let people know what our channels look like
	PANIC(FL, "Panic Channel");
	ERRORL(FL, "Error Channel");
	WARN(FL, "Warn Channel");
	INFO(FL, "Info Channel");
	DEBUG(FL, "Debug Channel");
	TRACE(FL, "Trace Channel");
	SQLTRACE(FL, "SQLTrace Channel");

}

void TheMain::InitStorageDB(void)
{
	EnEx ee(FL, "TheMain::InitStorageDB()");

	xmlNodePtr root = xmlDocGetRootElement(m_config);
	xmlNodePtr storage = XmlHelpers::FindChild( root, "Storage" );
	if(storage == NULL){
		// Add in the default storage structure:
		storage = xmlNewChild(root, NULL, (const xmlChar*)"Storage", NULL);
		xmlNodePtr db = xmlNewChild(storage, NULL, (const xmlChar*)"DB", NULL);
		xmlSetProp(storage, (const xmlChar*)"config", (const xmlChar*)"helixconfig");
		xmlSetProp(db, (const xmlChar*)"name", (const xmlChar*)"helixconfig");
		xmlSetProp(db, (const xmlChar*)"layout", (const xmlChar*)"helix.db.xml");
		SaveConfig(); // write the update back out to disk
	}

	vector<xmlNodePtr> dbs = XmlHelpers::FindChildren( storage, "DB" );
	for(size_t i = 0; i < dbs.size(); i++){
		twine dbName( dbs[i], "name" );	
		twine dbType( dbs[i], "type" );	
		// Any type of exception initializing a database will (and should) cause us to
		// fail to start.  Don't try/catch here.
		if( dbType == "SqlDB" ){
			SqlDB* sqldb = new SqlDB( dbs[i] );
			m_databases[ dbName ] = sqldb;
		} else if ( dbType == "MySQL" ){
			m_connection_pools[ dbName ] = new ConnectionPool( dbName );
			MySqlDbInit dbinit( dbName );
			dbinit.VerifyInstallSchema();
		} else if ( dbType == "SqlServer" ){
			m_connection_pools[ dbName ] = new ConnectionPool( dbName );
			SqlServerDbInit dbinit( dbName );
			dbinit.VerifyInstallSchema();
		}
	}

	// After we've initialized our storage, ensure that our actions have been
	// inserted into the database.
	ActionMap::getInstance().SaveToConfigDB();

}

SqlDB& TheMain::GetSqlDB( const twine& whichOne )
{
	EnEx ee(FL, "TheMain::GetSqlDB(const twine& whichOne)");

	if(whichOne.length() == 0){
		// pick up "helixconfig"
		twine which = "helixconfig";
		if(m_databases.count( which ) != 0){
			return *(m_databases[ which ]);
		}
	}
	if(m_databases.count( whichOne ) != 0){
		return *(m_databases[ whichOne ]);
	}

	throw AnException(0, FL, "Unknown local database requested: (%s)", whichOne() );
}

SqlDB& TheMain::GetConfigDB( void )
{
	EnEx ee(FL, "TheMain::GetConfigDB()");

	xmlNodePtr root = xmlDocGetRootElement(m_config);
	xmlNodePtr storage = XmlHelpers::FindChild( root, "Storage" );
	twine config;
	config.getAttribute(storage, "config");

	return GetSqlDB( config );
}

BlockingQueue<IOConn*>& TheMain::getIOQueue(void)
{
	return m_io_queue;
}

void TheMain::LoadLogics(void)
{
	EnEx ee(FL, "TheMain::LoadLogics()");

	xmlNodePtr logics;

	// Walk our Logics children in the config file
	logics = XmlHelpers::FindChild(xmlDocGetRootElement(m_config), "Logics");
	if(logics == NULL){
		INFO(FL, "Logics Node not listed in config file.");
		return;
	}

	vector<xmlNodePtr> nodes = XmlHelpers::FindChildren( logics, "Logic" );
	for(size_t i = 0; i < nodes.size(); i++){
		xmlNodePtr node = nodes[i];
		twine logicName;
		twine logicLibrary;
		if(XmlHelpers::getBoolAttr(node, "active")){
			logicName.getAttribute(node, "name");
			if(logicName.empty()){
				ERRORL(FL, "Logic node has missing or empty name attribute.");
				continue;
			}
			logicLibrary.getAttribute(node, "library");
			if(logicLibrary.empty()){
				ERRORL(FL, "Logic[%s] library attribute is missing or empty.", logicName() );
				continue;
			}
			try {
				LoadDLL( logicLibrary );
			} catch(AnException& e){
				ERRORL(FL, "Error loading Logic[%s] library[%s]: %s", logicName(), logicLibrary(), e.Msg() );
				continue;
			}
		}
	}	
}

#ifdef _WIN32
HINSTANCE TheMain::LoadDLL(const twine& dll_name)
#else
void* TheMain::LoadDLL(const twine& dll_name)
#endif
{
	EnEx ee(FL, "TheMain::LoadDLL(const twine& dll_name)");

	// First look the name up to see if we've already loaded it
	if(m_loaded_dlls.count(dll_name) > 0){
		return m_loaded_dlls[ dll_name ]; // found it
	}

	// Didn't find it - go ahead and load it.
	DEBUG(FL, "Trying to load library (%s)", dll_name() );
#ifdef _WIN32
	HINSTANCE dllHandle = LoadLibrary(dll_name());
#else
	void* dllHandle = dlopen(dll_name(), RTLD_LAZY | RTLD_GLOBAL);
#endif

	if(dllHandle == NULL){
		throw AnException(0, FL, "Error loading library(%s)", dll_name() );
	}

	// Record it before returning
	m_loaded_dlls[ dll_name ] = dllHandle;

	return dllHandle;
}

void TheMain::LaunchIOAdapters(void)
{
	EnEx ee(FL, "TheMain::LaunchIOAdapters()");

	xmlNodePtr root;
	xmlNodePtr node;
	xmlNodePtr proc;

	// Next launch our scheduler.  That should always be running as well.
	pair < Thread*, Threadable* > p3;
	p3.first = new Thread();
	p3.second = &(Schedule::getInstance());
	p3.first->start(Threadable::Start, p3.second);
	m_our_threads.push_back(p3);

	// Then walk the config file and launch everything else	
	
	root = xmlDocGetRootElement(m_config);
	proc = XmlHelpers::FindChild(root, "IOAdapters");
	if(proc == NULL){
		WARN(FL, "IOAdapters Node not listed in config file.");
		return;
	}
	
	for(node = proc->xmlChildrenNode; node != NULL; node = node->next){
		if(strncmp((const char*)node->name, "IOAdapter", 9) == 0){
			LoadIOAdapter(node);
		}
	}	
}

void TheMain::LoadIOAdapter(xmlNodePtr node)
{
	EnEx ee(FL, "TheMain::LoadIOAdapter()");

	twine name;
	twine className;

	name.getAttribute(node, "name");
	if(name.empty()){
		ERRORL(FL, "IOAdapter Must have a name attribute");
		return;
	} 

	className.getAttribute(node, "class");
	if(className.empty()){
		ERRORL(FL, "IOAdapter Must have a class attribute");
		return;
	} 

	INFO(FL, "Launching IOAdapter (%s) from class (%s)", name(), className());

	try {
		pair < Thread*, Threadable* > p;
		p.first = new Thread();
		p.second = IOAdapterFactory::createInstance(className);
		((IOAdapter*)p.second)->Init( node );

		p.first->start(Threadable::Start, p.second);

		m_our_threads.push_back(p);
	} catch (AnException& e){
		ERRORL(FL, "Error loading IOAdapter: %s", e.Msg() );
	}

}

void TheMain::LaunchMsgProcScaler(void)
{
	EnEx ee(FL, "TheMain::LaunchMsgProcScaler(void)");

	pair< Thread*, Threadable* > p;
	p.first = new Thread();
	p.second = new MsgProcScaler("Central Message Processor");
	p.first->start(Threadable::Start, p.second);
	m_our_threads.push_back(p);

	pair< Thread*, Threadable* > p2;
	p2.first = new Thread();
	p2.second = new SessionSerializer();
	p2.first->start(Threadable::Start, p2.second);
	m_our_threads.push_back(p2);


}

void TheMain::ShutdownDatabase(void)
{
	EnEx ee(FL, "TheMain::ShutdownDatabase()");

	INFO(FL, "Shutting down odbc database connection pools");
	map<twine, ConnectionPool*>::iterator it;
	for(it = m_connection_pools.begin(); it != m_connection_pools.end(); it++){
		delete it->second;
	}

	INFO(FL, "Shutting down local SqlDB databases");
	map<twine, SqlDB*>::iterator it2;
	for(it2 = m_databases.begin(); it2 != m_databases.end(); it2++){
		delete it2->second;
	}
}

void TheMain::ShutdownThreads(void)
{
	EnEx ee(FL, "TheMain::ShutdownThreads()");

	int i;

	// The logger is always thread 0.  Shut it down last

	// for every thread that we have, call it's shutdown method
	INFO(FL, "Shutting down threads");
	for(i = 1; i < (int)m_our_threads.size(); i++){
		m_our_threads[i].second->Shutdown();
	}	

	// for every thread that we have, join on the thread to ensure
	// that it is done.
	INFO(FL, "Joining threads");
	for(i = 1; i < (int)m_our_threads.size(); i++){
		//m_our_threads[i].first->join();
		m_our_threads[i].first->cancel();
	}	

	// for every thread that we have, delete the thread and
	// the threadable object.
	INFO(FL, "Deleteing threads");
	//for(i = 1; i < (int)m_our_threads.size(); i++){
		//delete m_our_threads[i].first;
		//delete m_our_threads[i].second;
	//}	

	INFO(FL, "Thread Shutdown complete");

}

void TheMain::ShutdownLogger(void)
{
	EnEx ee(FL, "TheMain::ShutdownLogger()");

	// The Logger is always thread 0.
	PANIC(FL, "Shutting down Logger.  TheMain exiting.");

	m_our_threads[0].second->Shutdown();
	Tools::ssleep( 1 ); // sleep for 1 second to allow logs to shutdown.
	m_our_threads[0].first->cancel();
	//delete m_our_threads[0].first;
	//delete m_our_threads[0].second;

	// any logging at this point will go to stdout.
	// which means it will most likely be lost.

	// clear up the threads vector
	m_our_threads.clear();

}

twine& TheMain::SystemName(void)
{
	EnEx ee(FL, "TheMain::SystemName()");
	return m_system_name;
}

const char* TheMain::ServerVersion(void)
{
	EnEx ee(FL, "TheMain::ServerVersion()");

	return _globalServerVersion;
}

const char* TheMain::ServerBuiltOn(void)
{
	EnEx ee(FL, "TheMain::ServerBuiltOn()");

	return _globalServerBuiltOn;
}

void TheMain::ReReadConfig(void)
{
	EnEx ee(FL, "TheMain::ReReadConfig()");

/*
	// for every thread that we have, tell them to re-read their config
	INFO(FL, "ReReading Configuration Info");

	for(int i = 1; i < (int)m_our_threads.size(); i++){
		m_our_threads[i].second->ReReadConfig();
	}	
*/

	INFO(FL, "Shutting down for re-configuration cycle");
	m_is_shutdown_reconfig = true;
	m_shutdown = true;

}

twine& TheMain::GetConfigFileName(void)
{
	EnEx ee(FL, "TheMain::GetConfigFileName()");
	return m_config_file_name;
}

Connection& TheMain::GetOdbcConnection()
{
	EnEx ee(FL, "TheMain::GetOdbcConnection()");

	xmlNodePtr root = xmlDocGetRootElement(m_config);
	xmlNodePtr storage = XmlHelpers::FindChild( root, "Storage" );
	twine defaultDB;
	defaultDB.getAttribute(storage, "default");
	if(defaultDB.length() == 0){
		throw AnException(0, FL, "Storage node has no 'default' database indicated.");
	}

	return GetOdbcConnection( defaultDB );
}

Connection& TheMain::GetOdbcConnection(const twine& whichOne)
{
	EnEx ee(FL, "TheMain::GetOdbcConnection(const twine& whichOne)");

	if(m_connection_pools.count( whichOne ) == 0){
		throw AnException(0, FL, "Unknown Database: %s", whichOne() );
	}
	ConnectionPool* cp = m_connection_pools[ whichOne ];
	return cp->getConnection();
}

void TheMain::RefreshAdaptiveLogs(void)
{
	EnEx ee(FL, "TheMain::RefreshAdaptiveLogs()");

	m_logger->RefreshConfig();
}

AdaptiveLogs& TheMain::GetAdaptiveLogs(void)
{
	if(m_logger == NULL){
		throw AnException(0, FL, "Logger not initialized.");
	}
	return *m_logger;
}

void TheMain::FindKeys(void)
{
	EnEx ee(FL, "TheMain::FindKeys()");

	CRYPTO_malloc_init();
	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	SSLeay_add_ssl_algorithms();

	if(File::Exists("./Helix.rsa_pub")){
		// Our keys exist.  Load them.
		ReadKeys();
	} else {
		// Our Keys don't exist, generate them
		CreateKeys();
	}
}

void TheMain::CreateKeys(void)
{
	EnEx ee(FL, "TheMain::CreateKeys()");

	m_keypair = RSA_generate_key(2048, 17, NULL, NULL);
	if(m_keypair == NULL){
		WARN(FL, "Generating RSA key pair failed.");
		return;
	}

	BIO* fp = BIO_new_file("./Helix.rsa", "wb" );
	if(fp == NULL){
		WARN(FL, "Saving RSA key pair failed.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		return;
	}
	int ret = 0;
	ret = PEM_write_bio_RSAPrivateKey(fp, m_keypair, NULL, NULL, 0, NULL, NULL);
	if(!ret){
		WARN(FL, "Error writing RSA private key.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		BIO_free( fp );
		return;
	}
	BIO_free(fp);

	fp = BIO_new_file("./Helix.rsa_pub", "wb");
	if(fp == NULL){
		WARN(FL, "Saving RSA key pair failed.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		return;
	}
	ret = PEM_write_bio_RSAPublicKey(fp, m_keypair);
	if(!ret){
		WARN(FL, "Error writing RSA public key.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		BIO_free( fp );
		return;
	}
	BIO_free(fp);

	DEBUG(FL, "RSA public/private keypair generated and saved as Helix.rsa_pub, Helix.rsa");
}

void TheMain::ReadKeys(void)
{
	EnEx ee(FL, "TheMain::ReadKeys()");

	BIO* fp = BIO_new_file("./Helix.rsa", "rb" );
	if(fp == NULL){
		WARN(FL, "Reading RSA private key failed - error opening file.");
		return;
	}
	
	m_keypair = PEM_read_bio_RSAPrivateKey(fp, &m_keypair, NULL, NULL);
	if(m_keypair == NULL){
		WARN(FL, "Error reading RSA private key.");
		BIO_free(fp);
		return;
	}
	BIO_free(fp);

	fp = BIO_new_file("./Helix.rsa_pub", "rb");
	if(fp == NULL){
		WARN(FL, "Reading RSA public key failed - error opening file.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		return;
	}

	m_keypair = PEM_read_bio_RSAPublicKey(fp, &m_keypair, NULL, NULL);
	if(m_keypair == NULL){
		WARN(FL, "Error reading RSA public key.");
		BIO_free(fp);
		return;
	}
	BIO_free(fp);

	DEBUG(FL, "RSA public/private keypair read from Helix.rsa_pub, Helix.rsa");
}

RSA* TheMain::GetKeypair(void)
{
	EnEx ee(FL, "TheMain::GetKeypair()");

	if(m_keypair == NULL){
		FindKeys();
	}
	return m_keypair;
}

void TheMain::TestEncrypt(RSA* keypair)
{
	EnEx ee(FL, "TheMain::TestEncrypt()");

	// Serialize our config file and then encrypt it and output the results to
	// the log.
	MemBuf configContents = XmlHelpers::docToStringPretty( m_config );
	sptr<xmlDoc, xmlFreeDoc> encryptedContents = configContents.Encrypt( keypair );

	DEBUG(FL, "Encrypted config file contents:\n%s", 
		XmlHelpers::docToStringPretty( encryptedContents )() );

	MemBuf decryptedContents;
	decryptedContents.Decrypt( encryptedContents, keypair );

	DEBUG(FL, "Decrypted config file contents:\n%s", decryptedContents.data() );

}































