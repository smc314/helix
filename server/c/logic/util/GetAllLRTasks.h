/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetAllLRTasks_H
#define GetAllLRTasks_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT GetAllLRTasks : public ActionClass
{
	public:
		/// Standard Constructor
		GetAllLRTasks(xmlNodePtr action);

		/// Standard Copy Constructor
		GetAllLRTasks(const GetAllLRTasks& c);

		/// Standard Copy operator
		GetAllLRTasks& operator=(const GetAllLRTasks& c);

		/// Standard Destructor
		virtual ~GetAllLRTasks();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetAllLRTasks> reg;

};

}}} // End of Namespace definitions

#endif // GetAllLRTasks_H Defined
