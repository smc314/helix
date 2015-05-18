/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef APPLICATION_H
#define APPLICATION_H

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

#include "Api.h"
#include "DObject.h"
#include "Screen.h"


namespace Helix {
namespace Logic {
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/Application.sql.xml
  */
class Application
{
	public:

		/// All Data Members are public
		twine AppName;
		twine Description;
		twine PackageName;
		twine guid;
		twine projguid;


		/// Any Child Vectors will be defined here
		Api_svect Apis;
		DObject_svect DataObjects;
		Screen_svect Screens;


		/// Standard Constructor
		Application();

		/// Standard Copy Constructor
		Application(const Application& c);

		/// Standard Assignment Operator
		Application& operator=(const Application& c);

		/// Standard Destructor
		virtual ~Application();

		/// Initialize this data object to have all empty or 0 values.
		Application& init();

		/// Call check_size() on all of our twine members.
		Application& checkSize();

		/// Construct from an XML Node
		Application(xmlNodePtr node);

		/// Read an XML Node to set our contents
		Application& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<Application* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<Application* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Application* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<Application* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/Application.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new project application entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into projapp (guid, projguid, AppName, Description, PackageName)
			values ( ?, ?, ?, ?, ?)
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, Application& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, Application& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< Application* >* v, bool useTransaction = true);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, Application& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into projapp (guid, projguid, AppName, Description, PackageName) 			values ( ?, ?, ?, ?, ?)";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given project application in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update projapp
			set AppName = ?,
				Description = ?,
				PackageName = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& AppName, twine& Description, twine& PackageName, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& AppName, twine& Description, twine& PackageName, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& AppName, twine& Description, twine& PackageName, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update projapp 			set AppName = ?, 				Description = ?, 				PackageName = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a project application by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from projapp
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
			return "delete from projapp 			where guid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all project applications for a given project
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, projguid, AppName, Description, PackageName
			from projapp
			where projguid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>projguid</li>
		  *   <li>AppName</li>
		  *   <li>Description</li>
		  *   <li>PackageName</li>
		  * </ul>
		  */
		static vector<Application* >* selectAllForProject(SqlDB& sqldb, twine& projguid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Application* >* selectAllForProject(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projguid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForProject_prepSQL(IOConn& ioc, twine& projguid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForProject_getSQL() {
			return "select guid, projguid, AppName, Description, PackageName 			from projapp 			where projguid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects a single project application by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, projguid, AppName, Description, PackageName
			from projapp
			where guid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>projguid</li>
		  *   <li>AppName</li>
		  *   <li>Description</li>
		  *   <li>PackageName</li>
		  * </ul>
		  */
		static vector<Application* >* selectByID(SqlDB& sqldb, twine& guid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Application* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, twine& guid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select guid, projguid, AppName, Description, PackageName 			from projapp 			where guid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the Application
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * Application_svect myVect = Application::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< Application* >, Application::deleteVector> Application_svect;

}}} // End Namespace stack

#endif // APPLICATION_H defined
