/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "ConnectionPool.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Lock.h>
#include <AnException.h>
#include <Log.h>
using namespace SLib;

ConnectionPool::ConnectionPool(twine dbname, twine dblocation, int max, int grow) :
	m_dbname(dbname), m_dblocation(dblocation)
{
	EnEx ee("ConnectionPool::ConnectionPool()");
	m_mutex = new Mutex();

	initDB();
	
	if(max <= 0){
		m_max_connections = 10; // reasonable default
	} else {
		m_max_connections = max; // let the user control this.
	}
	
	if(grow <= 0){
		m_grow_by = 2; // reasonable default
	} else {
		m_grow_by = grow; // let the user control this.
	}
	
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
	return m_dbname;
}

void ConnectionPool::initDB(void)
{
	EnEx ee("ConnectionPool::initDB()");

	try {
		//FIXME: Load the ODBC Driver here.
	} catch (AnException e) {
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
			//FIXME: Implement this:
			//cpe->con.rollback(); // undo anything that is left hanging on this connection
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
			//CPEntry* cpe = m_pool[i];
			//FIXME: Implement these
			//cpe->con.rollback();
			//cpe->con.close();
		}
	} catch (AnException sqle){
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
	//FIXME: Implement these
	//cpe->con = DriverManager.getConnection("jdbc:hsqldb:file:" + m_dblocation, "sa", "");
	//cpe->con.setAutoCommit(false);
	cpe->usage_count = 0;
	cpe->in_use = false;
	return cpe;
}

