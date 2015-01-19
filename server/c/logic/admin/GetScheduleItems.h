/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef GetScheduleItems_H
#define GetScheduleItems_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetScheduleItems : public ActionClass
{
	public:
		/// Standard Constructor
		GetScheduleItems(xmlNodePtr action);

		/// Standard Copy Constructor
		GetScheduleItems(const GetScheduleItems& c);

		/// Standard Copy operator
		GetScheduleItems& operator=(const GetScheduleItems& c);

		/// Standard Destructor
		virtual ~GetScheduleItems();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetScheduleItems> reg;

};

}}} // End of Namespace definitions

#endif // GetScheduleItems_H Defined
