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

void ApiTest_logic_admin_GetSQLWork_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_GetSQLWork_CallWithEmptyPayload();
void ApiTest_logic_admin_GetSQLWork_CallWithValidPayload();
void ApiTest_logic_admin_GetSQLWork_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/GetSQLWork here

/** This is the main method that executes the tests for the /logic/admin/GetSQLWork api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_GetSQLWork()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/GetSQLWork") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_GetSQLWork_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_GetSQLWork_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_GetSQLWork_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_GetSQLWork_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/GetSQLWork without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_GetSQLWork_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetSQLWork_NoAuthorization_ShouldFail" )

	// Api /logic/admin/GetSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	xmlDocPtr resp;
	resp = m_api->GetSQLWork(inputObj);
	ASSERT_NOTNULL(resp, "resp should not be null, but it is.")
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

/** This test will call the /logic/admin/GetSQLWork with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetSQLWork_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetSQLWork_CallWithEmptyPayload" )

	// Api /logic/admin/GetSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->GetSQLWork(inputObj);
		ASSERT_TRUE(false, "API Call should have failed.");
	} catch (AnException& e){
		// Ignore this - this is what we expect to happen.
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

/** This test will call the /logic/admin/GetSQLWork with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetSQLWork_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetSQLWork_CallWithValidPayload" )

	// Save a test file to the server first so that we can test the Get call.
	SQLWork newWork;
	newWork.FileName = "ApiTest_logic_admin_GetSQLWork_CallWithValidPayload";
	m_api->SaveSQLWork( newWork );


	// Api /logic/admin/GetSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;
	inputObj.FileName = newWork.FileName;

	xmlDocPtr resp;
	resp = m_api->GetSQLWork(inputObj);
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	SQLWork_svect workList = SQLWork::readXmlChildren( xmlDocGetRootElement( resp ) );
	ASSERT_EQUALS(1, workList->size(), "Returned list of SQLWork files should have a size of 1.")
	SQLWork* respWork = (*workList)[0];

	ASSERT_EQUALS(newWork.FileName, respWork->FileName, "FileName fields don't match.")

	// When we are done with it - ensure that we delete the work file:
	m_api->DeleteSQLWork( newWork );

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

/** This test will call the /logic/admin/GetSQLWork with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetSQLWork_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetSQLWork_CallWithInvalidPayload" )

	// Api /logic/admin/GetSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->GetSQLWork(inputObj);
		ASSERT_TRUE(false, "Api call should have failed.")
	} catch(AnException& e){
		// Ignore this - we expect an exception
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
