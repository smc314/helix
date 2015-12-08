/* ***************************************************************************

   Copyright (c): 2008 - 2015 Hericus Software LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

/* ***************************************************************************
	This is a testing application that is used to test both the client UI
	and the server HTTP Api's.  Test configurations are external config 
	files and drive the tests that are defined.  Command line arguments 
	indicate which tests will be executed.
*************************************************************************** */

/* ***************************************************************************
   Output log messages look use a series of 2 character prefix symbols to
   indicate what the log messages pertain to.  Each of the different types
   can be enabled/disabled for the test run.

>> TestName - host:port
++ Optional Details about what we are doing
++ as we do it.
!! Any Errors that we see, or failed assertions about the api tests
!! will have these lines reported.
<< TestName - Success - Duration - Tests Total (123) Success (123) Failure (0)
** Total (123) Success (123) Failure (0)\n",

*************************************************************************** */

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdexcept>

#include <XmlHelpers.h>
#include <AnException.h>
#include <dptr.h>
using namespace SLib;

#include "TestCache.h"
#include "TestStats.h"
#include "TestLog.h"
#include "DynamicTest.h"
#include "HTest.h"
using namespace Helix::Test;

// Our Common testing utilities
const char* usage = 
	"Usage: %s [options]\n"
	"\twhere [options] include the following:\n"
	"--log-all=[true|false]            Turn on/off all of our logging. False by default.\n"
	"--log-test=[true|false]           Turn on/off test start/finish logging.  True by default.\n"
	"--log-steps=[true|false]          Turn on/off step by step logging.  False by default.\n"
	"--log-err=[true|false]            Turn on/off error logging.  True by default.\n"
	"\n"
	"--dry=[true|false]                Indicates whether we are in a dry-run.  False by default.\n"
	"                                  If true, we'll only print out the tests that would be run, but\n"
	"                                  not actually execute them.\n"
	"\n"
	"--test=apiname                    Use to tell us which api test to include.  We'll take this\n"
	"                                  string and match it to the full api path's and any api path\n"
	"                                  that includes this string will be included in the test run.\n"
	"\n";

/** This is the method we use to print our total's information.
  */
void PrintTotal( );

void ParseArgs(int argc, char** argv);
void InitSettings(void);
void LoadConfig(void);
void LoadInclude( const twine& fileName );
void WalkDynamicTests(void);
bool MatchesFunctionalArea(DynamicTest* test);
bool MatchesTestName(DynamicTest* test);
bool ExecuteTestDependencies(DynamicTest* test);
DynamicTest* FindTestThatProvides(const twine& requirement);
bool IsCapabilitySatisfied(const twine& requirement);
void AddCapabilitiesSatisfied(DynamicTest* test);
bool ExecuteTest( DynamicTest* test );

vector <DynamicTest*> dynamicTests;
vector <twine> FunctionalAreas;
vector <twine> TargetTestList;
vector <twine> CapabilitiesSatisfied;
bool StopOnFailure;

int main(int argc, char** argv)
{
	InitSettings();
	ParseArgs(argc, argv);
	LoadConfig();
	WalkDynamicTests();

	PrintTotal( ); // print the overall totals

	return EXIT_SUCCESS;
}

void InitSettings(void)
{
	TestCache& tc = TestCache::getInstance();

	tc.AddCacheItem( "TestHost", "localhost");
	tc.AddCacheItem( "TestPort", "8082");
	tc.AddCacheItem( "TestUser", "");
	tc.AddCacheItem( "TestPass", "");
	tc.AddCacheItem( "TestApiName", "");
	tc.AddCacheItem( "LogAll", "false");
	tc.AddCacheItem( "LogTest", "true");
	tc.AddCacheItem( "LogSteps", "false");
	tc.AddCacheItem( "LogError", "true");
	tc.AddCacheItem( "LogHtml", "false");
	tc.AddCacheItem( "DryRun", "false");
	tc.AddCacheItem( "ConfigFile", "SmokeTest.xml");
}

void ParseArgs(int argc, char** argv)
{
	TestCache& tc = TestCache::getInstance();

	for(int i = 1; i < argc; i++){
		twine arg( argv[i] );
		vector<twine> argSplits = arg.split("=");

		if(arg.find("--log-all=") == 0){
			tc.AddCacheItem("LogAll", argSplits[1] );
		} else if(arg.find("--log-test=") == 0){
			tc.AddCacheItem("LogTest", argSplits[1] );
		} else if(arg.find("--log-steps=") == 0){
			tc.AddCacheItem("LogSteps", argSplits[1] );
		} else if(arg.find("--log-err=") == 0){
			tc.AddCacheItem("LogError", argSplits[1] );
		} else if(arg.find("--dry=") == 0){
			tc.AddCacheItem("DryRun", argSplits[1] );
		} else if(arg.find("--test=") == 0){
			tc.AddCacheItem("TestApiName", argSplits[1] );
		} else if(arg.find("--host=") == 0){
			tc.AddCacheItem("TestHost", argSplits[1] );
		} else if(arg.find("--port=") == 0){
			tc.AddCacheItem("TestPort", argSplits[1] );
		} else if(arg.find("--user=") == 0){
			tc.AddCacheItem("TestUser", argSplits[1] );
		} else if(arg.find("--pass=") == 0){
			tc.AddCacheItem("TestPass", argSplits[1] );
		} else if(argSplits.size() > 1){
			tc.AddCacheItem(argSplits[0], argSplits[1] );
		} else {
			printf("Unknown argument \"%s\"\n", arg.c_str() );
			printf(usage, argv[0]);
			exit(EXIT_FAILURE);
		}
	}
}

void PrintTotal( )
{
	TestStats& ts = TestStats::getInstance();

	printf("** %s.%s Total (%d) Success (%d) Failure (%d)\n",
		TestCache::get("TestHost")(), TestCache::get("TestPort")(),
		ts.TestCount, ts.TestSuccess, ts.TestFailure
	);	
}

void LoadConfig(void)
{
	xmlInitParser();
	twine configFile = TestCache::get( "ConfigFile" );
	LoadInclude( configFile );	
}

void LoadInclude( const twine& fileName )
{
	TestCache& tc = TestCache::getInstance();

	twine loadFile;
	if(fileName.startsWith("./") || fileName.startsWith("../") || fileName.startsWith("/") ){
		// That's fine, don't change it
		loadFile = fileName;
	} else {
		// Insert the ./config prefix
		loadFile = "./config/" + fileName;
	}
	//TestLog::LogError("Loading Config: " + loadFile);

	xmlDocPtr doc = xmlParseFile( loadFile() );
	if(!doc){
		TestLog::LogError( "Error loading config file: " + loadFile );
		return;
	}

	xmlNodePtr root = xmlDocGetRootElement( doc );
	if(strncmp( (const char*)(root->name), "HTest", 5) != 0){
		TestLog::LogError( "Config file: " + loadFile + " is not an HTest document.");
		xmlFreeDoc( doc );
		return;
	}

	// Walk the list of settings:
	vector<xmlNodePtr> settings = XmlHelpers::FindChildren( root, "Setting" );
	for(size_t i = 0; i < settings.size(); i++){
		twine name( settings[i], "name" );
		twine value( settings[i], "value" );
		tc.AddCacheItem( name, value );
	}

	// Walk the list of includes:
	vector<xmlNodePtr> includes = XmlHelpers::FindChildren( root, "Include" );
	for(size_t i = 0; i < includes.size(); i++){
		twine includeFileName( includes[i], "fileName" );
		LoadInclude( tc.ReplaceVars( includeFileName ) );
	}

	// Walk the list of dynamic tests:
	vector<xmlNodePtr> testGroups = XmlHelpers::FindChildren( root, "DynamicTests" );
	for(size_t i = 0; i < testGroups.size(); i++){
		// Walk each test in the group and load it
		for(xmlNodePtr test = testGroups[i]->xmlChildrenNode; test != NULL; test = test->next){
			if(test->type == XML_ELEMENT_NODE){
				DynamicTest* dt = new DynamicTest( test );
				dynamicTests.push_back( dt );
			}
		}
	}
}

void WalkDynamicTests(void)
{
	TestCache& tc = TestCache::getInstance();
	StopOnFailure = false;
	if(tc.HasCacheItem("Area")){
		FunctionalAreas = tc.get("Area").split(",");
	}
	if(tc.HasCacheItem("Test")){
		TargetTestList = tc.get("Test").split(",");
	}
	for(size_t i = 0; i < dynamicTests.size(); i++){
		DynamicTest* test = dynamicTests[i];
		//printf("Looking at test: %s\n", test->Name()());
		if(MatchesFunctionalArea( test ) || MatchesTestName( test )){
			if(ExecuteTestDependencies( test )){
				ExecuteTest( test );
			}
		}
	}
}

bool MatchesFunctionalArea(DynamicTest* test)
{
	if(FunctionalAreas.size() == 0 && TargetTestList.size() == 0){
		//printf("FunctionalAreas size is zero\n");
		return true; // everything matches
	}
	for(size_t i = 0; i < FunctionalAreas.size(); i++){
		for(size_t j = 0; j < test->FunctionalAreas().size(); j++){
			if( FunctionalAreas[i] == test->FunctionalAreas()[j] ){
				return true; // Matches one of the requested functional areas.
			}
		}
	}
	return false; // doesn't match any functional area requested.
}

bool MatchesTestName(DynamicTest* test)
{
	if(FunctionalAreas.size() == 0 && TargetTestList.size() == 0){
		return true; // everything matches
	}
	for(size_t i = 0; i < TargetTestList.size(); i++){
		if( test->Name().startsWith( TargetTestList[i] ) ){
			return true; // Matches one of the requested test names
		}
	}
	return false; // doesn't match any test name requested.
}

bool ExecuteTestDependencies(DynamicTest* test)
{
	//printf("Checking test dependencies for test: %s\n", test->Name()() );
	// Run through the list of requirements for this test, and find the first
	// test in our list that provides that capability
	for(size_t i = 0; i < test->Requires().size(); i++){
		const twine& requirement = test->Requires()[i];
		// Check to see if the requirement is satisfied
		if( IsCapabilitySatisfied( requirement ) ){
			continue; // already handled this one.
		}

		// If not then find a test that provides this and execute it:
		DynamicTest* provider = FindTestThatProvides( requirement );
		if(provider != NULL){
			// Execute the providers dependencies
			if(ExecuteTestDependencies( provider )){
				// Execute the provider itself
				return ExecuteTest( provider );
			} else {
				return false;
			}
		} else {
			printf( "No test provides capability %s required by %s\n", requirement(), test->Name()() );
			return false;
		}
	}
	return true;
}

DynamicTest* FindTestThatProvides(const twine& requirement)
{
	//printf("Looking for a test that provides: %s\n", requirement() );
	for(size_t i = 0; i < dynamicTests.size(); i++){
		DynamicTest* test = dynamicTests[i];
		for(size_t j = 0; j < test->Provides().size(); j++){
			if( test->Provides()[j] == requirement ){
				//printf("Found test %s that provides %s\n", test->Name()(), requirement() );
				return test;
			}
		}
	}
	return NULL; // Didn't find a test that provides the requested capability
}

bool IsCapabilitySatisfied(const twine& requirement)
{
	//printf("Checking to see if capability: %s is satisfied\n", requirement() );
	for(size_t i = 0; i < CapabilitiesSatisfied.size(); i++ ){
		if(requirement == CapabilitiesSatisfied[i]){
			return true;
		}
	}
	return false; // Capability has not yet been satisfied
}

void AddCapabilitiesSatisfied(DynamicTest* test)
{
	for(size_t i = 0; i < test->Provides().size(); i++){
		CapabilitiesSatisfied.push_back( test->Provides()[i] );
	}
}

bool ExecuteTest( DynamicTest* test )
{
	if(StopOnFailure){
		return false; // Stop executing any tests at this point
	}

	TestStats& ts = TestStats::getInstance();
	TestCache& tc = TestCache::getInstance();
	ts.TestCount++;
	test->Describe();
	if(tc.getBool("DryRun")){
		// Don't execute the test, just log the header and indicate that the capability has been satisfied
		ts.TestSuccess++;
		AddCapabilitiesSatisfied( test );
		return true;
	}

	try {
		dptr<DynamicTest> executor;
		executor = DynamicTestFactory::createInstance(test->Type(), test->Node() );
		if(executor == NULL){
			ts.TestFailure++;
			return false;
		}
		executor->Passed(false);
		executor->Run();
		if(executor->Passed()){
			if(executor->ShouldWork()){
				ts.TestSuccess++;
				AddCapabilitiesSatisfied( test );
				return true;
			} else {
				ts.TestFailure++;
				return false;
			}
		} else {
			if(executor->ShouldWork()){
				ts.TestFailure++;
				return false;
			} else {
				ts.TestSuccess++;
				AddCapabilitiesSatisfied( test );
				return true;
			}
		}
	} catch (AnException& e){
		return false;
	}

}
