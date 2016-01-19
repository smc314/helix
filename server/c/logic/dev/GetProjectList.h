/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetProjectList_H
#define GetProjectList_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace dev {

class DLLEXPORT GetProjectList : public ActionClass
{
	public:
		/// Standard Constructor
		GetProjectList(xmlNodePtr action);

		/// Standard Copy Constructor
		GetProjectList(const GetProjectList& c);

		/// Standard Copy operator
		GetProjectList& operator=(const GetProjectList& c);

		/// Standard Destructor
		virtual ~GetProjectList();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetProjectList> reg;

};

}}} // End of Namespace definitions

#endif // GetProjectList_H Defined
