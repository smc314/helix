#!/bin/bash
#############################################################################################
# This script makes it easy to start a new api skeleton.  We'll create the header and body
# files with everything required.  Just pass us the new Class name.

CLASSNAME=$1
HEADER=${CLASSNAME}.h
BODY=${CLASSNAME}.cpp
TMP=`pwd`
PACKAGE=${TMP##*/}

#############################################################################################
# Here's the Header File
#############################################################################################
cat >${HEADER} <<EOF
/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef ${CLASSNAME}_H
#define ${CLASSNAME}_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace ${PACKAGE} {

class DLLEXPORT ${CLASSNAME} : public ActionClass
{
	public:
		/// Standard Constructor
		${CLASSNAME}(xmlNodePtr action);

		/// Standard Copy Constructor
		${CLASSNAME}(const ${CLASSNAME}& c);

		/// Standard Copy operator
		${CLASSNAME}& operator=(const ${CLASSNAME}& c);

		/// Standard Destructor
		virtual ~${CLASSNAME}();

		/// We implement the ExecuteRequest method
		virtual void ExecuteRequest(IOConn& ioc);

		/// Override this to return true if this is a long running server task
		virtual bool isLongRunning();

		/// Override this to return our long running task name - if we are long running
		virtual twine lrTaskName();

	private:

		// Registers us with the global factory map:
		static ActionClassRegister<${CLASSNAME}> reg;

};

}}} // End of Namespace definitions

#endif // ${CLASSNAME}_H Defined
EOF

#############################################################################################
# Here's the Body File
#############################################################################################
cat >${BODY} <<EOF
/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "${CLASSNAME}.h"
using namespace Helix::Logic::${PACKAGE};

#include "Statics.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

// Include local data objects here


// This adds us to the global ActionClass Registry:
ActionClassRegister<${CLASSNAME}> ${CLASSNAME}::reg("${CLASSNAME}", 1, "/logic/${PACKAGE}/${CLASSNAME}");

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/${PACKAGE}/${CLASSNAME} Input=NULL

${CLASSNAME}::${CLASSNAME}(xmlNodePtr action)
{
	EnEx ee(FL, "${CLASSNAME}::${CLASSNAME}(xmlNodePtr action)");
	
}

${CLASSNAME}::${CLASSNAME}(const ${CLASSNAME}& c)
{
	EnEx ee(FL, "${CLASSNAME}::${CLASSNAME}(const ${CLASSNAME}& c)");

}

${CLASSNAME}& ${CLASSNAME}::operator=(const ${CLASSNAME}& c)
{
	EnEx ee(FL, "${CLASSNAME}::operator=(const ${CLASSNAME}& c)");

	return *this;
}

${CLASSNAME}::~${CLASSNAME}()
{
	EnEx ee(FL, "${CLASSNAME}::~${CLASSNAME}()");

}

bool ${CLASSNAME}::isLongRunning()
{
	EnEx ee(FL, "${CLASSNAME}::isLongRunning()");

	// If we are a long running transaction, we need to return true here.  This will trigger
	// special logic that causes an immediate return to the caller, and for us to be executed
	// via the internal server queue - rather than executed in-line on the http thread.

	// Most of the time our server logic classes are _NOT_ long running.  But in the rare
	// case when they are, simply return true here.
	// return true;

	// This is the default.  And in fact, if this method returns false, it's better to just
	// delete this whole method to save confusion.  Our super-class already returns false for us.
	return false;
}

twine ${CLASSNAME}::lrTaskName()
{
	EnEx ee(FL, "${CLASSNAME}::lrTaskName()");

	// Read above comments in isLongRunning.  Delete this method if not required.
	return "${CLASSNAME} Request";
}


void ${CLASSNAME}::ExecuteRequest(IOConn& ioc)
{
	// The "true" parameter at the end here indicates to the entry/exit timing
	// mechanism that it should copy this thread's stats to the global collection.
	// This should not be done everywhere, but is appropriate to do at this point.
	EnEx ee(FL, "${CLASSNAME}::ExecuteRequest(IOConn& ioc)", true);

	// Set up the response document name
	ioc.initializeResponseDocument("${CLASSNAME}");

	// Example of reading input and using it to select from the odbc driver:
	// OdbcTable local( XmlHelpers::FindChild( ioc.GetRequestRoot(), OdbcTable::Name()() ) );
	//
	// OdbcObj& odbc = *ioc.getDBConnection();
	//
	// twine stmt = OdbcTable::selectConfig_prepSQL(ioc, local.Name1);
	// OdbcTable_svect vect = OdbcTable::selectConfig(odbc, stmt, false, local.Name1);

	// Example of a simple select to return an unfiltered list of data:
	// OdbcObj& odbc = *ioc.getDBConnection();
	// 
	// OdbcTable_svect vect = OdbcTable::selectMdiCfgLst(odbc);

	// Example of accessing a local configuration database
	// SqlDB& sqldb = TheMain::getInstance()->GetSqlDB( "helixdev" );
	//
	// LocalProject_svect vect = LocalProject::selectAll( sqldb );

	// Returning data in one of the above vectors back to the client is as
	// easy as doing this:
	// 
	// OdbcObj::createXmlChildren( ioc.getResponseRoot(), vect );
	// or
	// LocalProject::createXmlChildren( ioc.getResponseRoot(), vect );

	///////////////////////////////////////////////////////////////////
	// LONG RUNNING TASK Notes
	///////////////////////////////////////////////////////////////////
	// If we are a long running transaction, our execution looks very similar to the above.
	// With a few exceptions.  Once you figure out what the start and finish markers look like,
	// then make this call:
	// ioc.updateLRTask( start, start, finish, "Starting ${CLASSNAME} Process" );
	//
	// As you progress through this long task, keep making calls like this:
	// ioc.updateLRTask( start, current, finish, "Doing something interesting" );
	//
	// When you are done, don't do anything special.  Just make the ioc.SendReturn(); call
	// as below.  Note, you'll still send return data using the ioc.getResponseRoot() as above.
	///////////////////////////////////////////////////////////////////


	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
EOF
