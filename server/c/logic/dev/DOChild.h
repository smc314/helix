/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef DOCHILD_H
#define DOCHILD_H

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
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/DOChild.sql.xml
  */
class DOChild
{
	public:

		/// All Data Members are public
		twine VectorName;
		twine VectorType;
		twine doguid;
		twine guid;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		DOChild();

		/// Standard Copy Constructor
		DOChild(const DOChild& c);

		/// Standard Assignment Operator
		DOChild& operator=(const DOChild& c);

		/// Standard Destructor
		virtual ~DOChild();

		/// Initialize this data object to have all empty or 0 values.
		DOChild& init();

		/// Call check_size() on all of our twine members.
		DOChild& checkSize();

		/// Construct from an XML Node
		DOChild(xmlNodePtr node);

		/// Read an XML Node to set our contents
		DOChild& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<DOChild* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<DOChild* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<DOChild* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<DOChild* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/DOChild.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new data object child entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into dochildvect (guid, doguid, VectorName, VectorType)
			values ( ?, ?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, DOChild& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, DOChild& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< DOChild* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, DOChild& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into dochildvect (guid, doguid, VectorName, VectorType) 			values ( ?, ?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given data object child in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update dochildvect
			set VectorName = ?,
				VectorType = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& VectorName, twine& VectorType, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& VectorName, twine& VectorType, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& VectorName, twine& VectorType, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update dochildvect 			set VectorName = ?, 				VectorType = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a data object child by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from dochildvect
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
			return "delete from dochildvect 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes all data object children for the given data object id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from dochildvect
			where doguid = ?
		
		  * </pre>
		  */
		static void deleteByDOID(SqlDB& sqldb, twine& doguid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void deleteByDOID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine deleteByDOID_prepSQL(IOConn& ioc, twine& doguid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine deleteByDOID_getSQL() {
			return "delete from dochildvect 			where doguid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all data objects children for a given data object
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, doguid, VectorName, VectorType
			from dochildvect
			where doguid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>doguid</li>
		  *   <li>VectorName</li>
		  *   <li>VectorType</li>
		  * </ul>
		  */
		static vector<DOChild* >* selectAllForDO(SqlDB& sqldb, twine& doguid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<DOChild* >* selectAllForDO(SqlDB& sqldb, twine& stmt, bool useInputs, twine& doguid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForDO_prepSQL(IOConn& ioc, twine& doguid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForDO_getSQL() {
			return "select guid, doguid, VectorName, VectorType 			from dochildvect 			where doguid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the DOChild
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * DOChild_svect myVect = DOChild::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< DOChild* >, DOChild::deleteVector> DOChild_svect;

}}} // End Namespace stack

#endif // DOCHILD_H defined
