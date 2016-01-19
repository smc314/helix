/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef THEMAIN_H
#define THEMAIN_H

#include "ThreadList.h"
#include "Threadable.h"
#include "IOConn.h"
#include "OdbcObj.h"
#include "AdaptiveLogs.h"
#include "SqlDB.h"
#include "ConnectionPool.h"

#include <vector>
#include <utility>
using namespace std;

#include <Thread.h>
#include <Mutex.h>
#include <twine.h>
#include <xmlinc.h>
#include <BlockingQueue.h>
using namespace SLib;

#include <openssl/rsa.h>

/// This is a useful macro that helps to keep the code readable.
#define SVECT( type ) sptr< vector<type*>, type::deleteVector> 

namespace Helix {
namespace Glob {


class DLLEXPORT ProtocolMaster;

/**
  * This class does double duty as our main execution body
  * as well as holding any information that needs to be
  * globally accessable.  Instantiate this with the argc
  * and argv values from the c main function, and then
  * call Execute().  This will do the rest.
  *
  * @author Steven M. Cherry
  */
class DLLEXPORT TheMain
{
	private:

		// Default constructor is private to prevent use.
		TheMain() {}

		// Copy constructor is private to prevent use.
		TheMain(const TheMain& c) {}

		// Assignment operator is private to prevent use.
		TheMain& operator=(const TheMain& c) { return *this; }

	public:

		/** 
		  * Our main constructor allows the input of one command
		  * line argument as follows:
		  * <ul>
		  *   <li>ConfigFile</li>
		  * </ul>
		  * <P>
		  * This will throw an exception if anything goes wrong.
		  */
		TheMain(char *p_config_file_name);

		/// Standard destructor
		virtual ~TheMain();

		/// Use this to access the global instance of TheMain.
		static TheMain* getInstance(void);

		/// This is how you start us up.
		void Execute(void);

		/// Returns the global ThreadList object
		ThreadList& GetThreadList(void);

		/// Allows anyone to tell us to shutdown.
		void Shutdown(void);

		/// Are we in a shutdown state?
		bool isShutdown(void);

		/// Has our shutdown finished?
		bool isShutdownDone(void);

		/** 
		  * Allows anyone to tell us to re-read our config information.
		  * We will in turn, tell all of our sub-threads to re-read
		  * their config information.  Call this whenever the config
		  * file changes so that everyone can react to it.
		  */
		void ReReadConfig(void);

		/// Returns a pointer to our config document
		xmlDocPtr GetConfig(void);

		/// Saves our current in-memory config document to the disk.
		void SaveConfig(void);

		/// Returns the name of our config file on disk
		twine& GetConfigFileName(void);

		/// Returns our system name
		twine& SystemName(void);

		/// Returns our server version
		const char* ServerVersion(void);

		/// Returns our server built-on date 
		const char* ServerBuiltOn(void);

		/// Returns the global IO Queue that we maintain:
		BlockingQueue<IOConn*>& getIOQueue(void);

		/// Dumps interesting things to the logs.
		void DumpStateToLogs(void);

		/// Returns an entry from our ODBC Connection pool for the default database
		Connection& GetOdbcConnection();

		/// Returns an entry from our ODBC Connection pool with the given name
		Connection& GetOdbcConnection(const twine& whichOne);

		/// Returns a SQL DB object that represnets an interface to one of our local databses.
		SqlDB& GetSqlDB( const twine& whichOne );

		/// Returns a SQL DB object that represnets an interface to our local configuration database.
		SqlDB& GetConfigDB( void );

		/// Tell TheMain that something has changed in the config and AdaptiveLogs needs to be refreshed.
		void RefreshAdaptiveLogs(void);

		/// Get a reference to the adaptive logs object
		AdaptiveLogs& GetAdaptiveLogs(void);

		/// Returns our public/private RSA keypair which can be used for encryption/decryption
		RSA* GetKeypair(void);

	private:

		/// This is the real execute method
		void InternalExecute(void);

		/// Finds our config file
		void FindConfigFile(void);

		/// Loads our config file
		void LoadConfig(void);

		/// Checks for any upgrades that need to be done for our config file
		void CheckUpgrades();

		/// Handles 510 -> 511 upgrades in our config file
		void Handle510_511();

		/// Autogenerates a default config file
		void GenConfig(void);

		/// Sets up simple logging
		void InitLogs(void);

		/// Finds our public/private keys
		void FindKeys(void);

		/// Creates our public/private keys if they don't exist.
		void CreateKeys(void);

		/// Reads our public/private keys from their standard files
		void ReadKeys(void);

		/// Test method to research RSA encryption/decryption
		void TestEncrypt(RSA* keypair);

		/// Loads our logic libraries
		void LoadLogics();

		/// Loads and creates any databases that we have defined
		void InitStorageDB(void);

		/// Loads and starts our IOAdapters
		void LaunchIOAdapters(void);

		/// Load and start a single IOAdapter
		void LoadIOAdapter(xmlNodePtr node);

		/// Loads and starts one protocol
		void LoadProtocol(xmlNodePtr node);

		/// Launches all Processor processes
		//void LaunchAllProcessors(void);

		/// Loads a dll that we need to keep track of for unloading
#ifdef _WIN32
		HINSTANCE LoadDLL(const twine& dll_name);
#else
		void* LoadDLL(const twine& dll_name);
#endif

		/// Launches our message processor
		void LaunchMsgProcScaler(void);
	
		/// Shuts down database connections we have allocated
		void ShutdownDatabase(void);

		/// Shuts down threads we've launched
		void ShutdownThreads(void);

		/// Shuts down our logger thread (do this last)
		void ShutdownLogger(void);

		/// The global ThreadList object
		ThreadList* m_threads;

		/// Our config file name
		twine m_config_file_name;

		/// Our system name
		twine m_system_name;

		/// Should we shutdown now or not?
		bool m_shutdown;
		bool m_shutdown_done;

		/**
		  * This is our list of threads that we have
		  * launched directly.  Since we launched 'em
		  * we're responsible for joining on 'em when
		  * they are all done.
		  */
		vector < pair < Thread*, Threadable* > > m_our_threads;

		/**
		  * This vector tracks by name and reference all of the DLL
		  * files that we have loaded for any reason.  When execution
		  * is finished, we will unload everything in this vector
		  * prior to exiting.
		  */
#ifdef _WIN32
		map < twine, HINSTANCE >  m_loaded_dlls;
#else
		map < twine, void* >  m_loaded_dlls;
#endif

		/** Global list of IOConn objects, this is the work that the
		 * system is doing.
		 */
		BlockingQueue<IOConn*> m_io_queue;

		/**
		  * This keeps our protocol masters arranged by protocol
		  * type.  It gives ready access to anyone who needs to 
		  * send or receive a message via a specific protocol type.
		  */
		map < twine, ProtocolMaster* > m_protocol_types;

		/// This is our config file
		xmlDocPtr m_config;

		/// This is the current transaction id for our system
		int m_transaction_id;

		/// This is the mutex that protects access to the trans id.
		Mutex* m_transaction_mut;
		
		/// Is the current shutdown only for a re-config cycle
		bool m_is_shutdown_reconfig;

		/// Our list of connection pools
		map< twine, ConnectionPool* > m_connection_pools;

		/// Our list of local databases:
		map< twine, SqlDB* > m_databases;

		/// This is our Adaptive Logger object.
		AdaptiveLogs* m_logger;

		/// This is our RSA keypair that is used to encrypt/decrypt our documents.
		RSA* m_keypair;

};

}} // End Namespace Helix::Glob

#endif // THEMAIN Defined
