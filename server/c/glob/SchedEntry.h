/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SCHEDENTRY_H
#define SCHEDENTRY_H

#include <time.h>

#include <vector>
using namespace std;

#include <twine.h>
#include <xmlinc.h>
using namespace SLib;

#include "TheMain.h"

namespace Helix {
namespace Glob {


/**
  * This class defines our schedule entry object.  It contains 
  * a description of one schedule entry and functions to tell if
  * a given time smapshot matches the scheduled time for this entry to
  * run.  This also contains a function that will send the
  * scheduled message to a processor and return.
  *
  * @author Steven M. Cherry
  */
class SchedEntry {

	public:

		/**
		  * Schedule entries are read from the schedule
		  * portion of the configuration file.  As such,
		  * the standard way to create a schedule entry object
		  * is with an xml node pointer.
		  */
		SchedEntry(xmlNodePtr node);

		/**
		  * The destructor cleans up all of the data held
		  * by this class.
		  */
		virtual ~SchedEntry();

		/**
		  * This method checks to see if the given time value
		  * matches the time for this schedule entry to run.
		  */
		bool MatchesTime(time_t t);

		/**
		  * This method allows the caller to launch the scheduled
		  * message represented by this object.  The intent of
		  * this method is to be called upon a true return from
		  * a call to MatchesTime.  However, it is provided
		  * as a seperate independant function so that the
		  * scheduling engine may make appropriate decisions
		  * in alternative cases.
		  */
		void LaunchProcess(void);

	private:

		/// Grabs the second values.
		void ParseSecond(char *d);
	
		/// Grabs the minute values.
		void ParseMinute(char *d);
	
		/// Grabs the hour values.
		void ParseHour(char *d);
	
		/// Grabs the day of week values.
		void ParseDayw(char *d);
	
		/// Grabs the day of month values.
		void ParseDaym(char *d);
	
		/// Grabs the month values.
		void ParseMonth(char *d);
	
		/// Grabs the year values.
		void ParseYear(char *d);
	
		/// general parser for a string of values.
		void ParseValues(char *d, vector < int > &);

		/// Reads the sub node to our node
		void ReadMsg(xmlNodePtr schedule_entry_node);

		bool           m_isactive;
		twine         m_sec_value;
		vector < int > m_sec_list;		
		twine         m_min_value;
		vector < int > m_min_list;		
		twine         m_hour_value;
		vector < int > m_hour_list;		
		twine         m_dayw_value;
		vector < int > m_dayw_list;		
		twine         m_daym_value;
		vector < int > m_daym_list;		
		twine         m_mon_value;
		vector < int > m_mon_list;		
		twine         m_year_value;
		vector < int > m_year_list;		

		// This is the message that we read from the config file:
		xmlDocPtr m_msg;
};

}} // End Namespace Helix::Glob

#endif // SCHEDENTRY_H Defined
