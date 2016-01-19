/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef CloseConnection_H
#define CloseConnection_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT CloseConnection : public ActionClass
{
	public:
		/// Standard Constructor
		CloseConnection(xmlNodePtr action);

		/// Standard Copy Constructor
		CloseConnection(const CloseConnection& c);

		/// Standard Copy operator
		CloseConnection& operator=(const CloseConnection& c);

		/// Standard Destructor
		virtual ~CloseConnection();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<CloseConnection> reg;

};

}}} // End of Namespace definitions

#endif // CloseConnection_H Defined
