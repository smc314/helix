/* ***************************************************************************

   Copyright (c): 2008 - 2014 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "MySqlDbInit.h"
#include "OdbcObj.h"
#include "TheMain.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
#include <Lock.h>
#include <File.h>
#include <XmlHelpers.h>
using namespace SLib;

MySqlDbInit::MySqlDbInit( const twine& dbName )
{
	EnEx ee(FL, "MySqlDbInit::MySqlDbInit()");
	
	m_odbc = NULL;
	xmlDocPtr mainConfig = TheMain::getInstance()->GetConfig();
	xmlNodePtr root = xmlDocGetRootElement( mainConfig );
	xmlNodePtr storage = XmlHelpers::FindChild(root, "Storage");
	if(storage == NULL){
		return; // nothing to do;
	}
	xmlNodePtr db = XmlHelpers::FindChildWithAttribute(storage, "DB", "name", dbName() );
	if(db == NULL){
		return; // nothing to do;
	}
	_targetDbName.getAttribute(db, "dbname");
	_layoutFileName.getAttribute(db, "layout");
	_dbUser.getAttribute(db, "user");
	_dbPass.getAttribute(db, "pass");

	//twine connStr(db, "connstr");
	//SQLTRACE(FL, "Connection String is: %s", connStr() );
	//m_odbc = new OdbcObj(_dbUser, _dbPass, connStr);
	m_connection = &TheMain::getInstance()->GetOdbcConnection( dbName );
	m_odbc = m_connection->odbc;

}

MySqlDbInit::~MySqlDbInit()
{
	EnEx ee(FL, "MySqlDbInit::~MySqlDbInit()");

	if(m_connection != NULL){
		m_connection->release(); // release it back to the pool
	}
	m_connection = NULL;
	m_odbc = NULL;
}

void MySqlDbInit::VerifyInstallSchema()
{
	EnEx ee(FL, "MySqlDbInit::VerifyInstallSchema()");

	// Only do this if we have a valid database setup in our main config file:
	if(_targetDbName.length() == 0 || m_odbc == NULL){
		return;
	}

	if(_layoutFileName.length() == 0){
		return; // No layout file specified - this is ok.
	}
	if(!File::Exists(_layoutFileName)){
		throw AnException(0, FL, "Layout file (%s) for DB (%s) not found!", _layoutFileName(), _targetDbName() );
	}

	ProcessFile( _layoutFileName );
}

void MySqlDbInit::ProcessFile( const twine& fileName )
{
	EnEx ee(FL, "MySqlDbInit::ProcessFile()");
	_dbSetup = xmlParseFile( fileName() );

	xmlNodePtr root = xmlDocGetRootElement( _dbSetup );
	VerifyCreateDatabase();

	xmlNodePtr tables_node = XmlHelpers::FindChild(root, "Tables");
	vector<xmlNodePtr> tables = XmlHelpers::FindChildren(tables_node, "Table");
	for(size_t i = 0; i < tables.size(); i++){
		VerifyTable(tables[i]);	
	}
}

void MySqlDbInit::VerifyCreateDatabase()
{
	EnEx ee(FL, "MySqlDbInit::VerifyCreateDatabase()");

	// Get a list of existing databases:
	twine stmt = "show databases like '" + _targetDbName + "'";
	twine dbName;
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	m_odbc->BindOutput(1, dbName);

	while(m_odbc->FetchData() != 0){
		dbName.check_size();
		if(dbName == _targetDbName){
			// Found it. switch to using the target database
			stmt = "use " + _targetDbName;
			SQLTRACE(FL, "%s", stmt() );
			m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
			m_odbc->ExecStmt();
			return;
		}
	}

	// If we get to here, then the target db was not found.  Create it.
	stmt = "create database " + _targetDbName;
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
	m_odbc->ExecStmt();

	stmt = "use " + _targetDbName;
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
	m_odbc->ExecStmt();
}

void MySqlDbInit::VerifyTable(xmlNodePtr table)
{
	EnEx ee(FL, "MySqlDbInit::VerifyTable(xmlNodePtr table)");

	twine tableName(table, "name");
	twine stmt = "show tables like '" + tableName + "'";

	twine tabName;
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	m_odbc->BindOutput(1, tabName);

	while(m_odbc->FetchData() != 0){
		tabName.check_size();
		if(tabName == tableName){
			// Found it. Verify the contents
			VerifyTableStructure(table);
			return;
		}
	}

	// Didn't find it.  Create it
	CreateTable(table);
}

void MySqlDbInit::CreateTable(xmlNodePtr table)
{
	EnEx ee(FL, "MySqlDbInit::CreateTable(xmlNodePtr table)");

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
	m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
	m_odbc->ExecStmt();

	CreateIndexes(table);

	RunCreateSql(table);

}

void MySqlDbInit::CreateIndexes(xmlNodePtr table)
{
	EnEx ee(FL, "MySqlDbInit::CreateIndexes(xmlNodePtr table)");

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
		m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
		m_odbc->ExecStmt();
	}
}

void MySqlDbInit::RunCreateSql(xmlNodePtr table)
{
	EnEx ee(FL, "MySqlDbInit::RunCreateSql(xmlNodePtr table)");

	xmlNodePtr createSqlNode = XmlHelpers::FindChild(table, "SqlCreate");
	if(createSqlNode == NULL){
		return; // nothing to do
	}

	twine stmts = XmlHelpers::getTextNodeValue( createSqlNode );

	vector<twine> stmt_vect = stmts.split(";");
	for(size_t i = 0; i < stmt_vect.size(); i++){
		if(stmt_vect[i].ltrim().rtrim().length() != 0){
			SQLTRACE(FL, "%s", stmt_vect[i]() );
			m_odbc->SetStmt( stmt_vect[i], SQL_TYPE_INSERT );
			m_odbc->ExecStmt();
			m_odbc->Commit();
		}
	}
}

void MySqlDbInit::VerifyTableStructure(xmlNodePtr table)
{
	EnEx ee(FL, "MySqlDbInit::VerifyTableStructure(xmlNodePtr table)");

}
