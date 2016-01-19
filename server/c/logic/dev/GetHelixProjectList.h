/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetHelixProjectList_H
#define GetHelixProjectList_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace dev {

class DLLEXPORT GetHelixProjectList : public ActionClass
{
	public:
		/// Standard Constructor
		GetHelixProjectList(xmlNodePtr action);

		/// Standard Copy Constructor
		GetHelixProjectList(const GetHelixProjectList& c);

		/// Standard Copy operator
		GetHelixProjectList& operator=(const GetHelixProjectList& c);

		/// Standard Destructor
		virtual ~GetHelixProjectList();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetHelixProjectList> reg;

};

}}} // End of Namespace definitions

#endif // GetHelixProjectList_H Defined
