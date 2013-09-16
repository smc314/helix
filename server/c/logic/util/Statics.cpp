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

twine Statics::encryptPwd( twine& pass, int len)
{
	EnEx ee(FL, "Statics::encryptPwd(twine& pass, int len)");

	int fibs = 0;
	int k = 0;
	twine input = pass;
	if(input.length() < (size_t)len){
		while(input.length() < (size_t)len) input += " ";
	}
	twine temp = "";
	// first character in ring is not used.  Added to make the
	// C# 1-based indexing algorithm work.
	twine ring = "  !#$%&+-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	size_t ringLen = ring.length() - 1;
	size_t fib1 = 0;
	size_t fib2 = 1;
	for(size_t i = 0; i < input.length(); i++){
		fibs = fib1 + fib2;
		fib1 = fib2;
		fib2 = fibs;
		bool done = true;
		for(size_t j = 1; j <= ringLen; j++){
			if(input[i] == ring[j]){
				if(j + fibs <= ringLen){
					temp = temp + ring[j + fibs];
				} else {
					k = (j + fibs) % ringLen;
					if(k == 0){
						k = ringLen;
					}
					temp = temp + ring[(size_t)k];
				}
				done = false;
				break;
			}
		}
		// char not found
		if(done){
			return twine("        ");
		}
	}
	return temp;
}

twine Statics::decryptPwd( twine& enc)
{
	EnEx ee(FL, "Statics::decryptPwd(twine& pass)");

	int fibs = 0;
	int k = 0;

	twine temp = "";
	twine ring = "  !#$%&+-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	size_t ringLen = ring.length() - 1;
	size_t fib1 = 0;
	size_t fib2 = 1;
	for(size_t i = 0; i < enc.length(); i++){
		fibs = fib1 + fib2;
		fib1 = fib2;
		fib2 = fibs;
		bool done = true;
		for(size_t j = 1; j <= ringLen; j++){
			if(enc[i] == ring[j]){
				if(j > (size_t)fibs){
					temp = temp + ring[j - fibs];
				} else {
					k = (j - fibs) % ringLen;
					if(k < 0){
						k = -k;
					}
					k = ringLen - k;
					temp = temp + ring[(size_t)k];
				}
				done = false;
				break;
			}
		}
		// char not found
		if(done){
			WARN(FL, "Encrypted password (%s) contains an invalid character.  Decryption fails.", enc() );
			return twine("");
		}
	}
	return temp;
}

twine Statics::decryptCSAPwd( twine& enc)
{
	EnEx ee(FL, "Statics::decryptCSAPwd(twine& pass)");

	int i, j, k;      // indexes
	int pwi;          // password index
	int iFibCnt[33];  // max length of password is 31
	twine decPwd;     // decrypted password
	twine codeTable = "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-+'&%$#\"! ";

	iFibCnt[0] = 1;
	iFibCnt[1] = 1;

	DEBUG(FL, "CSA Encrypted password --%s--", enc() );

	for (j=1, pwi = 0; j <= (int)enc.length(); j++) {
		/***************************************************************/
		/* Get position of password character in the CodeTable if not  */
		/* in table return with an error.                              */
		/***************************************************************/
		i = codeTable.find( enc[ (size_t)pwi ] );
		if(i == TWINE_NOT_FOUND ){
			throw AnException(0, FL, "Invalid encrypted password." );
		}

		/***********************************************************/
		/* Decrypt the character using Fibonacci indexing into the */
		/* CodeTable. (1, 2, 3, 5, 8,...)                          */
		/***********************************************************/
		if (i + iFibCnt[j] >= codeTable.length() ) {
			/*
			**  @r292 9/11/2007 Use mod operator to support password
			**  longer than about 10 chars.
			*/
			k = (i + iFibCnt[j]) % codeTable.length();
			decPwd.append( codeTable[k] );
		} else {
			decPwd.append( codeTable[i+iFibCnt[j]] );
		}


		if (decPwd[ (size_t)pwi ] == ' ' || j == 30) {
			break; // we're done
		}
		
		//  move on to the next password character
		pwi++;

		iFibCnt[j+1] = iFibCnt[j] + iFibCnt[j-1];
	}

	DEBUG(FL, "CSA Decrypted password --%s--", decPwd() );

	return decPwd;
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
