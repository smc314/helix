/* ***************************************************************************

   Copyright (c): 2008 - 2014 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "SqlServerDbInit.h"
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

SqlServerDbInit::SqlServerDbInit( const twine& dbName )
{
	EnEx ee(FL, "SqlServerDbInit::SqlServerDbInit()");
	
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

SqlServerDbInit::SqlServerDbInit( const twine& dbName, const twine& targetDbName, const twine& layoutFile,
	const twine& user, const twine& pass, OdbcObj* odbc)
{
	EnEx ee(FL, "SqlServerDbInit::SqlServerDbInit(const twine& dbName, const twine& targetDbName, const twine& layoutFile, const twine& user, const twine& pass, OdbcObj* odbc)");

	_targetDbName = targetDbName;
	_layoutFileName = layoutFile;
	_dbUser = user;
	_dbPass = pass;
	m_connection = NULL;
	m_odbc = odbc;

}

SqlServerDbInit::~SqlServerDbInit()
{
	EnEx ee(FL, "SqlServerDbInit::~SqlServerDbInit()");

	if(m_connection != NULL){
		m_connection->release(); // release it back to the pool
	}
	m_connection = NULL;
	m_odbc = NULL;
}

void SqlServerDbInit::VerifyInstallSchema()
{
	EnEx ee(FL, "SqlServerDbInit::VerifyInstallSchema()");

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

void SqlServerDbInit::ProcessFile( const twine& fileName )
{
	EnEx ee(FL, "SqlServerDbInit::ProcessFile()");
	_dbSetup = xmlParseFile( fileName() );

	xmlNodePtr root = xmlDocGetRootElement( _dbSetup );
	_layoutRoot = root;
	_targetSchema.getAttribute(root, "schema");
	if(_targetSchema.length() == 0){
		_targetSchema = "dbo";
	}
	VerifyCreateDatabase();

	xmlNodePtr tables_node = XmlHelpers::FindChild(root, "Tables");
	vector<xmlNodePtr> tables = XmlHelpers::FindChildren(tables_node, "Table");
	for(size_t i = 0; i < tables.size(); i++){
		VerifyTable(tables[i]);	
	}
}

void SqlServerDbInit::VerifyCreateDatabase()
{
	EnEx ee(FL, "SqlServerDbInit::VerifyCreateDatabase()");

	// Get a list of existing databases:
	twine stmt = "select name, database_id from sys.databases where name like '%" + _targetDbName + "%'";
	twine dbName;
	twine dbId;
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	m_odbc->BindOutput(1, dbName);
	m_odbc->BindOutput(2, dbId);

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
	stmt = "create database [" + _targetDbName + "] collate SQL_Latin1_General_CP1_CS_AS";
	INFO(FL, "Creating new database [%s]", _targetDbName() );
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
	m_odbc->ExecStmt();

	stmt = "use " + _targetDbName;
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
	m_odbc->ExecStmt();
}

void SqlServerDbInit::VerifyTable(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::VerifyTable(xmlNodePtr table)");

	twine tableName(table, "name");
	twine stmt = "select name, object_id from sys.tables where name like '%" + tableName + "%'";

	twine tabName;
	twine tabId;
	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	m_odbc->BindOutput(1, tabName);
	m_odbc->BindOutput(2, tabId);

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

xmlNodePtr SqlServerDbInit::FindTable(const twine& tableName)
{
	EnEx ee(FL, "SqlServerDbInit::CreateTable(xmlNodePtr table)");

	xmlNodePtr tables_node = XmlHelpers::FindChild(_layoutRoot, "Tables");
	vector<xmlNodePtr> tables = XmlHelpers::FindChildren(tables_node, "Table");
	for(size_t i = 0; i < tables.size(); i++){
		twine name(tables[i], "name");
		if(name == tableName){
			return tables[i];
		}
	}
	return NULL;
}

void SqlServerDbInit::CreateTable(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::CreateTable(xmlNodePtr table)");

	twine tableName(table, "name");
	twine stmt;
	stmt.format("Create Table [%s].[%s] (\n", _targetSchema(), tableName());
	twine pkStmt = "";

	vector<xmlNodePtr> cols = XmlHelpers::FindChildren( table, "Column" );
	for(size_t i = 0; i < cols.size(); i++){
		twine colName(cols[i], "name");
		twine colType = FormatType(cols[i]);
		bool pk = XmlHelpers::getBoolAttr(cols[i], "pk");
		bool colDelete = XmlHelpers::getBoolAttr(cols[i], "delete");
		if(colDelete) continue; // skip these
		twine colFormat;
		colFormat.format("\t[%s] %s,\n", colName(), colType() );
		stmt += colFormat;
	}

	stmt += FormatPrimaryKey( table );

	// Handle Foreign Keys
	vector<xmlNodePtr> foreignKeys = XmlHelpers::FindChildren( table, "ForeignKey" );
	for(size_t i = 0; i < foreignKeys.size(); i++){
		stmt += "\t, " + FormatForeignKey( foreignKeys[i], table );

		// Find the foreign table that this references, and ensure that it is set up first
		twine fkTableName(foreignKeys[i], "references");
		VerifyTable( FindTable( fkTableName ) );
	}

	stmt += ")\n"; // End the create table statement


	SQLTRACE(FL, "%s", stmt() );
	INFO(FL, "Creating new table [%s].[%s]", _targetSchema(), tableName() );
	m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
	m_odbc->ExecStmt();

	// Handle Indexes
	CreateIndexes(table);

	RunCreateSql(table);

}

twine SqlServerDbInit::FormatPrimaryKey(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::FormatPrimaryKey(xmlNodePtr table)");

	twine tableName( table, "name" );
	twine pk;
	pk.format("\tCONSTRAINT [PK_%s.%s] PRIMARY KEY ", _targetSchema(), tableName() );
	
	xmlNodePtr pkElement = XmlHelpers::FindChild( table, "PrimaryKey" );
	if(pkElement != NULL){
		if(XmlHelpers::getBoolAttr( pkElement, "clustered" ) ){
			pk += "CLUSTERED";
		}
	}
	pk += "\n\t(\n";

	vector<xmlNodePtr> cols = XmlHelpers::FindChildren( table, "Column");
	for(size_t i = 0; i < cols.size(); i++){
		if(XmlHelpers::getBoolAttr(cols[i], "delete")) continue; // Skip deleted columns
		if(XmlHelpers::getBoolAttr(cols[i], "pk") != true) continue; // Skip non-primary key columns
		twine colName( cols[i], "name" );
		twine pkOptions( cols[i], "pkoptions" );
		twine tmp;
		if(i == 0){
			tmp.format("\t\t[%s] %s\n", colName(), pkOptions() );
		} else {
			tmp.format("\t\t,[%s] %s\n", colName(), pkOptions() );
		}
		pk += tmp;
	}
	pk += "\t)\n";

	return pk;
}

twine SqlServerDbInit::FormatForeignKey(xmlNodePtr fk, xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::FormatForeignKey(xmlNodePtr fk, xmlNodePtr table)");

	twine fkName( fk, "name");
	twine fkTableRef( fk, "references");
	bool fkCascade = XmlHelpers::getBoolAttr(fk, "cascade");
	twine fkSql;
	twine constraint;
	twine references;
	twine tmp, tmp2;
	constraint.format("\tCONSTRAINT [%s] FOREIGN KEY\n\t(\n\t\t ", fkName() );
	references.format("\n\t)\n\tREFERENCES [%s]\n\t(\n\t\t", fkTableRef() );
	
	vector<xmlNodePtr> cols = XmlHelpers::FindChildren( fk, "Column" );
	for(size_t i = 0; i < cols.size(); i++){
		twine colName( cols[i], "name" );
		twine colRef( cols[i], "ref" );
		if(i == 0){
			tmp.format("[%s]", colName() );
			tmp2.format("[%s]", colRef.length() > 0 ? colRef() : colName() );
		} else {
			tmp.format(", [%s]", colName() );
			tmp2.format(", [%s]", colRef.length() > 0 ? colRef() : colName() );
		}
		constraint += tmp;
		references += tmp2;
	}

	if(fkCascade){
		fkSql = constraint + references + "\n\t) on delete cascade\n";
	} else {
		fkSql = constraint + references + "\n\t) on delete no action\n";
	}

	return fkSql;
}

twine SqlServerDbInit::FormatIndex(xmlNodePtr idx, xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::FormatIndex(xmlNodePtr idx, xmlNodePtr table)");

	twine tableName( table, "name" );
	twine ixName(idx, "name");
	bool isUnique = XmlHelpers::getBoolAttr(idx, "unique");
	twine uniqueClause = isUnique ? "unique" : "";

	twine stmt = "";
	vector<xmlNodePtr> indexCols = XmlHelpers::FindChildren( idx, "Column" );
	for(size_t j = 0; j < indexCols.size(); j++){
		twine idxColName(indexCols[j], "name");
		bool desc = XmlHelpers::getBoolAttr( indexCols[j], "desc" );

		if(stmt.length() == 0){
			stmt = "create " + uniqueClause + " index [" + ixName + "] on [" + tableName + "] (" +
				idxColName;
		} else {
			stmt = stmt + ", " + idxColName;
		}
		if(desc){
			stmt += " DESC";
		} else {
			stmt += " ASC";
		}
	}
	stmt = stmt + ")";

	return stmt;
}

void SqlServerDbInit::CreateIndexes(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::CreateIndexes(xmlNodePtr table)");

	twine tableName(table, "name");
	vector<xmlNodePtr> indexes = XmlHelpers::FindChildren( table, "Index" );
	for(size_t i = 0; i < indexes.size(); i++){
		twine stmt = FormatIndex(indexes[i], table);

		SQLTRACE(FL, "%s", stmt() );
		INFO(FL, "Creating index %s", stmt() );
		m_odbc->SetStmt( stmt, SQL_TYPE_INSERT );
		m_odbc->ExecStmt();
	}
}

void SqlServerDbInit::RunCreateSql(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::RunCreateSql(xmlNodePtr table)");

	xmlNodePtr createSqlNode = XmlHelpers::FindChild(table, "SqlCreate");
	if(createSqlNode == NULL){
		return; // nothing to do
	}

	twine stmts = XmlHelpers::getTextNodeValue( createSqlNode );

	vector<twine> stmt_vect = stmts.split(";");
	for(size_t i = 0; i < stmt_vect.size(); i++){
		if(stmt_vect[i].ltrim().rtrim().length() != 0){
			SQLTRACE(FL, "%s", stmt_vect[i]() );
			INFO(FL, "Running post-create sql");
			m_odbc->SetStmt( stmt_vect[i], SQL_TYPE_INSERT );
			m_odbc->ExecStmt();
			m_odbc->Commit();
		}
	}
}

void SqlServerDbInit::VerifyTableStructure(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::VerifyTableStructure(xmlNodePtr table)");

	// Verify Columns
	VerifyColumns( table );

	// Verify Indexes
	VerifyIndexes( table );

	// Verify Foreign Keys
	VerifyForeignKeys( table );

	// Verify Primary Key
	VerifyPrimaryKey( table );

}

vector<SqlServerCol> SqlServerDbInit::GetColsForTable(twine tableName)
{
	EnEx ee(FL, "SqlServerDbInit::GetColsForTable(table tableName)");

	vector<SqlServerCol> ret;
	twine stmt = "select sys.columns.name, column_id, system_type_id, max_length, precision, scale, is_nullable, is_identity "
		"from sys.columns, sys.tables "
		"where sys.tables.object_id = sys.columns.object_id "
		"and sys.tables.name = '" + tableName + "' "
		"order by sys.columns.column_id";

	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	SqlServerCol binder;
	m_odbc->BindOutput(1, binder.name);
	m_odbc->BindOutput(2, binder.column_id);
	m_odbc->BindOutput(3, binder.system_type_id);
	m_odbc->BindOutput(4, binder.max_length);
	m_odbc->BindOutput(5, binder.precision);
	m_odbc->BindOutput(6, binder.scale);
	m_odbc->BindOutput(7, binder.is_nullable);
	m_odbc->BindOutput(8, binder.is_identity);

	while(m_odbc->FetchData() != 0){
		binder.check_size();
		SqlServerCol row;
		row.name = binder.name;
		row.column_id = binder.column_id;
		row.system_type_id = binder.system_type_id;
		row.max_length = binder.max_length;
		row.precision = binder.precision;
		row.scale = binder.scale;
		row.is_nullable = binder.is_nullable;
		row.is_identity = binder.is_identity;

		ret.push_back(row);
		binder.erase();
	}

	return ret;
}

SqlServerCol* SqlServerDbInit::ColumnExists(vector<SqlServerCol>& cols, const twine& colName)
{
	for(size_t j = 0; j < cols.size(); j++){
		if(cols[j].name == colName){
			return &cols[j]; // found it
		}
	}
	return NULL; // Didn't find it
}


void SqlServerDbInit::VerifyColumns(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::VerifyColumns(xmlNodePtr table)");

	twine tableName(table, "name");

	// Get a list of existing columns for our table:
	vector<SqlServerCol> cols = GetColsForTable( tableName );

	// Get the list of columns from our XML
	vector<xmlNodePtr> xmlCols = XmlHelpers::FindChildren( table, "Column" );

	// Run through the list of columns that should be deleted
	for(size_t i = 0; i < xmlCols.size(); i++){
		twine colName(xmlCols[i], "name");
		bool toDelete = XmlHelpers::getBoolAttr(xmlCols[i], "delete");
		// Delete if the col exists
		if(toDelete && (ColumnExists(cols, colName) != NULL)){
			twine dropCommand;
			dropCommand.format("ALTER TABLE [%s] DROP COLUMN [%s]", tableName(), colName() );

			SQLTRACE(FL, "%s", dropCommand() );
			INFO(FL, "Dropping table column: [%s].[%s]", tableName(), colName() );
			m_odbc->SetStmt( dropCommand, SQL_TYPE_SELECT );
			m_odbc->ExecStmt();
		}
	}

	// Refresh our metadata:
	cols = GetColsForTable( tableName );

	// Run through the list of columns that should be there
	for(size_t i = 0; i < xmlCols.size(); i++){
		twine colName(xmlCols[i], "name");
		twine colType = FormatType(xmlCols[i]);
		bool toDelete = XmlHelpers::getBoolAttr(xmlCols[i], "delete");
		if(toDelete) continue; // Skip deleted columns
		SqlServerCol* sqlCol = ColumnExists(cols, colName);
		if(sqlCol == NULL){
			twine addCommand;
			addCommand.format("ALTER TABLE [%s] ADD [%s] %s", tableName(), colName(), colType() );

			SQLTRACE(FL, "%s", addCommand() );
			INFO(FL, "Adding table column: [%s].[%s]", tableName(), colName() );
			m_odbc->SetStmt( addCommand, SQL_TYPE_SELECT );
			m_odbc->ExecStmt();
		} else {
			// Column exists, verify structure
			twine systype(xmlCols[i], "systype");
			twine length(xmlCols[i], "length");
			twine precision(xmlCols[i], "precision");
			twine scale(xmlCols[i], "scale");
			twine nullable(xmlCols[i], "nullable");
			if(SysType(sqlCol->system_type_id) != systype ||
				sqlCol->max_length != length ||
				sqlCol->precision != precision ||
				sqlCol->scale != scale ||
				sqlCol->is_nullable != nullable
			){
				twine alterCommand;
				alterCommand.format("ALTER TABLE [%s] ALTER COLUMN [%s] %s", tableName(), colName(), colType() );

				SQLTRACE(FL, "%s", alterCommand() );
				INFO(FL, "Altering table column: [%s].[%s]", tableName(), colName() );
				m_odbc->SetStmt( alterCommand, SQL_TYPE_SELECT );
				m_odbc->ExecStmt();
			}
		}
	}
}

void SqlServerDbInit::VerifyIndexes(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::VerifyIndexes(xmlNodePtr table)");

	twine tableName(table, "name");

	// Get the list of indexes from our XML
	vector<xmlNodePtr> xmlIndexes = XmlHelpers::FindChildren( table, "Index" );

	// Run through the list of indexes that should be deleted
	for(size_t i = 0; i < xmlIndexes.size(); i++){
		twine idxName(xmlIndexes[i], "name");
		bool toDelete = XmlHelpers::getBoolAttr(xmlIndexes[i], "delete");
		// Delete if the index exists
		if(toDelete && IndexExists(idxName)){
			twine dropCommand;
			dropCommand.format("DROP INDEX [%s] ON [%s]", idxName(), tableName() );

			SQLTRACE(FL, "%s", dropCommand() );
			INFO(FL, "Dropping Index [%s].[%s]", tableName(), idxName() );
			m_odbc->SetStmt( dropCommand, SQL_TYPE_SELECT );
			m_odbc->ExecStmt();
		}
	}

	// Run through the list of indexes that should be there
	for(size_t i = 0; i < xmlIndexes.size(); i++){
		twine idxName(xmlIndexes[i], "name");
		bool toDelete = XmlHelpers::getBoolAttr(xmlIndexes[i], "delete");
		if(toDelete) continue; // Skip deleted indexes
		if(IndexExists(idxName) == false){
			twine addCommand = FormatIndex( xmlIndexes[i], table );

			SQLTRACE(FL, "%s", addCommand() );
			INFO(FL, "Adding index [%s]", idxName() );
			m_odbc->SetStmt( addCommand, SQL_TYPE_SELECT );
			m_odbc->ExecStmt();
		} else {
			// Index exists, verify structure

		}
	}
}

bool SqlServerDbInit::IndexExists(const twine& indexName)
{
	EnEx ee(FL, "SqlServerDbInit::IndexExists(const twine& indexName)");

	twine stmt = "select name from sys.indexes where name = '" + indexName + "'";

	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	twine name;
	m_odbc->BindOutput(1, name);

	while(m_odbc->FetchData() != 0){
		name.check_size();
		return true; // Found it
	}

	return false; // Not in the DB
}


void SqlServerDbInit::VerifyForeignKeys(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::VerifyForeignKeys(xmlNodePtr table)");

	twine tableName(table, "name");

	// Get the list of indexes from our XML
	vector<xmlNodePtr> xmlIndexes = XmlHelpers::FindChildren( table, "ForeignKey" );

	// Run through the list of indexes that should be deleted
	for(size_t i = 0; i < xmlIndexes.size(); i++){
		twine idxName(xmlIndexes[i], "name");
		bool toDelete = XmlHelpers::getBoolAttr(xmlIndexes[i], "delete");
		// Delete if the index exists
		if(toDelete && ForeignKeyExists(idxName)){
			twine dropCommand;
			dropCommand.format("ALTER TABLE [%s] DROP CONSTRAINT [%s]", tableName(), idxName() );

			SQLTRACE(FL, "%s", dropCommand() );
			INFO(FL, "Dropping foreign key [%s].[%s]", tableName(), idxName() );
			m_odbc->SetStmt( dropCommand, SQL_TYPE_SELECT );
			m_odbc->ExecStmt();
		}
	}

	// Run through the list of indexes that should be there
	for(size_t i = 0; i < xmlIndexes.size(); i++){
		twine idxName(xmlIndexes[i], "name");
		bool toDelete = XmlHelpers::getBoolAttr(xmlIndexes[i], "delete");
		if(toDelete) continue; // Skip deleted indexes
		if(ForeignKeyExists(idxName) == false){
			twine addCommand;
			addCommand.format("ALTER TABLE [%s] ADD %s", tableName(), FormatForeignKey( xmlIndexes[i], table )() );

			SQLTRACE(FL, "%s", addCommand() );
			INFO(FL, "Adding foreign key [%s].[%s]", tableName(), idxName() );
			m_odbc->SetStmt( addCommand, SQL_TYPE_SELECT );
			m_odbc->ExecStmt();
		} else {
			// Index exists, verify structure

		}
	}
}

bool SqlServerDbInit::ForeignKeyExists(const twine& indexName)
{
	EnEx ee(FL, "SqlServerDbInit::ForeignKeyExists(const twine& indexName)");

	twine stmt = "select name from sys.foreign_keys where name = '" + indexName + "'";

	SQLTRACE(FL, "%s", stmt() );
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	twine name;
	m_odbc->BindOutput(1, name);

	while(m_odbc->FetchData() != 0){
		name.check_size();
		return true; // Found it
	}

	return false; // Not in the DB
}

void SqlServerDbInit::VerifyPrimaryKey(xmlNodePtr table)
{
	EnEx ee(FL, "SqlServerDbInit::VerifyPrimaryKey(xmlNodePtr table)");

}

twine SqlServerDbInit::FormatType(xmlNodePtr col)
{
	EnEx ee(FL, "SqlServerDbInit::FormatType(xmlNodePtr col)");

	twine systype(col, "systype");
	twine length(col, "length");
	twine precision(col, "precision");
	twine scale(col, "scale");
	bool isNullable = XmlHelpers::getBoolAttr(col, "nullable");
	bool isIdentity = XmlHelpers::getBoolAttr(col, "identity");

	twine ret;
	if(systype == "int"){
		if(isIdentity){
			ret = "int IDENTITY(1,1)";
		} else {
			ret = "int";
		}
	} else if(systype == "nvarchar"){
		ret = "nvarchar(" + length + ")";
	} else if(systype == "varchar"){
		ret = "varchar(" + length + ")";
	} else if(systype == "varbinary"){
		if(length == "-1"){
			ret = "varbinary(max)";
		} else {
			ret = "varbinary(" + length + ")";
		}
	} else if(systype == "datetime"){
		ret = "datetime";
	} else if(systype == "datetimeoffset"){
		ret = "datetimeoffset(" + scale + ")";
	} else if(systype == "decimal"){
		ret = "decimal(" + precision + ", " + scale + ")";
	} else if(systype == "bit"){
		ret = "bit";
	} else {
		ret = "unknown";
	}

	if(isNullable){
		ret += " null";
	} else {
		ret += " not null";
	}
	return ret;
}

twine SqlServerDbInit::SysType(const twine& system_type_id)
{
	EnEx ee(FL, "SqlServerDbInit::SysType(const twine& system_type_id)");

	if(system_type_id == "56"){
		return "int";
	} else if(system_type_id == "231"){
		return "nvarchar";
	} else if(system_type_id == "167"){
		return "varchar";
	} else if(system_type_id == "165"){
		return "varbinary";
	} else if(system_type_id == "61"){
		return "datetime";
	} else if(system_type_id == "43"){
		return "datetimeoffset";
	} else if(system_type_id == "106"){
		return "decimal";
	} else if(system_type_id == "104"){
		return "bit";
	} else {
		return "unknown";
	}
}


