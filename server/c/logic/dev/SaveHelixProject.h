/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SaveHelixProject_H
#define SaveHelixProject_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace dev {

class DLLEXPORT SaveHelixProject : public ActionClass
{
	public:
		/// Standard Constructor
		SaveHelixProject(xmlNodePtr action);

		/// Standard Copy Constructor
		SaveHelixProject(const SaveHelixProject& c);

		/// Standard Copy operator
		SaveHelixProject& operator=(const SaveHelixProject& c);

		/// Standard Destructor
		virtual ~SaveHelixProject();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SaveHelixProject> reg;

};

}}} // End of Namespace definitions

#endif // SaveHelixProject_H Defined
