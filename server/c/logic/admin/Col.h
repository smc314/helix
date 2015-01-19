/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef COL_H
#define COL_H

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
  * ../logic/admin/Col.sql.xml
  */
class Col
{
	public:

		/// All Data Members are public
		twine colName;
		twine dataValue;
		intptr_t idx;
		twine typeName;
		intptr_t verifyData;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		Col();

		/// Standard Copy Constructor
		Col(const Col& c);

		/// Standard Assignment Operator
		Col& operator=(const Col& c);

		/// Standard Destructor
		virtual ~Col();

		/// Initialize this data object to have all empty or 0 values.
		Col& init();

		/// Call check_size() on all of our twine members.
		Col& checkSize();

		/// Construct from an XML Node
		Col(xmlNodePtr node);

		/// Read an XML Node to set our contents
		Col& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<Col* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<Col* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<Col* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Col.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is here to allow us to define the data object.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Empty on purpose
		
		  * </pre>
		  */
		static void unused(OdbcObj& odbc, Col& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unused(OdbcObj& odbc, twine& stmt, bool useInputs, Col& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unused_prepSQL(IOConn& ioc, Col& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unused_getSQL() {
			return "-- Empty on purpose";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the Col
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * Col_svect myVect = Col::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< Col* >, Col::deleteVector> Col_svect;

}}} // End Namespace stack

#endif // COL_H defined
