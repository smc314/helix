/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "Schedule.h"
#include "TheMain.h"
#include "SchedConn.h"
using namespace Helix::Glob;

#include <AnException.h>
#include <Date.h>
#include <EnEx.h>
#include <sptr.h>
#include <Tools.h>
#include <Lock.h>
using namespace SLib;

static Schedule* our_schedule = NULL;

Schedule& Schedule::getInstance()
{
	if(our_schedule == NULL){
		our_schedule = new Schedule();
	}
	return *our_schedule;
}

Schedule::Schedule() : Threadable()
{
	EnEx ee(FL, "Schedule::Schedule()");

	m_descr = "Scheduler Thread";
	m_mutex = new Mutex();

	LoadSchedule();
}

Schedule::~Schedule()
{
	EnEx ee(FL, "Schedule::~Schedule()");
	
	delete m_mutex;
	m_mutex = NULL;
}

void Schedule::Execute(void)
{
	EnEx ee(FL, "Schedule::Start()");

	INFO(FL, "Scheduler Thread Execute starting");

	m_state = Threadable::Startup;

	while(!m_shutdown && !TheMain::getInstance()->isShutdown()){
		try {
			Date rightNow;
			if(rightNow.Sec() == 0){
				// We're at the top of a minute, check to see if there is anything to launch.
				{ // Used for scope to lock/unlock the mutex
					Lock the_lock(m_mutex);
					for(size_t i = 0; i < m_scheds->size(); i++){
						if(m_shutdown || TheMain::getInstance()->isShutdown()) break;
						if( MatchesTime( *(m_scheds->at( i )), rightNow) ){
							LaunchProcess( *(m_scheds->at( i )) );
						}
					}
				}
				// Sleep for a full second to get us off the top of the minute:
				Tools::ssleep( 1 );
			}
			// sleep for 1/10 second and keep looping until the top of the next minute
			Tools::msleep(100);

			// keep looping until shutdown.

		} catch (AnException e) {
			ERRORL(FL, "Exception:\n%s\nCaught in Scheduler.",
				e.Msg());
		} catch (...) {
			ERRORL(FL, "Unknown Exception caught in scheduler.");
		}
	}
	
}

void Schedule::LoadSchedule(void)
{
	EnEx ee(FL, "Schedule::LoadSchedule()");

	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixconfig" );
	Lock the_lock(m_mutex);
	m_scheds = SchedItem::selectAll( sqldb );

}

bool Schedule::MatchesTime( const SchedItem& si, Date& now )
{
	EnEx ee(FL, "Schedule::MatchesTime(const SchedItem& si, Date& now)");

	// Are we active?
	if(si.isActive == 0){
		// nope.  Bail out early.
		return false;
	}
	
	// Check to see if today matches the day of week filters.  If not, then don't bother
	// checking the other stuff
	if(now.DayW() == 0 && si.dowSunday == 0) return false; // It's sunday and we don't run on sundays.
	if(now.DayW() == 1 && si.dowMonday == 0) return false; // It's monday and we don't run on mondays.
	if(now.DayW() == 2 && si.dowTuesday == 0) return false; // It's tuesday and we don't run on tuesdays.
	if(now.DayW() == 3 && si.dowWednesday == 0) return false; // It's wednesday and we don't run on wednesdays.
	if(now.DayW() == 4 && si.dowThursday == 0) return false; // It's thursday and we don't run on thursdays.
	if(now.DayW() == 5 && si.dowFriday == 0) return false; // It's friday and we don't run on fridays.
	if(now.DayW() == 6 && si.dowSaturday == 0) return false; // It's saturday and we don't run on saturdays.

	// Are we a runEvery, or a runAtTime:
	if(si.useInterval){
		// We are a runEvery.  Check our LastRun time:
		if(si.LastRun.length() == 0){
			// We've never been run.  Time to get started.
			DEBUG(FL, "%s: Interval check: si.LastRun.length() == 0 - return true", si.TaskName());
			return true;
		}
		Date lastRunDate; lastRunDate.SetValue( si.LastRun );
		Interval diff = now.operator-(lastRunDate);
		if( diff.Sec() >= (si.runEvery * 60)){ // runEvery is measured in minutes
			DEBUG(FL, "%s: Interval check: LastRun(%s) Now(%s) RunEvery(%d) - return true", 
				si.TaskName(), si.LastRun(), now.GetValue(), si.runEvery );
			return true; // time to run.
		} else {
			DEBUG(FL, "%s: Interval check: LastRun(%s) Now(%s) RunEvery(%d) - return false",
				si.TaskName(), si.LastRun(), now.GetValue(), si.runEvery );
			return false; // not yet.
		}
	} else {
		// We are a runAtTime.  Check the time now, vs. the time we are supposed to run.
		if(si.RunAtTime.length() < 4){
			WARN(FL, "Schedule entry %s has an invalid RunAtTime setting.", si.TaskName() );
			return false;
		}

		twine hours = si.RunAtTime.substr(0, 2);
		twine mins = si.RunAtTime.substr(2);
		if(hours.get_int() == now.Hour() &&
			mins.get_int() == now.Min()
		){
			DEBUG(FL, "%s: RunAtTime check: (%s) Now (%s) - return true", 
				si.TaskName(), si.RunAtTime(), now.GetValue() );
			return true;
		} else {
			DEBUG(FL, "%s: RunAtTime check: (%s) Now (%s) - return false",
				si.TaskName(), si.RunAtTime(), now.GetValue() );
			return false;
		}
	}
}

void Schedule::LaunchProcess( SchedItem& si )
{
	EnEx ee(FL, "Schedule::LaunchProcess(const SchedItem& si)");

	Date now;

	// Update the database to record the last-run time for this task.
	SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixconfig" );
	si.LastRun.set( now.GetValue() );
	SchedItem::updateLastRun( sqldb, si.LastRun, si.id );
	
	// Launch the task within our system
	xmlDocPtr doc;
	if(si.InputDocument.length() != 0){
		doc = xmlParseDoc( si.InputDocument );
	} else {
		doc = xmlNewDoc((const xmlChar*)"1.0");
		doc->children = xmlNewDocNode( doc, NULL, (const xmlChar*)"Empty", NULL );
	}
	dptr<SchedConn> sc = new SchedConn( si.TaskUrl, doc );
	TheMain::getInstance()->getIOQueue().push( sc.release() );

}
