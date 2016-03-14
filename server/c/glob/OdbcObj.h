/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ODBCOBJ_H
#define ODBCOBJ_H


#include <vector>
#include <map>
using namespace std;

#include "DBDataTypes.h"

#include <twine.h>
#include <MemBuf.h>
#include <Date.h>
using namespace SLib;

#include "OdbcDate.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>

namespace Helix {
namespace Glob {

// Forward declaration
class SessionInfo;


/** This class is used when querying about result set column metadata.
 */
class DLLEXPORT ColumnInfo
{
	public:
		int position;
		twine name;
		int dbtype;
		size_t size;
		int scale;
		bool nullable;
};

/**
  * This class defines our interaction with the Odbc database.
  * It encapsulates all of the ODBC calls into a standard
  * object interface.
  * It has everything we need to start from, and we will evolve it as
  * necessary as time goes on.
  * 
  * @author Steven M. Cherry
  * @copyright 2011
  */

class DLLEXPORT OdbcObj
{
	public:

		/**
 		  * The Constructor for a blank OdbcObj class:
		  */
		OdbcObj();

		/**
		  * The Constructor for a pre-connected ready to go class:
		  */
		OdbcObj(const twine& user, const twine& pass, const twine& inst);

		/**
 		  * The Destructor:
		  */
		virtual ~OdbcObj();

		/**
		  * The Connect function allows for defining this
		  * object's connection.  It will also re-connect
		  * to a new database after disconnecting from the
		  * old.
		  *
		  * @param user This is the user name for the new connection.
		  * @param pass This is the password for the given user.
		  * @param inst This is the oracle instance to connect to.
		  */
		virtual void Connect(const twine& user, const twine& pass, const twine& inst);

		/**
		  * The Disconnect method will close the current 
		  * connection to the database, and free all resources.
		  * This is functionally equivalent to destroying this
		  * object.
		  */
		virtual void Disconnect(void);

		/**
		  * Allows the caller to check if we are connected or
		  * not.
		  *
		  */
		virtual int isConnected(void);

		/**
		  * The SetAutoCommit method allows the user of this object
		  * to indicate whether auto-commit should be turned on
		  * or off.  By default when you create an OdbcObj, the
		  * AutoCommit flag is left on.  Use this method to set it
		  * as you require.
		  */
		virtual void SetAutoCommit(bool onOff);

		/**
		  * The SetStmt method allows the user of this object
		  * to setup a sql statment that is to be executed.  This
		  * function will clear the current statement, set and
		  * parse the given statement as the new one to be 
		  * executed, and handle any errors.
		  *
		  * @param stmt This is the sql text for the statement to be
		  *             executed.
		  * @param type This is the type of the sql statement that is
		  *             being set.  These types correspond to the 
		  *             defines set at the top of this header file:
		  *             0 = select
		  *             1 = insert
		  *             2 = update
		  *             3 = delete
		  */
		virtual void SetStmt(twine& stmt, int type);
		virtual void SetStmt(twine* stmt, int type);
		virtual void SetStmt(char* stmt, int type);

		/**
		  * This function is used to validate the syntax of a
		  * statement.  It is equivalent to a call to SetStmt followed
		  * by a call to SQLNumResultCols.  The call to 
		  * SQLNumResultsCols forces the driver to really evaluate the
		  * statement that we prepared and generate any errors that
		  * might be necessary.  Not all drivers will fully parse and
		  * syntax check a statement during the call to SQLPrepare.
		  */
		virtual void ValidateStmt(char* stmt, int type);

		/**
		  * The BindInput method allows the user to bind the
		  * address of a variable to be used for data input to 
		  * the current sql statement.            
		  *
		  * @param pos Position in the sql statment that this variable
		  *            will correspond to.
		  * @param mem The memory location to read the data from.
		  * @param size The size of the data pointed to by mem.
		  * @param type The data type of this variable.
		  */
		virtual void BindInput(int pos, void *mem, int *size, int type);

		virtual void BindInput(int pos, twine& data);

		virtual void BindInput(int pos, MemBuf& data);

		virtual void BindInput(int pos, OdbcDate& data);

		/**
		  * The BindOutput method allows the user to bind the
		  * address of a variable to be used for data output from 
		  * the current sql statement.            
		  *
		  * @param pos Position in the sql statment that this variable
		  *            will correspond to.
		  * @param mem The memory location to read the data from / write
		  *            the data to.
		  * @param size The size of the data pointed to by mem.
		  * @param type The data type of this variable.
		  */
		virtual void BindOutput(int pos, void *mem, int *size, int type);

		virtual void BindOutput(int pos, twine& data);

		virtual void BindOutput(int pos, OdbcDate& data);

		/**
		  * The ExecStmt method does the actual execution 
		  * for the statement defined.  New data should be placed 
		  * in the bound variables prior to each call to this 
		  * method.
		  */
		virtual void ExecStmt(void);

		/**
		  * This returns the number of columns in the current result set.
		  * This is only valid after a call to ExecStmt.
		  */
		virtual int GetResultsetColumnCount(void);

		/** This returns column information for the given column position in
		 * the result set.  This must be called only after ExecStmt has been
		 * called.
		 */
		virtual ColumnInfo GetColumnInfo(int pos);

		/**
		  * This will commit the currently open transaction.
		  * 
		  */
		virtual void Commit(void);

		/**
		  * This will rollback the currently open transaction.
		  * 
		  */
		virtual void Rollback(void);

		/**
		  * This method only works on select statments and handles
		  * the execution of the select statment and the fetch
		  * of the data for that statement.
                  * <P>
                  * The return value here indicates how many rows were
                  * fetched.  When the return is zero, then the statement
                  * has been completely fetched.
		  */
		virtual int FetchData(void);

		/** If you want to pull data from the result set directly, then you
		 * can use this call to retrieve data for a specific column.  This
		 * only works after a call to FetchData.
		 */
		virtual twine GetColumnData(int pos);
		virtual twine GetColumnData(int pos, bool trim);

		/** This will use the SQLGetInfo function to retrieve the odbc driver
		 * version.
		 */
		virtual twine GetDriverVersion(void);

		/**
		  * This converts a SQL column data type into the equivalent name.
		  */
		static twine GetDataTypeName( int sql_data_type );
		
		/**
		  * This escapes a string input by doubling up all single quotes: '
		  */
		static twine EscapeStringInput( const twine& input );
		
		/**
		  * This returns the number of rows affected by an UPDATE, INSERT, or DELETE.
		  * This is only valid after a call to ExecStmt.
		  */
		virtual int GetSQLRowCount(void);

		/**
		  * Allows us to know which session is currently using this database object.
		  */
		virtual void SetSessionInfo(SessionInfo* si);

		/**
		  * Allows the caller to retrieve the current session info for this db object.
		  */
		virtual SessionInfo* GetSessionInfo(void);

	protected:

		/**
		  * The check_err function is used internally to 
		  * convert odbc status errors into exceptions that
		  * will be used by our applications.  This should
		  * encapsulate all of our knowledge of odbc errors.
		  *
		  * @param status This is the return code from the statement
		  *               that we are doing error checking on.
		  * @param htype  This is the handle type that was used in
		  *               the last statment.  We need this for
		  *               diagnostic info lookup.
		  * @param hndl   This is the actual handle that was used in
		  *               the statment.
		  */
		int check_err(SQLRETURN status, SQLSMALLINT htype,
			SQLHANDLE hndl);

		/**
		  * This is where the knowledge of odbc data types
		  * is built into the object.  This will handle the
		  * conversion of datatypes from our generic defines
		  * to odbc specific defines.
		  */
		int dbtype(int type);

		/**
		  * This is another conversion function that produces
		  * Odbc "C" data types.  It is required for some
		  * Odbc api calls.
		  */
		int dbtype2(int type);

		/**
		  * The SanityCheck method simply makes sure of things
		  * like "are we connected?" and "are our variables in
		  * good shape?".
		  */
		void SanityCheck(void);

		/// The text of the current sql statement:
		twine *m_sql_text;

		/// Flag to signal whether we are connected or not:
		int m_connected;

		/// Flag to signal whether we have a statement or not:
		int m_stmt_defined;

		/// Flag to signal what type of statement we have:
		int m_stmt_is_select;

		/// Flag to signal whether we have done the first fetch
		int m_first_fetch_done;

		/// Status of the last ODBC function call.
		SQLRETURN m_last_status;

		/// Odbc environment handle:
		SQLHANDLE m_env_handle;

		/// Odbc connection handle:
		SQLHANDLE m_conn_handle;

		/// Odbc statment handle pointer:
		SQLHANDLE m_statement_handle;

		/// Number of statements we have executed:
		int m_execute_count;

		/// Number of fetches we have performed:
		int m_fetch_count;

		/// Current session info - may be null
		SessionInfo* m_session_info;

};

/** Helper class that makes creating, committing and rolling back a transaction easier
  * to manage by using the scope handling characteristics of the compiler.
  */
class Transaction {
	public:
		Transaction( OdbcObj& odbc ) : m_odbc(odbc)
		{
			m_odbc.SetAutoCommit( false ); // Turn off autocommit while our transaction is active
		}

		virtual ~Transaction() {
			m_odbc.Rollback();
			m_odbc.SetAutoCommit( true ); // Turn on autocomit when we go out of scope
		}

		void Rollback() {
			m_odbc.Rollback();
		}

		void Commit() {
			m_odbc.Commit();
		}

	protected:
		OdbcObj& m_odbc;

};

}} // End Namespace Helix::Glob

#endif //ODBCOBJ_H Defined

