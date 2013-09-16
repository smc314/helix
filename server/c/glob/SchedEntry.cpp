/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "SchedEntry.h"
using namespace Helix::Glob;

#include <AnException.h>
#include <Log.h>
#include <Tools.h>
#include <AutoXMLChar.h>
using namespace SLib;

SchedEntry::SchedEntry(xmlNodePtr node)
{
	AutoXMLChar tmpval;
	
	TRACE(FL, "Enter SchedEntry::SchedEntry()");

	if(strcmp((const char *)node->name, "ScheduleEntry") != 0){
		throw AnException(0, FL, "XML Node is not a Schedule Entry "
			"Node.  It is (%s)", (const char *)node->name);
	}

	tmpval = xmlGetProp(node, (const xmlChar *)"Active");
	if(tmpval() == NULL){
		throw AnException(0, FL, "Active attribute missing");
	}
	if(strncmp(tmpval, "Y", 1) == 0){
		m_isactive = true;
	} else {
		m_isactive = false;
	}

	tmpval = xmlGetProp(node, (const xmlChar *)"Second");
	if(tmpval() == NULL){
		throw AnException(0, FL, "Second attribute missing");
	}
	ParseSecond(tmpval);
		
	tmpval = xmlGetProp(node, (const xmlChar *)"Minute");
	if(tmpval() == NULL){
		throw AnException(0, FL, "Minute attribute missing");
	}
	ParseMinute(tmpval);
		
	tmpval = xmlGetProp(node, (const xmlChar *)"Hour");
	if(tmpval() == NULL){
		throw AnException(0, FL, "Hour attribute missing");
	}
	ParseHour(tmpval);
		
	tmpval = xmlGetProp(node, (const xmlChar *)"DayOfWeek");
	if(tmpval() == NULL){
		throw AnException(0, FL, "DayOfWeek attribute missing");
	}
	ParseDayw(tmpval);
		
	tmpval = xmlGetProp(node, (const xmlChar *)"DayOfMon");
	if(tmpval() == NULL){
		throw AnException(0, FL, "DayOfMon attribute missing");
	}
	ParseDaym(tmpval);
		
	tmpval = xmlGetProp(node, (const xmlChar *)"Month");
	if(tmpval() == NULL){
		throw AnException(0, FL, "Month attribute missing");
	}
	ParseMonth(tmpval);
		
	tmpval = xmlGetProp(node, (const xmlChar *)"Year");
	if(tmpval() == NULL){
		throw AnException(0, FL, "Year attribute missing");
	}
	ParseYear(tmpval);
		
	// now read our iWaveMsg child
	ReadMsg(node);


	TRACE(FL, "Exit  SchedEntry::SchedEntry()");
}	

SchedEntry::~SchedEntry()
{
	TRACE(FL, "Enter SchedEntry::~SchedEntry()");
	// doesn't have to do anything
	TRACE(FL, "Exit  SchedEntry::~SchedEntry()");
}


bool SchedEntry::MatchesTime(time_t t)
{
	struct tm *the_tm;
	int i, match;

	TRACE(FL, "Enter SchedEntry::MatchesTime()");

	if(!m_isactive){
		TRACE(FL, "Exit  SchedEntry::MatchesTime()");
		return m_isactive;
	}

	the_tm = gmtime(&t);

	if(m_sec_value != "*"){
		// check the second array:
		match = 0;
		for(i = 0; i < (int)m_sec_list.size(); i++){
			if(the_tm->tm_sec == m_sec_list[i]){
				match = 1;
				break;
			}
		}
		if(match == 0){  // didn't find a matching second 
			TRACE(FL, "Exit  SchedEntry::MatchesTime()");
			return false;
		}
	}

	if(m_min_value != "*"){
		// check the minute array:
		match = 0;
		for(i = 0; i < (int)m_min_list.size(); i++){
			if(the_tm->tm_min == m_min_list[i]){
				match = 1;
				break;
			}
		}
		if(match == 0){  // didn't find a matching minute
			TRACE(FL, "Exit  SchedEntry::MatchesTime()");
			return false;
		}
	}

	if(m_hour_value != "*"){
		// check the hour array:
		match = 0;
		for(i = 0; i < (int)m_hour_list.size(); i++){
			if(the_tm->tm_hour == m_hour_list[i]){
				match = 1;
				break;
			}
		}
		if(match == 0){  // didn't find a matching hour
			TRACE(FL, "Exit  SchedEntry::MatchesTime()");
			return false;
		}
	}

	if(m_dayw_value != "*"){
		// check the day of week array:
		match = 0;
		for(i = 0; i < (int)m_dayw_list.size(); i++){
			if(the_tm->tm_wday == m_dayw_list[i]){
				match = 1;
				break;
			}
		}
		if(match == 0){  // didn't find a matching day of week
			TRACE(FL, "Exit  SchedEntry::MatchesTime()");
			return false;
		}
	}

	if(m_daym_value != "*"){
		// check the day of month array:
		match = 0;
		for(i = 0; i < (int)m_daym_list.size(); i++){
			if(the_tm->tm_mday == m_daym_list[i]){
				match = 1;
				break;
			}
		}
		if(match == 0){  // didn't find a matching day of month
			TRACE(FL, "Exit  SchedEntry::MatchesTime()");
			return false;
		}
	}

	if(m_mon_value != "*"){
		// check the month array:
		match = 0;
		for(i = 0; i < (int)m_mon_list.size(); i++){
			if(the_tm->tm_mon == m_mon_list[i]){
				match = 1;
				break;
			}
		}
		if(match == 0){  // didn't find a matching month
			TRACE(FL, "Exit  SchedEntry::MatchesTime()");
			return false;
		}
	}

	if(m_year_value != "*"){
		// check the year array:
		match = 0;
		for(i = 0; i < (int)m_year_list.size(); i++){
			if(the_tm->tm_year == m_year_list[i]){
				match = 1;
				break;
			}
		}
		if(match == 0){  // didn't find a matching year
			TRACE(FL, "Exit  SchedEntry::MatchesTime()");
			return false;
		}
	}

	// if we passed all of the above tests, then we found a match
	// or all of the values are *'s
	TRACE(FL, "Exit  SchedEntry::MatchesTime()");
	return true;
}

void SchedEntry::LaunchProcess(void)
{
	TRACE(FL, "Enter SchedEntry::LaunchProcess()");

	// don't run this guy if he's not marked as active.
	if(!m_isactive){
		TRACE(FL, "Exit  SchedEntry::LaunchProcess()");
		return;
	}

	// FIXME: Route this properly
	// create a new copy of our message:
	//iWaveMsg* msg = new iWaveMsg(m_msg);

	// Send it to routing for delivery
	//m_main->GetRouting().SendToProcessor(msg);

	// That's it.

	TRACE(FL, "Exit  SchedEntry::LaunchProcess()");
}

void SchedEntry::ReadMsg(xmlNodePtr sched_entry)
{
	TRACE(FL, "Enter SchedEntry::ReadMsg()");

	// Find our iWaveMsg subnode:
	//xmlNodePtr msg = iWaveMsg::FindSubNode(sched_entry, "iWaveMsg");

	// copy the node into a new document:
	//xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	//doc->children = xmlCopyNode(msg, 1);

	// Put the new document into our iWaveMsg:
	//m_msg.data = doc;
	//m_msg.type = iWaveMsg::DOM;
	//m_msg.size = 0;

	// Ensure that it's routing headers are set:
	//m_msg.ReadRoutingInfo();

	TRACE(FL, "Exit  SchedEntry::ReadMsg()");
}

void SchedEntry::ParseSecond(char *d)
{
	TRACE(FL, "Enter SchedEntry::ParseSecond()");

	m_sec_value = d;
	if(m_sec_value != "*")
		ParseValues(d, m_sec_list);

	TRACE(FL, "Exit  SchedEntry::ParseSecond()");
}

void SchedEntry::ParseMinute(char *d)
{
	TRACE(FL, "Enter SchedEntry::ParseMinute()");

	m_min_value = d;
	if(m_min_value != "*")
		ParseValues(d, m_min_list);

	TRACE(FL, "Exit  SchedEntry::ParseMinute()");
}

void SchedEntry::ParseHour(char *d)
{
	TRACE(FL, "Enter SchedEntry::ParseHour()");

	m_hour_value = d;
	if(m_hour_value != "*")
		ParseValues(d, m_hour_list);

	TRACE(FL, "Exit  SchedEntry::ParseHour()");
}

void SchedEntry::ParseDayw(char *d)
{
	TRACE(FL, "Enter SchedEntry::ParseDayw()");

	m_dayw_value = d;
	if(m_dayw_value != "*")
		ParseValues(d, m_dayw_list);

	TRACE(FL, "Exit  SchedEntry::ParseDayw()");
}

void SchedEntry::ParseDaym(char *d)
{
	TRACE(FL, "Enter SchedEntry::ParseDaym()");

	m_daym_value = d;
	if(m_daym_value != "*")
		ParseValues(d, m_daym_list);

	TRACE(FL, "Exit  SchedEntry::ParseDaym()");
}

void SchedEntry::ParseMonth(char *d)
{
	TRACE(FL, "Enter SchedEntry::ParseMonth()");

	m_mon_value = d;
	if(m_mon_value != "*")
		ParseValues(d, m_mon_list);

	TRACE(FL, "Exit  SchedEntry::ParseMonth()");

}

void SchedEntry::ParseYear(char *d)
{
	TRACE(FL, "Enter SchedEntry::ParseYear()");

	m_year_value = d;
	if(m_year_value != "*")
		ParseValues(d, m_year_list);

	TRACE(FL, "Exit  SchedEntry::ParseYear()");
}

void SchedEntry::ParseValues(char *d, vector < int >& v)
{
	TRACE(FL, "Enter SchedEntry::ParseValues()");

	int len;
	char *ptr1, *ptr2;
	char tmp[32];

	len = strlen(d);
	ptr1 = d;
	ptr2 = strchr(ptr1, ',');
	while((ptr2 != NULL) && (ptr2-d < len)){
		memset(tmp, 0, 32);
		strncpy(tmp, ptr1, ptr2-ptr1);
		v.push_back(atoi(tmp));
		ptr1 = ptr2+1;
		ptr2 = strchr(ptr1, ',');
	}	
	// remember to grab the last one in the list
	v.push_back(atoi(ptr1));

	TRACE(FL, "Exit  SchedEntry::ParseValues()");
}

