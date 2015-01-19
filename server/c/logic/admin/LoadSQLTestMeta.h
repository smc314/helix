/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef LoadSQLTestMeta_H
#define LoadSQLTestMeta_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "SQLTests.h"
using namespace Helix::Logic::admin;

namespace Helix {
namespace Logic {
namespace admin {

class LoadSQLTestMeta : public ActionClass
{
	public:
		/// Standard Constructor
		LoadSQLTestMeta(xmlNodePtr action);

		/// Standard Copy Constructor
		LoadSQLTestMeta(const LoadSQLTestMeta& c);

		/// Standard Copy operator
		LoadSQLTestMeta& operator=(const LoadSQLTestMeta& c);

		/// Standard Destructor
		virtual ~LoadSQLTestMeta();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		void Disconnect();
		void Connect();
		void LoopSqlStatements();
		void RunSqlTest( SQLStmt* stmt );
		void CaptureMetadata( SQLStmt* stmt );
		void CaptureResults( SQLStmt* stmt );

		// Registers us with the global factory map:
		static ActionClassRegister<LoadSQLTestMeta> reg;

		SQLTests* m_Tests;		
		OdbcObj* m_odbc;

};

}}} // End of Namespace definitions

#endif // LoadSQLTestMeta_H Defined
