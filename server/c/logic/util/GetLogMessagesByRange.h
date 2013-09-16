/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetLogMessagesByRange_H
#define GetLogMessagesByRange_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class GetLogMessagesByRange : public ActionClass
{
	public:
		/// Standard Constructor
		GetLogMessagesByRange(xmlNodePtr action);

		/// Standard Copy Constructor
		GetLogMessagesByRange(const GetLogMessagesByRange& c);

		/// Standard Copy operator
		GetLogMessagesByRange& operator=(const GetLogMessagesByRange& c);

		/// Standard Destructor
		virtual ~GetLogMessagesByRange();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetLogMessagesByRange> reg;

};

}}} // End of Namespace definitions

#endif // GetLogMessagesByRange_H Defined
