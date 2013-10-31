/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/* ************************************************************************
#asset(dev/icon/basic_foundation/16x16/plain/refresh.png)
#asset(dev/icon/basic_foundation/32x32/shadow/sign_warning.png)
************************************************************************ */
qx.Class.define("dev.ObjectTreeListDisplay",
{
	extend : qx.ui.container.Composite,
	construct : function()
	{
		this.base(arguments);
		this.setLayout(new qx.ui.layout.VBox());
		this.runImmediateQuery = true;
		this.doAddNew = true;
		this.setupNamesAndFunctions();
		this.toolbar = new qx.ui.toolbar.ToolBar;
		this.initializeToolbar(this.toolbar);
		this.add(this.toolbar);
		this.loadDynamicLayouts(0, function()
		{
			// Anything that sub-classes want to do prior to the table:
			this.preTableCreate();
			this.doCreateTreeTable();
		}, this);
	},
	members :
	{
		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function()
		{
			this.doAddNew = false;
			this.deleteApi = null;
			this.editFormPrefix = "Product: ";
			this.newFormPrefix = "New Product";
		},

		/** This method allows sub-classes to do things to our layout before
		  * we create the display table and add it to our layout.
		  */
		preTableCreate : function() {
		},
		doCreateTreeTable : function()
		{
			this.tree = new qx.ui.treevirtual.TreeVirtual(this.getColumnNames());
			this.tree.set(
			{
				height : 1,
				minHeight : 1
			});
			this.tree.setAlwaysShowOpenCloseSymbol(true);
			this.tree.setContextMenu(this.createRMCMenu());
			this.tree.addListener("dblclick", this.onDoubleClick, this);
			this.tree.getSelectionModel().setSelectionMode(qx.ui.table.selection.Model.MULTIPLE_INTERVAL_SELECTION);
			this.tree.getDataRowRenderer().setHighlightFocusRow(false);
			this.tree.setFocusCellOnMouseMove(false);
			this.tree.setShowCellFocusIndicator(false);
			this.tree.setAlwaysUpdateCells(false);
			if (this.runImmediateQuery) {
				this.getServerData(this.tree.getDataModel());
			}

			// Obtain the resize behavior object to manipulate
			var resizeBehavior = this.tree.getTableColumnModel().getBehavior();

			// Ensure that the tree column remains sufficiently wide
			resizeBehavior.set(0,
			{
				width : "1*",
				minWidth : 180
			});
			this.add(this.tree, {
				flex : 1
			});
		},

		/**
		 * This function is responsible for initializing our toolbar
		 *
		 * @type member
		 */
		initializeToolbar : function(tb)
		{
			// Save/Cancel part
			this.toolbar_part1 = new qx.ui.toolbar.Part;

			// Refresh button
			dev.Statics.addToToolbar(this.toolbar_part1, "dev/icon/basic_foundation/16x16/plain/refresh.png", "Refresh", this.rmcFullRefresh, this, this);
			tb.add(this.toolbar_part1);
			return tb;
		},

		/** This method allows sub-classes to set the column display names
		  * that will be used for this query display.
		  */
		getColumnNames : function() {
			return [];
		},

		/** This method allows sub-classes to set the query that will be
		  * used to populate the data for this display.
		  */
		getServerData : function(dataModel)
		{
			var rowData = [];
			dataModel.setData(rowData);
		},
		onDoubleClick : function(ev) {
			this.rmcEdit(ev);
		},
		createRMCMenu : function(ev)
		{
			this.rmc = new qx.ui.menu.Menu;

			// refresh
			dev.Statics.addToRMCMenu(this.rmc, "Refresh", 'dev/icon/basic_foundation/16x16/plain/refresh.png', this.rmcFullRefresh, this);

			// edit
			dev.Statics.addToRMCMenu(this.rmc, "Edit...", 'dev/icon/basic_foundation/16x16/plain/edit.png', this.rmcEdit, this);

			// Add New...
			if (this.doAddNew) {
				dev.Statics.addToRMCMenu(this.rmc, "Add New...", 'dev/icon/basic_foundation/16x16/plain/document_new.png', this.addNew, this);
			}

			// Delete...
			if (this.deleteApi !== null) {
				dev.Statics.addToRMCMenu(this.rmc, "Delete...", 'dev/icon/basic_foundation/16x16/plain/delete2.png', this.doDelete, this);
			}

			//this.rmc.addToDocument();
			return this.rmc;
		},
		hideRMC : function()
		{
			if (!this.rmc) {
				return;
			}
			this.rmc.hide();
		},
		rmcFullRefresh : function(ev) {
			this.rmcRefresh();
		},
		rmcRefresh : function(ev) {
			this.getServerData(this.tree.getDataModel());
		},

		/** This allows subclasses to tell us which forms to use for editing
		  * individual objects from our display list.
		  */
		getEditForm : function(id) {
			return null;
		},
		rmcEdit : function(ev)
		{
			var targetTabView = this.getTargetTabView();
			var row = this.tree.getFocusedRow();
			var id = this.tree.getTableModel().getValue(1, row);
			var page = dev.StandardPage.addStandardTab(targetTabView, this.editFormPrefix + id, true);
			var edit = this.getEditForm(id);
			page.add(edit, {
				flex : 1
			});
		},

		/** This function is used to find the right place to open a new view in the display.
		  * We default to just our current tabview, but subclasses may override this to change
		  * the behaviour as they required.
		  */
		getTargetTabView : function()
		{
			var targetTabView = null;
			var parentTaskPage = dev.Statics.findQXParent(this, dev.StandardPage);
			if (parentTaskPage === null) {
				targetTabView = dev.Statics.findQXParent(this, qx.ui.tabview.TabView);
			} else {
				if ((parentTaskPage.detailsTabView) && !parentTaskPage.detailsTabView.__disposed) {
					targetTabView = parentTaskPage.detailsTabView;
				} else {
					targetTabView = dev.Statics.findQXParent(this, qx.ui.tabview.TabView);
				}
			}
			return targetTabView;
		},

		/** This function will return an array that has the id's
		  * of all of the currently selected rows from this.tree.
		  */
		getSelectedIDs : function()
		{
			var selectedRowData = [];
			var smodel = this.tree.getSelectionModel();
			var tmodel = this.tree.getTableModel();
			smodel.iterateSelection(function(index) {
				selectedRowData.push(tmodel.getValue(1, index));
			});
			return selectedRowData;
		},

		/** This function will convert our selected ID's to a comma
		  * separated list that is typical for the server to use during
		  * multi-update calls.
		  */
		getSelectedIDList : function()
		{
			var idList = this.getSelectedIDs();

			// Add the assignment information to each task selected:
			var string = "";
			for (var i = 0, l = idList.length; i < l; i++) {
				if (i === 0) {
					string = idList[i];
				} else {
					string = string + "," + idList[i];
				}
			}
			return string;
		},

		/** This will set the data object on the tree node that has the given ID.
		  * The ID comes from calls to dataModel.addBranch().
		  */
		setdevDataObject : function(nodeID, dataObject)
		{
			var node = this.tree.getTableModel().getData()[nodeID];
			if (node) {
				node.devDataObject = dataObject;
			}
		},

		/** This will get the data object on the tree node that has the given ID.
		  * The ID comes from calls to dataModel.addBranch().
		  */
		getdevDataObject : function(nodeID)
		{
			var node = this.tree.getTableModel().getData()[nodeID];
			if (node) {
				return node.devDataObject;
			} else {
				return null;
			}
		},
		addNew : function(ev)
		{
			this.hideRMC();                               // hide the RMC menu.
			var page = dev.StandardPage.addStandardTab(this.getTargetTabView(), this.newFormPrefix, true);
			var edit = this.getEditForm(0);
			page.add(edit, {
				flex : 1
			});
		},
		doDelete : function(ev)
		{
			this.hideRMC();                               // hide the RMC menu.
			if (this.tree.getSelectionModel().isSelectionEmpty())
			{
				dev.Statics.doAlert("Nothing selected to delete!");
				return;
			}
			var windowTitle = "Deleting...";
			var windowIcon = "dev/icon/basic_foundation/32x32/shadow/sign_warning.png";
			var windowLabel = "Are you sure you want to delete the selected items?";
			var tmpWindow = new dev.dialog.QuestionDialog(windowTitle, windowIcon, windowLabel);
			qx.core.Init.getApplication().getRoot().add(tmpWindow);
			tmpWindow.addOkEventListener("execute", function()
			{
				var idString = this.getSelectedIDList();
				this.deleteApi(idString, function()
				{
					this.rmcFullRefresh();
					this.tree.getSelectionModel().resetSelection();
				}, this);
			}, this);
			tmpWindow.open();
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
			var url = "/script/layouts/" + this.dynamicLayouts[start].name;

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
		},
		setAutoRefreshTimer : function(callback, recurTime)
		{
			// if we already have a timer, then just return
			if (this.refreshTimer) {
				return;
			}
			var timer = qx.util.TimerManager.getInstance();
			this.refreshTimer = timer.start(callback, recurTime, this, null, 30000);
		},
		cancelAutoRefreshTimer : function() {
			if (this.refreshTimer)
			{
				qx.util.TimerManager.getInstance().stop(this.refreshTimer);
				this.refreshTimer = null;
			}
		}
	},
	statics : {

	},
	destruct : function()
	{
		if (this.refreshTimer)
		{
			qx.util.TimerManager.getInstance().stop(this.refreshTimer);
			this.refreshTimer = null;
		}
		dev.Statics.cleanupStandardTable(this.tree);

		// RMC Menus need to be disposed of as simple fields because

		// they are really now owned by the object (tree, table, etc.)

		// for which they were created
		this._disposeFields("rmc");
		this._disposeObjects("tree", "toolbar", "toolbar_part1");
		dev.Statics.destroyExtraObjects(this);
	}
});
