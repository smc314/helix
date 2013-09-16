/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef MSGPROCSCALER_H
#define MSGPROCSCALER_H

#include "Scaler.h"

namespace Helix {
namespace Glob {


/**
  * This class is the scaler driver that handles all Processor
  * threads.  All it does is handle the scaling.
  *
  * @author Steven M. Cherry
  */
class MsgProcScaler : public Scaler 
{
	public:
		/**
		  * Our standard constructor.
		  * @param m The global TheMain pointer
		  * @param name This is our own processor name
		  */
		MsgProcScaler(const twine& name);

		/**
		  * Standard copy constructor
		  */
		MsgProcScaler(const MsgProcScaler& c);

		/// Standard assignmet operator
		MsgProcScaler& operator=(const MsgProcScaler& c);

		/// Standard destructor
		virtual ~MsgProcScaler();

		/**
		  * We implement the Execute method.
		  */
		virtual void Execute(void);

		/**
		  * This allows one of our child threads to tell us
		  * to shutdown for a restart only.  This isn't quite a
		  * full stop.  All of the threads will be shutdown and
		  * destroyed, and then we will cycle once and start 'em
		  * all back up.
		  */
		void ShutdownRestart(void);

	protected:
		/// This creates Processor objects.
		virtual Threadable* CreateThreadable(void);

		/// This returns the size of m_input_queue
		virtual int GetSize(void);
		 
	private:

		/// Our name
		twine m_name;

		/// Indicates that a shutdown is only for a restart
		bool m_is_shutdown_restart;

};

}} // End Namespace Helix::Glob

#endif // MSGPROCSCALER_H Defined
