/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "SchedConn.h"
#include "LongRunningTask.h"
using namespace Helix::Glob;

#include <Date.h>
#include <EnEx.h>
#include <Log.h>
#include <File.h>
#include <memptr.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

SchedConn::SchedConn(const twine& msgTarget, xmlDocPtr msg) : IOConn()
{
	EnEx ee(FL, "SchedConn::SchedConn()");
	if(msg != NULL){
		m_doc = msg;
	} else {
		// create an empty XML document - this is important for storing our
		// session information
		m_doc = xmlNewDoc((const xmlChar*)"1.0");
		m_doc->children = xmlNewDocNode( m_doc, NULL, (const xmlChar*)"SchedConn", NULL );
	}
	m_doc_loaded = true;
	m_msg_target = msgTarget;
}

SchedConn::~SchedConn()
{
	EnEx ee(FL, "SchedConn::~SchedConn()");

	if(m_doc != NULL){
		xmlFreeDoc(m_doc);
		m_doc = NULL;
		m_doc_loaded = false;
	}

}

twine SchedConn::MsgTarget()
{
	EnEx ee(FL, "SchedConn::MsgTarget()");
	if(!m_override_target.empty()){
		return m_override_target;
	} else {
		return m_msg_target;
	}
}

xmlDocPtr SchedConn::GetMsg()
{
	EnEx ee(FL, "SchedConn::GetMsg()");
	return m_doc;
}

xmlNodePtr SchedConn::GetRequestRoot(void)
{
	EnEx ee(FL, "SchedConn::GetRequestRoot()");

	xmlDocPtr doc = GetMsg();
	if(doc == NULL){
		throw AnException(0, FL, "No input Request document found.");
	}

	// Return the root element.
	return xmlDocGetRootElement(doc);
}

void SchedConn::SendReturn() 
{
	EnEx ee(FL, "SchedConn::SendReturn()");
	if(m_resp_doc == NULL){
		initializeResponseDocument("Response");
	}
	if(m_lr_taskid.length() == 0){
		return; // nothing to do
	}

	// Attach our response document to the long running task so that it can be sent back to
	// the caller on the final request of the client polling job.
	LongRunningTask& lrt = LongRunningTask::getInstance();
	if(lrt.hasTask( m_lr_taskid ) ){
		try {
			lrt.finishTask( m_lr_taskid, m_resp_doc );
		} catch (AnException& e){
			// ignore this
		}
	}
}

void SchedConn::SendReturn(
		unsigned char* data, 
		int dataLen, 
		twine fileName, 
		Date lastModified, 
		Date expires) 
{
	EnEx ee(FL, "SchedConn::SendReturn(unsigned char* data)");
	throw AnException(0, FL, "Not implemented in SchedConn.");
}

void SchedConn::SendReturn(twine& filePath, twine& fileName, Date lastModified, Date expires)
{
	EnEx ee(FL, "SchedConn::SendReturn(twine& filePath)");
	throw AnException(0, FL, "Not implemented in SchedConn.");
}

void SchedConn::SendError() 
{
	EnEx ee(FL, "SchedConn::SendError()");

	SendReturn();
}

void SchedConn::SendNotFound() 
{
	EnEx ee(FL, "SchedConn::SendNotFound()");

	SendReturn();
}
