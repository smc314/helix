/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */
/* ***************************************************************************
This is the Linux daemon version of SvcMain.  Our job is to keep HelixMain running
at all times, except when we are asked to shut down.  As we are shutting down,
we will bring HelixMain down as well - nicely or forcibly as the case may be.

We implement the Daemon process as defined here:
http://netzmafia.de/skripten/unix/linux-daemon-howto.html

This ensures we play well with others and behave as a proper daemon should.
*************************************************************************** */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

pid_t child_pid, our_sid;
static bool in_sighandler = false;
void sighandler(int param);
void doDaemon(void);

int main(int argc, char** argv)
{
	// Make ourselves into a daemon
	doDaemon();

	// Set up our signal handlers to catch and gracefully terminate if something goes wrong
	signal( SIGABRT, sighandler);
	signal( SIGFPE, sighandler);
	signal( SIGILL, sighandler);
	signal( SIGINT, sighandler);
	signal( SIGSEGV, sighandler);
	signal( SIGTERM, sighandler);
	signal( SIGQUIT, sighandler);

	// Launch HelixMain and Ensure it stays up
	while(1){
		int ret = system("./HelixMain");		
		if(WIFSIGNALED(ret) && 
			(WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)
		){
			break; // Someone told our child process to shutdown.
		}
	}

	return 0;
}


/** This method handles daemon-ising our process.  We follow the pattern laid out in
  * the how-to: http://netzmafia.de/skripten/unix/linux-daemon-howto.html
  */
void doDaemon(void)
{
	// Fork off the parent process:
	child_pid = fork();
	if(child_pid < 0){
		printf("Unable to fork our child process.\n");
		exit(EXIT_FAILURE);
	}
	// If we got a good child pid, then we can exit the parent process
	if(child_pid > 0){
		exit(EXIT_SUCCESS);
	}

	// We are the child.  Continue from here.
	
	// Change the file-mode mask so we'll have full access to any files we write:
	umask( 0 );

	// Create a new SID for the child process
	our_sid = setsid();
	if(our_sid < 0){
		printf("Unable to get our SID.\n");
		exit(EXIT_FAILURE);
	}

	// CWD to someplace safe
	/*
	if((chdir("/")) < 0){
		printf("Unable to change to root directory.\n");
		exit(EXIT_FAILURE);
	}
	 */

	// Close all of the standard descriptors:
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

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
		case SIGQUIT: signame = (char*)"SIGQUIT"; break;
		default: signame = (char*)"UNKNOWN";
	}

	if(in_sighandler){
		// We're getting called again.  Something is going wrong during
		// shutdown.  Log this to the console and exit.
		printf("%s: called recursively.  Error in signal handler and shutdown!\n", signame);
		exit(1);
	}
	in_sighandler = true; // watch for recursive calls to this method.

	printf("%s: called.  Shutting down HelixMain.\n", signame);
	exit(0);
}
