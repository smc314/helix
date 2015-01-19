/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/error.png)
************************************************************************ */


/** This class defines a simple dialog base class that defines a dialog window
  * with a Cancel button.
  */
qx.Class.define("admin.dialog.CancelDialog", {
	extend : qx.ui.window.Window,

	properties : {
		/**
		* This property is toggled when the display has been completely loaded.
		* All layouts will have been retrieved from the server, the doFormLayout()
		* will have completed, and if an initial selectApi call to the server was
		* warranted, it will have been issued and returned prior to changing the
		* property value and firing an "editorLoaded" event.
		*/
		displayLoaded : {init : false, event : "displayLoaded", check : "Boolean", inheritable : true}
	},

	/** You may pass in window title.
	  */
	construct : function ( title, addToolbar ) {
		this.base( arguments, title );

		this.doSetSpace();
		this.setModal(true);
		this.setShowClose(true);
		this.setAllowClose(true);
		this.setShowMaximize(false);
		this.setShowMinimize(false);
		this.setAllowMinimize(false);
		this.addListenerOnce("resize", this.center, this);
		this.setLayout( new qx.ui.layout.VBox(10) );

		if(addToolbar !== undefined && addToolbar === true){
			this.toolbar = new qx.ui.toolbar.ToolBar;
			this.initializeToolbar( this.toolbar );
			this.add( this.toolbar );
		}

		this.child_layout = new qx.ui.container.Composite(new qx.ui.layout.VBox(10));
		this.add(this.child_layout, {flex:1});

		this.loadDynamicLayouts( 0, function() {
			// allow children to add their own items to our layout:
			this.doFormLayout( this.child_layout );

			this.addListenerOnce("focusin", this.setFocusFirst, this);

		}, this);

		// OK/Cancel Buttons
		var hbox = new qx.ui.layout.HBox(10);
		this.button_layout = new qx.ui.container.Composite(hbox);
		this.button_layout.set({paddingTop:0, paddingBottom:2});
		hbox.setAlignX("center");
		this.cancel_btn = new qx.ui.form.Button("OK", "admin/icon/16x16/plain/error.png");
		admin.Statics.setHtmlID( this.cancel_btn, "OK" );

		this.cancel_btn.addListener("execute", function() {
			this.close();
			qx.core.Init.getApplication().getRoot().remove(this);
		}, this);

		this.button_layout.add(this.cancel_btn);

		this.add(this.button_layout);

		this.setupKeyListener();
	},

	members : {

		setupKeyListener : function () {
			this.addListener("keypress",
			function(event){
				if(event.getKeyIdentifier() === "Escape"){
					// For some reason, we're not getting the escape key
					// press notifications.  Someone else along the chain
					// is intercepting them and stoping them.
					this.cancel_btn.press();
					this.cancel_btn.execute();
				}
			}, this );
		},

		/** Allows you to add an event listener to our Cancel button.
		  */
		addCancelEventListener : function (event_name, event_fcn, event_this) {
			this.cancel_btn.addListener(event_name, event_fcn, event_this);
		},

		/** Allows you to add another button to the form - this will add it to
		  * the beginning of the button list, so that the Cancel button always
		  * stays to the right.
		  */
		addButton : function (buttonLabel, buttonIcon) {
			var btn = new qx.ui.form.Button(buttonLabel, buttonIcon);
			this.button_layout.addAt( btn, 0 ); // Add the button to the leftmost side
			admin.Statics.setHtmlID( btn, buttonLabel );
			return btn; // return it so the caller can add any listeners or further customize it.
		},

		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function () {
			this.setWidth(400);
			this.setHeight(150);
		},

		/** This method will initialize our toolbar if requested in the constructor.
		 */
		initializeToolbar : function ( toolbar ) {
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {

		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {
			this.cancel_btn.focus();
		},

		loadDynamicLayouts : function ( start, callback ) {
			if(!this.dynamicLayouts){
				// nothing to do, run the callback.
				callback.call(this );
				return;
			}
			if(start >= this.dynamicLayouts.length){
				// we're done.  Call the callback
				callback.call(this);
				return;
			}

			var url = "layouts/" + this.dynamicLayouts[start].name;
			// load the layout:
			admin.Api.LoadXMLDoc( url,
			function( response ){
				this.dynamicLayouts[start].doc = response.ownerDocument;
				// recurse for all of the rest of the layouts
				this.loadDynamicLayouts( start + 1, callback );
			}, this);
		},

		getDynamicLayout : function ( layoutName ){
			for(var i = 0, l = this.dynamicLayouts.length; i < l; i++){
				if(this.dynamicLayouts[i].name === layoutName){
					return this.dynamicLayouts[i].doc;
				}
			}
			return null;
		}


	},

	destruct : function() {
		this._disposeObjects( "cancel_btn", "button_layout" );
		admin.Statics.destroyExtraObjects(this);

	}

});
