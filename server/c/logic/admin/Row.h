/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef ROW_H
#define ROW_H

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

#include "Col.h"


namespace Helix {
namespace Logic {
namespace admin {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/admin/Row.sql.xml
  */
class Row
{
	public:

		/// All Data Members are public
		intptr_t idx;


		/// Any Child Vectors will be defined here
		Col_svect Cols;


		/// Standard Constructor
		Row();

		/// Standard Copy Constructor
		Row(const Row& c);

		/// Standard Assignment Operator
		Row& operator=(const Row& c);

		/// Standard Destructor
		virtual ~Row();

		/// Initialize this data object to have all empty or 0 values.
		Row& init();

		/// Call check_size() on all of our twine members.
		Row& checkSize();

		/// Construct from an XML Node
		Row(xmlNodePtr node);

		/// Read an XML Node to set our contents
		Row& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<Row* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<Row* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Row* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<Row* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/Row.sql.xml */
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
		static void unused(OdbcObj& odbc, Row& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void unused(OdbcObj& odbc, twine& stmt, bool useInputs, Row& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unused_prepSQL(IOConn& ioc, Row& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unused_getSQL() {
			return "-- Empty on purpose";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the Row
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * Row_svect myVect = Row::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< Row* >, Row::deleteVector> Row_svect;

}}} // End Namespace stack

#endif // ROW_H defined
