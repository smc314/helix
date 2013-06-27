/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
qx.Class.define("PACKAGE.test.TestStatics", {

	type: "static",

	statics: {

		/** We need a hand-full of synchronous requests to go back and forth to the server.  We
		 * re-implement PACKAGE.Api.SendRequest in order to accomplish this.
		 */
		SendRequest : function (requestDoc, requestName){

			var resp = null;
			var req = new qx.bom.request.Xhr;
			req.onreadystatechange = qx.lang.Function.bind(function() {
				if(req.readyState != 4){
					return;
				}
				if(!req.responseXML){
					PACKAGE.Statics.doAlert("Server is not responding.");
					return;
				}
				resp = req.responseXML.documentElement;

				if(PACKAGE.Api.returnRequiresDB(resp)){
					PACKAGE.Statics.doAlert("No DB Connection Available.  Log in in the real app, then run this test again.");
					return;
				}
				if(PACKAGE.Api.returnHasErrors(resp, true, null, null)){
					return;
				}
			});
			req.open("POST", requestName, false); // don't use async
			req.send(PACKAGE.Statics.xmlDocToString(requestDoc));
			return resp;
		},

		SetServerConnection : function( host, port, user, pass) {
			var serverMenu = qx.core.Init.getApplication().serverMenu;
			var menu = serverMenu.getMenu();
			var children = menu.getChildren();
			// push the "New Connection..." button:
			for(var i = 0, l = children.length; i < l; i++){
				if(children[i].getLabel() === "New Connection..."){
					children[i].execute();
					break;
				}
			}

			// wait for the dialog to show up:
			PACKAGE.test.TestStatics.waitForDialog( "Connect to Ivory Hub Server", function(dialog){
				dialog.hostField.setValue( host );
				dialog.portField.setValue( port );
				dialog.userField.setValue( user );
				dialog.passField.setValue( pass );
				dialog.aliasField.setValue( "" );
				dialog.ok_btn.execute();
			}, null);
		},

		SetServerConnectionNoApp : function( host, port, user, pass) {

			var obj = new PACKAGE.sqldo.LogOn();
			obj.setHost( host );
			obj.setPort( port );
			obj.setUser( user );
			obj.setPass( pass );

			var requestDoc = qx.xml.Document.create(null, "ConnectToServer");
			var requestRoot = requestDoc.documentElement;
			obj.createXMLElement( requestRoot );
			PACKAGE.test.TestStatics.SendRequest(requestDoc, "/logic/utils/ConnectToServer");
		},

		SwitchServerConnection : function( connName ){
			var obj = new PACKAGE.sqldo.LogOn;
			obj.setConnName( connName );

			var requestDoc = qx.xml.Document.create(null, "SwitchServerConnection");
			var requestRoot = requestDoc.documentElement;
			obj.createXMLElement( requestRoot );
			PACKAGE.test.TestStatics.SendRequest(requestDoc, "/logic/utils/SwitchServerConnection");
		},

		selectBrowserTab : function( tabName ) {
			PACKAGE.test.TestStatics.selectTabViewPage( qx.core.Init.getApplication().treeTabs, tabName );
		},

		selectEditor : function( editorName ) {
			PACKAGE.test.TestStatics.selectTabViewPage( qx.core.Init.getApplication().tabView, editorName );
		},

		selectEditorTab : function( editor, tabName ) {
			PACKAGE.test.TestStatics.selectTabViewPage( editor.tabview, tabName );
		},

		selectTabViewPage : function( tabView, pageName ){
			var pages = tabView.getChildren();
			for(var i = 0, l = pages.length; i < l; i++){
				if(pages[i].getLabel().indexOf( pageName ) === 0 ){ // use this to do "startsWith()"
					tabView.setSelection( [pages[i]] );
					return;
				}
			}
			throw String("Tab Page Not Found: " + pageName);
		},

		selectToolsMenuItem : function( primary, secondary) {
			var toolsmenu = qx.core.Init.getApplication().menu;
			var children = toolsmenu.getChildren();
			for(var i = 0, l = children.length; i < l; i++){
				if((children[i] instanceof qx.ui.menu.Button) && (children[i].getLabel() === primary)){
					children[i].execute();
					if(secondary !== undefined && secondary !== null){
						var grandChildren = children[i].getMenu().getChildren();
						for(var j = 0, m = grandChildren.length; j < m; j++){
							if((grandChildren[j] instanceof qx.ui.menu.Button) &&
								(grandChildren[j].getLabel() === secondary)
							){
								grandChildren[j].execute();
								break;
							}
						}
					}
					break;
				}
			}
		},

		waitForDialog : function( title, callBack, theThis ){
			// Check to see if the dialog is present:
			var dialog = PACKAGE.test.TestStatics.findDialog( title );
			if(dialog !== null ){
				// found it
				callBack.call( theThis, dialog );
				return;
			}

			// If not, then wait for 1/2 second and try again:
			qx.event.Timer.once( function() {
				PACKAGE.test.TestStatics.waitForDialog( title, callBack, theThis );
			}, theThis, 100 );
		},

		waitForMessageDialog : function( title, callBack, theThis ){
			// Check to see if the dialog is present:
			var dialog = PACKAGE.test.TestStatics.findMessageDialog( title );
			if(dialog !== null ){
				// found it
				callBack.call( theThis, dialog );
				return;
			}

			// If not, then wait for 1/2 second and try again:
			qx.event.Timer.once( function() {
				PACKAGE.test.TestStatics.waitForMessageDialog( title, callBack, theThis );
			}, theThis, 100 );
		},

		findDialog : function( title ) {

			var rootChildren = qx.core.Init.getApplication().getRoot().getChildren();
			for(var i = 0, l = rootChildren.length; i < l; i++){
				var child = rootChildren[i];
				if(child instanceof qx.ui.window.Window ){
					if(title !== null && title !== undefined){
						// Check the title against the window caption.
						var caption = child.getCaption();
						if(caption.indexOf( title ) !== -1){
							return child;
						}
					} else {
						// title not provided, just return the first window we find.
						return child;
					}
				}
			}
			return null; // Message Dialog not found.
		},

		findMessageDialog : function( title ) {

			var rootChildren = qx.core.Init.getApplication().getRoot().getChildren();
			for(var i = 0, l = rootChildren.length; i < l; i++){
				var child = rootChildren[i];
				if(child instanceof PACKAGE.dialog.MessageDialog ){
					if(title !== null && title !== undefined){
						// Check the title against the window caption.
						var caption = child.getCaption();
						if(caption.indexOf( title ) !== -1){
							return child;
						}
					} else {
						// title not provided, just return the first window we find.
						return child;
					}
				}
			}
			return null; // Message Dialog not found.
		},

		/**
		  * Uses the standard qx locators to find an object and then calculate its position
		  * and size and take a screen shot of it. 
		  * <p>
		  * Contrast this with the captureScreenshot command, which captures the
		  * contents of the OS viewport (i.e. whatever is currently being displayed
		  * on the monitor), and is implemented in the RC only. Currently this only
		  * works in Firefox when running in chrome mode, and in IE non-HTA using
		  * the EXPERIMENTAL "Snapsie" utility. The Firefox implementation is mostly
		  * borrowed from the Screengrab! Firefox extension. Please see
		  * http://www.screengrab.org and http://snapsie.sourceforge.net/ for
		  * details.
		  * <p>
		  * Note: This does not work.  It must be run by a firefox extension like selenium
		  * which controls loading of the page and runs with elevated privileges.  Running
		  * directly from within a webpage like this is expressly forbidden by the firefox
		  * code.
		  * 
		  * @type member
		  * @param locator {var} an element locator 
		  * @param filename  the path to the file to persist the screenshot as. No
		  *                  filename extension will be appended by default.
		  *                  Directories will not be created if they do not exist,  
		  *                  and an exception will be thrown, possibly by native
		  *                  code.
		  * @return {void}  
		  */
		doCaptureComponentScreenshot : function(qxObject, filename) {

			// Get the width and height of the object:
			var qxMap = qxObject.getBounds();
			qxObject.debug("qx says left=" + qxMap.left + ", top=" + qxMap.top 
				+ ", width=" + qxMap.width + ", height=" + qxMap.height );

			// do or do not ... there is no try
			var grabber = {
				prepareCanvas: function(width, height) {
					var styleWidth = width + 'px';
					var styleHeight = height + 'px';

					var grabCanvas = document.getElementById('screenshot_canvas');
					if (!grabCanvas) {
						// create the canvas
						var ns = 'http://www.w3.org/1999/xhtml';
						grabCanvas = document.createElementNS(ns, 'html:canvas');
						grabCanvas.id = 'screenshot_canvas';
						grabCanvas.style.display = 'none';
						document.documentElement.appendChild(grabCanvas);
						//element.appendChild(grabCanvas);
					}

					grabCanvas.width = width;
					grabCanvas.style.width = styleWidth;
					grabCanvas.style.maxWidth = styleWidth;
					grabCanvas.height = height;
					grabCanvas.style.height = styleHeight;
					grabCanvas.style.maxHeight = styleHeight;

					return grabCanvas;
				},

				prepareContext: function(canvas, box) {
					var context = canvas.getContext('2d');
					context.clearRect(box.x, box.y, box.width, box.height);
					context.save();
					return context;
				}
			};

			var SGNsUtils = {
				dataUrlToBinaryInputStream: function(dataUrl) {
					var nsIoService = Components.classes["@mozilla.org/network/io-service;1"]
						.getService(Components.interfaces.nsIIOService);
					var channel = nsIoService
						.newChannelFromURI(nsIoService.newURI(dataUrl, null, null));
					var binaryInputStream = Components.classes["@mozilla.org/binaryinputstream;1"]
						.createInstance(Components.interfaces.nsIBinaryInputStream);

					binaryInputStream.setInputStream(channel.open());
					return binaryInputStream;
				},

				newFileOutputStream: function(nsFile) {
					var writeFlag = 0x02; // write only
					var createFlag = 0x08; // create
					var truncateFlag = 0x20; // truncate
					var fileOutputStream = Components.classes["@mozilla.org/network/file-output-stream;1"]
						.createInstance(Components.interfaces.nsIFileOutputStream);

					fileOutputStream.init(nsFile, writeFlag | createFlag | truncateFlag, 0664, null);
					return fileOutputStream;
				},

				writeBinaryInputStreamToFileOutputStream: function(binaryInputStream, fileOutputStream) {
					var numBytes = binaryInputStream.available();
					var bytes = binaryInputStream.readBytes(numBytes);
					fileOutputStream.write(bytes, numBytes);
				}
			};

			// compute dimensions
			//var window = this.browserbot.getCurrentWindow();
			//var doc = window.document.documentElement;
			var box = {
				x: qxMap.left,
				y: qxMap.top,
				width: qxMap.width,
				height: qxMap.height
			};
			qxObject.info('computed dimensions x(' + box.x + ') y(' + box.y + ') width(' + box.width + ') height(' + box.height + ')');

			// grab
			var format = 'png';
			var canvas = grabber.prepareCanvas(box.width, box.height);
			var context = grabber.prepareContext(canvas, box);
			context.drawWindow(window.top, box.x, box.y, box.width, box.height, 'rgb(0, 0, 0)');
			context.restore();
			var dataUrl = canvas.toDataURL("image/" + format);
			qxObject.debug('grabbed to canvas');

			// save to file
			var nsFile = Components.classes["@mozilla.org/file/local;1"]
				.createInstance(Components.interfaces.nsILocalFile);
			try {
				nsFile.initWithPath(filename);
			} catch (e) {
				if (/NS_ERROR_FILE_UNRECOGNIZED_PATH/.test(e.message)) {
					// try using the opposite file separator
					if (filename.indexOf('/') != -1) {
						filename = filename.replace(/\//g, '\\');
					} else {
						filename = filename.replace(/\\/g, '/');
					}
					nsFile.initWithPath(filename);
				} else {
					throw e;
				}
			}
			var binaryInputStream = SGNsUtils.dataUrlToBinaryInputStream(dataUrl);
			var fileOutputStream = SGNsUtils.newFileOutputStream(nsFile);
			SGNsUtils.writeBinaryInputStreamToFileOutputStream(binaryInputStream,
			fileOutputStream);
			fileOutputStream.close();
			qxObject.debug('saved to file');

		}
	}
});
