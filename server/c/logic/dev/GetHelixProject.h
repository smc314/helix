/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetHelixProject_H
#define GetHelixProject_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace dev {

class DLLEXPORT GetHelixProject : public ActionClass
{
	public:
		/// Standard Constructor
		GetHelixProject(xmlNodePtr action);

		/// Standard Copy Constructor
		GetHelixProject(const GetHelixProject& c);

		/// Standard Copy operator
		GetHelixProject& operator=(const GetHelixProject& c);

		/// Standard Destructor
		virtual ~GetHelixProject();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetHelixProject> reg;

};

}}} // End of Namespace definitions

#endif // GetHelixProject_H Defined
