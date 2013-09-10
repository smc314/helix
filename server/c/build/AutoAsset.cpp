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
vector<twine> findIcons( vector<twine>& lines );
void updateAssetTags( vector<twine>& lines, vector<twine>& icons );

int main (void)
{
	printf("============================================================================\n");
	printf("Auto-Asset analyzing all javascript files to create the asset header tags.  \n");
	printf("============================================================================\n");
	findAllJSFiles("../../../qd");

	return 0;
}

void findAllJSFiles(twine start)
{
	// check all of the normal files:
	vector<twine> files = File::listFiles(start);
	for(int i = 0; i < (int)files.size(); i++){
		twine child = start + "/" + files[i];
		if(child.endsWith(twine(".js"))){
			m_currentFile = child;
			processFile(child);
		}
	}

	// Then recurse through all of the subdirectories:
	vector<twine> folders = File::listFolders(start);
	for(int i = 0; i < (int)folders.size(); i++){
		if(folders[i] != "." && folders[i] != ".."){
			findAllJSFiles(start + "/" + folders[i]);
		}
	}

}

void processFile( twine& file_name ) 
{
	vector<twine> pathElements = file_name.split("/");
	if(pathElements[5] != "source" ||
		pathElements[6] != "class"
	){
		return; // skip this file
	}
	m_currentPackage = pathElements[4];
	//printf("Processing JavaScript File: %s\n", file_name() );

	vector<twine> lines;
	try {
		File f(file_name);
		lines = f.readLines();

		vector<twine> icons = findIcons( lines );
		
		updateAssetTags( lines, icons);

	} catch (AnException& e){
		printf("Error processing file %s:\n%s\n", file_name(), e.Msg() );
		return;
	}
	
	// Now save the updated file:
	twine output;
	for(int i = 0; i < (int)lines.size(); i++){
		output += lines[i] + "\n";
	}
	File::writeToFile(file_name, output);
}

vector<twine> findIcons( vector<twine>& lines ) 
{
	vector<twine> ret;
	
	for(int i = 0; i < (int)lines.size(); i++){
		if(lines[i].startsWith("#asset")){
			continue; // skip this line
		}
		size_t idx1 = lines[i].find("\"" + m_currentPackage + "/");
		if(idx1 == TWINE_NOT_FOUND){
			continue; // skip this line
		}
		bool found_template = false;
		size_t idx2 = lines[i].find(".png\"");
		if(idx2 == TWINE_NOT_FOUND){
			idx2 = lines[i].find(".gif\"");
			if(idx2 == TWINE_NOT_FOUND){
				idx2 = lines[i].find(".jpg\"");
				if(idx2 == TWINE_NOT_FOUND){
					// not a .png, .gif, or .jpg file.
					// check for a template file
					idx2 = lines[i].find("\"" + m_currentPackage + "/templates/" );
					if(idx2 == TWINE_NOT_FOUND){
						// not a template file either
						continue;
					} else {
						// found a template file.  move idx2 to the end of the string.
						idx2 = lines[i].find( '"', idx1 + 5 );
						found_template = true;
					}
				}
			}
		}
		idx1 ++; // skip the quote at the beginning
		if(!found_template){
			idx2 += 4; // skip the quote at the end
		}
		ret.push_back( lines[i].substr(idx1, idx2-idx1) );
	}
	return ret;
}

void updateAssetTags( vector<twine>& lines, vector<twine>& icons )
{
	int idx1, idx2;
	idx1 = idx2 = 0;
	
	// Find the first #asset line
	for(int i = 0; i < (int)lines.size(); i++){
		if(lines[i].startsWith("#asset(")){
			idx1 = i;
			break;
		}
	}
		
	// find the last #asset line
	for(int i = idx1 + 1; i < (int)lines.size(); i++){
		if(lines[i].startsWith("#asset(")){
			idx2 = i;
		}
	}
	
	if(idx1 == 0){
		// no #asset tags in the file.  log a warning.
		if(icons.size() != 0){
			// Find the first *** line:
			for(int i = 0; i < (int)lines.size(); i++){
				if(lines[i].startsWith("**********")){
					lines.insert(lines.begin() + i + 1, "************************************************************************ */");
					lines.insert(lines.begin() + i + 1, "");
					lines.insert(lines.begin() + i + 1, "/* ************************************************************************");
					idx1 = i+2;
					break;
				}
			}
			if(idx1 == 0){ // still zero
				printf("Couldn't find the place to add the #asset tags\n");
				return;
			}
			
		} else {
			return; // no icons so no issue.
		}
	}
	if(idx2 == 0){
		idx2 = idx1;
	}
	
	// Get rid of all #asset tags.
	for(int i = 0; i < idx2-idx1+1; i++){
		// save it if it has a star in it.
		if(lines[ idx1 ].find('*') != TWINE_NOT_FOUND){
			size_t starIdx1 = lines[ idx1 ].find( '(' );
			size_t starIdx2 = lines[ idx1 ].find( ')' );
			starIdx1 ++;
			icons.push_back( lines[ idx1 ].substr( starIdx1, starIdx2 - starIdx1 ) );
		}
		lines.erase(lines.begin() + idx1);
	}
	
	// Now add back in the correct #asset tags for the icons we use.
	for(int i = 0; i < (int)icons.size(); i++){
		lines.insert(lines.begin() + idx1, "#asset(" + icons[i] + ")");
		idx1++;
	}
	
}
	
