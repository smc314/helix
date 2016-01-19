/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef DeleteSQLWork_H
#define DeleteSQLWork_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT DeleteSQLWork : public ActionClass
{
	public:
		/// Standard Constructor
		DeleteSQLWork(xmlNodePtr action);

		/// Standard Copy Constructor
		DeleteSQLWork(const DeleteSQLWork& c);

		/// Standard Copy operator
		DeleteSQLWork& operator=(const DeleteSQLWork& c);

		/// Standard Destructor
		virtual ~DeleteSQLWork();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<DeleteSQLWork> reg;

};

}}} // End Namespace definition

#endif // DeleteSQLWork_H Defined
