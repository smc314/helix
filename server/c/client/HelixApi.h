#ifndef HELIXAPI_H
#define HELIXAPI_H

#include <twine.h>
#include <Log.h>
#include <EnEx.h>
#include <dptr.h>
#include <sptr.h>
#include <HttpClient.h>
#include <xmlinc.h>
using namespace SLib;

// We need references to every single data object class here:
#include <Api.h>
#include <Application.h>
#include <DOChild.h>
#include <DOStmt.h>
#include <DOStmtInput.h>
#include <DOStmtOutput.h>
#include <DObject.h>
#include <HitMap.h>
#include <LRTask.h>
#include <LogMessageFilter.h>
#include <LogObj.h>
#include <LogOn.h>
#include <LogSettings.h>
#include <Project.h>
#include <ProjectData.h>
#include <ProjectTable.h>
#include <SQLStatement.h>
#include <SchedItem.h>
#include <Screen.h>
#include <TableCol.h>
//using namespace Helix::Logic::admin;
using namespace Helix::Logic::dev;
//using namespace Helix::Logic::test;
using namespace Helix::Logic::util;

namespace Helix {
namespace Client {

/** This API represents the C++ interface to the Hub server.  All API's that are
* available to the Javascript client are also available here, and re-generated
* each time the Hub is compiled.  Do Not Edit This Class directly.  Update the
* code generator and make your edits there.
*/
class HelixApi : public HttpClient
{
	public:

		/// Default Constructor requires the host and port of the Hub to which you want to connect.
		HelixApi(const twine& host, int port, bool useSSL = false);

		/// Standard destructor
		virtual ~HelixApi();
		/**
		  * We override this method from the base class to allow us to track progress
		  * and update internal long running task status values appropriately.
		  */
		virtual int Progress(double dltotal, double dlnow, double ultotal, double ulnow);

		/**
		  * Used to check the response from the Hub to see if it has errors.  Any errors found
		  * will be converted into exceptions that are then thrown from this method.
		  */
		void returnHasErrors();

		/**
		  * Checks to see if the return from the Hub is indicating that a DB connection
		  * is required to perform the requested action.
		  */
		bool returnRequiresDB();

		/**
		  * Sends a POST request to the Hub and checks the response for errors.
		  */
		xmlDocPtr SendRequest( xmlDocPtr req, const twine& requestName );

		/**
		  * Sends a GET request to the Hub and checks the response for errors.
		  */
		xmlDocPtr LoadXMLDoc( const twine& requestName );

		/**
		  * Sends a GET request to the Hub and does no response checking - use this for
		  * requesting static content from the Hub such as web pages, images, etc.  Note,
		  * this is an override of the HttpClient::Get method, where we change the
		  * understanding of the input requestPath.  We do not require it to be a full URL, but
		  * will build the URL based on the input host/port setup when creating this HelixApi
		  * object.
		  */
		virtual char* Get( const twine& requestPath );

		/**
		  * Sends a POST request to the Hub and expects to download the response as a binary
		  * payload.  Note, this is an override of the HttpClient::PostRaw method, where we change the
		  * understanding of the input requestPath.  We do not require it to be a full URL, but
		  * will build the URL based on the input host/port setup when creating this HelixApi
		  * object.
		  */
		virtual char* PostRaw( const twine& requestPath, const char* msg, size_t msgLen );

		/**
		  * Allows the caller to retrieve our response document to directly examine anything of
		  * interest to them.
		  */
		xmlDocPtr ResponseDoc() { return m_response; }

		/**
		  * When used internally by the Hub itself, this allows the invoker of this API to
		  * tell us about a Long Running Task ID that we should update as our download
		  * progresses.
		  */
		void SetLRTaskID( const twine& lrTaskID );

	private:

		/// Copy constructor is private to prevent use
		HelixApi(const HelixApi& c) {}

		/// Assignment operator is private to prevent use
		HelixApi& operator=(const HelixApi& c) {return *this;}

		/// Our target hub host name
		twine m_host;

		/// Our target hub port number
		int m_port;

		/// Whether we should use an SSL connection
		bool m_use_ssl;

		/// Our response document
		sptr<xmlDoc, xmlFreeDoc> m_response;

		/// Our long running task ID
		twine m_lr_task_id;

	/* ******************************************************************************* */
	/* This section declares all of the public api's that we provide for communicating */
	/* with the Hub.                                                                   */
	/* ******************************************************************************* */
	public:

		/** This method will call the /logic/dev/GetProject
		  * server API.
		  */
		xmlDocPtr GetProject( const Project& dataObj );

		/** This method will call the /logic/dev/GetProjectList
		  * server API.
		  */
		xmlDocPtr GetProjectList( );

		/** This method will call the /logic/dev/SaveProject
		  * server API.
		  */
		xmlDocPtr SaveProject( const Project& dataObj );

		/** This method will call the /logic/util/CleanoutLRTask
		  * server API.
		  */
		xmlDocPtr CleanoutLRTask( const LRTask& dataObj );

		/** This method will call the /logic/util/CloseConnection
		  * server API.
		  */
		xmlDocPtr CloseConnection( );

		/** This method will call the /logic/util/ExecuteGenericSQL
		  * server API.
		  */
		xmlDocPtr ExecuteGenericSQL( const SQLStatement& dataObj );

		/** This method will call the /logic/util/FindLogMessage
		  * server API.
		  */
		xmlDocPtr FindLogMessage( const LogMessageFilter& dataObj );

		/** This method will call the /logic/util/GetAllLayouts
		  * server API.
		  */
		xmlDocPtr GetAllLayouts( );

		/** This method will call the /logic/util/GetAllLRTasks
		  * server API.
		  */
		xmlDocPtr GetAllLRTasks( );

		/** This method will call the /logic/util/GetHitMap
		  * server API.
		  */
		xmlDocPtr GetHitMap( );

		/** This method will call the /logic/util/GetLogFiles
		  * server API.
		  */
		xmlDocPtr GetLogFiles( );

		/** This method will call the /logic/util/GetLogMessages
		  * server API.
		  */
		xmlDocPtr GetLogMessages( const LogMessageFilter& dataObj );

		/** This method will call the /logic/util/GetLogMessagesByRange
		  * server API.
		  */
		xmlDocPtr GetLogMessagesByRange( const LogMessageFilter& dataObj );

		/** This method will call the /logic/util/GetLogMsgCount
		  * server API.
		  */
		xmlDocPtr GetLogMsgCount( const LogMessageFilter& dataObj );

		/** This method will call the /logic/util/GetLogSettings
		  * server API.
		  */
		xmlDocPtr GetLogSettings( );

		/** This method will call the /logic/util/GetOneLRTask
		  * server API.
		  */
		xmlDocPtr GetOneLRTask( const LRTask& dataObj );

		/** This method will call the /logic/util/GetProfile
		  * server API.
		  */
		xmlDocPtr GetProfile( );

		/** This method will call the /logic/util/SaveLogMsg
		  * server API.
		  */
		xmlDocPtr SaveLogMsg( const LogObj& dataObj );

		/** This method will call the /logic/util/SwitchServerConnection
		  * server API.
		  */
		xmlDocPtr SwitchServerConnection( const LogOn& dataObj );

		/** This method will call the /logic/util/UpdateLogSettings
		  * server API.
		  */
		xmlDocPtr UpdateLogSettings( const LogSettings& dataObj );


}; // End HelixApi class

} } // End Helix::Client namespace stack

#endif // HELIXAPI_H Defined
