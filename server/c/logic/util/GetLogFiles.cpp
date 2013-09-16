/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "GetLogFiles.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "GetLogMessages.h"


// This adds us to the global ActionClass Registry:
ActionClassRegister<GetLogFiles> GetLogFiles::reg("GetLogFiles", 1, "/logic/util/GetLogFiles");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/GetLogFiles Input=NULL

GetLogFiles::GetLogFiles(xmlNodePtr action)
{
	EnEx ee(FL, "GetLogFiles::GetLogFiles(xmlNodePtr action)");
	
}

GetLogFiles::GetLogFiles(const GetLogFiles& c)
{
	EnEx ee(FL, "GetLogFiles::GetLogFiles(const GetLogFiles& c)");

}

GetLogFiles& GetLogFiles::operator=(const GetLogFiles& c)
{
	EnEx ee(FL, "GetLogFiles::operator=(const GetLogFiles& c)");

	return *this;
}

GetLogFiles::~GetLogFiles()
{

}

void GetLogFiles::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "GetLogFiles::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("GetLogFiles");
	xmlNodePtr root = ioc.getResponseRoot();

	twine logName = GetLogMessages::GetCurrentLogFileName();
	// look for anything in the current directory that starts with the same
	// name as the current log file.
	vector<twine> files = File::listFiles(".");
	for(size_t i = 0; i < files.size(); i++){
		// Look for current log file name, and old viaserv.log log files as well
		if(files[i].startsWith( logName ) || files[i].startsWith("viaserv.log") ){
			// Record this name
			xmlNodePtr child = xmlNewChild(root, NULL, (const xmlChar*)"LogFile", NULL);
			xmlSetProp(child, (const xmlChar*)"name", files[i]);
			xmlSetProp(child, (const xmlChar*)"id", files[i]);
			xmlSetProp(child, (const xmlChar*)"path", (const xmlChar*)"");
		}
	}

	// Also include everything in our ./logs folder
	try {
		FindAllLogs(root, "./logs" );
	} catch (AnException& e){
		// we don't actually care if there is nothing in the ./logs folder
	}

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}

void GetLogFiles::FindAllLogs(xmlNodePtr root, const twine& path)
{
	EnEx ee(FL, "GetLogFiles::FindAllLogs(xmlNodePtr root, const twine& path)");

	vector<twine> files = File::listFiles( path );
	vector<twine> folders = File::listFolders( path );

	// Record all of the files that we find:
	for(size_t i = 0; i < files.size(); i++){
		// Record this name
		xmlNodePtr child = xmlNewChild(root, NULL, (const xmlChar*)"LogFile", NULL);
		xmlSetProp(child, (const xmlChar*)"name", path + "/" + files[i]);
		xmlSetProp(child, (const xmlChar*)"id", path + "/" + files[i]);
		xmlSetProp(child, (const xmlChar*)"path", path);
	}

	// Loop through all of our folders to find all of their files
	for(size_t i = 0; i < folders.size(); i++){
		if(folders[i] != "." && folders[i] != ".." ){
			twine subpath = path + "/" + folders[i];
			FindAllLogs(root, subpath);
		}
	}
}
