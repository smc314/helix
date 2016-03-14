/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "TheMain.h"
#include "OdbcObj.h"
using namespace Helix::Glob;

#include "Statics.h"
using namespace Helix::Logic::util;

#include <Log.h>
#include <dptr.h>
#include <File.h>
#include <EnEx.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

#ifdef _WIN32
#include <direct.h>
#endif

void Statics::ReplaceSessionVars(IOConn& ioc, twine& target)
{
	EnEx ee(FL, "Statics::ReplaceSessionVars(IOConn& ioc, twine& target)");

	// Pull out the normal user-properties from the session.
	SessionInfo& si = ioc.getSessionInfo();

	DEBUG(FL, "ReplaceSessionVars - original string: %s", target() );

	size_t idx1 = 0, idx2 = 0;
	while(idx1 < target.length() ){
		idx1 = target.find("${", idx1);
		if(idx1 == TWINE_NOT_FOUND){
			break; // nothing to do.
		}
		idx1 += 2;
		idx2 = target.find("}", idx1);
		if(idx2 == TWINE_NOT_FOUND){
			continue; // nothing to do.
		}
		twine varName = target.substr(idx1, idx2-idx1);
		idx1 -= 2;
		if(si.userProperties.count(varName) != 0){
			target.replace(idx1, idx2-idx1 + 1, si.userProperties[ varName ] );
		} else if(varName == "userid"){
			twine useridStr; useridStr.format("%d", si.userid);
			target.replace(idx1, idx2-idx1 + 1, useridStr );
		} else {
			idx1 += 2;
		}
	}

	DEBUG(FL, "ReplaceSessionVars - updated string: %s", target() );
}

void Statics::ConvertToOneZero(twine& str)
{
	EnEx ee(FL, "Statics::ConvertToOneZero(twine& str)");

	if(str.length() > 0 && (str[(size_t)0] == 'Y' || str[(size_t)0] == 'y')){
		str = "1";
	} else {
		str = "0";
	}
}

void Statics::ConvertToYesNo( twine& flag )
{
	EnEx ee(FL, "Statics::ConvertToYesNo(twine& flag)");
	if(flag == "1"){
		flag = "YES";
	} else {
		flag = "NO";
	}
}

void Statics::ConvertToYN( twine& flag )
{
	EnEx ee(FL, "Statics::ConvertToYN(twine& flag)");
	if(flag == "1"){
		flag = "Y";
	} else {
		flag = "N";
	}
}

void Statics::ConvertToNULL( twine& flag )
{
	EnEx ee(FL, "Statics::ConvertToNULL(twine& flag)");
	if(flag.length() == 0){
		flag = "NULL";
	}
}

void Statics::ConvertToZero( twine& flag )
{
	EnEx ee(FL, "Statics::ConvertToZero(twine& flag)");
	if(flag.length() == 0){
		flag = "0";
	}
}

void Statics::ConvertOnOffToOneZero(twine& str)
{
	EnEx ee(FL, "Statics::ConvertOnOffToOneZero(twine& str)");

	if(str.length() > 1 && (str[(size_t)1] == 'N' || str[(size_t)1] == 'n') ){
		str = "1";
	} else {
		str = "0";
	}
}

void Statics::ConvertToOnOff( twine& flag )
{
	EnEx ee(FL, "Statics::ConvertToOnOff(twine& flag)");
	if(flag == "1"){
		flag = "ON";
	} else {
		flag = "OFF";
	}
}

twine Statics::convertIP( unsigned int ipAddr )
{
	EnEx ee(FL, "Statics::convertIP(int ipAddr)");

	// Convert the IPAddr into a dotted quad:
	int tmp1 = ipAddr >> 24 & 0x000000FF;
	int tmp2 = ipAddr >> 16 & 0x000000FF;
	int tmp3 = ipAddr >> 8 & 0x000000FF;
	int tmp4 = ipAddr & 0x000000FF;
	twine ret;
	ret.format("%d.%d.%d.%d", tmp1, tmp2, tmp3, tmp4);
	return ret;
}

void Statics::ensureSubDir( const twine& dirName )
{
	EnEx ee(FL, "Statics::convertIP(int ipAddr)");

	vector<twine> folders = File::listFolders( "." ); // right here
	for(int i = 0; i < (int)folders.size(); i++){
		if(folders[i] == dirName){
			return; // we've found it, nothing else to do.
		}
	}

	// If we get here, we didn't find it.  Create it
#ifdef _WIN32
	_mkdir( dirName() );
#else
	mkdir( dirName(), 0777 );
#endif

	// That's it.
}

bool Statics::areWeHomeBase()
{
	// smc - 05/01/2013 - change this to be a configuration entry so that it's very
	// easy to setup, and not dependent on which machine we are running - no more
	// hard-coded machine names.
	xmlDocPtr config = TheMain::getInstance()->GetConfig();
	xmlNodePtr root = xmlDocGetRootElement(config);
	return XmlHelpers::getBoolAttr( root, "areWeHomeBase" );
}
