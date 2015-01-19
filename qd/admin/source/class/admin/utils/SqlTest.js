/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/scroll2_add.png)
#asset(admin/icon/64x64/shadow/scroll.png)
#asset(admin/icon/16x16/plain/barcode.png)
#asset(admin/icon/16x16/plain/scroll2_add.png)
#asset(admin/icon/16x16/plain/delete2.png)
#asset(admin/icon/16x16/plain/navigate_up2.png)
#asset(admin/icon/16x16/plain/navigate_down2.png)
#asset(admin/icon/16x16/plain/table2_run.png)
#asset(admin/icon/16x16/plain/gears_run.png)
#asset(admin/icon/16x16/plain/check.png)
#asset(admin/icon/16x16/plain/checks.png)
#asset(admin/icon/16x16/plain/scroll.png)
************************************************************************ */
qx.Class.define("admin.utils.SqlTest", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "SqlTest.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "SqlTest.NextPage.xml", doc:null});
		this.dynamicLayouts.push({name: "SqlTest.SqlStmtPage.xml", doc:null});
		this.dynamicLayouts.push({name: "SqlTest.SqlMetaPage.xml", doc:null});
		this.dynamicLayouts.push({name: "SqlTest.SqlSavedResultsPage.xml", doc:null});

		this.currentStmt = null;
		this.base(arguments, object_id);

	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = admin.Api.GetSQLTest;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb); // Call the parent class first

			//var part = new qx.ui.toolbar.Part;

			//admin.Statics.addToToolbar( part, "admin/icon/16x16/plain/scroll2_add.png",
			//	"Adds a new SQL Statement", this.addSqlStatement, this, this);

			//tb.add(part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "SQL Statements", false));
			// Load more tabs here

			this.TestGroupNameField.focus();

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "SQL Test",
				"admin/icon/64x64/shadow/scroll.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getFileName() );

			this.addStatusHeading("General");
			//this.overview_label1 = this.addStatusItem("Overview Label1:", "admin/icon/16x16/plain/barcode.png");


			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("SqlTest.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			// These are icons referenced in the layout.  Do not delete these comments:
			// "admin/icon/16x16/plain/scroll2_add.png"
			// "admin/icon/16x16/plain/delete2.png"
			// "admin/icon/16x16/plain/navigate_up2.png"
			// "admin/icon/16x16/plain/navigate_down2.png"
			// "admin/icon/16x16/plain/table2_run.png"
			// "admin/icon/16x16/plain/gears_run.png"
			// "admin/icon/16x16/plain/check.png"
			// "admin/icon/16x16/plain/checks.png"

			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("SqlTest.NextPage.xml"),
				tab_page );

			this.sqlTabView = new qx.ui.tabview.TabView;
			this.rightBox.add( this.sqlTabView, {flex: 10 });

			this.createSqlStmtTab( admin.Statics.addEditorSubTab( this.sqlTabView, "Statement", true));
			this.createSqlMetaTab( admin.Statics.addEditorSubTab( this.sqlTabView, "Metadata", false));
			this.createSqlResultsTab( admin.Statics.addEditorSubTab( this.sqlTabView, "Saved Results", false));

			this.stmtTable.getSelectionModel().addListener( "changeSelection", this.stmtChange, this );

			this.stmtAddNew.addListener("execute", this.addSqlStatement, this);
			this.stmtAddNew.setToolTipText("Add New SQL Statement");

			this.stmtDelete.addListener("execute", this.deleteSqlStatement, this);
			this.stmtDelete.setToolTipText("Delete Selected SQL Statements");

			this.stmtMoveUp.addListener("execute", this.moveStatementsUp, this);
			this.stmtMoveUp.setToolTipText("Move Selected SQL Statements Up");

			this.stmtMoveDown.addListener("execute", this.moveStatementsDown, this);
			this.stmtMoveDown.setToolTipText("Move Selected SQL Statements Down");

			this.stmtLoadOne.addListener("execute", this.loadSqlStatement, this);
			this.stmtLoadOne.setToolTipText("Execute/Load Metadata and Results for Selected Statements");

			this.stmtLoadAll.addListener("execute", this.loadAllStatements, this);
			this.stmtLoadAll.setToolTipText("Execute/Load Metadata and Results for All Statements");

			this.stmtCheckOne.addListener("execute", this.checkSqlStatement, this);
			this.stmtCheckOne.setToolTipText("Execute Selected Statements and verify Metadata and Results");

			this.stmtCheckAll.addListener("execute", this.checkAllStatements, this);
			this.stmtCheckAll.setToolTipText("Execute All Statements and verify Metadata and Results");

		},

		createSqlStmtTab: function(tab_page) {
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("SqlTest.SqlStmtPage.xml"),
				tab_page );

			this.StatementNameField.addListener( "input", this.stmtNameChange, this );
			this.newConnectionField.addListener( "changeValue", this.stmtConnChange, this );
		},

		createSqlMetaTab: function(tab_page) {
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("SqlTest.SqlMetaPage.xml"),
				tab_page );
		},

		createSqlResultsTab: function(tab_page) {
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("SqlTest.SqlSavedResultsPage.xml"),
				tab_page );
		},

		stmtNameChange: function(e) {
			var row = this.getFirstSelected();
			this.stmtTable.getTableModel().setValue( 0, row, this.StatementNameField.getValue() );
		},

		stmtConnChange: function(e) {
			var row = this.getFirstSelected();
			this.stmtTable.getTableModel().setValue( 1, row,
				this.newConnectionField.getValue() ? "true" : "false" );
		},

		stmtChange: function(e) {
			if(this.currentStmt !== null){
				// Save whatever is in the form back to the current statement before
				// switching to the next table row.
				admin.Statics.pullAllFields(this, this.currentStmt);
			}

			// Find the new statement based on the table selection:
			//var row = this.stmtTable.getFocusedRow();
			var row = this.getFirstSelected();
			if(row !== null){
				this.currentStmt = this.dataObject.SQLStatements[row];
				var resetDirtyFlag = !this.isDirty;
				admin.Statics.loadAllFields(this, this.currentStmt);

				// Load the metadata table:
				this.loadMetaData();

				// Load the results table:
				this.loadResults();

				if(resetDirtyFlag){
					// Our dirty flag was not set before we did the load fields.
					// turn it back off again.
					this.resetDirty();
				}
			}

		},

		loadMetaData: function( ){

			var metaData = [];
			for(var i = 0, l = this.currentStmt.MetaData.length; i < l; i++){
				var col = this.currentStmt.MetaData[ i ];
				metaData.push([
					col.getIdx(),
					col.getColName(),
					col.getVerifyData() === 1 ? "true" : "false",
					col.getTypeName()
				]);
			}
			this.stmtMetaTable.getTableModel().setData( metaData );

			var metaDataCheck = [];
			for(var i = 0, l = this.currentStmt.MetaDataCheck.length; i < l; i++){
				var col = this.currentStmt.MetaDataCheck[ i ];
				metaDataCheck.push([
					col.getIdx(),
					col.getColName(),
					col.getVerifyData() === 1 ? "true" : "false",
					col.getTypeName()
				]);
			}
			this.stmtMetaCheckTable.getTableModel().setData( metaDataCheck );
		},

		loadResults: function() {
			var colNames = [];
			for(var i = 0, l = this.currentStmt.MetaData.length; i < l; i++){
				var col = this.currentStmt.MetaData[ i ];
				colNames.push( col.getColName() );
			}

			// Load the results table:
			var tableParent = this.stmtResultsTable.getLayoutParent();
			tableParent.remove(this.stmtResultsTable);
			admin.Statics.cleanupStandardTable( this.stmtResultsTable );
			this.stmtResultsTable = null;

			this.stmtResultsTable = admin.Statics.createStandardTable( colNames, null );
			tableParent.add( this.stmtResultsTable, {flex: 1} );
			// Ensure that all columns have a minimum width:
			var sizing = this.stmtResultsTable.getTableColumnModel().getBehavior();
			for(var i = 0, l = colNames.length; i < l; i++){
				var hash = {};
				hash.width = "1*";
				hash.minWidth = 50;
				sizing.set(i, hash);
			}

			var resData = [];
			for(var i = 0, l = this.currentStmt.Results.length; i < l; i++){
				var row = this.currentStmt.Results[i];
				var colData = [];
				for(var j = 0, k = row.Cols.length; j < k; j++){
					var col = row.Cols[ j ];
					colData.push( col.getDataValue() );
				}
				resData.push( colData );
			}
			this.stmtResultsTable.getTableModel().setData( resData );

			tableParent = this.stmtResultsCheckTable.getLayoutParent();
			tableParent.remove(this.stmtResultsCheckTable);
			admin.Statics.cleanupStandardTable( this.stmtResultsCheckTable );
			this.stmtResultsCheckTable = null;

			this.stmtResultsCheckTable = admin.Statics.createStandardTable( colNames, null );
			tableParent.add( this.stmtResultsCheckTable, {flex: 1} );
			// Ensure that all columns have a minimum width:
			var sizing = this.stmtResultsCheckTable.getTableColumnModel().getBehavior();
			for(var i = 0, l = colNames.length; i < l; i++){
				var hash = {};
				hash.width = "1*";
				hash.minWidth = 50;
				sizing.set(i, hash);
			}

			var resData = [];
			for(var i = 0, l = this.currentStmt.ResultsCheck.length; i < l; i++){
				var row = this.currentStmt.ResultsCheck[i];
				var colData = [];
				for(var j = 0, k = row.Cols.length; j < k; j++){
					var col = row.Cols[ j ];
					colData.push( col.getDataValue() );
				}
				resData.push( colData );
			}
			this.stmtResultsCheckTable.getTableModel().setData( resData );
		},

		getFirstSelected: function(){
			var selectedRowData = this.getSelectedIndexes();
			if(selectedRowData.length === 0){
				return null; // nothing selected.
			}
			return selectedRowData[ 0 ];
		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = true;

			this.dataObject = new admin.sqldo.SQLTests;

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

			this.fieldModified();
		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.SQLTests.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}

			this.dataObject = objectList[0];

			this.isNewObject = false;

			this.loadDataIntoForm();

			this.resetDirty();
		},

		/** This handles loading our GUI form fields based on the information contained
		  * in our data object.
		  */
		loadDataIntoForm : function ()
		{
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			admin.Statics.loadAllFields(this, this.dataObject);

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */
			this.loadStatementTable();
		},

		loadStatementTable : function () {
			var rowData = [];

			for(var i = 0, l = this.dataObject.SQLStatements.length; i < l; i++){
				var stmt = this.dataObject.SQLStatements[i];
				rowData.push([
					stmt.getStatementName(),
					stmt.getNewConnection() === 1 ? "true" : "false",
					stmt.getStatus() === 0 ? "Success" : "Failure"
				]);
			}

			this.stmtTable.getTableModel().setData( rowData );
		},

		/** This handles pulling data from GUI form fields and loading their values
		  * back into our data object.
		  */
		pullDataFromForm : function ()
		{
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

		},

		addSqlStatement : function() {
			if(this.currentStmt !== null){
				// Save whatever is in the form back to the current statement before
				// switching to the next table row.
				admin.Statics.pullAllFields(this, this.currentStmt);
			}

			var stmt = new admin.sqldo.SQLStmt;
			stmt.setStatementName( "New Statement" );
			stmt.setDescription( "Description goes here" );
			stmt.setStmt( "Select * from owner.table" );

			this.dataObject.SQLStatements.push( stmt );

			this.pullDataFromForm();
			this.loadDataIntoForm();

			var lastRow = this.dataObject.SQLStatements.length - 1;
		},

		getSelectedIndexes: function() {
			var smodel = this.stmtTable.getSelectionModel();
			if(smodel.isSelectionEmpty()){
				return []; // nothing selected.  bail out.
			}

			var tmodel = this.stmtTable.getTableModel();
			var selectedRowData = [];
			smodel.iterateSelection(function(index){
				selectedRowData.push( index );
			} );

			return selectedRowData;
		},

		deleteSqlStatement: function() {
			var selectedRowData = this.getSelectedIndexes();
			if(selectedRowData.length === 0){
				return; // nothing selected.
			}

			// Run the indexes in reverse order, and remove them from the table
			for(var i = selectedRowData.length - 1; i >= 0; i--){
				var index = selectedRowData[ i ];
				this.dataObject.SQLStatements.splice( index, 1 );
			}

			this.pullDataFromForm();
			this.loadDataIntoForm();

			this.currentStmt = null;
			this.stmtTable.getSelectionModel().resetSelection();
			this.clearStatement();
		},

		moveStatementsUp: function() {
		},

		moveStatementsDown: function() {
		},

		clearStatement: function() {
			var stmt = new admin.sqldo.SQLStmt;
			admin.Statics.loadAllFields(this, stmt);
		},

		/** This handles verifying all of our form fields prior to saving the
		  * record back to the server.
		  */
		verifyFields : function()
		{
			// Use the built-in verification to do as much work for us as possible:
			if( admin.Statics.verifyAllFields(this) === -1) return -1;

			// Then do any special verification required here:

			// If everything is ok, return 0
			return 0;
		},

		/** This handles the calls required to save our dataObject back to the
		  * server.
		  */
		doSaveToServer : function ( )
		{
			if(this.verifyFields() === -1){
				return; // Don't save an invalid object
			}

			this.pullDataFromForm();
			if(this.currentStmt !== null){
				// Save whatever is in the form back to the current statement before
				// switching to the next table row.
				admin.Statics.pullAllFields(this, this.currentStmt);
			}

			if(this.isNewObject === true){
				admin.Api.SaveSQLTest( this.dataObject,
				function(response){
					// pick up any new information here.
					this.isNewObject = false;

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getTestGroupName() );

					this.loadDataIntoForm(); // Gets all of our overview labels

					this.resetDirty();

					// Remember to add the new guy to the tree:
					var treeObj = new admin.sqldo.IAFile;
					treeObj.setParentFolder("./test/");
					treeObj.setFileName( this.dataObject.getTestGroupName() );

					qx.core.Init.getApplication().addNewTreeItem( "SQL Tests",
						this.dataObject.getTestGroupName(), treeObj,
						"admin/icon/16x16/plain/scroll.png" );

				}, this);
			} else {
				admin.Api.SaveSQLTest( this.dataObject,
				function(response){
					// pick up any new information here.

					this.loadDataIntoForm(); // Gets all of our overview labels

					this.resetDirty();
				}, this);
			}

		},

		loadSqlStatement: function() {
			var selectedRowData = this.getSelectedIndexes();
			if(selectedRowData.length === 0){
				return; // nothing selected.
			}
			// First turn everything off:
			for(var i = 0, l = this.dataObject.SQLStatements.length; i < l; i++){
				var stmt = this.dataObject.SQLStatements[i];
				stmt.setIsSelected( 0 );
			}
			// Then turn on the ones selected:
			for(var i = 0, l = selectedRowData.length; i < l; i++){
				var stmt = this.dataObject.SQLStatements[ selectedRowData[ i ] ];
				stmt.setIsSelected( 1 );
			}

			// Now send our sql test group to the server for processing:
			admin.Api.LoadSQLTestMeta( this.dataObject,
			function(response) {
				this.getObjectDetails(response);
			}, this);

		},

		loadAllStatements: function() {
			// First turn everything on:
			for(var i = 0, l = this.dataObject.SQLStatements.length; i < l; i++){
				var stmt = this.dataObject.SQLStatements[i];
				stmt.setIsSelected( 1 );
			}
			// Now send our sql test group to the server for processing:
			admin.Api.LoadSQLTestMeta( this.dataObject,
			function(response) {
				this.getObjectDetails(response);
			}, this);
		},

		checkSqlStatement: function() {
			var selectedRowData = this.getSelectedIndexes();
			if(selectedRowData.length === 0){
				return; // nothing selected.
			}
			// First turn everything off:
			for(var i = 0, l = this.dataObject.SQLStatements.length; i < l; i++){
				var stmt = this.dataObject.SQLStatements[i];
				stmt.setIsSelected( 0 );
			}
			// Then turn on the ones selected:
			for(var i = 0, l = selectedRowData.length; i < l; i++){
				var stmt = this.dataObject.SQLStatements[ selectedRowData[ i ] ];
				stmt.setIsSelected( 1 );
			}

			// Now send our sql test group to the server for processing:
			admin.Api.CheckSQLTest( this.dataObject,
			function(response) {
				this.getObjectDetails(response);
			}, this);


		},

		checkAllStatements: function() {
			// First turn everything on:
			for(var i = 0, l = this.dataObject.SQLStatements.length; i < l; i++){
				var stmt = this.dataObject.SQLStatements[i];
				stmt.setIsSelected( 1 );
			}
			// Now send our sql test group to the server for processing:
			admin.Api.CheckSQLTest( this.dataObject,
			function(response) {
				this.getObjectDetails(response);
			}, this);
		}

	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct : function() {
		this._disposeObjects(
			"tabview",
			"dataObject",
			"m_object_id"
		);
		admin.Statics.destroyExtraObjects( this );
	}

});
