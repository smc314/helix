/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef SCHEDCONN_H
#define SCHEDCONN_H

#include "IOConn.h"

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

namespace Helix {
namespace Glob {


/** This class defines the internal/scheduler version of the IOConn object.
*
* @author Steven M. Cherry
*/
class SchedConn : public IOConn 
{

	protected:
		/// The message that we read from the soap connection.
		xmlDocPtr m_doc;
		bool m_doc_loaded;
	
		twine m_sessionid;
		bool m_sessionid_loaded;

		twine m_msg_target;

		/// Copy constructor is private to prevent use:
		SchedConn(const SchedConn& c) { }

		/// Copy operator is private to prevent use:
		SchedConn& operator=(const SchedConn& c) { return *this; }

	public:
		
		/** Default constructor */
		SchedConn(const twine& msgTarget, xmlDocPtr msg);

		/// Standard Destructor
		virtual ~SchedConn();

		/** This allows the processing logic to query the connection
		  * to find out what message target should be used to process
		  * it.
		  */
		virtual twine MsgTarget();

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

};

}} // End Namespace Helix::Glob

#endif // SCHEDCONN_H defined
