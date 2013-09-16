/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "LongRunningTask.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <Log.h>
#include <AnException.h>
#include <Lock.h>
#include <File.h>
#include <XmlHelpers.h>
using namespace SLib;


static LongRunningTask* m_tasklist = NULL;

LongRunningTask& LongRunningTask::getInstance()
{
	EnEx ee(FL, "LongRunningTask::getInstance()");

	if(m_tasklist == NULL){
		m_tasklist = new LongRunningTask();
	}
	return *m_tasklist;
}


LongRunningTask::LongRunningTask()
{
	EnEx ee(FL, "LongRunningTask::LongRunningTask()");

	m_tasks_mutex = new Mutex();
}

LongRunningTask::~LongRunningTask()
{
	EnEx ee(FL, "LongRunningTask::~LongRunningTask()");

	delete m_tasks_mutex;
}

LRTask& LongRunningTask::getTask(const twine& taskGUID)
{
	EnEx ee(FL, "LongRunningTask::getSession()");
	if(taskGUID.length() == 0){
		throw AnException(0, FL, "Invalid taskGUID");
	}
	Lock theLock(m_tasks_mutex);
	if(m_tasks.count(taskGUID) > 0 ){
		LRTask *si = m_tasks[taskGUID];
		return *si;
	} else {
		throw AnException(0, FL, "taskGUID not found");
	}
}

bool LongRunningTask::hasTask(const twine& taskGUID)
{
	EnEx ee(FL, "LongRunningTask::hasTask()");
	if(taskGUID.length() == 0){
		throw AnException(0, FL, "Invalid taskGUID");
	}
	Lock theLock(m_tasks_mutex);
	if(m_tasks.count(taskGUID) > 0 ){
		return true;
	} else {
		return false;
	}
}

LRTask& LongRunningTask::addTask(const twine& taskName)
{
	EnEx ee(FL, "LongRunningTask::addTask()");
	Lock theLock(m_tasks_mutex);

	LRTask* si = new LRTask();
	si->TaskID = IOConn::genSessionID();
	si->TaskName = taskName;
	
	m_tasks[si->TaskID] = si;

	return *si;
}

LRTask& LongRunningTask::updateTask(const twine& taskGUID, intptr_t start, intptr_t current, 
	intptr_t finish, const twine& msg)
{
	EnEx ee(FL, "LongRunningTask::updateTask()");
	Lock theLock(m_tasks_mutex);

	if(m_tasks.count(taskGUID) > 0 ){
		LRTask *si = m_tasks[taskGUID];
		si->TaskStart = start;
		si->TaskCurrent = current;
		si->TaskFinish = finish;
		si->TaskMsg = msg;
		si->TaskMsg = msg;
		return *si;
	} else {
		throw AnException(0, FL, "taskGUID not found");
	}
}

LRTask& LongRunningTask::finishTask(const twine& taskGUID, xmlDocPtr resp)
{
	EnEx ee(FL, "LongRunningTask::finishTask()");
	Lock theLock(m_tasks_mutex);

	if(m_tasks.count(taskGUID) > 0 ){
		LRTask *si = m_tasks[taskGUID];
		si->TaskResponse = XmlHelpers::docToString( resp );
		si->TaskCurrent = si->TaskFinish;
		return *si;
	} else {
		throw AnException(0, FL, "taskGUID not found");
	}

}

void LongRunningTask::removeTask(const twine& taskGUID)
{
	EnEx ee(FL, "LongRunningTask::removeTask()");
	Lock theLock(m_tasks_mutex);
	
	if(m_tasks.count(taskGUID) > 0){
		try {
			delete m_tasks[taskGUID];
			m_tasks.erase(taskGUID);
		} catch (AnException& e){
			ERRORL(FL, "Error removing task: %s", e.Msg());
		}
	}
}

void LongRunningTask::describeTasks(xmlNodePtr node)
{
	EnEx ee(FL, "LongRunningTask::describeTasks()");
	Lock theLock(m_tasks_mutex);

	map<twine, LRTask*>::iterator it;
	for(it = m_tasks.begin(); it != m_tasks.end(); it++){
		it->second->createXmlNode( node );
	}
}

void LongRunningTask::describeTask(xmlNodePtr parent, const twine& taskGUID)
{
	EnEx ee(FL, "LongRunningTask::describeTasks()");
	Lock theLock(m_tasks_mutex);

	if(m_tasks.count(taskGUID) > 0 ){
		LRTask *si = m_tasks[taskGUID];
		si->createXmlNode( parent );
	} else {
		throw AnException(0, FL, "taskGUID not found");
	}
}

