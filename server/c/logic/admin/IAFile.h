/* **************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#ifndef IAFILE_H
#define IAFILE_H

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
  * ../logic/admin/IAFile.sql.xml
  */
class IAFile
{
	public:

		/// All Data Members are public
		twine Description;
		twine FileContents;
		twine FileName;
		intptr_t FileSize;
		twine MoveDest;
		twine MoveSource;
		twine ParentFolder;
		intptr_t ReturnCode;
		twine Status;
		twine Step;
		twine TargetFolder;
		twine Title;
		twine Type;
		intptr_t isVSE;
		intptr_t isZOS;


		/// Any Child Vectors will be defined here


		/// Standard Constructor
		IAFile();

		/// Standard Copy Constructor
		IAFile(const IAFile& c);

		/// Standard Assignment Operator
		IAFile& operator=(const IAFile& c);

		/// Standard Destructor
		virtual ~IAFile();

		/// Initialize this data object to have all empty or 0 values.
		IAFile& init();

		/// Call check_size() on all of our twine members.
		IAFile& checkSize();

		/// Construct from an XML Node
		IAFile(xmlNodePtr node);

		/// Read an XML Node to set our contents
		IAFile& readXmlNode(xmlNodePtr node);

		/// Create an XML Node as a child of the given parent
		xmlNodePtr createXmlNode(xmlNodePtr parent) const;

		/// Create an XML Document from this data object
		xmlDocPtr createXmlDoc() const;

		/// Create a series of these objects by reading all children of the given parent
		static vector<IAFile* >* readXmlChildren(xmlNodePtr parent);

		/// Create a series of xml child nodes based on the input vector
		static void createXmlChildren(xmlNodePtr parent, vector<IAFile* >* vect);

		/// Handle deleting a vector and its contents.
		static void deleteVector( vector<IAFile* >* vect);

		/// Static method to retrieve the name of this object.
		static twine& Name();

		/* ******************************************************************************** */
		/* The following are a series of static methods created based on the SQL Statements */
		/* defined in the file ../logic/admin/IAFile.sql.xml */
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
		  *   <li>ParentFolder</li>
		  *   <li>FileName</li>
		  *   <li>Description</li>
		  *   <li>Step</li>
		  *   <li>Type</li>
		  *   <li>Title</li>
		  *   <li>Status</li>
		  *   <li>ReturnCode</li>
		  *   <li>MoveSource</li>
		  *   <li>MoveDest</li>
		  *   <li>FileContents</li>
		  *   <li>TargetFolder</li>
		  * </ul>
		  */
		static vector<IAFile* >* unusedSqlStmt(OdbcObj& odbc, intptr_t isZOS, intptr_t isVSE, intptr_t FileSize);

		/** This one matches the above in functionality, but allows you to pass in
		  * the sql statement and a flag to indicate whether the input parameters
		  * will be used.
		  */
		static vector<IAFile* >* unusedSqlStmt(OdbcObj& odbc, twine& stmt, bool useInputs, intptr_t isZOS, intptr_t isVSE, intptr_t FileSize);


		/** This method will do a replacement of all of the parameter markers in
		  * the sql statement with the standard parameter list that is defined.
		  * This is useful for automatically prepping a SQL statement that doesn't
		  * work with parameter markers.
		  */
		static twine unusedSqlStmt_prepSQL(IOConn& ioc, intptr_t isZOS, intptr_t isVSE, intptr_t FileSize);

		/** This method returns the sql statement that is used by the above functions.
		  */
		static twine unusedSqlStmt_getSQL() {
			return "-- Nothing here on purpose 			-- Note, the Output/Input designations below don't matter.  Output 			-- defaults to string as a type.  Inputs require you to specify the  			-- data type.  So, for those object members where we care about the 			-- data type, we use Input.  All the others are strings and so we 			-- just use Output for less typing.";
		}


};

/** This typedef makes it easy to declare smart pointer vectors of the IAFile
  * object type.  Use this to keep your code clean and easy to read. For example:
  * <pre>
  * IAFile_svect myVect = IAFile::selectSomething(odbc);
  * </pre>
  */
typedef sptr< vector< IAFile* >, IAFile::deleteVector> IAFile_svect;

}}} // End Namespace stack

#endif // IAFILE_H defined
