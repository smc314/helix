/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/**
 * This class is the base class for all of our Hub Unit/Gui testing.  We
 * create a full application of the hub inside the testrunner framework so that
 * all of our trees/dialogs/editors/etc. will function as normal.  When the
 * tests are all done, we tear down the hub application and return control
 * to the testrunner application.
 *
 * We also have a series of methods that make it easier to find items in the
 * tree(s) and execute various standard activities within the application.
 *
 */
qx.Class.define("welcome.test.HelixTest",
{
	extend : qx.dev.unit.TestCase,
	type : "abstract",

	construct : function() {
		this.base(arguments);

	},

	properties: {

		ServerHost : {init : "viazos19", check : "String" },
		ServerPort : {init : "6311", check : "String" },
		ServerUser : {init : "SMC", check : "String" },
		ServerPass : {init : "SMC", check : "String" }

	},

	members :
	{
		_lastTest : false,

		/**
		  * This function is executed prior to each of the test* methods defined
		  * below.
		  */
		setUp : function() {
			// construct our welcome Application so we can test it
			this.getRoot();
		},

		/**
		  * This function is executed after each of the test* methods defined
		  * below.
		  */
		tearDown : function() {
			if (this._lastTest === true) {

				this.getRoot().removeAll();
				var cls = welcome.test.HubTest;
				if (cls._app) {
					this._disposeObjects( cls._app );
					cls._app = null;
					qx.core.Init.getApplication = cls._oldGetApp;
				}

				// Support re-running without re-loading
				this._lastTest = false;
			}
		},

		getRoot : function() {
			var cls = welcome.test.HubTest;
			if(cls._app){
				return cls._app.getRoot();
			}
			cls._app = new welcome.Application( document );
			cls._oldApplication = qx.core.Init.getApplication();
			cls._oldGetApp = qx.core.Init.getApplication;

			qx.core.Init.getApplication = function() {
				return cls._app;
			}
			cls._app.main();

			return cls._app.getRoot();
		},

		/*
		---------------------------------------------------------------------------
		  TESTS
		---------------------------------------------------------------------------
		*/

		/**
		  * Set our server connection to viazos19, 6311, SMC by default.  Override
		  * this test method if you want to use a different server connection.
		  */
		test0000_setServer: function() {
			qx.core.Init.getApplication().addListener( "appInitialized", function() {
				welcome.test.TestStatics.SetServerConnection(this.getServerHost(), this.getServerPort(),
					this.getServerUser(), this.getServerPass());

				// sleep for 3 seconds to give the app a little more time to initialize:
				qx.event.Timer.once( function() { this.resume(); }, this, 3000 );
			}, this );

			this.wait( 10000 );
		},

		/**
		 * Set the properties for this test case
		 */
		test0001_setProps: function () {
			this.populateProperties();
		},


		/**
		  * The last test in this class will simply set the _lastTest boolean
		  * to true.  This will trigger our tearDown function to get rid of our
		  * testing application.
		  */
		test9999_LastTest: function() {
			this._lastTest = true;
		},

		/** Use this to do a "Refresh" on the browse tree and the catalog tree.
		  */
		doTreeRefresh : function() {
			qx.core.Init.getApplication().fillTree();
		},

		/** Use this in order to find/open a given node in the browse tree.  Use slashes
		  * to separate the levels: i.e. "Data Sources/VSAM_LDS/VIASQL".
		  */
		getBrowseTreeNode : function(treePath, callBack, rootNode){
			this.treePath = treePath.split("/");
			this.treePathCallback = callBack;
			if(rootNode){
				var browseRoot = rootNode;
			} else {
				var browseRoot = qx.core.Init.getApplication().browseTreeRoot;
			}
			this.assertNotNull( browseRoot, "Application browse tree root is null.");
			this.assertNotUndefined( browseRoot, "Application browse tree root is null.");

			this.expectantParent = browseRoot;
			this.treePathIdx = 0;
			this.childFound();
		},

		/** Use this in order to find/open a given node in the normal tree.  Use slashes
		  * to separate the levels: i.e. "Tables/HWRD/AUTHORS".
		  */
		getFileTreeNode : function(treePath, callBack, rootNode){
			this.treePath = treePath.split("/");
			this.treePathCallback = callBack;
			if(rootNode){
				var treeRoot = rootNode;
			} else {
				var treeRoot = qx.core.Init.getApplication().treeRoot;
			}
			this.assertNotNull( treeRoot, "Application tree root is null.");
			this.assertNotUndefined( treeRoot, "Application tree root is null.");

			this.expectantParent = treeRoot;
			this.treePathIdx = 0;
			this.childFound();
		},

		/** This method is used by the getBrowseTreeNode, and getFileTreeNode.  Do not use
		  * this method directly.
		  */
		childFound : function() {
			// Find the next level child:
			var children = this.expectantParent.getChildren();
			var childName = this.treePath[ this.treePathIdx ];
			var childNode = null;

			for(var j = 0, m = children.length; j < m; j++){
				if(children[ j ].getLabel().indexOf( childName ) === 0){ // use this instead of startsWith
					childNode = children[ j ];
					break;
				}
			}

			if(childNode === null){
				throw "Unknown child node: " + childName + " in browse tree.";
			}

			if(this.treePathIdx === (this.treePath.length - 1) ){
				// we're done.  call the callback:
				this.treePathCallback.call( this, childNode );
				return;
			}

			// otherwise, keep looking for the next level down:
			if(!childNode.isOpen()){
				childNode.toggleOpen();
			}

			this.treePathIdx ++;

			// wait for the childNode to open up and fill up its children:
			this.expectantParent = childNode;
			this.waitForChildren();
		},

		/** This method is used by the getBrowseTreeNode, and getFileTreeNode.  Do not use
		  * this method directly.
		  */
		waitForChildren : function() {
			if(this.expectantParent.getChildren().length !== 0){
				this.childFound(); // children found
				return;
			}
			// otherwise wait for 1/2 second and check again:
			qx.event.Timer.once( this.waitForChildren, this, 100 );
		},

		/** This fires the double-click event on the given widget.
		  */
		doubleClick : function( widg ) {
			widg.fireEvent( "dblclick", qx.event.type.Mouse, [{}, widg, widg, false, true] );
		},

		/** This method will find a given tab name, or return null if
		  * it doesn't exist.
		  */
		findTab : function(tabName) {
			var app = qx.core.Init.getApplication();
			var pages = app.tabView.getChildren();
			for(var i = 0, l = pages.length; i < l; i++){
				if(pages[i].getLabel() === tabName ||
					pages[i].getLabel() === "*" + tabName
				){
					// Found it.  Ensure that it is fully loaded and ready:
					return pages[i];
				}
			}
			// Didn't find anything
			return null;
		},

		/** This method will wait for an editor with the given tab name.
		  */
		waitForEditor : function(editorName, callBack) {
			// Check to see if the editor is present:
			var page = this.findTab( editorName );
			if(page !== null){
				// Found it.  Ensure that it is fully loaded and ready:
				var editor = page.getChildren()[0];
				if(editor.isEditorLoaded()){
					callBack.call( this, editor );
				} else {
					editor.addListener("editorLoaded", function() {
						callBack.call( this, editor );
					}, this );
				}
				return;
			}

			// If not, then wait for 1/2 second and try again:
			qx.event.Timer.once( function() {
				this.waitForEditor( editorName, callBack );
			}, this, 100 );
		},

		/**
		  * Finds and presses the named button on the editor toolbar.  We do this directly
		  * through the editor toolbar and save button.  This ensures that all events and actions
		  * are wired up together properly.
		  */
		pressEditorToolbar : function( editor, buttonName ) {
			var child1 = editor.getChildren()[ 0 ];
			if(child1 instanceof qx.ui.toolbar.ToolBar){
				var part1 = child1.getChildren()[ 0 ];
				if(part1 instanceof qx.ui.toolbar.Part){
					var children = part1.getChildren();
					for(var i = 0, l = children.length; i < l; i++){
						if(children[i] instanceof qx.ui.toolbar.Separator) { continue; }
						if(children[i].getLabel().indexOf( buttonName ) === 0 ){
							// found the named button.
							children[i].execute();
							return;
						}
					}
					// If we get to here, there was no button with the given label on the toolbar.
					throw "No '" + buttonName + "' button found on editor toolbar.";
				} else {
					throw "First toolbar child is not a toolbar.Part";
				}
			} else {
				throw "First child is not a toolbar";
			}
		},

		/**
		  * Finds and presses the "Save" Button on the toolbar.  We do this directly through
		  * the editor toolbar and save button.  This ensures that all events and actions
		  * are wired up together properly.
		  */
		pressSave : function () {
			this.pressEditorToolbar( this._editor, "Save" );
		},

		/** This function closes the named tab.  This does its work directly through the
		  * tab view and presses the close button on the tab directly.  This way all associated
		  * events and actions should fire correctly
		  */
		closeTab : function(tabName) {
			var page = this.findTab( tabName );
			if(page === null){
				throw "Tab named " + tabName + " is not open.";
			}
			page.getButton().fireDataEvent("close", page.getButton() );
		},

		/** This method will wait for a named tab to close
		  */
		waitForTabToClose : function(tabName, callBack) {
			// Check to see if the editor is present:
			var page = this.findTab( tabName );
			if(page === null){
				// It's closed.  Call the callback
				callBack.call( this );
				return;
			} else {
				// If not, then wait for 1/2 second and try again:
				qx.event.Timer.once( function() {
					this.waitForTabToClose( tabName, callBack );
				}, this, 100 );
			}
		},

		/**
		  * This function uses the data defined in _propData to drive the population
		  * of our properties.
		  */
		populateProperties : function () {
			if(this._propData === null || this._propData === undefined){
				return;
			}

			var single = welcome.Singleton.getInstance();
			var props = single.getSystemProperties();

			for(var i = 0, l = this._propData.length; i < l; i ++ ){
				var field = this._propData[i];
				props[field.name] = field.value;
			}
		},

		/**
		  * This function uses the data defined in _testData to drive the population
		  * of all of our form fields.  We'll switch tabs as required to get each one
		  * populated.
		  */
		populateFormFields : function () {
			if(this._testData === null || this._testData === undefined){
				throw "No _testData defined to populate form fields.";
			}
			for(var i = 0, l = this._testData.length; i < l; i ++ ){
				var field = this._testData[i];
				this.populateOneField( field );
			}
		},

		/** This handles populating one field in the form based on the given input field
		  * hash information.  The field has should look like this:
		  * {name: "FieldWidgetName", value: "ValueForField" }
		  */
		populateOneField: function( field ) {
			var widget = this._editor[ field.name ];
			if(widget === null || widget === undefined){
				throw String("_testData field " + field.name + " is not found in the editor.");
			}
			if(widget instanceof qx.ui.form.TextField ||
				widget instanceof qx.ui.form.PasswordField ||
				widget instanceof qx.ui.form.TextArea ||
				widget instanceof qx.ui.form.ComboBox
			){
				widget.setValue( field.value );
			} else if(widget instanceof qx.ui.form.SelectBox ){
				welcome.Statics.setDropDownByLabel( widget, field.value );
			} else if(widget instanceof qx.ui.form.CheckBox ||
				widget instanceof qx.ui.form.RadioButton ||
				widget instanceof qx.ui.groupbox.CheckGroupBox ||
				widget instanceof qx.ui.groupbox.RadioGroupBox
			){
				widget.setValue( field.value === "true" ? true : false );
			} else if (widget instanceof qx.ui.table.Table) {
				//widget.getTableModel().setData(field.value);
			} else {
				throw String("Unknown field type for field: " + field.name );
			}
		},

		/**
		  * This function uses the data defined in _testData to check any fields that
		  * have default data in them.  If no default value is defined for a field, that
		  * field is skipped.
		  */
		checkDefaultData : function () {
			if(this._testData === null || this._testData === undefined){
				throw "No _testData defined.";
			}
			for(var i = 0, l = this._testData.length; i < l; i ++ ){
				var field = this._testData[i];
				if(field.defaultValue === null || field.defaultValue === undefined){
					continue; // skip this field.
				}
				var widget = this._editor[ field.name ];
				if(widget === null || widget === undefined){
					throw String("_testData field " + field.name + " is not found in the editor.");
				}
				this.checkOneField( widget, field.defaultValue, field.name);
			}
		},

		/**
		  * This function uses the data defined in _testData to check all standard field data.
		  */
		checkData : function (phase) {
			if(this._testData === null || this._testData === undefined){
				throw "No _testData defined.";
			}
			for(var i = 0, l = this._testData.length; i < l; i ++ ){
				var field = this._testData[i];
				var widget = this._editor[ field.name ];
				if(widget === null || widget === undefined){
					throw String("_testData field " + field.name + " is not found in the editor.");
				}
				if(phase === "AfterSave"){
					if(field.valueAfterSave !== null && field.valueAfterSave !== undefined){
						this.checkOneField( widget, field.valueAfterSave, field.name);
					} else {
						this.checkOneField( widget, field.value, field.name); // use the normal value
					}
				} else if(phase === "AfterReload"){
					if(field.valueAfterReload !== null && field.valueAfterReload !== undefined){
						this.checkOneField( widget, field.valueAfterReload, field.name);
					} else {
						this.checkOneField( widget, field.value, field.name); // use the normal value
					}
				} else {
					this.checkOneField( widget, field.value, field.name); // use the normal value
				}
			}
		},

		/**
		  * This function checks the data in a single field against a given value to
		  * ensure that it is correct.
		  */
		checkOneField : function(widget, value, name){
			var err = "Field " + name + " value is incorrect.";
			if(widget instanceof qx.ui.form.TextField ||
				widget instanceof qx.ui.form.PasswordField ||
				widget instanceof qx.ui.form.TextArea ||
				widget instanceof qx.ui.form.ComboBox
			){
				this.assertEquals(value, widget.getValue(), err)

			} else if(widget instanceof qx.ui.form.SelectBox ){
				this.assertEquals(value, widget.getSelection()[0].getLabel(), err);

			} else if(widget instanceof qx.ui.form.CheckBox ||
				widget instanceof qx.ui.form.RadioButton ||
				widget instanceof qx.ui.groupbox.CheckGroupBox ||
				widget instanceof qx.ui.groupbox.RadioGroupBox
			){
				this.assertEquals( value === "true" ? true : false, widget.getValue(), err );
			} else if (widget instanceof qx.ui.table.Table) {
				this.checkTableValues(widget, value, name);
				//this.assertJsonEquals(value, widget.getTableModel().getData(), err);
			} else {
				throw String("Unknown field type for field: " + name );
			}

		},

		/** This function walks through a list of table values and compares them against
		  * the actual cells in the live table.
		  */
		checkTableValues : function(tableWidget, value, name) {
			for(var i = 0, l = value.length; i < l; i++){
				var cellCheck = value[i];
				this.checkTableCellValue(
					tableWidget, cellCheck.row, cellCheck.col, cellCheck.value, name);
			}
		},

		/** This function compares row/column data in a table against a given value.
		  */
		checkTableCellValue: function(tableWidget, row, col, value, name){
			var tableCellVal = tableWidget.getTableModel().getValue( col, row );
			this.assertEquals( value, tableCellVal,
				"Table (" + name + ") value at row (" + row + ") col (" + col +
				") does not match.  Expected (" + value + ") actual (" + tableCellVal + ")"
			);
		}


	},

	statics :
	{

	},

	destruct : function () {


	}
});
