/* ************************************************************************

Copyright: 2008 - 2011 Hericus Software, LLC

License: MIT License

Authors:  Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/bullet_triangle_glass_green.png)
#asset(admin/icon/16x16/plain/code_c.png)
#asset(admin/icon/16x16/plain/code_csharp.png)
#asset(admin/icon/16x16/plain/code_java.png)
#asset(admin/icon/64x64/shadow/scroll_run.png)
#asset(admin/icon/16x16/plain/barcode.png)
#asset(admin/icon/16x16/plain/barcode.png)
#asset(admin/templates/CTemplate.c)
#asset(admin/icon/64x64/shadow/code_c.png)
#asset(admin/templates/CSharpTemplate.cs)
#asset(admin/icon/64x64/shadow/code_csharp.png)
#asset(admin/templates/JavaTemplate.java)
#asset(admin/icon/64x64/shadow/code_java.png)
#asset(admin/icon/16x16/plain/scroll_run.png)
************************************************************************ */
qx.Class.define("admin.admin.ExecuteSQL", {
	extend: admin.ObjectEdit,

	construct: function (object_id) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({ name: "ExecuteSQL.MainPage.xml", doc: null });
		this.dynamicLayouts.push({ name: "ExecuteSQL.ResultPage.xml", doc: null });
		this.dynamicLayouts.push({ name: "ExecuteSQL.MetaPage.xml", doc: null });

		this.dataObject = object_id;

		this.base(arguments, object_id);
	},

	members: {

		/** This is where the subclasses will tell us which API functions to use,
		* which callbacks to use, which names to use, etc.
		*/
		setupNamesAndFunctions: function () {
			this.selectApiCall = admin.Api.GetSQLWork;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		* the parent class functionality by adding our own icons and actions.
		*/
		initializeToolbar: function (tb) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb); // Call the parent class first

			// Then add any other actions that you would like here:
			var part = new qx.ui.toolbar.Part;

			admin.Statics.addToToolbarWithShortcut(part, "admin/icon/16x16/plain/bullet_triangle_glass_green.png",
				"Run SQL Statement", this.runSQL, this, this, null, "Run SQL");

			part.addSeparator();

			admin.Statics.addToToolbarWithShortcut(part, "admin/icon/16x16/plain/code_c.png",
				"Generate C Code For SQL", this.genCCode, this, this, null, "C Code");

			admin.Statics.addToToolbarWithShortcut(part, "admin/icon/16x16/plain/code_csharp.png",
				"Generate C# Code For SQL", this.genCSharpCode, this, this, null, "C# Code");

			admin.Statics.addToToolbarWithShortcut(part, "admin/icon/16x16/plain/code_java.png",
				"Generate Java Code For SQL", this.genJavaCode, this, this, null, "Java Code");

			tb.add(part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			this.resultsTabPage = this.createResultTab(admin.Statics.addEditorSubTab(this.tabview, "Results", false));
			this.createMetaTab(admin.Statics.addEditorSubTab(this.tabview, "Results Metadata", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		* set of form fields.
		*/
		createMainTab: function (tab_page) {
			var live = this.createOverviewLayout( tab_page, "SQL Workbench",
				"admin/icon/64x64/shadow/scroll_run.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getFileName() );

			this.addStatusHeading("Select Results");
			this.overview_label1 = this.addStatusItem("Column Count:",
				"admin/icon/16x16/plain/barcode.png");
			this.overview_label2 = this.addStatusItem("Row Count:",
				"admin/icon/16x16/plain/barcode.png");

			this.addStatusHeading("Hint");
			this.addStatusHint("To execute a SQL statement, enter the statement in the text box to the right " +
							   "and choose the Run SQL button on the toolbar.<p>Use Control-V to paste one or more " +
							   "statements into the text box.<p> To run a single SQL statement, highlight the statement " +
							   "in the text box and choose the Run SQL button on the toolbar.");

			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("ExecuteSQL.MainPage.xml"),
				live);

			this.SQLBorder.setNativeContextMenu( true );
			this.SQLBorder.addListenerOnce("appear", function() {
				// Timeout needed for chrome to not get the ACE layout wrong and show
				// the text on top of the gutter
				qx.event.Timer.once(function() {
					var container = this.SQLBorder.getContentElement().getDomElement();
					var editor = this.SqlField = ace.edit( container );
					editor.setTheme( "ace/theme/chrome" );
					editor.getSession().setMode("ace/mode/sql");

					// Copy in any initial data that might be available:
					if(this.dataObject){
						this.SqlField.getSession().setValue( this.dataObject.getSql() );
					}

					var self = this;
					this.SqlField.getSession().selection.on('changeSelection', function(e) {
						self.sel = self.SqlField.getSession().getTextRange( editor.getSelectionRange() );
					});

					this.SQLBorder.addListener("resize", function() {
						// use a timeout to let the layout queue apply its changes to the dom
						window.setTimeout(function() {
							self.SqlField.resize();
						}, 0 );
					});

					this.SqlField.commands.addCommand({
						name: "SaveSql",
						bindKey: {win: 'Ctrl-S',  mac: 'Command-S'},
						exec: function(editor) {
							self.doSaveToServer();
						}
					});

					this.SqlField.on("change", function(e) {
						self.fieldModified();
					} );

					this.SqlField.focus();
				}, this, 500);
			}, this);

			admin.Statics.addToDropDown( this.HostDBField, "Legacy Data Server", "lds" );
			admin.Statics.addToDropDown( this.HostDBField, "DB2/zOS", "db2" );
			admin.Statics.addToDropDown( this.HostDBField, "SQL/DS or DB2/zVSE", "sds" );
			admin.Statics.addToDropDown( this.HostDBField, "Datacom", "dso" );
			admin.Statics.addToDropDown( this.HostDBField, "Director-Config", "Director-Config" );
			//admin.Statics.addToDropDown( this.HostDBField, "Director-Logs", "Director-Logs" );
			admin.Statics.addToDropDown( this.HostDBField, "Director-MFLogs", "Director-MFLogs" );

		},

		/** This creates a standard tab that is controlled by the layout page
		* rendered onto it.
		*/
		createResultTab: function (tab_page) {
			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("ExecuteSQL.ResultPage.xml"),
				tab_page);

			this.resultsTable.getDataRowRenderer()._renderFont(new qx.bom.Font(12, ["monospace"]));
		},

		/** This creates a standard tab that is controlled by the layout page
		* rendered onto it.
		*/
		createMetaTab: function (tab_page) {
			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("ExecuteSQL.MetaPage.xml"),
				tab_page);

			this.metaTable.getDataRowRenderer()._renderFont(new qx.bom.Font(12, ["monospace"]));

			// make the column editable so copy function works
			this.metaTable.getTableModel().setColumnEditable(1, true);
			this.metaTable.getTableModel().setColumnEditable(2, true);
			this.metaTable.getTableModel().setColumnEditable(3, true);
			this.metaTable.getTableModel().setColumnEditable(4, true);
		},

		getCurrentSQL : function() {

			var sql = (this.sel) ? this.sel : this.SqlField.getValue();
			if (!sql) {
				admin.Statics.doAlert("No SQL statement found. Enter a valid SQL statement.")
				return null;
			}

			sql = qx.lang.String.trimRight(sql);
			if (sql.length == 0) {
				admin.Statics.doAlert("The SQL statement contains only blanks.  Enter a valid SQL statement.")
				return null;
			}

			return sql;
		},

		/*
		 *
		*/
		runSQL: function (e) {
			// get out if the editor is not selected
			//if (!admin.Statics.isActiveEditor(this)) return;

			var dt = {0:"WLONGVARCHAR",1:"WVARCHAR",2:"WCHAR",3:"BIT",4:"BYTEINT",5:"BIGINT",6:"LONGVARBINARY",7:"VARBINARY",8:"BINARY",9:"LONGVARCHAR",
				11:"CHAR",12:"NUMERIC",13:"DECIMAL",14:"INTEGER",15:"SMALLINT",16:"FLOAT",17:"REAL",18:"DOUBLE",19:"DATE",20:"TIME",21:"TIMESTAMP",22:"VARCHAR"};

			var sql = this.getCurrentSQL();
			if(sql === null){
				return;
			}

			var sqlDO = new admin.sqldo.SQLStatement();
			sqlDO.setSql(sql);

			sqlDO.setHostDB(admin.Statics.getDDSelectedValue(this.HostDBField));

			// cleanup
			this.overview_label1.setLabel("Column Count:");
			this.overview_label2.setLabel("Row Count:");

			this.resultsGB.setLegend("SQL Results");
			this.metadataGB.setLegend("SQL Metadata");

			this.metaTable.getTableModel().setData([]);
			this.resultsTable.getTableModel().setData([]);

			admin.Api.ExecuteGenericSQL(sqlDO,
			function (response) {
				// Walk the results for metadata and column rows

				// Find the Metadata node:
				var metaNode = null;
				for (var i = 0, l = response.childNodes.length; i < l; i++) {
					if (response.childNodes[i].nodeName === "MetaData") {
						metaNode = response.childNodes[i];
						break;
					}
				}

				var colNames = [];
				if (metaNode !== null) {
					if (qx.lang.String.startsWith(sql.toUpperCase(), "INSERT") ||
						qx.lang.String.startsWith(sql.toUpperCase(), "UPDATE") ||
						qx.lang.String.startsWith(sql.toUpperCase(), "DELETE")) {
						admin.Statics.doAlertGreen("Rows affected by this SQL statement: " + metaNode.getAttribute("rows"))
						return;
					}

					this.columnCount = Number(metaNode.getAttribute("columns"));
					var metaRowData = [];
					for (var i = 0, l = metaNode.childNodes.length; i < l; i++) {
						var node = metaNode.childNodes[i];
						if (node.nodeName === "Column") {
							metaRowData.push([
								node.getAttribute("position"),
								node.getAttribute("name"),
								dt[Number(node.getAttribute("dbtype"))+10],
								node.getAttribute("size"),
								node.getAttribute("scale"),
								node.getAttribute("nullable")
							]);
							colNames.push(node.getAttribute("name"));
						}
					}
					this.metaTable.getTableModel().setData(metaRowData);
					this.overview_label1.setLabel("Column Count: " + this.columnCount);
					this.metadataGB.setLegend("SQL Metadata for '" + sql + "'");
				}

				// Reset the results table columns:
				var tableParent = this.resultsTable.getLayoutParent();
				tableParent.remove(this.resultsTable);
				admin.Statics.cleanupStandardTable(this.resultsTable);
				this.resultsTable = null;

				this.resultsTable = admin.Statics.createStandardTable(colNames, resultsRowData);
				tableParent.add(this.resultsTable, { flex: 1 });
				// Ensure that all columns have a minimum width:
				var sizing = this.resultsTable.getTableColumnModel().getBehavior();
				for (var i = 0, l = colNames.length; i < l; i++) {
					var hash = {};
					hash.width = "1*";
					hash.minWidth = 50;
					sizing.set(i, hash);

					// make the column editable so copy function works
					this.resultsTable.getTableModel().setColumnEditable(i, true);
				}
				this.resultsTable.getDataRowRenderer()._renderFont(new qx.bom.Font(12, ["monospace"]));

				// Find all of the row data:
				var resultsRowData = [];
				for (var i = 0, l = response.childNodes.length; i < l; i++) {
					var node = response.childNodes[i];
					if (node.nodeName === "Row") {
						var colData = [];
						for (var j = 0, k = node.childNodes.length; j < k; j++) {
							var node2 = node.childNodes[j];
							if (node2.nodeName === "Column") {
								colData.push(
									admin.Statics.xmlGetBase64(
										admin.Statics.xmlFindChild(node2, "value")
									)
								);
							}
						}
						resultsRowData.push(colData);
					}
				}
				this.resultsTable.getTableModel().setData(resultsRowData);
				this.overview_label2.setLabel("Row Count: " + resultsRowData.length);
				this.resultsGB.setLegend("SQL Results for '" + sql + "'");

				// select the results tab
				var our_tab = admin.Statics.findQXParent(this.resultsTable, qx.ui.tabview.Page);
				our_tab.getButton().execute();

			}, this);


		},

		genCCode : function() {
			var sql = this.getCurrentSQL();
			if(sql === null){
				return;
			}

			admin.Api.LoadPlainDoc( qx.util.ResourceManager.getInstance().toUri("admin/templates/CTemplate.c"),
			function(response) {

				var templateParms = {sqlText: sql};

				var winTitle = "C Code for Executing SQL";
				var winLabel = "C Code to execute the selected SQL Statements<br/>Copy this code and paste it into your favorite development environment.";
				var winIcon = "admin/icon/64x64/shadow/code_c.png";
				var dialog = new admin.dialog.CodeDisplayDialog(winTitle, winIcon, winLabel);
				dialog.open();
				dialog.setText( qx.bom.Template.render( response, templateParms ) );
			}, this);
		},

		genCSharpCode : function() {
			var sql = this.getCurrentSQL();
			if(sql === null){
				return;
			}

			admin.Api.LoadPlainDoc( qx.util.ResourceManager.getInstance().toUri("admin/templates/CSharpTemplate.cs"),
			function(response) {

				var templateParms = {sqlText: sql};

				var winTitle = "C# Code for Executing SQL";
				var winLabel = "C# Code to execute the selected SQL Statements<br/>Copy this code and paste it into your favorite development environment.";
				var winIcon = "admin/icon/64x64/shadow/code_csharp.png";
				var dialog = new admin.dialog.CodeDisplayDialog(winTitle, winIcon, winLabel);
				dialog.open();
				dialog.setText( qx.bom.Template.render( response, templateParms ) );
			}, this);
		},

		genJavaCode : function() {
			var sql = this.getCurrentSQL();
			if(sql === null){
				return;
			}

			admin.Api.LoadPlainDoc( qx.util.ResourceManager.getInstance().toUri("admin/templates/JavaTemplate.java"),
			function(response) {

				var templateParms = {sqlText: sql};

				var winTitle = "Java Code for Executing SQL";
				var winLabel = "Java Code to execute the selected SQL Statements<br/>Copy this code and paste it into your favorite development environment.";
				var winIcon = "admin/icon/64x64/shadow/code_java.png";
				var dialog = new admin.dialog.CodeDisplayDialog(winTitle, winIcon, winLabel);
				dialog.open();
				dialog.setText( qx.bom.Template.render( response, templateParms ) );
			}, this);
		},

		/** This allows our subclasses to do something in the scenario where the
		* edit view is opened up for a brand new object.
		*/
		initializeNewObject: function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = true;

			this.dataObject = new admin.sqldo.SQLWork;

			this.dataObject.setHostDB("lds");

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

			// Editor needs to be saved
			this.fieldModified();
		},

		/** This method is called by the "get" API function and should be prepared to read
		* our data object from the XML sent back to us by the server.
		*/
		getObjectDetails: function (response) {
			var objectList = admin.sqldo.SQLWork.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.isNewObject = false;

			this.loadDataIntoForm();

			// Once data is loaded, reset our dirty flag
			this.resetDirty();
		},

		/** This handles loading our GUI form fields based on the information contained
		* in our data object.
		*/
		loadDataIntoForm: function () {
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			admin.Statics.loadAllFields(this, this.dataObject);


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			//this.overview_label1.setLabel("Overview Label1: " + this.dataObject.getTName());

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */
			if(this.SqlField){
				this.SqlField.getSession().setValue( this.dataObject.getSql() );
			}

		},

		/** This handles pulling data from GUI form fields and loading their values
		* back into our data object.
		*/
		pullDataFromForm: function () {
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* pulling all fields that are registered in this object   */
			/* directly from our form and saving them to the dataObject*/
			/* ******************************************************* */
			admin.Statics.pullAllFields(this, this.dataObject);

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */
			this.dataObject.setSql( this.SqlField.getValue() );
		},

		/** This handles verifying all of our form fields prior to saving the
		* record back to the server.
		*/
		verifyFields: function () {
			if (this.FileNameField.getValue != this.dataObject.getFileName()) {
				this.isNewObject = true;
			}

			// Use the built-in verification to do as much work for us as possible:
			if (admin.Statics.verifyAllFields(this) === -1) return -1;

			// Then do any special verification required here:

			// If everything is ok, return 0
			return 0;
		},

		/** This handles the calls required to save our dataObject back to the
		* server.
		*/
		doSaveToServer: function () {
			if (this.verifyFields() === -1) {
				return; // Don't save an invalid object
			}
			this.pullDataFromForm();
			if(this.isNewObject === true){
				admin.Api.SaveSQLWork( this.dataObject,
				function(response){
					// pick up any new information here.
					this.isNewObject = false;

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getFileName() );

					this.loadDataIntoForm(); // Gets all of our overview labels

					this.resetDirty();

					// Remember to add the new guy to the tree:
					var obj = new admin.sqldo.SQLWork;
					obj.setFileName( this.dataObject.getFileName() );
					qx.core.Init.getApplication().addNewTreeItem( "SQL Workbench Sessions",
						obj.getFileName(), obj,
						"admin/icon/16x16/plain/scroll_run.png",
						admin.admin.SqlWorkTreeNodes.editObject);

				}, this);
			} else {
				admin.Api.SaveSQLWork( this.dataObject,
				function(response){
					// pick up any new information here.

					this.loadDataIntoForm(); // Gets all of our overview labels
					this.resetDirty();
				}, this);
			}

		}


	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		this._disposeObjects(
			"tabview",
			"dataObject",
			"m_object_id"
		);
		admin.Statics.destroyExtraObjects(this);
		this.SqlField = null;
	}

});
