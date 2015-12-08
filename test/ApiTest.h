/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#ifndef APITEST_H
#define APITEST_H

#include <map>
#include <vector>
using namespace std;

#include <twine.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

#include "DynamicTest.h"
using namespace Helix::Test;

namespace Helix {
namespace Test {

/**
 * This class defines a test that will execute a server API directly and check
 * the response from the server.
 */
class ApiTest : public DynamicTest
{
	public:
		
		/** Standard constructor to create an empty dynamic test.
		 */
		ApiTest();

		/** Constructor that will read our configuration from the given XML Node.
		 */
		ApiTest(xmlNodePtr testNode);

		/// Standard Destructor
		virtual ~ApiTest();

		/// This method will execute the test itself.  Must be implemented by subclasses.
		virtual void Run();

	protected:

		void returnHasErrors();
		void SendRequest(xmlDocPtr req, const twine& requestName);
		xmlDocPtr CreateInputDoc();
		void VerifyOutput();
		void VerifyRootElementName(xmlNodePtr outputRules);
		void VerifyChildNodes(xmlNodePtr outputRules);

		bool m_sendInput;
		bool m_verifyOutput;
		bool m_logInput;
		bool m_logOutput;
		twine m_apiPath;
		xmlDocPtr m_response;


	private:
		// Registers us with the global factory map
		static DynamicTestRegister<ApiTest> reg;

}; // End ApiTest class

} } // End namespace stack

#endif // APITEST_H Defined
