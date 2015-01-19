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

void ApiTest_logic_util_UpdateLogSettings_NoAuthorization_ShouldFail();
void ApiTest_logic_util_UpdateLogSettings_CallWithEmptyPayload();
void ApiTest_logic_util_UpdateLogSettings_CallWithValidPayload();
void ApiTest_logic_util_UpdateLogSettings_CallWithInvalidPayload();

// Define more of your own tests and methods for testing /logic/util/UpdateLogSettings here

/** This is the main method that executes the tests for the /logic/util/UpdateLogSettings api.  All tests
  * that should be executed against this api should be invoked directly here.
  */
void ApiTest_logic_util_UpdateLogSettings()
{
	// Ensure that we should be testing this API
	if(runTestsForApi("/logic/util/UpdateLogSettings") == false){
		return; // Tests for this api are not included in this run.
	}

	// Test the Api without authorization:
	ApiTest_logic_util_UpdateLogSettings_NoAuthorization_ShouldFail();

	// Test the Api with an empty payload
	ApiTest_logic_util_UpdateLogSettings_CallWithEmptyPayload();

	// Test the Api with a valid payload
	ApiTest_logic_util_UpdateLogSettings_CallWithValidPayload();

	// Test the Api with an invalid payload
	ApiTest_logic_util_UpdateLogSettings_CallWithInvalidPayload();

	// Call any other tests that you have defined here:
}

/** This will call the /logic/util/UpdateLogSettings without any authorization information.  This should
  * be rejected by the server, and we should receive the error message.
  */
void ApiTest_logic_util_UpdateLogSettings_NoAuthorization_ShouldFail()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_util_UpdateLogSettings_NoAuthorization_ShouldFail" )

	// Api /logic/util/UpdateLogSettings requires an object of type LogSettings as input.
	LogSettings inputObj;

	xmlDocPtr resp;
	resp = m_api->UpdateLogSettings(inputObj);
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

/** This test will call the /logic/util/UpdateLogSettings with an empty payload and check the response
  * that is received.
  */
void ApiTest_logic_util_UpdateLogSettings_CallWithEmptyPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_util_UpdateLogSettings_CallWithEmptyPayload" )

	// Api /logic/util/UpdateLogSettings requires an object of type LogSettings as input.
	LogSettings inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->UpdateLogSettings(inputObj);
		ASSERT_TRUE(false, "API Call should have failed.");
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

/** This test will call the /logic/util/UpdateLogSettings with a valid payload and check the response
  * that is received.
  */
void ApiTest_logic_util_UpdateLogSettings_CallWithValidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_util_UpdateLogSettings_CallWithValidPayload" )

	// First retrieve the current log settings for backup:
	LogSettings_svect origList = LogSettings::readXmlChildren(
		xmlDocGetRootElement(
			m_api->GetLogSettings()
		)
	);
	LogSettings* origSettings = (*origList)[0];
	
	// Api /logic/util/UpdateLogSettings requires an object of type LogSettings as input.
	LogSettings inputObj;
	inputObj.LogFile = "helixapitest.log";
	inputObj.BufferSize = 1234;
	inputObj.MaxSize = 102400;
	inputObj.panic = 1;
	inputObj.panicCapture = 1;
	inputObj.panicDump = 1234;
	inputObj.error = 1;
	inputObj.errorCapture = 1;
	inputObj.errorDump = 1234;
	inputObj.warn = 1;
	inputObj.warnCapture = 1;
	inputObj.warnDump = 1234;
	inputObj.info = 1;
	inputObj.infoCapture = 1;
	inputObj.infoDump = 1234;
	inputObj.debug = 1;
	inputObj.debugCapture = 1;
	inputObj.debugDump = 1234;
	inputObj.trace = 1;
	inputObj.traceCapture = 1;
	inputObj.traceDump = 1234;
	inputObj.sql = 1;
	inputObj.sqlCapture = 1;
	inputObj.sqlDump = 1234;

	xmlDocPtr resp;
	resp = m_api->UpdateLogSettings(inputObj);
	ASSERT_NOTNULL(resp, "Response Document should not be null, but it is.")
	if(m_log_steps){
		printf("++ Received XML Response:\n%s\n", XmlHelpers::docToStringPretty( resp )() );
	}
	
	// Retrieve the new settings and ensure they match:
	LogSettings_svect updatedList = LogSettings::readXmlChildren(
		xmlDocGetRootElement(
			m_api->GetLogSettings()
		)
	);
	LogSettings* updatedSettings = (*updatedList)[0];

	ASSERT_EQUALS( inputObj.LogFile, updatedSettings->LogFile, "LogFile fields don't match");
	ASSERT_EQUALS( inputObj.BufferSize, updatedSettings->BufferSize, "BufferSize fields don't match");
	ASSERT_EQUALS( inputObj.MaxSize, updatedSettings->MaxSize, "MaxSize fields don't match");
	ASSERT_EQUALS( inputObj.panic, updatedSettings->panic, "panic fields don't match");
	ASSERT_EQUALS( inputObj.panicCapture, updatedSettings->panicCapture, "panicCapture fields don't match");
	ASSERT_EQUALS( inputObj.panicDump, updatedSettings->panicDump, "panicDump fields don't match");
	ASSERT_EQUALS( inputObj.error, updatedSettings->error, "error fields don't match");
	ASSERT_EQUALS( inputObj.errorCapture, updatedSettings->errorCapture, "errorCapture fields don't match");
	ASSERT_EQUALS( inputObj.errorDump, updatedSettings->errorDump, "errorDump fields don't match");
	ASSERT_EQUALS( inputObj.warn, updatedSettings->warn, "warn fields don't match");
	ASSERT_EQUALS( inputObj.warnCapture, updatedSettings->warnCapture, "warnCapture fields don't match");
	ASSERT_EQUALS( inputObj.warnDump, updatedSettings->warnDump, "warnDump fields don't match");
	ASSERT_EQUALS( inputObj.info, updatedSettings->info, "info fields don't match");
	ASSERT_EQUALS( inputObj.infoCapture, updatedSettings->infoCapture, "infoCapture fields don't match");
	ASSERT_EQUALS( inputObj.infoDump, updatedSettings->infoDump, "infoDump fields don't match");
	ASSERT_EQUALS( inputObj.debug, updatedSettings->debug, "debug fields don't match");
	ASSERT_EQUALS( inputObj.debugCapture, updatedSettings->debugCapture, "debugCapture fields don't match");
	ASSERT_EQUALS( inputObj.debugDump, updatedSettings->debugDump, "debugDump fields don't match");
	ASSERT_EQUALS( inputObj.trace, updatedSettings->trace, "trace fields don't match");
	ASSERT_EQUALS( inputObj.traceCapture, updatedSettings->traceCapture, "traceCapture fields don't match");
	ASSERT_EQUALS( inputObj.traceDump, updatedSettings->traceDump, "traceDump fields don't match");
	ASSERT_EQUALS( inputObj.sql, updatedSettings->sql, "sql fields don't match");
	ASSERT_EQUALS( inputObj.sqlCapture, updatedSettings->sqlCapture, "sqlCapture fields don't match");
	ASSERT_EQUALS( inputObj.sqlDump, updatedSettings->sqlDump, "sqlDump fields don't match");
	
	// Now put it back the way it was:
	m_api->UpdateLogSettings( *origSettings );

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

/** This test will call the /logic/util/UpdateLogSettings with an invalid payload and check the response
  * that is received.
  */
void ApiTest_logic_util_UpdateLogSettings_CallWithInvalidPayload()
{
	BEGIN_TEST_METHOD( "ApiTest_logic_util_UpdateLogSettings_CallWithInvalidPayload" )

	// Api /logic/util/UpdateLogSettings requires an object of type LogSettings as input.
	LogSettings inputObj;

	try {
		xmlDocPtr resp;
		resp = m_api->UpdateLogSettings(inputObj);
		ASSERT_TRUE(false, "API Call should have failed.");
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
