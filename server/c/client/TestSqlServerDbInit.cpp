/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

/* ***************************************************************************
	This is a utility used to dump an existing database schema into the
	format that the Helix Server supports for on-going maintenance.
*************************************************************************** */

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdexcept>

#include <XmlHelpers.h>
#include <AnException.h>
using namespace SLib;

#include <OdbcObj.h>
#include <SqlServerDbInit.h>
using namespace Helix::Glob;

OdbcObj* m_odbc;

int main(int argc, char** argv)
{
	// Turn all logging on
	Log::SetPanic(true);
	Log::SetError(true);
	Log::SetWarn(true);
	Log::SetInfo(true);
	Log::SetDebug(false);
	Log::SetTrace(false);
	Log::SetSqlTrace(true);

	try {
		m_odbc = new OdbcObj( "sa", "sql", "DSN=GalvestonTest1;" );

		SqlServerDbInit sqlServerInit("gal", "Galveston", "airtime.db.xml", "sa", "sql", m_odbc);

		sqlServerInit.VerifyInstallSchema();

	} catch(AnException& e){
		printf("Error caught: %s", e.Msg() );
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

