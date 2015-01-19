/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "UpdateLogSettings.h"
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
ActionClassRegister<UpdateLogSettings> UpdateLogSettings::reg("UpdateLogSettings", 1, "/logic/util/UpdateLogSettings");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/UpdateLogSettings Input=LogSettings

UpdateLogSettings::UpdateLogSettings(xmlNodePtr action)
{
	EnEx ee(FL, "UpdateLogSettings::UpdateLogSettings(xmlNodePtr action)");
	
}

UpdateLogSettings::UpdateLogSettings(const UpdateLogSettings& c)
{
	EnEx ee(FL, "UpdateLogSettings::UpdateLogSettings(const UpdateLogSettings& c)");

}

UpdateLogSettings& UpdateLogSettings::operator=(const UpdateLogSettings& c)
{
	EnEx ee(FL, "UpdateLogSettings::operator=(const UpdateLogSettings& c)");

	return *this;
}

UpdateLogSettings::~UpdateLogSettings()
{

}

void UpdateLogSettings::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "UpdateLogSettings::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("UpdateLogSettings");

	// Pull up our input document and convert it into an object we can use:
	LogSettings local( XmlHelpers::FindChild(ioc.GetRequestRoot(), LogSettings::Name()()) );

	// Sanity check
	if(local.LogFile.empty()){
		throw AnException(0, FL, "Missing log file name.");
	}
	if(local.BufferSize == 0){
		local.BufferSize = 1000;
	}
	if(local.MaxSize == 0){
		local.MaxSize = 52428800;
	}

	// Update our main config file:
	xmlDocPtr config = TheMain::getInstance()->GetConfig();
	xmlNodePtr root = xmlDocGetRootElement(config);
	xmlNodePtr logs = XmlHelpers::FindChild(root, "AdaptiveLogs");
	if(logs == NULL){
		logs = xmlNewChild(root, NULL, (const xmlChar*)"AdaptiveLogs", NULL);
	}
	xmlSetProp(logs, (const xmlChar*)"filename", local.LogFile ); 
	XmlHelpers::setIntAttr( logs, "buffer_size", local.BufferSize );
	XmlHelpers::setIntAttr( logs, "max_file_size", local.MaxSize );

	xmlNodePtr panic = XmlHelpers::FindChild(logs, "Panic");
	if(panic == NULL) panic = xmlNewChild(logs, NULL, (const xmlChar*)"Panic", NULL);
	xmlSetProp(panic, (const xmlChar*)"onoff", (const xmlChar*)(local.panic ? "ON" : "Of") );
	xmlSetProp(panic, (const xmlChar*)"buffered_when_off", (const xmlChar*)(local.panicCapture ? "ON" : "Of") );
	XmlHelpers::setIntAttr( panic, "dump_when_hit", local.panicDump );

	xmlNodePtr error = XmlHelpers::FindChild(logs, "Error");
	if(error == NULL) error = xmlNewChild(logs, NULL, (const xmlChar*)"Error", NULL);
	xmlSetProp(error, (const xmlChar*)"onoff", (const xmlChar*)(local.error ? "ON" : "Of") );
	xmlSetProp(error, (const xmlChar*)"buffered_when_off", (const xmlChar*)(local.errorCapture ? "ON" : "Of") );
	XmlHelpers::setIntAttr( error, "dump_when_hit", local.errorDump );

	xmlNodePtr warn = XmlHelpers::FindChild(logs, "Warn");
	if(warn == NULL) warn = xmlNewChild(logs, NULL, (const xmlChar*)"Warn", NULL);
	xmlSetProp(warn, (const xmlChar*)"onoff", (const xmlChar*)(local.warn ? "ON" : "Of") );
	xmlSetProp(warn, (const xmlChar*)"buffered_when_off", (const xmlChar*)(local.warnCapture ? "ON" : "Of") );
	XmlHelpers::setIntAttr( warn, "dump_when_hit", local.warnDump );

	xmlNodePtr info = XmlHelpers::FindChild(logs, "Info");
	if(info == NULL) info = xmlNewChild(logs, NULL, (const xmlChar*)"Info", NULL);
	xmlSetProp(info, (const xmlChar*)"onoff", (const xmlChar*)(local.info ? "ON" : "Of") );
	xmlSetProp(info, (const xmlChar*)"buffered_when_off", (const xmlChar*)(local.infoCapture ? "ON" : "Of") );
	XmlHelpers::setIntAttr( info, "dump_when_hit", local.infoDump );

	xmlNodePtr debug = XmlHelpers::FindChild(logs, "Debug");
	if(debug == NULL) debug = xmlNewChild(logs, NULL, (const xmlChar*)"Debug", NULL);
	xmlSetProp(debug, (const xmlChar*)"onoff", (const xmlChar*)(local.debug ? "ON" : "Of") );
	xmlSetProp(debug, (const xmlChar*)"buffered_when_off", (const xmlChar*)(local.debugCapture ? "ON" : "Of") );
	XmlHelpers::setIntAttr( debug, "dump_when_hit", local.debugDump );

	xmlNodePtr trace = XmlHelpers::FindChild(logs, "Trace");
	if(trace == NULL) trace = xmlNewChild(logs, NULL, (const xmlChar*)"Trace", NULL);
	xmlSetProp(trace, (const xmlChar*)"onoff", (const xmlChar*)(local.trace ? "ON" : "Of") );
	xmlSetProp(trace, (const xmlChar*)"buffered_when_off", (const xmlChar*)(local.traceCapture ? "ON" : "Of") );
	XmlHelpers::setIntAttr( trace, "dump_when_hit", local.traceDump );

	xmlNodePtr sql = XmlHelpers::FindChild(logs, "SqlTrace");
	if(sql == NULL) sql = xmlNewChild(logs, NULL, (const xmlChar*)"SqlTrace", NULL);
	xmlSetProp(sql, (const xmlChar*)"onoff", (const xmlChar*)(local.sql ? "ON" : "Of") );
	xmlSetProp(sql, (const xmlChar*)"buffered_when_off", (const xmlChar*)(local.sqlCapture ? "ON" : "Of") );
	XmlHelpers::setIntAttr( sql, "dump_when_hit", local.sqlDump );

	// Tell TheMain to save our config file back to disk:
	TheMain::getInstance()->SaveConfig();

	// Tell AdaptiveLogs to re-fresh its config information.
	TheMain::getInstance()->RefreshAdaptiveLogs();

	INFO(FL, "Adaptive log configuration saved and refreshed.");

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
