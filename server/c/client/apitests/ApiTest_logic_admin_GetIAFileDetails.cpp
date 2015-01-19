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

void ApiTest_logic_admin_GetIAFileDetails_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_GetIAFileDetails_CallWithEmptyPayload();
void ApiTest_logic_admin_GetIAFileDetails_CallWithValidPayload();
void ApiTest_logic_admin_GetIAFileDetails_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/GetIAFileDetails here

/** This is the main method that executes the tests for the /logic/admin/GetIAFileDetails api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_GetIAFileDetails()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/GetIAFileDetails") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_GetIAFileDetails_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_GetIAFileDetails_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_GetIAFileDetails_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_GetIAFileDetails_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/GetIAFileDetails without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_GetIAFileDetails_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetIAFileDetails_NoAuthorization_ShouldFail" )

	// Api /logic/admin/GetIAFileDetails requires an object of type IAFile as input.
	IAFile inputObj;

	xmlDocPtr resp;
	resp = m_api->GetIAFileDetails(inputObj);
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

/** This test will call the /logic/admin/GetIAFileDetails with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetIAFileDetails_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetIAFileDetails_CallWithEmptyPayload" )

	// Api /logic/admin/GetIAFileDetails requires an object of type IAFile as input.
	IAFile inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->GetIAFileDetails(inputObj);
		ASSERT_TRUE(false, "API Call should fail.");
	} catch (AnException& e){
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

/** This test will call the /logic/admin/GetIAFileDetails with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetIAFileDetails_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetIAFileDetails_CallWithValidPayload" )

	// Api /logic/admin/GetIAFileDetails requires an object of type IAFile as input.
	
	// Save the file first, so that we can play with retrieving it's details
	IAFile inputObj;
	inputObj.ParentFolder = "./";
	inputObj.FileName = "ApiTest_logic_admin_GetIAFileDetails_CallWithValidPayload";
	inputObj.FileContents = "Something\nVery\nInteresting\ngoes in here!\n";
	m_api->SaveIAFile( inputObj );
		
	// Now pull up the saved file and verify the details
	xmlDocPtr resp;
	resp = m_api->GetIAFileDetails(inputObj);
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	IAFile_svect fileList = IAFile::readXmlChildren( xmlDocGetRootElement( resp ) );
	ASSERT_EQUALS( 1, fileList->size(), "Should be one element in file list.")
	IAFile* respFile = (*fileList)[0];

	ASSERT_EQUALS(inputObj.ParentFolder, respFile->ParentFolder, "ParentFolder fields don't match.")
	ASSERT_EQUALS(inputObj.FileName, respFile->FileName, "FileName fields don't match.")
	ASSERT_EQUALS(inputObj.FileContents, respFile->FileContents, "FileContents fields don't match.")

	// When we are done with it, go ahead and remove it
	m_api->DeleteIAFile( inputObj );

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

/** This test will call the /logic/admin/GetIAFileDetails with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_GetIAFileDetails_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_GetIAFileDetails_CallWithInvalidPayload" )

	// Api /logic/admin/GetIAFileDetails requires an object of type IAFile as input.
	IAFile inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->GetIAFileDetails(inputObj);
		ASSERT_TRUE(false, "API Call should fail.");
	} catch (AnException& e){
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
