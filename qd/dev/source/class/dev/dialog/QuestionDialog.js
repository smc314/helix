/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/** This class defines a simple dialog that presents a question
  * to the user.  You can set the window title, icon, and label to customize
  * the presentation of the window.
  */
qx.Class.define("dev.dialog.QuestionDialog",
{
	extend : dev.dialog.OKCancelDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function(title, icon, label)
	{
		this.icon = icon;
		this.label = label;

		// Call the parent constructor:
		this.base(arguments, title);
	},
	members :
	{
		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function()
		{
			this.setWidth(400);
			this.setHeight(150);
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function(layout)
		{
			var a1 = new qx.ui.basic.Atom(this.label, this.icon);
			a1.setRich(true);
			layout.add(a1);
		}
	},
	destruct : function()
	{
		//this._disposeObjects(  );
	}
});
