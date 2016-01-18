/* ***************************************************************************

	Copyright: 2013 Hericus Software, LLC

	License: The MIT License (MIT)

	Authors: Steven M. Cherry

*************************************************************************** */

#include <AnException.h>
#include <Log.h>
#include <xmlinc.h>
#include <XmlHelpers.h>
#include <twine.h>
#include <File.h>
using namespace SLib;

#include <vector>
using namespace std;

twine m_platform;
twine m_currentPackage;
twine m_currentFile;

void findAllSLFolders(twine start);
void createLogicMakefile( const twine& targetFolder ) ;
void createWin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);
void createWin32Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);
void createLin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);

void createGlobMakefile( const twine& targetFolder ) ;
void createGlobWin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);
void createGlobWin32Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);
void createGlobLin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);

void createClientMakefile( const twine& targetFolder ) ;
void createClientWin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);
void createClientWin32Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);
void createClientLin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder);

twine win64LFlags = "-machine:x64 -subsystem:console";
twine win64CFlags = "-c -Zp8 -EHsc -O2 -D_WIN64 -DWIN64 -D_AMD64_=1 -D__64BIT__ -DWIN32 -D_MT -D_DLL -DLINT_ARGS -MP8 -MD -W3 -D \"_CRT_SECURE_NO_DEPRECATE\" -D \"_CRT_NON_CONFORMING_SWPRINTFS\" -D CS_NO_LARGE_IDENTIFIERS -I \"$(3PL)/include\" ";

// Debug flags are -debug for linker and -Od -Zi for compiler.
twine win32LFlags = "-machine:i386 -subsystem:console -debug";
twine win32CFlags = "-c -Od -Zi -Zp8 -EHsc -DWIN32 -D_MT -D_DLL -DLINT_ARGS -D_X86_=1 -MP8 -MD -W3 -D \"_CRT_SECURE_NO_DEPRECATE\" -D \"_CRT_NON_CONFORMING_SWPRINTFS\" -D CS_NO_LARGE_IDENTIFIERS -D _USE_32BIT_TIME_T -I \"$(3PL)/include\" ";

twine lin64LFlags = "-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -luuid -lz -lodbc -L$(3PL)/slib/lib -lSLib";
twine mac64LFlags = "-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -lz -lodbc -L$(3PL)/slib/lib -lSLib";
twine lin64CFlags = "-g -Wall -D_REENTRANT -fPIC -O2 -rdynamic -I$(OPENSSLDIR)/include -I/usr/include -I/usr/include/libxml2 -I \"$(3PL)/slib/include\" ";

bool doJni = true;

int main (int argc, char** argv)
{

	if(argc > 1){
		twine argv1 = argv[1];
		if(argv1.startsWith( "-jni=" )){
			if(argv1.endsWith( "true" )){
				doJni = true;
			} else {
				doJni = false;
			}
		}
	}

	printf("============================================================================\n");
#ifdef _WIN32
#	ifdef _X86_
	m_platform = "WIN32_x86";
#	else
	m_platform = "WIN32_x64";
#	endif
#else
	m_platform = "LINUX_x64";
#endif
	printf("Generating src/logic makefiles based on a %s platform.\n", m_platform());
	printf("============================================================================\n");

	findAllSLFolders("../logic");

	try {
		createGlobMakefile("../glob");
		createClientMakefile("../client");
	} catch(AnException& e){
		printf("%s\n", e.Msg());
	}

	return 0;
}

void findAllSLFolders(twine start)
{
	// Find all folders under the given start:
	vector<twine> folders = File::listFolders(start);
	for(size_t i = 0; i < folders.size(); i++){
		if(folders[i] != "." && folders[i] != ".."){
			twine targetFolder = start + "/" + folders[i];
			// Create the makefile
			createLogicMakefile( targetFolder );

			// Now process all sub-folders
			findAllSLFolders( targetFolder );
		}
	}

}

void createLogicMakefile( const twine& targetFolder ) 
{
	// check all of the normal files:
	vector<twine> allFiles = File::listFiles(targetFolder);
	vector<twine> objFiles;
	for(size_t i = 0; i < allFiles.size(); i++){
		if( allFiles[i].endsWith(twine(".cpp")) || allFiles[i].endsWith(twine(".c")) ){
			objFiles.push_back( allFiles[i] );
		}
	}
	
	// Find all folders under the given start:
	vector<twine> folders = File::listFolders(targetFolder);


	if(m_platform == "WIN32_x86"){
		createWin32Makefile( objFiles, folders, targetFolder);
	} else if(m_platform == "WIN32_x64"){
		createWin64Makefile( objFiles, folders, targetFolder);
	} else if(m_platform == "LINUX_x64"){
		createLin64Makefile( objFiles, folders, targetFolder);
	}
}

void createWin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{

	twine tmpFolder = targetFolder;
	vector<twine> pathElements = tmpFolder.split("/");
	twine extraDotDot;
	for(size_t i = 4; i < pathElements.size(); i++){
		extraDotDot.append( "..\\" );
	}


	twine output;
	output.append(
		"#\n"
		"# This is a Win64 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=..\\..\\..\\..\\..\\" + extraDotDot + "3rdParty\n"
		"SOCKET_LIB=ws2_32.lib odbc32.lib rpcrt4.lib\n"
		"MINGW_BINDIR=c:/Program Files/Git/mingw64/bin\n"
		"GIT_USRBIN=c:/Program Files/Git/usr/bin\n"
		"TOUCH=\"$(GIT_USRBIN)/touch.exe\"\n"
		"\n"
		"CFLAGS=" + win64CFlags +
		"-I ..\\..\\" + extraDotDot + "glob "
		"-I ..\\..\\" + extraDotDot + "client "
		"-I ..\\" + extraDotDot + "util "
		"-I ..\\" + extraDotDot + "admin "
		"-I ..\\" + extraDotDot + "dev "
		"-I ..\\" + extraDotDot + "test "
		"\n"
		"LFLAGS=" + win64LFlags + "\n"
		"LLIBS=$(3PL)\\lib\\libeay32.lib $(3PL)\\lib\\ssleay32.lib \\\n"
		"\t$(3PL)\\lib\\libxml2.lib $(3PL)\\lib\\libSLib.lib \\\n"
		"\t$(3PL)\\lib\\zdll.lib $(SOCKET_LIB)"
		"\n"
		".cpp.obj:\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		".c.obj:\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		vector<twine> splits = objFiles[i].split(".");
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".obj\n" );
		} else {
			output.append( "\t" + splits[0] + ".obj \\\n" );
		}
	}

	twine slibName = "libhelix/" + targetFolder.substr(3);
	slibName.replace('/', '.');
	twine slib2Name; slib2Name = slibName;
	slibName.append(".dll");
	slib2Name.append(".lib");

	output.append(
		"\n"
		"all: $(DOTOH)\n"
	);
	if(objFiles.size() > 0){
		if(slibName.endsWith(".util.dll") || slibName.endsWith(".admin.dll")){
			// Don't create a shared library for util.so or admin.so it's rolled into glob.dll
		} else {
			output.append(
				"\tlink.exe $(LFLAGS) /OUT:" + slibName + " /DLL $(DOTOH) $(LLIBS) ..\\..\\" + extraDotDot + "bin\\libhelix.glob.lib\n"
				"\tcopy " + slibName + " ..\\..\\" + extraDotDot + "bin\n"
				"\tcopy " + slib2Name + " ..\\..\\" + extraDotDot + "bin\n"
			);
		}
	}
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && nmake -f Makefile all\n"
			);
		}
	}

	output.append(
		"\n"
		"clean:\n"
		"\tdel /Q /S $(DOTOH) *.obj *.pch *.lib *.exp *.exe.manifest *.exe *.dll *.dll.manifest\n"
		"\t$(TOUCH) -c *.sql.xml\n"
	);
	if(objFiles.size() > 0){
		output.append(
			"\tdel /Q /S ..\\..\\" + extraDotDot + "bin\\" + slibName + "\n"
			"\tdel /Q /S ..\\..\\" + extraDotDot + "bin\\" + slib2Name + "\n"
		);
	}
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && nmake -f Makefile clean\n"
			);
		}
	}

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createWin32Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{

	twine tmpFolder = targetFolder;
	vector<twine> pathElements = tmpFolder.split("/");
	twine extraDotDot;
	for(size_t i = 4; i < pathElements.size(); i++){
		extraDotDot.append( "../" );
	}


	twine output;
	output.append(
		"#\n"
		"# This is a Win32 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../../" + extraDotDot + "3rdParty\n"
		"SOCKET_LIB=ws2_32.lib odbc32.lib rpcrt4.lib\n"
		"GMAKE=c:/cygwin/bin/make.exe -j 8\n"
		"\n"
		"CFLAGS=" + win32CFlags +
		"-I ../../" + extraDotDot + "glob "
		"-I ../../" + extraDotDot + "client "
		"-I ../" + extraDotDot + "util "
		"-I ../" + extraDotDot + "admin "
		"-I ../" + extraDotDot + "dev "
		"-I ../" + extraDotDot + "test "
		"\n"
		"\n"
		"%.obj: %.cpp\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"%.obj: %.c\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		vector<twine> splits = objFiles[i].split(".");
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".obj\n" );
		} else {
			output.append( "\t" + splits[0] + ".obj \\\n" );
		}
	}

	output.append(
		"\n"
		"all: $(DOTOH)\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile all\n"
			);
		}
	}

	output.append(
		"\n"
		"clean:\n"
		"\trm -f $(DOTOH) *.obj *.pch *.lib *.exp *.exe.manifest *.exe *.dll *.dll.manifest\n"
		"\ttouch -c *.sql.xml\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile clean\n"
			);
		}
	}

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createLin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{

	twine tmpFolder = targetFolder;
	vector<twine> pathElements = tmpFolder.split("/");
	twine extraDotDot;
	for(size_t i = 3; i < pathElements.size(); i++){
		extraDotDot.append( "../" );
	}


	twine output;
	output.append(
		"#\n"
		"# This is a Lin64 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../../" + extraDotDot + "3rdParty\n"
		"GMAKE=make -j 8\n"
		"\n"
		"ifeq ($(UNAME),Linux)\n"
		"\tOPENSSLDIR=/usr\n"
		"else\n"
		"\tOPENSSLDIR=/usr/local/opt/openssl\n"
		"endif\n"
		"\n"
		"CFLAGS=" + lin64CFlags +
		"-I ../../" + extraDotDot + "glob "
		"-I ../../" + extraDotDot + "client "
		"-I ../" + extraDotDot + "util "
		"-I ../" + extraDotDot + "admin "
		"-I ../" + extraDotDot + "dev "
		"-I ../" + extraDotDot + "test "
		"\n"
		"\n"
		"ifeq ($(UNAME),Linux)\n"
		"\tLFLAGS=" + lin64LFlags + "\n"
		"else\n"
		"\tLFLAGS=" + mac64LFlags + "\n"
		"endif\n"
		"\n"
		"\n"
		"%.o: %.cpp\n"
		"\tg++ $(CFLAGS) -c $< -o $@\n"
		"\n"
		"%.o: %.c\n"
		"\tg++ $(CFLAGS) -c $< -o $@\n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		vector<twine> splits = objFiles[i].split(".");
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".o\n" );
		} else {
			output.append( "\t" + splits[0] + ".o \\\n" );
		}
	}

	twine slibName = "libhelix/" + targetFolder.substr(3);
	slibName.replace('/', '.');
	slibName.append( ".so" );

	output.append(
		"\n"
		"all: $(DOTOH)\n"
	);
	if(objFiles.size() > 0){
		if(slibName.endsWith(".util.so") || slibName.endsWith(".admin.so")){
			// Don't create a shared library for util.so - it's rolled up into glob
		} else {
			output.append(
				"\tg++ -shared -o " + slibName + " $(DOTOH) $(LFLAGS) -L../../" +
				extraDotDot + "bin -lhelix.glob\n" +
				"\tcp " + slibName + " ../../" + extraDotDot + "bin/\n"
			);
		}
	}
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile all\n"
			);
		}
	}

	output.append(
		"\n"
		"clean:\n"
		"\trm -f $(DOTOH) *.o *.obj core *.so\n"
		"\ttouch -c *.sql.xml\n"
	);
	if(objFiles.size() > 0){
		output.append(
			"\trm -f ../../" + extraDotDot + "bin/" + slibName + "\n"
		);
	}
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile clean\n"
			);
		}
	}

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createGlobMakefile( const twine& targetFolder ) 
{
	// check all of the normal files:
	vector<twine> allFiles = File::listFiles(targetFolder);
	vector<twine> objFiles;
	for(size_t i = 0; i < allFiles.size(); i++){
		if( allFiles[i].endsWith(twine(".cpp")) || allFiles[i].endsWith(twine(".c")) ){
			objFiles.push_back( allFiles[i] );
		}
	}
	
	// Find all folders under the given start:
	vector<twine> folders = File::listFolders(targetFolder);


	if(m_platform == "WIN32_x86"){
		createGlobWin32Makefile( objFiles, folders, targetFolder);
	} else if(m_platform == "WIN32_x64"){
		createGlobWin64Makefile( objFiles, folders, targetFolder);
	} else if(m_platform == "LINUX_x64"){
		createGlobLin64Makefile( objFiles, folders, targetFolder);
	}
}

void createGlobWin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{
	twine output;
	output.append(
		"#\n"
		"# This is a Win64 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../3rdParty\n"
		"SOCKET_LIB=ws2_32.lib odbc32.lib rpcrt4.lib\n"
		"GMAKE=c:/cygwin/bin/make.exe -j 8\n"
		"\n"
		"CFLAGS=" + win64CFlags + " -I ../logic/util -I ../logic/admin\n"
		"\n"
		"LFLAGS=" + win64LFlags + "\n"
		"LLIBS=$(3PL)\\lib\\libeay32.lib $(3PL)\\lib\\ssleay32.lib \\\n"
		"\t$(3PL)\\lib\\libxml2.lib $(3PL)\\lib\\libSLib.lib \\\n"
		"\t$(3PL)\\lib\\zdll.lib $(SOCKET_LIB)"
		"\n"
		".cpp.obj:\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		".c.obj:\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		vector<twine> splits = objFiles[i].split(".");
		if(splits[0] == "Jvm") continue; // Skip this one
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".obj\n" );
		} else {
			output.append( "\t" + splits[0] + ".obj \\\n" );
		}
	}

	output.append(
		"\n"
		"all: $(DOTOH)\n"
		"\tlink.exe $(LFLAGS) /OUT:libhelix.glob.dll /DLL $(DOTOH) ..\\logic\\util\\*.obj ..\\logic\\admin\\*.obj $(LLIBS)\n"
		"\tcopy libhelix.glob.lib ..\\bin\n"
		"\tcopy libhelix.glob.dll ..\\bin\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile all\n"
			);
		}
	}

	output.append(
		"\n"
		"clean:\n"
		"\tdel /Q /S $(DOTOH) *.obj *.pch *.lib *.exp *.exe.manifest *.exe *.dll *.dll.manifest\n"
		"\tdel /Q /S ..\\bin\\libhelix.glob.lib\n"
		"\tdel /Q /S ..\\bin\\libhelix.glob.lib\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && nmake -f Makefile clean\n"
			);
		}
	}

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createGlobWin32Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{
	twine output;
	output.append(
		"#\n"
		"# This is a Win32 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../3rdParty\n"
		"SOCKET_LIB=ws2_32.lib odbc32.lib rpcrt4.lib\n"
		"GMAKE=c:/cygwin/bin/make.exe -j 8\n"
		"\n"
		"CFLAGS=" + win32CFlags + " -I ../logic/util -I \"$(3PL)/programs/jdk5u22/include\" -I \"$(3PL)/programs/jdk5u22/include/win32\" \n"
		"\n"
		"\n"
		"%.obj: %.cpp\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"%.obj: %.c\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		vector<twine> splits = objFiles[i].split(".");
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".obj\n" );
		} else {
			output.append( "\t" + splits[0] + ".obj \\\n" );
		}
	}

	output.append(
		"\n"
		"all: $(DOTOH)\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile all\n"
			);
		}
	}

	output.append(
		"\n"
		"clean:\n"
		"\trm -f $(DOTOH) *.obj *.pch *.lib *.exp *.exe.manifest *.exe *.dll *.dll.manifest\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile clean\n"
			);
		}
	}

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createGlobLin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{
	twine output;
	output.append(
		"#\n"
		"# This is a Lin64 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../3rdParty\n"
		"GMAKE=make -j 8\n"
		"\n"
		"ifeq ($(UNAME),Linux)\n"
		"\tOPENSSLDIR=/usr\n"
		"else\n"
		"\tOPENSSLDIR=/usr/local/opt/openssl\n"
		"endif\n"
		"\n"
		"CFLAGS=" + lin64CFlags + " -I ../logic/util -I ../logic/admin -I. -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux \n"
		"\n"
		"ifeq ($(UNAME),Linux)\n"
		"\tLFLAGS=" + lin64LFlags + "\n"
		"else\n"
		"\tLFLAGS=" + mac64LFlags + "\n"
		"endif\n"
		"\n"
		"\n"
		"%.o: %.cpp\n"
		"\tg++ $(CFLAGS) -c $< -o $@\n"
		"\n"
		"%.o: %.c\n"
		"\tg++ $(CFLAGS) -c $< -o $@\n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		vector<twine> splits = objFiles[i].split(".");
		if(doJni == false && splits[0] == "Jvm") continue; // skip the Jvm.cpp if doJni is false
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".o\n" );
		} else {
			output.append( "\t" + splits[0] + ".o \\\n" );
		}
	}

	output.append(
		"\n"
		"all: $(DOTOH)\n"
		"\tg++ -shared -o libhelix.glob.so $(DOTOH) ../logic/util/*.o ../logic/admin/*.o $(LFLAGS)\n"
		"\tcp libhelix.glob.so ../bin/\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile all\n"
			);
		}
	}

	output.append(
		"\n"
		"clean:\n"
		"\trm -f $(DOTOH) *.o *.obj core *.so\n"
		"\trm -f ../bin/libhelix.glob.so\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile clean\n"
			);
		}
	}

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createClientMakefile( const twine& targetFolder ) 
{
	// check all of the normal files:
	vector<twine> allFiles = File::listFiles(targetFolder);
	vector<twine> objFiles;
	for(size_t i = 0; i < allFiles.size(); i++){
		if( allFiles[i].endsWith(twine(".cpp")) || allFiles[i].endsWith(twine(".c")) ){
			objFiles.push_back( allFiles[i] );
		}
	}
	
	// Find all folders under the given start:
	vector<twine> folders = File::listFolders(targetFolder);


	if(m_platform == "WIN32_x86"){
		createClientWin32Makefile( objFiles, folders, targetFolder);
	} else if(m_platform == "WIN32_x64"){
		createClientWin64Makefile( objFiles, folders, targetFolder);
	} else if(m_platform == "LINUX_x64"){
		createClientLin64Makefile( objFiles, folders, targetFolder);
	}
}

void createClientWin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{

	twine output;
	output.append(
		"#\n"
		"# This is a Win64 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../3rdParty\n"
		"SOCKET_LIB=ws2_32.lib odbc32.lib rpcrt4.lib\n"
		"GMAKE=c:/cygwin/bin/make.exe -j 8\n"
		"LINK=link.exe\n"
		"\n"
		"CFLAGS=" + win64CFlags + " -I \"$(3PL)/programs/jdk5u22/include\" -I \"$(3PL)/programs/jdk5u22/include/win32\" "
		"-I ../glob "
		"-I ../logic/admin "
		"-I ../logic/dev "
		"-I ../logic/test "
		"-I ../logic/util "
		"\n"
		"\n"
		"SSLLIBS=$(3PL)/lib/libeay32.lib $(3PL)/lib/ssleay32.lib \\\n"
		"\t$(3PL)/lib/libxml2.lib $(3PL)/lib/libSLib.lib $(3PL)/lib/zdll.lib \\\n"
		"\t$(3PL)/lib/libcurl.lib\n"
		"\n"
		"LFLAGS=" + win64LFlags + "\n"
		"LLIBS=$(SSLLIBS) $(SOCKET_LIB)\n"
		"\n"
		".cpp.obj:\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		".c.obj:\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"GLOBOBJS=../glob/*.obj\n"
		"LOGICOBJS=../logic/admin/*.obj \\\n"
		"\t../logic/dev/*.obj \\\n"
		"\t../logic/test/*.obj \\\n"
		"\t../logic/util/*.obj \n"
		"\n"
		"APIOH=HelixApi_Part1.obj HelixApi_Part2.obj\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		if(objFiles[i].startsWith("HelixApi_")){
			continue; // skip these
		}
		vector<twine> splits = objFiles[i].split(".");
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".obj\n" );
		} else {
			output.append( "\t" + splits[0] + ".obj \\\n" );
		}
	}

	output.append(
		"\n"
		"LINKOBJ=$(APIOH) $(GLOBOBJS) $(LOGICOBJS) $(LLIBS)\n"
		"\n"
		"all: $(DOTOH) $(APIOH)\n"
		"\tlink.exe $(LFLAGS) /OUT:libhelix.client.dll /DLL $(APIOH) ..\\bin\\libhelix.glob.lib ..\\bin\\libhelix.logic.dev.lib $(LLIBS)\n"
		"\tcopy libhelix.client.lib ..\\bin\n"
		"\tcopy libhelix.client.dll ..\\bin\n"
	);
	for(size_t i = 0; i < objFiles.size(); i++){
		if(objFiles[i].startsWith("HelixApi_")){
			continue; // skip these
		}
		vector<twine> splits = objFiles[i].split(".");
		output.append( "\t$(LINK) $(LFLAGS) /OUT:../bin/" + splits[0] + ".exe " + splits[0] + ".obj $(LINKOBJ)\n" );
	}


	output.append(
		"\n"
		"clean:\n"
		"\tdel /Q /S $(DOTOH) *.obj *.pch *.lib *.exp *.exe.manifest *.exe *.dll *.dll.manifest\n"
		"\tdel /Q /S ..\\bin\\libhelix.client.lib\n"
		"\tdel /Q /S ..\\bin\\libhelix.client.dll\n"
	);
	/*
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && nmake -f Makefile clean\n"
			);
		}
	}
	*/

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createClientWin32Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{
	twine output;
	output.append(
		"#\n"
		"# This is a Win32 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../3rdParty\n"
		"SOCKET_LIB=ws2_32.lib odbc32.lib rpcrt4.lib\n"
		"GMAKE=c:/cygwin/bin/make.exe -j 8\n"
		"LINK=link.exe\n"
		"\n"
		"CFLAGS=" + win32CFlags + " -I \"$(3PL)/programs/jdk5u22/include\" -I \"$(3PL)/programs/jdk5u22/include/win32\" "
		"-I ../glob "
		"-I ../logic/admin "
		"-I ../logic/dev "
		"-I ../logic/test "
		"-I ../logic/util "
		"\n"
		"\n"
		"SSLLIBS=$(3PL)/lib/libeay32.lib $(3PL)/lib/ssleay32.lib \\\n"
		"\t$(3PL)/lib/libxml2.lib $(3PL)/lib/libSLib.lib $(3PL)/lib/zdll.lib \\\n"
		"\t$(3PL)/lib/libcurl_imp.lib\n"
		"\n"
		"LFLAGS=" + win32LFlags + "\n"
		"LLIBS=$(SSLLIBS) $(SOCKET_LIB)\n"
		"\n"
		"%.obj: %.cpp\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"%.obj: %.c\n"
		"\tcl.exe $(CFLAGS) $<\n"
		"\n"
		"GLOBOBJS=../glob/*.obj\n"
		"LOGICOBJS=../logic/admin/*.obj \\\n"
		"\t../logic/dev/*.obj \\\n"
		"\t../logic/test/*.obj \\\n"
		"\t../logic/util/*.obj \n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		if(objFiles[i].startsWith("HelixApi_")){
			continue; // skip these
		}
		vector<twine> splits = objFiles[i].split(".");
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".obj\n" );
		} else {
			output.append( "\t" + splits[0] + ".obj \\\n" );
		}
	}

	output.append(
		"\n"
		"APIOH=HelixApi_Part1.obj HelixApi_Part2.obj\n"
		"LINKOBJ=$(APIOH) $(GLOBOBJS) $(LOGICOBJS) $(LLIBS)\n"
		"\n"
		"all: $(DOTOH) $(APIOH)\n"
	);
	for(size_t i = 0; i < objFiles.size(); i++){
		if(objFiles[i].startsWith("HelixApi_")){
			continue; // skip these
		}
		vector<twine> splits = objFiles[i].split(".");
		output.append( "\t$(LINK) $(LFLAGS) /OUT:../../bin/" + splits[0] + ".exe " + splits[0] + ".obj $(LINKOBJ)\n" );
	}


	output.append(
		"\n"
		"clean:\n"
		"\trm -f $(DOTOH) *.obj *.pch *.lib *.exp *.exe.manifest *.exe *.dll *.dll.manifest\n"
	);
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile clean\n"
			);
		}
	}

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

void createClientLin64Makefile( vector<twine>& objFiles, vector<twine>& subFolders, const twine& targetFolder)
{
	twine output;
	output.append(
		"#\n"
		"# This is a Lin64 Makefile generated for folder " + targetFolder + "\n"
		"# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp\n"
		"######################################################################\n"
		"\n"
		"3PL=../../../../3rdParty\n"
		"GMAKE=make -j 8\n"
		"LINK=g++\n"
		"UNAME := $(shell uname)\n"
		"\n"
		"ifeq ($(UNAME),Linux)\n"
		"\tOPENSSLDIR=/usr\n"
		"else\n"
		"\tOPENSSLDIR=/usr/local/opt/openssl\n"
		"endif\n"
		"\n"
		"CFLAGS=" + lin64CFlags + " -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux "
		"-I ../glob "
		"-I ../logic/admin "
		"-I ../logic/dev "
		"-I ../logic/test "
		"-I ../logic/util "
		"\n"
		"\n"
		"ifeq ($(UNAME),Linux)\n"
		"\tLFLAGS=" + lin64LFlags + "\n"
		"else\n"
		"\tLFLAGS=" + mac64LFlags + "\n"
		"endif\n"
		"\n"
		"GLOBOBJS=-L../bin -lhelix.glob\n"
		"LOGICOBJS=-L../bin \\\n"
		"\t-lhelix.logic.dev \n"
		"\n"
		"%.o: %.cpp\n"
		"\tg++ $(CFLAGS) -c $< -o $@\n"
		"\n"
		"%.o: %.c\n"
		"\tg++ $(CFLAGS) -c $< -o $@\n"
		"\n"
		"DOTOH=\\\n"
	);

	for(size_t i = 0; i < objFiles.size(); i++){
		if(objFiles[i].startsWith("HelixApi_")){
			continue; // skip these
		}
		if(objFiles[i].startsWith("NetTest")){
			continue; // skip these
		}
		vector<twine> splits = objFiles[i].split(".");
		if(i == (objFiles.size() - 1)){
			output.append( "\t" + splits[0] + ".o\n" );
		} else {
			output.append( "\t" + splits[0] + ".o \\\n" );
		}
	}

	output.append(
		"\n"
		"APIOH=HelixApi_Part1.o HelixApi_Part2.o\n"
		"LINKOBJ=-L../bin -lhelix.client $(GLOBOBJS) $(LOGICOBJS) $(LLIBS)\n"
		"\n"
		"all: $(DOTOH) $(APIOH)\n"
		"\tg++ -shared -o libhelix.client.so $(APIOH) $(LFLAGS) $(GLOBOBJS) $(LOGICOBJS)\n"
		"\tcp libhelix.client.so ../bin/\n"
	);
	for(size_t i = 0; i < objFiles.size(); i++){
		if(objFiles[i].startsWith("HelixApi_")){
			continue; // skip these
		}
		if(objFiles[i].startsWith("NetTest")){
			continue; // skip these
		}
		vector<twine> splits = objFiles[i].split(".");
		output.append( "\t$(LINK) -o ../bin/" + splits[0] + " " + splits[0] + ".o $(LINKOBJ) $(LFLAGS)\n" );
	}

	output.append(
		"\n"
		"clean:\n"
		"\trm -f $(DOTOH) *.o *.obj core *.so\n"
		"\trm -f ../bin/libhelix.client.so\n"
	);
	/*
	for(size_t i = 0; i < subFolders.size(); i++){
		if(subFolders[i] != "." && subFolders[i] != ".."){
			output.append(
				"\tcd " + subFolders[i] + " && $(GMAKE) -f Makefile clean\n"
			);
		}
	}
	*/

	output.append(
		"\n"
	);

	// Now save the updated file:
	try {
		File::writeToFile(targetFolder + "/Makefile" , output);
	} catch (AnException& e){
		printf("Error writing to file %s/Makefile:\n%s\n", targetFolder(), e.Msg() );
	}
}

