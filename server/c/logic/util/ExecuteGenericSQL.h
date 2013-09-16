/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ExecuteGenericSQL_H
#define ExecuteGenericSQL_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

#include "SQLStatement.h"

namespace Helix {
namespace Logic {
namespace util {

class ExecuteGenericSQL : public ActionClass
{
	public:
		/// Standard Constructor
		ExecuteGenericSQL(xmlNodePtr action);

		/// Standard Copy Constructor
		ExecuteGenericSQL(const ExecuteGenericSQL& c);

		/// Standard Copy operator
		ExecuteGenericSQL& operator=(const ExecuteGenericSQL& c);

		/// Standard Destructor
		virtual ~ExecuteGenericSQL();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);
		
		/// Get an ODBC connection
		virtual OdbcObj* GetDBConnection(SQLStatement& local, IOConn& ioc);
		
		/// Fetch the data
		virtual void FetchData(OdbcObj& odbc, xmlNodePtr resp, twine& sql);

		/// Handle doing the sql against a local database
		virtual void LocalExec( SQLStatement& local, xmlNodePtr resp);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<ExecuteGenericSQL> reg;

};

}}} // End of Namespace definitions

#endif // ExecuteGenericSQL_H Defined
