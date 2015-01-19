/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef DeleteIAFile_H
#define DeleteIAFile_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class DeleteIAFile : public ActionClass
{
	public:
		/// Standard Constructor
		DeleteIAFile(xmlNodePtr action);

		/// Standard Copy Constructor
		DeleteIAFile(const DeleteIAFile& c);

		/// Standard Copy operator
		DeleteIAFile& operator=(const DeleteIAFile& c);

		/// Standard Destructor
		virtual ~DeleteIAFile();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<DeleteIAFile> reg;

};

}}} // End of Namespace definitions

#endif // DeleteIAFile_H Defined
