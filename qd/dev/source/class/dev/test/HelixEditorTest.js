/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */

/**
 * This class demonstrates how to define unit tests for your application.
 *
 * Execute <code>generate.py test</code> to generate a testrunner application
 * and open it from <tt>test/index.html</tt>
 *
 * The methods that contain the tests are instance methods with a
 * <code>test</code> prefix. You can create an arbitrary number of test
 * classes like this one. They can be organized in a regular class hierarchy,
 * i.e. using deeper namespaces and a corresponding file structure within the
 * <tt>test</tt> folder.
 */
qx.Class.define("dev.test.HelixEditorTest",
{
	extend : dev.test.HubTest,
	type : "abstract",
	construct : function() {
		this.base(arguments);
	},
	members :
	{
		_editor : null,

		/** Which tools/new menu should be invoked to create a new editor.
		  */
		_toolsNew : "Undefined",

		/** Which parent node in the tree will our items befound under:
		  */
		_treeNode : "Undefined",

		/** Which tree node name is used - full path.  Use this when _treeNode + "/" + _tabNameSaved
		  * doesn't work.
		  */
		_treeNodePath : null,

		/** Defines our tab name when we do a tools/New/...
		  */
		_tabNameNew : "NEW1",

		/** Defines our tab name after a save
		  */
		_tabNameSaved : "Undefined",

		/**
		  * This defines our test data, which consists of an array of fields.
		  * Our subclasses will define this.
		  */
		_testData : null,

		/**
		 *      Just in case this node was created and not deleted in a previous
		 *		test, delete it now.
		 */
		test0005_deleteOldNode : function()
		{
			var editorUtils = new dev.test.EditorTestUtil(this, this._treeNode, this._tabNameNew, this._tabNameSaved);
			editorUtils.deleteTreeNode(this._treeNode, this._tabNameSaved);
		},

		/**
		  * This tests opens the new editor and verifies all of the tab pages
		  * that should be in the editor.
		  */
		test0010_OpenNewEditor : function()
		{
			dev.test.TestStatics.selectToolsMenuItem("New", this._toolsNew);
			qx.event.Timer.once(function() {              // avoids resume called before wait when the app is fast
				this.waitForEditor(this._tabNameNew, function(editor)
				{
					this._editor = editor;                      // got it.
					this.resume();
				});
			}, this, 100);
			this.wait(15000);
		},

		/**
		  * The editor should come up with a series of default values populated.
		  * Check that all of the defaults are provided.
		  */
		test0020_VerifyDefaultData : function() {
			this.checkDefaultData();
		},

		/**
		  * The first save should fail because we haven't entered all of the
		  * data required for it to succeed.
		  */
		test0030_FirstSaveFails : function()
		{
			this._editor.addListener("saveFailed", function() {
				// Find and get rid of the error dialog.
				dev.test.TestStatics.waitForMessageDialog(null, function(dialog)
				{
					dialog.ok_btn.execute();

					// Need a small pause here so that wait() can be called.
					qx.event.Timer.once(function() {
						this.resume();
					}, this, 500);
				}, this);
			}, this);
			this.pressSave();                             // should trigger the saveFailed event
			this.wait(5000);
		},

		/**
		  * This test will populate all form fields based on our _testData structure
		  * defined above.  Parent class methods are used to make this simple for us.
		  */
		test0040_EnterValidData : function() {
			this.populateFormFields();
		},

		/**
		  * This test will save the editor after it has been populated with good data.
		  */
		test0050_SaveValidData : function()
		{
			// Catch any errors - hope this doesn't happen
			this._editor.addListener("saveFailed", function() {
				// Find and get rid of the error dialog.
				dev.test.TestStatics.waitForDialog("Alert", function(dialog)
				{
					dialog.ok_btn.execute();
					this.fail("Save of valid data failed.");
				}, this);
			}, this);

			// Catch the save success - this is what we want.
			this._editor.addListener("saveSucceeded", function() {
				// we saved successfully.

				// Need a small pause here so that wait() can be called.

				// qx.event.Timer.once( function() { this.resume(); }, this, 500 );
				this.resume();
			}, this);

			// Now actually press the save button
			var test = this;
			qx.event.Timer.once(function() {
				// should trigger the saveFailed event
				test.pressSave();
			}, this._test, 500);
			this.wait(50000);                             // wait for the saveSucceeded or saveFailed event.
		},

		/**
		  * This test will check the editor fields after they have been saved.  Some of
		  * them will have been modified during the verification steps.
		  */
		test0060_CheckDataAfterSave : function() {
			this.checkData("AfterSave");
		},

		/**
		  * This test will close the editor after it has been saved successfully.
		  */
		test0070_CloseEditor : function()
		{
			this.closeTab(this._tabNameSaved);

			// Verify that the editor did indeed close:
			qx.event.Timer.once(function() {
				this.waitForTabToClose(this._tabNameSaved, function() {
					this.resume();
				});
			}, this, 100);                                // give it a moment before starting the wait.
			this.wait(10000);                             // wait up to 10 seconds for the editor to close.
		},

		/**
		  * This test will open the editor on the new object.
		  */
		test0080_OpenEditor : function()
		{
			qx.event.Timer.once(function()
			{                                             // avoid's resume called before wait when the app is fast
				var treePath = this._treeNode + "/" + this._tabNameSaved;
				if (this._treeNodePath !== null)
				{
					treePath = this._treeNodePath;              // use the override
				}
				this.getFileTreeNode(treePath, function(treeNode)
				{
					this.doubleClick(treeNode);
					this.waitForEditor(this._tabNameSaved, function(editor)
					{
						this._editor = editor;                     // got it
						this.resume();
					});
				});
			}, this, 100);
			this.wait(10000);
		},

		/**
		  * This test will check the editor fields after it has been re-opened.
		  */
		test0090_CheckDataAfterReload : function() {
			this.checkData("AfterReload");
		},

		/**
		  * This test will delete the new object that we created.  This is usually
		  * overridden by the individual test classes to handle the delete call
		  * properly.
		  */
		test0100_DeleteNewObject : function()
		{
			qx.event.Timer.once(function()
			{                                             // avoid's resume called before wait when the app is fast
				var treePath = this._treeNode + "/" + this._tabNameSaved;
				if (this._treeNodePath !== null)
				{
					treePath = this._treeNodePath;              // use the override
				}
				this.getFileTreeNode(treePath, function(treeNode)
				{
					var tree = treeNode.getTree();
					var selection = [];
					selection.push(treeNode);
					tree.setSelection(selection);
					qx.core.Init.getApplication().deleteTreeSelection();
					dev.test.TestStatics.waitForDialog("Deleting...", function(dialog)
					{
						dialog.ok_btn.execute();

						// Need a small pause here so that wait() can be called.
						qx.event.Timer.once(function() {
							this.resume();
						}, this, 500);
					}, this);
				});
			}, this, 100);
			this.wait(10000);
		}
	},
	statics : {

	},
	destruct : function() {
	}
});
