/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include <Log.h>
#include <EnEx.h>
#include <AnException.h>
#include <twine.h>
using namespace SLib;

#ifndef _WIN32
#include <dlfcn.h>
#endif

#include "OdbcDrv.h"
using namespace Helix::Glob;

OdbcDrv::OdbcDrv(const twine& dllName)
{
	EnEx ee(FL, "OdbcDrv::OdbcDrv(const twine& dllName)");
#ifdef _WIN32
	dllHandle = LoadLibrary(dllName());
#else
	dllHandle = dlopen(dllName(), RTLD_LAZY | RTLD_GLOBAL);
#endif
	if(dllHandle == NULL){
		throw AnException(0, FL, "Error loading ODBC DLL (%s).", dllName() );
	}
	mapFunctions();
}

OdbcDrv::~OdbcDrv()
{
	EnEx ee(FL, "OdbcDrv::~OdbcDrv()");
	if(dllHandle != NULL){
#ifdef _WIN32
		FreeLibrary(dllHandle);
#else
		dlclose(dllHandle);
#endif
	}
}

void OdbcDrv::mapFunctions()
{
	EnEx ee(FL, "OdbcDrv::mapFunctions()");

#ifdef _WIN32
	this->SQLAllocConnect = (proto_SQLAllocConnect)GetProcAddress(dllHandle, "SQLAllocConnect");
	this->SQLAllocEnv = (proto_SQLAllocEnv)GetProcAddress(dllHandle, "SQLAllocEnv");
	this->SQLAllocStmt = (proto_SQLAllocStmt)GetProcAddress(dllHandle, "SQLAllocStmt");
	this->SQLBindCol = (proto_SQLBindCol)GetProcAddress(dllHandle, "SQLBindCol");
	this->SQLCancel = (proto_SQLCancel)GetProcAddress(dllHandle, "SQLCancel");
	this->SQLConnect = (proto_SQLConnect)GetProcAddress(dllHandle, "SQLConnect");
	this->SQLDescribeCol = (proto_SQLDescribeCol)GetProcAddress(dllHandle, "SQLDescribeCol");
	this->SQLDisconnect = (proto_SQLDisconnect)GetProcAddress(dllHandle, "SQLDisconnect");
	this->SQLExecDirect = (proto_SQLExecDirect)GetProcAddress(dllHandle, "SQLExecDirect");
	this->SQLExecute = (proto_SQLExecute)GetProcAddress(dllHandle, "SQLExecute");
	this->SQLFetch = (proto_SQLFetch)GetProcAddress(dllHandle, "SQLFetch");
	this->SQLFreeStmt = (proto_SQLFreeStmt)GetProcAddress(dllHandle, "SQLFreeStmt");
	this->SQLGetCursorName = (proto_SQLGetCursorName)GetProcAddress(dllHandle, "SQLGetCursorName");
	this->SQLNumResultCols = (proto_SQLNumResultCols)GetProcAddress(dllHandle, "SQLNumResultCols");
	this->SQLPrepare = (proto_SQLPrepare)GetProcAddress(dllHandle, "SQLPrepare");
	this->SQLRowCount = (proto_SQLRowCount)GetProcAddress(dllHandle, "SQLRowCount");
	this->SQLSetCursorName = (proto_SQLSetCursorName)GetProcAddress(dllHandle, "SQLSetCursorName");
	this->SQLColumns = (proto_SQLColumns)GetProcAddress(dllHandle, "SQLColumns");
	this->SQLDriverConnect = (proto_SQLDriverConnect)GetProcAddress(dllHandle, "SQLDriverConnect");
	this->SQLGetData = (proto_SQLGetData)GetProcAddress(dllHandle, "SQLGetData");
	this->SQLGetFunctions = (proto_SQLGetFunctions)GetProcAddress(dllHandle, "SQLGetFunctions");
	this->SQLGetInfo = (proto_SQLGetInfo)GetProcAddress(dllHandle, "SQLGetInfo");
	this->SQLGetTypeInfo = (proto_SQLGetTypeInfo)GetProcAddress(dllHandle, "SQLGetTypeInfo");
	this->SQLParamData = (proto_SQLParamData)GetProcAddress(dllHandle, "SQLParamData");
	this->SQLPutData = (proto_SQLPutData)GetProcAddress(dllHandle, "SQLPutData");
	this->SQLSpecialColumns = (proto_SQLSpecialColumns)GetProcAddress(dllHandle, "SQLSpecialColumns");
	this->SQLStatistics = (proto_SQLStatistics)GetProcAddress(dllHandle, "SQLStatistics");
	this->SQLTables = (proto_SQLTables)GetProcAddress(dllHandle, "SQLTables");
	this->SQLColumnPrivileges = (proto_SQLColumnPrivileges)GetProcAddress(dllHandle, "SQLColumnPrivileges");
	this->SQLExtendedFetch = (proto_SQLExtendedFetch)GetProcAddress(dllHandle, "SQLExtendedFetch");
	this->SQLForeignKeys = (proto_SQLForeignKeys)GetProcAddress(dllHandle, "SQLForeignKeys");
	this->SQLMoreResults = (proto_SQLMoreResults)GetProcAddress(dllHandle, "SQLMoreResults");
	this->SQLNativeSql = (proto_SQLNativeSql)GetProcAddress(dllHandle, "SQLNativeSql");
	this->SQLNumParams = (proto_SQLNumParams)GetProcAddress(dllHandle, "SQLNumParams");
	this->SQLPrimaryKeys = (proto_SQLPrimaryKeys)GetProcAddress(dllHandle, "SQLPrimaryKeys");
	this->SQLProcedureColumns = (proto_SQLProcedureColumns)GetProcAddress(dllHandle, "SQLProcedureColumns");
	this->SQLProcedures = (proto_SQLProcedures)GetProcAddress(dllHandle, "SQLProcedures");
	this->SQLSetPos = (proto_SQLSetPos)GetProcAddress(dllHandle, "SQLSetPos");
	this->SQLTablePrivileges = (proto_SQLTablePrivileges)GetProcAddress(dllHandle, "SQLTablePrivileges");
	this->SQLBindParameter = (proto_SQLBindParameter)GetProcAddress(dllHandle, "SQLBindParameter");
	this->SQLAllocHandle = (proto_SQLAllocHandle)GetProcAddress(dllHandle, "SQLAllocHandle");
	this->SQLCloseCursor = (proto_SQLCloseCursor)GetProcAddress(dllHandle, "SQLCloseCursor");
	this->SQLColAttribute = (proto_SQLColAttribute)GetProcAddress(dllHandle, "SQLColAttribute");
	this->SQLCopyDesc = (proto_SQLCopyDesc)GetProcAddress(dllHandle, "SQLCopyDesc");
	this->SQLEndTran = (proto_SQLEndTran)GetProcAddress(dllHandle, "SQLEndTran");
	this->SQLFetchScroll = (proto_SQLFetchScroll)GetProcAddress(dllHandle, "SQLFetchScroll");
	this->SQLFreeHandle = (proto_SQLFreeHandle)GetProcAddress(dllHandle, "SQLFreeHandle");
	this->SQLGetConnectAttr = (proto_SQLGetConnectAttr)GetProcAddress(dllHandle, "SQLGetConnectAttr");
	this->SQLGetDescField = (proto_SQLGetDescField)GetProcAddress(dllHandle, "SQLGetDescField");
	this->SQLGetDescRec = (proto_SQLGetDescRec)GetProcAddress(dllHandle, "SQLGetDescRec");
	this->SQLGetDiagField = (proto_SQLGetDiagField)GetProcAddress(dllHandle, "SQLGetDiagField");
	this->SQLGetDiagRec = (proto_SQLGetDiagRec)GetProcAddress(dllHandle, "SQLGetDiagRec");
	this->SQLGetEnvAttr = (proto_SQLGetEnvAttr)GetProcAddress(dllHandle, "SQLGetEnvAttr");
	this->SQLGetStmtAttr = (proto_SQLGetStmtAttr)GetProcAddress(dllHandle, "SQLGetStmtAttr");
	this->SQLSetConnectAttr = (proto_SQLSetConnectAttr)GetProcAddress(dllHandle, "SQLSetConnectAttr");
	this->SQLSetDescField = (proto_SQLSetDescField)GetProcAddress(dllHandle, "SQLSetDescField");
	this->SQLSetDescRec = (proto_SQLSetDescRec)GetProcAddress(dllHandle, "SQLSetDescRec");
	this->SQLSetEnvAttr = (proto_SQLSetEnvAttr)GetProcAddress(dllHandle, "SQLSetEnvAttr");
	this->SQLSetStmtAttr = (proto_SQLSetStmtAttr)GetProcAddress(dllHandle, "SQLSetStmtAttr");
	this->SQLBulkOperations = (proto_SQLBulkOperations)GetProcAddress(dllHandle, "SQLBulkOperations");
#else
	this->SQLAllocConnect = (proto_SQLAllocConnect)dlsym(dllHandle, "SQLAllocConnect");
	this->SQLAllocEnv = (proto_SQLAllocEnv)dlsym(dllHandle, "SQLAllocEnv");
	this->SQLAllocStmt = (proto_SQLAllocStmt)dlsym(dllHandle, "SQLAllocStmt");
	this->SQLBindCol = (proto_SQLBindCol)dlsym(dllHandle, "SQLBindCol");
	this->SQLCancel = (proto_SQLCancel)dlsym(dllHandle, "SQLCancel");
	this->SQLConnect = (proto_SQLConnect)dlsym(dllHandle, "SQLConnect");
	this->SQLDescribeCol = (proto_SQLDescribeCol)dlsym(dllHandle, "SQLDescribeCol");
	this->SQLDisconnect = (proto_SQLDisconnect)dlsym(dllHandle, "SQLDisconnect");
	this->SQLExecDirect = (proto_SQLExecDirect)dlsym(dllHandle, "SQLExecDirect");
	this->SQLExecute = (proto_SQLExecute)dlsym(dllHandle, "SQLExecute");
	this->SQLFetch = (proto_SQLFetch)dlsym(dllHandle, "SQLFetch");
	this->SQLFreeStmt = (proto_SQLFreeStmt)dlsym(dllHandle, "SQLFreeStmt");
	this->SQLGetCursorName = (proto_SQLGetCursorName)dlsym(dllHandle, "SQLGetCursorName");
	this->SQLNumResultCols = (proto_SQLNumResultCols)dlsym(dllHandle, "SQLNumResultCols");
	this->SQLPrepare = (proto_SQLPrepare)dlsym(dllHandle, "SQLPrepare");
	this->SQLRowCount = (proto_SQLRowCount)dlsym(dllHandle, "SQLRowCount");
	this->SQLSetCursorName = (proto_SQLSetCursorName)dlsym(dllHandle, "SQLSetCursorName");
	this->SQLColumns = (proto_SQLColumns)dlsym(dllHandle, "SQLColumns");
	this->SQLDriverConnect = (proto_SQLDriverConnect)dlsym(dllHandle, "SQLDriverConnect");
	this->SQLGetData = (proto_SQLGetData)dlsym(dllHandle, "SQLGetData");
	this->SQLGetFunctions = (proto_SQLGetFunctions)dlsym(dllHandle, "SQLGetFunctions");
	this->SQLGetInfo = (proto_SQLGetInfo)dlsym(dllHandle, "SQLGetInfo");
	this->SQLGetTypeInfo = (proto_SQLGetTypeInfo)dlsym(dllHandle, "SQLGetTypeInfo");
	this->SQLParamData = (proto_SQLParamData)dlsym(dllHandle, "SQLParamData");
	this->SQLPutData = (proto_SQLPutData)dlsym(dllHandle, "SQLPutData");
	this->SQLSpecialColumns = (proto_SQLSpecialColumns)dlsym(dllHandle, "SQLSpecialColumns");
	this->SQLStatistics = (proto_SQLStatistics)dlsym(dllHandle, "SQLStatistics");
	this->SQLTables = (proto_SQLTables)dlsym(dllHandle, "SQLTables");
	this->SQLColumnPrivileges = (proto_SQLColumnPrivileges)dlsym(dllHandle, "SQLColumnPrivileges");
	this->SQLExtendedFetch = (proto_SQLExtendedFetch)dlsym(dllHandle, "SQLExtendedFetch");
	this->SQLForeignKeys = (proto_SQLForeignKeys)dlsym(dllHandle, "SQLForeignKeys");
	this->SQLMoreResults = (proto_SQLMoreResults)dlsym(dllHandle, "SQLMoreResults");
	this->SQLNativeSql = (proto_SQLNativeSql)dlsym(dllHandle, "SQLNativeSql");
	this->SQLNumParams = (proto_SQLNumParams)dlsym(dllHandle, "SQLNumParams");
	this->SQLPrimaryKeys = (proto_SQLPrimaryKeys)dlsym(dllHandle, "SQLPrimaryKeys");
	this->SQLProcedureColumns = (proto_SQLProcedureColumns)dlsym(dllHandle, "SQLProcedureColumns");
	this->SQLProcedures = (proto_SQLProcedures)dlsym(dllHandle, "SQLProcedures");
	this->SQLSetPos = (proto_SQLSetPos)dlsym(dllHandle, "SQLSetPos");
	this->SQLTablePrivileges = (proto_SQLTablePrivileges)dlsym(dllHandle, "SQLTablePrivileges");
	this->SQLBindParameter = (proto_SQLBindParameter)dlsym(dllHandle, "SQLBindParameter");
	this->SQLAllocHandle = (proto_SQLAllocHandle)dlsym(dllHandle, "SQLAllocHandle");
	this->SQLCloseCursor = (proto_SQLCloseCursor)dlsym(dllHandle, "SQLCloseCursor");
	this->SQLColAttribute = (proto_SQLColAttribute)dlsym(dllHandle, "SQLColAttribute");
	this->SQLCopyDesc = (proto_SQLCopyDesc)dlsym(dllHandle, "SQLCopyDesc");
	this->SQLEndTran = (proto_SQLEndTran)dlsym(dllHandle, "SQLEndTran");
	this->SQLFetchScroll = (proto_SQLFetchScroll)dlsym(dllHandle, "SQLFetchScroll");
	this->SQLFreeHandle = (proto_SQLFreeHandle)dlsym(dllHandle, "SQLFreeHandle");
	this->SQLGetConnectAttr = (proto_SQLGetConnectAttr)dlsym(dllHandle, "SQLGetConnectAttr");
	this->SQLGetDescField = (proto_SQLGetDescField)dlsym(dllHandle, "SQLGetDescField");
	this->SQLGetDescRec = (proto_SQLGetDescRec)dlsym(dllHandle, "SQLGetDescRec");
	this->SQLGetDiagField = (proto_SQLGetDiagField)dlsym(dllHandle, "SQLGetDiagField");
	this->SQLGetDiagRec = (proto_SQLGetDiagRec)dlsym(dllHandle, "SQLGetDiagRec");
	this->SQLGetEnvAttr = (proto_SQLGetEnvAttr)dlsym(dllHandle, "SQLGetEnvAttr");
	this->SQLGetStmtAttr = (proto_SQLGetStmtAttr)dlsym(dllHandle, "SQLGetStmtAttr");
	this->SQLSetConnectAttr = (proto_SQLSetConnectAttr)dlsym(dllHandle, "SQLSetConnectAttr");
	this->SQLSetDescField = (proto_SQLSetDescField)dlsym(dllHandle, "SQLSetDescField");
	this->SQLSetDescRec = (proto_SQLSetDescRec)dlsym(dllHandle, "SQLSetDescRec");
	this->SQLSetEnvAttr = (proto_SQLSetEnvAttr)dlsym(dllHandle, "SQLSetEnvAttr");
	this->SQLSetStmtAttr = (proto_SQLSetStmtAttr)dlsym(dllHandle, "SQLSetStmtAttr");
	this->SQLBulkOperations = (proto_SQLBulkOperations)dlsym(dllHandle, "SQLBulkOperations");
#endif

	if(this->SQLAllocConnect == NULL) throw AnException(0, FL,"SQLAllocConnect function not found.");
	if(this->SQLAllocEnv == NULL) throw AnException(0, FL,"SQLAllocEnv function not found.");
	if(this->SQLAllocStmt == NULL) throw AnException(0, FL,"SQLAllocStmt function not found.");
	if(this->SQLBindCol == NULL) throw AnException(0, FL,"SQLBindCol function not found.");
	if(this->SQLCancel == NULL) throw AnException(0, FL,"SQLCancel function not found.");
	if(this->SQLConnect == NULL) throw AnException(0, FL,"SQLConnect function not found.");
	if(this->SQLDescribeCol == NULL) throw AnException(0, FL,"SQLDescribeCol function not found.");
	if(this->SQLDisconnect == NULL) throw AnException(0, FL,"SQLDisconnect function not found.");
	if(this->SQLExecDirect == NULL) throw AnException(0, FL,"SQLExecDirect function not found.");
	if(this->SQLExecute == NULL) throw AnException(0, FL,"SQLExecute function not found.");
	if(this->SQLFetch == NULL) throw AnException(0, FL,"SQLFetch function not found.");
	if(this->SQLFreeStmt == NULL) throw AnException(0, FL,"SQLFreeStmt function not found.");
	if(this->SQLGetCursorName == NULL) throw AnException(0, FL,"SQLGetCursorName function not found.");
	if(this->SQLNumResultCols == NULL) throw AnException(0, FL,"SQLNumResultCols function not found.");
	if(this->SQLPrepare == NULL) throw AnException(0, FL,"SQLPrepare function not found.");
	if(this->SQLRowCount == NULL) throw AnException(0, FL,"SQLRowCount function not found.");
	if(this->SQLSetCursorName == NULL) throw AnException(0, FL,"SQLSetCursorName function not found.");
	if(this->SQLColumns == NULL) throw AnException(0, FL,"SQLColumns function not found.");
	if(this->SQLDriverConnect == NULL) throw AnException(0, FL,"SQLDriverConnect function not found.");
	if(this->SQLGetData == NULL) throw AnException(0, FL,"SQLGetData function not found.");
	if(this->SQLGetFunctions == NULL) throw AnException(0, FL,"SQLGetFunctions function not found.");
	if(this->SQLGetInfo == NULL) throw AnException(0, FL,"SQLGetInfo function not found.");
	if(this->SQLGetTypeInfo == NULL) throw AnException(0, FL,"SQLGetTypeInfo function not found.");
	if(this->SQLParamData == NULL) throw AnException(0, FL,"SQLParamData function not found.");
	if(this->SQLPutData == NULL) throw AnException(0, FL,"SQLPutData function not found.");
	if(this->SQLSpecialColumns == NULL) throw AnException(0, FL,"SQLSpecialColumns function not found.");
	if(this->SQLStatistics == NULL) throw AnException(0, FL,"SQLStatistics function not found.");
	if(this->SQLTables == NULL) throw AnException(0, FL,"SQLTables function not found.");
	if(this->SQLColumnPrivileges == NULL) throw AnException(0, FL,"SQLColumnPrivileges function not found.");
	if(this->SQLExtendedFetch == NULL) throw AnException(0, FL,"SQLExtendedFetch function not found.");
	if(this->SQLForeignKeys == NULL) throw AnException(0, FL,"SQLForeignKeys function not found.");
	if(this->SQLMoreResults == NULL) throw AnException(0, FL,"SQLMoreResults function not found.");
	if(this->SQLNativeSql == NULL) throw AnException(0, FL,"SQLNativeSql function not found.");
	if(this->SQLNumParams == NULL) throw AnException(0, FL,"SQLNumParams function not found.");
	if(this->SQLPrimaryKeys == NULL) throw AnException(0, FL,"SQLPrimaryKeys function not found.");
	if(this->SQLProcedureColumns == NULL) throw AnException(0, FL,"SQLProcedureColumns function not found.");
	if(this->SQLProcedures == NULL) throw AnException(0, FL,"SQLProcedures function not found.");
	if(this->SQLSetPos == NULL) throw AnException(0, FL,"SQLSetPos function not found.");
	if(this->SQLTablePrivileges == NULL) throw AnException(0, FL,"SQLTablePrivileges function not found.");
	if(this->SQLBindParameter == NULL) throw AnException(0, FL,"SQLBindParameter function not found.");
	if(this->SQLAllocHandle == NULL) throw AnException(0, FL,"SQLAllocHandle function not found.");
	if(this->SQLCloseCursor == NULL) throw AnException(0, FL,"SQLCloseCursor function not found.");
	if(this->SQLColAttribute == NULL) throw AnException(0, FL,"SQLColAttribute function not found.");
	if(this->SQLCopyDesc == NULL) throw AnException(0, FL,"SQLCopyDesc function not found.");
	if(this->SQLEndTran == NULL) throw AnException(0, FL,"SQLEndTran function not found.");
	if(this->SQLFetchScroll == NULL) throw AnException(0, FL,"SQLFetchScroll function not found.");
	if(this->SQLFreeHandle == NULL) throw AnException(0, FL,"SQLFreeHandle function not found.");
	if(this->SQLGetConnectAttr == NULL) throw AnException(0, FL,"SQLGetConnectAttr function not found.");
	if(this->SQLGetDescField == NULL) throw AnException(0, FL,"SQLGetDescField function not found.");
	if(this->SQLGetDescRec == NULL) throw AnException(0, FL,"SQLGetDescRec function not found.");
	if(this->SQLGetDiagField == NULL) throw AnException(0, FL,"SQLGetDiagField function not found.");
	if(this->SQLGetDiagRec == NULL) throw AnException(0, FL,"SQLGetDiagRec function not found.");
	if(this->SQLGetEnvAttr == NULL) throw AnException(0, FL,"SQLGetEnvAttr function not found.");
	if(this->SQLGetStmtAttr == NULL) throw AnException(0, FL,"SQLGetStmtAttr function not found.");
	if(this->SQLSetConnectAttr == NULL) throw AnException(0, FL,"SQLSetConnectAttr function not found.");
	if(this->SQLSetDescField == NULL) throw AnException(0, FL,"SQLSetDescField function not found.");
	if(this->SQLSetDescRec == NULL) throw AnException(0, FL,"SQLSetDescRec function not found.");
	if(this->SQLSetEnvAttr == NULL) throw AnException(0, FL,"SQLSetEnvAttr function not found.");
	if(this->SQLSetStmtAttr == NULL) throw AnException(0, FL,"SQLSetStmtAttr function not found.");
	if(this->SQLBulkOperations == NULL) throw AnException(0, FL,"SQLBulkOperations function not found.");
}

int OdbcDrv::check_err(SQLRETURN status, SQLSMALLINT htype, SQLHANDLE hndl)
{
	SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLCHAR sqlstate[5 + 1];
	SQLINTEGER errcode = 0;
	SQLSMALLINT msglen, length, i;
	char tmp[32];

	EnEx ee(FL, "OdbcDrv::check_err(status, htype, hndl)");
	DEBUG(FL, "status = %d htype = %d hndl = %p", status, htype, hndl);

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

			DEBUG(FL, "Found a SQL_ERROR.");
			twine complete_message = "\n";
			i = 1;
			DEBUG(FL, "Running SQLGetDiagRec(...) (%s)", complete_message());
			msglen = SQL_MAX_MESSAGE_LENGTH + 1;
			while (this->SQLGetDiagRec(htype, hndl, i, sqlstate,
				&errcode, message, msglen, &length) == SQL_SUCCESS)
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
					
			WARN(FL, "Throwing exception for SQL_ERROR: %s", complete_message() );
			throw AnException(104, FL, "Error - SQL_ERROR: %s", complete_message() );

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
				"ODBC Driver in OdbcDrv::check_err function.",
				status);
			break;
	}
	return 1;
}

