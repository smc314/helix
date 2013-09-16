/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetHitMap.h"
using namespace Helix::Logic::util;

#include "Statics.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "HitMap.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetHitMap> GetHitMap::reg("GetHitMap", 1, "/logic/util/GetHitMap");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetHitMap Input=NULL

GetHitMap::GetHitMap(xmlNodePtr action)
{
	EnEx ee(FL, "GetHitMap::GetHitMap(xmlNodePtr action)");
	
}

GetHitMap::GetHitMap(const GetHitMap& c)
{
	EnEx ee(FL, "GetHitMap::GetHitMap(const GetHitMap& c)");

}

GetHitMap& GetHitMap::operator=(const GetHitMap& c)
{
	EnEx ee(FL, "GetHitMap::operator=(const GetHitMap& c)");

	return *this;
}

GetHitMap::~GetHitMap()
{

}

void GetHitMap::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetHitMap::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetHitMap");

	EnEx::RecordGlobalHitMap( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
