/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(PACKAGE/icon/16x16/plain/floppy_disk_ok.png)
#asset(PACKAGE/icon/16x16/plain/refresh.png)
#asset(PACKAGE/icon/16x16/plain/refresh.png)
************************************************************************ */
qx.Class.define("PACKAGE.ObjectEdit", {
	extend: qx.ui.container.Composite,
	
	properties : {
		/**
		* This property is toggled when the editor has been completely loaded.
		* All layouts will have been retrieved from the server, the doFormLayout()
		* will have completed, and if an initial selectApi call to the server was
		* warranted, it will have been issued and returned prior to changing the
		* property value and firing an "editorLoaded" event.
		*/
		editorLoaded : {init : false, event : "editorLoaded", check : "Boolean", inheritable : true}
	},

	construct: function (object_id) {
		this.base(arguments, new qx.ui.layout.VBox());

		this.setupNamesAndFunctions();

		this.isDirty = false;
		this.m_object_id = object_id;
		this.toolbar = new qx.ui.toolbar.ToolBar;
		this.initializeToolbar(this.toolbar);
		this.addHelpMenu(this.toolbar);
		this.add(this.toolbar);

		this.loadDynamicLayouts(0, function () {

			this.doFormLayout();

			if (this.m_object_id !== 0 && this.selectApiCall) {
				this.selectApiCall(this.m_object_id, this.firstGetObjectDetails, this);
			} else {
				this.initializeNewObject();
				this.setFocusFirst();
				if (!this.isEditorLoaded()) {this.toggleEditorLoaded();}
			}

			this.hookCloseEvent();
		}, this);

	},

	events : {
		/* ****************************************************************** */
		/* These events are primarily used in the automated testing framework */
		/* but may have general use beyond that.                              */
		/* ****************************************************************** */

		/**
		  * Whenever we call a server API function, the API call will either succeed or 
		  * fail.  This event gets fired when the API function is successful.
		  */
		apiCallSucceeded : "qx.event.type.Event",

		/**
		  * Whenever we call a server API function, the API call will either succeed or 
		  * fail.  This event gets fired when the API function fails.
		  */
		apiCallFailed : "qx.event.type.Event",

		/**
		  * Fired when the doSaveToServer call fails.  This is usually because of
		  * data validation failure.  Note, this event may not be fired even when the
		  * overall save actually fails, because the data validation may be ok, but the
		  * server API call may fail.  To watch for the failure "event" you need to 
		  * listen for both saveFailed and apiCallFailed.  Either that or listen to
		  * the saveSucceeded with a timeout and if the timeout expires, then you know
		  * that the save failed.
		  */
		saveFailed : "qx.event.type.Event",

		/**
		  * Fired when the doSaveToServer call succeeds.  This means that the data 
		  * validation was a success and the server API call succeeded.
		  */
		saveSucceeded : "qx.event.type.Event"

	},

	members: {

		/** This is where the subclasses will tell us which API functions to use, 
		* which callbacks to use, which names to use, etc.
		*/
		setupNamesAndFunctions: function () {
			this.selectApiCall = PACKAGE.Api.selectOneProductInfo;
			this.tabNamePrefix = "Product: ";
		},

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {

		},

		/** This method allows you to set the focus of whichever field you
		* want when this window becomes active.  This will be called every
		* time this window becomes the active window, which will only happen
		* once for a modal window.
		*/
		setFocusFirst: function () {

		},

		/** This allows our subclasses to do something in the scenario where the
		* edit view is opened up for a brand new object.
		*/
		initializeNewObject: function () {

		},

		/** This catches events from form fields that indicate a change in our
		 * dirty status.  We'll update the isDirty flag, and also update our
		 * tab label to indicate that we are dirty.
		 */
		fieldModified : function(e) {
			this.isDirty = true;

			var our_page = PACKAGE.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return;
			}
			var label = our_page.getButton().getLabel();
			if(label.charAt(0) === "*"){
				// already dirty, nothing to do.
			} else {
				our_page.setLabel( "*" + label);
				our_page.getButton().setLabel( "*" + label);
			}
		},

		/** This will turn off our dirty flag and reset our editor name back to normal.
		 */
		resetDirty : function() {
			this.isDirty = false;

			var our_page = PACKAGE.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return;
			}
			var label = our_page.getButton().getLabel();
			if(label.charAt(0) === "*"){
				our_page.setLabel( label.substr(1));
				our_page.getButton().setLabel( label.substr(1) );
			}
		},

		hookCloseEvent : function(){
			var our_page = PACKAGE.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return;
			}
			//our_page.getButton().__childControls["close-button"].addListener("mousedown", function(e){
			our_page.getButton().getChildControl("close-button").addListener("mousedown", function(e){
				if(! e.isLeftPressed() ){
					// they are right or middle clicking.  nothing to worry about.
					return;
				}
				if(this.isDirty === false){
					// nothing to warn about.
					return;
				}
				// We are dirty.  Warn the user:
				e.stop();
				var windowTitle = "Unsaved Changes!";
				var windowIcon = "PACKAGE/icon/32x32/shadow/sign_warning.png";
				var windowLabel = "You have unsaved changes and are about to close the editor.<br/><br/>Press OK to close the editor and lose your changes.<br/>Press Cancel to keep the editor open.";
				var dialog = new PACKAGE.dialog.QuestionDialog(windowTitle, windowIcon, windowLabel);
				qx.core.Init.getApplication().getRoot().add( dialog );
				dialog.addOkEventListener("execute", function(){
					// forcibly remove the tab page:
					var tabView = PACKAGE.Statics.findQXParent(our_page, qx.ui.tabview.TabView);
					tabView.remove( our_page );
				}, this);
				dialog.open();

			}, this);
		},

		/** This function will reset the name of our tab to be the string that you have
		* passed in.
		*/
		resetTabName: function (newTabName) {
			var our_page = PACKAGE.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return;
			}
			our_page.setLabel( newTabName );
			our_page.getButton().setLabel( newTabName );
			this.updateSummaryName( newTabName );
		},

		closePage: function () {
			var our_page = PACKAGE.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return;
			}
			our_page.getButton().fireDataEvent("close", our_page.getButton());
		},

		/**
		* This function is responsible for initializing our toolbar
		* 
		* @type member
		*/
		initializeToolbar: function (tb) {
			// Save/Cancel part
			var sc_part = new qx.ui.toolbar.Part;
			// Save button
			PACKAGE.Statics.addToToolbarWithShortcut(sc_part, "PACKAGE/icon/16x16/plain/floppy_disk_ok.png",
					this.tr("Save To Server"), this.doSaveToServer, this, this, null, "Save");

			// Revert button
			PACKAGE.Statics.addToToolbarWithShortcut(sc_part, "PACKAGE/icon/16x16/plain/refresh.png",
					this.tr("Reload From Server"), this.doRevert, this, this, null, "Revert");

			tb.add(sc_part);

			return tb;
		},
		
		addHelpMenu: function (tb) {
			// Force the help part to the far right
			tb.addSpacer();
			
			// Help part
			var help_part = new qx.ui.toolbar.Part;
			
			// Help button
			PACKAGE.Statics.addToToolbar(help_part, "PACKAGE/icon/16x16/plain/help2.png",
					this.tr("View Help"), this.doShowHelp, this, this, "Help");

			tb.add(help_part);

			return tb;
		},

		createRMCMenu: function (ev) {
			this.rmc = new qx.ui.menu.Menu;

			// refresh
			PACKAGE.Statics.addToRMCMenu(this.rmc, "Refresh", 'PACKAGE/icon/16x16/plain/refresh.png',
				this.doRevert, this);

			return this.rmc;
		},

		hideRMC: function () {
			if (!this.rmc) {
				return;
			}
			this.rmc.hide();
		},
		
		doShowHelp: function () {
			window.open(this.getHelpUrl(), "_blank");
		},
		
		getHelpUrl: function () {
			return "/PACKAGE/NetHelp/PACKAGE.htm";
		},

		doRevert: function (e) {
			if (this.m_object_id === 0) {
				// skip the revert for now, user hasn't saved their 
				// new object yet.
				return;
			}
			if (this.selectApiCall) {
				this.selectApiCall(this.m_object_id, this.getObjectDetails, this);
			}
		},

		/** This is used the very first time the editor is loaded.
		* 
		*/
		firstGetObjectDetails: function (response) {
			this.getObjectDetails(response);
			// the first time the object is loaded, we also need to set
			// the focus on the appropriate field of the editor.
			this.setFocusFirst();
			if (!this.isEditorLoaded()) {this.toggleEditorLoaded();}
		},

		getObjectDetails: function (response) {
		},

		/** This will save our current task information to the server
		* using an XML document to represent all of our task information.
		*/
		doSaveToServer: function () {
		},

		loadDynamicLayouts: function (start, callback) {
			if (!this.dynamicLayouts) {
				// nothing to do, run the callback.
				callback.call(this);
				return;
			}
			if (start >= this.dynamicLayouts.length) {
				// we're done.  Call the callback
				callback.call(this);
				return;
			}

			var url = "layouts/" + this.dynamicLayouts[start].name;
			// load the layout:
			PACKAGE.Api.LoadXMLDoc(url,
			function (response) {
				this.dynamicLayouts[start].doc = response.ownerDocument;
				// recurse for all of the rest of the layouts
				this.loadDynamicLayouts(start + 1, callback);
			}, this);
		},

		/** This function is used to find the right place to open a new view in the display.
		* We default to just our current tabview, but subclasses may override this to change
		* the behaviour as they required.
		*/
		getTargetTabView: function () {
			var targetTabView = null;
			var parentTaskPage = PACKAGE.Statics.findQXParent(this, PACKAGE.StandardPage);
			if (parentTaskPage === null) {
				targetTabView = PACKAGE.Statics.findQXParent(this, qx.ui.tabview.TabView);
			} else {
				if ((parentTaskPage.detailsTabView) &&
					!parentTaskPage.detailsTabView.__disposed
				) {
					targetTabView = parentTaskPage.detailsTabView;
				} else {
					targetTabView = PACKAGE.Statics.findQXParent(this, qx.ui.tabview.TabView);
				}
			}
			return targetTabView;
		},

		getDynamicLayout: function (layoutName) {
			for (var i = 0, l = this.dynamicLayouts.length; i < l; i++) {
				if (this.dynamicLayouts[i].name === layoutName) {
					return this.dynamicLayouts[i].doc;
				}
			}
			return null;
		},

		setAutoRefreshTimer: function (callback, recurTime) {
			// if we already have a timer, then just return
			if (this.refreshTimer) {
				return;
			}
			var timer = qx.util.TimerManager.getInstance();
			this.refreshTimer = timer.start(callback, recurTime, this);
		},

		cancelAutoRefreshTimer: function () {
			if (this.refreshTimer) {
				qx.util.TimerManager.getInstance().stop(this.refreshTimer);
				this.refreshTimer = null;
			}
		},

		createOverviewLayout: function (layoutParent, editorName, editorIcon, objName) {
			var root = new qx.ui.container.Composite(new qx.ui.layout.HBox);
			layoutParent.add(root, { flex: 10 });

			var live = new qx.ui.container.Composite(new qx.ui.layout.VBox).set({
				decorator: "pane",
				backgroundColor: "red",
				padding: 5,
				minWidth: 200
			});

			root.add(this.initGeneralStatus(editorName, editorIcon, objName), { flex: 1 });
			root.add(live, { flex: 10 });

			return live;
		},

		initGeneralStatus: function (type, icon, name) {
			this.status = new qx.ui.container.Composite(new qx.ui.layout.VBox(5)).set({
				decorator: "pane",
				backgroundColor: "blue",
				padding: 5,
				minWidth: 250,
				maxWidth: 250
			});

			var l1 = new qx.ui.basic.Label(type).set({ allowGrowX: true });
			l1.setFont(qx.bom.Font.fromString("font-size: 24px;font-style: normal;font-weight: bold;"));
			l1.setRich(true);
			this.status.add(l1);

			this.summaryName = new qx.ui.basic.Atom("<b>" + name + "</b>", icon);
			this.summaryName.setRich(true);
			this.status.add(this.summaryName);

			return this.status;
		},

		updateSummaryName: function (name) {
			this.summaryName.setLabel("<b>" + name + "</b>");
		},

		addStatusHeading: function (label) {
			var l1 = new qx.ui.basic.Label().set({
				backgroundColor: "#6396ef",
				textColor: "white",
				value: label,
				paddingLeft: 10,
				rich: true,
				allowGrowX: true
			});

			this.status.add(l1);

			return l1;
		},

		addStatusItem: function (text, icon) {

			var a1 = new qx.ui.basic.Atom(text, icon).set({
				paddingLeft: 20
			});
			a1.setSelectable(true);

			this.status.add(a1);

			return a1;
		},

		addStatusList: function () {

			var a1 = new qx.ui.form.List();

			this.status.add(a1);

			return a1;
		},

		addStatusHint: function(text){
			var a1 = new qx.ui.basic.Atom( text ).set({
				paddingLeft: 20,
				paddingRight: 20,
				rich: true
			});
			a1.setSelectable(true);
			this.status.add( a1 );
			return a1;
		}

	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		if (this.refreshTimer) {
			qx.util.TimerManager.getInstance().stop(this.refreshTimer);
			this.refreshTimer = null;
		}
		this._disposeObjects(
			"toolbar"
		);
		PACKAGE.Statics.destroyExtraObjects(this);

	}

});
