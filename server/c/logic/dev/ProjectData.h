/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef PROJECTDATA_H
#define PROJECTDATA_H

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

#include "ProjectTable.h"


namespace Helix {
namespace Logic {
namespace dev {

/** This is a generated data object class that is used for interfacing with a
  * database.  This class was generated based on the settings in the file:
  * ../logic/dev/ProjectData.sql.xml
  */
class ProjectData
{
	public:

		/// All Data Members are public
		twine ConnectionString;
		twine DataName;
		intptr_t DataType;
		twine Deployment;
		twine Description;
		twine DevTimePass;
		twine DevTimeUser;
		twine Location;
		twine ProjName;
		twine ShortName;
		twine guid;
		twine projguid;


		/// Any Child Vectors will be defined here
		ProjectTable_svect Tables;


		/// Standard Constructor
		ProjectData();

		/// Standard Copy Constructor
		ProjectData(const ProjectData& c);

		/// Standard Assignment Operator
		ProjectData& operator=(const ProjectData& c);

		/// Standard Destructor
		virtual ~ProjectData();

		/// Initialize this data object to have all empty or 0 values.
		ProjectData& init();

		/// Call check_size() on all of our twine members.
		ProjectData& checkSize();

		/// Construct from an XML Node
		ProjectData(xmlNodePtr node);

		/// Read an XML Node to set our contents
		ProjectData& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<ProjectData* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<ProjectData* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<ProjectData* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/dev/ProjectData.sql.xml */
		/* ******************************************************************************** */


		/** This is an INSERT method.  It is designed to run a single insert
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This adds a new project data entry to our database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			insert into projdata (guid, projguid, DataName, Description, DataType, 
				ConnectionString, DevTimeUser, DevTimePass)
			values ( ?, ?, ?, ?, ?,
				?, ?, ? )
		
		  * </pre>
		  */
		static void insert(SqlDB& sqldb, ProjectData& obj );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void insert(SqlDB& sqldb, twine& stmt, bool useInputs, ProjectData& obj );

		/** This version of the method allows you to pass in a vector of objects to be
		  * inserted, and we will ensure that all of them are inserted within a single commit
		  * block within Sqlite.
		  */
		static void insert(SqlDB& sqldb, vector< ProjectData* >* v);

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine insert_prepSQL(IOConn& ioc, ProjectData& obj );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine insert_getSQL() {
			return "insert into projdata (guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass) 			values ( ?, ?, ?, ?, ?, 				?, ?, ? )";
		}

		/** This is an UPDATE method.  It is designed to run a single update
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This updates the settings for a given project data entry in the database
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			update projdata
			set DataName = ?,
				Description = ?,
				DataType = ?,
				ConnectionString = ?,
				DevTimeUser = ?,
				DevTimePass = ?
			where guid = ?
		
		  * </pre>
		  */
		static void update(SqlDB& sqldb, twine& DataName, twine& Description, intptr_t DataType, twine& ConnectionString, twine& DevTimeUser, twine& DevTimePass, twine& guid );

		/** This one matches the above in functionality, but allows you to pass in the sql
		  * statement and a flag to indicate whether the input parameters will be used.
		  */
		static void update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& DataName, twine& Description, intptr_t DataType, twine& ConnectionString, twine& DevTimeUser, twine& DevTimePass, twine& guid );

		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine update_prepSQL(IOConn& ioc, twine& DataName, twine& Description, intptr_t DataType, twine& ConnectionString, twine& DevTimeUser, twine& DevTimePass, twine& guid );

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine update_getSQL() {
			return "update projdata 			set DataName = ?, 				Description = ?, 				DataType = ?, 				ConnectionString = ?, 				DevTimeUser = ?, 				DevTimePass = ? 			where guid = ?";
		}

		/** This is an DELETE method.  It is designed to run a single delete
		  * statement and return. If something goes wrong, we will throw AnException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This removes a project data entry by guid
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			delete from projdata
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
			return "delete from projdata 			where guid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects all project data entries for a given project
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, projguid, DataName, Description, DataType, 
				ConnectionString, DevTimeUser, DevTimePass
			from projdata
			where projguid = ?
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>guid</li>
		  *   <li>projguid</li>
		  *   <li>DataName</li>
		  *   <li>Description</li>
		  *   <li>DataType</li>
		  *   <li>ConnectionString</li>
		  *   <li>DevTimeUser</li>
		  *   <li>DevTimePass</li>
		  * </ul>
		  */
		static vector<ProjectData* >* selectAllForProj(SqlDB& sqldb, twine& projguid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<ProjectData* >* selectAllForProj(SqlDB& sqldb, twine& stmt, bool useInputs, twine& projguid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectAllForProj_prepSQL(IOConn& ioc, twine& projguid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectAllForProj_getSQL() {
			return "select guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass 			from projdata 			where projguid = ?";
		}

		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This selects a single project data entry by id
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			select guid, projguid, DataName, Description, DataType, 
				ConnectionString, DevTimeUser, DevTimePass
			from projdata
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
		static vector<ProjectData* >* selectByID(SqlDB& sqldb, twine& guid);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<ProjectData* >* selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, twine& guid);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine selectByID_prepSQL(IOConn& ioc, twine& guid);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine selectByID_getSQL() {
			return "select guid, projguid, DataName, Description, DataType,  				ConnectionString, DevTimeUser, DevTimePass 			from projdata 			where guid = ?";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the ProjectData
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * ProjectData_svect myVect = ProjectData::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< ProjectData* >, ProjectData::deleteVector> ProjectData_svect;

}}} // End Namespace stack

#endif // PROJECTDATA_H defined
