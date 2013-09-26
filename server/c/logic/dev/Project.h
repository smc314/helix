/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef PROJECT_H
#define PROJECT_H

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

#include "Application.h"
#include "ProjectData.h"


namespace Helix {
namespace Logic {
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/Project.sql.xml
  */
class Project
{
	public:

		/// All Data Members are public
		twine Deployment;
		twine Description;
		twine Location;
		twine ProjName;
		twine ShortName;
		twine guid;


		/// Any Child Vectors will be defined here
		Application_svect Apps;
		ProjectData_svect Data;


		/// Standard Constructor
		Project();

		/// Standard Copy Constructor
		Project(const Project& c);

		/// Standard Assignment Operator
		Project& operator=(const Project& c);

		/// Standard Destructor
		virtual ~Project();

		/// Initialize this data object to have all empty or 0 values.
		Project& init();

		/// Call check_size() on all of our twine members.
		Project& checkSize();

		/// Construct from an XML Node
		Project(xmlNodePtr node);

		/// Read an XML Node to set our contents
		Project& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<Project* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<Project* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<Project* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/Project.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new project entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into project (guid, ProjName, ShortName, Description, Deployment, Location )
			values ( ?, ?, ?, ?, ?, ?)
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, Project& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, Project& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< Project* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, Project& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into project (guid, ProjName, ShortName, Description, Deployment, Location ) 			values ( ?, ?, ?, ?, ?, ?)";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given project in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update project
			set ProjName = ?,
				ShortName = ?,
				Description = ?,
				Deployment = ?,
				Location = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& ProjName, twine& ShortName, twine& Description, twine& Deployment, twine& Location, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& ProjName, twine& ShortName, twine& Description, twine& Deployment, twine& Location, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& ProjName, twine& ShortName, twine& Description, twine& Deployment, twine& Location, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update project 			set ProjName = ?, 				ShortName = ?, 				Description = ?, 				Deployment = ?, 				Location = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a project by guid
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from project
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
			return "delete from project 			where guid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all projects in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, ProjName, ShortName, Description, Deployment, Location
			from project
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>ProjName</li>
		  *   <li>ShortName</li>
		  *   <li>Description</li>
		  *   <li>Deployment</li>
		  *   <li>Location</li>
		  * </ul>
		  */
		static vector<Project* >* selectAll(SqlDB& sqldb);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Project* >* selectAll(SqlDB& sqldb, twine& stmt, bool useInputs);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAll_prepSQL(IOConn& ioc);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAll_getSQL() {
			return "select guid, ProjName, ShortName, Description, Deployment, Location 			from project";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects a single project by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, ProjName, ShortName, Description, Deployment, Location
			from project
			where guid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>ProjName</li>
		  *   <li>ShortName</li>
		  *   <li>Description</li>
		  *   <li>Deployment</li>
		  *   <li>Location</li>
		  * </ul>
		  */
		static vector<Project* >* selectByID(SqlDB& sqldb, twine& guid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<Project* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, twine& guid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select guid, ProjName, ShortName, Description, Deployment, Location 			from project 			where guid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the Project
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * Project_svect myVect = Project::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< Project* >, Project::deleteVector> Project_svect;

}}} // End Namespace stack

#endif // PROJECT_H defined
