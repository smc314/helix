/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ACTIONLOGIC_H
#define ACTIONLOGIC_H


#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"

namespace Helix {
namespace Glob {


class DLLEXPORT ActionLogic : public ActionClass 
{
	public:
		twine handler;

		/// Standard constructor	
		ActionLogic(xmlNodePtr action);

		/// Standard Copy Constructor
		ActionLogic(const ActionLogic& c);

		/// Standard Copy operator
		ActionLogic& operator=(const ActionLogic& c);

		/// Standard Destructor
		virtual ~ActionLogic();
	
		/// We handle requests for "/"
		virtual void ExecuteRequest(IOConn& ioc);

	private:
		
		// Registers us with the global factory map:
		static ActionClassRegister<ActionLogic> reg;
};

}} // End Namespace Helix::Glob

#endif // ACTIONLOGIC_H Defined
