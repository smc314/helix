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


twine m_currentPackage;
twine m_currentFile;

void findAllJSFiles(twine start);
void processFile( twine& file_name );

int main (void)
{
	printf("============================================================================\n");
	printf(" CopyCommon copying in global javascript files to each application.         \n");
	printf("============================================================================\n");

	m_currentPackage = "admin"; findAllJSFiles("../qd/common");
	m_currentPackage = "dev"; findAllJSFiles("../qd/common");
	m_currentPackage = "welcome"; findAllJSFiles("../qd/common");


	return 0;
}

void findAllJSFiles(twine start)
{
	// check all of the normal files:
	vector<twine> files = File::listFiles(start);
	for(size_t i = 0; i < files.size(); i++){
		twine child = start + "/" + files[i];
		if(child.endsWith(twine(".js")) || child.endsWith(twine(".base")) ){
			m_currentFile = child;
			processFile(child);
		}
	}

	// Then recurse through all of the subdirectories:
	vector<twine> folders = File::listFolders(start);
	for(size_t i = 0; i < folders.size(); i++){
		if(folders[i] != "." && folders[i] != ".."){
			findAllJSFiles(start + "/" + folders[i]);
		}
	}

}

void processFile( twine& file_name ) 
{
	vector<twine> pathElements = file_name.split("/");

	twine targetPath;
	if(pathElements.size() == 4){
		targetPath = "../qd/" + m_currentPackage + "/source/class/" + m_currentPackage + "/" +
			pathElements[3];
	} else {
		targetPath = "../qd/" + m_currentPackage + "/source/class/" + m_currentPackage + "/" +
			pathElements[3] + "/" + pathElements[4];
	}
	// printf("Copy (%s) to (%s)\n", file_name(), targetPath() );

	vector<twine> lines;
	try {
		File f(file_name);
		lines = f.readLines();

		for(size_t i = 0; i < lines.size(); i++){
			// replace PACKAGE with our current package name:
			size_t idx = lines[i].find("PACKAGE");
			while(idx != TWINE_NOT_FOUND){
				lines[i].replace(idx, 7, m_currentPackage);
				idx = lines[i].find("PACKAGE", idx);
			}
		}

	} catch (AnException& e){
		printf("Error processing file %s:\n%s\n", file_name(), e.Msg() );
		return;
	}
	
	// Now save the updated file:
	try {
		twine output;
		for(size_t i = 0; i < lines.size(); i++){
			output += lines[i] + "\n";
		}
		File::writeToFile(targetPath, output);
	} catch (AnException& e){
		printf("Error writing to file %s:\n%s\n", targetPath(), e.Msg() );
	}
}

