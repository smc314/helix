/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef Jvm_H
#define Jvm_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "ActionClass.h"
using namespace Helix::Glob;

#include <jni.h>

namespace Helix {
namespace Glob {

/** This class contains the implementation for loading a JVM and executing methods
 *  inside the JVM that has been loaded.
 */
class Jvm
{
	public:
		/// Standard Constructor
		Jvm(twine jvmName);

		/// Standard Copy Constructor
		Jvm(const Jvm& c);

		/// Standard Copy operator
		Jvm& operator=(const Jvm& c);

		/// Standard Destructor
		virtual ~Jvm();
	
	protected:

		/** Handles the loading of the JVM based on our current classpath, libpath,
		 * location and options.
		 */
		void loadJvm();

		/** Handles setting appropriate defaults for classpath, libpath, location,
		 * and options.  These defaults should allow us to load our bundled JVM without
		 * any overrides to our options.
		 */
		void setDefaults();

	private:

		twine m_jvmName;
		twine m_jvmClasspath;
		twine m_jvmLibpath;
		twine m_jvmLocation;
		twine m_jvmOptions;

		JavaVM* m_jvm;
		JNIEnv* m_env;
};

}} // End of Helix::Glob Namespace definition

#endif // Jvm_H Defined
