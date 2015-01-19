/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef GetSQLTest_H
#define GetSQLTest_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetSQLTest : public ActionClass
{
	public:
		/// Standard Constructor
		GetSQLTest(xmlNodePtr action);

		/// Standard Copy Constructor
		GetSQLTest(const GetSQLTest& c);

		/// Standard Copy operator
		GetSQLTest& operator=(const GetSQLTest& c);

		/// Standard Destructor
		virtual ~GetSQLTest();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetSQLTest> reg;

};

}}} // End of Namespace definitions

#endif // GetSQLTest_H Defined
