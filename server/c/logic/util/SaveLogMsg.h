/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SaveLogMsg_H
#define SaveLogMsg_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT SaveLogMsg : public ActionClass
{
	public:
		/// Standard Constructor
		SaveLogMsg(xmlNodePtr action);

		/// Standard Copy Constructor
		SaveLogMsg(const SaveLogMsg& c);

		/// Standard Copy operator
		SaveLogMsg& operator=(const SaveLogMsg& c);

		/// Standard Destructor
		virtual ~SaveLogMsg();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SaveLogMsg> reg;

};

}}} // End of Namespace definitions

#endif // SaveLogMsg_H Defined
