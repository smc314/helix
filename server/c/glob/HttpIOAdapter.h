/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef HTTPIOADAPTER_H
#define HTTPIOADAPTER_H

#include "IOAdapter.h"
#include "mongoose.h"

namespace Helix {
namespace Glob {


/**
 * This class is the implementation of IOAdapter for the Http
 * protocol.  This provides access to Http inbound and outbound communications.
 *
 * @author Steven M. Cherry
 */
class DLLEXPORT HttpIOAdapter : public IOAdapter 
{

	public:
		/// Standard Constructor:
		HttpIOAdapter();

		/// Standard destructor:
		virtual ~HttpIOAdapter();

		/// We implement the Init method:
		virtual void Init(xmlNodePtr node);

		/// We implement the Execute method:
		virtual void Execute(void);

		/// This is our mongoose callback function:
		static void* HandleInbound(enum mg_event event, struct mg_connection* conn, 
			const struct mg_request_info* request_info);

	protected:

		/// our adapter name
		twine m_name;

		/// our port number to listen on
		int m_port;

		/// Our local ip to listen on
		twine m_local_ip;
		
		/// Whether we should use a secure listener or not.
		bool m_use_secure;
		
		/// Which httpDomain (if any) should be used when setting up cookies.
		twine m_httpDomain;

		/// Where is the ssl certificate that we should use
		twine m_sslCert;

		/// Mongoose server context:
		struct mg_context* m_ctx;

		/// At what point should we start compressing return data?
		int m_compressionThreshold;

		/// How many threads should we let mongoose startup?
		int m_threads;

		/// Whether or not we have keepalive enabled.
		twine m_keepalive;

	private:

		/// Standard copy constructor.  Private to prevent use
		HttpIOAdapter(const HttpIOAdapter& c) {}

		/// Standard assignment operator. Private to prevent use
		HttpIOAdapter& operator=(const HttpIOAdapter& c) {return *this;}

	public:
		// Registers us with the global factory map:
		static IOAdapterRegister<HttpIOAdapter> reg;
	
};


}} // End Namespace Helix::Glob

#endif // HTTPIOADAPTER_H Defined
