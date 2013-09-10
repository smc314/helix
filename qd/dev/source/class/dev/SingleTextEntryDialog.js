/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */


/** This class defines a simple dialog that presents a single text entry
  * to the user.  You can set the window title, icon, and label to customize
  * the presentation of the window.
  */
qx.Class.define("dev.SingleTextEntryDialog", {
	extend : dev.dialog.OKCancelDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( title, icon, label) {
		this.icon = icon;
		this.label = label;
		this.selectedValue = null;

		// Call the parent constructor:
		this.base( arguments, title );

		this.addOkEventListener("execute", function() {
			this.selectedValue = this.textField.getValue();
		}, this);

		this.addCancelEventListener("execute", function() {
			this.selectedValue = null;
		}, this);
	},

	members : {

		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function () {
			this.setWidth(400);
			this.setHeight(150);
		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {
			this.textField.selectAllText();
			this.textField.focus();
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {
			var a1 = new qx.ui.basic.Atom(this.label, this.icon );
			layout.add(a1);

			this.textField = new qx.ui.form.TextField;
			layout.add(this.textField);

		},

		/** Returns the value of the text field.  If the OK button
		  * was not pressed, this will always be null, regardless of the
		  * entry that the user may have made.
		  */
		getTextValue : function() {
			return this.selectedValue;
		},

		/** Returns our text field.
		  */
		getTextField : function() {
			return this.textField;
		}

	},

	destruct : function() {
		this._disposeObjects( "textField" );

	}

});
