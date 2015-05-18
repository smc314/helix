/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ACTIONMAP_H
#define ACTIONMAP_H

#include <map>
#include <vector>
using namespace std;

#include <twine.h>
#include <Mutex.h>
using namespace SLib;

namespace Helix {
namespace Glob {


class ActionClass;
class ActionHtml;

class ActionMap {
	
	public:
		static ActionMap& getInstance(void);
	
		/** Add an action to our map by passing in the XML Element that contains the action
		 *  definition.  We will update our records with the appropriate details.
		 */
		void addAction(xmlNodePtr action);
	
		/** Add an action to our map by passing in the name and handler information directly.
		 *  We will update our records with the appropriate details.
		 */
		void addLogicAction(twine name, twine handler);
	
		/** Add an action to our map by passing in the name and handler information directly.
		 *  We will update our records with the appropriate details.
		 */
		void addHtmlAction(twine name, twine handler);
	
		/** Allows the caller to clear out our action maps for re-loading
		 * 
		 */
		void clearMap(void);

		/** Finds the appropriate action, based on the action name.  We search for Logic
		 * actions first, and then HTML actions.  If nothing appropriate is found, we
		 * return null.
		 * 
		 */
		ActionClass* findAction(twine name);

		/** Returns a list of all of the class names that we know about.
		  * 
		  */
		vector<pair<twine, twine> > listHandlers();

		virtual ~ActionMap();

		/** Ensures that all of our action logic and html mappings have been saved
		  * to the database so that permissions can be set on them.
		  */
		void SaveToConfigDB(void);

	protected:
		/// Maps action name to class name that will handle it.
		map<twine, twine> m_logics;

		/** A list of action html's each processing their own
		  * url area.
		  */
		vector<ActionHtml*> m_html;

		Mutex* m_mut;
	
	private:
		/** Keep the constructor private so that there's only one instance of
		 * this object in memory during a run of the server.
		 */
		ActionMap();
		ActionMap(const ActionMap& c);
		ActionMap& operator=(const ActionMap& c);

	
	
};

}} // End Namespace Helix::Glob

#endif // ACTIONMAP_H defined
