/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef UserProperties_H
#define UserProperties_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT UserProperties : public ActionClass
{
	public:
		/// Standard Constructor
		UserProperties(xmlNodePtr action);

		/// Standard Copy Constructor
		UserProperties(const UserProperties& c);

		/// Standard Copy operator
		UserProperties& operator=(const UserProperties& c);

		/// Standard Destructor
		virtual ~UserProperties();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<UserProperties> reg;

};

}}} // End Namespace definition

#endif // UserProperties_H Defined
