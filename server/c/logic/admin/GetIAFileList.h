/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef GetIAFileList_H
#define GetIAFileList_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetIAFileList : public ActionClass
{
	public:
		/// Standard Constructor
		GetIAFileList(xmlNodePtr action);

		/// Standard Copy Constructor
		GetIAFileList(const GetIAFileList& c);

		/// Standard Copy operator
		GetIAFileList& operator=(const GetIAFileList& c);

		/// Standard Destructor
		virtual ~GetIAFileList();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetIAFileList> reg;

};

}}} // End Namespace definition

#endif // GetIAFileList_H Defined
