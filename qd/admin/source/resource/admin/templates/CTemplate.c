{{!  This is a moustache template that will generate a C source file that is capable of
     executing some SQL text.  This demonstrates to the user how to use C and ODBC to execute
	 SQL of their choosing.
}}
/* *****************************************************************************
   This is an ODBC application generated to test the following SQL statement:

   {{{sqlText}}}

***************************************************************************** */

/* *****************************************************************************
For information on the ODBC C api, visit the following URL:
http://msdn.microsoft.com/en-us/library/windows/desktop/ms714562(v=vs.85).aspx
***************************************************************************** */

#ifdef _WIN32
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <stdlib.h>

/* Our Database connection handles. These don't have to be global, but if you
 * split your code across multiple methods, it makes accessing these easier
 */
SQLHANDLE m_env_handle = SQL_NULL_HANDLE;
SQLHANDLE m_conn_handle = SQL_NULL_HANDLE;
SQLHANDLE m_statement_handle = SQL_NULL_HANDLE;

/* This is a standard method that we use to test ODBC return codes for 
 * success/failure/etc.  If a failure is hit, it will log a message about 
 * the failure and return -1.
 */
int check_err( SQLRETURN status, SQLSMALLINT htype, SQLHANDLE hndl);

/* Makes our connection to the server.  Modify this to adjust host, port, 
 * user, pass, driver, and dsn settings.
 */
int Connect(void);

/* Disconnects from the server and properly cleans up our handles.
 */
int Disconnect(void);

/* Executes our SQL statement and prints out any results.
 */
int ExecuteSQL(void);

int main(int argc, char** argv)
{
	int ret;

	ret = Connect();
	if(ret < 0){
		exit(ret);
	}

	ExecuteSQL();

	Disconnect();
}

int check_err( SQLRETURN status, SQLSMALLINT htype, SQLHANDLE hndl)
{
	SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLCHAR sqlstate[5 + 1];
	SQLINTEGER errcode = 0;
	SQLSMALLINT length, i;

	switch ( status ) {
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NEED_DATA:
			printf("SQL_NEED_DATA returned from call.\n");
			return -1;
		case SQL_NO_DATA_FOUND:
			return 0;
		case SQL_ERROR: {
			printf("Error - SQL_ERROR:\n");
			i = 1;
			while( SQLGetDiagRec(htype, hndl, i, sqlstate, &errcode, message, 
				SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS)
			{
				printf("\tSQLSTATE = %s\n", (char*)SQLSTATE );
				printf("\tNative Error = %d\n", errcode);
				printf("\tError Message = %s\n", message);
				i ++;
			}
			return -1;
		}
		case SQL_INVALID_HANDLE:
			printf("Error - SQL_INVALID_HANDLE\n");
			return -1;
		case SQL_STILL_EXECUTING:
			printf("Error - SQL_STILL_EXECUTING\n");
			return -1;
		default:
			printf("Error - Unknown status (%d) in check_err function.",
				status);
			return -1;
	}	

	return 1; /* We're ok, and there is data to fetch */
}

int Connect(void)
{
	int rc;
	char* host = "FIXME_HostName";
	int port = 5501; /* FIXME - port number */
	char* user = "FIXME_UserName";
	char* pass = "FIXME_Password";
	char connstr[512];

	/* If you want to use a DSN to connect to the server, then format your
	   connection string like this
	*/
	snprintf(connstr, 512, "DSN=%s;UID=%s;PWD=%s;", 
		"FIXME_DsnNameGoesHere", user, pass );

	/* If you want to use a DSN-Less connection to the server, then format
	   your connection string like this
	*/
	snprintf(connstr, 512, "DRIVER={%s};SRV=%s/%d/lds;UID=%s;PWD=%s;",
		/* 32-bit driver name = "Ivory Direct ODBC Driver"
		   64-bit driver name = "Ivory Direct ODBC Driver x64"
		*/
		"Ivory Direct ODBC Driver", 
		host, port, user, pass
	);
	printf("Connection string is: %s\n", connstr);

	/* Allocate our environment handle */
	printf("Allocating our environment handle\n");
	rc = check_err(
		SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_env_handle),
		SQL_HANDLE_ENV, SQL_NULL_HANDLE
	);
	if(rc < 0) return rc;

	/* Set the ODBC version to v3. */
	printf("Setting the ODBC Version to v3.\n");
	rc = check_err(
		SQLSetEnvAttr(m_env_handle, SQL_ATTR_ODBC_VERSION, 
			(SQLPOINTER)SQL_OV_ODBC3, 0),
		SQL_HANDLE_ENV, SQL_NULL_HANDLE
	);
	if(rc < 0) return rc;

	/* Allocate the DB Connection handle */
	printf("Allocating the DB connection handle\n");
	rc = check_err(
		SQLAllocHandle(SQL_HANDLE_DBC, m_env_handle, &m_conn_handle),
		SQL_HANDLE_ENV, m_env_handle
	);
	if(rc < 0) return rc;

	/* Connect to the database */
	printf("Connecting to the database\n");
	rc = check_err(
		SQLDriverConnect(
			m_conn_handle,           /* Connection Handle */
			NULL,                    /* Window handle */
			connstr,                 /* Connection String - in */
			SQL_NTS,                 /* length */
			NULL,                    /* Connection String - out */
			0,                       /* buffer length */
			NULL,                    /* string length 2 prt */
			SQL_DRIVER_NOPROMPT),    /* Driver completion */
		SQL_HANDLE_DBC, m_conn_handle
	);
	if(rc < 0) return rc;

	/* Get/Print the driver version */
	SQLSMALLINT driverVersionSize = 256;
	char driverVersion[ 256 ];
	memset(driverVersion, 0, 256);
	rc = check_err(
		SQLGetInfo(m_conn_handle, SQL_DRIVER_VER, driverVersion, 255, 
			&driverVersionSize),
		SQL_HANDLE_DBC, m_conn_handle
	);
	printf("ODBC Driver Version: %s\n", driverVersion );

}

int Disconnect(void)
{
	/* As we free each of these statements, we set them back to NULL handles,
	 * which means you can make multiple calls to this method with no adverse
	 * effects.
	 */
	if(m_statement_handle != SQL_NULL_HANDLE){
		printf("Freeing the statement handle\n");
		check_err(
			SQLFreeHandle(SQL_HANDLE_STMT, m_statement_handle),
			SQL_HANDLE_STMT, m_statement_handle
		);
		m_statement_handle = SQL_NULL_HANDLE;
	}

	if(m_conn_handle != SQL_NULL_HANDLE){
		printf("Disconnecting from the server\n");
		check_err(
			SQLDisconnect(m_conn_handle),
			SQL_HANDLE_DBC, m_conn_handle
		);
		printf("Freeing the connection handle\n");
		check_err(
			SQLFreeHandle(SQL_HANDLE_DBC, m_conn_handle),
			SQL_HANDLE_DBC, m_conn_handle
		);
		m_conn_handle = SQL_NULL_HANDLE;
	}

	if(m_env_handle != SQL_NULL_HANDLE){
		printf("Freeing the environment handle\n");
		check_err(
			SQLFreeHandle(SQL_HANDLE_ENV, m_env_handle),
			SQL_HANDLE_ENV, m_env_handle
		);
		m_env_handle = SQL_NULL_HANDLE;
	}

	return 0;
}

int ExecuteSQL(void)
{
	int rc = 0;
	SQLSMALLINT columns = 0;
	int row = 0;
	int i;
	char cname[64];
	char data[512];
	short lcname, dbtype, scale, nullable;
	SQLULEN colsize;
	SQLINTEGER indicator;

	/* If your sql statement is split across multiple lines, you'll have to ensure
	 * that it is properly defined and quoted here.
	 */
	char* sql = "{{{sqlText}}}";

	if(m_statement_handle == SQL_NULL_HANDLE){
		printf("Allocating the statement handle\n");
		rc = check_err(
			SQLAllocHandle(SQL_HANDLE_STMT, m_conn_handle, &m_statement_handle),
			SQL_HANDLE_STMT, m_statement_handle
		);
		if(rc < 0) return rc;
	}

	printf("Preparing the statement\n");
	rc = check_err(
		SQLPrepare(m_statement_handle, (SQLCHAR*)sql, SQL_NTS ),
		SQL_HANDLE_STMT, m_statement_handle
	);
	if(rc < 0) return rc;

	printf("Executing the statement\n");
	rc = check_err(
		SQLExecute( m_statement_handle ),
		SQL_HANDLE_STMT, m_statement_handle
	);
	if(rc < 0) return rc;

	if(rc == 1){
		/* We have results data, and can show the results here */
		rc = check_err(
			SQLNumResultCols( m_statement_handle, &columns ),
			SQL_HANDLE_STMT, m_statement_handle
		);
		if(rc < 0 ) return rc;

		/* Print out the results metadata */
		for(i = 1; i <= columns; i++){
			rc = check_err(
				SQLDescribeCol( m_statement_handle,
					(short)i,              /* Which column do we want? */
					cname,                 /* Buffer for the col name */
					(short)sizeof(cname),  /* how big is the buffer? */
					&lcname,               /* how long is the col name */
					&dbtype,               /* what is the db type */
					&colsize,              /* How big is the col data */
					&scale,                /* Is there any scale */
					&nullable),            /* Is the col nullable? */
				SQL_HANDLE_STMT, m_statement_handle
			);
			if(rc < 0) return rc;

			if(i == 1){
				printf("%s", cname);
			} else {
				printf("\t%s", cname);
			}
		}
		printf("\n"); /* End the column header line */
		printf("------------------------------------------------------------\n");

		/* Walk the result set data */
		while( (rc = SQLFetch(m_statement_handle)) != SQL_NO_DATA ){
			if(check_err( rc ) < 0) return rc; // double-check for errors

			/* Walk all columns and print out their data */
			for(i = 1; i <= columns; i++){
				rc = check_err(
					SQLGetData( m_statement_handle,
						i,            /* Which column */
						SQL_C_CHAR,   /* Return data as char */
						data,         /* Buffer for data */
						sizeof(data), /* buffer size */
						&indicator),  /* NULL indicator or length */
					SQL_HANDLE_STMT, m_statement_handle
				);
				if(rc < 0) return rc;

				if(indicator == SQL_NULL_DATA){
					printf("NULL");
				} else {
					printf("%.*s", indicator, data );
				}
				printf("\t");
			}
			printf("\n");
		}

		/* We're skipping the check for multiple result sets here, but if you
		 * want to add that check, use SQLMoreResults( m_statement _handle ) and
		 * check the return code.
		 */
	}
}

