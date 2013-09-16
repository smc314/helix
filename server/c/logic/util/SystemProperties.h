/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SystemProperties_H
#define SystemProperties_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class SystemProperties : public ActionClass
{
	public:
		/// Standard Constructor
		SystemProperties(xmlNodePtr action);

		/// Standard Copy Constructor
		SystemProperties(const SystemProperties& c);

		/// Standard Copy operator
		SystemProperties& operator=(const SystemProperties& c);

		/// Standard Destructor
		virtual ~SystemProperties();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SystemProperties> reg;

};

}}} // End Namespace definition

#endif // SystemProperties_H Defined
