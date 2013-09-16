/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

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

namespace Helix {
namespace Glob {


class Connection {

};

class CPEntry {
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
class ConnectionPool {

	private:
		/// Copy constructor is private to prevent use:
		ConnectionPool(const ConnectionPool& c) {}

		/// Assignment operator is private to prevent use:
		ConnectionPool& operator=(const ConnectionPool& c) { return *this; }
	
	public:
	
		/// Standard constructor.
		ConnectionPool(twine dbname, twine dblocation, int max, int grow);
	
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

	private:

		twine m_dbname;
		twine m_dblocation;
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
