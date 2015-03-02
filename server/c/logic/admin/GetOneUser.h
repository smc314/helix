/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetOneUser_H
#define GetOneUser_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetOneUser : public ActionClass
{
	public:
		/// Standard Constructor
		GetOneUser(xmlNodePtr action);

		/// Standard Copy Constructor
		GetOneUser(const GetOneUser& c);

		/// Standard Copy operator
		GetOneUser& operator=(const GetOneUser& c);

		/// Standard Destructor
		virtual ~GetOneUser();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetOneUser> reg;

};

}}} // End of Namespace definitions

#endif // GetOneUser_H Defined
