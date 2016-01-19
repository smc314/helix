/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetUsers_H
#define GetUsers_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT GetUsers : public ActionClass
{
	public:
		/// Standard Constructor
		GetUsers(xmlNodePtr action);

		/// Standard Copy Constructor
		GetUsers(const GetUsers& c);

		/// Standard Copy operator
		GetUsers& operator=(const GetUsers& c);

		/// Standard Destructor
		virtual ~GetUsers();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetUsers> reg;

};

}}} // End of Namespace definitions

#endif // GetUsers_H Defined
