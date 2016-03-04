/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

/* ***************************************************************************
	This is a utility used to dump an existing database schema into the
	format that the Helix Server supports for on-going maintenance.
*************************************************************************** */

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdexcept>

#include <XmlHelpers.h>
#include <AnException.h>
using namespace SLib;

#include <OdbcObj.h>
#include <SqlServerDbInit.h>
using namespace Helix::Glob;

OdbcObj* m_odbc;
vector<pair<twine, twine> > allTables;

void ConnectToDB();
void DumpTables();
void DumpColumns(twine tableName);
void DumpIndexes(twine tableName);
void DumpForeignKeys(twine tableName);
void GetTables();
vector<SqlServerCol> GetColsForTable( twine tableName );
vector<SqlServerCol> GetPKColsForTable( twine tableName );
vector<SqlServerIndex> GetIndexesForTable( twine tableName );
vector<SqlServerIndexCol> GetColumnsForIndex( twine tableName, twine indexName );
vector<SqlServerForeignKey> GetForeignKeysForTable( twine tableName );
vector<SqlServerForeignKeyCol> GetColumnsForForeignKey( twine tableName, twine fkName );
twine FormatType(SqlServerCol col);
twine SysType(twine system_type_id);

int main(int argc, char** argv)
{
	try {
		ConnectToDB();

		DumpTables();

	} catch(AnException& e){
		printf("Error caught: %s", e.Msg() );
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void ConnectToDB()
{
	m_odbc = new OdbcObj( "sa", "sql", "DSN=GalvestonTest1;" );
}

void DumpTables()
{

	printf("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");
	printf("<DatabaseSetup schema=\"dbo\">\n");
	printf("\t<Comment>\n");
	printf("\t\tThis is the setup file that is used to ensure that our physical database is\n");
	printf("\t\tstructured in the way that we expect.  This will be loaded at server startup\n");
	printf("\t\tand will be used to create/modify/remove elements from our database according\n");
	printf("\t\tto it's structure.\n");
	printf("\t</Comment>\n");
	printf("\t<Tables>\n");

	GetTables();
	for(size_t i = 0; i < allTables.size(); i++){
		twine tableName = allTables[i].first;
		twine tableId = allTables[i].second;

		printf("\t\t<Table name=\"%s\">\n", tableName() );
		printf("\t\t\t<Comment>\n");
		printf("\t\t\t\tPut a good comment here about what the table is used for.\n");
		printf("\t\t\t</Comment>\n");
		DumpColumns( tableName );
		DumpIndexes( tableName );
		DumpForeignKeys( tableName );
		printf("\t\t</Table>\n");
		printf("\n");
	}

	printf("\t</Tables>\n");
	printf("</DatabaseSetup>\n");
}

void DumpColumns(twine tableName )
{
	vector<SqlServerCol> cols = GetColsForTable(tableName);
	vector<SqlServerCol> pkcols = GetPKColsForTable(tableName);

	for(size_t i = 0; i < cols.size(); i++){
		bool isPkCol = false;
		for(size_t j = 0; j < pkcols.size(); j++){
			if(cols[i].name == pkcols[j].name){
				isPkCol = true;
				break;
			}
		}
		printf("\t\t\t<Column name=\"%s\" type=\"%s\"\n\t\t\t\tsystype=\"%s\" length=\"%s\" precision=\"%s\" scale=\"%s\" nullable=\"%s\" identity=\"%s\" pk=\"%s\"/>\n",
			cols[i].name(), FormatType(cols[i])(), SysType(cols[i].system_type_id)(),
			cols[i].max_length(), cols[i].precision(), cols[i].scale(), cols[i].is_nullable(),
			cols[i].is_identity(), 
			isPkCol ? "true" : "false"
		);
	}

}

void DumpIndexes(twine tableName )
{
	vector<SqlServerIndex> indexes = GetIndexesForTable(tableName);

	for(size_t i = 0; i < indexes.size(); i++){
		if(indexes[i].is_primary_key == "1"){
			printf("\t\t\t<PrimaryKey clustered=\"true\"/>\n" );
		} else {
			printf("\t\t\t<Index name=\"%s\" unique=\"%s\">\n",
				indexes[i].name(), indexes[i].is_unique()
			);

			vector<SqlServerIndexCol> idxcols = GetColumnsForIndex(tableName, indexes[i].name);
			for(size_t j = 0; j < idxcols.size(); j++){
				printf("\t\t\t\t<Column name=\"%s\" desc=\"%s\"/>\n",
					idxcols[j].name(), idxcols[j].is_descending_key()
				);
			}

			printf("\t\t\t</Index>\n");
		}
	}
}

void DumpForeignKeys(twine tableName )
{
	vector<SqlServerForeignKey> indexes = GetForeignKeysForTable(tableName);

	for(size_t i = 0; i < indexes.size(); i++){
		printf("\t\t\t<ForeignKey name=\"%s\" references=\"%s\" cascade=\"%s\">\n",
			indexes[i].name(), indexes[i].references(), indexes[i].cascade()
		);

		vector<SqlServerForeignKeyCol> idxcols = GetColumnsForForeignKey(tableName, indexes[i].name);
		for(size_t j = 0; j < idxcols.size(); j++){
			printf("\t\t\t\t<Column name=\"%s\" ref=\"%s\"/>\n",
				idxcols[j].name(), idxcols[j].references()
			);
		}

		printf("\t\t\t</ForeignKey>\n");
	}

}

twine FormatType(SqlServerCol col)
{
	twine ret;
	if(col.system_type_id == "56"){
		if(col.is_identity == "1"){
			ret = "int IDENTITY(1,1)";
		} else {
			ret = "int";
		}
	} else if(col.system_type_id == "231"){
		ret = "nvarchar(" + col.max_length + ")";
	} else if(col.system_type_id == "167"){
		ret = "varchar(" + col.max_length + ")";
	} else if(col.system_type_id == "165"){
		ret = "varbinary(" + col.max_length + ")";
	} else if(col.system_type_id == "61"){
		ret = "datetime";
	} else if(col.system_type_id == "43"){
		ret = "datetimeoffset(" + col.scale + ")";
	} else if(col.system_type_id == "106"){
		ret = "decimal(" + col.precision + ", " + col.scale + ")";
	} else if(col.system_type_id == "104"){
		ret = "bit";
	} else {
		ret = "unknown";
	}

	if(col.is_nullable == "1"){
		ret += " null";
	} else {
		ret += " not null";
	}
	return ret;
}

twine SysType(twine system_type_id)
{
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

void GetTables()
{
	twine stmt = "select name, object_id from sys.tables order by name";
	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	twine tableName, tableId;
	m_odbc->BindOutput(1, tableName);
	m_odbc->BindOutput(2, tableId);
	while(m_odbc->FetchData() != 0){
		tableName.check_size();
		tableId.check_size();
		allTables.push_back( pair<twine, twine>(tableName, tableId) );
		tableName.erase();
		tableId.erase();
	}
}

vector<SqlServerCol> GetColsForTable(twine tableName)
{
	vector<SqlServerCol> ret;
	twine stmt = "select sys.columns.name, column_id, system_type_id, max_length, precision, scale, is_nullable, is_identity "
		"from sys.columns, sys.tables "
		"where sys.tables.object_id = sys.columns.object_id "
		"and sys.tables.name = '" + tableName + "' "
		"order by sys.columns.column_id";

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

vector<SqlServerCol> GetPKColsForTable(twine tableName)
{
	vector<SqlServerCol> ret;
	twine stmt = 
		"select sys.index_columns.column_id, sys.columns.name "
		"from sys.columns, sys.index_columns, sys.indexes, sys.tables "
		"where sys.indexes.object_id = sys.index_columns.object_id "
		"and sys.indexes.index_id = sys.index_columns.index_id "
		"and sys.indexes.object_id = sys.columns.object_id "
		"and sys.index_columns.column_id = sys.columns.column_id "
		"and sys.indexes.is_primary_key = 1 "
		"and sys.indexes.object_id = sys.tables.object_id "
		"and sys.tables.name = '" + tableName + "' "
		"order by sys.index_columns.key_ordinal "
	;

	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	SqlServerCol binder;
	m_odbc->BindOutput(1, binder.column_id);
	m_odbc->BindOutput(2, binder.name);

	while(m_odbc->FetchData() != 0){
		binder.check_size();
		SqlServerCol row;
		row.name = binder.name;
		row.column_id = binder.column_id;

		ret.push_back(row);
		binder.erase();
	}

	return ret;
}

vector<SqlServerIndex> GetIndexesForTable( twine tableName )
{
	vector<SqlServerIndex> ret;
	twine stmt = 
		"select sys.indexes.name, sys.indexes.is_primary_key, sys.indexes.is_unique "
		"from sys.tables, sys.indexes "
		"where sys.tables.object_id = sys.indexes.object_id "
		"and sys.tables.name = '" + tableName + "' "
	;

	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	SqlServerIndex binder;
	m_odbc->BindOutput(1, binder.name);
	m_odbc->BindOutput(2, binder.is_primary_key);
	m_odbc->BindOutput(3, binder.is_unique);

	while(m_odbc->FetchData() != 0){
		binder.check_size();
		SqlServerIndex row;
		row.name = binder.name;
		row.is_primary_key = binder.is_primary_key;
		row.is_unique = binder.is_unique;

		ret.push_back(row);
		binder.erase();
	}

	return ret;
}

vector<SqlServerIndexCol> GetColumnsForIndex( twine tableName, twine indexName )
{
	vector<SqlServerIndexCol> ret;
	twine stmt = 
		"select sys.index_columns.column_id, sys.columns.name, sys.index_columns.is_descending_key "
		"from sys.columns, sys.index_columns, sys.indexes, sys.tables "
		"where sys.indexes.object_id = sys.index_columns.object_id "
		"and sys.indexes.index_id = sys.index_columns.index_id "
		"and sys.indexes.object_id = sys.columns.object_id "
		"and sys.index_columns.column_id = sys.columns.column_id "
		"and sys.indexes.object_id = sys.tables.object_id "
		"and sys.tables.name = '" + tableName + "' "
		"and sys.indexes.name = '" + indexName + "' "
		"order by sys.index_columns.key_ordinal "
	;

	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	SqlServerIndexCol binder;
	m_odbc->BindOutput(1, binder.column_id);
	m_odbc->BindOutput(2, binder.name);
	m_odbc->BindOutput(3, binder.is_descending_key);

	while(m_odbc->FetchData() != 0){
		binder.check_size();
		SqlServerIndexCol row;
		row.name = binder.name;
		row.column_id = binder.column_id;
		row.is_descending_key = binder.is_descending_key;

		ret.push_back(row);
		binder.erase();
	}

	return ret;
}

vector<SqlServerForeignKey> GetForeignKeysForTable( twine tableName )
{
	vector<SqlServerForeignKey> ret;
	twine stmt = 
		"select sys.foreign_keys.name, referenced.name,	delete_referential_action "
		"from sys.foreign_keys, sys.tables parent, sys.tables referenced "
		"where sys.foreign_keys.parent_object_id = parent.object_id "
		"and sys.foreign_keys.referenced_object_id = referenced.object_id "
		"and parent.name = '" + tableName + "' "
	;

	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	SqlServerForeignKey binder;
	m_odbc->BindOutput(1, binder.name);
	m_odbc->BindOutput(2, binder.references);
	m_odbc->BindOutput(3, binder.cascade);

	while(m_odbc->FetchData() != 0){
		binder.check_size();
		SqlServerForeignKey row;
		row.name = binder.name;
		row.references = binder.references;
		row.cascade = binder.cascade;

		ret.push_back(row);
		binder.erase();
	}

	return ret;
}

vector<SqlServerForeignKeyCol> GetColumnsForForeignKey( twine tableName, twine fkName )
{
	vector<SqlServerForeignKeyCol> ret;
	twine stmt = 
		"select parentcols.name, referencedcols.name "
		"from sys.foreign_keys, sys.tables parent, sys.foreign_key_columns, sys.columns parentcols, sys.columns referencedcols "
		"where sys.foreign_keys.object_id = sys.foreign_key_columns.constraint_object_id "
		"and sys.foreign_key_columns.parent_object_id = parent.object_id "
		"and sys.foreign_key_columns.parent_object_id = parentcols.object_id "
		"and sys.foreign_key_columns.parent_column_id = parentcols.column_id "
		"and sys.foreign_key_columns.referenced_object_id = referencedcols.object_id "
		"and sys.foreign_key_columns.referenced_column_id = referencedcols.column_id "
		"and parent.name = '" + tableName + "' "
		"and sys.foreign_keys.name = '" + fkName + "' "
	;

	m_odbc->SetStmt( stmt, SQL_TYPE_SELECT );
	m_odbc->ExecStmt();

	SqlServerForeignKeyCol binder;
	m_odbc->BindOutput(1, binder.name);
	m_odbc->BindOutput(2, binder.references);

	while(m_odbc->FetchData() != 0){
		binder.check_size();
		SqlServerForeignKeyCol row;
		row.name = binder.name;
		row.references = binder.references;

		ret.push_back(row);
		binder.erase();
	}

	return ret;
}

