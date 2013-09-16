/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "SessionInfo.h"
#include "SessionList.h"
using namespace Helix::Glob;

OdbcObj* SessionInfo::setDBConn(OdbcObj* oo)
{
	if(dbConn != NULL && dbConn != oo){
		delete dbConn;
	}
	dbConn = oo;
	return dbConn;
}


SessionInfo::SessionInfo()
{
	dbConn = NULL;
	userid = 0;
	dbConn_mutex = new Mutex();
}

SessionInfo::SessionInfo(xmlDocPtr doc)
{
	dbConn = NULL;
	dbConn_mutex = new Mutex();
	userid = 0;
	readFromXml(doc);
}

SessionInfo::~SessionInfo() 
{
	if(dbConn != NULL){
		delete dbConn;
		dbConn = NULL;
	}
	delete dbConn_mutex;
}

SessionInfo::SessionInfo(const SessionInfo& c)
{
	userid = c.userid;
	username = c.username;
	fullname = c.fullname;
	dbname = c.dbname;
	created = c.created;
	lastaccess = c.lastaccess;
	sessionGUID = c.sessionGUID;
	userProperties = c.userProperties;

	dbConn = c.dbConn;
}

SessionInfo& SessionInfo::operator=(const SessionInfo& c)
{
	userid = c.userid;
	username = c.username;
	fullname = c.fullname;
	dbname = c.dbname;
	created = c.created;
	lastaccess = c.lastaccess;
	sessionGUID = c.sessionGUID;
	userProperties = c.userProperties;

	dbConn = c.dbConn;

	return *this;
}

xmlDocPtr SessionInfo::createXmlDoc() 
{
	xmlDocPtr ret = xmlNewDoc((const xmlChar*)"1.0");
	ret->children = xmlNewDocNode(ret, NULL, (const xmlChar*)"SessionInfo", NULL);
	xmlNodePtr root = xmlDocGetRootElement(ret);

	xmlSetProp(root, (const xmlChar*)"sessionGUID", sessionGUID);
	xmlSetProp(root, (const xmlChar*)"created", created);
	xmlSetProp(root, (const xmlChar*)"lastaccess", lastaccess);

	map<twine, twine>::iterator it;
	for(it = userProperties.begin(); it != userProperties.end(); it++){
		xmlNodePtr elem = xmlNewChild(root, NULL, (const xmlChar*)"Property", NULL);
		xmlSetProp(elem, (const xmlChar*)"name", it->first);
		xmlSetProp(elem, (const xmlChar*)"value", it->second);
	}

	return ret;
}

void SessionInfo::readFromXml(xmlDocPtr doc)
{
	
	xmlNodePtr root = xmlDocGetRootElement(doc);
	sessionGUID.getAttribute( root, "sessionGUID" );
	twine tmp;
	tmp.getAttribute(root, "created");
	created.SetValue(tmp);
	tmp.getAttribute(root, "lastaccess");
	lastaccess.SetValue(tmp);

	vector<xmlNodePtr> props = XmlHelpers::FindChildren(root, "Property");
	for(int i = 0; i < (int)props.size(); i++){
		twine name(props[i], "name");
		twine value(props[i], "value");
		userProperties[name] = value;
	}

}

void SessionInfo::Save()
{
	SessionList& sl = SessionList::getInstance();
	sl.Save(*this);
}

