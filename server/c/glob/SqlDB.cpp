/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "SqlDB.h"
#include "OdbcObj.h"
#include "TheMain.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
#include <Lock.h>
#include <File.h>
#include <ZipFile.h>
#include <XmlHelpers.h>
using namespace SLib;

TableActions::TableActions(const twine& Name)
{
	TableName = Name;
}

TableActions::TableActions(const TableActions& c)
{
	TableName = c.TableName;
	Created = c.Created;
	Updated = c.Updated;
}

TableActions& TableActions::operator=(const TableActions& c)
{
	TableName = c.TableName;
	Created = c.Created;
	Updated = c.Updated;

	return *this;
}

TableActions::~TableActions()
{

}

SqlDB::SqlDB(const twine& layoutFile, const twine& dbFile, size_t maxSize )
{
	EnEx ee(FL, "SqlDB::SqlDB()");
	m_mutex = new Mutex();
	
	sqlite3_initialize();

	if(layoutFile.length() == 0){
		throw AnException(0, FL, "Invalid layoutFile passed to SqlDB");
	}
	if(dbFile.length() == 0){
		throw AnException(0, FL, "Invalid dbFile passed to SqlDB");
	}
	m_dbLayout = layoutFile;
	m_dbName = dbFile;;
	m_db_max_size = maxSize;

	sqlite3_open( m_dbName(), &m_db );
	ProcessFile( m_dbLayout );

}

SqlDB::SqlDB(xmlNodePtr db)
{
	EnEx ee(FL, "SqlDB::SqlDB()");
	m_mutex = new Mutex();
	
	sqlite3_initialize();

	if(db == NULL){
		throw AnException(0, FL, "Invalid (NULL) db node passed to SqlDB");
	}
	m_dbLayout.getAttribute(db, "layout");
	m_dbName.getAttribute(db, "name");
	m_db_max_size = XmlHelpers::getIntAttr( db, "maxsize" );

	sqlite3_open( m_dbName(), &m_db );
	ProcessFile( m_dbLayout );

}

SqlDB::~SqlDB()
{
	EnEx ee(FL, "SqlDB::~SqlDB()");

	if(m_db != NULL){
		sqlite3_close(m_db);
		m_db = NULL;
	}
	if(m_mutex != NULL){
		delete m_mutex;
		m_mutex = NULL;
	}
}

void SqlDB::ProcessFile( const twine& fileName )
{
	EnEx ee(FL, "SqlDB::ProcessFile()");
	_dbSetup = xmlParseFile( fileName() );

	xmlNodePtr root = xmlDocGetRootElement( _dbSetup );

	xmlNodePtr tables_node = XmlHelpers::FindChild(root, "Tables");
	vector<xmlNodePtr> tables = XmlHelpers::FindChildren(tables_node, "Table");
	for(size_t i = 0; i < tables.size(); i++){
		VerifyTable(tables[i]);	
	}
}

void SqlDB::VerifyTable(xmlNodePtr table)
{
	EnEx ee(FL, "SqlDB::VerifyTable(xmlNodePtr table)");

	twine tableName(table, "name");
	twine stmt = "select name from sqlite_master where type='table' and name='" + tableName + "'";

	twine tabName;
	SQLTRACE(FL, "%s", stmt() );
	check_err(
		sqlite3_prepare( m_db, stmt(), (int)stmt.length(), &m_stmt, NULL)
	);
	int rc = check_err( sqlite3_step( m_stmt ));
	if(rc == 0){
		// table does not exist - create it
		CreateTable( table );
	} else {
		// Found it, verify the contents
		VerifyTableStructure(table);
	}
}

void SqlDB::CreateTable(xmlNodePtr table)
{
	EnEx ee(FL, "SqlDB::CreateTable(xmlNodePtr table)");

	twine tableName(table, "name");
	twine stmt = "";
	twine pkStmt = "";

	vector<xmlNodePtr> cols = XmlHelpers::FindChildren( table, "Column" );
	for(size_t i = 0; i < cols.size(); i++){
		twine colName(cols[i], "name");
		twine colType(cols[i], "type");
		bool pk = XmlHelpers::getBoolAttr(cols[i], "pk");
		bool colDelete = XmlHelpers::getBoolAttr(cols[i], "delete");
		if(colDelete) continue; // skip these
		if(stmt.length() == 0){
			stmt = "create table " + tableName + " ( \n" +
				colName + " " + colType ;
		} else {
			stmt = stmt + ",\n" +
				colName + " " + colType ;
		}
		if(pk){
			if(pkStmt.length() == 0){
				pkStmt = "PRIMARY KEY (" + colName;
			} else {
				pkStmt = pkStmt + ", " + colName;
			}
		}
	}

	if(pkStmt.length() != 0){
		pkStmt += ")";
		stmt = stmt + ",\n" + pkStmt + "\n)";
	} else {
		stmt = stmt + "\n)";
	}

	SQLTRACE(FL, "%s", stmt() );
	if(m_stmt != NULL){
		sqlite3_finalize( m_stmt );
		m_stmt = NULL;
	}
	check_err( sqlite3_prepare( m_db, stmt(), (int)stmt.length(), &m_stmt, NULL ) );
	check_err( sqlite3_step( m_stmt ) );

	CreateIndexes(table);

	RunCreateSql(table);

}

void SqlDB::CreateIndexes(xmlNodePtr table)
{
	EnEx ee(FL, "SqlDB::CreateIndexes(xmlNodePtr table)");

	twine tableName(table, "name");
	vector<xmlNodePtr> indexes = XmlHelpers::FindChildren( table, "Index" );
	for(size_t i = 0; i < indexes.size(); i++){
		twine ixName(indexes[i], "name");
		bool isUnique = XmlHelpers::getBoolAttr(indexes[i], "unique");
		twine uniqueClause = isUnique ? "unique" : "";

		twine stmt = "";
		vector<xmlNodePtr> indexCols = XmlHelpers::FindChildren( indexes[i], "Column" );
		for(size_t j = 0; j < indexCols.size(); j++){
			twine idxColName(indexCols[j], "name");

			if(stmt.length() == 0){
				stmt = "create " + uniqueClause + " index " + ixName + " on " + tableName + " (" +
					idxColName;
			} else {
				stmt = stmt + ", " + idxColName;
			}
		}
		stmt = stmt + ")";

		SQLTRACE(FL, "%s", stmt() );
		if(m_stmt != NULL){
			sqlite3_finalize( m_stmt );
			m_stmt = NULL;
		}
		check_err( sqlite3_prepare( m_db, stmt(), (int)stmt.length(), &m_stmt, NULL ) );
		check_err( sqlite3_step( m_stmt ) );
	}
}

void SqlDB::RunCreateSql(xmlNodePtr table)
{
	EnEx ee(FL, "SqlDB::RunCreateSql(xmlNodePtr table)");

	xmlNodePtr createSqlNode = XmlHelpers::FindChild(table, "SqlCreate");
	if(createSqlNode == NULL){
		return; // nothing to do
	}

	twine stmts = XmlHelpers::getTextNodeValue( createSqlNode );

	vector<twine> stmt_vect = stmts.split(";");
	for(size_t i = 0; i < stmt_vect.size(); i++){
		if(stmt_vect[i].ltrim().rtrim().length() != 0){
			SQLTRACE(FL, "%s", stmt_vect[i]() );
			if(m_stmt != NULL){
				sqlite3_finalize( m_stmt );
				m_stmt = NULL;
			}
			check_err( sqlite3_prepare( m_db, stmt_vect[i](), (int)stmt_vect[i].length(), &m_stmt, NULL ) );
			check_err( sqlite3_step( m_stmt ) );
		}
	}
}

void SqlDB::VerifyTableStructure(xmlNodePtr table)
{
	EnEx ee(FL, "SqlDB::VerifyTableStructure(xmlNodePtr table)");

	twine tableName(table, "name");
	twine stmt = "";
	twine pkStmt = "";

	// Pull up all of the columns from the existing table
	map<twine, twine> existingCols;
	stmt = "pragma table_info (" + tableName + ")";

	twine tabName;
	SQLTRACE(FL, "%s", stmt() );
	if(m_stmt != NULL){
		sqlite3_finalize( m_stmt );
		m_stmt = NULL;
	}
	check_err(
		sqlite3_prepare( m_db, stmt(), (int)stmt.length(), &m_stmt, NULL)
	);
	int rc = check_err( sqlite3_step( m_stmt ));
	while( rc != 0){
		twine colName, colType;
		colName.set( (const char*)sqlite3_column_text( m_stmt, 1 ), (size_t)sqlite3_column_bytes(m_stmt, 1) );
		colType.set( (const char*)sqlite3_column_text( m_stmt, 2 ), (size_t)sqlite3_column_bytes(m_stmt, 2) );

		existingCols[ colName ] = colType;

		// advance to the next row of data:
		rc = check_err( sqlite3_step( m_stmt ));
	}

	// Now walk all of the columns that the table "should" have, and verify that they exist,
	// don't exist, etc. as appropriate.

	vector<xmlNodePtr> cols = XmlHelpers::FindChildren( table, "Column" );
	for(size_t i = 0; i < cols.size(); i++){
		twine colName(cols[i], "name");
		twine colType(cols[i], "type");
		bool pk = XmlHelpers::getBoolAttr(cols[i], "pk");
		bool colDelete = XmlHelpers::getBoolAttr(cols[i], "delete");
		if(colDelete) {
			// These columns should no longer be in the table definition
			// sqlite3 does not support dropping a column
			continue;
		}

		// Check to see if the column exists
		if(existingCols.count( colName ) == 0){
			// This column doesn't exist.  Add it to the table
			stmt = "alter table " + tableName + " add column " + colName + " " + colType ;

			SQLTRACE(FL, "%s", stmt() );
			if(m_stmt != NULL){
				sqlite3_finalize( m_stmt );
				m_stmt = NULL;
			}
			check_err( sqlite3_prepare( m_db, stmt(), (int)stmt.length(), &m_stmt, NULL ) );
			check_err( sqlite3_step( m_stmt ) );
		}

	}

	if(m_stmt != NULL){
		sqlite3_finalize( m_stmt );
		m_stmt = NULL;
	}
}

sqlite3* SqlDB::GetDatabase()
{
	EnEx ee(FL, "SqlDB::GetDatabase()");

	m_mutex->lock();
	return m_db;
}

void SqlDB::ReleaseDatabase()
{
	EnEx ee(FL, "SqlDB::ReleaseDatabase()");

	m_mutex->unlock();
}


int SqlDB::check_err( int rc )
{
	EnEx ee(FL, "SqlDB::check_err(int rc)");

	if(rc == SQLITE_OK){
		return 0; // everything is fine.
	} else if(rc == SQLITE_ROW){
		return 1; // everything is fine - data available
	} else if(rc == SQLITE_DONE){
		return 0; // everything is fine - no more data
	} else if(rc == SQLITE_MISUSE){
		throw AnException(0, FL, "Programming problem using the sqlite3 interface.");
	}

	// Otherwise, look up the error message and convert to an exception
	throw AnException(0, FL, "Sqlite3 Error: %s", sqlite3_errmsg( m_db ) );
}

void SqlDB::CheckSize( )
{
	EnEx ee(FL, "SqlDB::CheckSize()");

	if(m_db_max_size == 0){
		return; // don't do anything - let the db grow forever
	}

	Lock theLock( m_mutex );

	size_t page_size = 0, page_count = 0;
	sqlite3_stmt* stmt;
	try {
		twine sql = "pragma page_size";
		check_err( sqlite3_prepare( m_db, sql(), (int)sql.length(), &stmt, NULL));
		check_err( sqlite3_step( stmt ));
		page_size = sqlite3_column_int( stmt, 0 );
		sqlite3_finalize(stmt);
		stmt = NULL;

		sql = "pragma page_count;";
		check_err( sqlite3_prepare( m_db, sql(), (int)sql.length(), &stmt, NULL));
		check_err( sqlite3_step( stmt ));
		page_count = sqlite3_column_int( stmt, 0 );
		sqlite3_finalize(stmt);
		stmt = NULL;

		size_t total_size = page_size * page_count;
		if(total_size > m_db_max_size){
			createNewFile();
		}
	} catch (AnException& e){
		if(stmt != NULL){
			sqlite3_finalize( stmt );
			stmt = NULL;
		}
		throw e;
	}
}

void SqlDB::createNewFile( )
{
	EnEx ee(FL, "SqlDB::createNewFile()");

	// Close off our log file
	if(m_stmt != NULL){
		sqlite3_finalize( m_stmt );
		m_stmt = NULL;
	}
	if(m_db != NULL){
		sqlite3_close( m_db );
		m_db = NULL;
	}

	// Then move it to a new name:
	Date d;
	twine newName = m_dbName + "." + d.GetValue("%Y%m%d%H%M%S");
	int res = rename( m_dbName(), newName() );
	if(res){
		// Don't leave us without a database file:
		sqlite3_open( m_dbName(), &m_db );

		// Throw the exception that something went wrong.
		throw AnException(0, FL, "Error renaming sqldb file %s to %s", m_dbName(), newName() );
	}

	// Then zip it up to save space:
	ZipFile zf( newName + ".zip" );
	zf.AddFile( newName );
	zf.Close();

	// Remove the unzipped version:
	File::Delete( newName );

	// Then create our new file
	sqlite3_open( m_dbName(), &m_db );
	ProcessFile( m_dbLayout );

}

int SqlDB::GetDataType( int sqlite3_dbtype )
{
	switch(sqlite3_dbtype){
	case SQLITE_INTEGER: return SQL_INTEGER;
	case SQLITE_FLOAT: return SQL_FLOAT;
	case SQLITE_TEXT: return SQL_VARCHAR;
	case SQLITE_BLOB: return SQL_VARBINARY;
	case SQLITE_NULL: return SQL_VARCHAR;
	default: return SQL_VARCHAR;
	}
}

