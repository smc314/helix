/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Threadable.h"
#include "IOConn.h"

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
  * This class defines a MsgProcessor.  It's job is to wait
  * for messages that come to us from anywhere
  * and handle them appropriately. 
  *
  * @author Steven M. Cherry
  * @copyright 2011 Steven M. Cherry
  */
class DLLEXPORT MsgProcessor : public Threadable
{
	public:
		/**
		  * Our standard constructor.
		  * @param name This is the name of our processor.
		  * @param q This is the message queue that we drain.
		  * @param driver This is our processor driver.
		  */
		MsgProcessor();

		/**
		  * Standard copy constructor
		  */
		MsgProcessor(const MsgProcessor& c);

		/// Standard assignmet operator
		MsgProcessor& operator=(const MsgProcessor& c);

		/// Standard destructor
		virtual ~MsgProcessor();

		/**
		  * We implement the Execute method.
		  */
		virtual void Execute(void);

	private:
		/// Handles each document
		void ProcessIOConn(IOConn* ioc);

};

}} // End Namespace Helix::Glob

#endif // PROCESSOR_H Defined
