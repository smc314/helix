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

void ApiTest_logic_admin_DeleteIAFile_NoAuthorization_ShouldFail();
void ApiTest_logic_admin_DeleteIAFile_CallWithEmptyPayload();
void ApiTest_logic_admin_DeleteIAFile_CallWithValidPayload();
void ApiTest_logic_admin_DeleteIAFile_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/admin/DeleteIAFile here

/** This is the main method that executes the tests for the /logic/admin/DeleteIAFile api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_admin_DeleteIAFile()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/admin/DeleteIAFile") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_admin_DeleteIAFile_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_admin_DeleteIAFile_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_admin_DeleteIAFile_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_admin_DeleteIAFile_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/admin/DeleteIAFile without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_admin_DeleteIAFile_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteIAFile_NoAuthorization_ShouldFail" )

	// Api /logic/admin/DeleteIAFile requires an object of type IAFile as input.
	IAFile inputObj;

	xmlDocPtr resp;
	resp = m_api->DeleteIAFile(inputObj);
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

/** This test will call the /logic/admin/DeleteIAFile with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_DeleteIAFile_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteIAFile_CallWithEmptyPayload" )

	// Api /logic/admin/DeleteIAFile requires an object of type IAFile as input.
	IAFile inputObj;

	xmlDocPtr resp;
	resp = m_api->DeleteIAFile(inputObj);
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

/** This test will call the /logic/admin/DeleteIAFile with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_DeleteIAFile_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteIAFile_CallWithValidPayload" )

	// Api /logic/admin/DeleteIAFile requires an object of type IAFile as input.
	IAFile inputObj;
	inputObj.ParentFolder = "./";
	inputObj.FileName = "ApiTest_logic_admin_DeleteIAFile_CallWithValidPayload";
	inputObj.FileContents = "Something\nVery\nInteresting\ngoes in here!\n";
	m_api->SaveIAFile( inputObj );
	if(m_log_steps){
		printf("++ Created test file.\n");
	}
		
	// Now pull up the file list and ensure that our file is in it.
	IAFolder inputFolder;
	inputFolder.ParentFolder = "./";
	xmlDocPtr resp;
	resp = m_api->GetIAFileList(inputFolder);
	IAFile_svect fileList = IAFile::readXmlChildren( xmlDocGetRootElement( resp ) );
	bool foundOurFile = false;
	for(size_t i = 0; i < fileList->size(); i++){
		if( (*fileList)[i]->FileName == inputObj.FileName ){
			foundOurFile = true;
			break;
		}
	}
	ASSERT_TRUE( foundOurFile, "Did not find our file after a save.")
	if(m_log_steps){
		printf("++ Found test file in list.\n");
	}

	// Now proceed with the delete
	resp = m_api->DeleteIAFile(inputObj);
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}

	// Get the file list again and verify that our file is gone
	resp = m_api->GetIAFileList(inputFolder);
	fileList = IAFile::readXmlChildren( xmlDocGetRootElement( resp ) );
	foundOurFile = false;
	for(size_t i = 0; i < fileList->size(); i++){
		if( (*fileList)[i]->FileName == inputObj.FileName ){
			foundOurFile = true;
			break;
		}
	}
	ASSERT_FALSE( foundOurFile, "File still exists after delete.")
	if(m_log_steps){
		printf("++ Test file deleted correctly.\n");
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

/** This test will call the /logic/admin/DeleteIAFile with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_admin_DeleteIAFile_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_admin_DeleteIAFile_CallWithInvalidPayload" )

	// Api /logic/admin/DeleteIAFile requires an object of type IAFile as input.
	IAFile inputObj;

	xmlDocPtr resp;
	resp = m_api->DeleteIAFile(inputObj);
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
