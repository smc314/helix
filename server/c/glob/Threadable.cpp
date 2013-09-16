/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "Threadable.h"
using namespace Helix::Glob;

#include "AnException.h"
#include "EnEx.h"
using namespace SLib;

#include <stdexcept>

Threadable::Threadable()
{
	EnEx ee(FL, "Threadable::Threadable()");

	m_state = Threadable::Init;
	m_shutdown = false;
	m_reread_config = false;

	// This should be re-set by each child class
	m_descr = "Generic Threadable";

}

Threadable::Threadable(const Threadable& c)
{
	EnEx ee(FL, "Threadable::Threadable(const Threadable& c)");

	m_state = Threadable::Init;
	m_shutdown = false;
	m_reread_config = false;
	m_descr = c.m_descr;

}

Threadable& Threadable::operator=(const Threadable& c)
{
	EnEx ee(FL, "Threadable::operator=(const Threadable& c)");

	m_state = c.m_state;
	m_shutdown = c.m_shutdown;
	m_reread_config = c.m_reread_config;
	m_descr = c.m_descr;

	return *this;
}

Threadable::~Threadable()
{
	EnEx ee(FL, "Threadable::~Threadable()");
	m_state = Threadable::Done;
	m_shutdown = true;
}

void Threadable::PreExecute(void)
{
	EnEx ee(FL, "Threadable::PreExecute()");

	// Set our state
	m_state = Threadable::Startup;

	// Add ourselves to the global thread list
	TheMain::getInstance()->GetThreadList().AddThreadable(this);	

}

void Threadable::PostExecute(void)
{
	EnEx ee(FL, "Threadable::PostExecute()");

	// Set our state
	m_state = Threadable::Finishing;

	// Remove ourselves from the global thread list
	TheMain::getInstance()->GetThreadList().RemoveThreadable(this);

}

int Threadable::Status(void)
{
	EnEx ee(FL, "Threadable::Status()");
	return m_state;
}

void Threadable::Shutdown(void)
{
	EnEx ee(FL, "Threadable::Shutdown()");

	m_shutdown = true;

}

void Threadable::ReReadConfig(void)
{
	EnEx ee(FL, "Threadable::ReReadConfig()");

	m_reread_config = true;

}

twine& Threadable::Description(void)
{
	EnEx ee(FL, "Threadable::Description()");
	return m_descr;
}

void Threadable::ThreadID(THREAD_ID_TYPE tid)
{
	EnEx ee(FL, "Threadable::ThreadID(THREAD_ID_TYPE tid)");
	m_tid = tid;
}

THREAD_ID_TYPE Threadable::ThreadID(void)
{
	EnEx ee(FL, "Threadable::ThreadID()");
	return m_tid;
}

void* Threadable::Start(void* arg)
{
	EnEx ee(FL, "Threadable::Start()", true);

	// Cast the argument
	Threadable* t = (Threadable*)arg;

	// Set our thread id in the threadable object:
	t->ThreadID(CURRENT_THREAD_ID);
	
	// If PreExecute fails, then don't do anything else.
	// If PreExecute goes well, then guarantee to call
	// PostExecute, even if an exception happens in Execute().
	
	try {
		t->PreExecute();
	} catch (AnException& e){
		ERRORL(FL, "Exception during PreExecute: %s", e.Msg());
		return (void*)NULL;
	} catch (std::exception& stde){
		ERRORL(FL, "STD::Exception during PreExecute: %s", stde.what() );
		return (void*)NULL;
	} catch (...){
		ERRORL(FL, "Unknown Exception during PreExecute.");
		return (void*)NULL;
	}

	try {
		t->Execute();
	} catch (AnException& e) {
		ERRORL(FL, "Exception during Execute: %s", e.Msg());
	} catch (std::exception& stde){
		ERRORL(FL, "STD::Exception during Execute: %s", stde.what() );
	} catch (...){
		ERRORL(FL, "Unknown Exception during Execute");
	}

	try {
		t->PostExecute();
	} catch (AnException& e){
		ERRORL(FL, "Exception during PostExecute: %s", e.Msg());
	} catch (std::exception& stde){
		ERRORL(FL, "STD::Exception during PostExecute: %s", stde.what() );
	} catch (...){
		ERRORL(FL, "Unknown Exception during PostExecute");
	}

	return (void*)NULL;
}
