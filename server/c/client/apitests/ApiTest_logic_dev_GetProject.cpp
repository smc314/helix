/* ************************************************************************************** */
/* This is a Helix API Test file.  This file is included directly into the HelixTestApi   */
/* application at compile time.  No extra headers, etc. should be necessary here.  Refer  */
/* to HelixTestApi for the global variables and structures that you have access to.       */
/*                                                                                        */
/* Note that this file is auto-generated if missing, but then editable and maintained by  */
/* the developers.  If you want to get a fresh/updated version of this file, simply       */
/* delete it and it will be re-generated.                                                 */
/*                                                                                        */
/* ************************************************************************************** */

/* ************************************************************************************** */
/* Define all Local test methods here.                                                    */
/* ************************************************************************************** */

void ApiTest_logic_dev_GetProject_NoAuthorization_ShouldFail();
void ApiTest_logic_dev_GetProject_CallWithEmptyPayload();
void ApiTest_logic_dev_GetProject_CallWithValidPayload();
void ApiTest_logic_dev_GetProject_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/dev/GetProject here

/** This is the main method that executes the tests for the /logic/dev/GetProject api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_dev_GetProject()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/dev/GetProject") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_dev_GetProject_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_dev_GetProject_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_dev_GetProject_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_dev_GetProject_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/dev/GetProject without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_dev_GetProject_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_dev_GetProject_NoAuthorization_ShouldFail" )

	// Remove this out when you've updated these tests to be real
	ASSERT_TRUE(false, "Test not implemented yet.");

	// Api /logic/dev/GetProject requires an object of type Project as input.
	Project inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->GetProject(inputObj);
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}

	// Check to see if the return indicates that user hasn't logged in:
	ASSERT_TRUE(m_api->returnRequiresDB(), "Should have received a response indicating the user must log in.")

	// Useful macros:
	// ASSERT_EQUALS(a, b, "a is not equal to b, but it should be.")
	// ASSERT_NOTEQUALS(a, b, "a is equal to b, but it shouldn't be.")
	// ASSERT_NULL(a, "a should be null, but it isn't.")
	// ASSERT_NOTNULL(a, "a should not be null, but it is.")
	// ASSERT_TRUE(a, "a should be true, but it isn't.")
	// ASSERT_FALSE(a, "a should be false, but it isn't.")
	// QUIT_TEST_METHOD - Allows you to bail out of test early, with a successful result.

	END_TEST_METHOD
}

/** This test will call the /logic/dev/GetProject with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_dev_GetProject_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_dev_GetProject_CallWithEmptyPayload" )

	// Remove this out when you've updated these tests to be real
	ASSERT_TRUE(false, "Test not implemented yet.");

	// Api /logic/dev/GetProject requires an object of type Project as input.
	Project inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->GetProject(inputObj);
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}

	// Useful macros:
	// ASSERT_EQUALS(a, b, "a is not equal to b, but it should be.")
	// ASSERT_NOTEQUALS(a, b, "a is equal to b, but it shouldn't be.")
	// ASSERT_NULL(a, "a should be null, but it isn't.")
	// ASSERT_NOTNULL(a, "a should not be null, but it is.")
	// ASSERT_TRUE(a, "a should be true, but it isn't.")
	// ASSERT_FALSE(a, "a should be false, but it isn't.")
	// QUIT_TEST_METHOD - Allows you to bail out of test early, with a successful result.

	END_TEST_METHOD
}

/** This test will call the /logic/dev/GetProject with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_dev_GetProject_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_dev_GetProject_CallWithValidPayload" )

	// Remove this out when you've updated these tests to be real
	ASSERT_TRUE(false, "Test not implemented yet.");

	// Api /logic/dev/GetProject requires an object of type Project as input.
	Project inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->GetProject(inputObj);
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}

	// Useful macros:
	// ASSERT_EQUALS(a, b, "a is not equal to b, but it should be.")
	// ASSERT_NOTEQUALS(a, b, "a is equal to b, but it shouldn't be.")
	// ASSERT_NULL(a, "a should be null, but it isn't.")
	// ASSERT_NOTNULL(a, "a should not be null, but it is.")
	// ASSERT_TRUE(a, "a should be true, but it isn't.")
	// ASSERT_FALSE(a, "a should be false, but it isn't.")
	// QUIT_TEST_METHOD - Allows you to bail out of test early, with a successful result.

	END_TEST_METHOD
}

/** This test will call the /logic/dev/GetProject with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_dev_GetProject_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_dev_GetProject_CallWithInvalidPayload" )

	// Remove this out when you've updated these tests to be real
	ASSERT_TRUE(false, "Test not implemented yet.");

	// Api /logic/dev/GetProject requires an object of type Project as input.
	Project inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->GetProject(inputObj);
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}

	// Useful macros:
	// ASSERT_EQUALS(a, b, "a is not equal to b, but it should be.")
	// ASSERT_NOTEQUALS(a, b, "a is equal to b, but it shouldn't be.")
	// ASSERT_NULL(a, "a should be null, but it isn't.")
	// ASSERT_NOTNULL(a, "a should not be null, but it is.")
	// ASSERT_TRUE(a, "a should be true, but it isn't.")
	// ASSERT_FALSE(a, "a should be false, but it isn't.")
	// QUIT_TEST_METHOD - Allows you to bail out of test early, with a successful result.

	END_TEST_METHOD
}
