/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "ActionHtml.h"
#include "HttpConn.h"
using namespace Helix::Glob;

#include <EnEx.h>
#include <AnException.h>
#include <File.h>
#include <Date.h>
#include <memptr.h>
using namespace SLib;

// Adds us to the global ActionClass Registry:
ActionClassRegister<ActionHtml> ActionHtml::reg("ActionHtml", 2, "/");

ActionHtml::ActionHtml(xmlNodePtr action)
{
	EnEx ee(FL, "ActionHtml::ActionHtml(xmlNodePtr action)");

	m_name.getAttribute(action, "name");
	m_license_group.getAttribute(action, "group");
	m_requires_session = true;
	
	if(m_name.empty()){
		throw AnException(0, FL, "Action missing urlbase!");
	}
	if(m_license_group.empty()){
		throw AnException(0, FL, "Action missing group!");
	}
	
}

ActionHtml::ActionHtml(twine name)
{
	EnEx ee(FL, "ActionHtml::ActionHtml(twine name)");

	m_name = name;
	m_license_group = "";
	m_requires_session = false;
	
}

ActionHtml::ActionHtml(const ActionHtml& c)
{
	EnEx ee(FL, "ActionHtml::ActionHtml(const ActionHtml& c)");

	m_name = c.m_name;
	m_license_group = c.m_license_group;
	m_requires_session = c.m_requires_session;
}

ActionHtml& ActionHtml::operator= (const ActionHtml& c)
{
	EnEx ee(FL, "ActionHtml::operator=(const ActionHtml& c)");

	m_name = c.m_name;
	m_license_group = c.m_license_group;
	m_requires_session = c.m_requires_session;
	return *this;
}

ActionHtml::~ActionHtml()
{
	EnEx ee(FL, "ActionHtml::~ActionHtml()");

}

int ActionHtml::matchesURL(twine target_url)
{
	EnEx ee(FL, "ActionHtml::matchesURL()");

	if(target_url.startsWith(m_name)){
		return m_name.length();
	} else {
		return 0;
	}
}

void ActionHtml::ExecuteRequest(IOConn& ioc)
{
	EnEx ee(FL, "ActionHtml::ExecuteRequest()");

	// What's the page?
	twine html_page = ioc.MsgTarget();
	
	if(html_page == "/"){
		html_page = "/index.html";
	}
	
	File html;
	Date expires;
	expires.AddDay(1);
	
	try {
		// Check for a qd/page first:
		if(html_page.startsWith("/qd/")){
			// Accomodate our unit testing applications:
			size_t testLayouts = html_page.find( "/test/html/layouts/" ) ;
			if(testLayouts != TWINE_NOT_FOUND){
				html_page.replace( testLayouts, 10, "/build" );
			}
			html.open("../../.." + html_page);
			// don't expire these pages, they change all the time
			expires.AddDay(-2);
		} else if(html_page.startsWith("/qooxdoo_toolkit")){
			html.open(".." + html_page);
			// these are static, expires is just fine.
			expires.AddYear(1);
		} else if(html_page.startsWith("/qooxdoo-contrib")){
			html.open(".." + html_page);
			// these are static, expires is just fine.
			expires.AddYear(1);
		} else if(html_page.startsWith("/3rdParty/qooxdoo")){
			html.open("../../../.." + html_page);
			// these are static, expires is just fine.
			expires.AddYear(1);
		} else if(html_page.startsWith("/logfile/")){
			html.open("." + html_page.substr(8));
			// don't expire these pages, let the last-modified checks work.
			expires.AddDay(-2);
		} else if(html_page.startsWith("/forwardtosupport/")){
			html.open("." + html_page );
			// don't expire these pages, let the last-modified checks work.
			expires.AddDay(-2);
		} else {
			// Load the page from our html folder:
			html.open("../../../html" + html_page);
			// don't expire these pages, let the last-modified checks work.
			expires.AddDay(-2);
		}

		HttpConn& hioc = (HttpConn&)ioc;
		Date ims = hioc.GetIfModifiedSince();
		
		if(html.lastModified() <= ims){
			DEBUG(FL, "Url (%s) LastMod (%s) <= IfModSince (%s) - Sending Not Modified",
				html_page(), html.lastModified().GetValue(), ims.GetValue() );

			hioc.SendNotModified();
		} else {
			// Send the data
			memptr<unsigned char> data;
			data = html.readContents();
			
			DEBUG(FL, "Serving (%s) from (%s) with size (%d)", html_page(), html.name()(), html.size() );
			ioc.SendReturn(data, html.size(), html.name(), html.lastModified(), expires );
		}

		ioc.Close();
	} catch (AnException&){
		INFO(FL, "Sending NotFound for request (%s)", html_page() );
		ioc.SendNotFound();
		ioc.Close();
	}
}
