/* ************************************************************************

Copyright:

License:

Authors:

************************************************************************ */

/* ************************************************************************

#asset(dev/icon/16x16/plain/text_align_justified.png)
#asset(dev/icon/16x16/plain/scroll.png)
#asset(dev/icon/16x16/plain/scroll.png)
#asset(dev/icon/16x16/plain/scroll.png)
#asset(dev/icon/16x16/plain/sports_car.png)
#asset(dev/icon/16x16/plain/scroll.png)
#asset(dev/icon/16x16/plain/security_agent.png)
#asset(dev/icon/16x16/plain/security_agent_edit.png)

************************************************************************ */

/**
* This is the main application class of your custom application
*/
qx.Class.define("dev.Application",
{
	extend: qx.application.Standalone,

	include: [dev.StandardApp],

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
			this.ApplicationName = "Helix Development";
			this.setupStandardApp();

		},

		fillTree: function () {
			this.treeRoot.removeAll();

			// Main Tree Items:
			// Data Objects
			// Virtual Layouts
			// SQL Workbench
			// Load Tests
			// Unit Tests
			// Sql Tests

			// Main Tools Items:
			// New -> Data Object
			// New -> Virtual Layout
			// New -> SQL Workfile
			// New -> Load Test
			// New -> Unit Test
			// New -> SQL Test
			// Show/Hide Sidebar
			// Help ->

			dev.dataobj.DataObjectTreeNodes.createRootNode( this.treeRoot );
			dev.screens.LayoutTreeNodes.createRootNode( this.treeRoot );

			dev.utils.SqlWorkTreeNodes.createRootNode( this.treeRoot );

			dev.utils.LoadTestTreeNodes.createRootNode( this.treeRoot );

			dev.utils.UnitTestTreeNodes.createRootNode( this.treeRoot );
			dev.utils.SqlTestTreeNodes.createRootNode( this.treeRoot );
		},

		handleExpand: function (e) {
			var treeNode = e.getTarget();
		},

		editObject: function (obj) {
			var treeNode = this.tree.getSelection()[0];
		},

		showExecuteSQL: function () {
			dev.utils.SqlWorkTreeNodes.newObject();
		},

		customizeToolbar: function (toolbar) {
			//var part3 = new qx.ui.toolbar.Part();
			//toolbar.add(part3);

		},

		getToolsMenu: function () {
			var menu = new qx.ui.menu.Menu;

			var button = new qx.ui.menu.Button("New", null, null, this.getNewMenu());
			dev.Statics.setHtmlID(button, "New");
			menu.add(button);

			this.addMenuButton(menu, "Control+Alt+Z", "Show/Hide Side Bar",
				"dev/icon/16x16/plain/text_align_justified.png", "Toggle visibility of the tree view.", this.handleTreeViewToggle);


			return menu;
		},

		getNewMenu: function () {
			var menu = new qx.ui.menu.Menu;

			// Main Tools Items:
			// New -> Data Object
			// New -> Virtual Layout
			// New -> SQL Workfile
			// New -> Load Test
			// New -> Unit Test
			// New -> SQL Test
			// Show/Hide Sidebar
			// Help ->

			this.addMenuButton(menu, "Control+Alt+O", "Data Object",
				"dev/icon/16x16/plain/scroll.png", "New Data Object",
				dev.dataobj.DataObjectTreeNodes.newObject);

			this.addMenuButton(menu, "Control+Alt+V", "Visual Layout",
				"dev/icon/16x16/plain/scroll.png", "New Visual Layout",
				dev.screens.LayoutTreeNodes.newObject);

			this.addMenuButton(menu, "Control+Alt+Q", "SQL Workfile",
				"dev/icon/16x16/plain/scroll.png", "New SQL Workfile",
				dev.utils.SqlWorkTreeNodes.newObject);

			this.addMenuButton(menu, "Control+Alt+T", "Load Test",
				"dev/icon/16x16/plain/sports_car.png", "New Load Test",
				dev.utils.LoadTestTreeNodes.newObject);

			this.addMenuButton(menu, "Control+Alt+Q", "SQL Test",
				"dev/icon/16x16/plain/scroll.png", "New SQL Test",
				dev.utils.SqlTestTreeNodes.newObject);

			return menu;
		},

		getLogsMenu: function() {

			var menu = new qx.ui.menu.Menu;

			this.addMenuButton(menu, null, "View Helix Logs",
				"dev/icon/16x16/plain/security_agent.png", null, this.showMonitorServerLogs);

			this.addMenuButton(menu, null, "Helix Logging Configuration",
				"dev/icon/16x16/plain/security_agent_edit.png", null, this.showManageServerLogs);

			return menu;
		},

		deleteTreeSelection: function () {
			if(this.tree.getSelection().length === 0){
				dev.Statics.doAlert("There is nothing selected in the tree to delete.", "Alert");
				return;
			}

			var treeNode = this.tree.getSelection()[0];
			if(!treeNode.helixObj){
				dev.Statics.doAlert("The current selection cannot be deleted.");
				return;
			}

			// Delegate to the other classes to handle the delete. Keeps things cleaner this way.
			if(treeNode.helixObj instanceof dev.sqldo.User){
				dev.user.UserTreeNodes.doDelete( treeNode );
			} else if(treeNode.helixObj instanceof dev.sqldo.Group){
				dev.user.GroupTreeNodes.doDelete( treeNode );
			} else if(treeNode.helixObj instanceof dev.sqldo.SchedItem){
				dev.dev.ScheduleTreeNodes.doDelete( treeNode );
			} else {
				dev.Statics.doAlert("The current selection cannot be deleted because it's not a recognized type.");
				return;
			}

		},

		setdevPassword: function () {
		},

		setAuthKey: function () {
		},

		doNew : function() {
		},

		addNewTreeItem: function(parentLabel, childLabel, helixObj, icon, editObject) {
			var node = this.findNode(this.treeRoot, parentLabel);
			if(!node){
				dev.Statics.doAlert("Programming error: unknown tree node parent '" + parentLabel + "'.");
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
