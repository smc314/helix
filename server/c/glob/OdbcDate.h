#ifndef ODBCDATE_H
#define ODBCDATE_H
/*
 * Copyright (c) 2001,2002 Steven M. Cherry. All rights reserved.
 *
 * This file is a part of slib - a c++ utility library
 *
 * The slib project, including all files needed to compile 
 * it, is free software; you can redistribute it and/or use it and/or modify 
 * it under the terms of the GNU Lesser General Public License as published by 
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  See file COPYING for details.
 */

#include "Date.h"
using namespace SLib;

#include <sql.h>
#include <sqlext.h>

namespace Helix {
namespace Glob {

/**
  * The OdbcDate extends the SLib date class and adds Odbc specific 
  * handling for it.
  *
  * @author Steven M. Cherry
  * @copyright 2016 Steven M. Cherry
  */
class DLLEXPORT OdbcDate : public Date
{
	public:
		
		/**
		  * A Simple constructor for the date class.  This
		  * will initialize the date and time structures to
		  * the current date/time.
		  */
		OdbcDate();

		/**
		  * Copy constructor for the OdbcDate class.
		  */
		OdbcDate(const OdbcDate& d);

		/**
		  * The standard destructor for the date class.
		  */
		virtual ~OdbcDate();

		/// Assignment operator.
		OdbcDate& operator=(const OdbcDate& d);

		/// Returns the address of the ODBC SQL_TIMESTAMP_STRUCT that we hold
		SQL_TIMESTAMP_STRUCT* GetOdbcStruct();

		/// Reads the value from our internal TimeStruct and copies it into the OdbcStruct
		void InternalToOdbc();

		/// Reads the value from our OdbcStruct and copies it into our TimeStruct
		void OdbcToInternal();

	protected:

		SQL_TIMESTAMP_STRUCT* m_odbcStruct;

};

} // End Glob namespace.
} // End Helix namespace.

#endif // ODBCDATE_H Defined		
