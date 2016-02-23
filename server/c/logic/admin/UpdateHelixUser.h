/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef UpdateHelixUser_H
#define UpdateHelixUser_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT UpdateHelixUser : public ActionClass
{
	public:
		/// Standard Constructor
		UpdateHelixUser(xmlNodePtr action);

		/// Standard Copy Constructor
		UpdateHelixUser(const UpdateHelixUser& c);

		/// Standard Copy operator
		UpdateHelixUser& operator=(const UpdateHelixUser& c);

		/// Standard Destructor
		virtual ~UpdateHelixUser();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<UpdateHelixUser> reg;

};

}}} // End of Namespace definitions

#endif // UpdateHelixUser_H Defined
