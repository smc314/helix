/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetHelixUsers_H
#define GetHelixUsers_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT GetHelixUsers : public ActionClass
{
	public:
		/// Standard Constructor
		GetHelixUsers(xmlNodePtr action);

		/// Standard Copy Constructor
		GetHelixUsers(const GetHelixUsers& c);

		/// Standard Copy operator
		GetHelixUsers& operator=(const GetHelixUsers& c);

		/// Standard Destructor
		virtual ~GetHelixUsers();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetHelixUsers> reg;

};

}}} // End of Namespace definitions

#endif // GetHelixUsers_H Defined
