/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetGroups_H
#define GetGroups_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetGroups : public ActionClass
{
	public:
		/// Standard Constructor
		GetGroups(xmlNodePtr action);

		/// Standard Copy Constructor
		GetGroups(const GetGroups& c);

		/// Standard Copy operator
		GetGroups& operator=(const GetGroups& c);

		/// Standard Destructor
		virtual ~GetGroups();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetGroups> reg;

};

}}} // End of Namespace definitions

#endif // GetGroups_H Defined
