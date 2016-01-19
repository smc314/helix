/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SessionSerializer_H
#define SessionSerializer_H

#include "Threadable.h"
#include "SessionInfo.h"

#include <vector>
#include <utility>
#include <map>
using namespace std;

#include <AnException.h>
#include <suvector.h>
using namespace SLib;

namespace Helix {
namespace Glob {


/**
  * This class defines a thread that will run and handle seralization of
  * our SessionInfo classes.  Whenever they are created or updated, the
  * SessionList class drops them off on a BlockingQueue that we then read.
  * This allows the serialization to happen outside of the main response 
  * thread and maintain a fast response without waiting for our I/O to
  * happen.
  *
  * @author Steven M. Cherry
  * @copyright 2011 Steven M. Cherry
  */
class DLLEXPORT SessionSerializer : public Threadable
{
	public:
		/**
		  * Our standard constructor.
		  * @param name This is the name of our processor.
		  * @param q This is the message queue that we drain.
		  * @param driver This is our processor driver.
		  */
		SessionSerializer();

		/**
		  * Standard copy constructor
		  */
		SessionSerializer(const SessionSerializer& c);

		/// Standard assignmet operator
		SessionSerializer& operator=(const SessionSerializer& c);

		/// Standard destructor
		virtual ~SessionSerializer();

		/**
		  * We implement the Execute method.
		  */
		virtual void Execute(void);

		/// Ensures that our directory where we store session information has been created.
		static void EnsureSessionDir();

	private:

		/// Handles each SessionInfo we pull off the queue. 
		void ProcessSessionInfo(SessionInfo* si);


};

}} // End Namespace Helix::Glob

#endif // SessionSerializer_H Defined
