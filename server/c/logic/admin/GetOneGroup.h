/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetOneGroup_H
#define GetOneGroup_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT GetOneGroup : public ActionClass
{
	public:
		/// Standard Constructor
		GetOneGroup(xmlNodePtr action);

		/// Standard Copy Constructor
		GetOneGroup(const GetOneGroup& c);

		/// Standard Copy operator
		GetOneGroup& operator=(const GetOneGroup& c);

		/// Standard Destructor
		virtual ~GetOneGroup();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetOneGroup> reg;

};

}}} // End of Namespace definitions

#endif // GetOneGroup_H Defined
