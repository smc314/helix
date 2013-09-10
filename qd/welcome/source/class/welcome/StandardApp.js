/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(welcome/icon/16x16/plain/home.png)
#asset(welcome/icon/16x16/plain/control_panel.png)
#asset(welcome/icon/16x16/plain/compass.png)
#asset(welcome/icon/16x16/plain/house.png)
#asset(welcome/icon/16x16/plain/help2.png)
#asset(welcome/icon/16x16/plain/question_and_answer.png)
#asset(welcome/icon/16x16/plain/book_blue_open2.png)
#asset(welcome/icon/16x16/plain/about.png)
#asset(welcome/icon/16x16/plain/download.png)
#asset(welcome/icon/16x16/plain/about.png)
#asset(welcome/icon/16x16/plain/server_connection.png)
#asset(welcome/icon/16x16/plain/server_edit.png)
#asset(welcome/icon/16x16/plain/server_connection.png)
#asset(welcome/icon/16x16/plain/server_connection.png)
#asset(welcome/icon/16x16/plain/server_delete.png)
#asset(welcome/icon/16x16/plain/server_delete.png)
#asset(welcome/icon/16x16/plain/help2.png)
#asset(welcome/icon/16x16/plain/book_blue_open2.png)
#asset(welcome/icon/16x16/plain/book_blue_open2.png)
#asset(welcome/icon/16x16/plain/question_and_answer.png)
#asset(welcome/icon/16x16/plain/house.png)
#asset(welcome/icon/16x16/plain/download.png)
#asset(welcome/helix-about-background.png)
#asset(welcome/icon/16x16/plain/folder.png)
#asset(welcome/icon/16x16/plain/refresh.png)
#asset(welcome/icon/16x16/plain/eye_blue.png)
#asset(welcome/icon/16x16/plain/delete2.png)
#asset(welcome/icon/16x16/plain/refresh.png)
#asset(welcome/icon/16x16/plain/eye_blue.png)
#asset(welcome/icon/16x16/plain/delete2.png)
#asset(welcome/icon/16x16/plain/refresh.png)
#asset(welcome/icon/16x16/plain/eye_blue.png)
#asset(welcome/icon/16x16/plain/signpost.png)
#asset(welcome/icon/16x16/plain/carabiner.png)
#asset(welcome/icon/16x16/plain/server_delete.png)
#asset(welcome/icon/16x16/plain/server_connection.png)
#asset(welcome/icon/16x16/plain/refresh.png)
************************************************************************ */
qx.Mixin.define("welcome.StandardApp", {

	properties : {

		/** This property is toggled when the application has been initialized.
		  */
		appInitialized : {init: false, event : "appInitialized", check : "Boolean", inheritable : true }

	},

	events : {
		/* ****************************************************************** */
		/* These events are primarily used in the automated testing framework */
		/* but may have general use beyond that.                              */
		/* ****************************************************************** */

		/**
		  * Fired when the tree has been pruned.  The app can decide to
		  * refresh the tree if no connection is required.
		  */
		treePruned : "qx.event.type.Event"

	},

	members: {

		/** This function makes it easy to populate a list from XML that has a
		* given format.  Tell us the element Name that you want us to use from the XML
		* document and we will find all instances of that element name in the document,
		* pull out their "name" and "id" attributes, and use those to create the
		* list items.
		*
		* @param list {Object}
		* @param xmlDoc {Object}
		* @param elementName {Object}
		*/
		populateList: function (list, xmlDoc, elementName) {
			list.removeAll();

			var element_list = xmlDoc.getElementsByTagName(elementName);
			for (var i = 0, l = element_list.length; i < l; i++) {
				var opt = new qx.ui.form.ListItem(
					element_list[i].getAttribute("name"),
					null,
					element_list[i].getAttribute("id")
				);
				list.add(opt);
			}
		},

		/** This function makes it simple to add a menu button to a given menu with
		*  a label, icon, tooltip, shortcut command, and callback function setup for the menu button.
		*/
		addMenuButton: function (menu, shortcut, label, icon, tooltip, callback) {
			// Create and configure the command
			var command = new qx.ui.core.Command(shortcut);
			command.setLabel(label);
			command.setIcon(icon);
			command.setToolTipText(tooltip);
			command.addListener("execute", callback, this);
			var button = new qx.ui.menu.Button();
			button.setCommand(command);
			menu.add(button);
			return button;
		},

		/** All of the StandardApp applications have the same look and feel and layout.  This
		* is the method that initiates that structure.
		*/
		setupStandardApp: function (skipSystem, customSplitPane) {
			this.skipSystem = skipSystem;

			// Enable logging in debug variant
			if (qx.core.Environment.get("qx.debug")) {
				// support native logging.
				qx.log.appender.Native;

				// support cross-browser console.  Press F7 to toggle visibility
				qx.log.appender.Console;

				// support logging back to the Hub
				welcome.LogAppender;
			}

			this.HelixVersion = "314.314.314.314";

			// Load our user properties at first opportunity
			welcome.Api.UserProperties({}, {}, this, function () {
				// Document is the application root
				var doc = this.getRoot();

				// Add our application structure
				doc.add(this.getMainToolBar(), { left: 0, top: 0, right: 0 });

				if(customSplitPane){
					doc.add(customSplitPane.call(this), { left: 0, top: 32, right: 0, bottom: 5 });
				} else {
					doc.add(this.getSplitPane(), { left: 0, top: 32, right: 0, bottom: 5 });
				}

				// Add our welcome tab:
				this.showWelcome();

				this.loadSystemProperties();
			});

			var self = this;
			welcome.PageVisibility.getInstance().on("change",
			function() {
				if (welcome.PageVisibility.getInstance().isHidden()) {
					// do something when hidden
				} else {
					// do something when the page gets back to visible
					welcome.Api.UserProperties({}, {}, self,
					function () {
						var label = this.serverMenu.getLabel();
						if (label == "Server: Not Connected") { return; }
						var props = welcome.Singleton.getInstance().getUserProperties();
						var label = this.serverMenu.getLabel();
						if (label != props["CurrentConnection"] ) {
							var obj = new welcome.sqldo.LogOn();
							obj.setConnName(label);

							welcome.Api.SwitchServerConnection(obj,
							function (response) {
								//this.addToServerMenu(label);
								//this.serverMenu.setLabel(label);
								//this.addCloseConnection();
								//this.loadSystemProperties();
								//this.closeAllEditors();
							}, this);
						}
					});
				}
			});

		},

		loadSystemProperties: function () {
			if (this.skipSystem !== undefined && this.skipSystem === true) {
				// Just fill in the tree.
				this.fillTree();
				if(!this.isAppInitialized()) { this.toggleAppInitialized(); }
			} else {
				// Call for system properties - this will log the user in if not already cached
				welcome.Api.SystemProperties(this, function () {
					// Now we can finally start to load all of our initial data.
					this.fillTree();
					if(!this.isAppInitialized()) { this.toggleAppInitialized(); }
				});
			}
		},

		doTada : function () {
			// animation causes screen to freeze.  turn off for now.
			return;

			var upAndAway = {duration : 1000, timing: "ease-out", keyFrames : {
				0 : {translate : [null, "0px"]},
				10 : {translate : [null, "10px"]},
				20 : {translate : [null, "20px"]},
				30 : {translate : [null, "30px"]},
				40 : {translate : [null, "40px"]},
				50 : {translate : [null, "30px"]},
				60 : {translate : [null, "20px"]},
				70 : {translate : [null, "10px"]},
				80 : {translate : [null, "0px"]},
				90 : {translate : [null, "-10px"]},
				100 : {translate : [null, "0px"]}
			}};

			var element = this.container1.getContainerElement().getDomElement();
			qx.bom.element.Animation.animate(element, upAndAway);
		},

		/** This function standardizes the Applications menu so that everyone does it in
		*  the same way.
		*/
		getAppsMenu: function () {
			var menu = new qx.ui.menu.Menu;

			var welcome = new qx.ui.menu.Button("Welcome To Helix Development",
					"welcome/icon/16x16/plain/home.png");
			var admin = new qx.ui.menu.Button("Helix Administration",
					"welcome/icon/16x16/plain/control_panel.png");
			var dev = new qx.ui.menu.Button("Helix Development",
					"welcome/icon/16x16/plain/compass.png");

			welcome.addListener("execute", function () {
				this.openWindow("/qd/welcome/build/index.html", "_blank");
			}, this);
			admin.addListener("execute", function () {
				this.openWindow("/qd/admin/build/index.html", "_blank");
			}, this);
			dev.addListener("execute", function () {
				this.openWindow("/qd/dev/build/index.html", "_blank");
			}, this);

			menu.add(welcome);
			menu.add(admin);
			menu.add(dev);

			return menu;
		},

		openWindow: function(url, target) {
			if (!qx.bom.Window.open(url, target)) {
				window.location.assign(url);
			}
		},

		/** This standardizes the help menu to look a certain way.
		*/
		getHelpMenu: function () {
			var menu = new qx.ui.menu.Menu;

			var welcomeButton = new qx.ui.menu.Button("View Welcome Page",
					"welcome/icon/16x16/plain/house.png");
			var helpButton = new qx.ui.menu.Button("View Help",
					"welcome/icon/16x16/plain/help2.png");
			var supportButton = new qx.ui.menu.Button("Helix Q&A",
					"welcome/icon/16x16/plain/question_and_answer.png");
			var appGuidesButton = new qx.ui.menu.Button("Helix Development Guide",
					"welcome/icon/16x16/plain/book_blue_open2.png");
			var aboutSPButton = new qx.ui.menu.Button("About Helix",
					"welcome/icon/16x16/plain/about.png");
			var updatesButton = new qx.ui.menu.Button("Check For Updates...",
					"welcome/icon/16x16/plain/download.png");
			var aboutButton = new qx.ui.menu.Button("About " + this.ApplicationName);

			welcomeButton.addListener("execute", this.showWelcome, this);
			helpButton.addListener("execute", this.showHelp, this);
			docsButton.addListener("execute", this.showDocs, this);
			appGuidesButton.addListener("execute", this.showAppGuides, this);

			supportButton.addListener("execute", this.showQA, this);

			aboutSPButton.addListener("execute", function () {
				var tab_page = this.addEditingTab("Helix");
				if (tab_page != null) { // brand new
					tab_page.setIcon("welcome/icon/16x16/plain/about.png");
					var iframe = new qx.ui.embed.Iframe().set({
						source: "http://www.hericus.com/products/helix"
					});
					tab_page.add(iframe, { flex: 10 });
				}
			}, this);
			updatesButton.addListener("execute", this.showUpdates, this);
			aboutButton.addListener("execute", this.commonAbout, this);

			menu.add(welcomeButton);
			menu.add(helpButton);
			menu.add(appGuidesButton);
			menu.addSeparator();
			menu.add(aboutSPButton);
			menu.addSeparator();
			menu.add(updatesButton);
			menu.addSeparator();
			menu.add(aboutButton);

			return menu;
		},

		/** This standardizes the server menu to look and work a certain way.
		*/
		getServerMenu: function () {
			var menu = new qx.ui.menu.Menu;

			var btnNew = new qx.ui.menu.Button("New Connection...",
					"welcome/icon/16x16/plain/server_connection.png");

			btnNew.addListener("execute", function () {
				this.displayServerConnectDialog();
			}, this);

			menu.add(btnNew);

			var btnMng = new qx.ui.menu.Button("Manage Connections",
					"welcome/icon/16x16/plain/server_edit.png");

			btnMng.addListener("execute", function () {
				this.manageServerConnectDialog();
			}, this);

			menu.add(btnMng);

			menu.addSeparator();

			// Load the rest of the menu based on our cached user properties
			// that the server maintains for us.
			var props = welcome.Singleton.getInstance().getUserProperties();
			for (var p in props) {
				if (props.hasOwnProperty(p)) {
					var idx1 = p.indexOf("@");
					var idx2 = p.indexOf(":");
					if (idx1 != -1 && idx2 != -1 && idx2 > idx1) {
						// Add this to the list
						var btn = new qx.ui.menu.Button(p,
						"welcome/icon/16x16/plain/server_connection.png");
						btn.addListener("execute", function (e) {
							var obj = new welcome.sqldo.LogOn();
							var label = e.getTarget().getLabel();
							obj.setConnName(label);

							welcome.Api.SwitchServerConnection(obj, function (response) {
								this.serverMenu.setLabel(label);
								this.addCloseConnection();
								this.loadSystemProperties();
								this.closeAllEditors();
							}, this);
						}, this);
						menu.add(btn);
					}
				}
			}

			return menu;
		},

		displayServerConnectDialog: function () {
			var app = qx.core.Init.getApplication();
			var windowTitle = "Connect to Helix Server";
			var tmpWindow = new welcome.dialog.ServerConnectDialog(windowTitle);
			tmpWindow.addOkEventListener("execute", function () {
				var obj = new welcome.sqldo.LogOn();
				obj.setHost(tmpWindow.hostField.getValue().toUpperCase());
				obj.setPort(tmpWindow.portField.getValue());
				obj.setUser(tmpWindow.userField.getValue().toUpperCase());
				obj.setPass(tmpWindow.passField.getValue());
				obj.setAlias(tmpWindow.aliasField.getValue());

				welcome.Api.ConnectToServer(obj, function (response) {
					var objs = welcome.sqldo.LogOn.readElementChildren(response);
					var menuLabel = objs[0].getConnName();
					app.serverMenu.setLabel(menuLabel);

					// Add it in for future switching:
					this.addToServerMenu(menuLabel);

					this.loadSystemProperties();

					this.closeAllEditors();
				}, app);

			}, app);
			tmpWindow.open();
			qx.core.Init.getApplication().getRoot().add(tmpWindow);

		},

		manageServerConnectDialog : function(){

			var tmpWindow = new welcome.dialog.ManageServerConnections();
			tmpWindow.open();
			qx.core.Init.getApplication().getRoot().add(tmpWindow);

		},

		/** This will add an item to the server menu.  We'll ensure that it is
		* not already present.
		*/
		addToServerMenu: function (newLabel) {
			// Walk the existing labels to see if it is there:
			var children = this.serverMenu.getMenu().getChildren();
			for (var i = 0, l = children.length; i < l; i++) {
				if (!(children[i] instanceof qx.ui.menu.Separator) &&
					children[i].getLabel() == newLabel
				) {
					// The label already exists.  Bail out.
					return;
				}
			}

			// Label was not found.  Add it in:
			var btn = new qx.ui.menu.Button(newLabel, "welcome/icon/16x16/plain/server_connection.png");
			btn.addListener("execute", function () {
				var obj = new welcome.sqldo.LogOn();
				obj.setConnName(newLabel);

				welcome.Api.SwitchServerConnection(obj, function (response) {
					this.serverMenu.setLabel(newLabel);
					this.addCloseConnection();
					this.loadSystemProperties();
					this.closeAllEditors();
				}, this);
			}, this);

			this.serverMenu.getMenu().add(btn);

			this.addCloseConnection(this);

		},

		removeFromServerMenu: function(menuLabel) {
			// Walk the existing labels to see if it is there:
			var children = this.serverMenu.getMenu().getChildren();
			for (var i = 0, l = children.length; i < l; i++) {
				if (!(children[i] instanceof qx.ui.menu.Separator) &&
					children[i].getLabel() == menuLabel
				) {
					// The label exists, remove it:
					this.serverMenu.getMenu().remove( children[i] );
					return;
				}
			}
		},

		addCloseConnection: function () {

			// Check to see if we have the "Close Current Connection" action.
			// If not, then add it:
			var children = this.serverMenu.getMenu().getChildren();
			for (var i = 0, l = children.length; i < l; i++) {
				if (!(children[i] instanceof qx.ui.menu.Separator) &&
					children[i].getLabel() === "Close Current Connection"
				) {
					// The label already exists.  Bail out.
					return;
				}
			}
			// Close not found.  Add it in right after New Connection...
			var closeBtn = new qx.ui.menu.Button("Close Current Connection",
				"welcome/icon/16x16/plain/server_delete.png");
			closeBtn.addListener("execute", function () {
				welcome.Api.CloseConnection(function (response) {
					this.serverMenu.setLabel("Server: Not Connected");
					this.serverMenu.setIcon("welcome/icon/16x16/plain/server_delete.png");
					this.pruneTree();
				}, this);
			}, this);
			this.serverMenu.getMenu().addAt(closeBtn, 1);


		},

		/** This function will handle adding a new tab for the given object.  We will
		* search the current list of editing tabs to see if this object is already represented.
		* If it is found, then we will simply activate the existing tab.  If not, a new tab
		* will be added and made the active tab.
		*/
		addEditingTab: function (tabName) {

			// first check to see if this tab name already exists:
			var pages = this.tabView.getChildren();
			for (var i = 0, l = pages.length; i < l; i++) {
				if (pages[i].getLabel() === tabName ||
					pages[i].getLabel() === "*" + tabName
				) {
					pages[i].getButton().setValue(true); // bring it to the front.
					welcome.Statics.doAlertGreen("A tab is already open with the name: " + tabName);
					return null; // it's already there
				}
			}

			// Didn't find it, so go ahead and add a new tab for it:
			var page = welcome.Statics.addTabPage(this.tabView, tabName, true, true);
			return page;
		},

		/** This function will handle closing a tab with the given name.  We will
		* search the current list of editing tabs to see if this name is already represented.
		* If it is found, then we will close the tab.  If not, we will do nothing.
		*/
		closeEditingTab: function (tabName) {

			// first check to see if this tab name already exists:
			var pages = this.tabView.getChildren();
			for (var i = 0, l = pages.length; i < l; i++) {
				if (pages[i].getLabel() == tabName) {
					// Found it.  Tell it to close:
					this.tabView.remove(pages[i]);
					return;
				}
			}

			// Didn't find it, do nothing.
		},

		/** This function will handle adding a new tab for the given object.  We allow
		* duplicate tab names to be added and do not search the existing list.
		*/
		addEditingTabDup: function (tabName) {
			// Add it even if it is a duplicate tab name
			var page = welcome.Statics.addTabPage(this.tabView, tabName, true, true);
			return page;
		},

		/** This function will handle closing all open editors.  This is usually used
		  * when the user has changed their server connection.
		  */
		closeAllEditors: function() {
			var pages = this.tabView.getChildren();
			for (var i = pages.length - 1; i >= 0; i--) {
				if (pages[i].getLabel() !== "Welcome") { // don't close the welcome page
					// Tell it to close:
					this.tabView.remove(pages[i]);
				}
			}
		},

		showHelp: function () {
			var tab_page = this.addEditingTab("Help");
			if (tab_page != null) { // brand new
				tab_page.setIcon("welcome/icon/16x16/plain/help2.png");
				var iframe = new qx.ui.embed.Iframe().set({
					source: "/welcome/NetHelp/welcome.htm"
				});
				tab_page.add(iframe, { flex: 10 });
			}
		},

		showDocs: function () {
			var tab_page = this.addEditingTab("Documentation");
			if (tab_page != null) { // brand new
				tab_page.setIcon("welcome/icon/16x16/plain/book_blue_open2.png");
				var iframe = new qx.ui.embed.Iframe().set({
					source: "/docs/docs.html"
				});
				tab_page.add(iframe, { flex: 10 });
			}
		},

		showAppGuides: function () {
			var tab_page = this.addEditingTab("Application Guides");
			if (tab_page != null) { // brand new
				tab_page.setIcon("welcome/icon/16x16/plain/book_blue_open2.png");
				var iframe = new qx.ui.embed.Iframe().set({
					source: "/docs/appguides/NetHelp/AppGuides.htm"
				});
				tab_page.add(iframe, { flex: 10 });
			}
		},

		showQA: function () {
			var tab_page = this.addEditingTab("Q & A");
			if (tab_page != null) { // brand new
				tab_page.setIcon("welcome/icon/16x16/plain/question_and_answer.png");
				var iframe = new qx.ui.embed.Iframe().set({
					source: "http://helix.hericus.com/osqa/"
				});
				tab_page.add(iframe, { flex: 10 });
			}
		},

		showWelcome: function () {
			var tab_page = this.addEditingTab("Welcome");
			if (tab_page != null) { // brand new
				tab_page.setIcon("welcome/icon/16x16/plain/house.png");
				tab_page.add(new welcome.HomePage(0), { flex: 10 });
			}
		},

		showUpdates : function () {
			var tab_page = this.addEditingTab("Check for Updates");
			if (tab_page != null) { // brand new
				tab_page.setIcon("welcome/icon/16x16/plain/download.png");
				tab_page.add(new welcome.help.CheckForUpdates(0), { flex: 10 });
			}
		},

		/** This function handles the About dialog box in a common way.  All applications
		* should use this common method so that About dialog boxes display in the same
		* style.
		*/
		commonAbout: function () {
			var d = new Date();
			var single = welcome.Singleton.getInstance();
			var props = single.getSystemProperties();
			var windowTitle = "About Helix " + this.ApplicationName;
			var windowIcon = null;
			var windowText = "<br/><br/><br/><br/><br/><br/><p style=\"text-shadow: black 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:white;\">" + this.ApplicationName + "<br/><br/>" +
				"Helix Version: " + this.HelixVersion + "<br/>" +
				"<br/>" +
				"Copyright &copy; 1997 - " + d.getFullYear() + " Hericus Software, Inc.  All Rights Reserved." +
				"</p>";

			var decorator = new qx.ui.decoration.Background();
			decorator.setBackgroundImage( "welcome/helix-about-background.png" );
			var tmpWindow = new welcome.dialog.MessageDialog(windowTitle, windowIcon, windowText);
			tmpWindow.child_layout.setDecorator( decorator );
			tmpWindow.displayAtom.setIconPosition("top");
			tmpWindow.setWidth( 474 );
			tmpWindow.setHeight( 384 );
			this.getRoot().add(tmpWindow);
			tmpWindow.open();
		},

		getSplitPane: function () {
			this.pane = new qx.ui.splitpane.Pane("horizontal").set({
				width: 1024,
				height: 768
			});

			this.container1 = new qx.ui.container.Composite(new qx.ui.layout.Grow).set({
				width: 300,
				decorator: "main"
			});

			this.container2 = new qx.ui.container.Composite(new qx.ui.layout.VBox(10)).set({
				padding: 0,
				decorator: "main"
			});

			this.treeTabs = new qx.ui.tabview.TabView;
			this.container1.add( this.treeTabs );

			this.tree = new qx.ui.tree.Tree();
			//this.tree.setDecorator(null);
			this.tree.setRootOpenClose(true);
			this.tree.addListener("changeSelection", this.handleTreeSelection, this);

			this.treeRoot = new qx.ui.tree.TreeFolder("RootNodeIsInvisible");
			this.treeRoot.setOpen(true);
			this.tree.setRoot(this.treeRoot);
			this.tree.setHideRoot(true);
			this.tree.setContextMenu(this.createTreeRMC());

			var navTab = welcome.Statics.addEditorSubTab( this.treeTabs, "Explorer", true, this.getTreeToolBar() );
			welcome.Statics.findQXParent( navTab, qx.ui.tabview.Page ).setIcon("welcome/icon/16x16/plain/folder.png" );
			navTab.add( this.tree, {flex:1} );

			this.pane.add(this.container1, 0);
			this.pane.add(this.container2, 1);
			this.tabView = new qx.ui.tabview.TabView;
			this.container2.add(this.tabView, { flex: 10 });

			return this.pane;

		},

		createTreeRMC: function () {
			this.treeRMC = new qx.ui.menu.Menu;

			welcome.Statics.addToRMCMenu(this.treeRMC, "Refresh Tree",
				"welcome/icon/16x16/plain/refresh.png", this.fillTree, this);
			welcome.Statics.addToRMCMenu(this.treeRMC, "View Selected Item",
				"welcome/icon/16x16/plain/eye_blue.png", this.viewTreeSelection, this);
			welcome.Statics.addToRMCMenu(this.treeRMC, "Delete Selected Item",
				"welcome/icon/16x16/plain/delete2.png", this.deleteTreeSelection, this);

			return this.treeRMC;
		},

		createTreeFolder: function (parent_node, obj, label, icon) {
			var folder = new qx.ui.tree.TreeFolder(label);
			folder.setOpenSymbolMode("always");
			folder.setIcon(icon);
			folder.helixObj = obj;
			parent_node.add(folder);
			//folder.addListener("dblclick", this.handleTreeDblClick, this);
			folder.addListener("changeOpen", this.handleTreeChangeOpen, this);
			return folder;
		},

		createTreeItem: function (parent_node, obj, label, icon) {
			var item = new qx.ui.tree.TreeFile(label);
			item.setIcon(icon);
			item.helixObj = obj;
			parent_node.add(item);
			item.addListener("dblclick", this.handleDisplay, this);
			return item;
		},

		createTreeFolder2: function (parent_node, obj, label, icon, populateChildren) {
			var folder = new qx.ui.tree.TreeFolder(label);
			folder.setOpenSymbolMode("always");
			folder.setIcon(icon);
			folder.helixObj = obj;
			folder.populateChildren = populateChildren;
			parent_node.add(folder);
			//folder.addListener("dblclick", this.handleTreeDblClick, this);
			folder.addListener("changeOpen", function(e){
				if(e.getData() == true){
					var treeNode = e.getTarget();
					if(treeNode.hasChildren()){
						// already filled.  Bail out.
						return;
					}
					// Not filled, get some children:
					if(treeNode.populateChildren){
						treeNode.populateChildren.call( this, treeNode );
					}
				}
			}, this);
			return folder;
		},

		createTreeItem2: function (parent_node, obj, label, icon, editObject) {
			var item = new qx.ui.tree.TreeFile(label);
			item.setIcon(icon);
			item.helixObj = obj;
			item.editObject = editObject;
			parent_node.add(item);
			item.addListener("dblclick", function(e){
				var treeNode = e.getTarget();
				if(treeNode.helixObj && treeNode.editObject){
					treeNode.editObject.call( this, treeNode );
				}
			}, this);
			return item;
		},

		// This one is used by ASCFG - which still has the old form of tree handling.
		createAnimatedTreeItem0: function (parent_node, obj, label, icon, editObject) {
			var item = new qx.ui.tree.TreeFile(label);

			item.addListenerOnce("appear", function() {
				var element = item.getContainerElement().getDomElement();
				qx.bom.element.Scroll.intoView(element);

				var color = {duration: 2000, keyFrames : {
					0 : {"backgroundColor" : "#ffffff"},
					50 : {"backgroundColor" : "#ffffaa"},
					100 : {"backgroundColor": qx.bom.element.Style.get(element, "backgroundColor")}
				}};

				qx.bom.element.Animation.animate(element, color);
			}, this);

			item.setIcon(icon);
			item.helixObj = obj;
			item.editObject = editObject;
			item.addListener("dblclick", this.handleDisplay, this);

			parent_node.setOpen(true);
			parent_node.add(item);

			return item;
		},

		createAnimatedTreeItem: function (parent_node, obj, label, icon, editObject) {
			var item = new qx.ui.tree.TreeFile(label);

			item.addListenerOnce("appear", function() {
				var element = item.getContainerElement().getDomElement();
				qx.bom.element.Scroll.intoView(element);

				var color = {duration: 2000, keyFrames : {
					0 : {"backgroundColor" : "#ffffff"},
					50 : {"backgroundColor" : "#ffffaa"},
					100 : {"backgroundColor": qx.bom.element.Style.get(element, "backgroundColor")}
				}};

				qx.bom.element.Animation.animate(element, color);
			}, this);

			item.setIcon(icon);
			item.helixObj = obj;
			item.editObject = editObject;
			item.addListener("dblclick", function(e){
				var treeNode = e.getTarget();
				if(treeNode.helixObj && treeNode.editObject){
					treeNode.editObject.call( this, treeNode );
				}
			}, this);

			parent_node.setOpen(true);
			parent_node.add(item);

			return item;
		},

		handleTreeChangeOpen: function (e) {
			if (e.getData() == true) {
				this.handleExpand(e);
			}
		},

		handleTreeDblClick: function (e) {
			// check for a double click on the twisty icon
			if (e.getTarget().classname != "qx.ui.tree.core.FolderOpenButton") {
				this.handleExpand(e);
			}
		},

		handleTreeSelection: function (e) {
			var data = e.getData();
			if (data.length == 0) {
				// no selection
				return;
			}

			var treeNode = data[0];
			if (treeNode.helixObj) {
			} else {
			}

		},

		handleDisplay: function (e) {
			var treeNode = e.getTarget();
			if (treeNode.helixObj) {
				this.editObject(treeNode.helixObj);
			}
		},

		viewTreeSelection: function () {
			if (this.tree.getSelection().length === 0) {
				welcome.Statics.doAlert("There is nothing selected in the tree.",
					"Alert", this.setTreeFocus, this);
				return; // nothing selected.
			}

			var treeNode = this.tree.getSelection()[0];
			if (treeNode.editObject){
				treeNode.editObject.call( this, treeNode );
			} else if (treeNode.helixObj) {
				this.editObject(treeNode.helixObj);
			} else {
				welcome.Statics.doAlert("There is nothing to view for the current selection.",
					"Alert", this.setTreeFocus, this);
			}

		},

		setTreeFocus: function () {
			this.tree.focus();
		},

		pruneTree: function () {
			//TODO: close all of the open editors

			this.treeRoot.removeAll();
			this.fireEvent("treePruned");
		},

		// get Tables, Views, Users toolbar
		getTreeToolBar: function () {
			var toolbar = new qx.ui.toolbar.ToolBar();
			var part0 = new qx.ui.toolbar.Part();
			toolbar.add(part0);

			welcome.Statics.addToToolbar(part0, "welcome/icon/16x16/plain/refresh.png",
				"Refresh Tree", function(e) {this.doTada(); this.fillTree();}, this, this, "Refresh");

			welcome.Statics.addToToolbar(part0, "welcome/icon/16x16/plain/eye_blue.png",
				"View/Modify Tree Selection", this.viewTreeSelection, this, this, "View");

			welcome.Statics.addToToolbar(part0, "welcome/icon/16x16/plain/delete2.png",
				"Delete Tree Selection", this.deleteTreeSelection, this, this, "Delete");

			this.customizeToolbar(toolbar);

			this.treeToolbar = toolbar;
			return toolbar;
		},

		// get Data Browser toolbar
		getBrowserToolBar: function () {
			var toolbar = new qx.ui.toolbar.ToolBar();
			var part0 = new qx.ui.toolbar.Part();
			toolbar.add(part0);

			welcome.Statics.addToToolbar(part0, "welcome/icon/16x16/plain/refresh.png",
				"Refresh Tree", function(e) {this.doTada(); this.fillTree();}, this, this, "Refresh");

			welcome.Statics.addToToolbar(part0, "welcome/icon/16x16/plain/eye_blue.png",
				"View/Modify Tree Selection", this.viewBrowseTreeSelection, this, this, "View");

			this.customizeToolbar(toolbar);

			this.browserToolbar = toolbar;
			return toolbar;
		},

		handleTreeViewToggle : function (e) {
			if (this.container1.getVisibility() == "visible" ) {
				this.excludeTreeView();
			} else {
				this.showTreeView();

				//var skew = {duration: 500, origin : "top left", keyFrames : {
				//	0: {"skew" : "0deg"},
				//	50: {"skew": "+1deg"},
				//	100: {"skew": "0deg"}
				//}};

				//var element = this.container1.getContainerElement().getDomElement();
				//qx.bom.element.Animation.animate(element, skew);
			}
		},

		showTreeView : function () {
			this.container1.show();
		},

		excludeTreeView : function () {
			this.container1.exclude();
		},

		getMainToolBar: function () {
			var frame = new qx.ui.container.Composite(new qx.ui.layout.Grow);
			var toolbar = new qx.ui.toolbar.ToolBar;
			toolbar.setWidth(1024);
			frame.add(toolbar);

			//var fileMenu = new qx.ui.menubar.Button("File", null, this.getFileMenu());
			//var editMenu = new qx.ui.menubar.Button("Edit", null, this.getEditMenu());

			// create applications menu button
			var appsMenu = new qx.ui.toolbar.MenuButton("Applications", "welcome/icon/16x16/plain/signpost.png", this.getAppsMenu());
			appsMenu.setToolTipText("Switch between the Helix applications");

			// create tools menu
			var toolsmenu = this.getToolsMenu();

			// add help menu to bottom of tools menu
			toolsmenu.addSeparator();
			var helpbutton = new qx.ui.menu.Button("Help", null, null, this.getHelpMenu());
			toolsmenu.add(helpbutton);

			// create tools menu button
			var toolsMenu = new qx.ui.toolbar.MenuButton("Tools", "welcome/icon/16x16/plain/carabiner.png", toolsmenu);
			toolsMenu.setToolTipText("Operate this application");

			// create connection menu button
			this.serverMenu = new qx.ui.toolbar.MenuButton("Server: Not Connected", "welcome/icon/16x16/plain/server_delete.png", this.getServerMenu(this));
			this.serverMenu.setToolTipText("Control the Helix database connection");

			var frontPart = new qx.ui.toolbar.Part;
			var backPart = new qx.ui.toolbar.Part;

			toolbar.add(frontPart);
			toolbar.addSpacer();
			toolbar.add(backPart);

			frontPart.add(appsMenu);
			frontPart.add(new qx.ui.toolbar.Separator);
			frontPart.add(toolsMenu);
			backPart.add(this.serverMenu);

			var props = welcome.Singleton.getInstance().getUserProperties();
			if (props["CurrentConnection"] !== undefined) {
				this.serverMenu.setLabel(props["CurrentConnection"]);
				this.serverMenu.setIcon("welcome/icon/16x16/plain/server_connection.png")
				this.addCloseConnection(this);
			}

			this.toolbar = toolbar;
			this.menu = toolsmenu;

			return frame;
		},

		getFileMenu: function () {
			var menu = new qx.ui.menu.Menu;

			this.addMenuButton(menu, "Control+Alt+R", "Refresh List",
				"welcome/icon/16x16/plain/refresh.png", null, this.fillTree);

			return menu;
		},

		findNode: function (tree, key) {
			var items = tree.getItems(true, true);
			for (var i = 0; i < items.length; i++) {
                var label = items[i].getLabel().replace("(Filtered)", "");
                label = qx.lang.String.trim(label);
                if (label == key) return items[i];
			}
			return null;
		},

		/** We override the close method so that we can check for open, dirty editors.  If
		* any are found, then we'll warn the user before they leave the application.
		*/
		close: function () {
			// walk the list of editors, and see if any are dirty:
			var pages = this.tabView.getChildren();
			for (var i = 0, l = pages.length; i < l; i++) {
				if (pages[i].getLabel().charAt(0) === "*") {
					// Found a dirty editor.
					pages[i].getButton().setValue(true); // bring it to the front.
					return "You have unsaved changes in your editors.  Please save your changes before leaving this page.";
				}
			}
		}



	},

	statics: {

	}
});
