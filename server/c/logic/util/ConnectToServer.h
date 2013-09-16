/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ConnectToServer_H
#define ConnectToServer_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class ConnectToServer : public ActionClass
{
	public:
		/// Standard Constructor
		ConnectToServer(xmlNodePtr action);

		/// Standard Copy Constructor
		ConnectToServer(const ConnectToServer& c);

		/// Standard Copy operator
		ConnectToServer& operator=(const ConnectToServer& c);

		/// Standard Destructor
		virtual ~ConnectToServer();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<ConnectToServer> reg;

};

}}} // End Namespace definition

#endif // ConnectToServer_H Defined
