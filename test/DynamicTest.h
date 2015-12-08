/* ****************************************************************************

   Copyright (c): 2015 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

**************************************************************************** */

#ifndef DYNAMICTEST_H
#define DYNAMICTEST_H

#include <map>
#include <vector>
using namespace std;

#include <twine.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

namespace Helix {
namespace Test {

/**
 * This class defines the base functionality included in every dynamic test in our
 * system.
 */
class DynamicTest
{
	public:
		
		/** Standard constructor to create an empty dynamic test.
		 */
		DynamicTest();

		/** Constructor that will read our configuration from the given XML Node.
		 */
		DynamicTest(xmlNodePtr testNode);

		/// Standard Destructor
		virtual ~DynamicTest();

		/// Retrieves the test name
		const twine& Name();

		/// Retrieves the test type
		const twine& Type();

		/// Retrieves the original xml node used to create this test
		xmlNodePtr Node();

		/// Writes a message to the console and our internal log
		void WriteLine(const twine& message);

		/// Writes a description of this test out to the log
		void Describe();

		/// Returns the list of functional areas that this test addresses
		const vector<twine>& FunctionalAreas();

		/// Returns the list of test capabilities that this test provides
		const vector<twine>& Provides();

		/// Returns the list of test capabilities that this test requires
		const vector<twine>& Requires();

		/// Sets the Passed status of this test
		void Passed(bool tf);

		/// Gets the Passed status of this test
		bool Passed();

		/// Indicates whether this test is expected to work or not
		bool ShouldWork();

		/// This method will execute the test itself.  Must be implemented by subclasses.
		virtual void Run();

	protected:

		/// This is our list of functional areas that this test covers.
		vector<twine> m_functionalAreas;

		/// This is our list of capabilities that this test provides
		vector<twine> m_provides;

		/// This is our list of capabilities that this test requires.
		vector<twine> m_requires;

		/// Whether this test has passed
		bool m_testPassed;

		/// Whether this test expects an error or not
		bool m_shouldWork;

		/// Whether this test should stop the rest of the tests on failure
		bool m_stopOnFailure;

		/// The name of this test
		twine m_name;

		/// The type of this test - should match the class implementing this test
		twine m_type;

		/// Our original test configuration xml node
		xmlNodePtr m_testNode;


}; // End DynamicTest class

// These are used so that we can register and dynamically create instances of DynamicTest
// classes at runtime on-demand.
template<typename T> DynamicTest* createT(xmlNodePtr node) { return new T(node); }
typedef std::map<twine, DynamicTest*(*)(xmlNodePtr) > map_type;

class DynamicTestFactory
{
	public:
		static DynamicTest* createInstance(twine className, xmlNodePtr node);

	protected:
		static map_type* getMap();
};

template<typename T>
class DynamicTestRegister : DynamicTestFactory
{
	public:
		DynamicTestRegister(twine className) {
			(*(getMap()))[className] = &createT<T>;
		}

};


} } // End namespace stack

#endif // DYNAMICTEST_H Defined
