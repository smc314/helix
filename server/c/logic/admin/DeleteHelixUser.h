/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef DeleteHelixUser_H
#define DeleteHelixUser_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT DeleteHelixUser : public ActionClass
{
	public:
		/// Standard Constructor
		DeleteHelixUser(xmlNodePtr action);

		/// Standard Copy Constructor
		DeleteHelixUser(const DeleteHelixUser& c);

		/// Standard Copy operator
		DeleteHelixUser& operator=(const DeleteHelixUser& c);

		/// Standard Destructor
		virtual ~DeleteHelixUser();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<DeleteHelixUser> reg;

};

}}} // End of Namespace definitions

#endif // DeleteHelixUser_H Defined
