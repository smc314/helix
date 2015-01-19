/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef UpdateScheduleItem_H
#define UpdateScheduleItem_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class UpdateScheduleItem : public ActionClass
{
	public:
		/// Standard Constructor
		UpdateScheduleItem(xmlNodePtr action);

		/// Standard Copy Constructor
		UpdateScheduleItem(const UpdateScheduleItem& c);

		/// Standard Copy operator
		UpdateScheduleItem& operator=(const UpdateScheduleItem& c);

		/// Standard Destructor
		virtual ~UpdateScheduleItem();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<UpdateScheduleItem> reg;

};

}}} // End of Namespace definitions

#endif // UpdateScheduleItem_H Defined
