/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef GetOneScheduleItem_H
#define GetOneScheduleItem_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetOneScheduleItem : public ActionClass
{
	public:
		/// Standard Constructor
		GetOneScheduleItem(xmlNodePtr action);

		/// Standard Copy Constructor
		GetOneScheduleItem(const GetOneScheduleItem& c);

		/// Standard Copy operator
		GetOneScheduleItem& operator=(const GetOneScheduleItem& c);

		/// Standard Destructor
		virtual ~GetOneScheduleItem();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetOneScheduleItem> reg;

};

}}} // End of Namespace definitions

#endif // GetOneScheduleItem_H Defined
