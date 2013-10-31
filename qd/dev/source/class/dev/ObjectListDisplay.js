/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/* ************************************************************************
#asset(dev/icon/basic_foundation/16x16/plain/refresh.png)
#asset(dev/icon/basic_foundation/32x32/shadow/sign_warning.png)
************************************************************************ */
qx.Class.define("dev.ObjectListDisplay",
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
			this.doCreateTable();
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
		closePage : function()
		{
			var our_page = dev.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return;
			}
			our_page.getButton().fireDataEvent("closetab", our_page.getButton());
		},

		/** This method allows sub-classes to do things to our layout before
		  * we create the display table and add it to our layout.
		  */
		preTableCreate : function() {
		},

		/** This method is used to create our table.
		 *
		 */
		doCreateTable : function()
		{
			// table model
			var tableModel = new qx.ui.table.model.Simple();
			tableModel.setColumns(this.getColumnNames());
			if (this.runImmediateQuery) {
				this.getServerData(tableModel);
			}

			// Customize the table column model.  We want one that automatically

			// resizes columns.
			var custom = {
				tableColumnModel : function(obj) {
					return new qx.ui.table.columnmodel.Resize(obj);
				}
			};

			// table
			this.table = new qx.ui.table.Table(tableModel, custom);
			this.table.set(
			{
				height : 1,
				minHeight : 1
			});
			this.table.getSelectionModel().setSelectionMode(qx.ui.table.selection.Model.MULTIPLE_INTERVAL_SELECTION);
			this.table.setContextMenu(this.createRMCMenu());
			this.table.addListener("dblclick", this.onDoubleClick, this);

			// Specify the resize behavior...  First, get the table column model,

			// which we specified to be a ResizeTableColumModel object.
			var tcm = this.table.getTableColumnModel();

			// Obtain the behavior object to manipulate
			var resizeBehavior = tcm.getBehavior();

			// This uses the set() method to set all attriutes at once; uses flex
			resizeBehavior.set(0,
			{
				width : "1*",
				minWidth : 45,
				maxWidth : 80
			});
			this.add(this.table, {
				flex : 1
			});
		},

		/** This method allows sub-classes to set the column display names
		  * that will be used for this query display.
		  */
		getColumnNames : function() {
			return [];
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

		/** This method allows sub-classes to set the query that will be
		  * used to populate the data for this display.
		  */
		getServerData : function(tableModel)
		{
			var rowData = [];
			tableModel.setData(rowData);
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
			this.getServerData(this.table.getTableModel());
		},

		/** This allows subclasses to tell us which forms to use for editing
		  * individual objects from our display list.
		  */
		getEditForm : function(id) {
			return null;
		},
		rmcEdit : function(ev)
		{
			this.hideRMC();                               // hide the RMC menu.
			if (this.table.getSelectionModel().isSelectionEmpty())
			{
				dev.Statics.doAlert("Nothing selected to edit!");
				return;
			}
			var targetTabView = this.getTargetTabView();
			var row = this.table.getFocusedRow();
			var id = this.table.getTableModel().getValue(0, row);
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
		  * of all of the currently selected rows from this.table.
		  */
		getSelectedIDs : function()
		{
			var selectedRowData = [];
			var smodel = this.table.getSelectionModel();
			var tmodel = this.table.getTableModel();
			smodel.iterateSelection(function(index) {
				selectedRowData.push(tmodel.getValue(0, index))
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
			if (this.table.getSelectionModel().isSelectionEmpty())
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
				this.deleteApi(idString, function() {
					this.rmcFullRefresh();
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
			this.refreshTimer = timer.start(callback, recurTime, this);
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
		dev.Statics.cleanupStandardTable(this.table);

		// RMC Menus need to be disposed of as simple fields because

		// they are really now owned by the object (tree, table, etc.)

		// for which they were created
		this._disposeFields("rmc");
		this._disposeObjects("table", "toolbar", "toolbar_part1");
		dev.Statics.destroyExtraObjects(this);
	}
});
