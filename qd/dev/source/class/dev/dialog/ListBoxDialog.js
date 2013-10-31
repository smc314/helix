/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/** This class defines a dialog that presents a list box
  * to the user.  You can set the window title, icon, and label to customize
  * the presentation of the window.
  */
qx.Class.define("dev.dialog.ListBoxDialog",
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
			this.setHeight(450);
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function(layout)
		{
			var a1 = new qx.ui.basic.Atom(this.label, this.icon);
			if (this.label.indexOf("<br/>") !== -1) {
				a1.setRich(true);
			}
			layout.add(a1);
			this.listBox = new qx.ui.form.List;
			this.listBox.addListener("dblclick", function()
			{
				this.ok_btn.press();
				this.ok_btn.execute();
			}, this);
			layout.add(this.listBox, {
				flex : 1
			});
		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function() {
			this.listBox.focus();
		},

		/** Returns our list box.
		  */
		getListBox : function() {
			return this.listBox;
		}
	},
	destruct : function() {
		this._disposeObjects("listBox");
	}
});
