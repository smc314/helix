/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
using namespace SLib;

#include "TestStats.h"
using namespace Helix::Test;

static TestStats* m_teststats = NULL;

TestStats::TestStats()
{
	EnEx ee(FL, "TestStats::TestStats()");

	TestCount = 0;
	TestSuccess = 0;
	TestFailure = 0;
}

TestStats& TestStats::getInstance()
{
	EnEx ee(FL, "TestStats::getInstance()");

	if(m_teststats == NULL){
		m_teststats = new TestStats();
	}
	return *m_teststats;
}

TestStats::~TestStats()
{
	EnEx ee(FL, "TestStats::~TestStats()");

}

