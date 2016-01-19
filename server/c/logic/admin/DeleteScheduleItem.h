/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef DeleteScheduleItem_H
#define DeleteScheduleItem_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DLLEXPORT DeleteScheduleItem : public ActionClass
{
	public:
		/// Standard Constructor
		DeleteScheduleItem(xmlNodePtr action);

		/// Standard Copy Constructor
		DeleteScheduleItem(const DeleteScheduleItem& c);

		/// Standard Copy operator
		DeleteScheduleItem& operator=(const DeleteScheduleItem& c);

		/// Standard Destructor
		virtual ~DeleteScheduleItem();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<DeleteScheduleItem> reg;

};

}}} // End of Namespace definitions

#endif // DeleteScheduleItem_H Defined
