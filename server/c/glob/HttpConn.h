/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef HTTPCONN_H
#define HTTPCONN_H

#include "IOConn.h"
#include "mongoose.h"

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

namespace Helix {
namespace Glob {


/** This class defines the Http version of the IOConn object.
*
* @author Steven M. Cherry
*/
class HttpConn : public IOConn 
{

	protected:
		/// The structures from mongoose that represent the connection:
		enum mg_event m_event;
		struct mg_connection* m_conn;
		const struct mg_request_info* m_ri;


		/** Whether or not our connections are secure */
		bool m_use_ssl;
	
		/** Which http domain to use in cookies */
		twine m_httpDomain;
	
		/// The message that we read from the soap connection.
		xmlDocPtr m_doc;
		bool m_doc_loaded;
	
		twine m_sessionid;
		bool m_sessionid_loaded;

		bool m_compression_ok;
		int m_compressionThreshold;

		bool m_keepalive;

		twine m_sessionCookie;
	
		/// Copy constructor is private to prevent use:
		HttpConn(const HttpConn& c) { }

		/// Copy operator is private to prevent use:
		HttpConn& operator=(const HttpConn& c) { return *this; }

	public:
		
		/** Default constructor */
		HttpConn(enum mg_event event, struct mg_connection* conn, 
			const struct mg_request_info* ri, int compressionThreshold, bool keepalive);

		/// Standard Destructor
		virtual ~HttpConn();

		/** This allows the processing logic to query the connection
		  * to find out what message target should be used to process
		  * it.
		  */
		virtual twine MsgTarget();

		/** This will retrieve the Session ID from the inbound message.  If
		 * there is no session id on the inbound message, this will return null.
		 */
		virtual twine getSessionID();
	
		/** This will set a new session id in the response document.  The client will
		 * use this for all further communications with the server.
		 */
		virtual void setSessionID(const twine newSession);

		/** When GetMsg is called, the IOConn object is responsible
		  * for presenting the contents of the inbound message to
		  * the caller as an XML document.  This allows the processing
		  * mechanisms to be standardized to XML and not have to worry
		  * about the specifics of the communications protocol.
		  */
		virtual xmlDocPtr GetMsg();
	
		/** This returns the root element of the input Request message.
		 */
		virtual xmlNodePtr GetRequestRoot(void);

		/** SendReturn is used by the processing logic to send the
		  * return response back to the original caller.  The IOConn
		  * object is responsible for knowing how to do this, and if
		  * no response is actually necessary, IOConn is responsible
		  * for silently eating the message at this point.
		  */
		virtual void SendReturn();

		/** This version of SendReturn is used to send back binary data
		 * that is not an XML document to the caller.  This is used for
		 * serving static HTML pages, e.g.
		 */
		virtual void SendReturn(unsigned char* data, int dataLen, twine fileName, Date lastModified, 
			Date expires);

		/** This version of SendReturn is used to send back binary data
		 * for files that are too large to read in all at once and send back.
		 */
		virtual void SendReturn(twine& filePath, twine& fileName, Date lastModified, Date expires);

		/** SendError is used by the processing logic to send an error
		  * return response back to the original caller.  The IOConn
		  * object is responsible for knowing how to do this, and if
		  * no response is actually necessary, IOConn is responsible
		  * for silently eating the message at this point.
		  */
		virtual void SendError();
	
		virtual void SendNotFound();

		virtual void SendNotModified();

		virtual void SendRedirect( twine redirectTarget ) ;

		twine getHttpDomain();

		static const twine& GetMimeType(twine& fileName);

		Date GetIfModifiedSince(void);

		/** This method uses zlib to implement gzip compression.
		 */
		unsigned char* CompressData(long* destSize, const unsigned char* source, long sourceSize);

		void WriteDataResponse(const unsigned char* data, long dataLen, const twine& mimeType);
};

}} // End Namespace Helix::Glob

#endif // HTTPCONN_H defined
