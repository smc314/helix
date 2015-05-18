/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef UpdateGroup_H
#define UpdateGroup_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class UpdateGroup : public ActionClass
{
	public:
		/// Standard Constructor
		UpdateGroup(xmlNodePtr action);

		/// Standard Copy Constructor
		UpdateGroup(const UpdateGroup& c);

		/// Standard Copy operator
		UpdateGroup& operator=(const UpdateGroup& c);

		/// Standard Destructor
		virtual ~UpdateGroup();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<UpdateGroup> reg;

};

}}} // End of Namespace definitions

#endif // UpdateGroup_H Defined
