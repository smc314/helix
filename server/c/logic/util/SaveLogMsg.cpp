/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
#include "AdaptiveLogs.h"
using namespace Helix::Glob;

#include "SaveLogMsg.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here
#include "LogObj.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<SaveLogMsg> SaveLogMsg::reg("SaveLogMsg", 1, "/logic/util/SaveLogMsg");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/util/SaveLogMsg Input=LogObj

SaveLogMsg::SaveLogMsg(xmlNodePtr action)
{
	EnEx ee(FL, "SaveLogMsg::SaveLogMsg(xmlNodePtr action)");
	
}

SaveLogMsg::SaveLogMsg(const SaveLogMsg& c)
{
	EnEx ee(FL, "SaveLogMsg::SaveLogMsg(const SaveLogMsg& c)");

}

SaveLogMsg& SaveLogMsg::operator=(const SaveLogMsg& c)
{
	EnEx ee(FL, "SaveLogMsg::operator=(const SaveLogMsg& c)");

	return *this;
}

SaveLogMsg::~SaveLogMsg()
{

}

void SaveLogMsg::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "SaveLogMsg::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("SaveLogMsg");

	// Pull up all of our input documents and convert them into objects we can use:
	LogObj_svect vect = LogObj::readXmlChildren( ioc.GetRequestRoot() ); 

	for(int i = 0; i < (int)vect->size(); i++){
		// Create the SLib::LogMsg object from our Log object
		LogMsg* lm = new LogMsg();
		lm->file = (*vect)[i]->file;
		lm->line = (*vect)[i]->line;
		lm->tid = (uint32_t)(*vect)[i]->tid;
#ifdef _WIN32
		lm->timestamp.time = (*vect)[i]->timestamp_a;
		lm->timestamp.millitm = (unsigned short)((*vect)[i]->timestamp_b);
#else
		lm->timestamp.tv_sec = (*vect)[i]->timestamp_a;
		lm->timestamp.tv_usec = (*vect)[i]->timestamp_b;
#endif
		lm->channel = (*vect)[i]->channel;
		lm->appName = (*vect)[i]->appName;
		lm->machineName = (*vect)[i]->machineName;
		lm->msg = (*vect)[i]->msg;

		// Then drop it onto the log queue to get it saved to our log file
		AdaptiveLogs::GetExternalLogQueue().AddMsg( lm );
	}
	
	// Add a message about how many rows we found
	twine tmp;
	//tmp.format("%d Messages saved.", vect->size());
	tmp.format("Messages saved.");
	ioc.addResponseMessage(tmp);

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
