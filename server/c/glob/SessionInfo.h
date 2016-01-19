/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SESSIONINFO_H
#define SESSIONINFO_H

#include "OdbcObj.h"

#include <twine.h>
#include <Date.h>
#include <xmlinc.h>
#include <XmlHelpers.h>
#include <Mutex.h>
using namespace SLib;

#include <map>
using namespace std;

namespace Helix {
namespace Glob {

class DLLEXPORT SessionInfo {
	public:
		int userid;
		twine username;
		twine fullname;
		twine dbname;
		Date created;
		Date lastaccess;
		twine sessionGUID;

		/** This is a name/value map that allows the client to store properties
		 *  about the current user's session back here on the server.
		 */
		map<twine, twine> userProperties;

		/** This is the current database connection that this session
		 * has to the back-end server.
		 */
		OdbcObj* dbConn;

		/** This is the mutex used to protect access to the dbConn member.
		 */
		Mutex* dbConn_mutex;

		/** Properly sets the DB connection, and destroys any existing connection
		 * that this session may have already owned.
		 */
		OdbcObj* setDBConn(OdbcObj* oo);


		/** Standard constructor
		 */
		SessionInfo();

		/** Standard constructor if you have an XML document representing a saved
		 * version of this object.
		 */
		SessionInfo(xmlDocPtr doc);

		/// Standard destructor
		virtual ~SessionInfo();

		/** Creates an XML document that represents the state of this session including
		 * all userProperties associated with this session.
		 */
		xmlDocPtr createXmlDoc();

		/** Reads our state from the given XML document.
		 */
		void readFromXml(xmlDocPtr doc);

		/** This will handle saving any changes to this session information,
		 * including user-properties to the session storage.
		 */
		void Save();

	private:

		/// Copy constructor is private to prevent use
		SessionInfo(const SessionInfo& c);

		/// Assignment operator is private to prevent use
		SessionInfo& operator=(const SessionInfo& c);
		

};

}} // End Namespace Helix::Glob

#endif // SESSIONINFO_H defined
