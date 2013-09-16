/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef UpdateLogSettings_H
#define UpdateLogSettings_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class UpdateLogSettings : public ActionClass
{
	public:
		/// Standard Constructor
		UpdateLogSettings(xmlNodePtr action);

		/// Standard Copy Constructor
		UpdateLogSettings(const UpdateLogSettings& c);

		/// Standard Copy operator
		UpdateLogSettings& operator=(const UpdateLogSettings& c);

		/// Standard Destructor
		virtual ~UpdateLogSettings();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<UpdateLogSettings> reg;

};

}}} // End of Namespace definitions

#endif // UpdateLogSettings_H Defined
