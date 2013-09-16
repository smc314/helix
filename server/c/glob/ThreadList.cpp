/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "ThreadList.h"
using namespace Helix::Glob;

#include "AnException.h"
#include "EnEx.h"
using namespace SLib;

#include <algorithm>
using namespace std;

ThreadList::ThreadList()
{
	EnEx ee(FL, "ThreadList::ThreadList()");

	m_mut = new Mutex();

}

ThreadList::~ThreadList()
{
	EnEx ee(FL, "ThreadList::~ThreadList()");
	delete m_mut;
}

void ThreadList::AddThreadable(Threadable* t)
{
	Lock the_lock(m_mut);
	EnEx ee(FL, "ThreadList::AddThreadable()");

	// The suvector will ensure that if t is already
	// in the vector that it doesn't get added a
	// second time.
	m_threads.push_back(t);

}

void ThreadList::RemoveThreadable(Threadable* t)
{
	Lock the_lock(m_mut);
	EnEx ee(FL, "ThreadList::RemoveThreadable()");

	vector<Threadable*>::iterator lb = lower_bound(
		m_threads.begin(), m_threads.end(), t);

	if(lb == m_threads.end()){
		// Not found, and iterator points to the end of the
		// vector.  That's bad
		throw AnException(0, FL, "Threadable not found in ThreadList");
	} else if(*lb != t) {
		// Not found, and iterator points to the middle of the
		// vector where it should be inserted.  That's bad
		throw AnException(0, FL, "Threadable not found in ThreadList");
	} else {
		// found.  Remove it.
		m_threads.erase(lb);
	}

}

twine ThreadList::DescribeThreads(void)
{
	Lock the_lock(m_mut);
	EnEx ee(FL, "ThreadList::DescribeThreads()");

	twine ret;
	twine tmp;
	int i;

	ret = "Thread List Contents:\n";

	for(i = 0; i < (int)m_threads.size(); i++){
		Threadable* th = m_threads[i];
		tmp.format("Thread[%ld] State[%.2d] Descr[%s]\n",
			th->ThreadID(), th->Status(), th->Description()() );
		ret += tmp;
	}

	return ret;
}
