/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef DBDATATYPES_H
#define DBDATATYPES_H

/* *************************************************************** */
/* This header defines our standardized database data types.  All  */
/* of these types will map to the defines for each of the database */
/* vendors that we interface to.  This gives a nice consistent     */
/* layer for all of our code to use.                               */
/* *************************************************************** */

namespace Helix {
namespace Glob {


/// Defines the Integer datatype.
static const int DB_INT = 0;

/// Defines the character datatype.
static const int DB_CHAR = 1;

/// Defines the float datatype.
static const int DB_FLOAT = 2;

/// Defines the datetime datatype.
static const int DB_DATETIME = 3;

/// Defines the type for a select statement.
static const int SQL_TYPE_SELECT = 100;

/// Defines the type for an insert statement.
static const int SQL_TYPE_INSERT = 101;

/// Defines the type for an update statement.
static const int SQL_TYPE_UPDATE = 102;

/// Defines the type for a delete statement.
static const int SQL_TYPE_DELETE = 103;


}} // End Namespace Helix::Glob

#endif // DBDATATYPES_H defined

