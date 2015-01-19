/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef GetSQLWork_H
#define GetSQLWork_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetSQLWork : public ActionClass
{
	public:
		/// Standard Constructor
		GetSQLWork(xmlNodePtr action);

		/// Standard Copy Constructor
		GetSQLWork(const GetSQLWork& c);

		/// Standard Copy operator
		GetSQLWork& operator=(const GetSQLWork& c);

		/// Standard Destructor
		virtual ~GetSQLWork();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetSQLWork> reg;

};

}}} // End of Namespace definitions

#endif // GetSQLWork_H Defined
