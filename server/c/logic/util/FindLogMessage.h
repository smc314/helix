/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef FindLogMessage_H
#define FindLogMessage_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class FindLogMessage : public ActionClass
{
	public:
		/// Standard Constructor
		FindLogMessage(xmlNodePtr action);

		/// Standard Copy Constructor
		FindLogMessage(const FindLogMessage& c);

		/// Standard Copy operator
		FindLogMessage& operator=(const FindLogMessage& c);

		/// Standard Destructor
		virtual ~FindLogMessage();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<FindLogMessage> reg;

};

}}} // End of Namespace definitions

#endif // FindLogMessage_H Defined
