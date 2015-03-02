/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef UpdateUser_H
#define UpdateUser_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class UpdateUser : public ActionClass
{
	public:
		/// Standard Constructor
		UpdateUser(xmlNodePtr action);

		/// Standard Copy Constructor
		UpdateUser(const UpdateUser& c);

		/// Standard Copy operator
		UpdateUser& operator=(const UpdateUser& c);

		/// Standard Destructor
		virtual ~UpdateUser();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<UpdateUser> reg;

};

}}} // End of Namespace definitions

#endif // UpdateUser_H Defined
