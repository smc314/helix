/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetOneLRTask_H
#define GetOneLRTask_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT GetOneLRTask : public ActionClass
{
	public:
		/// Standard Constructor
		GetOneLRTask(xmlNodePtr action);

		/// Standard Copy Constructor
		GetOneLRTask(const GetOneLRTask& c);

		/// Standard Copy operator
		GetOneLRTask& operator=(const GetOneLRTask& c);

		/// Standard Destructor
		virtual ~GetOneLRTask();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetOneLRTask> reg;

};

}}} // End of Namespace definitions

#endif // GetOneLRTask_H Defined
