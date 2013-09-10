/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(welcome/icon/64x64/shadow/user_headset.png)
#asset(welcome/icon/16x16/plain/download.png)
#asset(welcome/icon/16x16/plain/server_from_client.png)
************************************************************************ */


/** This class defines a dialog that presents choice for the user in how they want to forward
  * something to Ivory Support.  They can either download that file and e-mail it to us, or
  * they can send it directly to us if their firewall's permit it.
  * <p>
  * As a developer, you should use whatever API's you require to first build your support bundle.
  * That bundle should be saved on the server in the /forwardtosupport/ folder under the director's
  * /bin/ folder.  Call it whatever you like, and ensure that it has everything that you require.
  * <p>
  * Then call this dialog and pass us the name of your support bundle file.  Don't include the
  * /forwardtosupport/ prefix, we'll tack that on.  We'll give the user the choice to either download
  * the file or send it directly via our encrypted channel to the home base Director instance running
  * at GT.
  * <p>
  * Once we are done, we'll trigger the forwardFinished event so that you can do any type of clean-up
  * that you deem necessary.  It's not strictly necessary to clean-up all forwarded bundles, as sometimes
  * a customer may want to go back and look at some of them (for whatever reason).  But if you do
  * choose to do any clean-up, listen for the forwardFinished event, and that's when you'll know it's
  * ok to clean things up.
  */
qx.Class.define("welcome.dialog.ForwardToSupportDialog", {
	extend : welcome.dialog.CancelDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( forwardToSupportFileName ) {
		this.forwardFile = forwardToSupportFileName;
		this.icon = "welcome/icon/64x64/shadow/user_headset.png";
		this.label = "If your Ivory Director server has internet connectivity, you can " +
			"choose the 'Use Direct Send' button below, and we will send the contents " +
			"directly to Ivory Support using an encrypted connection.<br/>" +
			"<p>" +
			"If you can't use the Direct Send option because of firewall restrictions, " +
			"use the Download Zip option, and your browser will download a zip file with " +
			"the contents that you can then e-mail or otherwise upload to support.<br/>" +
			"<p>" +
			"Ivory Support can be reached here: <a href=\"mailto:support@gtsoftware.com?Subject=Ivory%20Director%20Support%20Bundle\">support@gtsoftware.com</a>";


		// Call the parent constructor:
		this.base( arguments, "Forward to Support");

		// Change the name of the "Cancel" button to "Close"
		this.cancel_btn.setLabel( "Close" );

		// Add our extra buttons:
		this.downloadBtn = this.addButton( "Download Zip", "welcome/icon/16x16/plain/download.png" );
		this.forwardBtn = this.addButton( "Use Direct Send", "welcome/icon/16x16/plain/server_from_client.png" );

		this.downloadBtn.addListener( "execute", this.handleDownload, this );
		this.forwardBtn.addListener( "execute", this.handleForward, this );

		// Add our seperate iframe for file downloads
		this._dlFrame = new qx.ui.embed.Iframe("");
		this.add( this._dlFrame );
		this._dlFrame.set({width: 0, height: 0, decorator: null});

		this.addListener( "close", function(event){
			this.fireEvent( "forwardFinished" );
		}, this );

	},

	events : {
		/** When this dialog is closed by the user, we'll fire this event so that you can handle
		  * any type of cleanup of the support bundles that is required.
		  */
		forwardFinished : "qx.event.type.Event"

	},

	members : {

		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function () {
			this.setWidth(400);
			this.setHeight(300);
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {
			var a1 = new qx.ui.basic.Atom(this.label, this.icon );
			a1.setRich( true );
			layout.add(a1);

		},

		handleDownload: function() {
			var url = "/forwardtosupport/" + this.forwardFile;
			if(this._dlFrame.getSource() === url){
				this._dlFrame.resetSource();
			}
			this._dlFrame.setSource( url );
		},

		handleForward: function() {
			var fileObj = new welcome.sqldo.SupportBundle;
			fileObj.setFileName( this.forwardFile );
			welcome.Api.ForwardFileToSupport( fileObj, function(response) {
				welcome.Statics.doAlertGreen(
					"Zip file has been sent to Ivory Support.",
					"Direct Send Successful."
				);
			}, this );
		}

	},

	destruct : function() {
		this._disposeObjects( "downloadBtn", "forwardBtn", "_dlFrame" );
	}

});
