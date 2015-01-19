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

void ApiTest_logic_admin_DeleteSQLWork_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_DeleteSQLWork_CallWithEmptyPayload();
void ApiTest_logic_admin_DeleteSQLWork_CallWithValidPayload();
void ApiTest_logic_admin_DeleteSQLWork_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/DeleteSQLWork here

/** This is the main method that executes the tests for the /logic/admin/DeleteSQLWork api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_DeleteSQLWork()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/DeleteSQLWork") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_DeleteSQLWork_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_DeleteSQLWork_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_DeleteSQLWork_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_DeleteSQLWork_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/DeleteSQLWork without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_DeleteSQLWork_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteSQLWork_NoAuthorization_ShouldFail" )

	// Api /logic/admin/DeleteSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	xmlDocPtr resp;
	resp = m_api->DeleteSQLWork(inputObj);
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

/** This test will call the /logic/admin/DeleteSQLWork with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_DeleteSQLWork_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteSQLWork_CallWithEmptyPayload" )

	// Api /logic/admin/DeleteSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	xmlDocPtr resp;
	resp = m_api->DeleteSQLWork(inputObj);
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

/** This test will call the /logic/admin/DeleteSQLWork with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_DeleteSQLWork_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteSQLWork_CallWithValidPayload" )


	// First create an working file that we can test with
	SQLWork inputObj;
	inputObj.FileName = "ApiTest_logic_admin_DeleteSQLWork_CallWithValidPayload";
	inputObj.Sql = "lots\nof\nwonderful\nsql\nstatements go in here;";

	xmlDocPtr resp;
	resp = m_api->SaveSQLWork(inputObj);

	// Now query for the list of sqlwork files
	IAFolder parentFolder;
	parentFolder.ParentFolder = "./sqlwork/";
	resp = m_api->GetWorkFileList( parentFolder );
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	IAFile_svect fileList = IAFile::readXmlChildren( xmlDocGetRootElement( resp ) );
	bool foundOurFile = false;
	for(size_t i = 0; i < fileList->size(); i++){
		if( (*fileList)[i]->FileName == inputObj.FileName ){
			foundOurFile = true;
			break;
		}
	}
	ASSERT_TRUE(foundOurFile, "Did not find our file after the save.");

	// Now verify that the delete works
	resp = m_api->DeleteSQLWork(inputObj);
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}

	// Query for the file list again, and verify that it is gone:
	resp = m_api->GetWorkFileList( parentFolder );
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	fileList = IAFile::readXmlChildren( xmlDocGetRootElement( resp ) );
	foundOurFile = false;
	for(size_t i = 0; i < fileList->size(); i++){
		if( (*fileList)[i]->FileName == inputObj.FileName ){
			foundOurFile = true;
			break;
		}
	}
	ASSERT_FALSE(foundOurFile, "Our file still exists after the delete.");

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

/** This test will call the /logic/admin/DeleteSQLWork with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_DeleteSQLWork_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteSQLWork_CallWithInvalidPayload" )

	// Api /logic/admin/DeleteSQLWork requires an object of type SQLWork as input.
	SQLWork inputObj;

	xmlDocPtr resp;
	resp = m_api->DeleteSQLWork(inputObj);
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
