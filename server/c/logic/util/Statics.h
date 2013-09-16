/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef Statics_H
#define Statics_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

namespace Helix {
namespace Logic {
namespace util {

/** This class holds a number of static methods that we use throughout the hub logic 
 * classes.
 */
class Statics
{
	public:
		/** This method handles replacing session variables in the given string.  The
		 * string should have tokens in the form of ${VarName} embedded within it, and
		 * we'll parse them out, look up "VarName" in our current session settings and,
		 * if found, replace the token in the string with the value from the session settings.
		 */
		static void ReplaceSessionVars(IOConn& ioc, twine& target);

		/** This method will convert the given string to either 1 or 0.  If the given string
		 * starts with either a Y or a y, then it will be converted into a 1.  Otherwise it will
		 * be converted into a 0.
		 */
		static void ConvertToOneZero(twine& str);

		/// If the input is "1", then reset the twine to "YES", otherwize to "NO"
		static void ConvertToYesNo( twine& flag );
		
		/// If the input is "1", then reset the twine to "Y", otherwize to "N"
		static void ConvertToYN( twine& flag );

		/// If the input is zero length, then reset the twine to "NULL", otherwize leave as is.
		static void ConvertToNULL( twine& flag );

		/// If the input is zero length, then reset the twine to "0", otherwize leave as is.
		static void ConvertToZero( twine& flag );

		/// If the input is "On" or "ON", then convert to "1", otherwise to "0".
		static void ConvertOnOffToOneZero(twine& str);

		/// If the input is "1" then convert to "ON", otherwise to "OFF"
		static void ConvertToOnOff( twine& flag );

		/// Implements our password scrambling method.
		static twine encryptPwd( twine& pass, int len);

		/// Implements our password un-scrambling method.
		static twine decryptPwd( twine& pass );

		/// This password descrambling is used by our CSA methods
		static twine decryptCSAPwd( twine& pass );

		/// Converts an IP address as an int into a string in dotted quad notation
		static twine convertIP( unsigned int ipAddr );

		/// Ensures that a given subdirectory exists under the current working directory
		static void ensureSubDir( const twine& dirName );

		/// Answers the question of whether we are home-base or not.
		static bool areWeHomeBase();

	private:
		/// Standard Constructor is private to prevent use.
		Statics() {}

		/// Standard Copy Constructor is private to prevent use.
		Statics(const Statics& c) {}

		/// Standard Copy operator is private to prevent use.
		Statics& operator=(const Statics& c) { return *this; }

		/// Standard Destructor is private to prevent use.
		virtual ~Statics() {}
};

}}} // End of Namespace definitions

#endif // Statics_H Defined
