/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SaveIAFile_H
#define SaveIAFile_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class SaveIAFile : public ActionClass
{
	public:
		/// Standard Constructor
		SaveIAFile(xmlNodePtr action);

		/// Standard Copy Constructor
		SaveIAFile(const SaveIAFile& c);

		/// Standard Copy operator
		SaveIAFile& operator=(const SaveIAFile& c);

		/// Standard Destructor
		virtual ~SaveIAFile();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SaveIAFile> reg;

};

}}} // End of Namespace definitions

#endif // SaveIAFile_H Defined
