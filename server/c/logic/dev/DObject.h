/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef DOBJECT_H
#define DOBJECT_H

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

#include "DOChild.h"
#include "DOStmt.h"


namespace Helix {
namespace Logic {
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/DObject.sql.xml
  */
class DObject
{
	public:

		/// All Data Members are public
		twine DataObjectName;
		twine guid;
		twine projappguid;


		/// Any Child Vectors will be defined here
		DOChild_svect DOChildren;
		DOStmt_svect DOStmts;


		/// Standard Constructor
		DObject();

		/// Standard Copy Constructor
		DObject(const DObject& c);

		/// Standard Assignment Operator
		DObject& operator=(const DObject& c);

		/// Standard Destructor
		virtual ~DObject();

		/// Initialize this data object to have all empty or 0 values.
		DObject& init();

		/// Call check_size() on all of our twine members.
		DObject& checkSize();

		/// Construct from an XML Node
		DObject(xmlNodePtr node);

		/// Read an XML Node to set our contents
		DObject& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<DObject* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<DObject* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<DObject* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/DObject.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new data object entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into dataobject (guid, projappguid, DataObjectName)
			values ( ?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, DObject& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, DObject& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< DObject* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, DObject& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into dataobject (guid, projappguid, DataObjectName) 			values ( ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given data object in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update dataobject
			set DataObjectName = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& DataObjectName, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& DataObjectName, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& DataObjectName, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update dataobject 			set DataObjectName = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a data object by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from dataobject
			where guid = ?
		
		  * </pre>
		  */
		static void deleteByID(SqlDB& sqldb, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteByID_prepSQL(IOConn& ioc, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteByID_getSQL() {
			return "delete from dataobject 			where guid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all data objects for a given application
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, projappguid, DataObjectName
			from dataobject
			where projappguid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>projappguid</li>
		  *   <li>DataObjectName</li>
		  * </ul>
		  */
		static vector<DObject* >* selectAllForApp(SqlDB& sqldb, twine& projappguid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<DObject* >* selectAllForApp(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projappguid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForApp_prepSQL(IOConn& ioc, twine& projappguid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForApp_getSQL() {
			return "select guid, projappguid, DataObjectName 			from dataobject 			where projappguid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the DObject
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * DObject_svect myVect = DObject::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< DObject* >, DObject::deleteVector> DObject_svect;

}}} // End Namespace stack

#endif // DOBJECT_H defined
