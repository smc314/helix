/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SaveLayout_H
#define SaveLayout_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT SaveLayout : public ActionClass
{
	public:
		/// Standard Constructor
		SaveLayout(xmlNodePtr action);

		/// Standard Copy Constructor
		SaveLayout(const SaveLayout& c);

		/// Standard Copy operator
		SaveLayout& operator=(const SaveLayout& c);

		/// Standard Destructor
		virtual ~SaveLayout();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SaveLayout> reg;

};

}}} // End of Namespace definitions

#endif // SaveLayout_H Defined
