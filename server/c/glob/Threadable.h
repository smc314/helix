/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef THREADABLE_H
#define THREADABLE_H

#include <twine.h>
#include <Thread.h>
using namespace SLib;

namespace Helix {
namespace Glob {


class TheMain;

/**
  * This is the parent that any class that wants to be the main
  * body of execution for a thread should inherit from.  This class
  * has all of the basic methods that are required for registering
  * this object with the ThreadList in the globals, as well as 
  * providing the query interface for the thread state, and the
  * Shutdown method.
  *
  * @author Steven M. Cherry
  */
class Threadable
{
	public:
		/**
		  * The standard constructor requires a pointer to
		  * TheMain object for global information and control
		  * structures.
		  */
		Threadable();

		/**
		  * Standard copy constructor
		  */
		Threadable(const Threadable& c);

		/**
		  * Standard assignment operator
		  */
		virtual Threadable& operator=(const Threadable& c);

		/**
		  * Standard destructor
		  */
		virtual ~Threadable();

		/**
		  * This is how the caller let's us know what our thread ID
		  * is.  This is typically only called by Threadable::Start().
		  * It shouldn't be necessary to be called by anyone else.
		  */
		void ThreadID(THREAD_ID_TYPE tid);

		/**
		  * This is how others ask us about our thread ID.  We return
		  * whatever was set by the initial call to ThreadID(...);
		  */
		THREAD_ID_TYPE ThreadID(void);

		/**
		  * This method is called before execution of
		  * the main body of the thread.  Subclasses may
		  * override this if necessary.  If they do, they should
		  * still ensure that this gets executed by doing:
		  * Threadable::PreExecute() at the top of their version
		  * of this method.
		  */
		virtual void PreExecute(void);

		/**
		  * This is the main body of the thread.  This must
		  * be implemented by the subclass.
		  */
		virtual void Execute(void) = 0;

		/**
		  * This method is called after execution of
		  * the main body of the thread.  Subclasses may
		  * override this if necessary.  If they do, they should
		  * still ensure that this gets executed by doing:
		  * Threadable::PostExecute() at the top of their version
		  * of this method.
		  */
		virtual void PostExecute(void);

		/**
		  * This method will return the current state
		  * of this thread.  It will be one of the
		  * above const int values. (Init, Startup,
		  * Running, Sleeping, Finishing, Done).
		  */
		int Status(void);

		/// Defines Thread Status of Initialization
#ifdef _WIN32
		const static int Init;
#else
		const static int Init = 0;
#endif
		/// Defines Thread Status of Startup
#ifdef _WIN32
		const static int Startup;
#else
		const static int Startup = 1;
#endif
		/// Defines Thread Status of Running
#ifdef _WIN32
		const static int Running;
#else
		const static int Running = 2;
#endif
		/// Defines Thread Status of Sleeping
#ifdef _WIN32
		const static int Sleeping;
#else
		const static int Sleeping = 3;
#endif
		/// Defines Thread Status of Finishing
#ifdef _WIN32
		const static int Finishing;
#else
		const static int Finishing = 4;
#endif
		/// Defines Thread Status of Done
#ifdef _WIN32
		const static int Done;
#else
		const static int Done = 5;
#endif

		/**
		  * This method will tell the thread to stop
		  * processing and shutdown gracefully.
		  */
		void Shutdown(void);

		/**
		  * This method will tell the thread to re-read it's config
		  * info from TheMain.
		  */
		void ReReadConfig(void);
		
		/**
		  * This method returns a description of what
		  * the point of this threadable object is.
		  * i.e. what it is trying to do.
		  */
		twine& Description(void);

		/**
		  * This static method should be used as the
		  * argument to the Thread::start() routine
		  * to start a Threadable object.  The arg
		  * value is expected to be a pointer to a 
		  * Threadable object.
		  * <P>
		  * Using this method ensures that PreExecute, Execute,
		  * and PostExecute all get called correctly, even in the
		  * case of exceptions.
		  */
		static void* Start(void* arg);

	protected:

		/// Our current thread state variable.
		int m_state;

		/// Our shutdown flag
		bool m_shutdown;

		/// Our re-read config flag
		bool m_reread_config;

		/// A description of what this object does
		twine m_descr;

		/// Our thread id
		THREAD_ID_TYPE m_tid;

};

#ifdef _WIN32
const int __declspec(selectany) Threadable::Init = 0;
const int __declspec(selectany) Threadable::Startup = 1;
const int __declspec(selectany) Threadable::Running = 2;
const int __declspec(selectany) Threadable::Sleeping = 3;
const int __declspec(selectany) Threadable::Finishing = 4;
const int __declspec(selectany) Threadable::Done = 5;
#endif

}} // End Namespace Helix::Glob

#endif // THREADABLE_H Defined
