/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetOneHelixUser_H
#define GetOneHelixUser_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT GetOneHelixUser : public ActionClass
{
	public:
		/// Standard Constructor
		GetOneHelixUser(xmlNodePtr action);

		/// Standard Copy Constructor
		GetOneHelixUser(const GetOneHelixUser& c);

		/// Standard Copy operator
		GetOneHelixUser& operator=(const GetOneHelixUser& c);

		/// Standard Destructor
		virtual ~GetOneHelixUser();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetOneHelixUser> reg;

};

}}} // End of Namespace definitions

#endif // GetOneHelixUser_H Defined
