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

void ApiTest_logic_admin_GetOneScheduleItem_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_GetOneScheduleItem_CallWithEmptyPayload();
void ApiTest_logic_admin_GetOneScheduleItem_CallWithValidPayload();
void ApiTest_logic_admin_GetOneScheduleItem_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/GetOneScheduleItem here

/** This is the main method that executes the tests for the /logic/admin/GetOneScheduleItem api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_GetOneScheduleItem()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/GetOneScheduleItem") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_GetOneScheduleItem_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_GetOneScheduleItem_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_GetOneScheduleItem_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_GetOneScheduleItem_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/GetOneScheduleItem without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_GetOneScheduleItem_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetOneScheduleItem_NoAuthorization_ShouldFail" )

	// Api /logic/admin/GetOneScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->GetOneScheduleItem(inputObj);
	ASSERT_NOTNULL(resp, "Response document should not be null, but it is.")
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

/** This test will call the /logic/admin/GetOneScheduleItem with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetOneScheduleItem_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetOneScheduleItem_CallWithEmptyPayload" )

	// Api /logic/admin/GetOneScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->GetOneScheduleItem(inputObj);
	ASSERT_NOTNULL(resp, "Response document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	SchedItem_svect respList = SchedItem::readXmlChildren( xmlDocGetRootElement( resp ) );
	ASSERT_EQUALS(0, respList->size(), "Should be no elements in the response list")

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

/** This test will call the /logic/admin/GetOneScheduleItem with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetOneScheduleItem_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetOneScheduleItem_CallWithValidPayload" )

	// First pull up the full list of schedule items:
	SchedItem_svect list = SchedItem::readXmlChildren( 
		xmlDocGetRootElement(
			m_api->GetScheduleItems()
		)
	);

	// Now verify that we can call for each by id:
	for(size_t i = 0; i < list->size(); i++){
		// Api /logic/admin/GetOneScheduleItem requires an object of type SchedItem as input.
		SchedItem inputObj;
		inputObj.id = (*list)[ i ]->id;

		xmlDocPtr resp;
		resp = m_api->GetOneScheduleItem(inputObj);
		ASSERT_NOTNULL(resp, "Response document should not be null, but it is.")
		if(m_log_steps){
			printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
		}

		SchedItem_svect respList = SchedItem::readXmlChildren( xmlDocGetRootElement( resp ) );
		ASSERT_EQUALS(1, respList->size(), "Should only be one element in the response list")
		ASSERT_EQUALS(inputObj.id, (*respList)[0]->id, "ID's in the request and response should match.");
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

/** This test will call the /logic/admin/GetOneScheduleItem with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetOneScheduleItem_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetOneScheduleItem_CallWithInvalidPayload" )

	// Api /logic/admin/GetOneScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	inputObj.id = 314159;

	xmlDocPtr resp;
	resp = m_api->GetOneScheduleItem(inputObj);
	ASSERT_NOTNULL(resp, "Response document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	SchedItem_svect respList = SchedItem::readXmlChildren( xmlDocGetRootElement( resp ) );
	ASSERT_EQUALS(0, respList->size(), "Should be no elements in the response list")

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
