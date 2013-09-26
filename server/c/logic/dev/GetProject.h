/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetProject_H
#define GetProject_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace dev {

class GetProject : public ActionClass
{
	public:
		/// Standard Constructor
		GetProject(xmlNodePtr action);

		/// Standard Copy Constructor
		GetProject(const GetProject& c);

		/// Standard Copy operator
		GetProject& operator=(const GetProject& c);

		/// Standard Destructor
		virtual ~GetProject();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetProject> reg;

};

}}} // End of Namespace definitions

#endif // GetProject_H Defined
