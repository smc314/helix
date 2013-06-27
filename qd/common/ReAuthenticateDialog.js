/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */


/** This class defines a simple dialog that will prompt the user to re-enter
  * their password for re-authentication.
  */
qx.Class.define("PACKAGE.ReAuthenticateDialog", {

	extend : PACKAGE.SingleTextEntryDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( title, icon, label) {
		this.base( arguments, title, icon, label );
	},
	
	members : {
		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {
			var a1 = new qx.ui.basic.Atom(this.label, this.icon );
			layout.add(a1);
	
			this.textField = new qx.ui.form.PasswordField;
			layout.add(this.textField);
		
		},

		/** Returns the value of the password text field.  If the OK button
		  * was not pressed, this will always be null, regardless of the
		  * entry that the user may have made.
		  */
		getPassValue : function() {
			return this.selectedValue;
		},

		/** Returns our text field.
		  */
		getPassField : function() {
			return this.textField;
		}

	},

	destruct : function() {
		this._disposeObjects( "textField" );
	}
	
});
