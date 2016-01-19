/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef GetLogFiles_H
#define GetLogFiles_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

class DLLEXPORT GetLogFiles : public ActionClass
{
	public:
		/// Standard Constructor
		GetLogFiles(xmlNodePtr action);

		/// Standard Copy Constructor
		GetLogFiles(const GetLogFiles& c);

		/// Standard Copy operator
		GetLogFiles& operator=(const GetLogFiles& c);

		/// Standard Destructor
		virtual ~GetLogFiles();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Finds all files under our ./logs directory
		void FindAllLogs(xmlNodePtr root, const twine& path);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<GetLogFiles> reg;

};

}}} // End of Namespace definitions

#endif // GetLogFiles_H Defined
