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

void ApiTest_logic_admin_InsertScheduleItem_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_InsertScheduleItem_CallWithEmptyPayload();
void ApiTest_logic_admin_InsertScheduleItem_CallWithValidPayload();
void ApiTest_logic_admin_InsertScheduleItem_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/InsertScheduleItem here

/** This is the main method that executes the tests for the /logic/admin/InsertScheduleItem api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_InsertScheduleItem()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/InsertScheduleItem") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_InsertScheduleItem_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_InsertScheduleItem_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_InsertScheduleItem_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_InsertScheduleItem_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/InsertScheduleItem without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_InsertScheduleItem_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_InsertScheduleItem_NoAuthorization_ShouldFail" )

	// Api /logic/admin/InsertScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	xmlDocPtr resp;
	resp = m_api->InsertScheduleItem(inputObj);
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

/** This test will call the /logic/admin/InsertScheduleItem with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_InsertScheduleItem_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_InsertScheduleItem_CallWithEmptyPayload" )

	// Api /logic/admin/InsertScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	try {
		xmlDocPtr resp;
		resp = m_api->InsertScheduleItem(inputObj);
		ASSERT_TRUE(false, "We should have received an error when inserting an empty item.");
	} catch (AnException& e){
		// Ignore this exception - it's what we are expecting.
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

/** This test will call the /logic/admin/InsertScheduleItem with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_InsertScheduleItem_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_InsertScheduleItem_CallWithValidPayload" )

	// Api /logic/admin/InsertScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	inputObj.TaskName = "Sample task from ApiTest_logic_admin_InsertScheduleItem_CallWithValidPayload";
	inputObj.TaskUrl = "/logic/admin/GetScheduleItems";
	inputObj.isActive = 0;
	inputObj.dowMonday = 1;
	inputObj.dowTuesday = 2;
	inputObj.dowWednesday= 3;
	inputObj.dowThursday = 3;
	inputObj.dowFriday = 5;
	inputObj.dowSaturday = 6;
	inputObj.dowSunday = 7;

	// Insert the new object and check the response
	xmlDocPtr resp;
	resp = m_api->InsertScheduleItem(inputObj);
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	SchedItem_svect respList = SchedItem::readXmlChildren( xmlDocGetRootElement( resp ) );
	ASSERT_EQUALS(1, respList->size(), "Should be one elements in the response list.");
	SchedItem* respObj = (*respList)[0];

	ASSERT_NOTEQUALS(inputObj.id, respObj->id, "ID Fields should not be the same.");
	ASSERT_EQUALS(inputObj.TaskName, respObj->TaskName, "TaskName Fields don't match.");
	ASSERT_EQUALS(inputObj.TaskUrl, respObj->TaskUrl, "TaskUrl Fields don't match.");
	ASSERT_EQUALS(inputObj.isActive, respObj->isActive, "isActive Fields don't match.");
	ASSERT_EQUALS(inputObj.dowMonday, respObj->dowMonday, "dowMonday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowTuesday, respObj->dowTuesday, "dowTuesday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowWednesday, respObj->dowWednesday, "dowWednesday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowThursday, respObj->dowThursday, "dowThursday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowFriday, respObj->dowFriday, "dowFriday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowSaturday, respObj->dowSaturday, "dowSaturday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowSunday, respObj->dowSunday, "dowSunday Fields don't match.");

	// Now query for the object directly by ID:
	SchedItem_svect respList2 = SchedItem::readXmlChildren(
		xmlDocGetRootElement(
			m_api->GetOneScheduleItem( *respObj )
		)
	);

	ASSERT_EQUALS(1, respList2->size(), "Should be one elements in the response list.");
	SchedItem* respObj2 = (*respList2)[0];

	ASSERT_NOTEQUALS(inputObj.id, respObj2->id, "ID Fields should not be the same.");
	ASSERT_EQUALS(respObj->id, respObj2->id, "ID Fields should not be the same.");
	ASSERT_EQUALS(inputObj.TaskName, respObj2->TaskName, "TaskName Fields don't match.");
	ASSERT_EQUALS(inputObj.TaskUrl, respObj2->TaskUrl, "TaskUrl Fields don't match.");
	ASSERT_EQUALS(inputObj.isActive, respObj2->isActive, "isActive Fields don't match.");
	ASSERT_EQUALS(inputObj.dowMonday, respObj2->dowMonday, "dowMonday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowTuesday, respObj2->dowTuesday, "dowTuesday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowWednesday, respObj2->dowWednesday, "dowWednesday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowThursday, respObj2->dowThursday, "dowThursday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowFriday, respObj2->dowFriday, "dowFriday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowSaturday, respObj2->dowSaturday, "dowSaturday Fields don't match.");
	ASSERT_EQUALS(inputObj.dowSunday, respObj2->dowSunday, "dowSunday Fields don't match.");

	// Once we're done testing with this one, remove it from the database
	m_api->DeleteScheduleItem( *respObj);

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

/** This test will call the /logic/admin/InsertScheduleItem with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_InsertScheduleItem_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_InsertScheduleItem_CallWithInvalidPayload" )

	// Api /logic/admin/InsertScheduleItem requires an object of type SchedItem as input.
	SchedItem inputObj;
	// Fill out the details for inputObj here:
	//inputObj.memberName1 = 1;
	//inputObj.memberName2 = 2;
	// etc...

	try {
		xmlDocPtr resp;
		resp = m_api->InsertScheduleItem(inputObj);
		ASSERT_TRUE(false, "We should have received an error when inserting an empty item.");
	} catch (AnException& e){
		// Ignore this exception - it's what we are expecting.
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
