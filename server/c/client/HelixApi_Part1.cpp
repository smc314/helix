/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License:  The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include <AnException.h>
#include <twine.h>
#include <Log.h>
#include <EnEx.h>
#include <dptr.h>
#include <Timer.h>
#include <HttpClient.h>
#include <XmlHelpers.h>
using namespace SLib;

#include "LongRunningTask.h"
using namespace Helix::Glob;

#include "HelixApi.h"
using namespace Helix::Client;

/* ***************************************************************************** */
/* The implementation of HelixApi is broken up into 2 .cpp files.  This one is     */
/* hand-written and maintained.  Part2 is auto-generated during the compile.     */
/* Edits to this file are just fine and will not be overwritten during the make. */
/* ***************************************************************************** */

HelixApi::HelixApi(const twine& host, int port, bool useSSL) : HttpClient()
{
	EnEx ee(FL, "HelixApi::HelixApi(const twine& host, int port)");

	m_host = host;
	m_port = port;
	m_use_ssl = useSSL;

}

HelixApi::~HelixApi( )
{
	EnEx ee(FL, "HelixApi::~HelixApi()");

}

int HelixApi::Progress(double dltotal, double dlnow, double ultotal, double ulnow)
{
	EnEx ee(FL, "HelixApi::Progress(double dltotal, double dlnow, double ultotal, double ulnow)");

	if( m_lr_task_id.length() == 0 ){
		return 0; // nothing to do
	}
	twine msg; msg.format( "Send: %d of %d Bytes - Recv: %d of %d Bytes", 
		(int)ulnow, (int)ultotal, 
		(int)dlnow, (int)dltotal);

	if(LongRunningTask::getInstance().hasTask( m_lr_task_id )){
		try {
			LongRunningTask::getInstance().updateTask( m_lr_task_id, 0, (intptr_t)dlnow, 
				(intptr_t)dltotal, msg );
		} catch (AnException& e){
			// ignore this.
		}
	}
	return 0; // return 0 so that the transfer is not aborted.
}

void HelixApi::returnHasErrors()
{
	EnEx ee(FL, "HelixApi::returnHasErrors()");

	if(m_response == NULL){
		throw AnException(0, FL, "No response received.");	
	}

	xmlNodePtr root = xmlDocGetRootElement( m_response );

	bool haserror = XmlHelpers::getBoolAttr(root, "haserror");
	if(haserror){
		twine errMessages;
		vector<xmlNodePtr> errs = XmlHelpers::FindChildren(XmlHelpers::FindChild(root, "Errors"),"Error");
		for(size_t i = 0; i < errs.size(); i++){
			twine msg( errs[i], "msg" );
			errMessages += msg + "\n\n";
		}
		throw AnException(0, FL, errMessages());
	}
}

bool HelixApi::returnRequiresDB()
{
	EnEx ee(FL, "HelixApi::returnRequiresDB()");

	if(m_response == NULL){
		throw AnException(0, FL, "No response received.");	
	}

	xmlNodePtr root = xmlDocGetRootElement( m_response );

	bool haserror = XmlHelpers::getBoolAttr(root, "haserror");
	if(haserror){
		vector<xmlNodePtr> errs = XmlHelpers::FindChildren(XmlHelpers::FindChild(root, "Errors"),"Error");
		for(size_t i = 0; i < errs.size(); i++){
			twine msg( errs[i], "msg" );
			if(msg.startsWith("Current session has not chosen a DB Connection")){
				return true;
			}
		}
		return false;
	}
	return false;
}

xmlDocPtr HelixApi::SendRequest(xmlDocPtr req, const twine& requestName )
{
	EnEx ee(FL, "HelixApi::SendRequest()");

	twine url; url.format("http%s://%s:%d%s", m_use_ssl ? "s" : "", m_host(), m_port, requestName() );
	twine msg = XmlHelpers::docToString( req );
	DEBUG(FL, "Sending post to (%s)", url() );
	m_response = Post( url, msg(), msg.length() );
	// check for errors:
	returnHasErrors();
	return m_response;
}

xmlDocPtr HelixApi::LoadXMLDoc(const twine& requestName )
{
	EnEx ee(FL, "HelixApi::LoadXMLDoc()");

	twine url; url.format("http%s://%s:%d%s", m_use_ssl ? "s" : "", m_host(), m_port, requestName() );
	DEBUG(FL, "Sending Get to (%s)", url() );
	m_response = GetXml( url );

	// check for errors:
	returnHasErrors();
	return m_response;
}

char* HelixApi::Get(const twine& requestPath)
{
	EnEx ee(FL, "HelixApi::Get()");

	twine url; url.format("http%s://%s:%d%s", m_use_ssl ? "s" : "", m_host(), m_port, requestPath() );
	DEBUG(FL, "Sending Get to (%s)", url() );
	return HttpClient::Get( url );
}

char* HelixApi::PostRaw(const twine& requestPath, const char* msg, size_t msgLen)
{
	EnEx ee(FL, "HelixApi::PostRaw()");

	twine url; url.format("http%s://%s:%d%s", m_use_ssl ? "s" : "", m_host(), m_port, requestPath() );
	DEBUG(FL, "Sending PostRaw to (%s)", url() );
	return HttpClient::PostRaw( url, msg, msgLen );
}

void HelixApi::SetLRTaskID( const twine& lrTaskID )
{
	EnEx ee(FL, "HelixApi::SetLRTaskID()");

	m_lr_task_id = lrTaskID;
}
