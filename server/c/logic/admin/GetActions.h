/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetActions_H
#define GetActions_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetActions : public ActionClass
{
	public:
		/// Standard Constructor
		GetActions(xmlNodePtr action);

		/// Standard Copy Constructor
		GetActions(const GetActions& c);

		/// Standard Copy operator
		GetActions& operator=(const GetActions& c);

		/// Standard Destructor
		virtual ~GetActions();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetActions> reg;

};

}}} // End of Namespace definitions

#endif // GetActions_H Defined
