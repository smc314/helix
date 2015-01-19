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

void ApiTest_logic_admin_SaveSQLWork_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_SaveSQLWork_CallWithEmptyPayload();
void ApiTest_logic_admin_SaveSQLWork_CallWithValidPayload();
void ApiTest_logic_admin_SaveSQLWork_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/SaveSQLWork here

/** This is the main method that executes the tests for the /logic/admin/SaveSQLWork api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_SaveSQLWork()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/SaveSQLWork") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_SaveSQLWork_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_SaveSQLWork_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_SaveSQLWork_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_SaveSQLWork_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/SaveSQLWork without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_SaveSQLWork_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_SaveSQLWork_NoAuthorization_ShouldFail" )

	// Api /logic/admin/SaveSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	xmlDocPtr resp;
	resp = m_api->SaveSQLWork(inputObj);
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
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

/** This test will call the /logic/admin/SaveSQLWork with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_SaveSQLWork_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_SaveSQLWork_CallWithEmptyPayload" )

	// Api /logic/admin/SaveSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->SaveSQLWork(inputObj);
		ASSERT_TRUE(false, "API call should have failed.");
	} catch (AnException& e){
		// Ignore this - we expect an exception to be raised
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

/** This test will call the /logic/admin/SaveSQLWork with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_SaveSQLWork_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_SaveSQLWork_CallWithValidPayload" )

	// Api /logic/admin/SaveSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;
	inputObj.FileName = "ApiTest_logic_admin_SaveSQLWork_CallWithValidPayload";
	inputObj.Sql = "lots\nof\nwonderful\nsql\nstatements go in here;";

	xmlDocPtr resp;
	resp = m_api->SaveSQLWork(inputObj);
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	SQLWork_svect respList = SQLWork::readXmlChildren( xmlDocGetRootElement( resp ) );
	ASSERT_EQUALS(0, respList->size(), "Response list should have no elements in it.")

	// Now query for the file directly:
	resp = m_api->GetSQLWork( inputObj );
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	SQLWork_svect respList2 = SQLWork::readXmlChildren( xmlDocGetRootElement( resp ) );
	SQLWork* respObj2 = (*respList2)[0];

	ASSERT_EQUALS(inputObj.FileName, respObj2->FileName, "FileName fields don't match.")
	ASSERT_EQUALS(inputObj.Sql, respObj2->Sql, "Sql fields don't match.")

	// When we are done - delete the working file
	m_api->DeleteSQLWork( inputObj );

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

/** This test will call the /logic/admin/SaveSQLWork with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_SaveSQLWork_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_SaveSQLWork_CallWithInvalidPayload" )

	// Api /logic/admin/SaveSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->SaveSQLWork(inputObj);
		ASSERT_TRUE(false, "API call should have failed.")
	} catch (AnException& e) {
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
