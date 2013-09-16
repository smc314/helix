/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetHitMap_H
#define GetHitMap_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class GetHitMap : public ActionClass
{
	public:
		/// Standard Constructor
		GetHitMap(xmlNodePtr action);

		/// Standard Copy Constructor
		GetHitMap(const GetHitMap& c);

		/// Standard Copy operator
		GetHitMap& operator=(const GetHitMap& c);

		/// Standard Destructor
		virtual ~GetHitMap();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetHitMap> reg;

};

}}} // End of Namespace definitions

#endif // GetHitMap_H Defined
