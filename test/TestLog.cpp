/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
using namespace SLib;

#include "TestLog.h"
#include "TestCache.h"
#include "TestStats.h"
using namespace Helix::Test;

static TestLog* m_testlog = NULL;

TestLog::TestLog()
{
	EnEx ee(FL, "TestLog::TestLog()");

	LogAll = TestCache::getBool("LogAll");
	LogTests = TestCache::getBool("LogTest");
	LogSteps = TestCache::getBool("LogSteps");
	LogErrors = TestCache::getBool("LogError");
	LogHtmls = TestCache::getBool("LogHtml");
}

TestLog& TestLog::getInstance()
{
	EnEx ee(FL, "TestLog::getInstance()");

	if(m_testlog  == NULL){
		m_testlog  = new TestLog();
	}
	return *m_testlog ;
}

TestLog::~TestLog()
{
	EnEx ee(FL, "TestLog::~TestLog()");

}

void TestLog::LogTest(bool in, bool fail, const twine& methodName)
{
	TestLog& tl = TestLog::getInstance();
	TestStats& ts = TestStats::getInstance();
	if(tl.LogAll || tl.LogTests){
		if(in){
			printf(">> %s - %s:%s %s/%s\n", 
				methodName(),
				TestCache::get("TestHost")(),
				TestCache::get("TestPort")(),
				TestCache::get("TestUser")(),
				TestCache::get("TestPass")()
			);
		} else {
			printf("<< %s - %s - Duration - Tests Total (%d) Success (%d) Failure (%d)\n",
				methodName(), 
				fail ? "Failure" : "Success",
				ts.TestCount, ts.TestSuccess, ts.TestFailure 
			);
		}
	}
}

void TestLog::LogStep(const twine& message)
{
	TestLog& tl = TestLog::getInstance();
	if(tl.LogAll || tl.LogSteps){
		printf("++ %s\n", message() );
	}
}

void TestLog::LogError(const twine& message)
{
	TestLog& tl = TestLog::getInstance();
	if(tl.LogAll || tl.LogErrors){
		printf("!! %s\n", message() );
	}
}

void TestLog::LogHtml(const twine& message)
{
	TestLog& tl = TestLog::getInstance();
	if(tl.LogAll || tl.LogHtmls){
		printf("<> %s\n", message() );
	}
}


