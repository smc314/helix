/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(PACKAGE/icon/64x64/shadow/server_connection.png)
************************************************************************ */


/** This class defines a dialog that presents a list box
  * to the user.  You can set the window title, icon, and label to customize
  * the presentation of the window.
  */
qx.Class.define("PACKAGE.dialog.ServerConnectDialog", {
	extend : PACKAGE.dialog.OKCancelDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( title) {
		this.icon = "PACKAGE/icon/64x64/shadow/server_connection.png";
		this.label = "Enter the connection information required:";

		// Call the parent constructor:
		this.base( arguments, title );

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
			layout.add(a1);

			PACKAGE.Statics.addFieldsToForm(this, layout,
				"Name:", 70, "aliasField", "TextField");

			PACKAGE.Statics.addFieldsToForm(this, layout,
				"Host Name:", 70, "hostField", "TextField");

			PACKAGE.Statics.addFieldsToForm(this, layout,
				"Port#:", 70, "portField", "TextField");

			PACKAGE.Statics.addFieldsToForm(this, layout,
				"User Name:", 70, "userField", "TextField");

			PACKAGE.Statics.addFieldsToForm(this, layout,
				"Password:", 70, "passField", "PasswordField");

			this.aliasField.setValue( "" ); // avoid nulls
		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {
			this.aliasField.focus();
		}

	},

	destruct : function() {
		//this._disposeObjects( "listBox" );
	}

});
