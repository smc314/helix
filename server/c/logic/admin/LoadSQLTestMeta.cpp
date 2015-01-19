/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "LoadSQLTestMeta.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "SQLTests.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<LoadSQLTestMeta> LoadSQLTestMeta::reg("LoadSQLTestMeta", 1, "/logic/admin/LoadSQLTestMeta");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/admin/LoadSQLTestMeta Input=SQLTests

LoadSQLTestMeta::LoadSQLTestMeta(xmlNodePtr action)
{
	EnEx ee(FL, "LoadSQLTestMeta::LoadSQLTestMeta(xmlNodePtr action)");
	m_odbc = NULL;
	m_Tests = NULL;
}

LoadSQLTestMeta::LoadSQLTestMeta(const LoadSQLTestMeta& c)
{
	EnEx ee(FL, "LoadSQLTestMeta::LoadSQLTestMeta(const LoadSQLTestMeta& c)");
	m_odbc = NULL;
	m_Tests = NULL;

}

LoadSQLTestMeta& LoadSQLTestMeta::operator=(const LoadSQLTestMeta& c)
{
	EnEx ee(FL, "LoadSQLTestMeta::operator=(const LoadSQLTestMeta& c)");
	m_odbc = NULL;
	m_Tests = NULL;

	return *this;
}

LoadSQLTestMeta::~LoadSQLTestMeta()
{
	EnEx ee(FL, "LoadSQLTestMeta::~LoadSQLTestMeta()");
	if(m_odbc != NULL){
		delete m_odbc;
		m_odbc = NULL;
	}
	if(m_Tests != NULL){
		delete m_Tests;
		m_Tests = NULL;
	}
}

void LoadSQLTestMeta::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "LoadSQLTestMeta::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("LoadSQLTestMeta");

	m_Tests = new SQLTests( XmlHelpers::FindChild( ioc.GetRequestRoot(), SQLTests::Name()() ) );

	// Run through every selected test:
	LoopSqlStatements();
	
	// When done, send everything back to the caller
	m_Tests->createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}

void LoadSQLTestMeta::Disconnect()
{
	EnEx ee(FL, "LoadSQLTestMeta::Disconnect()");

	if(m_odbc != NULL){
		delete m_odbc;
		m_odbc = NULL;
	}
}

void LoadSQLTestMeta::Connect()
{
	EnEx ee(FL, "LoadSQLTestMeta::Connect()");

	// Ensure that we are not connected:
	Disconnect();

	// Connect to the database
	twine connStr = "DRIVER={ViaSQL Direct ODBC Driver (tcp/ip)};"
		"SRV=" + m_Tests->host + "/" + m_Tests->port + "/lds;UID=" + m_Tests->user + ";PWD=" +
		m_Tests->pass + ";";
	m_odbc = new OdbcObj(m_Tests->user, m_Tests->pass, connStr);

	DEBUG(FL, "Driver Version: %s", m_odbc->GetDriverVersion()() );
}

void LoadSQLTestMeta::LoopSqlStatements()
{
	EnEx ee(FL, "LoadSQLTestMeta::LoopSqlStatements()");

	Connect();
	for(size_t i = 0; i < m_Tests->SQLStatements->size(); i++){
		SQLStmt* stmt = m_Tests->SQLStatements->at( i ) ;
		if(stmt->isSelected == 1){
			RunSqlTest( m_Tests->SQLStatements->at( i ) );
		}
	}
}

void LoadSQLTestMeta::RunSqlTest(SQLStmt* stmt)
{
	EnEx ee(FL, "LoadSQLTestMeta::RunSqlTest()");

	DEBUG(FL, "Loading metadata and results for test %s", stmt->StatementName() );
	if(stmt->newConnection == 1){
		Connect();
	}

	// Prepare and set the statment:
	m_odbc->SetStmt( stmt->stmt, SQL_TYPE_SELECT );

	if(stmt->ignoreErrors){
		// An error may or may not happen.  Ignore it if it does.
		try {
			m_odbc->ExecStmt();
			CaptureMetadata( stmt );
			CaptureResults( stmt );
		} catch (AnException& e){
			// ignore this.
		}
	} else if(stmt->expectErrors){
		// We expect an error to happen.  Capture the text of the error.
		try {
			m_odbc->ExecStmt();
			// No error - just set the error message to blank.
			stmt->expectedErrorMsg = "";
		} catch (AnException& e){
			stmt->expectedErrorMsg = e.Msg();
		}
	} else {
		// We expect the statement to go through just fine
		try {
			m_odbc->ExecStmt();
			CaptureMetadata( stmt );
			CaptureResults( stmt );
		} catch ( AnException& e) {

		}
	}

}

void LoadSQLTestMeta::CaptureMetadata(SQLStmt* stmt)
{
	EnEx ee(FL, "LoadSQLTestMeta::CaptureMetadata()");

	int columns = m_odbc->GetResultsetColumnCount();
	stmt->MetaData = new vector<Col*>();
	for(int i = 1; i <= columns; i++){
		ColumnInfo ci = m_odbc->GetColumnInfo( i );
		dptr<Col> c = new Col();
		c->idx = i ;
		c->colName = ci.name;
		c->verifyData = 1;
		c->typeName = OdbcObj::GetDataTypeName( ci.dbtype );

		stmt->MetaData->push_back( c.release() );
	}
}

void LoadSQLTestMeta::CaptureResults(SQLStmt* stmt)
{
	EnEx ee(FL, "LoadSQLTestMeta::CaptureResults()");

	int columns = m_odbc->GetResultsetColumnCount();
	stmt->Results = new vector<Row*>();

	int rowCount = 0;
	while(m_odbc->FetchData() != 0){
		dptr<Row> row = new Row();		
		row->idx = rowCount ++;

		row->Cols = new vector<Col*>();
		for(int i = 1; i <= columns; i++){
			ColumnInfo ci = m_odbc->GetColumnInfo( i );
			dptr<Col> c = new Col();
			c->idx = i ;
			c->colName = ci.name;
			c->verifyData = 1;
			c->typeName = OdbcObj::GetDataTypeName( ci.dbtype );
			c->dataValue = m_odbc->GetColumnData( i, false );	
			row->Cols->push_back( c.release() );
		}

		stmt->Results->push_back( row.release() );
	}

}
