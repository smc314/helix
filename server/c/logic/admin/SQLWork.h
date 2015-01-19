/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef SQLWORK_H
#define SQLWORK_H

#include <vector>
using namespace std;

#include <twine.h>
#include <Date.h>
#include <xmlinc.h>
#include <sptr.h>
using namespace SLib;

#include "IOConn.h"
#include "OdbcObj.h"
#include "SqlDB.h"
using namespace Helix::Glob;



namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/admin/SQLWork.sql.xml
  */
class SQLWork
{
	public:

		/// All Data Members are public
		twine AciInMap;
		twine AciOutMap;
		twine AciService;
		twine BuildSql;
		twine Code;
		twine ConvertSql;
		twine Description;
		twine FileName;
		twine HostDB;
		twine Owner;
		twine Pfkey;
		twine Sql;
		twine Type;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		SQLWork();

		/// Standard Copy Constructor
		SQLWork(const SQLWork& c);

		/// Standard Assignment Operator
		SQLWork& operator=(const SQLWork& c);

		/// Standard Destructor
		virtual ~SQLWork();

		/// Initialize this data object to have all empty or 0 values.
		SQLWork& init();

		/// Call check_size() on all of our twine members.
		SQLWork& checkSize();

		/// Construct from an XML Node
		SQLWork(xmlNodePtr node);

		/// Read an XML Node to set our contents
		SQLWork& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<SQLWork* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<SQLWork* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<SQLWork* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/SQLWork.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is here to allow us to define the SQLTests data object.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Empty on purpose
		
		  * </pre>
		  */
		static void unused(OdbcObj& odbc, SQLWork& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unused(OdbcObj& odbc, twine& stmt, bool useInputs, SQLWork& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unused_prepSQL(IOConn& ioc, SQLWork& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unused_getSQL() {
			return "-- Empty on purpose";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the SQLWork
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * SQLWork_svect myVect = SQLWork::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< SQLWork* >, SQLWork::deleteVector> SQLWork_svect;

}}} // End Namespace stack

#endif // SQLWORK_H defined
