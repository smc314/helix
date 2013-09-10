/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(welcome/icon/64x64/shadow/server_to_client.png)
************************************************************************ */


/** This class defines a dialog that presents a list box
  * to the user.  You can set the window title, icon, and label to customize
  * the presentation of the window.
  */
qx.Class.define("welcome.dialog.LRTaskDialog", {
	extend : welcome.dialog.OKDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( lrTask, callback, errorCallback, callbackThis ) {
		this.lrTask = lrTask;
		this.icon = "welcome/icon/64x64/shadow/server_to_client.png";
		this.label = "The Server is working on your request...";

		// Call the parent constructor:
		this.base( arguments, this.lrTask.getTaskName());

		this.ok_btn.setLabel( "Close" );
		this.callback = callback;
		this.callbackThis = callbackThis;
		this.errorCallback = errorCallback;

		// Setup our timer to continually call this.runLongPoll;
		this.timer = qx.util.TimerManager.getInstance();
		this.timerID = this.timer.start( this.runLongPoll, 1000, this, null, 1000 );
		this.debug("timer started");

		this.ok_btn.addListener("execute", function() { this.timer.stop( this.timerID ); }, this );
	},

	members : {

		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function () {
			this.setWidth(400);
			this.setHeight(200);
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {
			var a1 = new qx.ui.basic.Atom(this.label, this.icon );
			layout.add(a1);


			this.pb = new qx.ui.indicator.ProgressBar(this.lrTask.getTaskStart(),
				this.lrTask.getTaskFinish() );
			this.pb_label = new qx.ui.basic.Label( this.lrTask.getTaskMsg() );
			layout.add( this.pb );
			layout.add( this.pb_label );

		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {
		},

		/** This loop will poll the server and update the progress bar with information
		  * about our long running task on the server.  When it is complete, we'll call
		  * the original call-back with the final response document.
		  */
		runLongPoll : function(userData, timerId) {
			this.debug("runLongPoll");

			// We have to send the requests directly rather than going through Api.SendRequest, because
			// we will handle the LRTask objects comming back during the interim of the long running
			// task.  If we used Api.SendRequest, it would end up opening another instance of us for
			// each LRTask object that it received.

			var req = new qx.bom.request.Xhr;
			req.onreadystatechange = qx.lang.Function.bind( function() {
				if(req.readyState != 4){
					return; // not ready yet
				}
				this.debug("readystatechange");

				if(!req.responseXML){
					this.debug("no response xml");
					welcome.Statics.doAlert("Server is not responding, please try again");
					this.timer.stop( timerId ); // stop our timer to prevent further calls to this method
					this.okPressed = false;
					this.close();
					if(this.errorCallback){
						this.errorCallback.call( this.errorThis, req );
					}
					return;
				}

				var response = req.responseXML.documentElement;

				if(welcome.Api.returnHasErrors( response, true, this.errorCallback, this.callbackThis ) ){
					this.debug("response has errors");
					this.timer.stop( timerId ); // stop our timer to prevent further calls to this method
					this.okPressed = false;
					this.close();
					if(this.errorCallback){
						this.errorCallback.call( this.callbackThis, req );
					}
					return;
				}

				if(response.nodeName === "GetOneLRTask"){
					this.debug("node name is GetOneLRTask");
					// This is still our long running task.  Update our progress bar with new information
					var objectList = welcome.sqldo.LRTask.readElementChildren( response );
					if(objectList.length !== 0){
						this.lrTask = objectList[0];

						this.pb.setMaximum( this.lrTask.getTaskFinish() );
						this.pb.setValue( this.lrTask.getTaskCurrent() );
						this.pb_label.setValue( this.lrTask.getTaskMsg() );
					}

				} else {
					// The long running task has completed, and now we have the correct response.  Call
					// the original callback and fire the apiCallSucceeded event
					this.debug("node name is not GetOneLRTask: " + response.nodeName );
					this.timer.stop( timerId ); // stop our timer to prevent further calls to this method
					this.ok_btn.press();
					this.ok_btn.execute();
					if(this.callback){
						this.callback.call( this.callbackThis, response );
					}
					if(this.callbackThis){
						this.callbackThis.fireEvent( "apiCallSucceeded" );
					}
				}

			}, this );

			// Now Send the request
			var requestDoc = qx.xml.Document.create( null, "GetOneLRTask" );
			var requestRoot = requestDoc.documentElement;
			this.lrTask.createXMLElement( requestRoot );
			req.open( "POST", "/logic/utils/GetOneLRTask", true);
			req.send( welcome.Statics.xmlDocToString( requestDoc ) );
			this.debug("sending GetOneLRTask api");
		}

	},

	destruct : function() {
		//this._disposeObjects( "listBox" );
	}

});
