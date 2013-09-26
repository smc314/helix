/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SQLDB_H
#define SQLDB_H

#include "OdbcObj.h"
using namespace Helix::Glob;

#include <Mutex.h>
#include <twine.h>
#include <XmlHelpers.h>
#include <sqlite3.h>
using namespace SLib;

namespace Helix {
namespace Glob {

class TableActions {
	public:

		/// Standard Constructor
		TableActions(const twine& Name);

		/// Copy Constructor
		TableActions(const TableActions& c);

		/// Assignment operator
		TableActions& operator=(const TableActions& c);

		/// Standard Destructor
		virtual ~TableActions();

		/// Which table are we working with
		twine TableName;

		/// Did we create it
		bool Created;

		/// Did we update it
		bool Updated;
};

/** This class is used to manage the installation and setup of our database schema.  It is
  * designed to find one or more of our database setup xml control files and then for each file,
  * verify that our database is installed, and each table is present with all of the columns,
  * keys, and indexes that we expect to exist.
  *
  * This should be a fast process, so it is safe to run this every time the application starts up.
  */
class SqlDB {

	protected:
		map<twine, TableActions> _setupSummary; 
		sptr<xmlDoc, xmlFreeDoc>  _dbSetup;
		twine m_dbLayout;
		twine m_dbName;
		size_t m_db_max_size;
		Mutex* m_mutex;
		sqlite3* m_db;
		sqlite3_stmt* m_stmt;
	
	private:
		/// Copy constructor is private to prevent use
		SqlDB( const SqlDB& c) {}

		/// Assignment operator is private to prevent use
		SqlDB& operator=(const SqlDB& c) { return *this; }

	public:
		/// Standard constructor
		SqlDB(xmlNodePtr db);

		/// Use this to manually pass in our intitialization parameters
		SqlDB(const twine& layoutFile, const twine& dbFile, size_t maxSize );

		/// Standard destructor
		virtual ~SqlDB();

		/** This method gets us started. We'll look in the current directory for every file ending
		  * with .db.xml, load it and run through it to ensure that every database and table defined
		  * in the file exists with the proper setup in the database.
		  */
		void VerifyInstallSchema();

		void ProcessFile(const twine& fileName);

		void VerifyCreateDatabase();

		void VerifyTable(xmlNodePtr table);

		void CreateTable(xmlNodePtr table);
		void CreateIndexes(xmlNodePtr table);
		void RunCreateSql(xmlNodePtr table);

		void VerifyTableStructure(xmlNodePtr table);

		int check_err( int rc );

		/** This will lock our internal mutex and then return our database object so that 
		  * you have exclusive access to it.  Use the ReleaseDatabase() method to properly
		  * tell us that you are done with the database, so that we can allow others to use it.
		  */
		sqlite3* GetDatabase();

		/** This will unlock our internal mutex and signifies that you are done with the database object.
		  */
		void ReleaseDatabase();

		/** This method will check the size of our database and if it is larger than our configured
		  * max size, we will close the db file, archive it, and create a new db file with the same
		  * table layout.  Note - this is usually only helpful for logging databases.  If our configured
		  * max size is zero, we will skip doing anything and allow the db to grow without limit.
		  */
		void CheckSize();

		/** This is a static method that will convert sqlite3 column types into their equivalent as
		  * they would come out of our OdbcObj.
		  */
		static int GetDataType( int sqlite3_dbtype );

		/** This will begin a transaction on the current database.
		  */
		void BeginTransaction();

		/** This will commit a transaction on the current database.
		  */
		void CommitTransaction();

		/** This will roll-back a transaction on the current database.
		  */
		void RollbackTransaction();

	protected:

		/** This method does the work of closing our db, archiving it, and creating a new db file.
		  */
		void createNewFile();
	
};

}} // End Namespace Helix::Glob

#endif // SQLDB_H Defined
