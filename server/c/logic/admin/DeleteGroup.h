/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef DeleteGroup_H
#define DeleteGroup_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT DeleteGroup : public ActionClass
{
	public:
		/// Standard Constructor
		DeleteGroup(xmlNodePtr action);

		/// Standard Copy Constructor
		DeleteGroup(const DeleteGroup& c);

		/// Standard Copy operator
		DeleteGroup& operator=(const DeleteGroup& c);

		/// Standard Destructor
		virtual ~DeleteGroup();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<DeleteGroup> reg;

};

}}} // End of Namespace definitions

#endif // DeleteGroup_H Defined
