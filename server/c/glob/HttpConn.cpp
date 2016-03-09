/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#include "HttpConn.h"
using namespace Helix::Glob;

#include <Date.h>
#include <EnEx.h>
#include <Log.h>
#include <File.h>
#include <memptr.h>
#include <AnException.h>
#include <XmlHelpers.h>
using namespace SLib;

#include "zlib.h"

// From the mongoose.c code
#ifdef _WIN32
extern "C" {
time_t parse_date_string(const char* s);
}
#else
time_t parse_date_string(const char* s);
#endif

static const twine defaultMimeType("text/plain");
static const struct {
	twine extension;
	twine mime_type;
} known_mime_types[] = {
	{".html", "text/html"},
	{".htm", "text/html"},
	{".shtm", "text/html"},
	{".shtml", "text/html"},
	{".css", "text/css"},
	//{".js",  "application/x-javascript"},
	{".js",  "text/javascript"},
	{".ico", "image/x-icon"},
	{".gif", "image/gif"},
	{".jpg", "image/jpeg"},
	{".jpeg", "image/jpeg"},
	{".png", "image/png"},
	{".svg", "image/svg+xml"},
	{".torrent", "application/x-bittorrent"},
	{".wav", "audio/x-wav"},
	{".mp3", "audio/x-mp3"},
	{".mid", "audio/mid"},
	{".m3u", "audio/x-mpegurl"},
	{".ram", "audio/x-pn-realaudio"},
	{".xml", "text/xml"},
	{".xslt", "application/xml"},
	{".ra",  "audio/x-pn-realaudio"},
	{".doc", "application/msword"},
	{".exe", "application/octet-stream"},
	{".zip", "application/x-zip-compressed"},
	{".xls", "application/excel"},
	{".tgz", "application/x-tar-gz"},
	{".tar", "application/x-tar"},
	{".gz",  "application/x-gunzip"},
	{".arj", "application/x-arj-compressed"},
	{".rar", "application/x-arj-compressed"},
	{".rtf", "application/rtf"},
	{".pdf", "application/pdf"},
	{".swf", "application/x-shockwave-flash"},
	{".mpg", "video/mpeg"},
	{".mpeg", "video/mpeg"},
	{".asf", "video/x-ms-asf"},
	{".avi", "video/x-msvideo"},
	{".bmp", "image/bmp"},
	{"", ""}
};

HttpConn::HttpConn(
	enum mg_event event, 
	struct mg_connection* conn, 
	const struct mg_request_info* ri,
	int compressionThreshold,
	bool keepalive) :
		IOConn(),
		m_event(event), 
		m_conn(conn), 
		m_ri(ri), 
		m_compressionThreshold(compressionThreshold),
		m_keepalive( keepalive )
{
	EnEx ee(FL, "HttpConn::HttpConn()");
	m_doc = NULL;
	m_doc_loaded = false;
	m_sessionid = "";
	m_sessionid_loaded = false;
	m_use_ssl = false;
	m_httpDomain = "";
	m_sessionCookie = "";
	m_compression_ok = false;
	if(m_compressionThreshold != 0){ // don't even check if it's not turned on.
		const char* enc = mg_get_header(m_conn, "Accept-Encoding");
		if(enc != NULL){
			twine encoding(enc);
			if(encoding.find("gzip") != TWINE_NOT_FOUND){
				m_compression_ok = true;
			}
		}
	}
}

HttpConn::~HttpConn()
{
	EnEx ee(FL, "HttpConn::~HttpConn()");

	if(m_doc != NULL){
		xmlFreeDoc(m_doc);
		m_doc = NULL;
		m_doc_loaded = false;
	}

}

twine HttpConn::MsgTarget()
{
	EnEx ee(FL, "HttpConn::MsgTarget()");
	twine ret;
	if(!m_override_target.empty()){
		ret = m_override_target;
	} else {
		ret = m_ri->uri;
	}
	if(ret == "/"){
		ret = "/index.html";
	}
	return ret;
}

unsigned long HttpConn::MsgRemoteIp()
{
	return m_ri->remote_ip;
}

twine HttpConn::getSessionID()
{
	EnEx ee(FL, "HttpConn::getSessionID()");

	if(m_sessionid_loaded){
		return m_sessionid;
	}
	m_sessionid_loaded = true; // whether we find it or not, we've now looked for it once.
	
	// Check for it first in our cookies:
	char buff[512];
	int len = mg_get_cookie(m_conn, "HelixSessionID", buff, sizeof(buff) );

	if(len <= 0){
		DEBUG(FL, "cookie not found. try it our parent's way.");
		m_sessionid = IOConn::getSessionID();
		return m_sessionid;
	}
		
	DEBUG(FL, "Setting sessionID from cookie: %s", buff);
	m_sessionid = buff;

	return m_sessionid;
}

void HttpConn::setSessionID(const twine newSession) 
{
	EnEx ee(FL, "HttpConn::setSessionID(const twine newSession)");
	
	m_sessionid = newSession;
	m_sessionid_loaded = true;

	// put it in the response XML document:
	IOConn::setSessionID(newSession);
	
	SessionInfo& si = getSessionInfo();
	Date expires = si.created;
	expires.AddYear( 10 );

	// and put it in an HTTP secure cookie:
	m_sessionCookie.format("Set-Cookie: HelixSessionID=%s; path=/; expires=%s;\r\n",
		m_sessionid(), expires.GetValue("%a, %d %b %Y %H:%M:%S GMT") );
}

xmlDocPtr HttpConn::GetMsg()
{
	EnEx ee(FL, "HttpConn::GetMsg()");
	if(!m_doc_loaded){ 
		try {
			if(strcmp(m_ri->request_method, "GET") == 0){
				// GET's don't have a body.
				m_doc_loaded = true;
				m_doc = NULL;
			} else if(strcmp(m_ri->request_method, "HEAD") == 0){
				// HEAD's don't have a body.
				m_doc_loaded = true;
				m_doc = NULL;
			} else {
				const char* contentLength = mg_get_header(m_conn, "Content-Length");
				if(contentLength == NULL){
					throw AnException(0, FL, "Missing Content-Length header on inbound POST request.");
				}
				int bufLen = atoi(contentLength);
				memptr<char> buff; buff = (char*)malloc(bufLen+1);
				memset(buff, 0, bufLen+1);

				mg_read(m_conn, buff, bufLen);
				m_doc = xmlParseDoc((xmlChar*)buff());

				if(m_doc == NULL){
					DEBUG(FL, "Bad XML Document Text:\n%s", buff());
				}
				m_doc_loaded = true;
				if(m_doc != NULL){
					DEBUG(FL, "%s", XmlHelpers::docToStringPretty(m_doc)());
				}
			}
		} catch (AnException& e){
			WARN(FL, "AnException reading input doc:\n%s", e.Msg() );
			m_doc = NULL;
			m_doc_loaded = true;
		}
	}
	return m_doc;
}

xmlNodePtr HttpConn::GetRequestRoot(void)
{
	EnEx ee(FL, "HttpConn::GetRequestRoot()");

	xmlDocPtr doc = GetMsg();
	if(doc == NULL){
		throw AnException(0, FL, "No input Request document found.");
	}

	// Return the root element.
	return xmlDocGetRootElement(doc);
}

void HttpConn::WriteDataResponse(const unsigned char* data, long dataLen, const twine& mimeType)
{
	EnEx ee(FL, "HttpConn::WriteDataResponse()");

	bool isCompressed = false;
	if(mimeType == "image/x-icon" ||
		mimeType == "image/gif" ||
		mimeType == "image/jpeg" ||
		mimeType == "image/jpeg" ||
		mimeType == "image/png" ||
		mimeType == "image/svg+xml" ||
		mimeType == "audio/x-mp3" ||
		mimeType == "audio/mid" ||
		mimeType == "audio/x-mpegurl" ||
		mimeType == "audio/x-pn-realaudio" ||
		mimeType ==  "audio/x-pn-realaudio" ||
		mimeType == "application/octet-stream" ||
		mimeType == "application/x-zip-compressed" ||
		mimeType == "application/x-tar-gz" ||
		mimeType ==  "application/x-gunzip" ||
		mimeType == "application/x-arj-compressed" ||
		mimeType == "application/x-arj-compressed" ||
		mimeType == "video/mpeg" ||
		mimeType == "video/mpeg" ||
		mimeType == "video/x-msvideo"
	){
		// These are already compressed, don't try and compress them further.
		isCompressed = true; 
	}

	DEBUG(FL, "Compression (%s) DataLen (%ld) Threshold (%d) MimeType (%s)",
		m_compression_ok ? "true" : "false", dataLen, m_compressionThreshold, mimeType() );
	if(m_compression_ok && dataLen >= m_compressionThreshold && isCompressed == false){
		long compDataLen = 0;
		memptr< unsigned char > compData; compData = CompressData( &compDataLen, data, dataLen );
		DEBUG(FL, "Sending back compressed data of size(%ld)", compDataLen);
		mg_printf(m_conn, "Content-Encoding: gzip\r\n");
		mg_printf(m_conn, "Content-Length: %ld\r\n", compDataLen );
		mg_printf(m_conn, "\r\n");
		mg_write(m_conn, compData, compDataLen);
	} else {
		DEBUG(FL, "Sending back un-compressed data of size(%ld)", dataLen);
		mg_printf(m_conn, "Content-Length: %d\r\n", dataLen );
		mg_printf(m_conn, "\r\n");
		mg_write(m_conn, data, dataLen);
	}
}

void HttpConn::SendReturn() 
{
	EnEx ee(FL, "HttpConn::SendReturn()");
	if(m_resp_doc == NULL){
		initializeResponseDocument("Response");
	}
	try {
		twine respString = XmlHelpers::docToString(m_resp_doc);
		DEBUG(FL, "Response:\n%s", respString() );
		mg_printf(m_conn, "HTTP/1.1 200 OK\r\n");
		mg_printf(m_conn, "Content-Type: application/xml\r\n");
		if(m_keepalive == false){
			mg_printf(m_conn, "Connection: close\r\n");
		}
		if(m_sessionCookie.length() != 0){
			mg_printf(m_conn, "%s", m_sessionCookie() );
		}
		//mg_printf(m_conn, "Connection: close\r\n");
		WriteDataResponse( (const unsigned char*)respString(), respString.size(), twine("text/xml") );

	} catch (AnException& e){
		WARN(FL, "Error sending response document: %s", e.Msg() );
	}
}

void HttpConn::SendReturn(
		unsigned char* data, 
		int dataLen, 
		twine fileName, 
		Date lastModified, 
		Date expires) 
{
	EnEx ee(FL, "HttpConn::SendReturn(unsigned char* data)");
	try {
		twine mimeType = GetMimeType(fileName);
		mg_printf(m_conn, "HTTP/1.1 200 OK\r\n");
		mg_printf(m_conn, "Last-Modified: %s\r\n", lastModified.GetValue("%a, %d %b %Y %H:%M:%S %Z") );
		mg_printf(m_conn, "Content-Type: %s\r\n", mimeType() );
		if(m_keepalive == false){
			mg_printf(m_conn, "Connection: close\r\n");
		}
		if(m_sessionCookie.length() != 0){
			mg_printf(m_conn, "%s", m_sessionCookie() );
		}
		WriteDataResponse( data, dataLen, mimeType );

	} catch (AnException& e){
		WARN(FL, "Error sending response document: %s", e.Msg() );
	}
}

void HttpConn::SendReturn(twine& filePath, twine& fileName, Date lastModified, Date expires)
{
	EnEx ee(FL, "HttpConn::SendReturn(twine& filePath)");
	try {
		File payload( filePath );

		mg_printf(m_conn, "HTTP/1.1 200 OK\r\n");
		mg_printf(m_conn, "Last-Modified: %s\r\n", payload.lastModified().GetValue("%a, %d %b %Y %H:%M:%S %Z") );
		mg_printf(m_conn, "Content-Type: %s\r\n", GetMimeType(payload.name())() );
		if(m_sessionCookie.length() != 0){
			mg_printf(m_conn, "%s", m_sessionCookie() );
		}
		// this will prompt the user's browser to open the file-save-as dialog
		mg_printf(m_conn, "Content-Disposition: attachment; filename=%s\r\n", fileName());
		mg_printf(m_conn, "Content-Length: %d\r\n", payload.size());
		if(m_keepalive == false){
			mg_printf(m_conn, "Connection: close\r\n");
		}
		mg_printf(m_conn, "\r\n");

		size_t ret;
		int ret2;
		MemBuf buf(4096000);
		while( (ret = payload.read( buf )) != 0){
			EnEx ee2(FL, "HttpConn::SendReturn(twine& filePath) - 4M Chunk Write"); // time the writes
			ret2 = mg_write(m_conn, buf(), ret);
			if(ret2 <= 0 && ret != 0){
				throw AnException(0, FL, "Error writing data response. 0 bytes written - %d available", ret);
			}
		}

	} catch (AnException& e){
		WARN(FL, "Error sending response document: %s", e.Msg() );
	}
}

void HttpConn::SendNotModified() 
{
	EnEx ee(FL, "HttpConn::SendNotModified()");
	try {
		mg_printf(m_conn, "HTTP/1.1 304 Not Modified\r\n");
		if(m_keepalive == false){
			mg_printf(m_conn, "Connection: close\r\n\r\n");
		}

	} catch (AnException& e){
		WARN(FL, "Error sending Not Modified Response: %s", e.Msg() );
	}
}

const twine& HttpConn::GetMimeType(twine& fileName)
{
	EnEx ee(FL, "HttpConn::GetMimeType(twine& fileName)");

	for(int i = 0; !known_mime_types[i].extension.empty(); i++){
		if(fileName.endsWith( known_mime_types[i].extension )){
			return known_mime_types[i].mime_type;
		}
	}
	return defaultMimeType;
}

void HttpConn::SendError() 
{
	EnEx ee(FL, "HttpConn::SendError()");

	SendReturn();
}

void HttpConn::SendNotFound() {
	EnEx ee(FL, "HttpConn::SendNotFound()");
	try {
		mg_printf(m_conn, "HTTP/1.1 404 Not Found\r\n");
		if(m_keepalive == false){
			mg_printf(m_conn, "Connection: close\r\n\r\n");
		}

	} catch (AnException& e){
		WARN(FL, "Error sending response document: %s", e.Msg() );
	}
}

void HttpConn::SendForbidden() {
	EnEx ee(FL, "HttpConn::SendForbidden()");
	try {
		mg_printf(m_conn, "HTTP/1.1 403 Forbidden\r\n");
		if(m_keepalive == false){
			mg_printf(m_conn, "Connection: close\r\n\r\n");
		}

	} catch (AnException& e){
		WARN(FL, "Error sending response document: %s", e.Msg() );
	}
}


void HttpConn::SendRedirect( const twine& newLocation ) {
	EnEx ee(FL, "HttpConn::SendRedirect()");
	try {
		mg_printf(m_conn, "HTTP/1.1 307 Temporary Redirect\r\n");
		mg_printf(m_conn, "Location: %s\r\n", newLocation() );
		if(m_keepalive == false){
			mg_printf(m_conn, "Connection: close\r\n\r\n");
		}

	} catch (AnException& e){
		WARN(FL, "Error sending redirect document: %s", e.Msg() );
	}
}

twine HttpConn::getHttpDomain()
{
	return m_httpDomain;
}

Date HttpConn::GetIfModifiedSince(void)
{
	EnEx ee(FL, "HttpConn::GetIfModifiedSince()");

	Date ret;
	const char* ims = mg_get_header(m_conn, "If-Modified-Since");
	if(ims == NULL){
		ret.AddYear(-20);
	} else {
		// parse the date:
		ret.SetValue( parse_date_string(ims) );
	}
	return ret;
}

unsigned char* HttpConn::CompressData(long* destSize, const unsigned char* source, long sourceSize)
{
	EnEx ee(FL, "HttpConn::CompressData()");

	int ret;
	z_stream strm;

	/* allocate deflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit2(&strm, 
		Z_BEST_COMPRESSION, // trade CPU for more compression
		Z_DEFLATED,  // only option at this point
		15 + 16, // max window size, and add 16 to get gzip formatting
		9, // max memory
		Z_DEFAULT_STRATEGY
	);
	if(ret != Z_OK){
		throw AnException(0, FL, "Error initializing zlib deflate.");
	}

	// What's our upper bound for compressing the data that we've received?
	*destSize = (long) deflateBound(&strm, sourceSize);

	// Allocate a buffer to hold the destination:
	memptr<unsigned char> dest; dest = (unsigned char*)malloc( *destSize );
	memset( dest, 0, *destSize);

	// compress the source into the dest
	strm.avail_in = sourceSize;
	strm.next_in = (Bytef*) source;
	strm.avail_out = *destSize;
	strm.next_out = dest();

	ret = deflate(&strm, Z_FINISH); // we've given it plenty of output space
	if(ret != Z_STREAM_END){
		deflateEnd(&strm);
		throw AnException(0, FL, "deflate did not return Z_STREAM_END");
	}

	// Calculate how many bytes were written, by looking at how many bytes
	// are left over in the dest buffer:
	*destSize = *destSize - strm.avail_out;

	deflateEnd(&strm);
	return dest.release();
}
