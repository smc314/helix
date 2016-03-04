/* ***************************************************************************

   Copyright (c): 2008 - 2014 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SQLSERVERDBINIT_H
#define SQLSERVERDBINIT_H

#include "ConnectionPool.h"
#include "OdbcObj.h"
#include "TableActions.h"
using namespace Helix::Glob;

#include <Mutex.h>
#include <twine.h>
#include <XmlHelpers.h>
using namespace SLib;

namespace Helix {
namespace Glob {

class DLLEXPORT SqlServerCol {
	public:
		twine name;
		twine column_id;
		twine system_type_id;
		twine max_length;
		twine precision;
		twine scale;
		twine is_nullable;
		twine is_identity;

		void check_size() {
			name.check_size();
			column_id.check_size();
			system_type_id.check_size();
			max_length.check_size();
			precision.check_size();
			scale.check_size();
			is_nullable.check_size();
			is_identity.check_size();
		}

		void erase() {
			name.erase();
			column_id.erase();
			system_type_id.erase();
			max_length.erase();
			precision.erase();
			scale.erase();
			is_nullable.erase();
			is_identity.erase();
		}
};

class DLLEXPORT SqlServerIndex {
	public:
		twine name;
		twine is_primary_key;
		twine is_unique;

		void check_size() {
			name.check_size();
			is_primary_key.check_size();
			is_unique.check_size();
		}

		void erase() {
			name.erase();
			is_primary_key.erase();
			is_unique.erase();
		}
};

class DLLEXPORT SqlServerIndexCol {
	public:
		twine name;
		twine column_id;
		twine is_descending_key;

		void check_size() {
			name.check_size();
			column_id.check_size();
			is_descending_key.check_size();
		}

		void erase() {
			name.erase();
			column_id.erase();
			is_descending_key.erase();
		}
};

class DLLEXPORT SqlServerForeignKey {
	public:
		twine name;
		twine references;
		twine cascade;

		void check_size() {
			name.check_size();
			references.check_size();
			cascade.check_size();
		}

		void erase() {
			name.erase();
			references.erase();
			cascade.erase();
		}
};

class DLLEXPORT SqlServerForeignKeyCol {
	public:
		twine name;
		twine references;

		void check_size() {
			name.check_size();
			references.check_size();
		}

		void erase() {
			name.erase();
			references.erase();
		}
};

/** This class is used to manage the installation and setup of our database schema.  It is
  * designed to find one or more of our database setup xml control files and then for each file,
  * verify that our database is installed, and each table is present with all of the columns,
  * keys, and indexes that we expect to exist.
  *
  * This should be a fast process, so it is safe to run this every time the application starts up.
  */
class DLLEXPORT SqlServerDbInit {

	protected:
		map<twine, TableActions> _setupSummary; 
		sptr<xmlDoc, xmlFreeDoc>  _dbSetup;
		twine _SetupFilesPath;
		twine _targetDbName;
		twine _targetSchema;
		twine _layoutFileName;
		twine _dbUser;
		twine _dbPass;
		OdbcObj* m_odbc;
		Connection* m_connection;
	
	private:
		/// Copy constructor is private to prevent use
		SqlServerDbInit( const SqlServerDbInit& c) {}

		/// Assignment operator is private to prevent use
		SqlServerDbInit& operator=(const SqlServerDbInit& c) { return *this; }

	public:
		/// Standard constructor
		SqlServerDbInit( const twine& dbName );

		/// Standard destructor
		virtual ~SqlServerDbInit();

		/** This method gets us started. We'll look in the current directory for every file ending
		  * with .db.xml, load it and run through it to ensure that every database and table defined
		  * in the file exists with the proper setup in the database.
		  */
		void VerifyInstallSchema();

		void ProcessFile(const twine& fileName);

		void VerifyCreateDatabase();

		void VerifyTable(xmlNodePtr table);

		void CreateTable(xmlNodePtr table);
		twine FormatPrimaryKey(xmlNodePtr table);
		twine FormatForeignKey(xmlNodePtr fk, xmlNodePtr table);
		twine FormatIndex(xmlNodePtr idx, xmlNodePtr table);
		void CreateIndexes(xmlNodePtr table);
		void RunCreateSql(xmlNodePtr table);

		void VerifyTableStructure(xmlNodePtr table);
		void VerifyColumns(xmlNodePtr table);
		void VerifyIndexes(xmlNodePtr table);
		void VerifyForeignKeys(xmlNodePtr table);
		void VerifyPrimaryKey(xmlNodePtr table);

		vector<SqlServerCol> GetColsForTable( twine tableName );
		bool ColumnExists(const vector<SqlServerCol>& cols, const twine& colName);
		bool IndexExists(const twine& indexName);
		bool ForeignKeyExists(const twine& indexName);
	
};

}} // End Namespace Helix::Glob

#endif // SQLSERVERDBINIT_H Defined
