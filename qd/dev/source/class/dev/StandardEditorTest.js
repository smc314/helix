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
qx.Class.define("dev.StandardEditorTest",
{
	extend : qx.dev.unit.TestCase,
	construct : function() {
		this.base(arguments);
	},
	members :
	{
		_editor : null,
		_lastTest : false,
		_abortAll : false,
		_useNewEditor : true,
		_setup : true,

		/**
		  * This defines our test data, which consists of an array of fields.
		  * Our subclasses will define this.
		  */
		_testData : null,

		/**
		  * Our job is to create the editor object that will be the subject of
		  * the tests in this class.  This function should be overridden by our
		  * child test classes.
		  *
		  * This version should create an empty editor as if the user clicked on
		  * "New ..." on the toolbar.
		  */
		createEditorNew : function() {
		},

		/**
		  * Our job is to create the editor object that will be the subject of
		  * the tests in this class.  This function should be overridden by our
		  * child test classes.
		  *
		  * This version should create an editor with an input object as if the
		  * user double-clicked on an item in the tree to open and manipulate.
		  */
		createEditorExist : function() {
		},

		/**
		  * This function is executed prior to each of the test* methods defined
		  * below.
		  */
		setUp : function()
		{
			// If we're in the setup phase, don't do anything here:
			if (this._setup) {
				return;
			}

			// construct a CopyBookDisplay object and add it to our root.
			if (this._editor === null)
			{
				if (this._useNewEditor) {
					this._editor = this.createEditorNew();
				} else {
					this._editor = this.createEditorExist();
				}
				var width = 80;
				var height = 80;
				qx.core.Init.getApplication().getRoot().add(this._editor,
				{
					minWidth : width,
					width : width,
					maxWidth : width,
					height : height,
					minHeight : height,
					maxHeight : height
				});
			}
		},

		/**
		  * This function is executed after each of the test* methods defined
		  * below.
		  */
		tearDown : function() {
			if (this._lastTest === true)
			{
				qx.core.Init.getApplication().getRoot().remove(this._editor);
				this._disposeObjects(this._editor);

				// Support re-running without re-loading
				this._editor = null;
				this._lastTest = false;
			}
		},

		/**
		  * Just in case anyone needs it, we'll load our singleton and system
		  * properties, just like our normal application does.
		  */
		test0000_LoadSingleton : function()
		{
			dev.Api.UserProperties( {

			}, {

			}, this, function() {
				this.resume();
			});
			this.wait(5000);
		},

		/**
		  * Just in case anyone needs it, we'll load our singleton and system
		  * properties, just like our normal application does.
		  */
		test0001_LoadSystemProps : function()
		{
			dev.Api.SystemProperties(this, function()
			{
				this._setup = false;                         // done with the setup phase.
				this.resume();
			});
			this.wait(5000);
		},

		/**
		  * This tests opens the new editor and verifies all of the tab pages
		  * that should be in the editor.
		  */
		test0010_OpenNewEditor : function()
		{
			// We only need to do this with the event listener on the first

			// test method, because it runs so quickly after the object has been

			// created.
			if (this._editor.isEditorLoaded()) {
				// nothting to do
				return;
			}
			this._editor.addListener("editorLoaded", function() {
				// Verify all of the tab pages here by switching to them:

				// Then switch back to the General tab:

				//ascfg.test.StandardEditorTest.selectTabViewPage("General");
				this.resume();
			}, this);
			this.wait(10000);
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
			this._editor.addListener("saveFailed", function()
			{
				// Find and get rid of the error dialog.
				var dialog = null;
				var count = 0;
				while (dialog === null && count < 100)
				{                                            // look for it only 100 times.
					dialog = dev.StandardEditorTest.findMessageDialog();
					count++;
				}
				if (dialog === null) {
					throw "Could not find error dialog.";
				}
				dialog.ok_btn.execute();

				// Need a small pause here so that wait() can be called.
				qx.event.Timer.once(function() {
					this.resume();
				}, this, 500);
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
			this._editor.addListener("saveSucceeded", function() {
				// we saved successfully.

				// Need a small pause here so that wait() can be called.
				qx.event.Timer.once(function() {
					this.resume();
				}, this, 500);
			}, this);
			this.pressSave();
			this.wait(5000);                              // wait for the saveSucceeded event.
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
			this._lastTest = true;                        // will trigger the close of the editor.
			this._useNewEditor = false;                   // will trigger the open of the editor with a data object.
		},

		/**
		  * This test will open the editor on the new object.
		  */
		test0080_OpenEditor : function()
		{
			// We need to do this with the event listener any time the editor is

			// being re-opened.
			if (this._editor.isEditorLoaded()) {
				// nothting to do
				return;
			}
			this._editor.addListener("editorLoaded", function() {
				this.resume();
			}, this);
			this.wait(10000);
		},

		/**
		  * This test will check the editor fields after it has been re-opened.
		  */
		test0090_CheckDataAfterReload : function()
		{
			this.checkData("AfterReload");

			// Set this back to true so that the user tests can work with

			// another new object if they like.
			this._useNewEditor = true;
		},

		/**
		  * This test will delete the new object that we created.  This is usually
		  * overridden by the individual test classes to handle the delete call
		  * properly.
		  */
		test0100_DeleteNewObject : function() {
		},

		/**
		  * The last test in this class will simply set the _lastTest boolean
		  * to true.  This will trigger our tearDown function to get rid of our
		  * testing form.
		  */
		test9999_LastTest : function() {
			this._lastTest = true;
		},

		/* ******************************************************************* */

		/* Utility functions that come in handy for each of our child classes  */

		/* to be able to access.                                               */

		/* ******************************************************************* */

		/**
		  * Simulates pressing the "Save" Button on the toolbar.
		  */
		pressSave : function() {
			this._editor.doSaveToServer();
		},

		/**
		  * This function uses the data defined in _testData to drive the population
		  * of all of our form fields.  We'll switch tabs as required to get each one
		  * populated.
		  */
		populateFormFields : function()
		{
			if (this._testData === null || this._testData === undefined) {
				throw "No _testData defined to populate form fields.";
			}
			for (var i = 0, l = this._testData.length; i < l; i++)
			{
				var field = this._testData[i];
				var widget = this._editor[field.name];
				if (widget === null || widget === undefined) {
					throw String("_testData field " + field.name + " is not found in the editor.");
				}
				if (widget instanceof qx.ui.form.TextField || widget instanceof qx.ui.form.PasswordField || widget instanceof qx.ui.form.TextArea || widget instanceof qx.ui.form.ComboBox) {
					widget.setValue(field.value);
				} else if (widget instanceof qx.ui.form.SelectBox) {
					dev.Statics.setDropDownByLabel(widget, field.value);
				} else if (widget instanceof qx.ui.form.CheckBox || widget instanceof qx.ui.form.RadioButton || widget instanceof qx.ui.groupbox.CheckGroupBox || widget instanceof qx.ui.groupbox.RadioGroupBox) {
					widget.setValue(field.value === "true" ? true : false);
				} else if (widget instanceof qx.ui.table.Table) {
					widget.getTableModel().setData(field.value);
				} else {
					throw String("Unknown field type for field: " + field.name);
				}



			}
		},

		/**
		  * This function uses the data defined in _testData to check any fields that
		  * have default data in them.  If no default value is defined for a field, that
		  * field is skipped.
		  */
		checkDefaultData : function()
		{
			if (this._testData === null || this._testData === undefined) {
				throw "No _testData defined.";
			}
			for (var i = 0, l = this._testData.length; i < l; i++)
			{
				var field = this._testData[i];
				if (field.defaultValue === null || field.defaultValue === undefined)
				{
					continue;                                   // skip this field.
				}
				var widget = this._editor[field.name];
				if (widget === null || widget === undefined) {
					throw String("_testData field " + field.name + " is not found in the editor.");
				}
				this.checkOneField(widget, field.defaultValue, field.name);
			}
		},

		/**
		  * This function uses the data defined in _testData to check all standard field data.
		  */
		checkData : function(phase)
		{
			if (this._testData === null || this._testData === undefined) {
				throw "No _testData defined.";
			}
			for (var i = 0, l = this._testData.length; i < l; i++)
			{
				var field = this._testData[i];
				var widget = this._editor[field.name];
				if (widget === null || widget === undefined) {
					throw String("_testData field " + field.name + " is not found in the editor.");
				}
				if (phase === "AfterSave") {
					if (field.valueAfterSave !== null && field.valueAfterSave !== undefined) {
						this.checkOneField(widget, field.valueAfterSave, field.name);
					} else
					{
						this.checkOneField(widget, field.value, field.name);           // use the normal value
					}
				} else if (phase === "AfterReload") {
					if (field.valueAfterReload !== null && field.valueAfterReload !== undefined) {
						this.checkOneField(widget, field.valueAfterReload, field.name);
					} else
					{
						this.checkOneField(widget, field.value, field.name);           // use the normal value
					}
				} else
				{
					this.checkOneField(widget, field.value, field.name);            // use the normal value
				}

			}
		},

		/**
		  * This function checks the data in a single field against a given value to
		  * ensure that it is correct.
		  */
		checkOneField : function(widget, value, name)
		{
			var err = "Field " + name + " value is incorrect.";
			if (widget instanceof qx.ui.form.TextField || widget instanceof qx.ui.form.PasswordField || widget instanceof qx.ui.form.TextArea || widget instanceof qx.ui.form.ComboBox) {
				this.assertEquals(value, widget.getValue(), err)
			} else if (widget instanceof qx.ui.form.SelectBox) {
				this.assertEquals(value, widget.getSelection()[0].getLabel(), err);
			} else if (widget instanceof qx.ui.form.CheckBox || widget instanceof qx.ui.form.RadioButton || widget instanceof qx.ui.groupbox.CheckGroupBox || widget instanceof qx.ui.groupbox.RadioGroupBox) {
				this.assertEquals(value === "true" ? true : false, widget.getValue(), err);
			} else if (widget instanceof qx.ui.table.Table) {
				this.assertJsonEquals(value, widget.getTableModel().getData(), err);
			} else {
				throw String("Unknown field type for field: " + name);
			}



		}
	},
	statics :
	{
		selectTabViewPage : function(tabView, pageName)
		{
			var pages = tabView.getChildren();
			for (var i = 0, l = pages.length; i < l; i++) {
				if (pages[i].getLabel() === pageName)
				{
					tabView.setSelection([pages[i]]);
					return;
				}
			}
			throw String("Tab Page Not Found: " + pageName);
		},
		findMessageDialog : function(title)
		{
			var rootChildren = qx.core.Init.getApplication().getRoot().getChildren();
			for (var i = 0, l = rootChildren.length; i < l; i++)
			{
				var child = rootChildren[i];
				if (child instanceof dev.dialog.MessageDialog) {
					if (title !== null && title !== undefined)
					{
						// Check the title against the window caption.
						var caption = child.getCaption();
						if (caption.indexOf(title) !== -1) {
							return child;
						}
					} else
					{
						// title not provided, just return the first MessageDialog we find.
						return child;
					}
				}
			}
			return null;                                  // Message Dialog not found.
		}
	},
	destruct : function() {
	}
});
