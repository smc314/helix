/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "MsgProcScaler.h"
#include "MsgProcessor.h"
using namespace Helix::Glob;

#include "AnException.h"
#include "Log.h"
#include "Tools.h"
#include "EnEx.h"
using namespace SLib;

MsgProcScaler::MsgProcScaler(const twine& name)
{
	EnEx ee(FL, "MsgProcScaler::MsgProcScaler()");

	m_name = name;
	m_is_shutdown_restart = false;

	m_descr.format("Processor (%s) Driver Thread", m_name());
	
}

MsgProcScaler::MsgProcScaler(const MsgProcScaler& c) :
	Scaler(c)
{
	EnEx ee(FL, "MsgProcScaler::MsgProcScaler(const MsgProcScaler& c)");

	m_name = c.m_name;
}

MsgProcScaler& MsgProcScaler::operator=(const MsgProcScaler& c)
{
	EnEx ee(FL, "MsgProcScaler::operator=(const MsgProcScaler& c)");

	Scaler::operator=(c);
	m_name = c.m_name;

	return *this;
}

MsgProcScaler::~MsgProcScaler()
{
	EnEx ee(FL, "MsgProcScaler::~MsgProcScaler()");
	// Nothing at the moment.
}

void MsgProcScaler::Execute()
{
	EnEx ee(FL, "MsgProcScaler::Execute()");

	do {
		INFO(FL, "Processor Driver (%s) Execute starting", m_name());
		m_is_shutdown_restart = false;
		Scaler::Execute();
		if(m_is_shutdown_restart){
			m_shutdown = false;
			INFO(FL, "Processor Driver (%s) Down for restart",
				m_name() );
		}
	} while(m_is_shutdown_restart);

}

Threadable* MsgProcScaler::CreateThreadable(void)
{
	EnEx ee(FL, "MsgProcScaler::CreateThreadable()");
	return new MsgProcessor();
}

int MsgProcScaler::GetSize()
{
	// Commented out to avoid the logs becomming too chatty
	//EnEx ee(FL, "MsgProcScaler::GetSize()");
	return TheMain::getInstance()->getIOQueue().size();
}

void MsgProcScaler::ShutdownRestart(void)
{
	EnEx ee(FL, "MsgProcScaler::ShutdownRestart()");

	m_is_shutdown_restart = true;
	Shutdown();

}
