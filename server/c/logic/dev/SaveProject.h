/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SaveProject_H
#define SaveProject_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace dev {

class DLLEXPORT SaveProject : public ActionClass
{
	public:
		/// Standard Constructor
		SaveProject(xmlNodePtr action);

		/// Standard Copy Constructor
		SaveProject(const SaveProject& c);

		/// Standard Copy operator
		SaveProject& operator=(const SaveProject& c);

		/// Standard Destructor
		virtual ~SaveProject();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SaveProject> reg;

};

}}} // End of Namespace definitions

#endif // SaveProject_H Defined
