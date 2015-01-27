/* ***************************************************************************

   Copyright (c): 2008 - 2014 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef MYSQLDBINIT_H
#define MYSQLDBINIT_H

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

/** This class is used to manage the installation and setup of our database schema.  It is
  * designed to find one or more of our database setup xml control files and then for each file,
  * verify that our database is installed, and each table is present with all of the columns,
  * keys, and indexes that we expect to exist.
  *
  * This should be a fast process, so it is safe to run this every time the application starts up.
  */
class MySqlDbInit {

	protected:
		map<twine, TableActions> _setupSummary; 
		sptr<xmlDoc, xmlFreeDoc>  _dbSetup;
		twine _SetupFilesPath;
		twine _targetDbName;
		twine _layoutFileName;
		twine _dbUser;
		twine _dbPass;
		OdbcObj* m_odbc;
		Connection* m_connection;
	
	private:
		/// Copy constructor is private to prevent use
		MySqlDbInit( const MySqlDbInit& c) {}

		/// Assignment operator is private to prevent use
		MySqlDbInit& operator=(const MySqlDbInit& c) { return *this; }

	public:
		/// Standard constructor
		MySqlDbInit( const twine& dbName );

		/// Standard destructor
		virtual ~MySqlDbInit();

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
	
};

}} // End Namespace Helix::Glob

#endif // MYSQLDBINIT_H Defined
