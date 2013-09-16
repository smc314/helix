/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetLogSettings.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "LogSettings.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<GetLogSettings> GetLogSettings::reg("GetLogSettings", 1, "/logic/util/GetLogSettings");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetLogSettings Input=NULL

GetLogSettings::GetLogSettings(xmlNodePtr action)
{
	EnEx ee(FL, "GetLogSettings::GetLogSettings(xmlNodePtr action)");
	
}

GetLogSettings::GetLogSettings(const GetLogSettings& c)
{
	EnEx ee(FL, "GetLogSettings::GetLogSettings(const GetLogSettings& c)");

}

GetLogSettings& GetLogSettings::operator=(const GetLogSettings& c)
{
	EnEx ee(FL, "GetLogSettings::operator=(const GetLogSettings& c)");

	return *this;
}

GetLogSettings::~GetLogSettings()
{

}

void GetLogSettings::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetLogSettings::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetLogSettings");

	LogSettings local; // Our local version of the log settings.

	// Read our main configuration file:
	xmlDocPtr config = TheMain::getInstance()->GetConfig();
	xmlNodePtr root = xmlDocGetRootElement(config);
	xmlNodePtr logs = XmlHelpers::FindChild(root, "AdaptiveLogs");
	if(logs == NULL){
		throw AnException(0, FL, "AdaptiveLogs node not found in config file!");
	}
	local.LogFile.getAttribute( logs, "filename" );
	local.BufferSize = XmlHelpers::getIntAttr( logs, "buffer_size");
	local.MaxSize = XmlHelpers::getIntAttr( logs, "max_file_size");

	xmlNodePtr panic = XmlHelpers::FindChild(logs, "Panic");
	if(panic == NULL) throw AnException(0, FL, "AdaptiveLogs missing the Panic channel.");
	local.panic = XmlHelpers::getBoolAttr( panic, "onoff" ) ? 1 : 0;
	local.panicCapture = XmlHelpers::getBoolAttr( panic, "buffered_when_off" ) ? 1 : 0;
	local.panicDump = (int)XmlHelpers::getIntAttr( panic, "dump_when_hit" );

	xmlNodePtr error = XmlHelpers::FindChild(logs, "Error");
	if(error == NULL) throw AnException(0, FL, "AdaptiveLogs missing the Error channel.");
	local.error = XmlHelpers::getBoolAttr( error, "onoff" ) ? 1 : 0;
	local.errorCapture = XmlHelpers::getBoolAttr( error, "buffered_when_off" ) ? 1 : 0;
	local.errorDump = (int)XmlHelpers::getIntAttr( error, "dump_when_hit" );

	xmlNodePtr warn = XmlHelpers::FindChild(logs, "Warn");
	if(warn == NULL) throw AnException(0, FL, "AdaptiveLogs missing the Warn channel.");
	local.warn = XmlHelpers::getBoolAttr( warn, "onoff" ) ? 1 : 0;
	local.warnCapture = XmlHelpers::getBoolAttr( warn, "buffered_when_off" ) ? 1 : 0;
	local.warnDump = (int)XmlHelpers::getIntAttr( warn, "dump_when_hit" );

	xmlNodePtr info = XmlHelpers::FindChild(logs, "Info");
	if(info == NULL) throw AnException(0, FL, "AdaptiveLogs missing the Info channel.");
	local.info = XmlHelpers::getBoolAttr( info, "onoff" ) ? 1 : 0;
	local.infoCapture = XmlHelpers::getBoolAttr( info, "buffered_when_off" ) ? 1 : 0;
	local.infoDump = (int)XmlHelpers::getIntAttr( info, "dump_when_hit" );

	xmlNodePtr debug = XmlHelpers::FindChild(logs, "Debug");
	if(debug == NULL) throw AnException(0, FL, "AdaptiveLogs missing the Debug channel.");
	local.debug = XmlHelpers::getBoolAttr( debug, "onoff" ) ? 1 : 0;
	local.debugCapture = XmlHelpers::getBoolAttr( debug, "buffered_when_off" ) ? 1 : 0;
	local.debugDump = (int)XmlHelpers::getIntAttr( debug, "dump_when_hit" );

	xmlNodePtr trace = XmlHelpers::FindChild(logs, "Trace");
	if(trace == NULL) throw AnException(0, FL, "AdaptiveLogs missing the Trace channel.");
	local.trace = XmlHelpers::getBoolAttr( trace, "onoff" ) ? 1 : 0;
	local.traceCapture = XmlHelpers::getBoolAttr( trace, "buffered_when_off" ) ? 1 : 0;
	local.traceDump = (int)XmlHelpers::getIntAttr( trace, "dump_when_hit" );

	xmlNodePtr sql = XmlHelpers::FindChild(logs, "SqlTrace");
	if(sql == NULL) throw AnException(0, FL, "AdaptiveLogs missing the SqlTrace channel.");
	local.sql = XmlHelpers::getBoolAttr( sql, "onoff" ) ? 1 : 0;
	local.sqlCapture = XmlHelpers::getBoolAttr( sql, "buffered_when_off" ) ? 1 : 0;
	local.sqlDump = (int)XmlHelpers::getIntAttr( sql, "dump_when_hit" );

	local.createXmlNode(ioc.getResponseRoot());

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
