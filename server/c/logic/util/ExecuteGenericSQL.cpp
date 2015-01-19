/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
using namespace Helix::Glob;

#include "ExecuteGenericSQL.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "SQLStatement.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<ExecuteGenericSQL> ExecuteGenericSQL::reg("ExecuteGenericSQL", 1, "/logic/util/ExecuteGenericSQL");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/ExecuteGenericSQL Input=SQLStatement

ExecuteGenericSQL::ExecuteGenericSQL(xmlNodePtr action)
{
	EnEx ee(FL, "ExecuteGenericSQL::ExecuteGenericSQL(xmlNodePtr action)");
	
}

ExecuteGenericSQL::ExecuteGenericSQL(const ExecuteGenericSQL& c)
{
	EnEx ee(FL, "ExecuteGenericSQL::ExecuteGenericSQL(const ExecuteGenericSQL& c)");

}

ExecuteGenericSQL& ExecuteGenericSQL::operator=(const ExecuteGenericSQL& c)
{
	EnEx ee(FL, "ExecuteGenericSQL::operator=(const ExecuteGenericSQL& c)");

	return *this;
}

ExecuteGenericSQL::~ExecuteGenericSQL()
{

}

void ExecuteGenericSQL::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "ExecuteGenericSQL::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("ExecuteGenericSQL");

	// Pull up our input document and convert it into an object we can use:
	SQLStatement local( XmlHelpers::FindChild(ioc.GetRequestRoot(), SQLStatement::Name()()) );

	SQLTRACE(FL, "ExecuteGenericSQL: SQL is: %s", local.Sql() );

	xmlNodePtr resp = ioc.getResponseRoot();

	// Get LDS connection from the IOConn object
	if ((int)local.HostDB.length() == 0 || local.HostDB == "lds") {
		// Get an ODBC connection
		OdbcObj& odbc = *ioc.getDBConnection();
	
		// Execute the SQL statement
		odbc.SetStmt(local.Sql, SQL_TYPE_SELECT);
		odbc.ExecStmt();
	
		// Fetch the data
		FetchData(odbc, resp, local.Sql);
	} else if(local.HostDB.startsWith("Director-") ){
		// Handle local database access
		LocalExec( local, resp );

	} else {
		// Get an ODBC connection
		dptr<OdbcObj> odbc = GetDBConnection(local, ioc);
	
		// Execute the SQL statement
		odbc->SetStmt(local.Sql, SQL_TYPE_SELECT);
		odbc->ExecStmt();
	
		// Fetch the data
		FetchData(*odbc, resp, local.Sql);
	}
	
	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
	
OdbcObj* ExecuteGenericSQL::GetDBConnection(SQLStatement& local, IOConn& ioc)
{	
	EnEx ee(FL, "ExecuteGenericSQL::GetDBConnection(SQLStatement& local, IOConn& ioc)");

	// create a one time connection
	SessionInfo& si = ioc.getSessionInfo();

	if(si.userProperties.count("CurrentConnection") == 0){
		throw AnException(0, FL, "Current session has not chosen a DB Connection yet.");
	}

	// Get LDS connection details
	twine connName = si.userProperties[ "CurrentConnection" ];
	twine Pass = si.userProperties[ connName ];
		
	twine Host;
	twine Port;
	twine User;
	IOConn::parseConnName(connName, Host, Port, User);

	twine connStr = "DRIVER={ViaSQL Direct ODBC Driver (tcp/ip)};"
		"SRV=" + Host + "/" + Port + "/" + local.HostDB + ";"
		"UID=" + User + ";PWD=" + Pass + ";";

	return new OdbcObj( User, Pass, connStr );
}
	
void ExecuteGenericSQL::FetchData(OdbcObj& odbc, xmlNodePtr resp, twine& sql)
{
	EnEx ee(FL, "ExecuteGenericSQL::FetchData(OdbcObj& odbc, xmlNodePtr resp, twine& sql)");

	int rowCount = -1;
	if (sql.startsWith("UPDATE") || sql.startsWith("update") ||
		sql.startsWith("INSERT") || sql.startsWith("insert") ||
		sql.startsWith("DELETE") || sql.startsWith("delete")) {
		rowCount = odbc.GetSQLRowCount();
	}
	
	// Look at the metadata so that we know what to expect.
	int colCount = odbc.GetResultsetColumnCount();
	xmlNodePtr meta = xmlNewChild(resp, NULL, (const xmlChar*)"MetaData", NULL);
	XmlHelpers::setIntAttr(meta, "columns", colCount);
	XmlHelpers::setIntAttr(meta, "rows", rowCount);

	// Record the metadata information in the response
	vector<ColumnInfo> cols;
	for(int i = 1; i <= colCount; i++){
		ColumnInfo ci = odbc.GetColumnInfo(i);
		cols.push_back(ci);
		xmlNodePtr col = xmlNewChild(meta, NULL, (const xmlChar*)"Column", NULL);
		xmlSetProp(col, (const xmlChar*)"name", ci.name);
		XmlHelpers::setIntAttr(col, "position", ci.position);
		XmlHelpers::setIntAttr(col, "dbtype", ci.dbtype);
		XmlHelpers::setIntAttr(col, "size", ci.size);
		XmlHelpers::setIntAttr(col, "scale", ci.scale);
		XmlHelpers::setBoolAttr(col, "nullable", ci.nullable);
	}

	// Now fetch the data and record it as we go:
	while(odbc.FetchData() != 0){
		xmlNodePtr row = xmlNewChild(resp, NULL, (const xmlChar*)"Row", NULL);
		for(int i = 1; i <= colCount; i++){
			xmlNodePtr col = xmlNewChild(row, NULL, (const xmlChar*)"Column", NULL);
			xmlSetProp(col, (const xmlChar*)"name", cols[i-1].name);
			XmlHelpers::setBase64(xmlNewChild(col, NULL, (const xmlChar*)"value", NULL), odbc.GetColumnData(i) );
		}
	}
}

void ExecuteGenericSQL::LocalExec( SQLStatement& local, xmlNodePtr resp)
{
	EnEx ee(FL, "ExecuteGenericSQL::LocalExec(SQLStatement& local, xmlNodePtr resp)");

	twine target;
	if(local.HostDB == "Director-Config"){
		target = "helixconfig";
//	} else if(local.HostDB == "Director-Logs"){
//		target = "logs";
	} else if(local.HostDB == "Director-MFLogs"){
		target = "mflog";
	} else {
		throw AnException(0, FL, "Unknown local database: %s", local.HostDB() );
	}

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( target );
	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		// Log and prepare the statement
		SQLTRACE(FL, "Using dynamic SQL: %s", local.Sql() );
		sqldb.check_err( sqlite3_prepare( db, local.Sql(), (int)local.Sql.length(), &db_stmt, NULL) );

		// Execute the statement
		int count = sqldb.check_err( sqlite3_step( db_stmt ) );
		int rowCount = 0;

		// Grab the column count to see if there are any columns in the result
		int colCount = sqlite3_column_count( db_stmt );

		// Capture the metadata
		xmlNodePtr meta = xmlNewChild(resp, NULL, (const xmlChar*)"MetaData", NULL);
		XmlHelpers::setIntAttr(meta, "columns", colCount);

		for(int i = 0; i < colCount; i++){
			xmlNodePtr col = xmlNewChild( meta, NULL, (const xmlChar*)"Column", NULL );
			xmlSetProp(col, (const xmlChar*)"name", (const xmlChar*)sqlite3_column_name( db_stmt, i ) );
			XmlHelpers::setIntAttr( col, "position", i + 1);
			XmlHelpers::setIntAttr( col, "dbtype", SqlDB::GetDataType( sqlite3_column_type( db_stmt, i ) ) );
			XmlHelpers::setIntAttr( col, "size", sqlite3_column_bytes( db_stmt, i ) );
			XmlHelpers::setIntAttr( col, "scale", 0 );
			XmlHelpers::setIntAttr( col, "nullable", 1 );
		}

		while( count != 0 ){
			// While we have some data to retrieve
			xmlNodePtr row = xmlNewChild( resp, NULL, (const xmlChar*)"Row", NULL);
			for(int i = 0; i < colCount; i++){
				xmlNodePtr col = xmlNewChild( row, NULL, (const xmlChar*)"Column", NULL);
				xmlSetProp( col, (const xmlChar*)"name", (const xmlChar*)sqlite3_column_name( db_stmt, i ) );
				twine value; value.set( (const char*)sqlite3_column_text( db_stmt, i), (size_t)sqlite3_column_bytes( db_stmt, i) );
				XmlHelpers::setBase64( xmlNewChild(col, NULL, (const xmlChar*)"value", NULL), value );
			}

			// Keep track of how many rows we've pulled out
			rowCount ++;

			// Move to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		XmlHelpers::setIntAttr(meta, "rows", rowCount);

	} catch (AnException& e){
		// Ensure that no matter the exception, we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw for standard handling
	}

	// When we return, ensure that we release the database
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
}
