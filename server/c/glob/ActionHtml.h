/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ACTIONHTML_H
#define ACTIONHTML_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
#include "IOConn.h"

namespace Helix {
namespace Glob {


class ActionHtml : public ActionClass {
	
	public:
		
		/// Standard Constructor
		ActionHtml(xmlNodePtr action);

		ActionHtml(twine name);

		/// Standard Copy Constructor
		ActionHtml(const ActionHtml& c);

		/// Standard assignment operator
		virtual ActionHtml& operator=(const ActionHtml& c);

		/// Standard Destructor
		virtual ~ActionHtml();
	
		/// This checks to see if the target url matches pages that we serve.
		int matchesURL(twine target_url);
	
		/// This will execute the request and serve up the page.
		virtual void ExecuteRequest(IOConn& ioc);


	private:
		// Registers us with the global factory map:
		static ActionClassRegister<ActionHtml> reg;
};

}} // End Namespace Helix::Glob

#endif // ACTIONHTML_H Defined
