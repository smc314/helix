/* **************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************** */

#include <AnException.h>
#include <EnEx.h>
#include <Log.h>
#include <XmlHelpers.h>
#include <Timer.h>
using namespace SLib;

#include "Action.h"
using namespace Helix::Logic::admin;

#include "Statics.h"
using namespace Helix::Logic::util;

/* ************************************************************************** */
/* This is a generated data object class that is used for interfacing with a  */
/* database.  This class was generated based on the settings in the file:     */
/* ../logic/admin/Action.sql.xml */
/* ************************************************************************** */

// Our Object Name, which is also used to create Xml Elements
static twine ActionName = "Action";

Action::Action()
{
	EnEx ee(FL, "Action::Action()");

	init();

}

Action::Action(const Action& c)
{
	EnEx ee(FL, "Action::Action(const Action& c)");

	Allow = c.Allow;
	OKWOSession = c.OKWOSession;
	Path = c.Path;
	groupid = c.groupid;
	id = c.id;
	userid = c.userid;


}

Action& Action::operator=(const Action& c)
{
	EnEx ee(FL, "Action::operator=(const Action& c)");

	Allow = c.Allow;
	OKWOSession = c.OKWOSession;
	Path = c.Path;
	groupid = c.groupid;
	id = c.id;
	userid = c.userid;


	return *this;
}

Action::~Action()
{
	EnEx ee(FL, "Action::~Action()");

}

Action& Action::init()
{
	EnEx ee(FL, "Action::init()");

	Allow = 0;
	OKWOSession = 0;
	Path.erase();
	groupid = 0;
	id = 0;
	userid = 0;


	return *this;
}

Action& Action::checkSize()
{
	EnEx ee(FL, "Action::checkSize()");

	Path.check_size();
	Path.rtrim();


	return *this;
}

/* ********************************************************************** */
/* Construct from an xmlNodePtr                                           */
/* ********************************************************************** */
Action::Action(xmlNodePtr node)
{
	EnEx ee(FL, "Action::Action(xmlNodePtr node)");

	// Read everything from the given xmlNodePtr
	readXmlNode(node);
}

/* ********************************************************************** */
/* Read from an xmlNodePtr                                                */
/* ********************************************************************** */
Action& Action::readXmlNode(xmlNodePtr node)
{
	EnEx ee(FL, "Action::readXmlNode(xmlNodePtr node)");

	if(node == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to construct Action is NULL.");
	}

	Allow = XmlHelpers::getIntAttr(node, "Allow");
	OKWOSession = XmlHelpers::getIntAttr(node, "OKWOSession");
	Path.getAttribute(node, "Path");
	groupid = XmlHelpers::getIntAttr(node, "groupid");
	id = XmlHelpers::getIntAttr(node, "id");
	userid = XmlHelpers::getIntAttr(node, "userid");


	return *this;
}

/* ********************************************************************** */
/* Create an xmlNodePtr child of the given parent node                    */
/* ********************************************************************** */
xmlNodePtr Action::createXmlNode(xmlNodePtr parent) const
{
	EnEx ee(FL, "Action::createXmlNode(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Action::createXmlNode is NULL.");
	}

	xmlNodePtr child = xmlNewChild(parent, NULL, (const xmlChar*)"Action", NULL);
	XmlHelpers::setIntAttr(child, "Allow", Allow);
	XmlHelpers::setIntAttr(child, "OKWOSession", OKWOSession);
	xmlSetProp(child, (const xmlChar*)"Path", Path);
	XmlHelpers::setIntAttr(child, "groupid", groupid);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "userid", userid);


	return child;
}

/* ********************************************************************** */
/* Create an xmlDocPtr from our data object                               */
/* ********************************************************************** */
xmlDocPtr Action::createXmlDoc() const
{
	EnEx ee(FL, "Action::createXmlDoc()");

	xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
	doc->children = xmlNewDocNode(doc, NULL, (const xmlChar*)"Action", NULL);
	xmlNodePtr child = xmlDocGetRootElement(doc);
	XmlHelpers::setIntAttr(child, "Allow", Allow);
	XmlHelpers::setIntAttr(child, "OKWOSession", OKWOSession);
	xmlSetProp(child, (const xmlChar*)"Path", Path);
	XmlHelpers::setIntAttr(child, "groupid", groupid);
	XmlHelpers::setIntAttr(child, "id", id);
	XmlHelpers::setIntAttr(child, "userid", userid);


	return doc;
}

/* ********************************************************************** */
/* Create a series of these objects by reading all children of the parent */
/* ********************************************************************** */
vector<Action* >* Action::readXmlChildren(xmlNodePtr parent)
{
	EnEx ee(FL, "Action::readXmlChildren(xmlNodePtr parent)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Action::readXmlChildren is NULL.");
	}

	// Use an sptr to ensure that if the method throws or causes an exception to be
	// thrown the vector will be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	for(xmlNodePtr child = parent->xmlChildrenNode; child != NULL; child = child->next){
		if(strcmp( (const char*)child->name, "Action") == 0){
			ret->push_back( new Action(child) );
		}
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	return ret.release();
}

/* ********************************************************************** */
/* Create a series of child nodes based on the input vector.              */
/* ********************************************************************** */
void Action::createXmlChildren(xmlNodePtr parent, vector<Action* >* vect)
{
	EnEx ee(FL, "Action::createXmlChildren(xmlNodePtr parent, vector<Action* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Action::createXmlChildren is NULL.");
	}

	for(size_t i = 0; i < vect->size(); i++){
		(*vect)[i]->createXmlNode(parent);
	}

}

/* ********************************************************************** */
/* Create a child node and a series of grand-child nodes from the vector. */
/* ********************************************************************** */
xmlNodePtr Action::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Action* >* vect)
{
	EnEx ee(FL, "Action::createXmlChildAndGrandchildren(xmlNodePtr parent, const twine& childName, vector<Action* >* vect)");

	if(parent == NULL){
		throw AnException(0, FL, "xmlNodePtr passed to Action::createXmlChildAndGrandchildren is NULL.");
	}

	xmlNodePtr child = xmlNewChild( parent, NULL, childName, NULL);
	Action::createXmlChildren( child, vect );

	return child;
}

/* ********************************************************************** */
/* Handle deleting a vector and its contents.                             */
/* ********************************************************************** */
void Action::deleteVector(vector<Action* >* vect)
{
	EnEx ee(FL, "Action::deleteVector(vector<Action* >* vect)");

	if(vect == NULL){
		return; // quick bail-out
	}

	for(size_t i = 0; i < vect->size(); i++){
		if( (*vect)[i] != NULL ){
			delete (*vect)[i];
		}
	}

	delete vect;

}

/* ********************************************************************** */
/* Return the name of our object.                                         */
/* ********************************************************************** */
twine& Action::Name()
{
	return ActionName;
}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add new action entries into our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into action (path, okwosession)
			values ( ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Action::insert(SqlDB& sqldb, Action& obj )
{
	EnEx ee(FL, "Action::insert()");

	twine stmt = "insert into action (path, okwosession) 			values ( ?, ? )";

	Action::insert(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Action::insert(SqlDB& sqldb, twine& stmt, bool useInputs, Action& obj )
{
	EnEx ee(FL, "Action::insert()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::insert()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, obj.Path() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, obj.Path(), (int)obj.Path.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.OKWOSession );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.OKWOSession) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::insert");
			sqldb.check_err( sqlite3_step( db_stmt ) );

			// Update the insert object to pick up the new autogen value:
			obj.id = sqlite3_last_insert_rowid( db );


		} // End the Timing scope
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This is the version that accepts an array of inputs and ensures that they are all      */
/* written to the database with a single transaction                                      */
/* ************************************************************************************** */
void Action::insert(SqlDB& sqldb, vector< Action* >* v, bool useTransaction)
{
	EnEx ee(FL, "Action::insert(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into action (path, okwosession) 			values ( ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::insert()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, v->at( v_i )->Path() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, v->at( v_i )->Path(), (int)v->at( v_i )->Path.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->OKWOSession );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->OKWOSession) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Action::insert");
				sqldb.check_err( sqlite3_step( db_stmt ) );

				// Update the insert object to pick up the new autogen value:
				v->at( v_i )->id = sqlite3_last_insert_rowid( db );


				// Reset the statement so that we can bind/execute again:
				sqlite3_reset( db_stmt );
			} // loop through all of the inputs

			// Commit our transaction here:
			if(useTransaction){
				DEBUG(FL, "Committing the vector insert transaction" );
				twine commitSql = "commit transaction;";
				sqldb.check_err( sqlite3_prepare( db, commitSql(), (int)commitSql.length(), &db_commit, NULL ) );
				sqldb.check_err( sqlite3_step( db_commit ) );
			}

		} // End the Timing scope
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.4){
			WARN(FL, "Array Insert took longer than 400ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		if(db_begin != NULL){
			sqlite3_finalize( db_begin );
		}
		if(db_commit != NULL){
			sqlite3_finalize( db_commit );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	if(db_begin != NULL){
		sqlite3_finalize( db_begin );
	}
	if(db_commit != NULL){
		sqlite3_finalize( db_commit );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::insert_prepSQL(IOConn& ioc, Action& obj )
{
	EnEx ee(FL, "Action::insert_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into action (path, okwosession) 			values ( ?, ? )";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Path parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, obj.Path );
	}

	// Replace the OKWOSession parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.OKWOSession;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add user's to an action.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into useraction (userid, actionid, allow)
			values ( ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Action::addUserToAction(SqlDB& sqldb, Action& obj )
{
	EnEx ee(FL, "Action::addUserToAction()");

	twine stmt = "insert into useraction (userid, actionid, allow) 			values ( ?, ?, ? )";

	Action::addUserToAction(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Action::addUserToAction(SqlDB& sqldb, twine& stmt, bool useInputs, Action& obj )
{
	EnEx ee(FL, "Action::addUserToAction()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::addUserToAction()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)obj.userid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.Allow );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)obj.Allow) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::addUserToAction");
			sqldb.check_err( sqlite3_step( db_stmt ) );


		} // End the Timing scope
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This is the version that accepts an array of inputs and ensures that they are all      */
/* written to the database with a single transaction                                      */
/* ************************************************************************************** */
void Action::addUserToAction(SqlDB& sqldb, vector< Action* >* v, bool useTransaction)
{
	EnEx ee(FL, "Action::addUserToAction(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into useraction (userid, actionid, allow) 			values ( ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::addUserToAction()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, v->at( v_i )->userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)v->at( v_i )->userid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, v->at( v_i )->Allow );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)v->at( v_i )->Allow) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Action::addUserToAction");
				sqldb.check_err( sqlite3_step( db_stmt ) );


				// Reset the statement so that we can bind/execute again:
				sqlite3_reset( db_stmt );
			} // loop through all of the inputs

			// Commit our transaction here:
			if(useTransaction){
				DEBUG(FL, "Committing the vector insert transaction" );
				twine commitSql = "commit transaction;";
				sqldb.check_err( sqlite3_prepare( db, commitSql(), (int)commitSql.length(), &db_commit, NULL ) );
				sqldb.check_err( sqlite3_step( db_commit ) );
			}

		} // End the Timing scope
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.4){
			WARN(FL, "Array Insert took longer than 400ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		if(db_begin != NULL){
			sqlite3_finalize( db_begin );
		}
		if(db_commit != NULL){
			sqlite3_finalize( db_commit );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	if(db_begin != NULL){
		sqlite3_finalize( db_begin );
	}
	if(db_commit != NULL){
		sqlite3_finalize( db_commit );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::addUserToAction_prepSQL(IOConn& ioc, Action& obj )
{
	EnEx ee(FL, "Action::addUserToAction_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into useraction (userid, actionid, allow) 			values ( ?, ?, ? )";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Allow parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Allow;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an INSERT method.  It is designed to run a single insert                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to add group's to an action.
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			insert into groupaction (groupid, actionid, allow)
			values ( ?, ?, ? )
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Action::addGroupToAction(SqlDB& sqldb, Action& obj )
{
	EnEx ee(FL, "Action::addGroupToAction()");

	twine stmt = "insert into groupaction (groupid, actionid, allow) 			values ( ?, ?, ? )";

	Action::addGroupToAction(sqldb, stmt, true, obj );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Action::addGroupToAction(SqlDB& sqldb, twine& stmt, bool useInputs, Action& obj )
{
	EnEx ee(FL, "Action::addGroupToAction()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::addGroupToAction()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, obj.groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)obj.groupid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, obj.id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)obj.id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, obj.Allow );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)obj.Allow) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::addGroupToAction");
			sqldb.check_err( sqlite3_step( db_stmt ) );


		} // End the Timing scope
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This is the version that accepts an array of inputs and ensures that they are all      */
/* written to the database with a single transaction                                      */
/* ************************************************************************************** */
void Action::addGroupToAction(SqlDB& sqldb, vector< Action* >* v, bool useTransaction)
{
	EnEx ee(FL, "Action::addGroupToAction(SqlDB& sqldb, vector<*>* v)");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;
	sqlite3_stmt* db_begin = NULL;
	sqlite3_stmt* db_commit = NULL;

	try {
		twine stmt = "insert into groupaction (groupid, actionid, allow) 			values ( ?, ?, ? )";
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::addGroupToAction()-BindExecStmt");

			// Begin our transaction here:
			if(useTransaction){
				DEBUG(FL, "Beginning the vector insert transaction" );
				twine beginSql = "begin transaction;";
				sqldb.check_err( sqlite3_prepare( db, beginSql(), (int)beginSql.length(), &db_begin, NULL) );
				sqldb.check_err( sqlite3_step( db_begin ) );
			}

			// Loop through the vector of inputs
			for(size_t v_i = 0; v_i < v->size(); v_i++ ){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, v->at( v_i )->groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)v->at( v_i )->groupid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, v->at( v_i )->id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)v->at( v_i )->id) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, v->at( v_i )->Allow );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)v->at( v_i )->Allow) );


				// Execute the statement
				DEBUG(FL, "Executing the statement for Action::addGroupToAction");
				sqldb.check_err( sqlite3_step( db_stmt ) );


				// Reset the statement so that we can bind/execute again:
				sqlite3_reset( db_stmt );
			} // loop through all of the inputs

			// Commit our transaction here:
			if(useTransaction){
				DEBUG(FL, "Committing the vector insert transaction" );
				twine commitSql = "commit transaction;";
				sqldb.check_err( sqlite3_prepare( db, commitSql(), (int)commitSql.length(), &db_commit, NULL ) );
				sqldb.check_err( sqlite3_step( db_commit ) );
			}

		} // End the Timing scope
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.4){
			WARN(FL, "Array Insert took longer than 400ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		if(db_begin != NULL){
			sqlite3_finalize( db_begin );
		}
		if(db_commit != NULL){
			sqlite3_finalize( db_commit );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	if(db_begin != NULL){
		sqlite3_finalize( db_begin );
	}
	if(db_commit != NULL){
		sqlite3_finalize( db_commit );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::addGroupToAction_prepSQL(IOConn& ioc, Action& obj )
{
	EnEx ee(FL, "Action::addGroupToAction_prepSQL()");

	size_t idx = 0;
	twine stmt = "insert into groupaction (groupid, actionid, allow) 			values ( ?, ?, ? )";

	// Replace the groupid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.groupid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.id;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Allow parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = obj.Allow;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an UPDATE method.  It is designed to run a single update                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to update existing action entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			update action
			set path = ?,
				okwosession = ?
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Action::update(SqlDB& sqldb, twine& Path, intptr_t OKWOSession, intptr_t id )
{
	EnEx ee(FL, "Action::update()");

	twine stmt = "update action 			set path = ?, 				okwosession = ? 			where id = ?";

	Action::update(sqldb, stmt, true, Path, OKWOSession, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Action::update(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Path, intptr_t OKWOSession, intptr_t id )
{
	EnEx ee(FL, "Action::update()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::update()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, Path() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, Path(), (int)Path.length(), SQLITE_STATIC) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, OKWOSession );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)OKWOSession) );
				DEBUG(FL, "Setting input (%d) to value: %d", 3, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 3, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::update");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::update_prepSQL(IOConn& ioc, twine& Path, intptr_t OKWOSession, intptr_t id )
{
	EnEx ee(FL, "Action::update_prepSQL()");

	size_t idx = 0;
	twine stmt = "update action 			set path = ?, 				okwosession = ? 			where id = ?";

	// Replace the Path parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Path );
	}

	// Replace the OKWOSession parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = OKWOSession;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an DELETE method.  It is designed to run a single delete                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to delete existing action entries in our database
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from action
			where id = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Action::deleteByID(SqlDB& sqldb, intptr_t id )
{
	EnEx ee(FL, "Action::deleteByID()");

	twine stmt = "delete from action 			where id = ?";

	Action::deleteByID(sqldb, stmt, true, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Action::deleteByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id )
{
	EnEx ee(FL, "Action::deleteByID()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::deleteByID()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::deleteByID");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::deleteByID_prepSQL(IOConn& ioc, intptr_t id )
{
	EnEx ee(FL, "Action::deleteByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from action 			where id = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an DELETE method.  It is designed to run a single delete                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to remove user's from an action
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from useraction
			where userid = ?
			and   actionid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Action::removeUserFromAction(SqlDB& sqldb, intptr_t userid, intptr_t id )
{
	EnEx ee(FL, "Action::removeUserFromAction()");

	twine stmt = "delete from useraction 			where userid = ? 			and   actionid = ?";

	Action::removeUserFromAction(sqldb, stmt, true, userid, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Action::removeUserFromAction(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, intptr_t id )
{
	EnEx ee(FL, "Action::removeUserFromAction()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::removeUserFromAction()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::removeUserFromAction");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::removeUserFromAction_prepSQL(IOConn& ioc, intptr_t userid, intptr_t id )
{
	EnEx ee(FL, "Action::removeUserFromAction_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from useraction 			where userid = ? 			and   actionid = ?";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is an DELETE method.  It is designed to run a single delete                       */
/* statement and return.  If something  goes wrong, we will throw AnException.            */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to remove group's from an action
		 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			delete from groupaction
			where groupid = ?
			and   actionid = ?
		 */
/*                                                                                        */
/* ************************************************************************************** */
void Action::removeGroupFromAction(SqlDB& sqldb, intptr_t groupid, intptr_t id )
{
	EnEx ee(FL, "Action::removeGroupFromAction()");

	twine stmt = "delete from groupaction 			where groupid = ? 			and   actionid = ?";

	Action::removeGroupFromAction(sqldb, stmt, true, groupid, id );

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
void Action::removeGroupFromAction(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid, intptr_t id )
{
	EnEx ee(FL, "Action::removeGroupFromAction()");

	Timer selectTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	try {
		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::removeGroupFromAction()-BindExecStmt");

			// Bind the inputs
			if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)groupid) );
				DEBUG(FL, "Setting input (%d) to value: %d", 2, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 2, (int)id) );

			} // if(useInputs)

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::removeGroupFromAction");
			sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

	} catch (AnException& e){
		// Ensure that no matter the exception we release the database back to the object
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// That's it.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return;
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::removeGroupFromAction_prepSQL(IOConn& ioc, intptr_t groupid, intptr_t id )
{
	EnEx ee(FL, "Action::removeGroupFromAction_prepSQL()");

	size_t idx = 0;
	twine stmt = "delete from groupaction 			where groupid = ? 			and   actionid = ?";

	// Replace the groupid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = groupid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}



	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up all action entries in our database
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::selectAll(SqlDB& sqldb)
{
	EnEx ee(FL, "Action::selectAll()");

	twine stmt = "select id, path, okwosession 			from action";

	return Action::selectAll(sqldb, stmt, true);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::selectAll(SqlDB& sqldb, twine& stmt, bool useInputs)
{
	EnEx ee(FL, "Action::selectAll(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::selectAll()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::selectAll");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::selectAll_prepSQL(IOConn& ioc)
{
	EnEx ee(FL, "Action::selectAll_prepSQL()");

	twine stmt = "select id, path, okwosession 			from action";

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up a single action entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action
			where id = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::selectByID(SqlDB& sqldb, intptr_t id)
{
	EnEx ee(FL, "Action::selectByID()");

	twine stmt = "select id, path, okwosession 			from action 			where id = ?";

	return Action::selectByID(sqldb, stmt, true, id);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::selectByID(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t id)
{
	EnEx ee(FL, "Action::selectByID(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, id );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)id) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::selectByID()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::selectByID");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::selectByID_prepSQL(IOConn& ioc, intptr_t id)
{
	EnEx ee(FL, "Action::selectByID_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, path, okwosession 			from action 			where id = ?";

	// Replace the id parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = id;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up a single action entry in our database.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action
			where path = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::selectByPath(SqlDB& sqldb, twine& Path)
{
	EnEx ee(FL, "Action::selectByPath()");

	twine stmt = "select id, path, okwosession 			from action 			where path = ?";

	return Action::selectByPath(sqldb, stmt, true, Path);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::selectByPath(SqlDB& sqldb, twine& stmt, bool useInputs, twine& Path)
{
	EnEx ee(FL, "Action::selectByPath(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %s", 1, Path() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 1, Path(), (int)Path.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::selectByPath()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::selectByPath");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::selectByPath_prepSQL(IOConn& ioc, twine& Path)
{
	EnEx ee(FL, "Action::selectByPath_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, path, okwosession 			from action 			where path = ?";

	// Replace the Path parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Path );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up all action entries for a given user in our database
			based on direct permissions.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action, useraction
			where useraction.userid = ?
			and   useraction.actionid = action.id
			and   useraction.allow = 1
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::selectActionsForUser(SqlDB& sqldb, intptr_t userid)
{
	EnEx ee(FL, "Action::selectActionsForUser()");

	twine stmt = "select id, path, okwosession 			from action, useraction 			where useraction.userid = ? 			and   useraction.actionid = action.id 			and   useraction.allow = 1";

	return Action::selectActionsForUser(sqldb, stmt, true, userid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::selectActionsForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid)
{
	EnEx ee(FL, "Action::selectActionsForUser(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::selectActionsForUser()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::selectActionsForUser");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::selectActionsForUser_prepSQL(IOConn& ioc, intptr_t userid)
{
	EnEx ee(FL, "Action::selectActionsForUser_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, path, okwosession 			from action, useraction 			where useraction.userid = ? 			and   useraction.actionid = action.id 			and   useraction.allow = 1";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = userid;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up all action entries for a given group in our database
			based on direct permissions.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action, groupaction
			where groupaction.groupid = ?
			and   groupaction.actionid = action.id
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::selectActionsForGroup(SqlDB& sqldb, intptr_t groupid)
{
	EnEx ee(FL, "Action::selectActionsForGroup()");

	twine stmt = "select id, path, okwosession 			from action, groupaction 			where groupaction.groupid = ? 			and   groupaction.actionid = action.id";

	return Action::selectActionsForGroup(sqldb, stmt, true, groupid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::selectActionsForGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t groupid)
{
	EnEx ee(FL, "Action::selectActionsForGroup(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, groupid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)groupid) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::selectActionsForGroup()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::selectActionsForGroup");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::selectActionsForGroup_prepSQL(IOConn& ioc, intptr_t groupid)
{
	EnEx ee(FL, "Action::selectActionsForGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, path, okwosession 			from action, groupaction 			where groupaction.groupid = ? 			and   groupaction.actionid = action.id";

	// Replace the groupid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = groupid;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to pull up all action entries for a given user in our database
			based on their group membership permissions.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action, groupaction, usergroup
			where usergroup.userid = ?
			and   usergroup.groupid = groupaction.groupid
			and   groupaction.actionid = action.id
			and   groupaction.allow = 1
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::selectActionsForUserByGroup(SqlDB& sqldb, intptr_t userid)
{
	EnEx ee(FL, "Action::selectActionsForUserByGroup()");

	twine stmt = "select id, path, okwosession 			from action, groupaction, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groupaction.groupid 			and   groupaction.actionid = action.id 			and   groupaction.allow = 1";

	return Action::selectActionsForUserByGroup(sqldb, stmt, true, userid);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::selectActionsForUserByGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid)
{
	EnEx ee(FL, "Action::selectActionsForUserByGroup(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::selectActionsForUserByGroup()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::selectActionsForUserByGroup");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::selectActionsForUserByGroup_prepSQL(IOConn& ioc, intptr_t userid)
{
	EnEx ee(FL, "Action::selectActionsForUserByGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, path, okwosession 			from action, groupaction, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groupaction.groupid 			and   groupaction.actionid = action.id 			and   groupaction.allow = 1";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = userid;
		stmt.replace(idx, 1, tmp);
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we use to check whether a given user has direct permissions
			to invoke a given action.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action, useraction
			where useraction.userid = ?
			and   useraction.actionid = action.id
			and   useraction.allow = 1
			and   action.path = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::checkActionForUser(SqlDB& sqldb, intptr_t userid, twine& Path)
{
	EnEx ee(FL, "Action::checkActionForUser()");

	twine stmt = "select id, path, okwosession 			from action, useraction 			where useraction.userid = ? 			and   useraction.actionid = action.id 			and   useraction.allow = 1 			and   action.path = ?";

	return Action::checkActionForUser(sqldb, stmt, true, userid, Path);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::checkActionForUser(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, twine& Path)
{
	EnEx ee(FL, "Action::checkActionForUser(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Path() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Path(), (int)Path.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::checkActionForUser()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::checkActionForUser");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::checkActionForUser_prepSQL(IOConn& ioc, intptr_t userid, twine& Path)
{
	EnEx ee(FL, "Action::checkActionForUser_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, path, okwosession 			from action, useraction 			where useraction.userid = ? 			and   useraction.actionid = action.id 			and   useraction.allow = 1 			and   action.path = ?";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Path parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Path );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

/* ************************************************************************************** */
/* This is a SELECTTODO method.  It is designed to run a single select                    */
/* statement and create a vector of data objects that represent the result set.           */
/* This method returns the resulting vector of data objects.  If something                */
/* goes wrong, we will throw a SQLException.                                              */
/*                                                                                        */
/* Developer Comments:                                                                    */
/* 
			This is the statement that we to check whether a given user has group permissions
			to invoke a given action.
		
 */
/*                                                                                        */
/* Sql Statement:                                                                         */
/* 
			select id, path, okwosession
			from action, groupaction, usergroup
			where usergroup.userid = ?
			and   usergroup.groupid = groupaction.groupid
			and   groupaction.actionid = action.id
			and   groupaction.allow = 1
			and   action.path = ?
		
 */
/*                                                                                        */
/* DataObject Attributes Used:
   * id
   * Path
   * OKWOSession
 */
/* ************************************************************************************** */
vector<Action* >* Action::checkActionForUserByGroup(SqlDB& sqldb, intptr_t userid, twine& Path)
{
	EnEx ee(FL, "Action::checkActionForUserByGroup()");

	twine stmt = "select id, path, okwosession 			from action, groupaction, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groupaction.groupid 			and   groupaction.actionid = action.id 			and   groupaction.allow = 1 			and   action.path = ?";

	return Action::checkActionForUserByGroup(sqldb, stmt, true, userid, Path);

}

/* ************************************************************************************** */
/* This one matches the above in functionality, but allows you to pass in the sql         */
/* statement and a flag to indicate whether the input parameters will be used.            */
/* ************************************************************************************** */
vector<Action* >* Action::checkActionForUserByGroup(SqlDB& sqldb, twine& stmt, bool useInputs, intptr_t userid, twine& Path)
{
	EnEx ee(FL, "Action::checkActionForUserByGroup(twine& stmt, bool useInputs)");

	Timer selectTimer;
	Timer fetchTimer;

	sqlite3* db = sqldb.GetDatabase();
	sqlite3_stmt* db_stmt = NULL;

	// Use an sptr to ensure that if this method throws or causes an exception to be
	// thrown the vector wil be cleaned up before leaving this method.
	sptr< vector<Action* >, Action::deleteVector> ret = new vector<Action* >();

	try {
		int count;

		SQLTRACE(FL, "Using SQL: %s", stmt() );
		sqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );

		if(useInputs){
				DEBUG(FL, "Setting input (%d) to value: %d", 1, userid );
				sqldb.check_err( sqlite3_bind_int( db_stmt, 1, (int)userid) );
				DEBUG(FL, "Setting input (%d) to value: %s", 2, Path() );
				sqldb.check_err( sqlite3_bind_text( db_stmt, 2, Path(), (int)Path.length(), SQLITE_STATIC) );
		}

		selectTimer.Start();
		{ // Used for scope for the timing object.
			EnEx eeExe("Action::checkActionForUserByGroup()-ExecStmt");

			// Execute the statement
			DEBUG(FL, "Executing the statement for Action::checkActionForUserByGroup");
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		selectTimer.Finish();
		if(selectTimer.Duration() > 0.2){
			WARN(FL, "Statement took longer than 200ms to execute.");
		}

		// Now that we've executed the statement, we'll know how many output columns we have.
		// Grab the column count so that we don't bind invalid output positions.
		int colCount = sqlite3_column_count( db_stmt );

		fetchTimer.Start();
		while( count != 0 ){
			// Create the new object for this row
			Action* obj = new Action( );

			// Pick up all of the output columns
			if( 0 < colCount ){
				obj->id = sqlite3_column_int( db_stmt, 0);
			}
			if( 1 < colCount ){
				obj->Path.set( (const char*)sqlite3_column_text( db_stmt, 1), (size_t)sqlite3_column_bytes(db_stmt, 1) );
			}
			if( 2 < colCount ){
				obj->OKWOSession = sqlite3_column_int( db_stmt, 2);
			}

			// Add the object to our return vector
			ret->push_back( obj );

			// Advance to the next row of data
			count = sqldb.check_err( sqlite3_step( db_stmt ) );
		}
		fetchTimer.Finish();
		if(fetchTimer.Duration() > 1.0){
			WARN(FL, "Statement took longer than 1000ms to fetch.");
		}


	} catch (AnException& e) {
		// Ensure that no matter the exception we release the database back to the object.
		if(db_stmt != NULL){
			sqlite3_finalize( db_stmt );
		}
		sqldb.ReleaseDatabase();
		throw e; // re-throw the exception
	}

	// When we return, ensure that we release the sptr, so that we don't accidentally
	// delete the vector and its contents when leaving this method.
	if(db_stmt != NULL){
		sqlite3_finalize( db_stmt );
	}
	sqldb.ReleaseDatabase();
	return ret.release();
}

/* ************************************************************************************** */
/* This method will do a replacement of all of the parameter markers in                   */
/* the sql statement with the standard parameter list that is defined.                    */
/* This is useful for automatically prepping a SQL statement that doesn't                 */
/* work with parameter markers.                                                           */
/* ************************************************************************************** */
twine Action::checkActionForUserByGroup_prepSQL(IOConn& ioc, intptr_t userid, twine& Path)
{
	EnEx ee(FL, "Action::checkActionForUserByGroup_prepSQL()");

	size_t idx = 0;
	twine stmt = "select id, path, okwosession 			from action, groupaction, usergroup 			where usergroup.userid = ? 			and   usergroup.groupid = groupaction.groupid 			and   groupaction.actionid = action.id 			and   groupaction.allow = 1 			and   action.path = ?";

	// Replace the userid parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		twine tmp; tmp = userid;
		stmt.replace(idx, 1, tmp);
	}

	// Replace the Path parameter marker.
	idx = stmt.find('?', idx);
	if(idx != TWINE_NOT_FOUND){
		stmt.replace(idx, 1, Path );
	}

	// Also take a look at the statement and replace any session variables
	Statics::ReplaceSessionVars(ioc, stmt);

	return stmt;

}

