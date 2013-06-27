/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(PACKAGE/icon/16x16/plain/error.png)
************************************************************************ */


/** This class defines a simple dialog base class that defines a dialog window
  * with an OK and Cancel button.
  */
qx.Class.define("PACKAGE.dialog.OKCancelDialog", {
	extend : PACKAGE.dialog.OKDialog,

	/** You may pass in window title.
	  */
	construct : function ( title, addToolbar ) {
		this.base( arguments, title, addToolbar );

		this.close_btn = new qx.ui.form.Button("Cancel", "PACKAGE/icon/16x16/plain/error.png");
		this.close_btn.addListener("execute", function() {
			this.okPressed = false;
			this.close();
			qx.core.Init.getApplication().getRoot().remove(this);
		}, this);

		this.button_layout.add(this.close_btn);

	},
	
	members : {

		/** Allows you to add an event listener to our Cancel button.
		  */
		addCancelEventListener : function (event_name, event_fcn, event_this) {
			this.close_btn.addListener(event_name, event_fcn, event_this);
		}

	},

	destruct : function() {
		this._disposeObjects( "close_btn" );
	}
	
});
