/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

/* ***************************************************************************
	This is a testing application that will test the HTTP API's that are 
	exposed by the Helix server.
*************************************************************************** */

/* ***************************************************************************
   Output log messages look use a series of 2 character prefix symbols to
   indicate what the log messages pertain to.  Each of the different types
   can be enabled/disabled for the test run.

>> TestName - host:port
++ Optional Details about what we are doing
++ as we do it.
!! Any Errors that we see, or failed assertions about the api tests
!! will have these lines reported.
<< TestName - Success - Duration - Tests Total (123) Success (123) Failure (0)
** Total (123) Success (123) Failure (0)\n",

*************************************************************************** */

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdexcept>

#include <XmlHelpers.h>
#include <AnException.h>
using namespace SLib;

#include "HelixApi.h"

// Our Common testing utilities

const char* usage = 
	"Usage: %s [options]\n"
	"\twhere [options] include the following:\n"
	"--log-all=[true|false]            Turn on/off all of our logging. False by default.\n"
	"--log-test=[true|false]           Turn on/off test start/finish logging.  True by default.\n"
	"--log-steps=[true|false]          Turn on/off step by step logging.  False by default.\n"
	"--log-err=[true|false]            Turn on/off error logging.  True by default.\n"
	"\n"
	"--dry=[true|false]                Indicates whether we are in a dry-run.  False by default.\n"
	"                                  If true, we'll only print out the tests that would be run, but\n"
	"                                  not actually execute them.\n"
	"\n"
	"--test=apiname                    Use to tell us which api test to include.  We'll take this\n"
	"                                  string and match it to the full api path's and any api path\n"
	"                                  that includes this string will be included in the test run.\n"
	"\n"
	"--host=HostName                   Use this to specify the host name of the server.  Defaults to\n"
	"                                  localhost.\n"
	"--port=PortNum                    Use this to specify the port number on the server.  Defaults to\n"
	"                                  8082.\n"
	"--user=UserName                   Use this to provide a user name.\n"
	"--pass=UserPassword               Use this to provide a password.\n"
	"\n"
	"If you don't supply any options, or the options you do supply don't make sense to us,\n"
	"we'll print out this usage statement and help you understand which options you need\n"
	"to supply for things to work properly.\n";

// Keep track of our test statistics
int m_test_count = 0;
int m_test_success = 0;
int m_test_failure = 0;
int m_overall_count = 0;
int m_overall_success = 0;
int m_overall_failure = 0;

/* Information about the current test that we are running */
string m_test_host = "localhost";
string m_test_port = "8082";
string m_test_user;
string m_test_pass;
string m_test_apiname;

/* Logging parameters to control what we output */
bool m_log_all = false;
bool m_log_test = true;
bool m_log_steps = false;
bool m_log_err = true;
bool m_log_html = false;

/* If we are doing a test-no-execute run, then this will be true */
bool m_dry_run = false;

/* Our connection to the Helix server */
Helix::Client::HelixApi* m_api = NULL;

/** This class helps us to track test method entry/exit.
  */
class TestMethodEnEx
{
	public:
		TestMethodEnEx(const char* methodName) : 
			m_method(methodName) 
		{
			if(m_log_test){
				printf(">> %s - %s:%s %s/%s\n", m_method.c_str(), 
					m_test_host.c_str() ,
					m_test_port.c_str() ,
					m_test_user.c_str() ,
					m_test_pass.c_str()
				);	
			}

			// Default to false.
			m_finish_success = false;
		}

		virtual ~TestMethodEnEx(){
			if(m_log_test){
				if(m_finish_success){
					printf("<< %s - Success - Duration - Tests Total (%d) Success (%d) Failure (%d)\n", 
						m_method.c_str(), m_test_count, m_test_success, m_test_failure );	
				} else {
					printf("<< %s - Failure - Duration - Tests Total (%d) Success (%d) Failure (%d)\n", 
						m_method.c_str(), m_test_count, m_test_success, m_test_failure );	
				}
			}
		}

		string m_method;
		bool m_finish_success;
};

/** This is a utility method for dumping sections of memory to the output for various
  * analysis
  */
void dump_mem(void* ptr, char* name, size_t prior, size_t length);

/** This is the method we use to print our total's information.
  */
void PrintTotal( bool doOverall );

/** This macro is used at the beginning of each test method and handles a number of calls
  * for us that record the entry into a test method.
  */
#define BEGIN_TEST_METHOD( a ) \
	TestMethodEnEx tmee( a ); \
	try { \
		m_test_count ++; \
		if(m_dry_run) { \
			m_test_success ++; \
			tmee.m_finish_success = true; \
			return; \
		}

/** This macros is used at the ending of each test method and handles catching exceptions
  * and recording test success or failure.
  */
#define END_TEST_METHOD \
		fflush(stdout); \
		m_test_success ++; \
		tmee.m_finish_success = true; \
	} catch (std::exception& stde){ \
		if(m_log_err) printf("!! std::exception caught during unit test: %s", stde.what() ); \
		m_test_failure ++; \
	} catch (AnException& ane){ \
		if(m_log_err) printf("!! AnException caught during unit test: %s", ane.Msg() ); \
		m_test_failure ++; \
	} catch (...){ \
		if(m_log_err) printf("!! Unknown exception caught during unit test\n" ); \
		m_test_failure ++; \
	}

/** This macro lets us bail out of a test early if we need to
  */
#define QUIT_TEST_METHOD \
		m_test_success ++; \
		tmee.m_finish_success = true; \
		return;

/** Tests if two items are equals using C++ == comparison.
  */
#define ASSERT_EQUALS(a,b,c) \
	if( (a) == (b) ) {\
	} else { \
		if(m_log_err) printf( "!! %s\n", c); \
		m_test_failure++; \
		return; \
	}

/** Tests if two items are not equal using C++ != comparison.
  */
#define ASSERT_NOTEQUALS(a,b,c) \
	if( (a) != (b) ) {\
	} else { \
		if(m_log_err) printf( "!! %s\n", c); \
		m_test_failure++; \
		return; \
	}

/** Tests if a given value is true.
  */
#define ASSERT_TRUE(a,b) \
	if( (a) ){\
	} else { \
		if(m_log_err) printf( "!! %s\n", b); \
		m_test_failure++; \
		return; \
	}

/** Tests if a given value is false.
  */
#define ASSERT_FALSE(a,b) \
	if( !(a) ){\
	} else { \
		if(m_log_err) printf( "!! %s\n", b); \
		m_test_failure++; \
		return; \
	}

/** Tests if a given value is not null.
  */
#define ASSERT_NOTNULL(a,b) \
	if( (a) == NULL ){\
		if(m_log_err) printf( "!! %s\n", b); \
		m_test_failure++; \
		return; \
	}

/** Tests if a given value is null.
  */
#define ASSERT_NULL(a,b) \
	if( (a) != NULL ){\
		if(m_log_err) printf( "!! %s\n", b); \
		m_test_failure++; \
		return; \
	}

bool runTestsForApi(string apiName);
void RunApiTests();
void ParseArgs(int argc, char** argv);
void SetLogParm(const string& arg, bool* logParm);

#include "HelixApiTest.h"

int main(int argc, char** argv)
{
	if(argc == 1){
		printf(usage, argv[0]);
		return EXIT_FAILURE;
	}
	ParseArgs(argc, argv);

	RunApiTests(); // Run all of our tests

	PrintTotal( true ); // print the overall totals

	return EXIT_SUCCESS;
}

void ParseArgs(int argc, char** argv)
{
	for(int i = 1; i < argc; i++){
		string arg = argv[i];

		if(arg.find("--log-all=") == 0){
			SetLogParm( arg, &m_log_all );			
		} else if(arg.find("--log-test=") == 0){
			SetLogParm( arg, &m_log_test );			
		} else if(arg.find("--log-steps=") == 0){
			SetLogParm( arg, &m_log_steps );			
		} else if(arg.find("--log-err=") == 0){
			SetLogParm( arg, &m_log_err );			
		} else if(arg.find("--dry=") == 0){
			SetLogParm( arg, &m_dry_run);			
		} else if(arg.find("--test=") == 0){
			m_test_apiname = arg.substr(7);
		} else if(arg.find("--host=") == 0){
			m_test_host = arg.substr(7);
		} else if(arg.find("--port=") == 0){
			m_test_port = arg.substr(7);
		} else if(arg.find("--user=") == 0){
			m_test_user = arg.substr(7);
		} else if(arg.find("--pass=") == 0){
			m_test_pass = arg.substr(7);
		} else {
			printf("Unknown argument \"%s\"\n", arg.c_str() );
			printf(usage, argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	// Sanity checks:

	// Update logging parms if log-all is true:
	if(m_log_all){
		m_log_test = true;
		m_log_steps = true;
		m_log_err = true;
	}

}

void SetLogParm(const string& arg, bool* logParm)
{
	size_t eq = arg.find("=");
	eq++;
	string val = arg.substr(eq);
	if(val == "true" ||
		val == "True" ||
		val == "TRUE" ||
		val == "yes" ||
		val == "Yes" ||
		val == "YES" ||
		val == "on" ||
		val == "On" ||
		val == "ON" ||
		val == "1"
	){
		*logParm = true;
	} else {
		*logParm = false;
	}
}

void PrintTotal( bool doOverall )
{
	if(doOverall){
		printf("== OVERALL Total (%d) Success (%d) Failure (%d)\n",
			m_overall_count, m_overall_success, m_overall_failure 
		);	
	} else {
		printf("** %s.%s Total (%d) Success (%d) Failure (%d)\n",
			m_test_host.c_str(), m_test_port.c_str(),
			m_test_count, m_test_success, m_test_failure 
		);	
	}

}

bool runTestsForApi(string apiName)
{
	if(apiName.find( m_test_apiname ) == string::npos){
		return false; // didn't find the filter text in the given api
	} else {
		return true; // found the filter text - run this test
	}
}

void RunApiTests()
{
	m_api = new Helix::Client::HelixApi(m_test_host.c_str(), atoi(m_test_port.c_str()));

	// Invoke all of our test methods here directly:
	ApiTest_logic_dev_GetHelixProject();
	ApiTest_logic_dev_SaveHelixProject();
	ApiTest_logic_dev_GetHelixProjectList();
	ApiTest_logic_util_GetLogMsgCount();
	ApiTest_logic_util_CloseConnection();
	ApiTest_logic_util_GetAllLayouts();
	ApiTest_logic_util_GetLogSettings();
	ApiTest_logic_util_GetLogMessagesByRange();
	ApiTest_logic_util_GetHitMap();
	ApiTest_logic_util_CleanoutLRTask();
	ApiTest_logic_util_GetAllLRTasks();
	ApiTest_logic_util_SaveLogMsg();
	ApiTest_logic_util_FindLogMessage();
	ApiTest_logic_util_UpdateLogSettings();
	ApiTest_logic_util_GetProfile();
	ApiTest_logic_util_GetOneLRTask();
	ApiTest_logic_util_SwitchServerConnection();
	ApiTest_logic_util_ExecuteGenericSQL();
	ApiTest_logic_util_GetLogMessages();
	ApiTest_logic_util_GetLogFiles();
	ApiTest_logic_admin_InsertScheduleItem();
	ApiTest_logic_admin_UpdateScheduleItem();
	ApiTest_logic_admin_SaveSQLWork();
	ApiTest_logic_admin_DeleteSQLWork();
	ApiTest_logic_admin_DeleteScheduleItem();
	ApiTest_logic_admin_DeleteIAFile();
	ApiTest_logic_admin_LoadSQLTestMeta();
	ApiTest_logic_admin_GetOneScheduleItem();
	ApiTest_logic_admin_GetIAFileList();
	ApiTest_logic_admin_SaveIAFile();
	ApiTest_logic_admin_GetSQLTest();
	ApiTest_logic_admin_GetIAFileDetails();
	ApiTest_logic_admin_GetWorkFileList();
	ApiTest_logic_admin_GetScheduleItems();
	ApiTest_logic_admin_SaveSQLTest();
	ApiTest_logic_admin_GetSQLWork();

	delete m_api;

	PrintTotal( false );
	m_overall_count += m_test_count;
	m_overall_success += m_test_success;
	m_overall_failure += m_test_failure;
	m_test_count = 0;
	m_test_success = 0;
	m_test_failure = 0;
	return;
}

/* ************************************************************************************ */
/* Beyond here are various utility methods used by everyone.                            */
/* ************************************************************************************ */

void dump_mem(void* ptr, char* name, size_t prior, size_t length)
{
	if(!m_log_steps) return; // skip dumping memory if log steps is not on.

	if(ptr == NULL){
		printf("++ dump_mem: %s - NULL Pointer\n", name );
		return;
	}

	char* bptr = (char*)ptr; // so that indexing works.
	char* aptr = bptr - prior;
	char* cptr = bptr + length;
	printf("++ dump_mem: %s - [%p - _%p_ - %p)\n", name, aptr, bptr, cptr );
	printf("++         +00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n" );
	while( aptr < cptr ){
		printf("++ %p ", aptr);
		for(int i = 0; i < 16 && aptr < cptr; i++, aptr++){
			printf("%.2X ", (unsigned)(unsigned char)aptr[ 0 ] );
		}
		printf("\n");
	}

}

