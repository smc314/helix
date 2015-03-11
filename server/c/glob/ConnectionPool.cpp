/* ***************************************************************************

   Copyright (c): 2008 - 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "ConnectionPool.h"
#include "TheMain.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Lock.h>
#include <AnException.h>
#include <XmlHelpers.h>
#include <Log.h>
using namespace SLib;

Connection::Connection()
{
	EnEx ee("Connection::Connection()");
	odbc = NULL;
	pool = NULL;
}

Connection::Connection(OdbcObj* o, ConnectionPool* p)
{
	EnEx ee("Connection::Connection(OdbcObj* o, ConnectionPool* p)");
	odbc = o;
	pool = p;
}

void Connection::release()
{
	EnEx ee("Connection::release()");

	if(pool != NULL){
		pool->releaseConnection( *this );
	}
}

ConnectionPool::ConnectionPool(const twine& poolName)
{
	EnEx ee("ConnectionPool::ConnectionPool()");
	m_mutex = new Mutex();

	xmlDocPtr mainConfig = TheMain::getInstance()->GetConfig();
	xmlNodePtr root = xmlDocGetRootElement( mainConfig );
	xmlNodePtr storage = XmlHelpers::FindChild( root, "Storage" );
	if(storage == NULL){
		throw AnException(0, FL, "Storage node missing in config file.");
	}
	xmlNodePtr db = XmlHelpers::FindChildWithAttribute(storage, "DB", "name", poolName() );
	if(db == NULL){
		throw AnException(0, FL, "DB configuration for %s not found.", poolName() );
	}

	m_name = poolName;
	m_dbname.getAttribute( db, "dbname" );
	m_user.getAttribute(db, "user" );
	m_pass.getAttribute(db, "pass" );
	m_connstr.getAttribute(db, "connstr" );
	
	// Update the connection string with the database name if it is not empty:
	if(m_dbname.length() != 0){
		m_connstr.append("database=" + m_dbname + ";");
	}

	m_max_connections = XmlHelpers::getIntAttr(db, "maxconnections");
	if(m_max_connections == 0){
		m_max_connections = 10; // reasonable default
	}

	m_grow_by = XmlHelpers::getIntAttr(db, "growby" );
	if(m_grow_by == 0){
		m_grow_by = 2; // reasonable default
	}

	initDB();
	addConnections();
}

ConnectionPool::~ConnectionPool()
{
	EnEx ee("ConnectionPool::~ConnectionPool()");

	{ // For Scope
		Lock theLock(m_mutex);

		for(int i = 0; i < (int)m_pool.size(); i++){
			delete m_pool[i];
		}
	}

	delete m_mutex;

}

const twine& ConnectionPool::getDBName(void)
{
	EnEx ee("ConnectionPool::getDBName()");
	return m_name;
}

void ConnectionPool::initDB(void)
{
	EnEx ee("ConnectionPool::initDB()");

	try {
		//Do any type of global odbc initialization here that is necessary.
	} catch (AnException& e) {
		ERRORL(FL, "Failed to load ODBC driver.");
		throw;
	}
}

Connection& ConnectionPool::getConnection(void)
{
	Lock theLock(m_mutex);

	EnEx ee("ConnectionPool::getConnection()");

	// Find the first unused connection:
	CPEntry* cpe = findFirstUnused();
	if(cpe != NULL){
		cpe->usage_count ++;
		cpe->in_use = true;
		checkConnection( cpe->con );
		return *(cpe->con);
	}

	// If we get here, everything was in-use.  Try to add more connections to the pool.
	addConnections();

	// try again
	cpe = findFirstUnused();
	if(cpe != NULL){
		cpe->usage_count ++;
		cpe->in_use = true;
		return *(cpe->con);
	} else {
		throw AnException(0, FL, "No Available DB Connections found!");
	}
}

void ConnectionPool::releaseConnection(Connection& con)
{
	Lock theLock(m_mutex);
	EnEx ee("ConnectionPool::releaseConnection()");
	// Find the connection in our pool and mark it unused.
	for(int i = 0; i < (int)m_pool.size(); i++){
		CPEntry* cpe = m_pool[i];
		if(cpe->con == &con){
			cpe->in_use = false;
			try {
				cpe->con->odbc->Rollback(); // undo anything that is left hanging on this connection
			} catch (AnException& e){
				// We don't care about exceptions here.
			}
			return;
		}
	}
	throw AnException(0, FL, "Unknown connection released to pool");
}

void ConnectionPool::closePool(void)
{
	Lock theLock(m_mutex);

	EnEx ee("Enter");
	try {
		for(int i = 0; i < (int)m_pool.size(); i++){
			CPEntry* cpe = m_pool[i];
			cpe->con->odbc->Rollback();
			delete cpe->con->odbc;
			delete cpe->con;
		}
	} catch (AnException& sqle){
		ERRORL(FL, "Error shutting down connections in pool: %s", sqle.Msg());
	}
}
			
CPEntry* ConnectionPool::findFirstUnused(void) 
{
	EnEx ee("ConnectionPool::findfirstUnused");
	for(int i = 0; i < (int)m_pool.size(); i++){
		CPEntry* cpe = m_pool[i];
		if(!cpe->in_use){
			return cpe;
		}
	}
	return NULL;
}

void ConnectionPool::addConnections(void)
{
	EnEx ee("ConnectionPool::addConnections");

	for(int i = 0; i < m_grow_by; i++){
		if((int)m_pool.size() >= m_max_connections) return;
		CPEntry* cpe = createConnection();
		m_pool.push_back(cpe);
	}
}

CPEntry* ConnectionPool::createConnection(void)
{
	EnEx ee("ConnectionPool::createConnection()");
	CPEntry* cpe = new CPEntry();
	cpe->usage_count = 0;
	cpe->in_use = false;
	cpe->con = new Connection();
	cpe->con->pool = this; // pointer back to us
	cpe->con->odbc = new OdbcObj( m_user, m_pass, m_connstr );
	return cpe;
}

void ConnectionPool::checkConnection(Connection* con)
{
	EnEx ee("ConnectionPool::checkConnection(Connection* con)");

	// If the connections in our pool hang around for too long, they can sometimes go
	// stale.  We need to check for this, and if the connection is bad, replace it with
	// a new connection.
	
	// Use a rollback to test whether the connection is still working or not.
	try {
		con->odbc->Rollback();
		// If all is well - then just return.
		return;
	} catch(...){
		// If we catch any type of exception or anything is thrown, then the connection is
		// stale and needs to be replaced.
		try {
			delete con->odbc;
		} catch(...){
			// We don't care about exceptions here.
		}
		// Hook up a new odbc connection to this
		con->odbc = new OdbcObj(m_user, m_pass, m_connstr );
	}

}
