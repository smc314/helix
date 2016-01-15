#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <xmlinc.h>
#include <Date.h>
#include <Mutex.h>
using namespace SLib;

#include <vector>
using namespace std;

#include "Threadable.h"

#include "SchedItem.h"
using namespace Helix::Logic::admin;

namespace Helix {
namespace Glob {


/**
  * This is our main schedule class. It is responsible for running
  * everything on time and keeping things moving.  The schedule is
  * written in the config file and maintained there.  This simply
  * executes the instructions in the config file.
  *
  * @author Steven M. Cherry
  */
class Schedule : public Threadable {

	public:

		static Schedule& getInstance();

		/// Standard Destructor
		virtual ~Schedule();

		/// We implement the Execute method
		void Execute(void);

		/**
		  * Loads the schedule from the config file.
		  */
		void LoadSchedule(void);

	private:

		/**
		  * Our standard constructor is private to prevent use.
		  */ 
		Schedule();

		/// Standard copy constructor
		Schedule(const Schedule& c) {}

		/// Standard assignment operator
		Schedule& operator=(const Schedule& c) { return *this; }

		/// Check to see if the scheduled item should be run now
		bool MatchesTime(const SchedItem& si, Date& now);

		/// launch the scheduled item
		void LaunchProcess(SchedItem& si);

		/// holds the list of things to run on a scheduled basis:
		SchedItem_svect m_scheds;

		/// Protects changs to the m_scheds vector
		Mutex* m_mutex;


};

}} // End Namespace Helix::Glob

#endif // SCHEDULE_H Defined.
