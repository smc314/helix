/* ************************************************************************

Copyright:

License:

Authors:

************************************************************************ */

/* ************************************************************************

#asset(admin/icon/16x16/plain/server_ok.png)
#asset(admin/icon/16x16/plain/server_edit.png)
#asset(admin/icon/16x16/plain/clients.png)
#asset(admin/icon/16x16/plain/security_agent_edit.png)
#asset(admin/icon/16x16/plain/security_agent.png)
#asset(admin/icon/16x16/plain/security_agent.png)
#asset(admin/icon/16x16/plain/text_rich_colored.png)
#asset(admin/icon/16x16/plain/user_time.png)
#asset(admin/icon/16x16/plain/window_cd.png)
#asset(admin/icon/16x16/plain/table2_run.png)
#asset(admin/icon/16x16/plain/window_cd.png)
#asset(admin/icon/16x16/plain/text_rich_colored.png)
#asset(admin/icon/16x16/plain/user_time.png)
#asset(admin/icon/16x16/plain/user_time.png)
#asset(admin/icon/16x16/plain/server_ok.png)
#asset(admin/icon/16x16/plain/server_edit.png)
#asset(admin/icon/16x16/plain/clients.png)
#asset(admin/icon/16x16/plain/text_align_justified.png)
#asset(admin/icon/16x16/plain/scroll.png)
#asset(admin/icon/16x16/plain/user_lock.png)
#asset(admin/icon/16x16/plain/users4_edit.png)
#asset(admin/icon/16x16/plain/sports_car.png)
#asset(admin/icon/16x16/plain/scroll.png)
#asset(admin/icon/16x16/plain/alarmclock.png)
#asset(admin/icon/16x16/plain/security_agent.png)
#asset(admin/icon/16x16/plain/security_agent_edit.png)

************************************************************************ */

/**
* This is the main application class of your custom application
*/
qx.Class.define("admin.Application",
{
	extend: qx.application.Standalone,

	include: [admin.StandardApp],

	/*
	*****************************************************************************
	MEMBERS
	*****************************************************************************
	*/

	members:
	{
		/**
		* This method contains the initial application code and gets called
		* during startup of the application
		*
		* @lint ignoreDeprecated(alert)
		*/
		main: function () {
			// Call super class
			this.base(arguments);
			this.ApplicationName = "Helix Administration";
			this.setupStandardApp();

		},

		fillTree: function () {
			this.treeRoot.removeAll();

			// Main Tree Items:
			// Users
			// Groups
			// Scheduled Tasks

			// Main Tools Items:
			// New -> User
			// New -> Group
			// New -> Scheduled Task
			// Logs ->
			// Manage Server Configuration (both helix.xml and system properties)
			// Manage Server Actions
			// Manage Server Sessions
			// Monitor Long Running Tasks
			// Monitor Hit Map - Server Profiling
			// Show/Hide Sidebar
			// Help ->

			admin.user.UserTreeNodes.createRootNode( this.treeRoot );
			admin.user.GroupTreeNodes.createRootNode( this.treeRoot );
			admin.admin.ScheduleTreeNodes.createRootNode( this.treeRoot );

			if(qx.core.Environment.get("qx.debug")){
				admin.dev.DevTreeNodes.createRootNode( this.treeRoot );
			}

			var sysprops = admin.Singleton.getInstance().getSystemProperties();
			if(sysprops[admin.Singleton.AreWeHomeBase] === "true"){
				admin.admin.ReleaseTreeNodes.createRootNode( this.treeRoot );
				admin.admin.SupportTreeNodes.createRootNode( this.treeRoot );
			}

			/*
			admin.utils.LoadTestTreeNodes.createRootNode( this.treeRoot );

			admin.utils.UnitTestTreeNodes.createRootNode( this.treeRoot );
			admin.utils.SqlTestTreeNodes.createRootNode( this.treeRoot );
			admin.admin.SqlWorkTreeNodes.createRootNode( this.treeRoot );

			if(qx.core.Environment.get("qx.debug")){
				admin.dev.DevTreeNodes.createRootNode( this.treeRoot );
			}
			*/
		},

		handleExpand: function (e) {
			var treeNode = e.getTarget();
		},

		editObject: function (obj) {
			var treeNode = this.tree.getSelection()[0];
		},

		showServerStatus: function () {
			var tab_page = this.addEditingTab("Helix Server Status");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/server_ok.png");
				tab_page.add(new admin.admin.ServerStatus(0), { flex: 10 });
			}
		},

		showServerSettings: function () {
			var tab_page = this.addEditingTab("Helix Server Settings");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/server_edit.png");
				tab_page.add(new admin.admin.ServerSettings(0), { flex: 10 });
			}
		},

		showServerSessions: function () {
			var tab_page = this.addEditingTab("Helix Server Sessions");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/clients.png");
				tab_page.add(new admin.admin.ServerSessions(0), { flex: 10 });
			}
		},

		showManageServerLogs: function () {
			var tab_page = this.addEditingTab("Helix Server Log Settings");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/security_agent_edit.png");
				tab_page.add(new admin.admin.ManageServerLogs(0), { flex: 10 });
			}
		},

		showMonitorServerLogs: function () {
			var tab_page = this.addEditingTab("Helix Server Logs");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/security_agent.png");
				tab_page.add(new admin.admin.MonitorServerLogs(0), { flex: 10 });
			}
		},

		showMonitorLRTasks : function () {
			var tab_page = this.addEditingTab("Long Running Tasks");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/security_agent.png");
				tab_page.add(new admin.admin.MonitorLRTask(0), { flex: 10 });
			}
		},

		showExecuteSQL: function () {
			admin.admin.SqlWorkTreeNodes.newObject();
		},

		showLayoutEditor: function () {
			var tab_page = this.addEditingTabDup("Layout Editor");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/text_rich_colored.png");
				tab_page.add(new admin.utils.LayoutEditor(0), { flex: 10 });
			}
		},

		showMonitorHitMap : function () {
			var tab_page = this.addEditingTabDup("Monitor Hit Map");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/user_time.png");
				tab_page.add(new admin.admin.MonitorHitMap(0), { flex: 10 });
			}
		},

		showInstallUtilities: function () {
			var tab_page = this.addEditingTab("Install Utilities");
			if (tab_page != null) {
				tab_page.setIcon("admin/icon/16x16/plain/window_cd.png");
				var iframe = new qx.ui.embed.Iframe().set({
					source: "/installs/index.html"
				});
				tab_page.add(iframe, { flex: 10 });
			}
		},

		customizeToolbar: function (toolbar) {
			//var part3 = new qx.ui.toolbar.Part();
			//toolbar.add(part3);

		},

		getToolsMenu: function () {
			var menu = new qx.ui.menu.Menu;

			var button = new qx.ui.menu.Button("New", null, null, this.getNewMenu());
			admin.Statics.setHtmlID(button, "New");
			menu.add(button);

			menu.addSeparator();

			var logsButton = new qx.ui.menu.Button("Logs", null, null, this.getLogsMenu());
			admin.Statics.setHtmlID(logsButton, "Logs");
			menu.add(logsButton);

			menu.addSeparator();

			this.addMenuButton(menu, "Control+Alt+W", "SQL Workbench",
				"admin/icon/16x16/plain/table2_run.png", "SQL Workbench", this.showExecuteSQL);

			this.addMenuButton(menu, null, "Download Drivers",
				"admin/icon/16x16/plain/window_cd.png", null, this.showInstallUtilities);

			menu.addSeparator();

			this.addMenuButton(menu, "Control+Alt+L", "Layout Editor",
				"admin/icon/16x16/plain/text_rich_colored.png", "Layout Editor", this.showLayoutEditor);

			menu.addSeparator();

			this.addMenuButton(menu, "Control+Alt+H", "Monitor Hit Map",
				"admin/icon/16x16/plain/user_time.png", "Monitor Hit Map", this.showMonitorHitMap);

			this.addMenuButton(menu, "Control+Alt+R", "Monitor Long Running Tasks",
				"admin/icon/16x16/plain/user_time.png", "Monitor Long Running Tasks", this.showMonitorLRTasks);

			/* These are not ready yet
			menu.addSeparator();

			this.addMenuButton(menu, null, "Server Status",
				"admin/icon/16x16/plain/server_ok.png", null, this.showServerStatus);

			this.addMenuButton(menu, null, "Server Settings",
				"admin/icon/16x16/plain/server_edit.png", null, this.showServerSettings);

			this.addMenuButton(menu, null, "Server Sessions",
				"admin/icon/16x16/plain/clients.png", null, this.showServerSessions);
			*/

			menu.addSeparator();

			this.addMenuButton(menu, "Control+Alt+Z", "Show/Hide Side Bar",
				"admin/icon/16x16/plain/text_align_justified.png", "Toggle visibility of the tree view.", this.handleTreeViewToggle);


			return menu;
		},

		getNewMenu: function () {
			var menu = new qx.ui.menu.Menu;

			this.addMenuButton(menu, "Control+Alt+V", "Visual Layout",
				"admin/icon/16x16/plain/scroll.png", "New Visual Layout",
				admin.dev.DevTreeNodes.newVisualLayout);

			this.addMenuButton(menu, "Control+Alt+U", "User",
				"admin/icon/16x16/plain/user_lock.png", "New User",
				admin.user.UserTreeNodes.newObject);

			this.addMenuButton(menu, "Control+Alt+G", "Group",
				"admin/icon/16x16/plain/users4_edit.png", "New Group",
				admin.user.GroupTreeNodes.newObject);

			/*
			this.addMenuButton(menu, "Control+Alt+T", "Load Test",
				"admin/icon/16x16/plain/sports_car.png", "New Load Test",
				admin.utils.LoadTestTreeNodes.newObject);

			this.addMenuButton(menu, "Control+Alt+Q", "SQL Test",
				"admin/icon/16x16/plain/scroll.png", "New SQL Test",
				admin.utils.SqlTestTreeNodes.newObject);
			*/

			this.addMenuButton(menu, "Control+Alt+K", "Scheduled Task",
				"admin/icon/16x16/plain/alarmclock.png", "New Scheduled Task",
				admin.admin.ScheduleTreeNodes.newObject);

			return menu;
		},

		getLogsMenu: function() {

			var menu = new qx.ui.menu.Menu;

			this.addMenuButton(menu, null, "View Helix Logs",
				"admin/icon/16x16/plain/security_agent.png", null, this.showMonitorServerLogs);

			this.addMenuButton(menu, null, "Helix Logging Configuration",
				"admin/icon/16x16/plain/security_agent_edit.png", null, this.showManageServerLogs);

			return menu;
		},

		deleteTreeSelection: function () {
			if(this.tree.getSelection().length === 0){
				admin.Statics.doAlert("There is nothing selected in the tree to delete.", "Alert");
				return;
			}

			var treeNode = this.tree.getSelection()[0];
			if(!treeNode.helixObj){
				admin.Statics.doAlert("The current selection cannot be deleted.");
				return;
			}

			// Delegate to the other classes to handle the delete. Keeps things cleaner this way.
			if(treeNode.helixObj instanceof admin.sqldo.User){
				admin.user.UserTreeNodes.doDelete( treeNode );
			} else if(treeNode.helixObj instanceof admin.sqldo.Group){
				admin.user.GroupTreeNodes.doDelete( treeNode );
			} else if(treeNode.helixObj instanceof admin.sqldo.SchedItem){
				admin.admin.ScheduleTreeNodes.doDelete( treeNode );
			} else {
				admin.Statics.doAlert("The current selection cannot be deleted because it's not a recognized type.");
				return;
			}

		},

		setAdminPassword: function () {
		},

		setAuthKey: function () {
		},

		doNew : function() {
		},

		addNewTreeItem: function(parentLabel, childLabel, helixObj, icon, editObject) {
			var node = this.findNode(this.treeRoot, parentLabel);
			if(!node){
				admin.Statics.doAlert("Programming error: unknown tree node parent '" + parentLabel + "'.");
				return;
			}

			// return if the tree item is not new
			var cnode = this.findNode(node, childLabel);
			if (cnode) {
				this.tree.resetSelection();
				this.tree.addToSelection(cnode);
				return;
			}

			// add the new node to the tree
			this.createAnimatedTreeItem(node, helixObj, childLabel, icon, editObject);
		}

	},

	/*
	*****************************************************************************
	DESTRUCT
	*****************************************************************************
	*/

	destruct: function () {
		//this._disposeObjects();
	}

});
