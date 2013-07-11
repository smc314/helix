/* ***************************************************************************

	Copyright: 2013 Hericus Software, LLC

	License: The MIT License (MIT)

	Authors: Steven M. Cherry

*************************************************************************** */

#include <AnException.h>
#include <Log.h>
#include <twine.h>
#include <File.h>
using namespace SLib;

#include <vector>
using namespace std;

twine m_prefix="./qd/source/resource/zed/icon/";
twine m_originals="../../../../IconExperience/v_collection/v_collection_png/";
	
vector<twine> m_sizes;

void run() ;
void checkFiles(int sizeIndex);
void copyFromOriginal(int sizeIndex, twine& filename) ;

int main(void)
{
	m_sizes.push_back("16x16/plain");
	m_sizes.push_back("24x24/plain");
	m_sizes.push_back("32x32/plain");
	m_sizes.push_back("32x32/shadow");
	m_sizes.push_back("48x48/plain");
	m_sizes.push_back("48x48/shadow");
	m_sizes.push_back("64x64/plain");
	m_sizes.push_back("64x64/shadow");
	m_sizes.push_back("128x128/plain");
	m_sizes.push_back("128x128/shadow");
	m_sizes.push_back("256x256/plain");
	m_sizes.push_back("256x256/shadow");
	
	m_prefix = "../qd/admin/source/resource/admin/icon/";
	run();
	m_prefix = "../qd/dev/source/resource/dev/icon/";
	run();
	m_prefix = "../qd/welcome/source/resource/welcome/icon/";
	run();

}

void run() 
{
	try {
		for(int j = 0; j < (int)m_sizes.size(); j++){
			checkFiles( j);
		}
	} catch (AnException& e){
		printf("Exception: %s\n", e.Msg());
	}
}

void checkFiles(int sizeIndex)
{
	
	vector<twine> files;
	try {
		files = File::listFiles( m_prefix + "/" + m_sizes[sizeIndex] );
	} catch (AnException&){
		printf("Icon size does not exist: %s\n", (m_prefix + "/" + m_sizes[sizeIndex])() );
		return; 
	}
	
	for(int i = 0; i < (int)files.size(); i++){
		// for every file in this directory, check it's existence in all
		// the other size directories with the same suffix.  If it doesn't
		// exist in another directory, copy it in from the originals.
		
		for(int j = 0; j < (int)m_sizes.size(); j++){
			if(j == sizeIndex){
				continue; // it's us.
			}
			try {
				File other_size(m_prefix + "/" + m_sizes[j] + "/" + files[i] );
			} catch (AnException&){
				// this means it doesn't exist
				copyFromOriginal( j, files[i] );
			}
			
		}
		
	}
	
}

void copyFromOriginal(int sizeIndex, twine& filename) 
{
	
	twine copy_from = m_originals + m_sizes[sizeIndex] + "/" + filename;
	
	twine copy_to = m_prefix + m_sizes[sizeIndex] + "/" + filename;
	
	printf("Copying from: %s\n", copy_from());
	printf("Copying to  : %s\n", copy_to());
	
	try {
		File::Copy(copy_from, copy_to);
	} catch (AnException& e){
		printf("\tException: %s\n", e.Msg());
	}
	
}
