/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SCALER_H
#define SCALER_H

#include "Threadable.h"

#include <vector>
#include <utility>
using namespace std;

#include <Thread.h>
#include <Timer.h>
using namespace SLib;

namespace Helix {
namespace Glob {


/**
  * This class implements our standard scaling algorithm.  Any thread
  * that needs to do scaling of a pool of sub-threads should sub-class
  * this class, so that all of our scaling code remains in one place.
  *
  * @author Steven M. Cherry
  */
class Scaler : public Threadable
{
	public:
		/// Standard constructor
		Scaler();

		/// Standard copy constructor
		Scaler(const Scaler& c);

		/// Standard assignment operator
		virtual Scaler& operator=(const Scaler& c);

		/// Standard destructor
		virtual ~Scaler();

		/**
		  * This method implements our standard scaling algorithm.
		  * If you need to have anything done prior to this, then
		  * override this method, but be sure to call Scaler::Execute()
		  * when you are ready for us to take over.
		  */
		virtual void Execute(void);

	protected:

		///  This method adds to our pool of threads
		void StartThreads(void);

		/// This method reduces the size of our pool of threads
		void ReduceThreads(void);

		/// This method shuts down all of our threads
		void StopAllThreads(void);

		/**
		  * Override this method to create the proper type of 
		  * threadable object for your process.
		  */
		virtual Threadable* CreateThreadable(void) = 0;

		/**
		  * Override this method to return the size parameter that
		  * we test against the threshold value to see if it's time
		  * to scale up.
		  */
		virtual int GetSize(void) = 0;
		 

		/// This is where we store our pool of threads:
		vector < pair < Thread*, Threadable* > > m_thread_pool;

		// These are the config parameters that manage the pool

		/// Defines the minimum number of threads in the pool
		size_t m_min_threads;
		/// Defines the maximum number of threads in the pool
		size_t m_max_threads;
		/// Defines the amount (+/-) by which we adjust the pool
		int m_adjust_size;
		/**
		  * Defines the target size that we check for to increase
		  * the size of the thread pool.  If GetSize() > m_target_size
		  * then we will increase the size of the thread pool.
		  */
		int m_target_size;

		/**
		  * This timer tracks how long it has been since we've started
		  * some worker threads.
		  */
		Timer m_last_started;

		/// The number of seconds to wait before starting more threads
		int m_start_wait_time;

		/**
		  * This timer tracks how long it has been since we've
		  * shutdown some worker threads.
		  */
		Timer m_last_stopped;
		
		/// The number of seconds to wait before stopping more threads
		int m_stop_wait_time;


};

}} // End Namespace Helix::Glob

#endif // SCALER_H Defined
		
