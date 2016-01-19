/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetLogSettings_H
#define GetLogSettings_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT GetLogSettings : public ActionClass
{
	public:
		/// Standard Constructor
		GetLogSettings(xmlNodePtr action);

		/// Standard Copy Constructor
		GetLogSettings(const GetLogSettings& c);

		/// Standard Copy operator
		GetLogSettings& operator=(const GetLogSettings& c);

		/// Standard Destructor
		virtual ~GetLogSettings();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetLogSettings> reg;

};

}}} // End of Namespace definitions

#endif // GetLogSettings_H Defined
