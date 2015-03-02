/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef IAFOLDER_H
#define IAFOLDER_H

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
  * ../logic/admin/IAFolder.sql.xml
  */
class IAFolder
{
	public:

		/// All Data Members are public
		twine Description;
		twine FolderName;
		twine ParentFolder;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		IAFolder();

		/// Standard Copy Constructor
		IAFolder(const IAFolder& c);

		/// Standard Assignment Operator
		IAFolder& operator=(const IAFolder& c);

		/// Standard Destructor
		virtual ~IAFolder();

		/// Initialize this data object to have all empty or 0 values.
		IAFolder& init();

		/// Call check_size() on all of our twine members.
		IAFolder& checkSize();

		/// Construct from an XML Node
		IAFolder(xmlNodePtr node);

		/// Read an XML Node to set our contents
		IAFolder& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<IAFolder* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<IAFolder* >* vect);

		/// Create a child and series of grandchild nodes based on the input vector.
		static xmlNodePtr createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<IAFolder* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<IAFolder* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/IAFolder.sql.xml */
		/* ******************************************************************************** */


		/** This is a SELECTTODO method.  It is designed to run a single select
		  * statement and create a vector of data objects that represent the result set.
		  * This method returns the resulting vector of data objects.  If something
		  * goes wrong, we will throw a SQLException.
		  * <P>
		  * Developer Comments:
		  * <P>
			This statement is merely here to define the data structure that is
			passed back and forth to define an installation plan
		
		  * <P>
		  * Sql Statement:
		  * <pre>
			-- Nothing here on purpose
			-- Note, the Output/Input designations below don't matter.  Output
			-- defaults to string as a type.  Inputs require you to specify the 
			-- data type.  So, for those object members where we care about the
			-- data type, we use Input.  All the others are strings and so we
			-- just use Output for less typing.
		
		  * </pre>
		  * <P>
		  * DataObject Attributes Used: <br/>
		  * <ul>
		  *   <li>FolderName</li>
		  *   <li>Description</li>
		  * </ul>
		  */
		static vector<IAFolder* >* unusedSqlStmt(OdbcObj& odbc, twine& ParentFolder);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<IAFolder* >* unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, twine& ParentFolder);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unusedSqlStmt_prepSQL(IOConn& ioc, twine& ParentFolder);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unusedSqlStmt_getSQL() {
			return "-- Nothing here on purpose 			-- Note, the Output/Input designations below don't matter.  Output 			-- defaults to string as a type.  Inputs require you to specify the  			-- data type.  So, for those object members where we care about the 			-- data type, we use Input.  All the others are strings and so we 			-- just use Output for less typing.";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the IAFolder
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * IAFolder_svect myVect = IAFolder::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< IAFolder* >, IAFolder::deleteVector> IAFolder_svect;

}}} // End Namespace stack

#endif // IAFOLDER_H defined
