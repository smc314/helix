/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
using namespace SLib;

#include "OdbcObj.h"
using namespace Helix::Glob;

static size_t throwAwaySize;

OdbcObj::OdbcObj()
{
	/* ************************************************************** */
	/* This version of the constructor does nothing but initialize an */
	/* empty OdbcObj object.  It will be ready to call "Connect..." on */
	/* and use for processing from there.                             */
	/* ************************************************************** */
	EnEx ee(FL, "OdbcObj::OdbcObj()");
	m_env_handle = 0;
	m_conn_handle = 0;
	m_connected = 0;

	m_execute_count = 0;
	m_fetch_count = 0;
	m_stmt_defined = 0;

	m_last_status = SQL_SUCCESS;

}

OdbcObj::OdbcObj(const twine& user, const twine& pass, const twine& inst)
{
	/* ************************************************************** */
	/* This version of the constructor will call the connect method   */
	/* for you and hand you back a fully ready OdbcObj for your use.   */
	/* ************************************************************** */
	EnEx ee(FL, "OdbcObj::OdbcObj(twine *, twine *, twine *)");

	m_env_handle = 0;
	m_conn_handle = 0;
	m_connected = 0;

	m_execute_count = 0;
	m_fetch_count = 0;
	m_stmt_defined = 0;

	m_last_status = SQL_SUCCESS;

	Connect(user, pass, inst);

}

OdbcObj::~OdbcObj()
{
	/* ************************************************************** */
	/* This method will clean up all of the handles and everything    */
	/* that we have allocated for use with oracle.                    */
	/* ************************************************************** */
	EnEx ee(FL, "OdbcObj::~OdbcObj()");

	try {
		if (m_connected) {
			INFO(FL, "Rolling back any transaction that is open:");
			Rollback();
			INFO(FL, "Disconnecting from the DB.");
			Disconnect();
		}
	} catch (AnException e){
		ERRORL(FL, "Exception caught when destroying this MSSQL object:\n"
			"%s", e.Msg());
		if (m_stmt_defined) {
			delete m_sql_text;
		}
	}

}

int OdbcObj::check_err(SQLRETURN status, SQLSMALLINT htype, SQLHANDLE hndl)
{
	SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLCHAR sqlstate[5 + 1];
	SQLINTEGER errcode = 0;
	SQLSMALLINT length, i;
	char tmp[32];

	EnEx ee(FL, "OdbcObj::check_err(status, htype, hndl)");

	switch (status) {
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NEED_DATA:
			throw AnException(102, FL, "Error - SQL_NEED_DATA");
			break;
		case SQL_NO_DATA_FOUND:
			// we return 0 here so that the fetch count is
			// zero for the caller.  This will stop them in their
			// fetch loops.
			return 0;
		case SQL_ERROR: {

			twine complete_message;
			complete_message.erase();
			complete_message = "\n";
			i = 1;
			while (SQLGetDiagRec(htype, hndl, i, sqlstate,
				&errcode, message, SQL_MAX_MESSAGE_LENGTH+1,
				&length) == SQL_SUCCESS)
			{
				complete_message.append("\tSQLSTATE = ");
				complete_message.append((char *)sqlstate);
				complete_message.append("\n");
					
				complete_message.append("\tNative Error = ");
				memset(tmp, 0, 32);
				sprintf(tmp, "%d", errcode);
				complete_message.append(tmp);
				complete_message.append("\n");
					
				complete_message.append("\tError Message = ");
				complete_message.append((char *)message);
				complete_message.append("\n");

				i ++;
			}
					
			throw AnException(104, FL, "Error - SQL_ERROR: %s", complete_message.c_str());
			break;
			}
		case SQL_INVALID_HANDLE:
			throw AnException(105, FL, "Error - SQL_INVALID_HANDLE");
			break;
		case SQL_STILL_EXECUTING:
			throw AnException(106, FL, "Error - SQL_STILL_EXECUTE");
			break;
		default:
			throw AnException(108, FL,
				"Unknown status = %d from "
				"ODBC Driver in OdbcObj::check_err function.",
				status);
			break;
	}
	return 1;
}

void OdbcObj::Connect(const twine& user, const twine& pass, const twine& inst)
{
	EnEx ee(FL, "OdbcObj::Connect(twine user, twine pass, twine inst)");

	if (m_connected) Disconnect();
	
	/* ******************************************************* */
	/* Initialize the environment handle                       */
	/* ******************************************************* */
	INFO(FL, "Initializing the environment handle.");
	check_err(
		SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_env_handle),
		SQL_HANDLE_ENV, SQL_NULL_HANDLE
	);

	/* ******************************************************* */
	/* Set the SQL_ODBC_VERSION env attribute                  */
	/* ******************************************************* */
	INFO(FL, "Setting SQL_ODBC_VERSION attribute");
	check_err(
		SQLSetEnvAttr(m_env_handle, SQL_ATTR_ODBC_VERSION,
			(SQLPOINTER)SQL_OV_ODBC3, 0),
		SQL_HANDLE_ENV, m_env_handle
	);

	/* ******************************************************* */
	/* Allocate a database connection handle                   */
	/* ******************************************************* */
	INFO(FL, "Allocating a database connection handle.");
	check_err(
		SQLAllocHandle(SQL_HANDLE_DBC, m_env_handle, &m_conn_handle),
		SQL_HANDLE_ENV, m_env_handle
	);

	/* ******************************************************* */
	/* Set the Autocommit feature to OFF.                      */
	/* ******************************************************* */
	//INFO(FL, "Turning autocommit off");
	//check_err(
	//	SQLSetConnectAttr(m_conn_handle, SQL_ATTR_AUTOCOMMIT,
	//		(SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_NTS),
	//	SQL_HANDLE_DBC, m_conn_handle
	//);
	
	/* ******************************************************* */
	/* Connect to the database:                                */
	/* ******************************************************* */
	twine tmpConnStr;
	tmpConnStr.format( "%s;UID=%s;PWD=%s;", inst(), user(), pass() );
	INFO(FL, "Connecting to the database.");
	check_err(
		SQLDriverConnect(
			m_conn_handle,                       // Connection Handle
			NULL,                                // Window handle
			(SQLCHAR *)tmpConnStr(),             // InConnection String 
			SQL_NTS,                             // String length
			NULL,                                // Out Connection String
			0,                                   // Buffer length
			NULL,                                // String Length 2 Ptr
			SQL_DRIVER_NOPROMPT),                // Driver Completion
		SQL_HANDLE_DBC, m_conn_handle
	);

	INFO(FL, "Connected to the database successfully.");
	m_connected = 1;

}

void OdbcObj::SetAutoCommit(bool onOff)
{
	EnEx ee(FL, "OdbcObj::SetAutoCommit(bool onOff)");

	/* ******************************************************* */
	/* Set the Autocommit feature to onOff.                    */
	/* ******************************************************* */
	if(onOff){
		check_err(
			SQLSetConnectAttr(m_conn_handle, SQL_ATTR_AUTOCOMMIT,
				(SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_NTS),
			SQL_HANDLE_DBC, m_conn_handle
		);
	} else {
		check_err(
			SQLSetConnectAttr(m_conn_handle, SQL_ATTR_AUTOCOMMIT,
				(SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_NTS),
			SQL_HANDLE_DBC, m_conn_handle
		);
	}
}

void OdbcObj::Disconnect(void)
{

	EnEx ee(FL, "OdbcObj::Disconnect()");

	if(m_connected == 0)
		return;

	if (m_stmt_defined) {
		DEBUG(FL, "\tremoving statement handle...\n");
		check_err(SQLFreeHandle(SQL_HANDLE_STMT, m_statement_handle),
			SQL_HANDLE_STMT, m_statement_handle);
		delete m_sql_text;
	}

	DEBUG(FL, "\tDetatching from MSSQL server...\n");
	check_err(SQLDisconnect(m_conn_handle),
		SQL_HANDLE_DBC, m_conn_handle
	);

	DEBUG(FL, "\tFreeing MSSQL connection handle...\n");
	check_err(SQLFreeHandle(SQL_HANDLE_DBC, m_conn_handle),
		SQL_HANDLE_DBC, m_conn_handle
	);

	DEBUG(FL, "\tFreeing MSSQL Environment handle...\n");
	check_err(SQLFreeHandle(SQL_HANDLE_ENV, m_env_handle),
		SQL_HANDLE_ENV, m_env_handle
	);

	m_connected = 0;

}

int OdbcObj::isConnected(void)
{
	EnEx ee(FL, "OdbcObj::isConnected(void)");
	return m_connected;
}

void OdbcObj::SetStmt(twine *stmt, int type)
{
	EnEx ee(FL, "OdbcObj::SetStmt(twine *stmt, int type)");
	SanityCheck();

	if (m_stmt_defined) {
		check_err(SQLFreeHandle( SQL_HANDLE_STMT, m_statement_handle),
			SQL_HANDLE_STMT, m_statement_handle );
		delete m_sql_text;
		m_stmt_defined = 0;
	}

	m_sql_text = new twine(*stmt);  // make a copy

	check_err(
		SQLAllocHandle(SQL_HANDLE_STMT, m_conn_handle, 
		&m_statement_handle),
		SQL_HANDLE_STMT, m_statement_handle
	);

	check_err(
		SQLPrepare(m_statement_handle, 
			(SQLCHAR *)m_sql_text->c_str(), (SQLINTEGER)m_sql_text->size()),
		SQL_HANDLE_STMT, m_statement_handle
	);

	m_stmt_defined = 1;
	m_first_fetch_done = 0;
	if (type == SQL_TYPE_SELECT)
		m_stmt_is_select = 1;
	else
		m_stmt_is_select = 0;

}

void OdbcObj::SetStmt(char *stmt, int type)
{

	EnEx ee(FL, "OdbcObj::SetStmt(char *stmt, int type)");

	twine tmp;
	tmp.erase();
	tmp = stmt;
	SetStmt(&tmp, type);

}

void OdbcObj::SetStmt(twine& stmt, int type)
{
	EnEx ee(FL, "OdbcObj::SetStmt(twine& stmt, int type)");

	SetStmt(&stmt, type);
}

void OdbcObj::ValidateStmt(char* stmt, int type)
{
	EnEx ee(FL, "OdbcObj::ValidateStmt(char *stmt, int type)");

	twine tmp;
	tmp.erase();
	tmp = stmt;
	SetStmt(&tmp, type);

	short col_count;

	check_err(
		SQLNumResultCols(m_statement_handle, &col_count),
		SQL_HANDLE_STMT, m_statement_handle
	);
	

}
	
void OdbcObj::BindInput(int pos, void *mem, int *size, int type)
{
	EnEx ee(FL, "OdbcObj::BindInput(int, void *, int, int)");

	SanityCheck();
	int tmp_colsize = *size;
	if(tmp_colsize == 0) tmp_colsize = 1;
	

	/* bind the input variable */
	check_err(
		SQLBindParameter(m_statement_handle, pos, SQL_PARAM_INPUT,
			dbtype2(type), dbtype(type), tmp_colsize, 0, mem, 
			*size, (SQLLEN*)size),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

void OdbcObj::BindInput(int pos, twine& data)
{
	EnEx ee(FL, "OdbcObj::BindInput(int, twine&)");

	SanityCheck();
	size_t tmp_colsize = data.size();
	if(tmp_colsize == 0) tmp_colsize = 1;
	

	/* bind the input variable */
	check_err(
		SQLBindParameter(m_statement_handle, pos, SQL_PARAM_INPUT,
			dbtype2(DB_CHAR), dbtype(DB_CHAR), tmp_colsize, 0, data.data(), 
			data.size(), NULL),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

void OdbcObj::BindInput(int pos, MemBuf& data)
{
	EnEx ee(FL, "OdbcObj::BindInput(int, MemBuf&)");

	SanityCheck();
	size_t tmp_colsize = data.size();
	if(tmp_colsize == 0) tmp_colsize = 1;
	

	/* bind the input variable */
	check_err(
		SQLBindParameter(m_statement_handle, pos, SQL_PARAM_INPUT,
			dbtype2(DB_CHAR), dbtype(DB_CHAR), tmp_colsize, 0, data.data(), 
			data.size(), NULL),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

void OdbcObj::BindInput(int pos, Date& data)
{
	EnEx ee(FL, "OdbcObj::BindInput(int, Date&)");

	SanityCheck();
	size_t tmp_colsize = 20;
	if(tmp_colsize == 0) tmp_colsize = 1;
	

	/* bind the input variable */
	check_err(
		SQLBindParameter(m_statement_handle, pos, SQL_PARAM_INPUT,
			dbtype2(DB_CHAR), dbtype(DB_CHAR), tmp_colsize, 0, data.GetValue(), 
			tmp_colsize, NULL),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

void OdbcObj::BindOutput(int pos, void *mem, int *size, int type)
{
	EnEx ee(FL, "OdbcObj::BindOutput(int, void *, int, int)");
	SanityCheck();

	/* The mssql driver expectes the size parameter to include
	* space for the null terminating character for string data.
	* We don't want to make the caller provide that, so for character
	* data, we bump up the size by 1.  The caller does have to ensure
	* that there actually is enough space for the null terminator.
	* They just don't have to account for it in the size parameter.
	*/
	if(type == DB_CHAR){
		*size += 1;
	}

	/* bind the output variable */
	check_err(
		SQLBindCol(m_statement_handle,
			pos, // Remember positions start at 1, not 0
			dbtype2(type),
			mem,
			*size,
			(SQLLEN*)size),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

void OdbcObj::BindOutput(int pos, twine& data)
{
	EnEx ee(FL, "OdbcObj::BindOutput(int, twine&)");
	SanityCheck();

	// We expect this version of BindOutput to be called after
	// the ExecStmt, but before a fetch.  This means that we have
	// metadata available to us so that we can use it to determine
	// column sizes.

	SQLCHAR cname[512];
	short lcname, dbtype, scale, nullable;
	SQLULEN colsize;

	check_err(
		SQLDescribeCol( m_statement_handle,
			(short)pos,             // Which column are we interested in?
			cname,                  // buffer for the column name
			(short)sizeof(cname),   // how big is that buffer
			&lcname,                // tell us how long the column name is
			&dbtype,                // tell us what the db type is
			&colsize,               // how big is the column data
			&scale,                 // is there any scale to the precision?
			&nullable),             // is the column nullable?
		SQL_HANDLE_STMT, m_statement_handle
	);

	// Now use that information to reserve space in the twine:
	DEBUG(FL, "Reserving %d in the output twine.", colsize);
	data.reserve( colsize );
	size_t size = data.capacity() + 1;

	// Now bind the twine data buffer to the column itself:
	check_err(
		SQLBindCol(m_statement_handle,
			pos, // remember positions start at 1, not 0
			dbtype2(DB_CHAR),
			data.data(),
			size,
			(SQLLEN*) &throwAwaySize ),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

void OdbcObj::BindOutput(int pos, Date& data)
{
	EnEx ee(FL, "OdbcObj::BindOutput(int, twine&)");
	SanityCheck();

	size_t size = 20;

	// Now bind the twine data buffer to the column itself:
	check_err(
		SQLBindCol(m_statement_handle,
			pos, // remember positions start at 1, not 0
			dbtype2(DB_CHAR),
			data.GetValue(),
			size,
			(SQLLEN*) &throwAwaySize ),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

ColumnInfo OdbcObj::GetColumnInfo(int pos)
{
	EnEx ee(FL, "OdbcObj::GetColumnInfo()");
	SanityCheck();

	SQLCHAR cname[512];
	short lcname, dbtype, scale, nullable;
	SQLULEN colsize;

	check_err(
		SQLDescribeCol( m_statement_handle,
			(short)pos,             // Which column are we interested in?
			cname,                  // buffer for the column name
			(short)sizeof(cname),   // how big is that buffer
			&lcname,                // tell us how long the column name is
			&dbtype,                // tell us what the db type is
			&colsize,               // how big is the column data
			&scale,                 // is there any scale to the precision?
			&nullable),             // is the column nullable?
		SQL_HANDLE_STMT, m_statement_handle
	);

	ColumnInfo ret;
	ret.position = pos;
	ret.name = cname;
	ret.dbtype = dbtype;
	ret.size = colsize;
	ret.scale = scale;
	ret.nullable = (nullable == 1);

	return ret;
}


int OdbcObj::GetResultsetColumnCount(void)
{
	EnEx ee(FL, "OdbcObj::GetResultsetColumnCount()");
	SanityCheck();

	SQLSMALLINT colCount = 0;
	check_err(
		SQLNumResultCols(m_statement_handle, &colCount),
		SQL_HANDLE_STMT, m_statement_handle
	);

	return (int)colCount;
}

twine OdbcObj::GetColumnData(int pos)
{
	EnEx ee(FL, "OdbcObj::GetResultsetColumnCount()");

	return GetColumnData(pos, true);
}

twine OdbcObj::GetColumnData(int pos, bool trim)
{
	EnEx ee(FL, "OdbcObj::GetResultsetColumnCount()");
	SanityCheck();

	int colCount = GetResultsetColumnCount();
	if(pos < 1 || pos > colCount){
		throw AnException(0, FL, "Invalid column position %d, should be in the range [%d, %d]",
			pos, 1, colCount);
	}

	SQLLEN indicator;
	ColumnInfo ci = GetColumnInfo(pos);
	twine ret; ret.reserve( ci.size );
	switch (ci.dbtype) {
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
			ret.reserve( ci.size );
			break;
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		case SQL_WLONGVARCHAR:
			ret.reserve( ci.size * 2 );
			break;
		case SQL_DECIMAL:
		case SQL_NUMERIC:
		case SQL_SMALLINT:
		case SQL_INTEGER:
		case SQL_REAL:
		case SQL_FLOAT:
		case SQL_DOUBLE:
			ret.reserve( 32 );
			break;
		case SQL_BIT:
			ret.reserve( 2 );
			break;
		case SQL_TINYINT:
		case SQL_BIGINT:
			ret.reserve( 32 );
			break;
		case SQL_BINARY:
		case SQL_VARBINARY:
		case SQL_LONGVARBINARY:
			ret.reserve( ci.size * 2);
			break;
		case SQL_TYPE_DATE:
		case SQL_TYPE_TIME:
		case SQL_TYPE_TIMESTAMP:
		case SQL_INTERVAL_MONTH:
		case SQL_INTERVAL_YEAR:
		case SQL_INTERVAL_YEAR_TO_MONTH:
		case SQL_INTERVAL_DAY:
		case SQL_INTERVAL_HOUR:
		case SQL_INTERVAL_MINUTE:
		case SQL_INTERVAL_SECOND:
		case SQL_INTERVAL_DAY_TO_HOUR:
		case SQL_INTERVAL_DAY_TO_MINUTE:
		case SQL_INTERVAL_DAY_TO_SECOND:
		case SQL_INTERVAL_HOUR_TO_MINUTE:
		case SQL_INTERVAL_HOUR_TO_SECOND:
		case SQL_INTERVAL_MINUTE_TO_SECOND:
		case SQL_GUID:
			ret.reserve( 32 );
			break;
		default :
			ret.reserve( 32 );
			break;
	}

	check_err(
		SQLGetData(m_statement_handle, pos, SQL_C_CHAR,
			ret.data(), ret.capacity(), &indicator),
		SQL_HANDLE_STMT, m_statement_handle
	);

	if(indicator == SQL_NULL_DATA){
		ret = "[null]";
	} else {
		ret.check_size();
		if(trim){
			ret.rtrim();
		}
	}

	return ret;
}

twine OdbcObj::GetDriverVersion(void)
{
	EnEx ee(FL, "OdbcObj::GetDriverVersion()");
	SanityCheck();

	SQLSMALLINT size;
	twine ret; ret.reserve(256);
	check_err(
		SQLGetInfo(m_conn_handle, SQL_DRIVER_VER,
			ret.data(), 256, &size),
		SQL_HANDLE_DBC, m_conn_handle
	);

	ret.check_size();
	ret.rtrim();
	return ret;
}


void OdbcObj::ExecStmt(void)
{
	EnEx ee(FL, "OdbcObj::ExecStmt()");
	SanityCheck();

	m_execute_count ++;

	/* execute only */
	check_err(
		SQLExecute(m_statement_handle),
		SQL_HANDLE_STMT, m_statement_handle
	);

}

void OdbcObj::Commit(void)
{
	EnEx ee(FL, "OdbcObj::Commit()");

	SanityCheck();
	check_err(
		SQLEndTran(SQL_HANDLE_DBC, m_conn_handle, SQL_COMMIT),
		SQL_HANDLE_DBC, m_conn_handle
	);
		
}

void OdbcObj::Rollback(void)
{
	EnEx ee(FL, "OdbcObj::Rollback()");

	SanityCheck();
	check_err(
		SQLEndTran(SQL_HANDLE_DBC, m_conn_handle, SQL_ROLLBACK),
		SQL_HANDLE_DBC, m_conn_handle
	);
		
}

int OdbcObj::FetchData(void)
{
	int fetch_count = 0;
	EnEx ee(FL, "OdbcObj::FetchData()");
	SanityCheck();

	m_fetch_count ++;

	fetch_count = check_err(
		SQLFetch(m_statement_handle),
		SQL_HANDLE_STMT, m_statement_handle
	);

	return fetch_count;
}

int OdbcObj::GetSQLRowCount(void)
{
	EnEx ee(FL, "OdbcObj::GetSQLRowCount()");
	SanityCheck();

	SQLLEN rowCount = 0;
	check_err(
		SQLRowCount(m_statement_handle, &rowCount),
		SQL_HANDLE_STMT, m_statement_handle
	);

	return (int)rowCount;
}

int OdbcObj::dbtype(int type)
{
	EnEx ee(FL, "OdbcObj::dbtype()");
	switch (type) {
		case DB_INT :
			return SQL_INTEGER;
		case DB_CHAR :
			return SQL_CHAR;
		case DB_FLOAT :
			return SQL_FLOAT;
		case DB_DATETIME:
			return SQL_TYPE_TIMESTAMP ;

/*
	And Here's a bunch of others that might come in handy some day:

		case ???? :
			return SQL_BIGINT;
		case ???? :
			return SQL_BINARY;
		case ???? :
			return SQL_BLOB;
		case ???? :
			return SQL_BLOB_LOCATOR;
		case ???? :
			return SQL_CLOB;
		case ???? :
			return SQL_CLOB_LOCATOR;
		case ???? :
			return SQL_DBCLOB;
		case ???? :
			return SQL_DBCLOB_LOCATOR;
		case ???? :
			return SQL_DECIMAL;
		case ???? :
			return SQL_DOUBLE;
		case ???? :
			return SQL_GRAPHIC;
		case ???? :
			return SQL_LONGVARBINARY;
		case ???? :
			return SQL_LONGVARCHAR;
		case ???? :
			return SQL_LONGVARGRAPHIC;
		case ???? :
			return SQL_NUMERIC;
		case ???? :
			return SQL_REAL;
		case ???? :
			return SQL_SMALLINT;
		case ???? :
			return SQL_TYPE_DATE;
		case ???? :
			return SQL_TYPE_TIME;
		case ???? :
			return SQL_TYPE_TIMESTAMP;
		case ???? :
			return SQL_VARBINARY;
		case ???? :
			return SQL_VARCHAR;
		case ???? :
			return SQL_VARGRAPHIC;

*/
		default :
			throw AnException(100, FL,
			                  "Undefined type in OdbcObj::dbtype "
			                  "conversion function");
	}
}

int OdbcObj::dbtype2(int type)
{
	EnEx ee(FL, "OdbcObj::dbtype2()");

	switch (type) {
		case DB_INT :
			return SQL_C_LONG ;
		case DB_CHAR :
			return SQL_C_CHAR ;
		case DB_FLOAT :
			return SQL_C_FLOAT ;
		case DB_DATETIME:
			return SQL_C_TYPE_TIMESTAMP ;

/*
	And Here's a bunch of others that might come in handy some day:

		case ???? :
			return SQL_C_BINARY ;
		case ???? :
			return SQL_C_BIT ;
		case ???? :
			return SQL_C_BLOB_LOCATOR ;
		case ???? :
			return SQL_C_CHAR ;
		case ???? :
			return SQL_C_CLOB_LOCATOR ;
		case ???? :
			return SQL_C_DBCHAR ;
		case ???? :
			return SQL_C_DBCLOB_LOCATOR ;
		case ???? :
			return SQL_C_DOUBLE ;
		case ???? :
			return SQL_C_FLOAT ;
		case ???? :
			return SQL_C_LONG ;
		case ???? :
			return SQL_C_NUMERIC ;
		case ???? :
			return SQL_C_SBIGINT ;
		case ???? :
			return SQL_C_SHORT ;
		case ???? :
			return SQL_C_TYPE_DATE ;
		case ???? :
			return SQL_C_TYPE_TIME ;
		case ???? :
			return SQL_C_TYPE_TIMESTAMP ;
		case ???? :
			return SQL_C_TINYINT ;
		case ???? :
			return SQL_C_UBIGINT ;

*/
		default :
			throw AnException(100, FL,
			                  "Undefined type in OdbcObj::dbtype2 "
			                  "conversion function");
	}

}

void OdbcObj::SanityCheck(void)
{
	EnEx ee(FL, "OdbcObj::SanityCheck()");
	if (!m_connected)
		throw AnException(110, FL,
			"Not connected to DB.  Can't perform operation.");

}

twine OdbcObj::GetDataTypeName( int sql_data_type )
{
	EnEx ee(FL, "OdbcObj::SanityCheck()");

	// Reference http://msdn.microsoft.com/en-us/library/windows/desktop/ms710150(v=vs.85).aspx
	// for the source of this lookup.

	switch (sql_data_type) {
		case SQL_CHAR:
			return "SQL_CHAR";
		case SQL_VARCHAR:
			return "SQL_VARCHAR";
		case SQL_LONGVARCHAR:
			return "SQL_LONGVARCHAR";
		case SQL_WCHAR:
			return "SQL_WCHAR";
		case SQL_WVARCHAR:
			return "SQL_WVARCHAR";
		case SQL_WLONGVARCHAR:
			return "SQL_WLONGVARCHAR";
		case SQL_DECIMAL:
			return "SQL_DECIMAL";
		case SQL_NUMERIC:
			return "SQL_NUMERIC";
		case SQL_SMALLINT:
			return "SQL_SMALLINT";
		case SQL_INTEGER:
			return "SQL_INTEGER";
		case SQL_REAL:
			return "SQL_REAL";
		case SQL_FLOAT:
			return "SQL_FLOAT";
		case SQL_DOUBLE:
			return "SQL_DOUBLE";
		case SQL_BIT:
			return "SQL_BIT";
		case SQL_TINYINT:
			return "SQL_TINYINT";
		case SQL_BIGINT:
			return "SQL_BIGINT";
		case SQL_BINARY:
			return "SQL_BINARY";
		case SQL_VARBINARY:
			return "SQL_VARBINARY";
		case SQL_LONGVARBINARY:
			return "SQL_LONGVARBINARY";
		case SQL_TYPE_DATE:
			return "SQL_TYPE_DATE";
		case SQL_TYPE_TIME:
			return "SQL_TYPE_TIME";
		case SQL_TYPE_TIMESTAMP:
			return "SQL_TYPE_TIMESTAMP";
		//case SQL_TYPE_UTCTIME:
			//return "SQL_TYPE_UTCTIME";
		case SQL_INTERVAL_MONTH:
			return "SQL_INTERVAL_MONTH";
		case SQL_INTERVAL_YEAR:
			return "SQL_INTERVAL_YEAR";
		case SQL_INTERVAL_YEAR_TO_MONTH:
			return "SQL_INTERVAL_YEAR_TO_MONTH";
		case SQL_INTERVAL_DAY:
			return "SQL_INTERVAL_DAY";
		case SQL_INTERVAL_HOUR:
			return "SQL_INTERVAL_HOUR";
		case SQL_INTERVAL_MINUTE:
			return "SQL_INTERVAL_MINUTE";
		case SQL_INTERVAL_SECOND:
			return "SQL_INTERVAL_SECOND";
		case SQL_INTERVAL_DAY_TO_HOUR:
			return "SQL_INTERVAL_DAY_TO_HOUR";
		case SQL_INTERVAL_DAY_TO_MINUTE:
			return "SQL_INTERVAL_DAY_TO_MINUTE";
		case SQL_INTERVAL_DAY_TO_SECOND:
			return "SQL_INTERVAL_DAY_TO_SECOND";
		case SQL_INTERVAL_HOUR_TO_MINUTE:
			return "SQL_INTERVAL_HOUR_TO_MINUTE";
		case SQL_INTERVAL_HOUR_TO_SECOND:
			return "SQL_INTERVAL_HOUR_TO_SECOND";
		case SQL_INTERVAL_MINUTE_TO_SECOND:
			return "SQL_INTERVAL_MINUTE_TO_SECOND";
		case SQL_GUID:
			return "SQL_GUID";
		default :
			return "SQL_UNKNOWN_TYPE";
	}
}
