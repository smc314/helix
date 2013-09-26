/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef PROJECTTABLE_H
#define PROJECTTABLE_H

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

#include "TableCol.h"


namespace Helix {
namespace Logic {
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/ProjectTable.sql.xml
  */
class ProjectTable
{
	public:

		/// All Data Members are public
		twine DataName;
		twine Description;
		twine TableName;
		twine guid;
		twine projdataguid;
		twine projguid;


		/// Any Child Vectors will be defined here
		TableCol_svect Columns;


		/// Standard Constructor
		ProjectTable();

		/// Standard Copy Constructor
		ProjectTable(const ProjectTable& c);

		/// Standard Assignment Operator
		ProjectTable& operator=(const ProjectTable& c);

		/// Standard Destructor
		virtual ~ProjectTable();

		/// Initialize this data object to have all empty or 0 values.
		ProjectTable& init();

		/// Call check_size() on all of our twine members.
		ProjectTable& checkSize();

		/// Construct from an XML Node
		ProjectTable(xmlNodePtr node);

		/// Read an XML Node to set our contents
		ProjectTable& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<ProjectTable* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<ProjectTable* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<ProjectTable* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/ProjectTable.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new project table entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into projtable (guid, projdataguid, TableName, Description)
			values ( ?, ?, ?, ?)
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, ProjectTable& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, ProjectTable& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< ProjectTable* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, ProjectTable& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into projtable (guid, projdataguid, TableName, Description) 			values ( ?, ?, ?, ?)";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given project table in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update projtable
			set TableName = ?,
				Description = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& TableName, twine& Description, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& TableName, twine& Description, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& TableName, twine& Description, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update projtable 			set TableName = ?, 				Description = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a project table by guid
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from projtable
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
			return "delete from projtable 			where guid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all project tables in the database for a given project
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select projtable.guid, project.guid, projdata.guid, projdata.DataName, TableName, projtable.Description
			from project, projdata, projtable
			where project.guid = projdata.projguid
			and   projdata.guid = projtabl.projdataguid
			order by projdata.DataName, TableName
			where project.guid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>projguid</li>
		  *   <li>projdataguid</li>
		  *   <li>DataName</li>
		  *   <li>TableName</li>
		  *   <li>Description</li>
		  * </ul>
		  */
		static vector<ProjectTable* >* selectAllForProject(SqlDB& sqldb, twine& projguid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<ProjectTable* >* selectAllForProject(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projguid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForProject_prepSQL(IOConn& ioc, twine& projguid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForProject_getSQL() {
			return "select projtable.guid, project.guid, projdata.guid, projdata.DataName, TableName, projtable.Description 			from project, projdata, projtable 			where project.guid = projdata.projguid 			and   projdata.guid = projtabl.projdataguid 			order by projdata.DataName, TableName 			where project.guid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the ProjectTable
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * ProjectTable_svect myVect = ProjectTable::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< ProjectTable* >, ProjectTable::deleteVector> ProjectTable_svect;

}}} // End Namespace stack

#endif // PROJECTTABLE_H defined
