/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "HttpIOAdapter.h"
#include "HttpConn.h"
#include "TheMain.h"
#include "ActionMap.h"
#include "ActionClass.h"
#include "SessionList.h"
#include "LongRunningTask.h"
#include "SchedConn.h"
using namespace Helix::Glob;

#include "LRTask.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <EnEx.h>
#include <Tools.h>
#include <dptr.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

static int HttpIOAdapter_compressionThreshold;
static bool HttpIOAdapter_keepalive;

// Adds us to the global IOAdapter Registry:
IOAdapterRegister<HttpIOAdapter> HttpIOAdapter::reg("HttpIOAdapter");

HttpIOAdapter::HttpIOAdapter() : IOAdapter()
{
	EnEx ee(FL, "HttpIOAdapter::HttpIOAdapter()");

	// Defaults
	m_name = "HttpIOAdapter";
	m_port = 8082;
	m_local_ip = "";
	m_use_secure = false;
	m_sslCert = "";
	m_httpDomain = "";
	m_compressionThreshold = 1024;
	m_threads = 10;
	m_descr = "HttpIOAdapter Inbound Listener";
	m_keepalive = "no";

}

HttpIOAdapter::~HttpIOAdapter()
{
	EnEx ee(FL, "HttpIOAdapter::~HttpIOAdapter()");

}

void HttpIOAdapter::Init(xmlNodePtr n)
{
	EnEx ee(FL, "HttpIOAdapter::Init()");

	m_name.getAttribute(n, "name");
	if(m_name.empty()){
		throw AnException(0, FL, "Missing name attribute on HTTP IOAdapter node");
	}

	m_port = (int)XmlHelpers::getIntAttr(n, "listen_port");
	if(m_port == 0){
		throw AnException(0, FL, "Missing listen_port attribute on HTTP IOAdapter node");
	}

	m_local_ip.getAttribute(n, "listen_ip");

	m_use_secure = XmlHelpers::getBoolAttr(n, "secure");
	m_sslCert.getAttribute(n, "sslcert");
	m_compressionThreshold = (int)XmlHelpers::getIntAttr(n, "compressionThreshold");
	m_threads = (int)XmlHelpers::getIntAttr(n, "threads");
	if(m_threads == 0 || m_threads > 100){
		m_threads = 10;
	}
	
	m_httpDomain.getAttribute(n, "httpdomain");
	m_keepalive.getAttribute(n, "keepalive");
	if(m_keepalive.length() == 0){
		m_keepalive = "no";
	}
}

void HttpIOAdapter::Execute(void)
{
	EnEx ee(FL, "HttpIOAdapter::Execute()");

	// Set up the mongoose http server:
	char portbuf[256];
	char threads[32];
	sprintf(threads, "%d", m_threads);
	if(m_local_ip.length() != 0){
		if(m_use_secure){
			sprintf(portbuf, "%s:%ds", m_local_ip(), m_port);
		} else {
			sprintf(portbuf, "%s:%d", m_local_ip(), m_port);
		}
	} else {
		if(m_use_secure){
			sprintf(portbuf, "%ds", m_port);
		} else {
			sprintf(portbuf, "%d", m_port);
		}
	}
	const char* options[] = { 
		NULL, NULL, // listening ports go here
		NULL, NULL, // num threads go here
		NULL, NULL, // authentication domain goes here
		NULL, NULL, // keepalive option goes here
		NULL, NULL, // ssl certificate goes here
		NULL
	};
	options[0] = "listening_ports";
	options[1] = portbuf;
	options[2] = "num_threads";
	options[3] = threads;
	options[4] = "authentication_domain";
	options[5] = m_httpDomain.length() != 0 ? m_httpDomain() : "mydomain.com";
	options[6] = "enable_keep_alive";
	options[7] = m_keepalive();
	if(m_sslCert.length() != 0){
		options[8] = "ssl_certificate";
		options[9] = m_sslCert();
	}

	WARN(FL, "Starting HttpIOAdapter listening on (%s) with (%s) threads to handle connections.",
		portbuf, threads);

	// put this in a static int to that our static handler can access it
	HttpIOAdapter_compressionThreshold = m_compressionThreshold;
	HttpIOAdapter_keepalive = (m_keepalive == "yes");

	m_ctx = mg_start(HttpIOAdapter::HandleInbound, NULL, options);

	while(TheMain::getInstance()->isShutdown() == false){

		Tools::ssleep(1); // Sleep for 1 second
	}

	mg_stop(m_ctx);

}

void* HttpIOAdapter::HandleInbound(
	enum mg_event event, 
	struct mg_connection* conn, 
	const struct mg_request_info* request_info
	)
{
	EnEx ee(FL, "HttpIOAdapter::HandleInbound()", true);

	// Event logs and errors need quick handling:
	if(event == MG_EVENT_LOG){
		WARN(FL, "Mongoose Message: %s", request_info->log_message);
		return (void*)"log written";
	} else if(event == MG_HTTP_ERROR) {
		WARN(FL, "Event == MG_HTTP_ERROR");
		return NULL; // We don't handle these.
	} else if(event == MG_INIT_SSL){
		DEBUG(FL, "Mongoose Init SSL callback.");
		return NULL; // done with this one.
	}

	if(conn == NULL || request_info == NULL){
		ERRORL(FL, "Mongoose connection or request_info is NULL!  Http listener not initialized properly.");
		return NULL;
	}

	// The rest we pass off to the message handling code
	// Log details of the inbound HTTP request:
	if(Log::DebugOn() ){ // don't bother building this debug message unless debugging is turned on.
		twine http_req_info;
		http_req_info.format("Http Request Info:\n"
			"\tEvent: [%d]\n"
			"\tMethod: [%s]\n"
			"\tURI: [%s]\n"
			"\tHTTP Version: [%s]\n"
			"\tQuery String: [%s]\n"
			"\tReport IP: [%lu]\n"
			"\tReport Port: [%d]\n"
			"\tLog Message: [%s]\n"
			"Incomming HTTP Headers:\n",
			event,
			request_info->request_method,
			request_info->uri,
			request_info->http_version,
			request_info->query_string ? request_info->query_string : "",
			request_info->remote_ip,
			request_info->remote_port,
			request_info->log_message
		);

		for(int i = 0; i < request_info->num_headers; i++){
			twine tmp; tmp.format("\t[%s]: [%s]\n",
				request_info->http_headers[i].name,
				request_info->http_headers[i].value
			);
			http_req_info.append( tmp );
		}
		DEBUG(FL, "%s", http_req_info() );
	}

	/* Having issues with thread synchronization here.  The boost mutex is not
	 * getting cleared properly for some reason.

	// Create a new HttpIOConn object and send it to TheMain for processing:
	boost::condition_variable cond;
	boost::mutex cond_mutex;
	HttpConn* ioc = new HttpConn(cond, cond_mutex, event, conn, request_info);
	TheMain::getInstance()->getIOQueue().push(ioc);

	// Wait for processing to happen:
	ioc->waitForResponse();	
	if(TheMain::getInstance()->isShutdown()){
		// TheMain is shutting down.  Force a response and get out:
		mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n");
		ioc->Close();
		return "processed";
	}
	*/

	/* This works well to handle the requests directly.
	 * But it doesn't leave open the option for the ActionClass to finish the response
	 * and choose to hold onto the IOC for a little while longer to access the database
	 * or do other work while we return to the http threadpool for further processing.
	 */
	
	dptr<HttpConn> ioc; ioc = new HttpConn(event, conn, request_info, 
		HttpIOAdapter_compressionThreshold, HttpIOAdapter_keepalive);
	try {
		ActionMap& am = ActionMap::getInstance();
		ActionClass* handler = am.findAction(ioc->MsgTarget());
		dptr<ActionClass> safe_handler;

		if(handler == NULL){
			ioc->SendNotFound();
			return (void*)"processed";
		}
		if(handler->m_delete_required == true){
			safe_handler = handler; // ensure we delete when we go out of scope
		}

		if(handler->isLongRunning()){
			// Clone the input document and setup the internal connection.
			dptr<SchedConn> sc = new SchedConn( ioc->MsgTarget(), xmlCopyDoc(ioc->GetMsg(), 1) );
			sc->setSessionID( ioc->getSessionID() ); // Ensure it uses the same session that started it

			// Setup the long running task and return that immediately to tell the client to check back
			LRTask& t = LongRunningTask::getInstance().addTask( handler->lrTaskName() );
			ioc->initializeResponseDocument( t.createXmlDoc() );
			ioc->SendReturn();
			ioc->Close();

			// Now drop the internal connection off for full processing.	
			sc->lrTaskID( t.TaskID );
			TheMain::getInstance()->getIOQueue().push( sc.release() );
		} else {
			// Execute the request directly
			handler->ExecuteRequest( *ioc );
		}
		return (void*)"processed.";
	} catch (AnException& e){
		ERRORL(FL, "Caught exception during handling of http inbound.  Aborting.\n%s", e.Msg() );
		ioc->addResponseError("Caught exception during handling of http inbound.", &e);
		ioc->SendError();
	} catch (exception& e){
		ERRORL(FL, "Caught std::exception during handling of http inbound.  Aborting.\n%s", e.what() );
		ioc->addResponseError("Caught std::exception during handling of http inbound.", NULL);
		ioc->SendError();
	} catch( ... ){
		ERRORL(FL, "Caught unknown error during handling of http inbound.  Aborting." );
		ioc->addResponseError("Caught unknown error during handling of http inbound.", NULL);
		ioc->SendError();
	}

	// If we return a NULL value, that means we have not handled the connection.
	// If we return anything non-null, then we've handled it.
	return (void*)"processed";
}
