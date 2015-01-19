/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SaveSQLWork_H
#define SaveSQLWork_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace admin {

class SaveSQLWork : public ActionClass
{
	public:
		/// Standard Constructor
		SaveSQLWork(xmlNodePtr action);

		/// Standard Copy Constructor
		SaveSQLWork(const SaveSQLWork& c);

		/// Standard Copy operator
		SaveSQLWork& operator=(const SaveSQLWork& c);

		/// Standard Destructor
		virtual ~SaveSQLWork();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<SaveSQLWork> reg;

};

}}} // End of Namespace definitions

#endif // SaveSQLWork_H Defined
