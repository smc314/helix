/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef THREADLIST_H
#define THREADLIST_H

#include <suvector.h>

#include "Lock.h"
using namespace SLib;

#include "Threadable.h"

namespace Helix {
namespace Glob {


class DLLEXPORT TheMain;

/**
  * This class is used as a global storage for Threadable
  * objects.  This allows us at any point to produce a 
  * list of information about the threads that are running
  * in our system.
  *
  * @author Steven M. Cherry
  */
class DLLEXPORT ThreadList
{
	private:

		/** 
		  * Copy constructor is private because there
		  * should only ever be one of these in an
		  * application.
		  */
		ThreadList(const ThreadList& c) { }

		/**
		  * Assignment operator is private to prevent
		  * use and copying.
		  */
		ThreadList& operator=(const ThreadList& c) {return *this;}

	public:
		/// Standard constructor
		ThreadList();

		/// Standard destructor
		virtual ~ThreadList();

		/// This adds a threadable object to our list
		void AddThreadable(Threadable* t);

		/// This removes a threadable object from our list
		void RemoveThreadable(Threadable* t);		

		/// This describes what's in our threadable list
		twine DescribeThreads(void);

	private:
		/// Our data structure
		suvector< Threadable* > m_threads;

		/// A mutex to protect our data
		Mutex* m_mut;
};

}} // End Namespace Helix::Glob

#endif // THREADLIST_H Defined
