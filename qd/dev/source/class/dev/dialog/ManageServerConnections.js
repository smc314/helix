/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/* ************************************************************************
#asset(dev/icon/64x64/shadow/server_edit.png)
#asset(dev/icon/16x16/plain/delete2.png)
************************************************************************ */

/** This class defines a dialog that presents a list box
  * to the user.  You can set the window title, icon, and label to customize
  * the presentation of the window.
  */
qx.Class.define("dev.dialog.ManageServerConnections",
{
	extend : dev.dialog.OKDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function() {
		// Call the parent constructor:
		this.base(arguments, "Manage Server Connections");
	},
	members :
	{
		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function()
		{
			this.setWidth(500);
			this.setHeight(450);
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function(layout)
		{
			var a1 = new qx.ui.basic.Atom("Use the delete button to remove any server connections that are no longer required.", "dev/icon/64x64/shadow/server_edit.png");
			a1.setRich(true);
			layout.add(a1);
			dev.Statics.addBoxWithButtons(this, layout, "listBox", 1, 1, "deleteBtn", "Delete", "dev/icon/16x16/plain/delete2.png");
			this.listBox.setSelectionMode("multi");
			this.deleteBtn.addListener("execute", this.deleteSelection, this);
			dev.Api.UserProperties( {

			}, {

			}, this, this.loadList);
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
		},
		loadList : function()
		{
			this.listBox.removeAll();
			var props = dev.Singleton.getInstance().getUserProperties();
			for (var p in props) {
				if (props.hasOwnProperty(p))
				{
					var idx1 = p.indexOf("@");
					var idx2 = p.indexOf(":");
					if (idx1 != -1 && idx2 != -1 && idx2 > idx1)
					{
						// Add this to the list:
						var item = new qx.ui.form.ListItem(p, null, p);
						this.listBox.add(item);
					}
				}
			}
		},
		deleteSelection : function()
		{
			var app = qx.core.Init.getApplication();
			var selected = this.listBox.getSelection();
			var delList = {

			};
			for (var i = 0, l = selected.length; i < l; i++)
			{
				var item = selected[i];
				delList[item.getModel()] = item.getModel();
				app.removeFromServerMenu(item.getModel());
			}

			// Ask the server to delete the properties selected and then re-load the list
			dev.Api.UserProperties( {

			}, delList, this, this.loadList);
		}
	},
	destruct : function() {
		this._disposeObjects("listBox");
	}
});
