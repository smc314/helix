/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetAllLayouts_H
#define GetAllLayouts_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT GetAllLayouts : public ActionClass
{
	public:
		/// Standard Constructor
		GetAllLayouts(xmlNodePtr action);

		/// Standard Copy Constructor
		GetAllLayouts(const GetAllLayouts& c);

		/// Standard Copy operator
		GetAllLayouts& operator=(const GetAllLayouts& c);

		/// Standard Destructor
		virtual ~GetAllLayouts();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		// Retrieves a list of layouts from the given director and adds them to the list.
		static void AddLayouts(vector<twine>& list, twine dirName);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetAllLayouts> reg;

};

}}} // End of Namespace definitions

#endif // GetAllLayouts_H Defined
