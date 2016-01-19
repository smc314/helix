/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef CleanoutLRTask_H
#define CleanoutLRTask_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT CleanoutLRTask : public ActionClass
{
	public:
		/// Standard Constructor
		CleanoutLRTask(xmlNodePtr action);

		/// Standard Copy Constructor
		CleanoutLRTask(const CleanoutLRTask& c);

		/// Standard Copy operator
		CleanoutLRTask& operator=(const CleanoutLRTask& c);

		/// Standard Destructor
		virtual ~CleanoutLRTask();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<CleanoutLRTask> reg;

};

}}} // End of Namespace definitions

#endif // CleanoutLRTask_H Defined
