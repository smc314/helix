/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef HITMAP_H
#define HITMAP_H

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
namespace util {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/util/HitMap.sql.xml
  */
class HitMap
{
	public:

		/// All Data Members are public
		intptr_t AverageCycles;
		intptr_t MaxCycles;
		twine MethodName;
		intptr_t MinCycles;
		intptr_t TotalCycles;
		intptr_t TotalHits;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		HitMap();

		/// Standard Copy Constructor
		HitMap(const HitMap& c);

		/// Standard Assignment Operator
		HitMap& operator=(const HitMap& c);

		/// Standard Destructor
		virtual ~HitMap();

		/// Initialize this data object to have all empty or 0 values.
		HitMap& init();

		/// Call check_size() on all of our twine members.
		HitMap& checkSize();

		/// Construct from an XML Node
		HitMap(xmlNodePtr node);

		/// Read an XML Node to set our contents
		HitMap& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<HitMap* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<HitMap* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<HitMap* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/util/HitMap.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This is a dummy statement used to define our data object.
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- empty on purpose
		
		  * </pre>
		  */
		static void dummy(OdbcObj& odbc, HitMap& obj );

		/** This mimics the above in functionality, but allows you to pass in your own
		  * sql statement for us to execute.  You can tell us whether to use or ignore
		  * the inputs as well.
		  */
		static void dummy(OdbcObj& odbc, twine& stmt, bool useInputs, HitMap& obj );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine dummy_prepSQL(IOConn& ioc, HitMap& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine dummy_getSQL() {
			return "-- empty on purpose";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the HitMap
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * HitMap_svect myVect = HitMap::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< HitMap* >, HitMap::deleteVector> HitMap_svect;

}}} // End Namespace stack

#endif // HITMAP_H defined
