/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetLogMessages_H
#define GetLogMessages_H

#include <xmlinc.h>
#include <twine.h>
#include <LogMsg.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

#include "LogObj.h"
#include "LogMessageFilter.h"

namespace Helix {
namespace Logic {
namespace util {

class GetLogMessages : public ActionClass
{
	public:
		/// Standard Constructor
		GetLogMessages(xmlNodePtr action);

		/// Standard Copy Constructor
		GetLogMessages(const GetLogMessages& c);

		/// Standard Copy operator
		GetLogMessages& operator=(const GetLogMessages& c);

		/// Standard Destructor
		virtual ~GetLogMessages();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Use this to convert from a LogMsg to a LogObj
		static LogObj* CreateLogObj(LogMsg* lm);

		/// Use this to get the current log file name
		static twine GetCurrentLogFileName();

		/// Use this to see if a log message matches a filter
		static bool MatchesFilter(LogMsg* lm, LogMessageFilter& filter);

		/// Use this to convert a filter into a where clause
		static twine BuildFilter(LogMessageFilter& filter);

		/// Use this to save the log message filters to the current session userProperties
		static void SaveLogFilters(IOConn& ioc, LogMessageFilter& filter);

		/// Use this to determine if the filters are empty or not.
		static bool isFilterEmpty(LogMessageFilter& filter);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetLogMessages> reg;

};

}}} // End of Namespace definitions

#endif // GetLogMessages_H Defined
