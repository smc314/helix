/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include <exception>
using namespace std;

#include "MsgProcessor.h"
#include "TheMain.h"
#include "ActionMap.h"
#include "ActionClass.h"
using namespace Helix::Glob;

#include <AutoXMLChar.h>
#include <AnException.h>
#include <dptr.h>
#include <Hash.h>
#include <EnEx.h>
#include <Tools.h>
using namespace SLib;

MsgProcessor::MsgProcessor()
{
	EnEx ee(FL, "MsgProcessor::MsgProcessor()");

	m_descr.format( "MsgProcessor (idle) Thread");

}

MsgProcessor::MsgProcessor(const MsgProcessor& c) : Threadable(c)
{
	EnEx ee(FL, "MsgProcessor::MsgProcessor(const MsgProcessor& c)");
	m_descr = c.m_descr;

}

MsgProcessor& MsgProcessor::operator=(const MsgProcessor& c)
{
	EnEx ee(FL, "MsgProcessor::operator=(const MsgProcessor& c)");
	m_descr = c.m_descr;

	return *this;
}

MsgProcessor::~MsgProcessor()
{
	EnEx ee(FL, "MsgProcessor::~MsgProcessor()");

}

void MsgProcessor::Execute(void)
{
	EnEx ee(FL, "MsgProcessor::Execute()");
	
	INFO(FL, "Execute starting: %s", m_descr());

	m_state = Threadable::Startup;
	BlockingQueue<IOConn*>& io_queue = TheMain::getInstance()->getIOQueue();

	while(!m_shutdown){
		try {
			// set our state
			m_state = Threadable::Sleeping; // We usually go to sleep waiting on the queue
			IOConn* ioc = io_queue.pop();
			m_state = Threadable::Running;
			if(ioc != NULL){
				// Process it.
				ProcessIOConn(ioc);
			}
		} catch (AnException e){
			ERRORL(FL, "Caught exception during "
				"MsgProcessor::Execute(). Message Deleted.\n%s", 
				e.Msg());
		} catch (...) {
			ERRORL(FL, "Caught unknown exception in "
				"MsgProcessor::Execute.  Message Deleted.");
		}
	}

	INFO(FL, "Execute finished");

}

void MsgProcessor::ProcessIOConn(IOConn* ioc)
{
	EnEx ee(FL, "MsgProcessor::ProcessIOConn(IOConn* ioc)", true);
	dptr<IOConn> safe_ioc; safe_ioc = ioc; // Ensure that ioc gets destroyed here.

	try {
		ActionMap& am = ActionMap::getInstance();
		ActionClass* handler = am.findAction(ioc->MsgTarget());
		dptr<ActionClass> safe_handler;
		if(handler == NULL){
			ioc->SendNotFound();
			throw AnException(0, FL, "Unknown action (%s) requested.", ioc->MsgTarget()() );
		} else if(handler->m_delete_required == true){
			safe_handler = handler; // ensure we delete when we go out of scope.
		}

		// Change our thread name to what we are doing.
		m_descr.format( "MsgProcessor (%s) Thread", ioc->MsgTarget()() );

		// Execute the request
		handler->ExecuteRequest( *ioc );

		// Ensure that the ioc is closed:
		ioc->Close();

	} catch (AnException& e){
		ERRORL(FL, "Caught exception during ProcessDocument(). Aborting.\n%s", e.Msg());
		ioc->addResponseError("Caught exception during ProcessDocument.", &e);
		ioc->SendError();
		// we need to let the http agent waiting know that we're done with the ioc.
		ioc->Close();
	} catch (std::exception& stde){
		ERRORL(FL, "Caught std::exception during ProcessDocument(). Aborting.\n%s", stde.what());
		ioc->addResponseError("Caught std::exception during ProcessDocument.", NULL);
		ioc->SendError();
		// we need to let the http agent waiting know that we're done with the ioc.
		ioc->Close();
	} catch (...) {
		ERRORL(FL, "Caught unknown exception in ProcessDocument.  Aborting");
		ioc->addResponseError("Unknown internal server error.", NULL);
		ioc->SendError();
		// we need to let the http agent waiting know that we're done with the ioc.
		ioc->Close();
	}

	m_descr.format( "MsgProcessor (idle) Thread");
}
