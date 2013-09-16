/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetLogMsgCount_H
#define GetLogMsgCount_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

#include "LogMessageFilter.h"

namespace Helix {
namespace Logic {
namespace util {

class GetLogMsgCount : public ActionClass
{
	public:
		/// Standard Constructor
		GetLogMsgCount(xmlNodePtr action);

		/// Standard Copy Constructor
		GetLogMsgCount(const GetLogMsgCount& c);

		/// Standard Copy operator
		GetLogMsgCount& operator=(const GetLogMsgCount& c);

		/// Standard Destructor
		virtual ~GetLogMsgCount();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetLogMsgCount> reg;

};

}}} // End of Namespace definitions

#endif // GetLogMsgCount_H Defined
