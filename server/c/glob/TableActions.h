/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef TABLEACTIONS_H
#define TABLEACTIONS_H

#include <twine.h>
using namespace SLib;

namespace Helix {
namespace Glob {

class TableActions {
	public:

		/// Standard Constructor
		TableActions(const twine& Name);

		/// Copy Constructor
		TableActions(const TableActions& c);

		/// Assignment operator
		TableActions& operator=(const TableActions& c);

		/// Standard Destructor
		virtual ~TableActions();

		/// Which table are we working with
		twine TableName;

		/// Did we create it
		bool Created;

		/// Did we update it
		bool Updated;
};

}} // End Namespace Helix::Glob

#endif // TABLEACTIONS_H Defined
