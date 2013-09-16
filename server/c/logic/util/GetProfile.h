/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GETPROFILE_H
#define GETPROFILE_H


#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class GetProfile : public ActionClass 
{

	public:
		twine handler;

		/// Standard constructor	
		GetProfile(xmlNodePtr action);

		/// Standard Copy Constructor
		GetProfile(const GetProfile& c);

		/// Standard Copy operator
		GetProfile& operator=(const GetProfile& c);

		/// Standard Destructor
		virtual ~GetProfile();
	
		/// We handle requests for "/"
		virtual void ExecuteRequest(IOConn& ioc);

	private:
		
		// Registers us with the global factory map:
		static ActionClassRegister<GetProfile> reg;
};

}}} // End Namespace definition

#endif // GETPROFILE_H Defined
