/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SwitchServerConnection_H
#define SwitchServerConnection_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class SwitchServerConnection : public ActionClass
{
	public:
		/// Standard Constructor
		SwitchServerConnection(xmlNodePtr action);

		/// Standard Copy Constructor
		SwitchServerConnection(const SwitchServerConnection& c);

		/// Standard Copy operator
		SwitchServerConnection& operator=(const SwitchServerConnection& c);

		/// Standard Destructor
		virtual ~SwitchServerConnection();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SwitchServerConnection> reg;

};

}}} // End Namespace definition

#endif // SwitchServerConnection_H Defined
