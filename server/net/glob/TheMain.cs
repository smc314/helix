/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using System.Reflection;
using System.Xml;

namespace Helix.Glob
{
	public class TheMain
	{
		public static TheMain _globalTheMain = null;
		public static String _globalServerVersion = "314.314.314.314";
		public static String _globalServerBuiltOn = "BUILD_DATE";

		// The name of our system
		protected string m_system_name;

		// Every thread started directly or indirectly by our system is tracked here.
		protected ThreadList m_threads = null;

		// Boolean to track whether we are shutting down for re-configuration
		protected bool m_is_shutdown_reconfig = false;

		// Boolean to track whether we are shutting down
		protected bool m_shutdown = false;

		// Boolean to track whether shutdown has finished.
		protected bool m_shutdown_done = false;

		// Our XML configuration information
		protected XmlDocument m_config = null; 

		// The file name where our configuration is stored
		protected string m_config_file_name = null;

		// Our list of threads that we launch directly
		protected List< KeyValuePair<Thread, Threadable> > m_our_threads = null;

		// Our pointer to the AdaptiveLogs threadable:
		protected AdaptiveLogs m_logger = null;

		// Our list of SqlDB's that we can work with:
		protected Dictionary<string, SqlDB> m_databases = null;

		// Our single odbc connection - FIXME
		protected OdbcObj m_odbc_conn = null;

		static void Main(string[] args)
		{
			Console.WriteLine ("Hello World from Helix.Glob.TheMain!");
			TheMain main = new TheMain ();
			main.Execute ();
		}

		public TheMain ()
		{
			using (EnEx ee = new EnEx ("TheMain::TheMain()")) {

				// Turn on all logs for the moment.  Our AdaptiveLogs will adjust this later when it starts up.
				Log.SetPanic (true);
				Log.SetError (true);
				Log.SetWarn (true);
				Log.SetInfo (true);
				Log.SetDebug (true);
				Log.SetTrace (true);
				Log.SetSqlTrace (true);

				// Find and load our configuration
				FindConfigFile ();
				LoadConfig ();

				// Tell everyone that we exist now
				_globalTheMain = this;
			} // End EnEx using
		} // End TheMain

		public static TheMain GetInstance() 
		{
			if (_globalTheMain == null) {
				throw new Exception ("TheMain has not yet been initialized.");
			}
			return _globalTheMain;
		}

		public ThreadList GetThreadList()
		{
			if (m_threads == null) {
				Log.Warn ("Thread list is NULL, creating on the fly - this may not be what you want.");
				m_threads = new ThreadList ();
			}
			return m_threads;
		}

		public void Execute()
		{
			using (EnEx ee = new EnEx ("TheMain::Execute()")) {

				// Keep looping while the shutdown is only for re-configuration
				// purposes.  If it's not, then allow the loop to end.
				do {

					InternalExecute ();

					// If we are re-configuring, then release and re-load
					// our configuration file.
					if (m_is_shutdown_reconfig && (m_config != null)) {
						m_config = null;
						LoadConfig ();
					}

				} while(m_is_shutdown_reconfig);

			} // End EnEx using
		} // End Execute

		public void InternalExecute()
		{
			using (EnEx ee = new EnEx ("TheMain::InternalExecute()")) {
				Log.Info ("TheMain Starting execution");
				try {
					m_shutdown = false;
					m_is_shutdown_reconfig = false;

					Log.Info("Creating thread list");
					m_threads = new ThreadList();
					m_our_threads = new List<KeyValuePair<Thread, Threadable>>();

					// Start draining and writing logs
					InitLogs();

					InitStorageDB();

					// Create and launch any IOAdapters that we have defined
					// so that we can listen for incomming messages.  The scheduler
					// is started here as well.
					LaunchIOAdapters();

					// Start up our message processing thread to handle passing
					// messages to ActionClass implementors.
					LaunchMsgProcScaler();

					Log.Info("TheMain::Execute everything started.  Waiting for shutdown notice.");

					int uptime = 0;
					int oneMinute = 0;
					// Wait for someone to tell us to stop
					while(!m_shutdown){
						System.Threading.Thread.Sleep(1000); // 1 second nap

						// tracks the number of seconds (roughly)
						// that we've been up.
						uptime++;
						oneMinute++;
						if(oneMinute == 600){
							// Dump interesting things to the log file every 10 minutes
							DumpStateToLogs();
							oneMinute = 0;
						}
					}

				} catch (Exception e){
					Log.Panic ("Something broke: {0}", e.Message);
				}

				try {
					Log.Info("Shutting down all threads");
					DumpStateToLogs();

					ShutdownThreads();

					ShutdownLogger();
					// logging goes to stdout at this point.

					m_threads = null;

					m_shutdown_done = true;

				} catch (Exception e){
					Log.Panic("Something broke during shutdown: {0}", e.Message);
				}

			} // End EnEx using
		} // End InternalExecute


		public void Shutdown()
		{
			using(EnEx ee = new EnEx("TheMain::Shutdown()") ){
				m_shutdown = true;
			}
		}

		public bool isShutdown()
		{
			if(m_shutdown ){
				return true;
			} else {
				return false;
			}
		}

		public bool isShutdownDone()
		{
			return m_shutdown_done;
		}

		public void DumpStateToLogs()
		{
			using(EnEx ee = new EnEx("TheMain::DumpStateToLogs(void)") ){

				try {
					// Dump the current thread list:
					Log.Info("Current Thread List:\n%s", GetThreadList().DescribeThreads()() );

					// Dump the current stats:
					Log.Info("Current Stats:\nFIXME");

					// Dump the current profiling information:
					string output;
					//EnEx::PrintGlobalHitMap(output);
					Log.Info("Current Global Hit Map:\n{0}", output );

				} catch (Exception e){
					Log.Error("Error dumping state to logs: {0}", e.Message );
				}
			}
		}

		public XmlDocument GetConfig()
		{
			return m_config;
		}

		public void SaveConfig()
		{
			using(EnEx ee = new EnEx("TheMain::SaveConfig()")){
				m_config.Save(m_config_file_name);
			}
		}


		public void FindConfigFile()
		{
			using(EnEx ee = new EnEx("TheMain::FindConfigFile()")){

				if (File.Exists ("./helix.xml")) {
					// file was found.  good to go
					Log.Info ("Setting config file name: ./helix.xml");
					m_config_file_name = "./helix.xml";
					return;
				}

				Log.Error("Helix Config file not found.  Generating Default");
				GenConfig();
			}
		}
		
		public void LoadConfig()
		{
			using(EnEx ee = new EnEx("TheMain::LoadConfig()") ){
				m_config = new XmlDocument ();
				m_config.Load (m_config_file_name);

				XmlNode root = m_config.DocumentElement;
				if(root == null){
					Log.Error("Config File has no root element.");
					throw new Exception(String.Format("Config file {0} has no root node", m_config_file_name));
				}

				if(root.Name != "HelixConfig"){
					Log.Error("Config File is not HelixConfig");
					m_config = null;
					throw new Exception(String.Format("Config file {0} is not a HelixConfig document", m_config_file_name));
				}

				// Config is good.  Read our information
				m_system_name = ((XmlElement)root).GetAttribute("name");
				if(String.IsNullOrEmpty(m_system_name)){
					Log.Warn("No System Name defined. Defaulting to SYS1");
					m_system_name = "SYS1";
				}

				CheckUpgrades();
			}
		}

		public void CheckUpgrades()
		{
			using(EnEx ee = new EnEx("TheMain::CheckUpgrades()")){

				// Any type of upgrade changes in the config file will be addressed here:


			}
		}

		public void GenConfig()
		{
			using(EnEx ee = new EnEx("TheMain::GenConfig()")){

				// Init the config document
				XmlDocument doc = new XmlDocument ();
				doc.AppendChild (doc.CreateElement ("HelixConfig"));
				XmlElement root = doc.DocumentElement;
				root.SetAttribute("name", "SYS1");

				// Adaptive Logging
				XmlElement al = doc.CreateElement("AdaptiveLogs");
				root.AppendChild(al);
				al.SetAttribute("filename", "helix.log");
				al.SetAttribute("buffer_size", "1000");
				al.SetAttribute("max_file_size", "52428800");

				// Panic channel
				XmlElement panic = doc.CreateElement("Panic");
				al.AppendChild(panic);
				panic.SetAttribute("onoff", "ON");
				panic.SetAttribute("buffered_when_off", "ON");
				panic.SetAttribute("dump_when_hit", "1000");

				// Error channel
				XmlElement error = doc.CreateElement("Error");
				al.AppendChild(error);
				error.SetAttribute("onoff", "ON");
				error.SetAttribute("buffered_when_off", "ON");
				error.SetAttribute("dump_when_hit", "500");

				// Warn channel
				XmlElement warn = doc.CreateElement("Warn");
				al.AppendChild(warn);
				warn.SetAttribute("onoff", "ON");
				warn.SetAttribute("buffered_when_off", "ON");
				warn.SetAttribute("dump_when_hit", "100");

				// Info channel
				XmlElement info = doc.CreateElement("Info");
				al.AppendChild(info);
				info.SetAttribute("onoff", "Of");
				info.SetAttribute("buffered_when_off", "ON");
				info.SetAttribute("dump_when_hit", "10");

				// Debug channel
				XmlElement debug = doc.CreateElement("Debug");
				al.AppendChild(debug);
				debug.SetAttribute("onoff", "Of");
				debug.SetAttribute("buffered_when_off", "ON");
				debug.SetAttribute("dump_when_hit", "5");

				// Trace channel
				XmlElement trace = doc.CreateElement("Trace");
				al.AppendChild(trace);
				trace.SetAttribute("onoff", "Of");
				trace.SetAttribute("buffered_when_off", "Of");
				trace.SetAttribute("dump_when_hit", "0");

				// SqlTrace channel
				XmlElement sqltrace = doc.CreateElement("SqlTrace");
				al.AppendChild(sqltrace);
				sqltrace.SetAttribute("onoff", "Of");
				sqltrace.SetAttribute("buffered_when_off", "ON");
				sqltrace.SetAttribute("dump_when_hit", "0");

				// LogForwarding setup
				XmlElement logforwarding = doc.CreateElement("LogForwarding");
				al.AppendChild(logforwarding);
				logforwarding.SetAttribute("onoff", "Of");
				logforwarding.SetAttribute("targethost", "");
				logforwarding.SetAttribute("targetport", "");

				// IOAdapters node
				XmlElement ioadapters = doc.CreateElement("IOAdapters");
				root.AppendChild(ioadapters);
				XmlElement ioadapter = doc.CreateElement("IOAdapter");
				ioadapters.AppendChild(ioadapter);

				ioadapter.SetAttribute("name", "Http");
				ioadapter.SetAttribute("class", "HttpIOAdapter");
				ioadapter.SetAttribute("listen_port", "8082");
				ioadapter.SetAttribute("listen_ip", "");
				ioadapter.SetAttribute("secure", "false");
				ioadapter.SetAttribute("httpdomain", "");
				ioadapter.SetAttribute("sslcert", "");
				ioadapter.SetAttribute("compressionThreshold", "512");
				ioadapter.SetAttribute("threads", "10");
				ioadapter.SetAttribute("keepalive", "no");

				// Logics node
				XmlElement logics = doc.CreateElement("Logics");
				root.AppendChild (logics);
				XmlElement logic = doc.CreateElement("Logic");
				logics.AppendChild(logic);

				logic.SetAttribute("actionmap", "utils.actions.xml");
				logic.SetAttribute("class", "Utils");
				logic.SetAttribute("setup", "Utils");
				logic.SetAttribute("name", "Utils");

				// Storage node
				XmlElement storage = doc.CreateElement("Storage");
				root.AppendChild(storage);
				XmlElement db = doc.CreateElement("DB");
				storage.AppendChild(db);

				db.SetAttribute("name", "helixconfig");
				db.SetAttribute("layout", "helix.db.xml");

				// Now save the file
				m_config_file_name = "./helix.xml";
				doc.Save( m_config_file_name );
			}
		}
	
		public void InitLogs()
		{
			using(EnEx ee = new EnEx("TheMain::InitLogs()") ){

				// Start our log handler on it's own thread if we are configured to do so:
				XmlElement root = m_config.DocumentElement;
				XmlElement al = XmlHelpers.FindChild (root, "AdaptiveLogs");
				if (XmlHelpers.getBoolAttr (al, "disabled") == false) {
					m_logger = new AdaptiveLogs (Log.GetLogQueue ()); // Remember this for later
					StartThreadable (m_logger);
				}

				System.Console.WriteLine("Adaptive logger started...");

				// Let people know what our channels look like
				Log.Panic("Panic Channel");
				Log.Error("Error Channel");
				Log.Warn("Warn Channel");
				Log.Info("Info Channel");
				Log.Debug("Debug Channel");
				Log.Trace("Trace Channel");
				Log.SqlTrace("SQLTrace Channel");

			}
		}

		public void InitStorageDB()
		{
			using(EnEx ee = new EnEx("TheMain::InitStorageDB()") ){

				m_databases = new Dictionary<string, SqlDB> ();

				XmlElement root = m_config.DocumentElement;
				XmlElement storage = XmlHelpers.FindChild( root, "Storage" );
				if(storage == null){
					// Add in the default storage structure:
					storage = m_config.CreateElement("Storage");
					root.AppendChild(storage);
					XmlElement db = m_config.CreateElement("DB");
					storage.AppendChild(db);
					db.SetAttribute("name", "helixconfig");
					db.SetAttribute("layout", "helix.db.xml");
					SaveConfig(); // write the update back out to disk
				}

				List<XmlElement> dbs = XmlHelpers.FindChildren( storage, "DB" );
				foreach(XmlElement db in dbs) {
					string dbName = db.GetAttribute( "name" );	
					try {
						SqlDB sqldb = new SqlDB( db );
						m_databases[ dbName ] = sqldb;
					} catch (Exception e){
						Log.Error("Exception opening one of our databases {0}:\n{1}", dbName, e.Message );
						Log.Error("This is most likely because the database is corrupt.  Moving to backup and starting over.");
						// Move the corrupt database out of the way
						string corruptName = dbName + ".corrupt";
						if(File.Exists( corruptName )){
							File.Delete( corruptName );
						}
						File.Move( dbName, corruptName );

						// Then re-open it:
						SqlDB sqldb = new SqlDB( db );
						m_databases[ dbName ] = sqldb;

						// Exceptions from this are allowed to bubble up and kill TheMain startup.  Exceptions at this
						// point indicate that we have a bad database setup file, and this should be addressed by
						// development.
					}
				}
			}
		}

		public SqlDB GetSqlDB( string whichOne )
		{
			using (EnEx ee = new EnEx ("TheMain::GetSqlDB(const twine& whichOne)")) {

				if (whichOne.Length == 0) {
					// pick up "helixconfig"
					string which = "helixconfig";
					if (m_databases.ContainsKey (which)) {
						return m_databases [which];
					}
				}
				if (m_databases.ContainsKey (whichOne) ) {
					return m_databases [whichOne];
				}

				throw new Exception ("Unknown local database requested: " + whichOne);
			}
		}

		/*
		BlockingQueue<IOConn*>& TheMain::getIOQueue(void)
		{
			return m_io_queue;
		}
		*/

		public void LaunchIOAdapters()
		{
			using(EnEx ee = new EnEx("TheMain::LaunchIOAdapters()") ){

				// First launch our scheduler.  That should always be running.
				StartThreadable (Schedule.getInstance ());

				// Then walk the config file and launch everything else	
				
				XmlElement ioAdapters = XmlHelpers.FindChild(m_config.DocumentElement, "IOAdapters");
				if(ioAdapters == null){
					Log.Warn("IOAdapters Node not listed in config file.");
					return;
				}
				
				foreach(XmlNode node in ioAdapters.ChildNodes){
					if(node.NodeType == XmlNodeType.Element && node.Name == "IOAdapter"){
						LoadIOAdapter((XmlElement)node);
					}
				}	
			}
		}

		public void LoadIOAdapter(XmlElement node)
		{
			using(EnEx ee = new EnEx("TheMain::LoadIOAdapter()") ){

				string name = node.GetAttribute("name");
				string className = node.GetAttribute ("class");

				if(String.IsNullOrEmpty(name)){
					Log.Error("IOAdapter Must have a name attribute");
					return;
				} 

				if(String.IsNullOrEmpty(className)){
					Log.Error("IOAdapter Must have a class attribute");
					return;
				} 

				Log.Info("Launching IOAdapter {0} from class {1}", name, className);

				try {
					Type type = Type.GetType( className, true);
					IOAdapter io = (IOAdapter)Activator.CreateInstance(type);
					io.Init( node );
					StartThreadable( io );
				} catch (Exception e){
					Log.Error("Error loading IOAdapter: {0}", e.Message );
				}
			}
		}

		public void LaunchMsgProcScaler()
		{
			using (EnEx ee = new EnEx ("TheMain::LaunchMsgProcScaler(void)")) {
				StartThreadable (new MsgProcScaler ("Central Message Processor"));
				StartThreadable (new SessionSerializer ());
			}
		}

		public void ShutdownThreads()
		{
			using (EnEx ee = new EnEx ("TheMain::ShutdownThreads()")) {

				int i;

				// The logger is always thread 0.  Shut it down last

				// for every thread that we have, call it's shutdown method
				Log.Info ("Shutting down threads");
				for (i = 1; i < (int)m_our_threads.Count; i++) {
					m_our_threads [i].Value.Shutdown ();
				}	

				// for every thread that we have, join on the thread to ensure
				// that it is done.
				Log.Info ("Joining threads");
				for (i = 1; i < (int)m_our_threads.Count; i++) {
					//m_our_threads[i].first->join();
					m_our_threads [i].Key.Abort ();
				}	

				// for every thread that we have, delete the thread and
				// the threadable object.
				Log.Info ("Deleteing threads");
				//for(i = 1; i < (int)m_our_threads.size(); i++){
				//delete m_our_threads[i].first;
				//delete m_our_threads[i].second;
				//}	

				Log.Info ("Thread Shutdown complete");
			}
		}

		public void ShutdownLogger()
		{
			using (EnEx ee = new EnEx ("TheMain::ShutdownLogger()")) {

				// The Logger is always thread 0.
				Log.Panic ("Shutting down Logger.  TheMain exiting.");

				m_our_threads [0].Value.Shutdown ();
				Thread.Sleep (1000);// sleep for 1 second to allow logs to shutdown.
				m_our_threads [0].Key.Abort ();
				//delete m_our_threads[0].first;
				//delete m_our_threads[0].second;

				// any logging at this point will go to stdout.
				// which means it will most likely be lost.

				// clear up the threads vector
				m_our_threads.Clear ();
			}
		}

		public string SystemName()
		{
			using (EnEx ee = new EnEx ("TheMain::SystemName()")) {
				return m_system_name;
			}
		}

		public string ServerVersion()
		{
			using (EnEx ee = new EnEx ("TheMain::ServerVersion()")) {

				return _globalServerVersion;
			}
		}

		public string ServerBuiltOn()
		{
			using (EnEx ee = new EnEx ("TheMain::ServerBuiltOn()")) {

				return _globalServerBuiltOn;
			}
		}

		public void ReReadConfig()
		{
			using (EnEx ee = new EnEx ("TheMain::ReReadConfig()")) {
				/*
				// for every thread that we have, tell them to re-read their config
				INFO(FL, "ReReading Configuration Info");

				for(int i = 1; i < (int)m_our_threads.size(); i++){
					m_our_threads[i].second->ReReadConfig();
				}	
				*/
				Log.Info ("Shutting down for re-configuration cycle");
				m_is_shutdown_reconfig = true;
				m_shutdown = true;
			}
		}

		public string GetConfigFileName()
		{
			using (EnEx ee = new EnEx ("TheMain::GetConfigFileName()")) {
				return m_config_file_name;
			}
		}

		public OdbcObj GetOdbcConnection(string whichOne)
		{
			using(EnEx ee = new EnEx("TheMain::GetOdbcConnection()")){

				if( m_odbc_conn == null){
					m_odbc_conn = new OdbcObj();
					m_odbc_conn.Connect("smc", "smc", "DSN=viazos19;");
				}

				return m_odbc_conn;
			}
		}

		public void RefreshAdaptiveLogs()
		{
			using (EnEx ee = new EnEx ("TheMain::RefreshAdaptiveLogs()")) {

				m_logger.RefreshConfig ();
			}
		}

		public AdaptiveLogs GetAdaptiveLogs()
		{
			if(m_logger == null){
				throw new Exception("Logger not initialized.");
			}
			return m_logger;
		}

		public void StartThreadable(Threadable t) {
			using (EnEx ee = new EnEx ("TheMain::StartThreadable()")) {
				Thread td = new Thread (Threadable.Start);
				KeyValuePair<Thread, Threadable> kvp = new KeyValuePair<Thread, Threadable> (td, t);
				td.Start (t);
				m_our_threads.Add (kvp);
			}
		}

		/*
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

	FILE* fp = fopen("./Helix.rsa", "wb" );
	if(fp == NULL){
		WARN(FL, "Saving RSA key pair failed.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		return;
	}
	int ret = 0;
	ret = PEM_write_RSAPrivateKey(fp, m_keypair, NULL, NULL, 0, NULL, NULL);
	if(!ret){
		WARN(FL, "Error writing RSA private key.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		fclose( fp );
		return;
	}
	fclose(fp);

	fp = fopen("./Helix.rsa_pub", "wb");
	if(fp == NULL){
		WARN(FL, "Saving RSA key pair failed.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		return;
	}
	ret = PEM_write_RSAPublicKey(fp, m_keypair);
	if(!ret){
		WARN(FL, "Error writing RSA public key.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		fclose( fp );
		return;
	}
	fclose(fp);

	DEBUG(FL, "RSA public/private keypair generated and saved as Helix.rsa_pub, Helix.rsa");
}

void TheMain::ReadKeys(void)
{
	EnEx ee(FL, "TheMain::ReadKeys()");

	FILE* fp = fopen("./Helix.rsa", "rb" );
	if(fp == NULL){
		WARN(FL, "Reading RSA private key failed - error opening file.");
		return;
	}
	
	m_keypair = PEM_read_RSAPrivateKey(fp, &m_keypair, NULL, NULL);
	if(m_keypair == NULL){
		WARN(FL, "Error reading RSA private key.");
		fclose(fp);
		return;
	}
	fclose(fp);

	fp = fopen("./Helix.rsa_pub", "rb");
	if(fp == NULL){
		WARN(FL, "Reading RSA public key failed - error opening file.");
		RSA_free( m_keypair );
		m_keypair = NULL;
		return;
	}

	m_keypair = PEM_read_RSAPublicKey(fp, &m_keypair, NULL, NULL);
	if(m_keypair == NULL){
		WARN(FL, "Error reading RSA public key.");
		fclose(fp);
		return;
	}
	fclose(fp);

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
*/



















	}
}
