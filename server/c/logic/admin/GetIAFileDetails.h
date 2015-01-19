/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef GetIAFileDetails_H
#define GetIAFileDetails_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetIAFileDetails : public ActionClass
{
	public:
		/// Standard Constructor
		GetIAFileDetails(xmlNodePtr action);

		/// Standard Copy Constructor
		GetIAFileDetails(const GetIAFileDetails& c);

		/// Standard Copy operator
		GetIAFileDetails& operator=(const GetIAFileDetails& c);

		/// Standard Destructor
		virtual ~GetIAFileDetails();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetIAFileDetails> reg;

};

}}} // End of Namespace definitions

#endif // GetIAFileDetails_H Defined
