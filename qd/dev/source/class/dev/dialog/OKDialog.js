/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/* ************************************************************************
#asset(dev/icon/16x16/plain/ok.png)
************************************************************************ */

/** This class defines a simple dialog base class that defines a dialog window
  * with an OK and Cancel button.
  */
qx.Class.define("dev.dialog.OKDialog",
{
	extend : qx.ui.window.Window,
	properties : {
		/**
		* This property is toggled when the display has been completely loaded.
		* All layouts will have been retrieved from the server, the doFormLayout()
		* will have completed, and if an initial selectApi call to the server was
		* warranted, it will have been issued and returned prior to changing the
		* property value and firing an "editorLoaded" event.
		*/
		displayLoaded :
		{
			init : false,
			event : "displayLoaded",
			check : "Boolean",
			inheritable : true
		}
	},

	/** You may pass in window title.
	  */
	construct : function(title, addToolbar)
	{
		this.base(arguments, title);

		// These are the values we capture and the caller can

		// interrogate to find out how things went
		this.okPressed = false;
		this.doSetSpace();
		this.setModal(true);
		this.setShowClose(true);
		this.setAllowClose(true);
		this.setShowMaximize(false);
		this.setShowMinimize(false);
		this.setAllowMinimize(false);
		this.addListenerOnce("resize", this.center, this);
		this.setLayout(new qx.ui.layout.VBox(10));
		if (addToolbar !== undefined && addToolbar === true)
		{
			this.toolbar = new qx.ui.toolbar.ToolBar;
			this.initializeToolbar(this.toolbar);
			this.add(this.toolbar);
		}
		this.child_layout = new qx.ui.container.Composite(new qx.ui.layout.VBox(10));
		this.add(this.child_layout, {
			flex : 1
		});
		this.loadDynamicLayouts(0, function()
		{
			// allow children to add their own items to our layout:
			this.doFormLayout(this.child_layout);
			this.addListenerOnce("focusin", this.setFocusFirst, this);
		}, this);

		// OK/Cancel Buttons
		var hbox = new qx.ui.layout.HBox(10);
		this.button_layout = new qx.ui.container.Composite(hbox);
		this.button_layout.set(
		{
			paddingTop : 0,
			paddingBottom : 2
		});
		hbox.setAlignX("center");
		this.ok_btn = new qx.ui.form.Button("OK", "dev/icon/16x16/plain/ok.png");
		this.ok_btn.addListener("execute", function()
		{
			this.okPressed = true;
			this.close();
			qx.core.Init.getApplication().getRoot().remove(this);
		}, this);
		this.button_layout.add(this.ok_btn);
		this.add(this.button_layout);
		this.setupKeyListener();
	},
	members :
	{
		setupKeyListener : function() {
			this.addListener("keypress", function(event) {
				if (event.getKeyIdentifier() === "Enter") {
					if (!(event.getTarget() instanceof qx.ui.form.TextArea))
					{
						this.ok_btn.press();
						this.ok_btn.execute();
					}
				} else if (event.getKeyIdentifier() === "Escape")
				{
					// For some reason, we're not getting the escape key

					// press notifications.  Someone else along the chain

					// is intercepting them and stoping them.
					this.okPressed = false;
					this.close();
				}

			}, this);
		},

		/** Allows you to add an event listener to our OK button.
		  */
		addOkEventListener : function(event_name, event_fcn, event_this) {
			this.ok_btn.addListener(event_name, event_fcn, event_this);
		},

		/** Returns whether the OK button was pressed to exit the dialog.
		  * True if OK was pressed, False if any other method was used to
		  * exit the dialog.
		  */
		getOkPressed : function() {
			return this.okPressed;
		},

		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function()
		{
			this.setWidth(400);
			this.setHeight(150);
		},

		/** This method will initialize our toolbar if requested in the constructor.
		 */
		initializeToolbar : function(toolbar) {
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function(layout) {
		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function() {
		},
		loadDynamicLayouts : function(start, callback)
		{
			if (!this.dynamicLayouts)
			{
				// nothing to do, run the callback.
				callback.call(this);
				return;
			}
			if (start >= this.dynamicLayouts.length)
			{
				// we're done.  Call the callback
				callback.call(this);
				return;
			}
			var url = "layouts/" + this.dynamicLayouts[start].name;

			// load the layout:
			dev.Api.LoadXMLDoc(url, function(response)
			{
				this.dynamicLayouts[start].doc = response.ownerDocument;

				// recurse for all of the rest of the layouts
				this.loadDynamicLayouts(start + 1, callback);
			}, this);
		},
		getDynamicLayout : function(layoutName)
		{
			for (var i = 0, l = this.dynamicLayouts.length; i < l; i++) {
				if (this.dynamicLayouts[i].name === layoutName) {
					return this.dynamicLayouts[i].doc;
				}
			}
			return null;
		}
	},
	destruct : function()
	{
		this._disposeObjects("ok_btn", "button_layout");
		dev.Statics.destroyExtraObjects(this);
	}
});
