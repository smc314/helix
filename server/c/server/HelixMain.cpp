/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <AnException.h>
#include <Tools.h>
#include <EnEx.h>
using namespace SLib;

#include "TheMain.h"
using namespace Helix::Glob;

static bool in_sighandler = false;
void sighandler(int param);

#ifdef _WIN32
LONG WINAPI OurCrashHandler(EXCEPTION_POINTERS* /*Exception Info*/);
#endif

int main(int argc, char** argv)
{
	char *p_config_file_name = NULL;

	// Set up our signal handlers to catch and gracefully terminate if something goes wrong
	signal( SIGABRT, sighandler);
	signal( SIGFPE, sighandler);
	signal( SIGILL, sighandler);
	signal( SIGINT, sighandler);
	signal( SIGSEGV, sighandler);
	signal( SIGTERM, sighandler);

#ifdef _WIN32
	::SetUnhandledExceptionFilter(OurCrashHandler);
#endif

	try {
		if(argc > 1) {
			p_config_file_name = argv[1];
		}
		TheMain tm(p_config_file_name);
		tm.Execute();
	} catch (AnException e){
		printf("Last level exception caught:\n%s",
			e.Msg());
		return 129;
	} catch (...) {
		printf("Last level unknown exception caught.\n");
		return 130;
	}
	return 0;
}

#ifdef _WIN32
LONG WINAPI OurCrashHandler(EXCEPTION_POINTERS* ep)
{
	sighandler(SIGSEGV);
	return EXCEPTION_EXECUTE_HANDLER;
}
#endif


/** This is our signal handler.  It is used to catch all signals that may be
 *  sent for this program.  This will dump our logs and then
 *  ensure that everything shuts down properly.
 */
void sighandler(int param)
{
	char* signame;
	switch(param){
		case SIGABRT: signame = (char*)"SIGABRT"; break;
		case SIGFPE: signame = (char*)"SIGFPE"; break;
		case SIGILL: signame = (char*)"SIGILL"; break;
		case SIGINT: signame = (char*)"SIGINT"; break;
		case SIGSEGV: signame = (char*)"SIGSEGV"; break;
		case SIGTERM: signame = (char*)"SIGTERM"; break;
		default: signame = (char*)"UNKNOWN";
	}

	if(in_sighandler){
		// We're getting called again.  Something is going wrong during
		// shutdown.  Log this to the console and exit.
		printf("%s: called recursively.  Error in signal handler and shutdown!\n", signame);
		if(param == SIGABRT){
			// just return from this method - that will allow the usual abort process to go through
			return;
		}
		// otherwise - raise the abort ourselves.
		abort();
	}
	in_sighandler = true; // watch for recursive calls to this method.

	PANIC(FL, "%s called.  Flushing and closing logs and shutting down TheMain.", signame);
	printf("%s: called.  Flushing and closing logs and shutting down TheMain.\n", signame);
	EnEx::PrintStackTrace( 0 ); // dump our stack trace to the Panic channel.
	EnEx::PrintStackTrace( ); // dump our stack trace to stdout
	TheMain* tm = TheMain::getInstance();
	tm->Shutdown();
	int max = 4;
	int count = 0;
	while(count < max){ // only wait for up to 2 seconds.
		Tools::msleep( 500 ); // wait for half a second
		if(tm->isShutdownDone()){
			break;
		}
		count ++;
	}
	if(count == max){
		printf("%s: Program shutdown forced.\n", signame);
	} else {
		printf("%s: Program shutdown complete.\n", signame);
	}
	exit(0);
}
