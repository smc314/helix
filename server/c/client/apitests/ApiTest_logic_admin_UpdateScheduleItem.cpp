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

void ApiTest_logic_admin_UpdateScheduleItem_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_UpdateScheduleItem_CallWithEmptyPayload();
void ApiTest_logic_admin_UpdateScheduleItem_CallWithValidPayload();
void ApiTest_logic_admin_UpdateScheduleItem_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/UpdateScheduleItem here

/** This is the main method that executes the tests for the /logic/admin/UpdateScheduleItem api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_UpdateScheduleItem()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/UpdateScheduleItem") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_UpdateScheduleItem_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_UpdateScheduleItem_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_UpdateScheduleItem_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_UpdateScheduleItem_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/UpdateScheduleItem without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_UpdateScheduleItem_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_UpdateScheduleItem_NoAuthorization_ShouldFail" )

	// Api /logic/admin/UpdateScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->UpdateScheduleItem(inputObj);
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

/** This test will call the /logic/admin/UpdateScheduleItem with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_UpdateScheduleItem_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_UpdateScheduleItem_CallWithEmptyPayload" )

	// Api /logic/admin/UpdateScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->UpdateScheduleItem(inputObj);
		ASSERT_TRUE(false, "Should have received an error from the server for an empty item.");
	} catch (AnException& e){
		// Ignore this - we expect an exception.
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

/** This test will call the /logic/admin/UpdateScheduleItem with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_UpdateScheduleItem_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_UpdateScheduleItem_CallWithValidPayload" )

	// Api /logic/admin/UpdateScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	inputObj.TaskName = "ApiTest_logic_admin_UpdateScheduleItem_CallWithValidPayload";
	inputObj.TaskUrl = "/logic/admin/GetScheduleItems";
	inputObj.isActive = 0;
	inputObj.dowMonday = 1;
	inputObj.dowTuesday = 2;
	inputObj.dowWednesday = 3;
	inputObj.dowThursday = 4;
	inputObj.dowFriday = 5;
	inputObj.dowSaturday = 6;
	inputObj.dowSunday = 7;

	// Insert this item first so that we can play with the update:
	SchedItem_svect insertList = SchedItem::readXmlChildren(
		xmlDocGetRootElement(
			m_api->InsertScheduleItem( inputObj )
		)
	);
	ASSERT_EQUALS(1, insertList->size(), "Insert list does not have 1 item in it.");
	SchedItem* insertResp = (*insertList)[0];

	// Then make our updates to the new item
	insertResp->TaskName = "Updated_ApiTest_logic_admin_UpdateScheduleItem_CallWithValidPayload";
	insertResp->TaskUrl = "/updated/logic/admin/GetScheduleItems";
	insertResp->dowMonday = 2;
	insertResp->dowTuesday = 3;
	insertResp->dowWednesday = 4;
	insertResp->dowThursday = 5;
	insertResp->dowFriday = 6;
	insertResp->dowSaturday = 7;
	insertResp->dowSunday = 8;

	xmlDocPtr resp;
	resp = m_api->UpdateScheduleItem(*insertResp);
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	SchedItem_svect updateList = SchedItem::readXmlChildren( xmlDocGetRootElement( resp ) );
	ASSERT_EQUALS(1, updateList->size(), "Update list does not have 1 item in it.");
	SchedItem* updateResp = (*updateList)[0];

	// Verify that our updates took hold
	ASSERT_EQUALS(insertResp->id, updateResp->id, "id Fields don't match.");
	ASSERT_EQUALS(insertResp->TaskName, updateResp->TaskName, "TaskName Fields don't match.");
	ASSERT_EQUALS(insertResp->TaskUrl, updateResp->TaskUrl, "TaskUrl Fields don't match.");
	ASSERT_EQUALS(insertResp->dowMonday, updateResp->dowMonday, "dowMonday Fields don't match.");
	ASSERT_EQUALS(insertResp->dowTuesday, updateResp->dowTuesday, "dowTuesday Fields don't match.");
	ASSERT_EQUALS(insertResp->dowWednesday, updateResp->dowWednesday, "dowWednesday Fields don't match.");
	ASSERT_EQUALS(insertResp->dowThursday, updateResp->dowThursday, "dowThursday Fields don't match.");
	ASSERT_EQUALS(insertResp->dowFriday, updateResp->dowFriday, "dowFriday Fields don't match.");
	ASSERT_EQUALS(insertResp->dowSaturday, updateResp->dowSaturday, "dowSaturday Fields don't match.");
	ASSERT_EQUALS(insertResp->dowSunday, updateResp->dowSunday, "dowSunday Fields don't match.");

	// When we're done with the new item, delete it from the server
	m_api->DeleteScheduleItem( *insertResp );
	
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

/** This test will call the /logic/admin/UpdateScheduleItem with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_UpdateScheduleItem_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_UpdateScheduleItem_CallWithInvalidPayload" )

	// Api /logic/admin/UpdateScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->UpdateScheduleItem(inputObj);
		ASSERT_TRUE(false, "Should have received an error from the server for an empty item.");
	} catch (AnException& e){
		// Ignore this - we expect an exception.
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
