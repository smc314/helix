/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "Jvm.h"
using namespace Helix::Glob;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

typedef jint (JNICALL *CreateVM)(JavaVM**, void**, JavaVMInitArgs*);
typedef jint (JNICALL *GetJVMs)(JavaVM**, jsize, jsize*);

Jvm::Jvm(twine jvmName) : m_jvmName(jvmName)
{
	EnEx ee(FL, "Jvm::Jvm(xmlNodePtr action)");

	m_jvm = NULL;
	m_env = NULL;
	
	setDefaults();
	loadJvm();
}

Jvm::Jvm(const Jvm& c)
{
	EnEx ee(FL, "Jvm::Jvm(const Jvm& c)");

}

Jvm& Jvm::operator=(const Jvm& c)
{
	EnEx ee(FL, "Jvm::operator=(const Jvm& c)");

	return *this;
}

Jvm::~Jvm()
{
	EnEx ee(FL, "Jvm::~Jvm()");

	if(m_jvm != NULL){
		m_jvm->DestroyJavaVM();
		m_jvm = NULL;
	}

}

void Jvm::loadJvm()
{
	EnEx ee(FL, "Jvm::loadJvm()");

	
	JavaVMInitArgs vm_args;
	JavaVMOption options[10];
	jint nargs;
	jint res;
	jsize numvms;
	JavaVM *jvmbuf;


	void *lib = NULL;

	CreateVM CreateJavaVM = NULL;
	GetJVMs GetCreatedJavaVMs = NULL;
	
	DEBUG(FL, "Setting the JVM options\n");
	options[0].optionString = (char*)m_jvmClasspath();
	options[1].optionString = (char*)m_jvmLibpath();
	options[2].optionString = (char*)"-verbose:jni"; // print JNI messages 
	nargs = 3; // nargs is always at least 2;

	// Check for other arguments
	// FIXME: do this.

	vm_args.version = JNI_VERSION_1_2;
	vm_args.options = options;
	vm_args.nOptions = nargs;
	vm_args.ignoreUnrecognized = JNI_TRUE;

#ifdef _WIN32
	lib = LoadLibrary( m_jvmLocation() );
	if(lib){
		DEBUG(FL, "JVM (%s) loaded.  lib value: %x", m_jvmLocation(), lib);
	} else {
		throw AnException(0, FL, "JVM (%s) failed to load.", m_jvmLocation());
	}

	CreateJavaVM = (CreateVM) GetProcAddress((HMODULE)lib, "JNI_CreateJavaVM");
	if(CreateJavaVM){
		DEBUG(FL, "JVM Entry Point JNI_CreateJavaVM found.");
	} else {
		throw AnException(0, FL, "JVM (%s) does not have entry point JNI_CreateJavaVM", m_jvmLocation());
	}

	GetCreatedJavaVMs = (GetJVMs) GetProcAddress((HMODULE)lib, "JNI_GetCreatedJavaVMs");
	if(GetCreatedJavaVMs){
		DEBUG(FL, "JVM Entry Point JNI_GetCreatedJavaVMs found.");
	} else {
		throw AnException(0, FL, "JVM (%s) does not have entry point JNI_GetCreatedJavaVMs", m_jvmLocation());
	}

	GetCreatedJavaVMs(&jvmbuf, 1, &numvms);
	DEBUG(FL, "JVM's running prior to starting ours: %d", numvms);

	INFO(FL, "Creating our JVM from (%s)", m_jvmLocation() );
	res = CreateJavaVM(&m_jvm, (void**)&m_env, &vm_args);
	if(res < 0){
		throw AnException(0, FL, "Bad result when creating a JVM: %d", res);
	}

	GetCreatedJavaVMs(&jvmbuf, 1, &numvms);
	DEBUG(FL, "JVM's running after starting ours: %d", numvms);
#else


#endif
}

void Jvm::setDefaults()
{
	EnEx ee(FL, "Jvm::setDefaults()");

	m_jvmClasspath = "-Djava.class.path=.";
	m_jvmLibpath = "-Djava.library.path=./jre/bin/";
	m_jvmLocation = "./jre/bin/client/jvm.dll";
	m_jvmOptions = "";

}
