/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SaveSQLTest_H
#define SaveSQLTest_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT SaveSQLTest : public ActionClass
{
	public:
		/// Standard Constructor
		SaveSQLTest(xmlNodePtr action);

		/// Standard Copy Constructor
		SaveSQLTest(const SaveSQLTest& c);

		/// Standard Copy operator
		SaveSQLTest& operator=(const SaveSQLTest& c);

		/// Standard Destructor
		virtual ~SaveSQLTest();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SaveSQLTest> reg;

};

}}} // End of Namespace definitions

#endif // SaveSQLTest_H Defined
