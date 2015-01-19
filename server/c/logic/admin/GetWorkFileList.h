/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

#ifndef GetWorkFileList_H
#define GetWorkFileList_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class GetWorkFileList : public ActionClass
{
	public:
		/// Standard Constructor
		GetWorkFileList(xmlNodePtr action);

		/// Standard Copy Constructor
		GetWorkFileList(const GetWorkFileList& c);

		/// Standard Copy operator
		GetWorkFileList& operator=(const GetWorkFileList& c);

		/// Standard Destructor
		virtual ~GetWorkFileList();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetWorkFileList> reg;

};

}}} // End Namespace definition

#endif // GetWorkFileList_H Defined
