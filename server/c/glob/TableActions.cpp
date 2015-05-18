/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TableActions.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
using namespace SLib;

TableActions::TableActions(const twine& Name)
{
	TableName = Name;
}

TableActions::TableActions(const TableActions& c)
{
	TableName = c.TableName;
	Created = c.Created;
	Updated = c.Updated;
}

TableActions& TableActions::operator=(const TableActions& c)
{
	TableName = c.TableName;
	Created = c.Created;
	Updated = c.Updated;

	return *this;
}

TableActions::~TableActions()
{

}
