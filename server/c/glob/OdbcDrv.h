#ifndef ODBCDRV_H
#define ODBCDRV_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>

#include <twine.h>
using namespace SLib;

namespace Helix {
namespace Glob {

/* ********************************************************************************** */
/* These are the function prototypes that we use when mapping the functions of our    */
/* ODBC Driver.                                                                       */
/* See the doc at http://msdn.microsoft.com/en-us/library/windows/desktop/ms714562(v=vs.85).aspx */
/* for the complete ODBC API reference.                                               */
/* ********************************************************************************** */
typedef SQLRETURN (*proto_SQLAllocConnect)(SQLHANDLE, SQLHANDLE*);
typedef SQLRETURN (*proto_SQLAllocEnv)(SQLHANDLE*);
typedef SQLRETURN (*proto_SQLAllocStmt)(SQLHANDLE, SQLHANDLE*);
typedef SQLRETURN (*proto_SQLBindCol)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN*);
typedef SQLRETURN (*proto_SQLCancel)(SQLHSTMT);
typedef SQLRETURN (*proto_SQLConnect)(SQLHDBC, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLDescribeCol)(SQLHSTMT, SQLUSMALLINT, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*, SQLSMALLINT*, SQLULEN*, SQLSMALLINT*, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLDisconnect)(SQLHDBC);
typedef SQLRETURN (*proto_SQLExecDirect)(SQLHSTMT, SQLCHAR*, SQLINTEGER);
typedef SQLRETURN (*proto_SQLExecute)(SQLHSTMT);
typedef SQLRETURN (*proto_SQLFetch)(SQLHSTMT);
typedef SQLRETURN (*proto_SQLFreeStmt)(SQLHSTMT, SQLUSMALLINT);
typedef SQLRETURN (*proto_SQLGetCursorName)(SQLHSTMT, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLNumResultCols)(SQLHSTMT, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLPrepare)(SQLHSTMT, SQLCHAR*, SQLINTEGER);
typedef SQLRETURN (*proto_SQLRowCount)(SQLHSTMT, SQLLEN*);
typedef SQLRETURN (*proto_SQLSetCursorName)(SQLHSTMT, SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLColumns)(SQLHSTMT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLDriverConnect)(SQLHDBC, SQLHWND, SQLCHAR*, SQLSMALLINT, 
	SQLCHAR*, SQLSMALLINT, SQLSMALLINT*, SQLUSMALLINT);
typedef SQLRETURN (*proto_SQLGetData)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN*);
typedef SQLRETURN (*proto_SQLGetFunctions)(SQLHDBC, SQLUSMALLINT, SQLUSMALLINT*);
typedef SQLRETURN (*proto_SQLGetInfo)(SQLHDBC, SQLUSMALLINT, SQLPOINTER, SQLSMALLINT, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLGetTypeInfo)(SQLHSTMT, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLParamData)(SQLHSTMT, SQLPOINTER*);
typedef SQLRETURN (*proto_SQLPutData)(SQLHSTMT, SQLPOINTER, SQLLEN);
typedef SQLRETURN (*proto_SQLSpecialColumns)(SQLHSTMT, SQLSMALLINT, SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLSMALLINT, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLStatistics)(SQLHSTMT, 
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLUSMALLINT, SQLUSMALLINT);
typedef SQLRETURN (*proto_SQLTables)(SQLHSTMT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLColumnPrivileges)(SQLHSTMT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLExtendedFetch)(SQLHSTMT, SQLUSMALLINT, SQLLEN, SQLULEN*, SQLUSMALLINT*);
typedef SQLRETURN (*proto_SQLForeignKeys)(SQLHSTMT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLMoreResults)(SQLHSTMT);
typedef SQLRETURN (*proto_SQLNativeSql)(SQLHSTMT,
	SQLCHAR*, SQLINTEGER, SQLCHAR*, SQLINTEGER, SQLINTEGER*);
typedef SQLRETURN (*proto_SQLNumParams)(SQLHSTMT, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLPrimaryKeys)(SQLHSTMT, 
	SQLCHAR*, SQLSMALLINT, 
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLProcedureColumns)(SQLHSTMT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLProcedures)(SQLHSTMT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLSetPos)(SQLHSTMT, SQLSETPOSIROW, SQLUSMALLINT, SQLUSMALLINT);
typedef SQLRETURN (*proto_SQLTablePrivileges)(SQLHSTMT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT,
	SQLCHAR*, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLBindParameter)(SQLHSTMT,
	SQLUSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLSMALLINT,
	SQLULEN, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN* );
typedef SQLRETURN (*proto_SQLAllocHandle)(SQLSMALLINT, SQLHANDLE, SQLHANDLE*);
typedef SQLRETURN (*proto_SQLCloseCursor)(SQLHSTMT);
typedef SQLRETURN (*proto_SQLColAttribute)(SQLHSTMT, SQLUSMALLINT, SQLUSMALLINT, SQLPOINTER,
	SQLSMALLINT, SQLSMALLINT*, SQLLEN*);
typedef SQLRETURN (*proto_SQLCopyDesc)(SQLHDESC, SQLHDESC);
typedef SQLRETURN (*proto_SQLEndTran)(SQLSMALLINT, SQLHANDLE, SQLSMALLINT);
typedef SQLRETURN (*proto_SQLFetchScroll)(SQLHSTMT, SQLSMALLINT, SQLLEN);
typedef SQLRETURN (*proto_SQLFreeHandle)(SQLSMALLINT, SQLHANDLE);
typedef SQLRETURN (*proto_SQLGetConnectAttr)(SQLHDBC, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER*);
typedef SQLRETURN (*proto_SQLGetDescField)(SQLHDESC, SQLSMALLINT, SQLSMALLINT, SQLPOINTER, 
	SQLINTEGER, SQLINTEGER*);
typedef SQLRETURN (*proto_SQLGetDescRec)(SQLHDESC, SQLSMALLINT, SQLCHAR*, SQLSMALLINT, SQLSMALLINT*,
	SQLSMALLINT*, SQLSMALLINT*, SQLLEN*, SQLSMALLINT*, SQLSMALLINT*, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLGetDiagField)(SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLSMALLINT,
	SQLPOINTER, SQLSMALLINT, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLGetDiagRec)(SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLCHAR*, SQLINTEGER*,
	SQLCHAR*, SQLSMALLINT, SQLSMALLINT*);
typedef SQLRETURN (*proto_SQLGetEnvAttr)(SQLHENV, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER*);
typedef SQLRETURN (*proto_SQLGetStmtAttr)(SQLHSTMT, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER*);
typedef SQLRETURN (*proto_SQLSetConnectAttr)(SQLHDBC, SQLINTEGER, SQLPOINTER, SQLINTEGER);
typedef SQLRETURN (*proto_SQLSetDescField)(SQLHDESC, SQLSMALLINT, SQLSMALLINT, SQLPOINTER, SQLINTEGER);
typedef SQLRETURN (*proto_SQLSetDescRec)(SQLHDESC, SQLSMALLINT, SQLSMALLINT, SQLSMALLINT,
	SQLLEN, SQLSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN*, SQLLEN*);
typedef SQLRETURN (*proto_SQLSetEnvAttr)(SQLHENV, SQLINTEGER, SQLPOINTER, SQLINTEGER);
typedef SQLRETURN (*proto_SQLSetStmtAttr)(SQLHSTMT, SQLINTEGER, SQLPOINTER, SQLINTEGER);
typedef SQLRETURN (*proto_SQLBulkOperations)(SQLHSTMT, SQLUSMALLINT);

/**
  * This class provides maps to all of the function pointers that have been loaded for
  * our ODBC driver. 
  */
class OdbcDrv
{
	public:
		/// Standard Constructor
		OdbcDrv(const twine& dllName);

		/// Standard Destructor
		virtual ~OdbcDrv();

		/// Use this method to convert an ODBC return code into AnException when appropriate.
		int check_err(SQLRETURN status, SQLSMALLINT htype, SQLHANDLE hndl);

		proto_SQLAllocConnect SQLAllocConnect;
		proto_SQLAllocEnv SQLAllocEnv;
		proto_SQLAllocStmt SQLAllocStmt;
		proto_SQLBindCol SQLBindCol;
		proto_SQLCancel SQLCancel;
		proto_SQLConnect SQLConnect;
		proto_SQLDescribeCol SQLDescribeCol;
		proto_SQLDisconnect SQLDisconnect;
		proto_SQLExecDirect SQLExecDirect;
		proto_SQLExecute SQLExecute;
		proto_SQLFetch SQLFetch;
		proto_SQLFreeStmt SQLFreeStmt;
		proto_SQLGetCursorName SQLGetCursorName;
		proto_SQLNumResultCols SQLNumResultCols;
		proto_SQLPrepare SQLPrepare;
		proto_SQLRowCount SQLRowCount;
		proto_SQLSetCursorName SQLSetCursorName;
		proto_SQLColumns SQLColumns;
		proto_SQLDriverConnect SQLDriverConnect;
		proto_SQLGetData SQLGetData;
		proto_SQLGetFunctions SQLGetFunctions;
		proto_SQLGetInfo SQLGetInfo;
		proto_SQLGetTypeInfo SQLGetTypeInfo;
		proto_SQLParamData SQLParamData;
		proto_SQLPutData SQLPutData;
		proto_SQLSpecialColumns SQLSpecialColumns;
		proto_SQLStatistics SQLStatistics;
		proto_SQLTables SQLTables;
		proto_SQLColumnPrivileges SQLColumnPrivileges;
		proto_SQLExtendedFetch SQLExtendedFetch;
		proto_SQLForeignKeys SQLForeignKeys;
		proto_SQLMoreResults SQLMoreResults;
		proto_SQLNativeSql SQLNativeSql;
		proto_SQLNumParams SQLNumParams;
		proto_SQLPrimaryKeys SQLPrimaryKeys;
		proto_SQLProcedureColumns SQLProcedureColumns;
		proto_SQLProcedures SQLProcedures;
		proto_SQLSetPos SQLSetPos;
		proto_SQLTablePrivileges SQLTablePrivileges;
		proto_SQLBindParameter SQLBindParameter;
		proto_SQLAllocHandle SQLAllocHandle;
		proto_SQLCloseCursor SQLCloseCursor;
		proto_SQLColAttribute SQLColAttribute;
		proto_SQLCopyDesc SQLCopyDesc;
		proto_SQLEndTran SQLEndTran;
		proto_SQLFetchScroll SQLFetchScroll;
		proto_SQLFreeHandle SQLFreeHandle;
		proto_SQLGetConnectAttr SQLGetConnectAttr;
		proto_SQLGetDescField SQLGetDescField;
		proto_SQLGetDescRec SQLGetDescRec;
		proto_SQLGetDiagField SQLGetDiagField;
		proto_SQLGetDiagRec SQLGetDiagRec;
		proto_SQLGetEnvAttr SQLGetEnvAttr;
		proto_SQLGetStmtAttr SQLGetStmtAttr;
		proto_SQLSetConnectAttr SQLSetConnectAttr;
		proto_SQLSetDescField SQLSetDescField;
		proto_SQLSetDescRec SQLSetDescRec;
		proto_SQLSetEnvAttr SQLSetEnvAttr;
		proto_SQLSetStmtAttr SQLSetStmtAttr;
		proto_SQLBulkOperations SQLBulkOperations;

	protected:
		void mapFunctions();

#ifdef _WIN32
		HINSTANCE dllHandle;
#else
		void* dllHandle;
#endif

	private:
		/// Standard Copy Constructor is private to prevent use.
		OdbcDrv(const OdbcDrv& c){}

		/// Standard Copy operator is private to prevent use.
		OdbcDrv& operator=(const OdbcDrv& c){ return *this; }

};


}} // End Helix::Glob namespace



#endif // ODBCDRV_H Defined
