/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef Authenticate_H
#define Authenticate_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
#include "SessionInfo.h"
using namespace Helix::Glob;

namespace Helix {
namespace Glob {

class DLLEXPORT Authenticate : public ActionClass
{
	public:
		/// Standard Constructor
		Authenticate(xmlNodePtr action);

		/// Standard Copy Constructor
		Authenticate(const Authenticate& c);

		/// Standard Copy operator
		Authenticate& operator=(const Authenticate& c);

		/// Standard Destructor
		virtual ~Authenticate();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

		/// Use this to check user authentication
		static SessionInfo& authenticateUser( IOConn* ioc );

		/// Use this to check user authorization for a particular activity
		static bool authorizeUserAction( IOConn* ioc );

		static bool verifyUserNameAndPassword( IOConn* ioc, const twine& UserName, const twine& Password);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<Authenticate> reg;

};

}} // End of Namespace definitions

#endif // Authenticate_H Defined
