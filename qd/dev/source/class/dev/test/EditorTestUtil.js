/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */


/**
 *    This mixin provides methods that allow manipulation of editor tabs
 *    to make writing tests easier.
 */
qx.Class.define("dev.test.EditorTestUtil", {

	extend: qx.core.Object,

	construct: function(test, treeNode, tabNameNew, tabNameSaved) {
		this.base(arguments);

	    this._test         = test;
	    this._treeNode     = treeNode;
	    this._tabNameNew   = tabNameNew;
	    this._tabNameSaved = tabNameSaved;

		if ( this._tabNameNew ) {

			this._test.debug( "tabNameNew is null" );
		}

		if ( this._tabNameSaved ) {

			this._test.debug( "tabNameSaved is null" );
		}

		if ( this._treeNode ) {

			this._test.debug( "treeNode is null" );
		}

		//		Stupid IE
		if (typeof console === "undefined") {
			console = {
				log: function (logMsg) {

					test.debug( logMsg );
			 	}
			};
		}
	},


	members: {

		_test: null,

		_editor: null,

		/** Which parent node in the tree will our items befound under:
		  */
		_treeNode: "Undefined",

		/** Defines our tab name when we do a tools/New/...
		  */
		_tabNameNew: "NEW1",

		/** Defines our tab name after a save
		  */
		_tabNameSaved: "Undefined",

		/**
		  * This defines our test data, which consists of an array of fields.
		  * Our subclasses will define this.
		  */
		_testData: null,

		_connectionInfo: {

			alias: "test",
			host: "viazos19",
			port: "6311",
			user: "SMC",
			pass: "SMC"
		},


		/**
		  *     Connect to the server.
		  */
		connect: function() {

			var connect_string = this._test.getServerHost()
				                 + "/" + this._test.getServerPort()
								 + "/" + this._test.getServerUser()
								 + "/" + this._test.getServerPass();

			var obj = new dev.sqldo.LogOn();

			obj.setHost( this._test.getServerHost() );
			obj.setPort( this._test.getServerPort() );
			obj.setUser( this._test.getServerUser() );
			obj.setPass( this._test.getServerPass() );
			obj.setAlias( 'test' );

			console.log( "Connecting to: " + connect_string );

			qx.event.Timer.once( function() {

				dev.Api.ConnectToServer( obj,
				    function(response) { // the success callback

					    console.log( "Connected to " + connect_string );

					    var objs      = dev.sqldo.LogOn.readElementChildren(response);
					    var app       = qx.core.Init.getApplication();
					    var menuLabel = objs[0].getConnName();

					    if ( app.serverMenu ) {
					    	app.serverMenu.setLabel( menuLabel );
					    }

					    app.addToServerMenu( menuLabel );

					    console.log( "EditorTestUtil.connect: calling resume in success" );
					    this.resume();
				    },
				    this,
				    function() { // the error callback

					   	// Connection to a DB did not succeed.
					    console.log( "EditorTestUtil.connect: calling resume in failure callback" );
					    this.resume();
				    });
			}, this._test, 500 );

			this._test.wait( 5000 );
		},


		executeEditorDialogOkButton: function( okButton ) {

			try {
				okButton.execute();
			} catch ( err ) {
				this.debug( "caught verification exception: " + err );
				if (/using exception to stop event processing./.test(err.message)) {
					this._test.debug( "got expected exception" );
				} else {
					this._test.debug( "got UNEXPECTED exception" );
					throw err;
				}
			}
		},


		/**
		  *    This function uses the data defined in _testData to drive the population
		  *    of all of our form fields.  We'll switch tabs as required to get each one
		  *    populated.
		  */
		populateFormFields: function( testData ) {

			if ( testData === null || testData === undefined) {

				throw "No testData defined to populate form fields.";
			}

			for (var i = 0, l = testData.length; i < l; i ++ ) {

				var field = testData[i];
				this.populateOneField( field );
			}
		},


		/**
		 *    This handles populating one field in the form based on the given input field
		  *    hash information.  The field has should look like this:
		  *    {name: "FieldWidgetName", value: "ValueForField" }
		  */
		populateOneField: function( field ) {

			var widget = this._editor[ field.name ];
			if (widget === null || widget === undefined) {

				throw String("_testData field " + field.name + " is not found in the editor.");
			}

			if ( widget instanceof qx.ui.form.TextField
				 || widget instanceof qx.ui.form.PasswordField
				 || widget instanceof qx.ui.form.TextArea
				 || widget instanceof qx.ui.form.ComboBox ) {

				widget.setValue( field.value );
			}
			else if ( widget instanceof qx.ui.form.SelectBox ) {

				dev.Statics.setDropDownByLabel( widget, field.value );
			}
			else if ( widget instanceof qx.ui.form.CheckBox
					  || widget instanceof qx.ui.form.RadioButton
					  || widget instanceof qx.ui.groupbox.CheckGroupBox
					  || widget instanceof qx.ui.groupbox.RadioGroupBox ) {

				widget.setValue( field.value === "true" ? true : false );
			}
			else if (widget instanceof qx.ui.table.Table) {

				//widget.getTableModel().setData(field.value);
			}
			else {

				throw String("Unknown field type for field: " + field.name );
			}
		},


		/**
		  * 	The first save should fail because we haven't entered all of the
		  * 	data required for it to succeed.
		  */
		saveFailsXXX: function() {

			this._editor.addListener("saveFailed", function() {

				// 		Find and get rid of the error dialog.
				dev.test.TestStatics.waitForMessageDialog( null, function(dialog) {

					console.log( "EditorTestUtil.saveFails: dialog says: " + dialog.label );
					dialog.ok_btn.execute();

					// 		Need a small pause here so that wait() can be called.
					// qx.event.Timer.once( function() {

						console.log( "EditorTestUtil.saveFails: calling resume after pressing ok button" );
						this._test.resume();
					// }, this, 500 );
				}, this );
			}, this );

			//		Seems to have more "resume before wait" messages w/o this Timer.once
			qx.event.Timer.once( function() {

				// should trigger the saveFailed event
				this.pressSave();
			}, this._test, 500);

			this._test.wait( 5000 );
		},
		saveFails: function() {

			this.pressSave();

			var repo = {}
			repo.test = this;

			this.tryWaitForDialog( null, 10, 2500, repo,
				function(dialog) {

					console.log( "found alert dialog: " + repo.dialog );
					repo.dialog.ok_btn.execute();
					console.log("Save of invalid data failed.");

					console.log( "dialog label: " + repo.dialog.label );
				},
				function( theTest ) {

					console.log( "theTest: " + theTest );
					theTest.fail( "Couldn't find the error dialog." );
				},
				this._test );

			console.log( "CacheTestUtils.executeOkAndWaitForError: exiting" );
	    },


		/**
	     * 		Finds and presses the "Save" Button on the toolbar.  We do this directly through
		 * 		the editor toolbar and save button.  This ensures that all events and actions
		 * 		are wired up together properly.
		 */
		pressSave: function () {

			this.pressEditorToolbar( this._editor, "Save" );
		},


		/**
		 * 		Finds and presses the named button on the editor toolbar.  We do this directly
		 * 		through the editor toolbar and save button.  This ensures that all events and actions
		 * 		are wired up together properly.
		 */
		pressEditorToolbar: function( editor, buttonName ) {

			var child1 = editor.getChildren()[ 0 ];

			if ( child1 instanceof qx.ui.toolbar.ToolBar ) {

				var part1 = child1.getChildren()[ 0 ];

				if ( part1 instanceof qx.ui.toolbar.Part ) {

					var children = part1.getChildren();

					for (var i = 0, l = children.length; i < l; i++) {

						if ( children[i] instanceof qx.ui.toolbar.Separator) { continue; }

						if ( children[i].getLabel().indexOf( buttonName ) === 0 ) {

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
		  * This test will save the editor after it has been populated with good data.
		  */
		saveValidData: function() {

			// Catch any errors - hope this doesn't happen
			this._editor.addListener("saveFailed", function() {
				// Find and get rid of the error dialog.
				dev.test.TestStatics.waitForDialog( "Alert", function(dialog) {
					dialog.ok_btn.execute();
					this._test.fail("Save of valid data failed.");
				}, this);
			}, this);

			// Catch the save success - this is what we want.
			this._editor.addListener("saveSucceeded", function() {
				// we saved successfully.
				// Need a small pause here so that wait() can be called.
				qx.event.Timer.once( function() { this._test.resume(); }, this, 500 );
			}, this );

			// Now actually press the save button
			this.pressSave();
			this._test.wait( 5000 ); // wait for the saveSucceeded or saveFailed event.
		},


		/**
		  * This test will close the editor after it has been saved successfully.
		  */
		closeEditor: function() {

			this.closeTab( this._tabNameSaved );

			// Verify that the editor did indeed close:
			qx.event.Timer.once( function() {

				this.waitForTabToClose( this._tabNameSaved, function() {

					this._test.resume();
				} );
			}, this, 100); // give it a moment before starting the wait.

			this._test.wait( 10000 ); // wait up to 10 seconds for the editor to close.
		},


		openNewEditor: function() {

			console.log( "Clicking on New -> " + this._test._toolsNew );
			dev.test.TestStatics.selectToolsMenuItem( "New", this._test._toolsNew );

			//     avoids resume called before wait when the app is fast
			qx.event.Timer.once( function() {

				console.log( "Waiting for editor tab: " + this._tabNameNew );
				this.waitForEditor( this._tabNameNew, function( editor ) {

					//     got it.
					this._test._editor = editor;
					this._editor       = editor;

					this._test.resume();
				} );
			}, this, 100);

			this._test.wait( 15000 );
		},


		/**
		  *    This function uses the data defined in _testData to check any fields that
		  *    have default data in them.  If no default value is defined for a field, that
		  *    field is skipped.
		  */
		checkDefaultData: function ( testData ) {

			//if (this._testData === null || this._testData === undefined) {
			if (testData === null || testData === undefined) {

				throw "No testData defined.";
			}

			for (var i = 0, l = testData.length; i < l; i ++ ) {

				var field = testData[i];
				if (field.defaultValue === null || field.defaultValue === undefined) {

					//    skip this field.
					continue;
				}

				var widget = this._test._editor[ field.name ];
				if ( widget === null || widget === undefined) {

					throw String("testData field " + field.name + " is not found in the editor.");
				}

				this.checkOneField( widget, field.defaultValue, field.name);
			}
		},


		/**
		  *    This function checks the data in a single field against a given value to
		  *    ensure that it is correct.
		  */
		checkOneField: function(widget, value, name) {

			var err = "Field " + name + " value is incorrect.";

			if ( widget instanceof qx.ui.form.TextField
				|| widget instanceof qx.ui.form.PasswordField
				|| widget instanceof qx.ui.form.TextArea
				|| widget instanceof qx.ui.form.ComboBox ) {

				this._test.assertEquals(value, widget.getValue(), err)
			}
			else if ( widget instanceof qx.ui.form.SelectBox ) {

				this._test.assertEquals(value, widget.getSelection()[0].getLabel(), err);
			}
			else if ( widget instanceof qx.ui.form.CheckBox
					  || widget instanceof qx.ui.form.RadioButton
					  || widget instanceof qx.ui.groupbox.CheckGroupBox
					  || widget instanceof qx.ui.groupbox.RadioGroupBox ) {

				this._test.assertEquals( value === "true" ? true : false, widget.getValue(), err );
			}
			else if (widget instanceof qx.ui.table.Table) {

				this.checkTableValues(widget, value, name);
				//this.assertJsonEquals(value, widget.getTableModel().getData(), err);
			}
			else {
				throw String("Unknown field type for field: " + name );
			}
		},


		/**
		 *		This function walks through a list of table values and compares them against
		 * 		the actual cells in the live table.
		 */
		checkTableValues: function(tableWidget, value, name) {

			for (var i = 0, l = value.length; i < l; i++) {

				var cellCheck = value[i];

				this.checkTableCellValue( tableWidget,
					                      cellCheck.row,
					                      cellCheck.col,
					                      cellCheck.value,
					                      name );
			}
		},


		/**
		 * 		This function compares row/column data in a table against a given value.
		 */
		checkTableCellValue: function(tableWidget, row, col, value, name) {

			var tableCellVal = tableWidget.getTableModel().getValue( col, row );

			this._test.assertEquals( value, tableCellVal,
				"Table (" + name + ") value at row (" + row + ") col (" + col +
				") does not match.  Expected (" + value + ") actual (" + tableCellVal + ")"
			);
		},



		/**
		  * This test will open the editor on the new object.
		  */
		openEditor: function() {

			//        avoids resume called before wait when the app is fast
			qx.event.Timer.once( function() {

				var treePath = this._treeNode + "/" + this._tabNameSaved;
				if ( this._treeNodePath !== null ) {
					treePath = this._treeNodePath; // use the override
				}

				this.getFileTreeNode( treePath, function(treeNode) {
					this.doubleClick( treeNode );

					this.waitForEditor( this._tabNameSaved, function(editor){
						this._editor = editor; // got it
						this.resume();
					} );
				} );
			}, this, 100);

			this.wait( 10000 );
		},


		/**
		 *    Try a number of times to wait for a dialog.  Can provide
		 *    the number of retries and the delay between retried.
		 */
		tryWaitForDialog: function( title, numTries, delay, repo, foundCallBack, notFoundCallBack, theThis ) {

			var searchFunction = function( title ) {

				return dev.test.TestStatics.findDialog( title );
			};

			this.tryWaitForSomething( title, numTries, delay, repo, searchFunction, foundCallBack, notFoundCallBack, theThis );
		},


		/**
		 *    Try a number of times to wait for a dialog.  Can provide
		 *    the number of retries and the delay between retried.
		 */
		tryWaitForSomething: function( title, numTries, delay, repo, searchFunction, foundCallBack, notFoundCallBack, theThis ) {

			var label  = "" + theThis + " ";
			// var dialog = dev.test.TestStatics.findDialog( title );
			var dialog = searchFunction.call( this, title );

			console.log( "dialog at start of tryWaitForDialog: " + dialog );

			if ( dialog ) {

				console.log( "FOUND DIALOG right off: " + dialog );
				console.log( "FOUND DIALOG right off, test is: " + theThis );

				repo.dialog = dialog;
				foundCallBack.call( theThis, theThis, dialog );
				return;
			}

			console.log( "waiting for dialog: " + title + " num tries: " + numTries + " delay: " + delay + " theThis: " + theThis );

			// Create timer instance
			var timer  = new qx.event.Timer(delay);
			var ii     = 0;

			// Add event listener to interval
			timer.addListener("interval", function(e) {

				console.log( label + "try: " + ii + " numTries: " + numTries + " theThis: " + theThis );

				// dialog = dev.test.TestStatics.findDialog( title );
				dialog = searchFunction.call( this, title );
				//theThis.debug( "dialog: " + dialog );

				if ( ii >= numTries || dialog ) {

					timer.stop();
					timer.dispose();

					console.log( label + "tryWaitForDialog: resuming" );
					theThis.resume( function() {
						repo.dialog = dialog;

						if ( dialog && foundCallBack ) {

							console.log( label + "tryWaitForDialog: in resume, calling callback with dialog: " + repo.dialog );
							foundCallBack.call( theThis, theThis, repo.dialog );
						}
						else if ( ! dialog && notFoundCallBack ) {

							console.log( label + "tryWaitForDialog: in resume, calling callback without dialog, with theThis: " + theThis );
							notFoundCallBack.call( theThis, theThis );
							// notFoundCallBack( theThis );
						}
					}, theThis );
				}

				ii++;
			}, theThis );

			//		Seems to have more "resume before wait" messages w/o this Timer.once
			qx.event.Timer.once( function() {
				timer.start();
			}, theThis, 500);

			console.log( label + "tryWaitForDialog: wait started for: " + (numTries + 3) * delay + " ms" );
			theThis.wait( (numTries + 3) * delay, null, theThis );
			console.log( label + "tryWaitForDialog: wait finished" );
		},


		/**
		  *    Delete a node in the tree by name, but do not wait for a dialog.
		  */
		deleteObjectByNameNoDialog: function( treeNodeName, subNodeName, rootNode ) {

			//this.debug( "tree node:      " + treeNodeName );
			//this.debug( "sub node:       " + subNodeName );

			//     avoids resume called before wait when the app is fast
			qx.event.Timer.once( function() {

				var treePath = treeNodeName + "/" + subNodeName;

				//this.debug( "tree path: " + treePath );

				this.getFileTreeNode( treePath, function(treeNode) {

					//this.debug( "about to call getTree" );
					//this.debug( "treeNode: " + treeNode );

					var tree      = treeNode.getTree();
					var selection = [];
					selection.push( treeNode );

					//this.debug( "tree node selection: " + selection );

					tree.setSelection( selection );
					qx.core.Init.getApplication().deleteTreeSelection();
					this._test.resume();
				},
				function( stuff ) {

					//this._test.debug( "Didn't find the tree node to delete: " + treePath );
					this._test.resume();
				}, rootNode );
			}, this, 0 );

			//this.debug( "tree node not found, resuming." );
			//qx.event.Timer.once( function() { this._test.resume(); }, this, 500 );
			this._test.wait( 10000 );
		},


		/**
		  *     This will delete the object that is created during the test.  This is usually
		  *     overridden by the individual test classes to handle the delete call
		  *     properly.
		  */
		deleteObjectByName: function( treeNodeName, subNodeName, rootNode ) {

			//this.debug( "tree node:      " + treeNodeName );
			//this.debug( "sub node:       " + subNodeName );

			//     avoids resume called before wait when the app is fast
			qx.event.Timer.once( function() {

				var treePath = treeNodeName + "/" + subNodeName;

				//this.debug( "tree path: " + treePath );

				this.getFileTreeNode( treePath,
				function(treeNode) {

					//this.debug( "about to call getTree" );
					//this.debug( "treeNode: " + treeNode );

					var tree      = treeNode.getTree();
					var selection = [];
					selection.push( treeNode );

					//this.debug( "tree node selection: " + selection );

					tree.setSelection( selection );
					qx.core.Init.getApplication().deleteTreeSelection();
					//this.debug( "waiting for Deleting... dialog" );

					dev.test.TestStatics.waitForDialog( "Deleting...",
					function(dialog) {
						dialog.ok_btn.execute();
						this._test.resume();

					}, this);
				},
				function( stuff ) {

					//this._test.debug( "Didn't find the tree node to delete: " + treePath );
					this._test.resume();
				}, rootNode );
			}, this, 0 );

			//this.debug( "tree node not found, resuming." );
			this._test.wait( 10000 );
		},


		/**
		  * This will delete the object that is created during the test.  This is usually
		  * overridden by the individual test classes to handle the delete call
		  * properly.
		  */
		deleteObject: function() {

			this.deleteTreeNode( this._treeNode, this._tabNameSaved );
		},


		/**
		  * This will delete the object that is created during the test.  This is usually
		  * overridden by the individual test classes to handle the delete call
		  * properly.
		  */
		deleteTreeNode: function( treeNode, tabNameSaved ) {

			this.debug( "tree node:      " + treeNode );
			this.debug( "tab name saved: " + tabNameSaved );

			this.deleteObjectByName( treeNode, tabNameSaved );
		},


		/** Use this in order to find/open a given node in the normal tree.  Use slashes
		  * to separate the levels: i.e. "Tables/HWRD/AUTHORS".
		  */
		getFileTreeNode: function( treePath, foundCallback, notFoundCallback, rootNode ) {

			//this.debug( "in getFileTreeNode" );
			//this.debug( "treePath: " + treePath );

			//this.debug( "foundCallback: " + foundCallback );
			//this.debug( "notFoundCallback: " + notFoundCallback );

			this.treePath = treePath.split("/");
			this.treePathCallback = notFoundCallback;

			if (rootNode) {
				var treeRoot = rootNode;
			} else {
				var treeRoot = qx.core.Init.getApplication().treeRoot;
			}

			//this.debug( "treeRoot: " + treeRoot );
			qx.core.Assert.assertNotNull( treeRoot, "Application tree root is null.");
			qx.core.Assert.assertNotUndefined( treeRoot, "Application tree root is null.");

			this.expectantParent = treeRoot;
			this.treePathIdx = 0;

			//this.debug( "calling childFound" );
			this.childFound( foundCallback, notFoundCallback );
		},


		/** This method is used by the getBrowseTreeNode, and getFileTreeNode.  Do not use
		  * this method directly.
		  */
		childFound: function( foundCallback, notFoundCallback ) {

			this.debug( "in childFound, expectant parent: ", this.expectantParent );

			// Find the next level child:
			var children  = this.expectantParent.getChildren();
			var childName = this.treePath[ this.treePathIdx ];
			var childNode = null;

			this.debug( "in childFound, child name: ", childName );

			for (var j = 0, m = children.length; j < m; j++) {

				this.debug( "in childFound, comparing to label: ", children[j].getLabel() );

				//      use indexOf instead of startsWith
				if (children[ j ].getLabel().indexOf( childName ) === 0) {
					childNode = children[ j ];
					break;
				}
			}

			if (childNode === null) {

				if ( notFoundCallback ) {

					notFoundCallback.call( this );
					return;
				}

				throw "Unknown child node: " + childName + " in browse tree.";
			}

			if (this.treePathIdx === (this.treePath.length - 1) ) {

				this.debug( "calling foundCallback with this: " + this + " and child node: " + childNode );
				foundCallback.call( this, childNode );
				return;
			}

			// otherwise, keep looking for the next level down:
			if ( ! childNode.isOpen() ) {

				childNode.toggleOpen();
			}

			this.treePathIdx ++;

			// wait for the childNode to open up and fill up its children:
			this.expectantParent = childNode;
			this.waitForChildren( foundCallback, notFoundCallback );
		},


		/** This method is used by the getBrowseTreeNode, and getFileTreeNode.  Do not use
		  * this method directly.
		  */
		waitForChildren: function( foundCallback, notFoundCallback ) {

			// children found
			if ( this.expectantParent.getChildren().length !== 0 ) {

				this.childFound( foundCallback, notFoundCallback );
				return;
			}

			// last node
			if (this.treePathIdx === (this.treePath.length - 1) ) {
				// otherwise wait for 1 second
				qx.event.Timer.once(
				function() {
					this.childFound( foundCallback, notFoundCallback );
				}, this, 1000 );
				return;
			}

			// otherwise wait for 1/2 second and check again:
			qx.event.Timer.once(
			function() {
				this.waitForChildren( foundCallback, notFoundCallback );
			}, this, 500 );
		},


		tryWaitForEditor: function( title, numTries, delay, repo, foundCallBack, notFoundCallBack, theThis ) {

			repo.findTab = this.findTab;
			var searchFunction = function( title ) {

				console.log( "EditorTestUtil.tryWaitForEditor: this: " + this );
				return this.findTab( title );
			};

			this.tryWaitForSomething( title, numTries, delay, repo, searchFunction, foundCallBack, notFoundCallBack, theThis );
		},

		/**
		 *    This method will wait for an editor with the given tab name.
		 */
		waitForEditor: function(editorName, callBack) {


			//     Check to see if the editor is present:
			var page = this.findTab( editorName );

			if ( page !== null ) {

				//      Found it.  Ensure that it is fully loaded and ready:
				var editor = page.getChildren()[0];
				if ( editor.isEditorLoaded() ) {

					callBack.call( this, editor );
				}
				else {

					editor.addListener("editorLoaded", function() {

						callBack.call( this, editor );
					}, this );
				}

				return;
			}

			//     If not, then wait for 1/2 second and try again:
			qx.event.Timer.once( function() {

				this.waitForEditor( editorName, callBack );
			}, this, 500 );
		},


		/**
		 *    This method will find a given tab name, or return null if
		 *    it doesn't exist.
		 */
		findTab: function(tabName) {

			var app   = qx.core.Init.getApplication();
			var pages = app.tabView.getChildren();

			for (var i = 0, l = pages.length; i < l; i++) {

				if ( pages[i].getLabel() === tabName
					 || pages[i].getLabel() === "*" + tabName ) {

					// Found it.  Ensure that it is fully loaded and ready:
					return pages[i];
				}
			}

			// Didn't find anything
			return null;
		},


		/**
		 *    This function closes the named tab.  This does its work directly through the
		 *    tab view and presses the close button on the tab directly.  This way all associated
		 *    events and actions should fire correctly
		 */
		closeTab: function(tabName) {

			var page = this.findTab( tabName );

			if (page === null) {

				throw "Tab named " + tabName + " is not open.";
			}

			page.getButton().fireDataEvent("close", page.getButton() );
		},


		/**
		 *    This method will wait for a named tab to close
		 */
		waitForTabToClose: function(tabName, callBack) {

			//     Check to see if the editor is present:
			var page = this.findTab( tabName );

			if (page === null) {

				// It's closed.  Call the callback
				callBack.call( this );
				return;
			}
			else {

				// If not, then wait for 1/2 second and try again:
				qx.event.Timer.once( function() {

					this.waitForTabToClose( tabName, callBack );
				}, this, 500 );
			}
		},


		copyMap: function( oldMap, newMap ) {

			//this.debug( "oldMap" + JSON.stringify( oldMap ) );
			//this.debug( "newMap" + JSON.stringify( newMap ) );

			for ( var i in oldMap ) {
				newMap[i] = oldMap[i];
			}

			//this.debug( "newMap" + JSON.stringify( newMap ) );
		},


		/**
		 *    tests to see if the given string starts with the given value.
		 */
		startsWith: function( source, match ) {

			if ( source.slice( 0, match.length ) === match ) {

				this.debug( "MATCH!" );
				return true;
			}

			return false;
		},


		/**
		 *     Try to pretty print an object.
		 */
		pprint : function(obj) {

			// Setup Arrays
			var sortedKeys = new Array();
			var sortedObj = {};
			var str = '';

			// Separate keys and sort them
			for (var i in obj){
				sortedKeys.push(i);
			}
			sortedKeys.sort();
			//console.log( sortedKeys );

			for(var p in sortedKeys) {
				var property_name = sortedKeys[p];
				var property_value = obj[property_name];
				var property_type = typeof obj[property_name];

				if ( property_name == 'content' || property_name == 'frameContent' ) {

					str += property_name + ':<' + property_type +  '>: {lots_o_stuff}\n';
					continue;
				}
				if ( typeof property_value == 'string' && property_value.lastIndexOf( 'function', 0 ) == 0 ) {

					str += property_name + ':<' + property_type +  '>: {function}\n';
					continue;
				}

				if (typeof property_value == 'string') {
					str += property_name + ':<string>: ' + property_value + ';\n';
				} else {
					str += property_name + ':<' + property_type +  '>: {' + print(property_value) + '}\n';
					//str += property_name + ': {\n' + print(property_name) + '}';
				}
					//console.log( str );
			}

			return str;
		}
	},

	statics: { },

	destruct: function() { }
});
