/* ***************************************************************************

   Copyright (c): 2008 - 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <vector>
#include <map>
using namespace std;

#include <twine.h>
#include <Mutex.h>
using namespace SLib;

#include "OdbcObj.h"
using namespace Helix::Glob;

namespace Helix {
namespace Glob {


class DLLEXPORT ConnectionPool;

/** This is the class handed back to the caller when they request an entry from the
  * connection pool.  We keep track of the Odbc connection that they have, and which
  * connection pool it came from, so that they can easily release it back to the pool.
  */
class DLLEXPORT Connection {
	public:
		OdbcObj* odbc;
		ConnectionPool* pool;

		/// Standard Constructor
		Connection();

		/// Constructor to create a fully connected object
		Connection(OdbcObj* o, ConnectionPool* p);

		/// Use this to release this connection back to the originating connection pool.
		void release();
};

class DLLEXPORT CPEntry {
	public:
		int usage_count;
		bool in_use;
		Connection* con;
};

/** This class gathers a collection of Database connections that are all identical
 *  and makes them available to callers when they need DB Connectivity.  This handles
 *  adding more connections to the pool, reducing the size of the pool, etc.
 *  
 *  
 * @author Steven M. Cherry
 *
 */
class DLLEXPORT ConnectionPool {

	private:
		/// Copy constructor is private to prevent use:
		ConnectionPool(const ConnectionPool& c) {}

		/// Assignment operator is private to prevent use:
		ConnectionPool& operator=(const ConnectionPool& c) { return *this; }
	
	public:
	
		/// Standard constructor.
		ConnectionPool(const twine& poolName);
	
		/// Standard destructor.
		virtual ~ConnectionPool();

		/// Get our database name
		const twine& getDBName(void);
	
		/** Use this method to retrieve a Connection to our database.
		 */
		Connection& getConnection(void);

		/** Use this method to release a connection back to the pool.
		 */
		void releaseConnection(Connection& con);
	
		/** Use this to completely shutdown all connections in the pool,
		 * regardless of whether they are in use or not, and to properly
		 * close the database.
		 */
		void closePool(void);

	protected:
		/** This is protected so that sub-classes can override it if required.
		 */
		void initDB(void);

		/** This is protected so that sub-classes can override it if required.
		 */
		CPEntry* createConnection(void);

		/** This method will check the odbc connection, and if it has gone stale
		  * it will replace it with a new connection to the database.
		  */
		void checkConnection(Connection* con);

	private:

		twine m_name;
		twine m_dbname;
		twine m_user;
		twine m_pass;
		twine m_connstr;
		vector<CPEntry* > m_pool;
		map<twine, int> m_table_id;
		int m_max_connections;
		int m_grow_by;
		Mutex* m_mutex;

		/** This tries to add more connections to the pool.  If the pool is full,
		 *  or we have any problems connecting to the DB, this will throw an exception.
		 */
		void addConnections(void);

		CPEntry* findFirstUnused(void);

				
}; // class ConnectionPool

}} // End Namespace Helix::Glob

#endif //CONNECTIONPOOL_H Defined
