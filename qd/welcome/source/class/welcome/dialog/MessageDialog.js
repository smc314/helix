/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */


/** This class defines a simple dialog that presents a message
  * to the user.  You can set the window title, icon, and label to customize
  * the presentation of the window.
  */
qx.Class.define("welcome.dialog.MessageDialog", {
	extend : welcome.dialog.OKDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( title, icon, label) {
		this.icon = icon;
		this.label = label;

		// Call the parent constructor:
		this.base( arguments, title );

	},

	members : {

		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function () {
			this.setWidth(450);
			this.setHeight(150);
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {
			this.displayAtom = new qx.ui.basic.Atom(this.label, this.icon );
			this.displayAtom.setRich( true );
			this.displayAtom.setSelectable(true);
			layout.add(this.displayAtom);
		}

	},

	destruct : function() {
		//this._disposeObjects(  );

	}

});
