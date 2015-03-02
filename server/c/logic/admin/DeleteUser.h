/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef DeleteUser_H
#define DeleteUser_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DeleteUser : public ActionClass
{
	public:
		/// Standard Constructor
		DeleteUser(xmlNodePtr action);

		/// Standard Copy Constructor
		DeleteUser(const DeleteUser& c);

		/// Standard Copy operator
		DeleteUser& operator=(const DeleteUser& c);

		/// Standard Destructor
		virtual ~DeleteUser();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<DeleteUser> reg;

};

}}} // End of Namespace definitions

#endif // DeleteUser_H Defined
