/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#ifndef HTEST_H
#define HTEST_H

#include <map>
using namespace std;

#include <twine.h>
#include <AnException.h>
using namespace SLib;

#include "TestCache.h"
#include "TestStats.h"
#include "TestLog.h"

namespace Helix {
namespace Test {

/** This class helps us to track test method entry/exit.
  */
class TestMethodEnEx
{
	public:
		TestMethodEnEx(const char* methodName) : 
			m_method(methodName) 
		{
			TestLog::LogTest(true, false, m_method);
			// Default to false.
			m_finish_success = false;
		}

		virtual ~TestMethodEnEx(){
			TestLog::LogTest(false, m_finish_success, m_method);
		}

		twine m_method;
		bool m_finish_success;
};

/** This macro is used at the beginning of each test method and handles a number of calls
  * for us that record the entry into a test method.
  */
#define BEGIN_TEST_METHOD( a ) \
	TestMethodEnEx tmee( a ); \
	try { \
		TestStats::getInstance().TestCount ++;\
		if(m_dry_run) { \
			TestStats::getInstance().TestSuccess ++;\
			tmee.m_finish_success = true; \
			return; \
		}

/** This macros is used at the ending of each test method and handles catching exceptions
  * and recording test success or failure.
  */
#define END_TEST_METHOD \
		fflush(stdout); \
		TestStats::getInstance().TestSuccess ++;\
		tmee.m_finish_success = true; \
	} catch (std::exception& stde){ \
		TestLog::LogError( (twine msg).format("!! std::exception caught during unit test: %s", stde.what() ) ); \
		TestStats::getInstance().TestFailure ++;\
	} catch (AnException& ane){ \
		TestLog::LogError( (twine msg).format("!! AnException caught during unit test: %s", ane.Msg() ) ); \
		TestStats::getInstance().TestFailure ++;\
	} catch (...){ \
		TestLog::LogError( (twine msg).format("!! Unknown exception caught during unit test" ) ); \
		TestStats::getInstance().TestFailure ++;\
	}

/** This macro lets us bail out of a test early if we need to
  */
#define QUIT_TEST_METHOD \
		TestStats::getInstance().TestSuccess ++;\
		tmee.m_finish_success = true; \
		return;

/** Tests if two items are equals using C++ == comparison.
  */
#define ASSERT_EQUALS(a,b,c) \
	if( (a) == (b) ) {\
	} else { \
		TestLog::LogError(c); \
		TestStats::getInstance().TestFailure ++;\
		return; \
	}

/** Tests if two items are not equal using C++ != comparison.
  */
#define ASSERT_NOTEQUALS(a,b,c) \
	if( (a) != (b) ) {\
	} else { \
		TestLog::LogError(c); \
		TestStats::getInstance().TestFailure ++;\
		return; \
	}

/** Tests if a given value is true.
  */
#define ASSERT_TRUE(a,b) \
	if( (a) ){\
	} else { \
		TestLog::LogError(b); \
		TestStats::getInstance().TestFailure ++;\
		return; \
	}

/** Tests if a given value is false.
  */
#define ASSERT_FALSE(a,b) \
	if( !(a) ){\
	} else { \
		TestLog::LogError(b); \
		TestStats::getInstance().TestFailure ++;\
		return; \
	}

/** Tests if a given value is not null.
  */
#define ASSERT_NOTNULL(a,b) \
	if( (a) == NULL ){\
		TestLog::LogError(b); \
		TestStats::getInstance().TestFailure ++;\
		return; \
	}

/** Tests if a given value is null.
  */
#define ASSERT_NULL(a,b) \
	if( (a) != NULL ){\
		TestLog::LogError(b); \
		TestStats::getInstance().TestFailure ++;\
		return; \
	}



} } // End namespace stack

#endif // HTEST_H Defined
