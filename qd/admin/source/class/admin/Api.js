/* ************************************************************************

   Copyright: 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
/*
#asset(admin/ajax-loader-16.gif)
#asset(admin/icon/16x16/plain/server_delete.png)
#asset(admin/icon/16x16/plain/server_connection.png)

*/
qx.Class.define("admin.Api", {

	type : "static",

	statics : {
		/** This function will walk a admin response XML document and look for
		 * errors in it.  If errors are found, and the doAlert parameter is set
		 * to true, then we will alert to the user that errors were found.
		 * <p>
		 * Returns true if errors were found, and false if no errors were found.
		 *
		 */
		returnHasErrors : function ( response, doAlert, callback, theThis ) {
			if(response == null){
				if(doAlert){
					admin.Statics.doAlert("xmlhttp response is null!");
				}
				return true;
			}

			// Check the response for errors:
			var error_response = response.getAttribute("haserror");
			if(error_response !== null && error_response === "true"){
				if( doAlert ){
					var errors = response.getElementsByTagName('Errors')[0].getElementsByTagName('Error');
					var err_msg = "";
					for(var i = 0; i < errors.length; i++){
						err_msg = err_msg + errors[i].getAttribute('msg') + "\n\n";
					}
					if(errors.length > 1){
						admin.Statics.doAlert("Errors occurred during processing:<br/><br/>" +
							admin.Statics.formatSQLError(err_msg), "Alert", callback, theThis);
					} else {
						admin.Statics.doAlert("Error occurred during processing:<br/><br/>" +
							admin.Statics.formatSQLError(err_msg), "Alert", callback, theThis);
					}
				}
				return true;
			}

			return false;
		},

		/** This function will check a response from the server to see if it has a particular
		 * error message in it indicating that the user has not connected to the ViaSQL Server.
		 */
		returnRequiresDB : function ( response ) {
			if(response == null){
				return false;
			}

			// Check the response for an error that says:
			// Current session has not chosen a DB Connection yet.
			var error_response = response.getAttribute("haserror");
			if(error_response !== null && error_response === "true"){
				var errors = response.getElementsByTagName('Errors')[0].getElementsByTagName('Error');
				var err_msg = "";
				for(var i = 0; i < errors.length; i++){
					if(errors[i].getAttribute('msg') == "Current session has not chosen a DB Connection yet."){
						return true;
					}
				}
				// Didn't find our trigger text
				return false;
			}

			// No errors found
			return false;
		},

		returnIsLong : function(response, callback, theThis, errorCallback){
			if(response == null){
				return false;
			}

			// Check the current document to see if it is an LRTask
			if(response.nodeName !== "LRTask"){
				return false; // Not a long running task.
			}

			// We have a long running task.  We need to launch a progress dialog and poll the
			// server to wait for it to finish.
			var lrTask = new admin.sqldo.LRTask();
			lrTask.readFromXML( response );
			var tmpWindow = new admin.dialog.LRTaskDialog( lrTask, callback, errorCallback, theThis );
			qx.core.Init.getApplication().getRoot().add(tmpWindow);
			tmpWindow.open();

			// Tell our caller that they shouldn't worry about handling any other callbacks.
			return true;

		},

		activateNetworkIcon : function ( theThis ){
			if(qx.core.Init.getApplication()){
				if(qx.core.Init.getApplication().getRoot()) {
					qx.core.Init.getApplication().getRoot().setCursor("wait");
				}
			}
			if(theThis && theThis.toolbar && theThis.serverMenu ){
				theThis.serverMenu.setIcon("admin/ajax-loader-16.gif");
			}
		},

		deactivateNetworkIcon : function ( theThis ){
			if(qx.core.Init.getApplication()){
				qx.core.Init.getApplication().getRoot().setCursor("default");
			}
			if(theThis && theThis.toolbar && theThis.serverMenu){
				if (qx.lang.String.contains(theThis.serverMenu.getLabel(), "Not Connected")) {
					theThis.serverMenu.setIcon("admin/icon/16x16/plain/server_delete.png");
				} else {
					theThis.serverMenu.setIcon("admin/icon/16x16/plain/server_connection.png");
				}
			}
		},

		getResponseMessages : function (response){
			var messages = response.getElementsByTagName('Messages')[0].getElementsByTagName('Message');
			var resp_msg = "";
			for(var i = 0; i < messages.length; i++){
				// Response messages are in a CDATA child:
				resp_msg = resp_msg + messages[i].firstChild.data + "\n\n";
			}
			return resp_msg;
		},

		CheckNullResponse : function(requestName, req, theThis) {
			var response = req.responseXML.documentElement;
			if(response != null){
				return false; // nothing to worry about
			}

			theThis.error( requestName + ": null xml response received." );
			theThis.error( requestName + ": response headers:\n" + req.getAllResponseHeaders() );
			theThis.error( requestName + ": response text:\n" + req.responseText );

			return true;
		},

		/** This will setup our request, add all of the callbacks, and
		  * then send the request to the server.
		  */
		SendRequest : function( requestDoc, requestName, callback, theThis, errorCallback) {
			admin.Api.activateNetworkIcon( theThis );
			//var req = new qx.bom.Request;
			var req = new qx.bom.request.Xhr;
			req.onreadystatechange = qx.lang.Function.bind(function() {
				if(req.readyState != 4){
					return;
				}
				admin.Api.deactivateNetworkIcon( theThis );
				if(!req.responseXML){
					admin.Statics.doAlert("Server is not responding, please try again.");
					if(errorCallback){
						errorCallback.call(theThis, req);
					}
					return;
				}

				if(admin.Api.CheckNullResponse( requestName, req, theThis ) === true){
					if(theThis.ApiNestLevel === undefined){
						theThis.ApiNestLevel = 1;
					} else {
						theThis.ApiNestLevel ++;
					}
					if(theThis.ApiNestLevel > 5){
						admin.Statics.doAlert("Error communicating with server.<br/><br/>Request: " +
							requestName + "<br/><br/>Failed to receive a response from the server."
						);
						if(theThis){
							theThis.fireEvent( "apiCallFailed" );
						}
						return;
					}
					// resend the original request.
					admin.Api.SendRequest( requestDoc, requestName, callback, theThis, errorCallback);
					return;
				}

				var response = req.responseXML.documentElement;

				if( admin.Api.returnRequiresDB(response) ){
					// User has not yet chosen a server connection.  Prompt them to do so.
					admin.Api.ReAuthenticate(requestDoc, requestName, callback, theThis);
					return;
				}

				if(admin.Api.returnHasErrors( response, true, errorCallback, theThis) ){
					if(theThis){
						theThis.fireEvent( "apiCallFailed" );
					}
					return;
				}

				// Handle any long-running responses with a progress dialog
				if(admin.Api.returnIsLong( response, callback, theThis, errorCallback ) ) {
					return;
				}

				if(callback){
					callback.call(theThis, response );
				}
				if(theThis){
					theThis.fireEvent( "apiCallSucceeded" );
				}
			}, theThis);

			// Now send the request
			req.open("POST", requestName, true);
			req.send(admin.Statics.xmlDocToString(requestDoc));
		},

		/** This version will submit a simple GET request, but also sets up
		  * and handles the re-authentication as above.
		  */
		LoadXMLDoc : function( requestName, callback, theThis, errorCallback) {
			admin.Api.activateNetworkIcon( theThis );
			//var req = new qx.bom.Request;
			var req = new qx.bom.request.Xhr;
			req.onreadystatechange = qx.lang.Function.bind(function() {
				if(req.readyState != 4){
					return;
				}
				admin.Api.deactivateNetworkIcon( theThis );
				if(req.responseXML === null && req.responseText.indexOf("admin_LOG_ON") !== -1){
					// session has expired.  Re-authenticate the user:
					admin.Api.ReAuthenticate(null, requestName, callback, theThis);
					return;
				}

				var response = req.responseXML.documentElement;
				if(admin.Api.returnHasErrors( response, true) ){
					if(errorCallback){
						errorCallback.call(theThis, req);
					}
					return;
				}
				if(callback){
					callback.call(theThis, response );
				}
			}, theThis);

			// Now send the request
			req.open("POST", requestName, true);
			req.send(null);
		},

		/** This version will submit a simple GET request and return the response text.
		  * No error checking is done on the response document as we expect it to be plain text.
		  */
		LoadPlainDoc : function( requestName, callback, theThis) {
			admin.Api.activateNetworkIcon( theThis );
			var req = new qx.bom.request.Xhr;
			req.onreadystatechange = qx.lang.Function.bind(function() {
				if(req.readyState != 4){
					return;
				}
				admin.Api.deactivateNetworkIcon( theThis );
				var response = req.responseText;
				if(callback){
					callback.call(theThis, response );
				}
			}, theThis);

			// Now send the request
			req.open("POST", requestName, true);
			req.send(null);
		},


		/** This function is used to prompt a user to connect to the ViaSQL Server
		  * if they don't have a current DB connection ready on the server.
		  */
		ReAuthenticate : function (requestDoc, requestName, callback, theThis) {
			var windowTitle = "Connect to Ivory Hub Server";
			var tmpWindow = new admin.dialog.ServerConnectDialog(windowTitle);
			qx.core.Init.getApplication().getRoot().add(tmpWindow);

			tmpWindow.addOkEventListener( "execute", function() {
				var obj = new admin.sqldo.LogOn();
				obj.setHost( tmpWindow.hostField.getValue().toUpperCase() );
				obj.setPort( tmpWindow.portField.getValue() );
				obj.setUser( tmpWindow.userField.getValue().toUpperCase() );
				obj.setPass( tmpWindow.passField.getValue() );
				obj.setAlias( tmpWindow.aliasField.getValue() );

				admin.Api.ConnectToServer(obj,
				function(response){ // the success callback
					var objs = admin.sqldo.LogOn.readElementChildren(response);
					var app = qx.core.Init.getApplication();
					var menuLabel = objs[0].getConnName();
					app.serverMenu.setLabel( menuLabel );

					app.addToServerMenu( menuLabel );

					// resend the original request.
					if(requestDoc){
						admin.Api.SendRequest( requestDoc, requestName, callback, theThis);
					} else {
						admin.Api.LoadXMLDoc( requestName, callback, theThis );
					}
				}, null,
				function(){ // the error callback
					// Connection to a DB did not succeed.  Keep them in the loop until
					// they succeed or cancel.
					admin.Api.ReAuthenticate(requestDoc, requestName, callback, theThis);
				});
			});

			tmpWindow.open();
		},

		/** This function will call the /logic/utils/ConnectToServer
		  * server API.
		  */
		ConnectToServer : function ( inputObj,
			completionFunction, theThis, errorFunction
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "ConnectToServer");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/utils/ConnectToServer",
				completionFunction, theThis, errorFunction);
		},

		/** This function will call the ExecuteNamedQuery server API passing
		  * in a document that requires no input parameters.
		  */
		ExecuteNamedQuery0: function ( queryName,
			completionFunction, theThis
		) {
			//First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "ExecuteNamedQuery");
			var requestRoot = requestDoc.documentElement;
			requestRoot.setAttribute("queryname", queryName);

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/ExecuteNamedQuery",
				completionFunction, theThis);
		},

		/** This function will call the ExecuteNamedQuery server API passing
		  * in a document that requires one input parameter.
		  */
		ExecuteNamedQuery1: function ( queryName, inputName, inputValue,
			completionFunction, theThis
		) {
			//First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "ExecuteNamedQuery");
			var requestRoot = requestDoc.documentElement;
			requestRoot.setAttribute("queryname", queryName);
			var inputElem = requestDoc.createElement("Input");
			requestRoot.appendChild(inputElem);
			inputElem.setAttribute("name", inputName);
			inputElem.setAttribute("value", inputValue);

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/ExecuteNamedQuery",
				completionFunction, theThis);
		},

		/** This function will call the ExecuteNamedQuery server API passing
		  * in a document that requires two input parameter.
		  */
		ExecuteNamedQuery2: function ( queryName, inputName, inputValue,
			input2Name, input2Value,
			completionFunction, theThis
		) {
			//First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "ExecuteNamedQuery");
			var requestRoot = requestDoc.documentElement;
			requestRoot.setAttribute("queryname", queryName);
			// First input name/value
			var inputElem = requestDoc.createElement("Input");
			requestRoot.appendChild(inputElem);
			inputElem.setAttribute("name", inputName);
			inputElem.setAttribute("value", inputValue);
			// second input name/value
			inputElem = requestDoc.createElement("Input");
			requestRoot.appendChild(inputElem);
			inputElem.setAttribute("name", input2Name);
			inputElem.setAttribute("value", input2Value);

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/ExecuteNamedQuery",
				completionFunction, theThis);
		},

		/** This function will call the Authenticate server
		  * API and pass in the given arguments.
		  */
		Authenticate : function ( user, pass, dbname,
			completionFunction, theThis, errorFunction
		) {
			//First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "Authenticate");
			var requestRoot = requestDoc.documentElement;
			requestRoot.setAttribute("user", user);
			requestRoot.setAttribute("pass", pass);
			requestRoot.setAttribute("dbname", dbname);

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/Authenticate",
				completionFunction, theThis, errorFunction);
		},

		/** This function will call the UserProperties server API
		  */
		UserProperties : function ( setList, delList,
			theThis, finalCallback
		) {
			var requestDoc = qx.xml.Document.create(null, "UserProperties");
			var requestRoot = requestDoc.documentElement;

			for (var n in setList) {
				if (setList.hasOwnProperty(n)) {
					var elem = requestDoc.createElement("SetProperty");
					requestRoot.appendChild(elem);
					elem.setAttribute("name", n);
					elem.setAttribute("value", setList[n] );
				}
			}

			for (var n in delList) {
				if (delList.hasOwnProperty(n)) {
					var elem = requestDoc.createElement("DelProperty");
					requestRoot.appendChild(elem);
					elem.setAttribute("name", n);
					elem.setAttribute("value", delList[n] );
				}
			}

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/UserProperties",
			// User properties always use the same completion function.
			// They always get stored in our global singleton so that everyone
			// can see and use them.
			function(response) {
				// store the return in our admin.Singleton.userProperties:
				var single = admin.Singleton.getInstance();
				single.setUserProperties( {} );
				var props = single.getUserProperties();
				var elem_list  = response.getElementsByTagName('Property');
				for(var i = 0; i < elem_list.length; i++){
					var elem = elem_list[i];
					props[ elem.getAttribute("name") ] = elem.getAttribute("value");
				}

				if(finalCallback){
					finalCallback.call(theThis);
				}

			}, theThis);
		},

		/** This function will call the SystemProperties server API
		  */
		SystemProperties : function (
			theThis, finalCallback
		) {
			var requestDoc = qx.xml.Document.create(null, "SystemProperties");
			var requestRoot = requestDoc.documentElement;

			admin.Api.SendRequest(requestDoc, "/SystemProperties",
			// System properties always use the same completion function.
			// They always get stored in our global singleton so that everyone
			// can see and use them.
			function(response) {
				// store the return in our admin.Singleton.systemProperties:
				var single = admin.Singleton.getInstance();
				var props = single.getSystemProperties();
				var elem_list  = response.getElementsByTagName('SystemProperty');
				for(var i = 0; i < elem_list.length; i++){
					var elem = elem_list[i];
					props[ elem.getAttribute("name") ] = elem.getAttribute("value");
				}

				if(finalCallback){
					finalCallback.call(theThis);
				}

			}, theThis);
		},

		/** This function will call the SaveLayout server API
		  */
		SaveLayout : function ( layoutDoc, layoutName,
			completionFunction, theThis
		) {
			var requestRoot = layoutDoc.documentElement;
			requestRoot.setAttribute("filename", layoutName);

			// Now send the request to the server.
			admin.Api.SendRequest(layoutDoc, "/logic/utils/SaveLayout",
				completionFunction, theThis);
		},


		/* ******************************************************************** */
		/* Everything above this point is hand-coded and meant to be sourced    */
		/* from Api.base.js.  Everything below this point is added during the   */
		/* code generation process at build time.  Do not edit anything below   */
		/* this point, and do not edit this file if it is Api.js.  Edit the     */
		/* Api.base.js version.                                                 */
		/* ******************************************************************** */



		/** This function will call the /logic/dev/GetProject
		  * server API.
		  */
		GetProject : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetProject");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/dev/GetProject",
				completionFunction, theThis);
		},

		/** This function will call the /logic/dev/GetProjectList
		  * server API.
		  */
		GetProjectList : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetProjectList");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/dev/GetProjectList",
				completionFunction, theThis);
		},

		/** This function will call the /logic/dev/SaveProject
		  * server API.
		  */
		SaveProject : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "SaveProject");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/dev/SaveProject",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/CleanoutLRTask
		  * server API.
		  */
		CleanoutLRTask : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "CleanoutLRTask");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/CleanoutLRTask",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/CloseConnection
		  * server API.
		  */
		CloseConnection : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "CloseConnection");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/CloseConnection",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/ExecuteGenericSQL
		  * server API.
		  */
		ExecuteGenericSQL : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "ExecuteGenericSQL");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/ExecuteGenericSQL",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/FindLogMessage
		  * server API.
		  */
		FindLogMessage : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "FindLogMessage");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/FindLogMessage",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetAllLayouts
		  * server API.
		  */
		GetAllLayouts : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetAllLayouts");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetAllLayouts",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetAllLRTasks
		  * server API.
		  */
		GetAllLRTasks : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetAllLRTasks");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetAllLRTasks",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetHitMap
		  * server API.
		  */
		GetHitMap : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetHitMap");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetHitMap",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetLogFiles
		  * server API.
		  */
		GetLogFiles : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetLogFiles");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetLogFiles",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetLogMessages
		  * server API.
		  */
		GetLogMessages : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetLogMessages");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetLogMessages",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetLogMessagesByRange
		  * server API.
		  */
		GetLogMessagesByRange : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetLogMessagesByRange");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetLogMessagesByRange",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetLogMsgCount
		  * server API.
		  */
		GetLogMsgCount : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetLogMsgCount");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetLogMsgCount",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetLogSettings
		  * server API.
		  */
		GetLogSettings : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetLogSettings");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetLogSettings",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetOneLRTask
		  * server API.
		  */
		GetOneLRTask : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetOneLRTask");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetOneLRTask",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/GetProfile
		  * server API.
		  */
		GetProfile : function (
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "GetProfile");

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/GetProfile",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/SaveLogMsg
		  * server API.
		  */
		SaveLogMsg : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "SaveLogMsg");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/SaveLogMsg",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/SwitchServerConnection
		  * server API.
		  */
		SwitchServerConnection : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "SwitchServerConnection");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/SwitchServerConnection",
				completionFunction, theThis);
		},

		/** This function will call the /logic/util/UpdateLogSettings
		  * server API.
		  */
		UpdateLogSettings : function ( inputObj,
			completionFunction, theThis
		){
			// First build the request XML Document
			var requestDoc = qx.xml.Document.create(null, "UpdateLogSettings");
			var requestRoot = requestDoc.documentElement;
			inputObj.createXMLElement( requestRoot );

			// Now send the request to the server.
			admin.Api.SendRequest(requestDoc, "/logic/util/UpdateLogSettings",
				completionFunction, theThis);
		},

		// Dummy function to end the file
		DontUseDummyFunction : function ()
		{

		}

	}
});
