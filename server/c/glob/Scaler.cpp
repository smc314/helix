/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "Scaler.h"
using namespace Helix::Glob;

#include "Tools.h"
#include "Log.h"
#include "AnException.h"
#include "EnEx.h"
using namespace SLib;

Scaler::Scaler() : Threadable()
{
	EnEx ee(FL, "Scaler::Scaler()");

	// We hard code these.  Sub classes can adjust them
	// as they see fit.
	m_min_threads = 30;
	m_max_threads = 50;
	m_adjust_size = 5;
	m_target_size = 3;

	m_start_wait_time = 10; // seconds
	m_stop_wait_time = 10; // seconds

	// Initialze the timers.
	m_last_started.Start();
	m_last_stopped.Start();

	m_descr = "Scaler Threadable";
}

Scaler::Scaler(const Scaler& c) : Threadable(c)
{
	EnEx ee(FL, "Scaler::Scaler(const Scaler& c)");

	m_min_threads = c.m_min_threads;
	m_max_threads = c.m_max_threads;
	m_adjust_size = c.m_adjust_size;
	m_target_size = c.m_target_size;

}

Scaler& Scaler::operator=(const Scaler& c)
{
	EnEx ee(FL, "Scaler::operator=(const Scaler& c)");

	Threadable::operator=(c);
	m_min_threads = c.m_min_threads;
	m_max_threads = c.m_max_threads;
	m_adjust_size = c.m_adjust_size;
	m_target_size = c.m_target_size;

	return *this;
}

Scaler::~Scaler()
{
	EnEx ee(FL, "Scaler::~Scaler()");

	// Ensure that all threads are stopped
	StopAllThreads();

}
	
void Scaler::Execute(void)
{
	EnEx ee(FL, "Scaler::Execute()");

	int qsz;

	INFO(FL, "Scaler Execute starting");

	m_state = Threadable::Startup;

	StartThreads();

	try {
		while(!m_shutdown) {
			// set our state
			m_state = Threadable::Running;

			// Scale up/down based on size of our private queue
			qsz = GetSize();
			if( (qsz > m_target_size) && (m_thread_pool.size() < m_max_threads))
			{
				// see if we've waited long enough before
				// starting more threads.
				m_last_started.Finish(); // time stamp it
				if(m_last_started.Duration() > m_start_wait_time){
					StartThreads(); // start more threads
				}
			}

			if( (qsz == 0) && (m_thread_pool.size() > m_min_threads))
			{
				// see if we've waited long enough before
				// stopping some threads.
				m_last_stopped.Finish(); // time stamp it
				if(m_last_stopped.Duration() > m_stop_wait_time){
					ReduceThreads(); // stop some threads
				}
			}

			// Short nap
			m_state = Threadable::Sleeping;
			Tools::msleep(100); // 1/10th second
			m_state = Threadable::Running;
		}
	} catch (AnException& e){
		ERRORL(FL, "Caught exception during Scaler processing.  Aborting.\n%s", e.Msg());
	} catch (std::exception& stde){
		ERRORL(FL, "Caught std::exception during Scaler processing.  Aborting.\n%s", stde.what());
	} catch (...){
		ERRORL(FL, "Caught unknown exception in Scaler. Aborting");
	}

	try {
		StopAllThreads();
	} catch (...) {
		PANIC(FL, "Error shuting down Scaler Threads.");
	}

}

void Scaler::StartThreads(void)
{
	EnEx ee(FL, "Scaler::StartThreads()");

	int idx;
	dptr <Thread> th;
	dptr <Threadable> tb;

	try {
		for(idx = 0; idx < m_adjust_size; idx ++){
			// don't add any more if we're at the max.
			if(m_thread_pool.size() == m_max_threads){
				break;
			}

			// add another thread:
			th = new Thread();
			tb = CreateThreadable();

			th->start(Threadable::Start, tb);

			pair < Thread*, Threadable* > p;
			p.first = th.release();
			p.second = tb.release();
			m_thread_pool.push_back(p);

		}
		// Keep track of when we started the threads:
		m_last_started.Start();

	} catch (AnException e){
		ERRORL(FL, "Error:\n%s\nOccurred while starting Scaler threads", e.Msg());
	} catch (...){
		ERRORL(FL, "Unknown Error while starting Scaler threads");
	}
}

void Scaler::ReduceThreads(void)
{
	EnEx ee(FL, "Enter Scaler::ReduceThreads()");

	int count = 0;
	int i = 0;

	try {
		while(count < m_adjust_size){
			// don't reduce any more if we're at the min
			if(m_thread_pool.size() == m_min_threads){
				break;
			}

			// Find a thread that is sleeping
			pair < Thread*, Threadable* > p;
			bool found_idle_thread = false;
			for(i = 0; i < (int)m_thread_pool.size(); i++){
				if(m_thread_pool[i].second->Status() == Threadable::Sleeping){
					p = m_thread_pool[i];
					found_idle_thread = true;
					break;
				}
			}

			if(found_idle_thread == false){
				// found no idle threads to shutdown.
				INFO(FL, "Found no idle threads to shutdown.  Skipping ReduceThreads.");
				break;
			}
				
			// Tell the threadable object to stop processing.
			p.second->Shutdown();
			// Join on the thread until it is done.
			p.first->join();

			// Delete both objects.
			delete p.second;
			delete p.first;

			// Remove the element from the vector:
			m_thread_pool.erase(m_thread_pool.begin() + i);

		}
		// keep track of when we stopped thr threads
		m_last_stopped.Start();

	} catch (AnException e){
		ERRORL(FL, "Error:\n%s\nOccurred while stopping Scaler threads",
			e.Msg());
	} catch (...){
		ERRORL(FL, "Unkown Error while stopping Scaler threads");
	}

}

void Scaler::StopAllThreads(void)
{
	EnEx ee(FL, "Scaler::StopAllThreads()");

	int i;
	try {
		for(i = 0; i < (int)m_thread_pool.size(); i++){
			pair < Thread*, Threadable* > p;
			p = m_thread_pool[i];

			// Tell the threadable object to stop processing.
			p.second->Shutdown();
			// Join on the thread until it is done.
			p.first->join();

			// Delete both objects.
			delete p.second;
			delete p.first;
		}
		// Ensure that the vector is cleared out.
		m_thread_pool.clear();
	} catch (AnException e){
		ERRORL(FL, "Error:\n%s\nOccurred while stopping all Scaler threads",
			e.Msg());
	} catch (...){
		ERRORL(FL, "Unkown Error while stopping all Scaler threads");
	}

}
