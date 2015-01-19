/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/64x64/plain/binocular.png)
************************************************************************ */


/** This class defines a simple dialog that presents a single drop-down
  * and a text entry window to the user.  You can set the window title,
  * icon, and label to customize
  * the presentation of the window.  You should also get the dropdown
  * after creating the window, but before opening it, and populate it with
  * the values that you want the user to choose from.
  */
qx.Class.define("admin.admin.LogFindDialog", {
	extend : admin.dialog.OKCancelDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( title ) {
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

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {
			this.idField.selectAllText();
			this.idField.focus();
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {
			var a1 = new qx.ui.basic.Atom(
				"Find a log message based on ID, Timestamp, or Log Message content.",
				"admin/icon/64x64/plain/binocular.png"
			);
			a1.setRich( true );
			layout.add( a1 );


			var leftSize = 80;
			var middleSize = 80;
			admin.Statics.addFieldsToForm( this, layout,
				"ID:", leftSize, "idField", "TextField");

			admin.Statics.addFieldsToForm( this, layout,
				"Timestamp:", leftSize, "dateField", "DateField");

			admin.Statics.addFieldsToForm( this, layout,
				"Message:", leftSize, "messageField", "TextField");

			this.dateField.setDateFormat( new qx.util.format.DateFormat( "yyyy/MM/dd HH:mm:ss" ) );
		}

	},

	destruct : function() {
		this._disposeObjects( "ok_btn", "idField", "dateField", "messageField"
		);
	}

});
