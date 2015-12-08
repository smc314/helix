/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#include <EnEx.h>
#include <Log.h>
#include <Date.h>
#include <AnException.h>
#include <twine.h>
#include <dptr.h>
#include <Timer.h>
#include <HttpClient.h>
#include <XmlHelpers.h>
using namespace SLib;

#include "ApiTest.h"
#include "TestLog.h"
#include "TestCache.h"
using namespace Helix::Test;

// This adds us to the global DynamicTest Registry
DynamicTestRegister<ApiTest> ApiTest::reg("ApiTest");

ApiTest::ApiTest() : DynamicTest()
{
	EnEx ee(FL, "ApiTest::ApiTest()");

	m_sendInput = false;
	m_verifyOutput = false;
	m_logInput = true;
	m_logOutput = true;
	m_response = NULL;
	m_apiPath = "/";
}

ApiTest::ApiTest(xmlNodePtr testNode) : DynamicTest(testNode)
{
	EnEx ee(FL, "ApiTest::ApiTest(xmlNodePtr testNode)");

	m_sendInput = XmlHelpers::getBoolAttr(testNode, "sendInput");
	m_verifyOutput = XmlHelpers::getBoolAttr(testNode, "verifyOutput");
	m_logInput = XmlHelpers::getBoolAttr(testNode, "logInput");
	m_logOutput = XmlHelpers::getBoolAttr(testNode, "logOutput");
	m_response = NULL;
	m_apiPath.getAttribute(testNode, "apiPath");
}

ApiTest::~ApiTest()
{
	EnEx ee(FL, "ApiTest::~ApiTest()");

	if(m_response != NULL){
		xmlFreeDoc( m_response );
		m_response = NULL;
	}
}

void ApiTest::Run()
{
	EnEx ee(FL, "ApiTest::Run()");

	m_testPassed = false;
	sptr<xmlDoc, xmlFreeDoc> request;
	request = CreateInputDoc();

	try {
		SendRequest( request, m_apiPath );
		// Response document is in m_response;
		if(m_logOutput){
			WriteLine("Response is:\n" + XmlHelpers::docToStringPretty( m_response ) );
		}
		if(m_verifyOutput){
			VerifyOutput();
		}
		m_testPassed = true;
		//WriteLine("Test Passed!");
	} catch (AnException& e){
		WriteLine( e.Msg() );
		m_testPassed = false;
		//WriteLine("Test Failed!");
	}
}

xmlDocPtr ApiTest::CreateInputDoc()
{
	EnEx ee(FL, "ApiTest::CreateInputDoc()");

	xmlDocPtr ret;
	ret = xmlNewDoc((const xmlChar*)"1.0");

	if(m_sendInput){
		// Find the InputDocument element of our test:
		xmlNodePtr inputDoc = XmlHelpers::FindChild( m_testNode, "InputDocument" );
		if(inputDoc != NULL){
			// Find the first Element node under InputDocument:
			for(xmlNodePtr node = inputDoc->xmlChildrenNode; node != NULL; node = node->next){
				if(node->type == XML_ELEMENT_NODE){
					// copy the node into the new document
					ret->children = xmlCopyNode(node, 1);
					return ret;
				}
			}
		}
	}

	// If sendInput is false, or we couldn't find the InputDocument in our test, then create
	// a single-node document that is just the name of the API we are invoking.
	vector<twine> pathParts = m_apiPath.split("/");
	twine lastPart = pathParts[ pathParts.size() - 1 ];
	ret->children = xmlNewDocNode(ret, NULL, lastPart, NULL);

	return ret;
}

void ApiTest::returnHasErrors()
{
	EnEx ee(FL, "ApiTest::returnHasErrors()");

	if(m_response == NULL){
		throw AnException(0, FL, "No response received.");	
	}

	xmlNodePtr root = xmlDocGetRootElement( m_response );

	bool haserror = XmlHelpers::getBoolAttr(root, "haserror");
	if(haserror){
		twine errMessages;
		vector<xmlNodePtr> errs = XmlHelpers::FindChildren(XmlHelpers::FindChild(root, "Errors"),"Error");
		for(size_t i = 0; i < errs.size(); i++){
			twine msg( errs[i], "msg" );
			errMessages += msg + "\n\n";
		}
		throw AnException(0, FL, errMessages());
	}
}

void ApiTest::SendRequest(xmlDocPtr req, const twine& requestName )
{
	EnEx ee(FL, "ApiTest::SendRequest()");

	twine baseUrl = TestCache::get("ApiTestBaseUrl");

	twine url; 
	url = baseUrl + requestName;
	twine msg = XmlHelpers::docToString( req );
	msg = TestCache::getInstance().ReplaceVars( msg );
	WriteLine("Sending to url: " + url );
	if(m_logInput){
		WriteLine("Message is:\n" + msg );
	}
	dptr<HttpClient> http;
	http = new HttpClient();
	m_response = http->Post( url, msg(), msg.length() );
	// check for errors:
	returnHasErrors();
}

void ApiTest::VerifyOutput()
{
	EnEx ee(FL, "ApiTest::VerifyOutput()");

	if(m_verifyOutput == false) return; // quick bail-out.

	xmlNodePtr output = XmlHelpers::FindChild(m_testNode, "Output");
	if(output == NULL) return; // No output verification instructions.

	VerifyRootElementName( output );
	VerifyChildNodes( output );

}

void ApiTest::VerifyRootElementName(xmlNodePtr outputRules)
{
	EnEx ee(FL, "ApiTest::VerifyRootElementName(xmlNodePtr outputRules)");

	twine rootElementName(outputRules, "rootElementName");
	xmlNodePtr respRoot = xmlDocGetRootElement( m_response );
	if( rootElementName.compare( respRoot->name ) != 0){
		throw AnException(0, FL, "Response root element name is incorrect.  Expected %s but found %s",
			rootElementName(), respRoot->name );
	}

}

void ApiTest::VerifyChildNodes(xmlNodePtr outputRules)
{
	EnEx ee(FL, "ApiTest::VerifyChildNodes(xmlNodePtr outputRules)");

	xmlNodePtr respRoot = xmlDocGetRootElement( m_response );
	vector<xmlNodePtr> childNodes = XmlHelpers::FindChildren(outputRules, "ChildNodes");
	for(size_t i = 0; i < childNodes.size(); i++){
		xmlNodePtr childNodeRules = childNodes[i];
		twine childNodeName(childNodeRules, "name");
		bool atLeastOne = XmlHelpers::getBoolAttr(childNodeRules, "atLeastOne");
		twine whereAttr(childNodeRules, "whereAttr");
		twine whereValue(childNodeRules, "whereValue");
		//WriteLine("whereAttr = " + whereAttr + ", whereValue = " + whereValue + ".");
		whereValue = TestCache::getInstance().ReplaceVars( whereValue );

		whereAttr.rtrim();
		whereValue.rtrim();
		//WriteLine("whereAttr = " + whereAttr + ", whereValue = " + whereValue + ".");

		vector<xmlNodePtr> matchingChildren = XmlHelpers::FindChildren(respRoot, childNodeName());
		if(atLeastOne){
			// First verify that we have any children at all
			if(matchingChildren.size() == 0){
				throw AnException(0, FL, "At least one child node named %s is expected in the output.",
					childNodeName() );
			}

			// Then if we are looking for a specific value, search for that as well
			if(whereAttr.size() != 0 && whereValue.size() != 0){
				// Search for a child with an attribute that has a value that matches the condition
				//WriteLine("Looking for child " + childNodeName + " having attribute " + whereAttr + "=" + whereValue);
				xmlNodePtr whereChild = XmlHelpers::FindChildWithAttribute(
					respRoot, childNodeName(), whereAttr(), whereValue() );
				if(whereChild == NULL){
					throw AnException(0, FL, "At least one which node named %s with attr %s having value %s is required.",
						childNodeName(), whereAttr(), whereValue() );
				}
			}
		}

		// Check the child node attributes
		vector<xmlNodePtr> attributes = XmlHelpers::FindChildren(childNodeRules, "Attribute");
		for(size_t ch_i = 0; ch_i < matchingChildren.size(); ch_i++){
			xmlNodePtr respChild = matchingChildren[ch_i];

			for(size_t attr_i = 0; attr_i < attributes.size(); attr_i++){
				xmlNodePtr attr = attributes[attr_i];

				twine attrName(attr, "name");
				twine verifyValue(attr, "verifyValue");
				twine saveAs(attr, "saveAs");
				twine saveIfAttr(attr, "saveIfAttr");
				twine saveIfValue(attr, "saveIfValue");

				// Verify that we find this attribute on the current child:
				bool hasProp = xmlHasProp(respChild, attrName);
				if(!hasProp){
					throw AnException(0, FL, "Child node %s missing attribute %s",
						childNodeName(), attrName() );
				}

				verifyValue = TestCache::getInstance().ReplaceVars( verifyValue );
				verifyValue.rtrim();
				if(verifyValue.size() != 0){
					twine checkValue(respChild, attrName());
					if(checkValue != verifyValue){
						throw AnException(0, FL, "Child node %s attribute %s expected to be '%s' but is '%s'",
							childNodeName(), attrName(), verifyValue(), checkValue() );
					}
				}

				saveAs.rtrim();
				saveIfAttr.rtrim();
				saveIfValue.rtrim();
				if(saveAs.size() != 0){
					if(saveIfAttr.size() != 0 && saveIfValue.size() != 0) {
						// Save the attr only if the condition matches
						twine checkValue(respChild, saveIfAttr());
						if(checkValue == saveIfValue){
							// go ahead and save the attribute
							twine attrValue(respChild, attrName());
							TestCache::getInstance().AddCacheItem( saveAs, attrValue );
						}
					} else {
						// Always save the attr
						twine attrValue(respChild, attrName());
						TestCache::getInstance().AddCacheItem( saveAs, attrValue );
					}
				}
			}
		}
	}
}
