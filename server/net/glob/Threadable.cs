/* ***************************************************************************

   Copyright (c): 2014 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;

namespace Helix.Glob
{
	public abstract class Threadable
	{
		public const int Init = 0;
		public const int Startup = 1;
		public const int Running = 2;
		public const int Sleeping = 3;
		public const int Finishing = 4;
		public const int Done = 5;

		public Threadable ()
		{
			m_state = Threadable.Init;
			m_shutdown = false;
			m_reread_config = false;

			// This should be re-set by each child class
			m_descr = "Generic Threadable";
		}

		/**
		  * This is how the caller let's us know what our thread ID
		  * is.  This is typically only called by Threadable::Start().
		  * It shouldn't be necessary to be called by anyone else.
		  */
		public void ThreadID(int tid)
		{
			m_tid = tid;
		}

		/**
		  * This is how others ask us about our thread ID.  We return
		  * whatever was set by the initial call to ThreadID(...);
		  */
		public int ThreadID()
		{
			return m_tid;
		}

		/**
		  * This method is called before execution of
		  * the main body of the thread.  Subclasses may
		  * override this if necessary.  If they do, they should
		  * still ensure that this gets executed by doing:
		  * Threadable::PreExecute() at the top of their version
		  * of this method.
		  */
		public virtual void PreExecute()
		{
			using(EnEx ee = new EnEx("Threadable::PreExecute()")){
				// Set our state
				m_state = Threadable::Startup;

				// Add ourselves to the global thread list
				TheMain.getInstance().GetThreadList().AddThreadable(this);	
			}
		}

		/**
		  * This is the main body of the thread.  This must
		  * be implemented by the subclass.
		  */
		public abstract void Execute();

		/**
		  * This method is called after execution of
		  * the main body of the thread.  Subclasses may
		  * override this if necessary.  If they do, they should
		  * still ensure that this gets executed by doing:
		  * Threadable::PostExecute() at the top of their version
		  * of this method.
		  */
		public virtual void PostExecute()
		{
			using(EnEx ee = new EnEx("Threadable::PostExecute()")){
				// Set our state
				m_state = Threadable.Finishing;

				// Remove ourselves from the global thread list
				TheMain.getInstance().GetThreadList().RemoveThreadable(this);
			}
		}

		/**
		  * This method will return the current state
		  * of this thread.  It will be one of the
		  * above const int values. (Init, Startup,
		  * Running, Sleeping, Finishing, Done).
		  */
		public int Status()
		{
			return m_state;
		}

		/**
		  * This method will tell the thread to stop
		  * processing and shutdown gracefully.
		  */
		public void Shutdown()
		{
			using(EnEx ee = new EnEx("Threadable::Shutdown()")){
				m_shutdown = true;
			}
		}

		/**
		  * This method will tell the thread to re-read it's config
		  * info from TheMain.
		  */
		public void ReReadConfig()
		{
			using(EnEx ee = new EnEx("Threadable::ReReadConfig()")){

			}
		}

		/**
		  * This method returns a description of what
		  * the point of this threadable object is.
		  * i.e. what it is trying to do.
		  */
		public string Description()
		{
			return m_descr;
		}

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
		public static void Start(object arg)
		{
			using(EnEx ee = new EnEx("Threadable::Start()")){
				// Cast the argument
				Threadable t = (Threadable)arg;

				// Set our thread id in the threadable object:
				t.ThreadID(System.Threading.Thread.CurrentThread.ManagedThreadId);

				// If PreExecute fails, then don't do anything else.
				// If PreExecute goes well, then guarantee to call
				// PostExecute, even if an exception happens in Execute().

				try {
					t.PreExecute();
				} catch (Exception e){
					Log.Error("Exception during PreExecute: {0}", e.Message);
					return;
				}

				try {
					t.Execute();
				} catch (Exception e) {
					Log.Error("Exception during Execute: {0}", e.Message);
				}

				try {
					t.PostExecute();
				} catch (Exception e){
					Log.Error("Exception during PostExecute: {0}", e.Message);
				}

				return;
			}
		}

		/// Our current thread state variable.
		protected volatile int m_state;

		/// Our shutdown flag
		protected volatile bool m_shutdown;

		/// Our re-read config flag
		protected volatile bool m_reread_config;

		/// A description of what this object does
		protected string m_descr;

		/// Our thread id
		protected int m_tid;

	}
}

