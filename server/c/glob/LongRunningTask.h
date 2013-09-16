/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef LONGRUNNINGTASK_H
#define LONGRUNNINGTASK_H

#include "LRTask.h"
using namespace Helix::Logic::util;

#include <Mutex.h>
using namespace SLib;

namespace Helix {
namespace Glob {


class LongRunningTask {

	protected:
		map<twine, LRTask*> m_tasks; 
		Mutex* m_tasks_mutex;
	
	private:
		/** Keep the constructor private so that there's only one instance of
		 * this object in memory during a run of the server.
		 */
		LongRunningTask();

	public:

		static LongRunningTask& getInstance();

		// Standard Destructor.
		~LongRunningTask();
	
		LRTask& getTask(const twine& taskGUID);
		bool hasTask(const twine& taskGUID);
	
		LRTask& addTask(const twine& taskName);
		LRTask& updateTask(const twine& taskGUID, intptr_t start, intptr_t current, intptr_t finish, const twine& msg);
		LRTask& finishTask(const twine& taskGUID, xmlDocPtr resp);

		void removeTask(const twine& taskGUID);
	
		/** Allows you to get a description of our current task list.  We
		 * create new children under the xml node given that describe each of our tasks.
		 */
		void describeTasks(xmlNodePtr node);

		/// Creates an xml child of the given node that describes a single task from our list.
		void describeTask(xmlNodePtr parent, const twine& taskGUID);
	
};

}} // End Namespace Helix::Glob

#endif // LONGRUNNINGTASK_H Defined
