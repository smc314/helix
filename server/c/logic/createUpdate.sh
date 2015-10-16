#!/bin/bash
#############################################################################################
# This script makes it easy to create the GetAll, GetOne, Insert/Update, and Delete API
# requests that are required for every standard object that we expose to our UI.
# Pass in the object name, and we'll create the header/body files for each of these API
# requests.  You'll still have to tweak things, but as long as your queries are based
# on the standard patterns, this will get pretty close.

OBJNAME=$1

CLASSNAME=Update${OBJNAME}
HEADERFILE=Update${OBJNAME}.h
BODYFILE=Update${OBJNAME}.cpp

TMP=`pwd`
PACKAGE=${TMP##*/}

#############################################################################################
# Here's the Header File
#############################################################################################
cat >${HEADERFILE} <<EOF
/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

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

class ${CLASSNAME} : public ActionClass
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
cat >${BODYFILE} <<EOF
/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software, LLC.

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
#include "${OBJNAME}.h"

// This adds us to the global ActionClass Registry:
ActionClassRegister<${CLASSNAME}> ${CLASSNAME}::reg("${CLASSNAME}", 1, 
	"/logic/${PACKAGE}/Insert${OBJNAME}",
	"/logic/${PACKAGE}/${CLASSNAME}"
);

// Used for auto generating the API on the javascript side:
// LOGICCODEGEN API=/logic/${PACKAGE}/Insert${OBJNAME} Input=${OBJNAME}
// LOGICCODEGEN API=/logic/${PACKAGE}/${CLASSNAME} Input=${OBJNAME}

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

	// How were we called?
	bool doingInsert = false;
	if(strcmp((const char*)ioc.GetRequestRoot()->name, "Insert${OBJNAME}") == 0){
		doingInsert = true;
	}

	// Set up the response document name
	if(doingInsert){
		ioc.initializeResponseDocument("Insert${OBJNAME}");
	} else {
		ioc.initializeResponseDocument("Update${OBJNAME}");
	}

	// Pick up the input object from the request document
	${OBJNAME} local( XmlHelpers::FindChild( ioc.GetRequestRoot(), ${OBJNAME}::Name()() ) );

	// Do any type of input validation here
	//if(local.RequiredField.empty()){
	//	throw AnException(0, FL, "${OBJNAME} must have a valid RequiredField.");
	//}

	// Read from our configuration database - change this to get data from elsewhere
	SqlDB& db = TheMain::getInstance()->GetConfigDB( );

	// Example of a doing this through an odbc connection
	// OdbcObj& db = *ioc.getDBConnection();

	// Start a transaction in case we need to handle delete's of multiple records
	SqlDBTransaction trans(db); // Transaction will be rolled back when this object goes out of scope

	// Example of doing a transaction through an odbc connection
	// Transaction trans(db); // Transaction will be rolled back when this object goes out of scope

	if(doingInsert){
		${OBJNAME}::insert( db, local );
		// Insert any other records required here

		/* ******************************************************************* */
		/* NOTE: Any type of vector insert done with Sqlite3 should have the   */
		/* useTransaction parameter set to "false" because we are handling the */
		/* transaction ourselves in this method.  e.g:                         */
		/*                                                                     */
		/* ${OBJNAME}_svect vect = ...;                                        */
		/* ${OBJNAME}::insert( db, vect, false ); // don't use a transaction   */
		/*                                                                     */
		/* ******************************************************************* */

	} else {
		//${OBJNAME}::update( db, local.Field1, local.Field2, local.Field3, local.id );
		// Update any other records here

	}

	// Commit the transaction:
	trans.Commit();

	// Send the updated object back to the caller
	local.createXmlNode( ioc.getResponseRoot() );

	// Send the response back to the caller and close the connection.
	ioc.SendReturn();
	ioc.Close();
}
EOF

