/* ************************************************************************

   Copyright: 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors:  Steven M. Cherry

************************************************************************ */

/* ************************************************************************
#asset(dev/icon/64x64/shadow/data_scroll.png)
#asset(dev/icon/16x16/plain/scroll2_add.png)
#asset(dev/icon/16x16/plain/delete2.png)
#asset(dev/icon/16x16/plain/navigate_up2.png)
#asset(dev/icon/16x16/plain/navigate_down2.png)
#asset(dev/icon/16x16/plain/table2_run.png)
#asset(dev/icon/16x16/plain/gears_run.png)
#asset(dev/icon/16x16/plain/bullet_triangle_glass_green.png)
#asset(dev/icon/16x16/plain/check.png)
#asset(dev/icon/16x16/plain/checks.png)
#asset(dev/icon/16x16/plain/scales.png)
#asset(dev/icon/16x16/plain/floppy_disk_yellow.png)
#asset(dev/icon/16x16/plain/scales.png)
#asset(dev/icon/16x16/plain/floppy_disk_yellow.png)
#asset(dev/icon/16x16/plain/scales.png)
#asset(dev/icon/16x16/plain/floppy_disk_yellow.png)
#asset(dev/icon/16x16/plain/scales.png)
#asset(dev/icon/16x16/plain/floppy_disk_yellow.png)
#asset(dev/icon/16x16/plain/cubes_blue_add.png)
#asset(dev/icon/16x16/plain/objects_transform.png)
#asset(dev/icon/64x64/shadow/code_c.png)
#asset(dev/icon/16x16/plain/data_scroll.png)
************************************************************************ */
qx.Class.define("dev.dataobj.SqlDOEditor",
{
	extend : dev.ObjectEdit,
	construct : function(object_id)
	{
		this.dynamicLayouts = [];
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.MainPage.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.NextPage.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.TestsPage.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.SqlStmtPage.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.SqlMetaPage.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.TestLiveMetadata.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.TestLiveResults.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.TestSavedMetadata.xml",
			doc : null
		});
		this.dynamicLayouts.push(
		{
			name : "SqlDOEditor.TestSavedResults.xml",
			doc : null
		});
		this.currentStmt = null;
		this.currentTest = null;
		this.base(arguments, object_id);
	},
	members :
	{
		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = dev.Api.GetIAFileDetails;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function(tb)
		{
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb);                     // Call the parent class first

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function()
		{
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, {
				flex : 10
			});
			this.createMainTab(dev.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(dev.Statics.addEditorSubTab(this.tabview, "SQL Statements", false));
			this.createTestsTab(dev.Statics.addEditorSubTab(this.tabview, "Tests", false));

			// Load more tabs here
		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab : function(tab_page)
		{
			var live = this.createOverviewLayout(tab_page, "Data Object Editor",
				"dev/icon/64x64/shadow/data_scroll.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getFileName());
			this.addStatusHeading("General");
			this.addStatusHint("Use this editor to define the Data Object that you would like to use " + "in your code." + "<p>" + "Group related SQL statements together into a single Data Object so that you can share " + "fields between the statements.  Try to keep unrelated statements in different Data Objects " + "so that the Object class layout is reasonable.");

			dev.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("SqlDOEditor.MainPage.xml"), live);
			this.childStandardTable = new dev.StandardTable(this.childTable,
				this.childVectAddNew, this.childVectDelete);
			this.childStandardTable.setDefaultRowData(["NewChildVector", "ChildVectorDataType"]);
			this.childVectAddNew.setToolTipText("Add New Child Vector");
			this.childVectDelete.setToolTipText("Delete Selected Child Vectors");

			// Both columns in the child vector table are editable
			this.childStandardTable.setEditable(0);
			this.childStandardTable.setEditable(1);
		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab : function(tab_page)
		{
			// These are icons referenced in the layout.  Do not delete these comments:

			// "dev/icon/16x16/plain/scroll2_add.png"

			// "dev/icon/16x16/plain/delete2.png"

			// "dev/icon/16x16/plain/navigate_up2.png"

			// "dev/icon/16x16/plain/navigate_down2.png"

			// "dev/icon/16x16/plain/table2_run.png"

			// "dev/icon/16x16/plain/gears_run.png"

			// "dev/icon/16x16/plain/bullet_triangle_glass_green.png"

			// "dev/icon/16x16/plain/check.png"

			// "dev/icon/16x16/plain/checks.png"
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.NextPage.xml"), tab_page);
			this.sqlTabView = new qx.ui.tabview.TabView;
			this.rightBox.add(this.sqlTabView, {
				flex : 10
			});
			this.createSqlStmtTab(dev.Statics.addEditorSubTab(this.sqlTabView, "Statement", true));
			this.createSqlSampleTab(dev.Statics.addEditorSubTab(this.sqlTabView, "Sample Results", false));
			this.stmtStandardTable = new dev.StandardTable(this.stmtTable);
			this.stmtTable.getSelectionModel().addListener("changeSelection", this.stmtChange, this);
			this.stmtAddNew.addListener("execute", this.addSqlStatement, this);
			this.stmtAddNew.setToolTipText("Add New SQL Statement");
			this.stmtDelete.addListener("execute", this.deleteSqlStatement, this);
			this.stmtDelete.setToolTipText("Delete Selected SQL Statements");
			this.stmtCreateCrud.addListener("execute", this.createCrudStatements, this);
			this.stmtCreateCrud.setToolTipText("Create Standard CRUD SQL Statements");
			this.stmtDuplicate.addListener("execute", this.duplicateSqlStatement, this);
			this.stmtDuplicate.setToolTipText("Duplicate Selected SQL Statements");

		},

		createTestsTab : function(tab_page)
		{
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.TestsPage.xml"), tab_page);
			this.testStandardTable = new dev.StandardTable(this.testTable);
			this.testTable.getSelectionModel().addListener("changeSelection", this.testChange, this);
			this.testAddNew.addListener("execute", this.addTest, this);
			this.testAddNew.setToolTipText("Add New Test");
			this.testDelete.addListener("execute", this.deleteTest, this);
			this.testDelete.setToolTipText("Delete Selected Tests");
			this.testInputTable.getTableModel().setColumnEditable(2, true);   // Third column is editable.
			this.testResultsView = new qx.ui.tabview.TabView;
			this.testResultsPanel.add(this.testResultsView, {
				flex : 10
			});
			this.createLiveResultsTab(dev.Statics.addEditorSubTab(this.testResultsView, "Live Results", true));
			this.createLiveMetadataTab(dev.Statics.addEditorSubTab(this.testResultsView, "Live Metadata", false));
			this.createSavedResultsTab(dev.Statics.addEditorSubTab(this.testResultsView, "Saved Results", false));
			this.createSavedMetadataTab(dev.Statics.addEditorSubTab(this.testResultsView, "Saved Metadata", false));
		},

		createLiveResultsTab : function(tab_page)
		{
			// These are icons referenced in the layout.  Do not delete these comments:

			// "dev/icon/16x16/plain/scales.png"

			// "dev/icon/16x16/plain/floppy_disk_yellow.png"
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.TestLiveResults.xml"), tab_page);
			this.liveResultsCompare.setToolTipText("Compare Live and Saved Results in a new Window");
			this.liveResultsSave.setToolTipText("Save the Live Results and Metadata.");
		},

		createLiveMetadataTab : function(tab_page)
		{
			// These are icons referenced in the layout.  Do not delete these comments:

			// "dev/icon/16x16/plain/scales.png"

			// "dev/icon/16x16/plain/floppy_disk_yellow.png"
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.TestLiveMetadata.xml"), tab_page);
			this.liveMetaCompare.setToolTipText("Compare Live and Saved Metadata in a new Window");
			this.liveMetaSave.setToolTipText("Save the Live Results and Metadata.");
		},

		createSavedResultsTab : function(tab_page)
		{
			// These are icons referenced in the layout.  Do not delete these comments:

			// "dev/icon/16x16/plain/scales.png"

			// "dev/icon/16x16/plain/floppy_disk_yellow.png"
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.TestSavedResults.xml"), tab_page);
			this.savedResultsCompare.setToolTipText("Compare Live and Saved Results in a new Window");
			this.savedResultsSave.setToolTipText("Save the Live Results and Metadata.");
		},

		createSavedMetadataTab : function(tab_page)
		{
			// These are icons referenced in the layout.  Do not delete these comments:

			// "dev/icon/16x16/plain/scales.png"

			// "dev/icon/16x16/plain/floppy_disk_yellow.png"
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.TestSavedMetadata.xml"), tab_page);
			this.savedMetaCompare.setToolTipText("Compare Live and Saved Metadata in a new Window");
			this.savedMetaSave.setToolTipText("Save the Live Results and Metadata.");
		},

		createSqlStmtTab : function(tab_page)
		{
			// These are icons referenced in the layout.  Do not delete these comments:

			// "dev/icon/16x16/plain/cubes_blue_add.png"

			// "dev/icon/16x16/plain/objects_transform.png"
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.SqlStmtPage.xml"), tab_page);
			this.StatementNameField.addListener("input", this.stmtNameChange, this);
			this.methodTypeField.addListener("changeValue", this.methodTypeChange, this);
			this.methodTargetField.addListener("changeValue", this.methodTargetChange, this);
			this.stmtField.setFont(new qx.bom.Font(14, ["monospace"]));
			dev.Statics.addToDropDown(this.methodTypeField, "SELECTTOXML", "SELECTTOXML");
			dev.Statics.addToDropDown(this.methodTypeField, "INSERT", "INSERT");
			dev.Statics.addToDropDown(this.methodTypeField, "UPDATE", "UPDATE");
			dev.Statics.addToDropDown(this.methodTypeField, "DELETE", "DELETE");
			dev.Statics.addToDropDown(this.methodTargetField, "odbc", "odbc");
			dev.Statics.addToDropDown(this.methodTargetField, "sqldb", "sqldb");
			this.stmtLoadOne.addListener("execute", this.loadSqlStatement, this);
			this.stmtLoadOne.setToolTipText("Run SQL and capture Metadata and Results");
			this.inputOutputStandardTable = new dev.StandardTable(this.inputOutputTable, this.ioFieldsAddNew, this.ioFieldsDelete, this.ioFieldsMoveUp, this.ioFieldsMoveDown);
			this.inputOutputStandardTable.defaultRowData = ["NewInputOutputField", "Input", "twine"];
			this.ioFieldsAddNew.setToolTipText("Add a new Input/Output Field");
			this.ioFieldsDelete.setToolTipText("Delete the selected Input/Output Fields");
			this.ioFieldsMoveUp.setToolTipText("Move the selected fields up in the list");
			this.ioFieldsMoveDown.setToolTipText("Move the selected fields down in the list");
			this.ioFieldsCopyFromMeta.addListener("execute", this.doIOFieldCopyFromMeta, this);
			this.ioFieldsCopyFromMeta.setToolTipText("Add Output Fields based on Sample Results Metadata");

			// IO Table First column is directly editable
			this.inputOutputStandardTable.setEditable(0);

			// IO Table Second column is editable as a drop-down selectbox
			this.inputOutputStandardTable.setEditableAsDropDown(1, ["Input", "Output"]);

			// IO Table Third column is editable as a drop-down selectbox
			this.inputOutputStandardTable.setEditableAsDropDown(2, ["twine", "int", "autogen", "base64", "bin", "cdata", "float", "Timestamp"]);
		},
		createSqlSampleTab : function(tab_page)
		{
			dev.layout.LayoutEngine.renderLayout(this, this.getDynamicLayout("SqlDOEditor.SqlMetaPage.xml"), tab_page);
			this.ioFieldsCopyFromMeta2.addListener("execute", this.doIOFieldCopyFromMeta, this);
			this.ioFieldsCopyFromMeta2.setToolTipText("Create Output Fields based on Sample Results Metadata");
		},
		stmtNameChange : function(e)
		{
			var row = this.stmtStandardTable.getFirstSelected();
			this.stmtTable.getTableModel().setValue(0, row, this.StatementNameField.getValue());
		},
		methodTypeChange : function(e)
		{
			var row = this.stmtStandardTable.getFirstSelected();
			this.stmtTable.getTableModel().setValue(1, row, this.methodTypeField.getValue());
		},
		methodTargetChange : function(e)
		{
			var row = this.stmtStandardTable.getFirstSelected();
			this.stmtTable.getTableModel().setValue(2, row, this.methodTargetField.getValue());
		},
		stmtChange : function(e)
		{
			if (this.currentStmt !== null) {
				// Save whatever is in the form back to the current statement before

				// switching to the next table row.
				this.pullOneStatement(this.currentStmt);
			}

			// Find the new statement based on the table selection:

			//var row = this.stmtTable.getFocusedRow();
			var row = this.stmtStandardTable.getFirstSelected();
			if (row !== null)
			{
				var stmtName = this.stmtTable.getTableModel().getValue(0, row);
				var resetDirtyFlag = !this.isDirty;
				this.currentStmt = dev.Statics.xmlFindChildWithAttr(this.dataObject.documentElement, "SqlStatement", "methodName", stmtName);
				if (this.currentStmt) {
					this.loadOneStatement(this.currentStmt);
				}
				if (resetDirtyFlag) {
					// Our dirty flag was not set before we did the load fields.

					// turn it back off again.
					this.resetDirty();
				}
			}

			// Ensure that we clear out any results metadata or sample results
			var rowData = [];
			this.stmtMetaTable.getTableModel().setData(rowData);
			this.stmtResultsTable.getTableModel().setData(rowData);
		},
		loadOneStatement : function(stmtNode)
		{
			this.StatementNameField.setValue(stmtNode.getAttribute("methodName"));
			dev.Statics.setDropDownByValue(this.methodTypeField, stmtNode.getAttribute("methodType"));
			if (this.currentStmt.hasAttribute("target")) {
				dev.Statics.setDropDownByValue(this.methodTargetField, stmtNode.getAttribute("target"));
			} else {
				dev.Statics.setDropDownByValue(this.methodTargetField, "odbc");
			}
			this.DescriptionField.setValue(dev.Statics.xmlGetText(dev.Statics.xmlFindChild(stmtNode, "Comment")));
			this.stmtField.setValue(dev.Statics.xmlGetText(dev.Statics.xmlFindChild(stmtNode, "Sql")));

			// Load the input output fields
			this.loadIOFields(stmtNode);
		},
		loadIOFields : function(stmtNode)
		{
			var rowData = [];
			for (var i = 0, l = stmtNode.childNodes.length; i < l; i++)
			{
				var node = stmtNode.childNodes[i];
				if (node.nodeName === "Input" || node.nodeName === "Output") {
					rowData.push([node.getAttribute("name"), node.nodeName, node.getAttribute("type")]);
				}
			}
			this.inputOutputTable.getTableModel().setData(rowData);
		},
		pullOneStatement : function(stmtNode)
		{
			// Clean out all children of the given node and re-build it from scratch:
			while (stmtNode.childNodes.length != 0)stmtNode.removeChild(stmtNode.childNodes[0]);

			stmtNode.setAttribute("methodName", this.StatementNameField.getValue());
			stmtNode.setAttribute("methodType", this.methodTypeField.getSelection()[0].getModel());
			stmtNode.setAttribute("target", this.methodTargetField.getSelection()[0].getModel());
			var doc = stmtNode.ownerDocument;
			var commentNode = doc.createElement("Comment");
			stmtNode.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, this.DescriptionField.getValue());
			var sqlNode = doc.createElement("Sql");
			stmtNode.appendChild(sqlNode);
			dev.Statics.xmlSetText(sqlNode, this.stmtField.getValue());
			var ioModel = this.inputOutputTable.getTableModel();
			for (var i = 0, l = ioModel.getRowCount(); i < l; i++)
			{
				var ioNode = doc.createElement(ioModel.getValue(1, i));
				stmtNode.appendChild(ioNode);
				ioNode.setAttribute("name", ioModel.getValue(0, i));
				var type = ioModel.getValue(2, i);
				if (type && type.length !== 0) {
					ioNode.setAttribute("type", type);
				} else {
					ioNode.setAttribute("type", "twine");
				}
			}
		},

		/** Our job is to create output fields from the current sample results
		  */
		doIOFieldCopyFromMeta : function(e)
		{
			var metaModel = this.stmtMetaTable.getTableModel();
			if (metaModel.getRowCount() === 0)
			{
				dev.Statics.doAlert("No current metadata.  Please execute the SQL Statement first.");
				return;
			}
			var stmtNode = this.currentStmt;
			var doc = stmtNode.ownerDocument;

			// First, get rid of any existing "Output" fields:

			// don't use l = length in this for-loop, because length is going to be changed inside

			// the loop, so it needs to be re-calculated every iteration
			for (var i = 0; i < stmtNode.childNodes.length; i++) {
				if (stmtNode.childNodes[i].nodeName === "Output")
				{
					// remove this node, and adjust our loop counter accordingly
					stmtNode.removeChild(stmtNode.childNodes[i]);
					i--;
				}
			}

			// Next, create new Output fields based on the results metadata
			for (var i = 0, l = metaModel.getRowCount(); i < l; i++)
			{
				var oNode = doc.createElement("Output");
				stmtNode.appendChild(oNode);
				oNode.setAttribute("name", this.mangleFieldName(metaModel.getValue(1, i)));
				oNode.setAttribute("type", this.translateType(metaModel.getValue(2, i)));
			}

			// Now re-display our input/output table.
			this.loadIOFields(stmtNode);
		},

		/** Our job is to take a result set column name and mangle it into a better
		  * looking name that is safe to use as an object member name.  We'll ensure
		  * the first letter is caps, lower-case the rest, remove any white-space or
		  * deves or underscores (uppercasing the next letter), and remove any illegal
		  * characters.
		  */
		mangleFieldName : function(orig)
		{
			var ret = qx.lang.String.clean(orig);         // first clean it up.
			//ret = ret.toLowerCase();                      // lower-case the whole string

			// Remove invalid characters:
			ret = ret.replace(/[^a-z,A-Z,0-9,_]/g, function(match, chr) {
				return " ";
			});

			// CamelCase based on deves:
			ret = ret.replace(/\-([a-z,A-Z,0-9])/g, function(match, chr) {
				return chr.toUpperCase();
			});

			// CamelCase based on underscores:
			ret = ret.replace(/\_([a-z,A-Z,0-9])/g, function(match, chr) {
				return chr.toUpperCase();
			});

			// CamelCase based on spaces:
			ret = ret.replace(/\ ([a-z,A-Z,0-9])/g, function(match, chr) {
				return chr.toUpperCase();
			});

			// Uppercase the first letter:
			ret = qx.lang.String.firstUp(ret);

			// return the result:
			return ret;
		},

		/** We'll translate a Database column type into the closest match for a data object
		  * field type.
		  */
		translateType : function(dbType) {
			if (dbType === "WLONGVARCHAR" || dbType === "WVARCHAR" || dbType === "WCHAR" || dbType === "CHAR" || dbType === "VARCHAR" || dbType === "LONGVARCHAR") {
				return "twine";
			} else if (dbType === "BIT" || dbType === "BYTEINT" || dbType === "INTEGER" || dbType === "SMALLINT") {
				return "int";
			} else if (dbType === "DECIMAL" || dbType === "FLOAT" || dbType === "REAL" || dbType === "DOUBLE") {
				return "float";
			} else if (dbType === "DATE" || dbType === "TIME" || dbType === "TIMESTAMP") {
				return "Timestamp";
			} else if (dbType === "LONGVARBINARY" || dbType === "VARBINARY" || dbType === "BINARY") {
				return "bin";
			} else {
				return "twine";
			}




		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function()
		{
			/* ******************************************************* */

			/* Do Any initialization here to this.dataObject           */

			/* ******************************************************* */
			this.isNewObject = true;
			this.dataObject = dev.Statics.xmlStringToDoc("<SQLXml generateClass=\"NewClass\" package=\"logic/dev\"/>");
			this.testObject = dev.Statics.xmlStringToDoc("<DataObjectTest do=\"NewClass\" tester=\"NewClassTest\"/>");

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();
			this.fieldModified();
		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function(response)
		{
			var objectList = dev.sqldo.IAFile.readElementChildren(response);
			if (objectList.length === 0)
			{
				this.resetDirty();
				dev.Statics.doAlert("File " + this.m_object_id.getFileName() + " was not found.");
				return;                                      // Nothing to do.
			}

			// Pick up the contents, and turn it into a real XML document that we can

			// work with directly.
			var contents = objectList[0].getFileContents();
			this.dataObject = dev.Statics.xmlStringToDoc(contents);
			if (this.dataObject === null)
			{
				dev.Statics.doAlert("File " + this.m_object_id.getFileName() + " is not an XML Document.");
				this.resetDirty();
				return;
			}

			// Double-check the root element:
			var elem = this.dataObject.documentElement;
			if (elem.nodeName !== "SQLXml")
			{
				dev.Statics.doAlert("File " + this.m_object_id.getFileName() + " is not an SQLXml Document.");
				this.dataObject = null;
				this.resetDirty();
				return;
			}

			// Also load any test xml file that we can find
			var testFile = new dev.sqldo.IAFile;
			testFile.setParentFolder(this.m_object_id.getParentFolder() + "test/");
			testFile.setFileName(elem.getAttribute("generateClass") + "0001.xml");
			dev.Api.GetIAFileDetails(testFile, function(response)
			{
				var objs = dev.sqldo.IAFile.readElementChildren(response);
				if (objs.length !== 0)
				{
					var testContents = objs[0].getFileContents();
					this.testObject = dev.Statics.xmlStringToDoc(testContents);
				} else
				{
					this.testObject = null;                     // this is ok
				}
				this.isNewObject = false;
				this.loadDataIntoForm();

				// Ensure that nothing is selected in the statement table, and clear out the statement form
				this.currentStmt = null;
				this.stmtTable.getSelectionModel().resetSelection();
				this.clearStatement();
				this.resetDirty();
			}, this);
		},

		/** This handles loading our GUI form fields based on the information contained
		  * in our data object.
		  */
		loadDataIntoForm : function()
		{
			var root = this.dataObject.documentElement;

			// Load the simple fields
			this.GenerateClassField.setValue(root.getAttribute("generateClass"));
			this.PackageField.setValue(root.getAttribute("package"));

			// Load our child vector table:
			this.loadChildVectorTable();

			// Load our list of sql statements
			this.loadStatementTable();

			// Load any tests that we have
			this.loadTestsTable();
		},
		loadStatementTable : function()
		{
			var root = this.dataObject.documentElement;
			var rowData = [];
			for (var i = 0, l = root.childNodes.length; i < l; i++)
			{
				var node = root.childNodes[i];
				if (node.nodeName === "SqlStatement") {
					rowData.push([node.getAttribute("methodName"), node.getAttribute("methodType"), node.getAttribute("target")]);
				}
			}
			this.stmtTable.getTableModel().setData(rowData);
		},
		loadChildVectorTable : function()
		{
			var root = this.dataObject.documentElement;
			var rowData = [];
			for (var i = 0, l = root.childNodes.length; i < l; i++)
			{
				var node = root.childNodes[i];
				if (node.nodeName === "ChildVector") {
					rowData.push([node.getAttribute("name"), node.getAttribute("type")]);
				}
			}
			this.childTable.getTableModel().setData(rowData);
		},
		pullChildVectorTable : function()
		{
			// First remove all child vector nodes from our xml document:
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			for (var i = 0; i < root.childNodes.length; i++)
			{                                             // length needs to be recalculated
				var node = root.childNodes[i];
				if (node.nodeName === "ChildVector")
				{
					// Remove this node.
					root.removeChild(node);
					i--;                                        // adjust loop count for removed node.
				}
			}

			// Add the new child nodes based on what is in the child vector table:
			var childModel = this.childTable.getTableModel();
			for (var i = 0, l = childModel.getRowCount(); i < l; i++)
			{
				var childNode = doc.createElement("ChildVector");
				root.appendChild(childNode);
				childNode.setAttribute("name", childModel.getValue(0, i));
				childNode.setAttribute("type", childModel.getValue(1, i));
			}
		},
		loadTestsTable : function()
		{
			if (this.testObject === undefined || this.testObject === null)
			{
				return;                                      // nothing to do
			}
			var root = this.testObject.documentElement;
			var rowData = [];
			for (var i = 0, l = root.childNodes.length; i < l; i++)
			{
				var node = root.childNodes[i];
				if (node.nodeName === "Test") {
					rowData.push([node.getAttribute("name"), node.getAttribute("method"), node.getAttribute("group")]);
				}
			}
			this.testTable.getTableModel().setData(rowData);
		},

		/** This handles pulling data from GUI form fields and loading their values
		  * back into our data object.
		  */
		pullDataFromForm : function()
		{
			if (this.currentStmt !== null) {
				// Save whatever is in the form back to the current statement before

				// doing the save here.
				this.pullOneStatement(this.currentStmt);
			}
			this.pullChildVectorTable();
			var elem = this.dataObject.documentElement;
			elem.setAttribute("generateClass", this.GenerateClassField.getValue());
			elem.setAttribute("package", this.PackageField.getValue());
		},

		addSqlStatement : function()
		{
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			var stmtNode = doc.createElement("SqlStatement");
			root.appendChild(stmtNode);
			stmtNode.setAttribute("methodName", "newSqlStatement");
			stmtNode.setAttribute("methodType", "SELECTTOXML");
			stmtNode.setAttribute("target", "odbc");
			var commentNode = doc.createElement("Comment");
			stmtNode.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, "Put a good description here - it gets copied into generated comments.");
			var sqlNode = doc.createElement("Sql");
			stmtNode.appendChild(sqlNode);
			dev.Statics.xmlSetText(sqlNode, "-- Your SQL Statement goes here");

			// re-load our statement table:
			this.loadStatementTable();

			// Select the last statement in the table:
			this.stmtTable.getSelectionModel().resetSelection();
			var lastRow = this.stmtTable.getTableModel().getRowCount() - 1;
			this.stmtTable.getSelectionModel().setSelectionInterval(lastRow, lastRow);
		},

		deleteSqlStatement : function()
		{
			var smodel = this.stmtTable.getSelectionModel();
			if (smodel.isSelectionEmpty())
			{
				return;                                      // nothing selected.  bail out.
			}
			var root = this.dataObject.documentElement;

			// Run the table selection and remove the named nodes from the xml
			var tmodel = this.stmtTable.getTableModel();
			smodel.iterateSelection(function(index)
			{
				var stmtName = tmodel.getValue(0, index);
				var sqlNode = dev.Statics.xmlFindChildWithAttr(root, "SqlStatement", "methodName", stmtName);
				if (sqlNode !== null) {
					root.removeChild(sqlNode);
				}
			});

			// One of the ones that was just deleted was the current selection, don't pull it
			this.currentStmt = null;

			// re-load our statement table:
			this.loadStatementTable();
			this.stmtTable.getSelectionModel().resetSelection();
			this.clearStatement();
		},

		duplicateSqlStatement : function()
		{
			var smodel = this.stmtTable.getSelectionModel();
			if (smodel.isSelectionEmpty())
			{
				return;                                      // nothing selected.  bail out.
			}
			var root = this.dataObject.documentElement;

			// Run the table selection and remove the named nodes from the xml
			var tmodel = this.stmtTable.getTableModel();
			smodel.iterateSelection(function(index)
			{
				var stmtName = tmodel.getValue(0, index);
				var sqlNode = dev.Statics.xmlFindChildWithAttr(root, "SqlStatement", "methodName", stmtName);
				if (sqlNode !== null) {
					var dupNode = sqlNode.cloneNode(true);
					dupNode.setAttribute("methodName", stmtName + "_copy");
					root.appendChild(dupNode);
				}
			});

			// re-load our statement table:
			this.loadStatementTable();

			// Select the last statement in the table:
			this.stmtTable.getSelectionModel().resetSelection();
			var lastRow = this.stmtTable.getTableModel().getRowCount() - 1;
			this.stmtTable.getSelectionModel().setSelectionInterval(lastRow, lastRow);
		},

		createCrudStatements : function()
		{
			var winTitle = "Table name";
			var winLabel = "Enter table name for CRUD Statements";
			var winIcon = "dev/icon/64x64/shadow/code_c.png";
			var dialog = new dev.SingleTextEntryDialog(winTitle, winIcon, winLabel);
			dialog.addOkEventListener("execute", function() {
				this.generateCrudStatements( dialog.getTextValue() );
			}, this);
			dialog.open();
		},

		generateCrudStatements : function(tableName)
		{
			// Set up the SQLStatement object that is used by the ExecuteGenericSQL Api.
			var sqlDO = new dev.sqldo.SQLStatement();
			sqlDO.setSql( "select top 1 * from " + tableName);
			sqlDO.setHostDB("lds");

			// Now send our sql test group to the server for processing:
			dev.Api.ExecuteGenericSQL(sqlDO, function(response)
			{
				// Walk the results for metadata and column rows
				var dt =
				{
					0 : "WLONGVARCHAR",
					1 : "WVARCHAR",
					2 : "WCHAR",
					3 : "BIT",
					4 : "BYTEINT",
					5 : "BIGINT",
					6 : "LONGVARBINARY",
					7 : "VARBINARY",
					8 : "BINARY",
					9 : "LONGVARCHAR",
					11 : "CHAR",
					12 : "NUMERIC",
					13 : "DECIMAL",
					14 : "INTEGER",
					15 : "SMALLINT",
					16 : "FLOAT",
					17 : "REAL",
					18 : "DOUBLE",
					19 : "DATE",
					20 : "TIME",
					21 : "TIMESTAMP",
					22 : "VARCHAR"
				};

				// Find the metadata node and read the metadata
				var metaNode = dev.Statics.xmlFindChild(response, "MetaData");
				var colNames = [];
				if (metaNode !== null)
				{
					var metaRowData = [];
					for (var i = 0, l = metaNode.childNodes.length; i < l; i++)
					{
						var node = metaNode.childNodes[i];
						if (node.nodeName === "Column")
						{
							metaRowData.push([
								node.getAttribute("position"),
								node.getAttribute("name"),
								dt[Number(node.getAttribute("dbtype")) + 10]
							]);
							colNames.push(node.getAttribute("name"));
						}
					}
				}

				this.generateInsertSql( tableName, metaRowData );
				this.generateUpdateSql( tableName, metaRowData );
				this.generateDeleteByIdSql( tableName, metaRowData );
				this.generateSelectIdentitySql( tableName, metaRowData );
				this.generateSelectAllSql( tableName, metaRowData );
				this.generateSelectByIdSql( tableName, metaRowData );

				this.loadStatementTable();
				this.stmtTable.getSelectionModel().resetSelection();
				this.clearStatement();

			}, this);
		},

		getUniqueName : function( root, prefix )
		{
			var counter = 1;
			do {
				var sqlNode = dev.Statics.xmlFindChildWithAttr(root, "SqlStatement",
					"methodName", prefix);
				if(sqlNode === null){
					return prefix;
				}
				prefix = prefix + counter;
				counter++;
			} while(sqlNode !== null);

		},

		generateInsertSql : function(tableName, metaRowData)
		{
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			var stmt = doc.createElement("SqlStatement");
			root.appendChild(stmt);
			stmt.setAttribute("methodName", this.getUniqueName(root, "insert"));
			stmt.setAttribute("methodType", "INSERT");
			stmt.setAttribute("target", "odbc");
			var commentNode = doc.createElement("Comment");
			stmt.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, "Inserts a single row into the table " + tableName);
			var sql = doc.createElement("Sql");
			stmt.appendChild(sql);

			var sqlText = "insert into " + tableName + "(\n    ";
			var valuesText = "values (\n    ";
			for(var i = 0, l = metaRowData.length; i < l; i++){
				sqlText += "[" + metaRowData[i][1] + "]";
				valuesText += "?";

				if(i < (l-1)){
					sqlText += ", ";
					valuesText += ", ";
				}

				if( (i+1) % 3 == 0){
					sqlText += "\n    ";
					valuesText += "\n    ";
				}
			}
			dev.Statics.xmlSetText(sql, sqlText + ")\n" + valuesText + ")\n" );

			// Next, create new Input fields based on the results metadata
			for (var i = 0, l = metaRowData.length; i < l; i++)
			{
				var oNode = doc.createElement("Input");
				stmt.appendChild(oNode);
				oNode.setAttribute("name", this.mangleFieldName(metaRowData[i][1]));
				oNode.setAttribute("type", this.translateType(metaRowData[i][2]));
			}

		},

		generateUpdateSql : function(tableName, metaRowData)
		{
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			var stmt = doc.createElement("SqlStatement");
			root.appendChild(stmt);
			stmt.setAttribute("methodName", this.getUniqueName(root, "update"));
			stmt.setAttribute("methodType", "UPDATE");
			stmt.setAttribute("target", "odbc");
			var commentNode = doc.createElement("Comment");
			stmt.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, "Updates a single row by Id in the table " + tableName);
			var sql = doc.createElement("Sql");
			stmt.appendChild(sql);

			var sqlText = "update " + tableName + " set\n";
			for(var i = 0, l = metaRowData.length; i < l; i++){
				if(metaRowData[i][1] === "Id") continue;
				sqlText += "    [" + metaRowData[i][1] + "] = ?";

				if(i < (l-1)){
					sqlText += ",\n";
				} else {
					sqlText += "\n";
				}
			}
			dev.Statics.xmlSetText(sql, sqlText + "where Id = ?\n" );

			// Next, create new Input fields based on the results metadata
			for (var i = 0, l = metaRowData.length; i < l; i++)
			{
				if(metaRowData[i][1] === "Id") continue;
				var oNode = doc.createElement("Input");
				stmt.appendChild(oNode);
				oNode.setAttribute("name", this.mangleFieldName(metaRowData[i][1]));
				oNode.setAttribute("type", this.translateType(metaRowData[i][2]));
			}
			// Add in the Id field
			var oNode = doc.createElement("Input");
			stmt.appendChild(oNode);
			oNode.setAttribute("name", "Id");
			oNode.setAttribute("type", "int");

		},

		generateDeleteByIdSql: function(tableName, metaRowData)
		{
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			var stmt = doc.createElement("SqlStatement");
			root.appendChild(stmt);
			stmt.setAttribute("methodName", this.getUniqueName(root, "deleteById"));
			stmt.setAttribute("methodType", "DELETE");
			stmt.setAttribute("target", "odbc");
			var commentNode = doc.createElement("Comment");
			stmt.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, "Removes a single row by Id from the table " + tableName);
			var sql = doc.createElement("Sql");
			stmt.appendChild(sql);

			var sqlText = "delete from " + tableName + " where Id = ?\n";
			dev.Statics.xmlSetText(sql, sqlText);

			// Add in the Id field
			var oNode = doc.createElement("Input");
			stmt.appendChild(oNode);
			oNode.setAttribute("name", "Id");
			oNode.setAttribute("type", "int");

		},

		generateSelectIdentitySql: function(tableName, metaRowData)
		{
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			var stmt = doc.createElement("SqlStatement");
			root.appendChild(stmt);
			stmt.setAttribute("methodName", this.getUniqueName(root, "selectIdentity"));
			stmt.setAttribute("methodType", "SELECTTOXML");
			stmt.setAttribute("target", "odbc");
			var commentNode = doc.createElement("Comment");
			stmt.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, "Retrieves the Id of the last inserted record.");
			var sql = doc.createElement("Sql");
			stmt.appendChild(sql);

			dev.Statics.xmlSetText(sql, "select @@IDENTITY as Id\n");

			// Add in the Id field
			var oNode = doc.createElement("Output");
			stmt.appendChild(oNode);
			oNode.setAttribute("name", "Id");
			oNode.setAttribute("type", "int");

		},

		generateSelectAllSql: function(tableName, metaRowData)
		{
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			var stmt = doc.createElement("SqlStatement");
			root.appendChild(stmt);
			stmt.setAttribute("methodName", this.getUniqueName(root, "selectAll"));
			stmt.setAttribute("methodType", "SELECTTOXML");
			stmt.setAttribute("target", "odbc");
			var commentNode = doc.createElement("Comment");
			stmt.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, "Retrieves all rows from the table " + tableName);
			var sql = doc.createElement("Sql");
			stmt.appendChild(sql);

			var sqlText = "select ";
			for(var i = 0, l = metaRowData.length; i < l; i++){
				sqlText += "[" + metaRowData[i][1] + "]";

				if(i < (l-1)){
					sqlText += ", ";
				}

				if( (i+1) % 3 == 0){
					sqlText += "\n    ";
				}
			}
			dev.Statics.xmlSetText(sql, sqlText + "\nfrom " + tableName + "\norder by Id\n" );

			// Next, create new Input fields based on the results metadata
			for (var i = 0, l = metaRowData.length; i < l; i++)
			{
				var oNode = doc.createElement("Output");
				stmt.appendChild(oNode);
				oNode.setAttribute("name", this.mangleFieldName(metaRowData[i][1]));
				oNode.setAttribute("type", this.translateType(metaRowData[i][2]));
			}

		},

		generateSelectByIdSql: function(tableName, metaRowData)
		{
			var root = this.dataObject.documentElement;
			var doc = root.ownerDocument;
			var stmt = doc.createElement("SqlStatement");
			root.appendChild(stmt);
			stmt.setAttribute("methodName", this.getUniqueName(root, "selectById"));
			stmt.setAttribute("methodType", "SELECTTOXML");
			stmt.setAttribute("target", "odbc");
			var commentNode = doc.createElement("Comment");
			stmt.appendChild(commentNode);
			dev.Statics.xmlSetText(commentNode, "Retrieves a single row by Id from the table " + tableName);
			var sql = doc.createElement("Sql");
			stmt.appendChild(sql);

			var sqlText = "select ";
			for(var i = 0, l = metaRowData.length; i < l; i++){
				sqlText += "[" + metaRowData[i][1] + "]";

				if(i < (l-1)){
					sqlText += ", ";
				}

				if( (i+1) % 3 == 0){
					sqlText += "\n    ";
				}
			}
			dev.Statics.xmlSetText(sql, sqlText + "\nfrom " + tableName + "\nwhere Id = ?\n" );

			// Next, create new Input fields based on the results metadata
			for (var i = 0, l = metaRowData.length; i < l; i++)
			{
				var oNode = doc.createElement("Output");
				stmt.appendChild(oNode);
				oNode.setAttribute("name", this.mangleFieldName(metaRowData[i][1]));
				oNode.setAttribute("type", this.translateType(metaRowData[i][2]));
			}

			// Add in the Id field
			var oNode = doc.createElement("Input");
			stmt.appendChild(oNode);
			oNode.setAttribute("name", "Id");
			oNode.setAttribute("type", "int");

		},

		/** Clears out all of the fields on the editing form - use this when the selection goes
		  * to something empty.
		  */
		clearStatement : function()
		{
			this.StatementNameField.setValue("");
			dev.Statics.setDropDownByValue(this.methodTypeField, "SELECTTOXML");
			dev.Statics.setDropDownByValue(this.methodTargetField, "odbc");
			this.DescriptionField.setValue("");
			this.stmtField.setValue("");
			var rowData = [];
			this.inputOutputTable.getTableModel().setData(rowData);
			this.stmtMetaTable.getTableModel().setData(rowData);
			this.stmtResultsTable.getTableModel().setData(rowData);
		},
		testChange : function(e)
		{
			if (this.currentTest !== null) {
				// Save whatever is in the form back to the current statement before

				// switching to the next table row.
				this.pullOneTest(this.currentTest);
			}

			// Find the new statement based on the table selection:

			//var row = this.stmtTable.getFocusedRow();
			var row = this.testStandardTable.getFirstSelected();
			if (row !== null)
			{
				var testName = this.testTable.getTableModel().getValue(0, row);
				var resetDirtyFlag = !this.isDirty;
				this.currentTest = dev.Statics.xmlFindChildWithAttr(this.testObject.documentElement, "Test", "name", testName);
				if (this.currentTest) {
					this.loadOneTest(this.currentTest);
				}
				if (resetDirtyFlag) {
					// Our dirty flag was not set before we did the load fields.

					// turn it back off again.
					this.resetDirty();
				}
			}
		},
		loadOneTest : function(testNode)
		{
			// Load the input table
			this.loadTestInputTable(testNode);

			// Load the saved results table
			this.loadTestSavedResults(testNode);
		},
		loadTestInputTable : function(testNode)
		{
			var inputNode = dev.Statics.xmlFindChild(testNode, "Input");
			if (inputNode === null)return;
                                                 // nothing to do
			var doNode = dev.Statics.xmlFindChild(inputNode, testNode.parentNode.getAttribute("do"));
			if (doNode === null)return;
                                                 // nothing to do

			// Find the statement that goes with this test so that we can determine which

			// of the input fields we should list
			var targetStmt = dev.Statics.xmlFindChildWithAttr(this.dataObject.documentElement, "SqlStatement", "methodName", testNode.getAttribute("method"));
			if (targetStmt == null)return;
                                                 // nothing to do
			var rowData = [];
			for (var i = 0, l = targetStmt.childNodes.length; i < l; i++)
			{
				var node = targetStmt.childNodes[i];
				if (node.nodeName === "Input")
				{
					// This is an input node that we should use.  Find it's value in the doNode.
					var fieldName = node.getAttribute("name");
					var fieldType = node.getAttribute("type");
					rowData.push([fieldName, fieldType, this.getTestInputValue(fieldName, fieldType, doNode)]);
				}
			}
			this.testInputTable.getTableModel().setData(rowData);
		},
		loadTestSavedResults : function(testNode) {
		},
		getTestInputValue : function(fieldName, fieldType, doNode) {
			if (fieldType === "base64" || fieldType === "bin") {
				// We have to read the data out of a sub-node and base64-decode it.
				return dev.Statics.xmlGetBase64(dev.Statics.xmlFindChild(doNode, fieldName));
			} else {
				// We can read the value directly from the attribute on the given doNode
				return doNode.getAttribute(fieldName);
			}
		},
		setTestInputValue : function(fieldName, fieldType, doNode, dataValue) {
			if (fieldType === "base64" || fieldType === "bin")
			{
				// We have to write the data out into a sub-node and base64-encode it.
				var childNode = dev.Statics.xmlFindChild(doNode, fieldName);
				if (childNode === null)
				{
					childNode = doNode.ownerDocument.createElement(fieldName);
					doNode.appendChild(childNode);
				}
				dev.Statics.xmlSetBase64(childNode, dataValue);
			} else
			{
				// We can set the value directly as an attribute of doNode
				doNode.setAttribute(fieldName, dataValue);
			}
		},
		addTest : function() {
		},
		deleteTest : function() {
		},
		pullOneTest : function(testNode)
		{
			// Clean out all children of the given node and re-build it from scratch:
			while (testNode.childNodes.length != 0)testNode.removeChild(testNode.childNodes[0]);

			var doc = testNode.ownerDocument;
			var inputNode = doc.createElement("Input");
			testNode.appendChild(inputNode);
			this.pullTestInputFields(testNode, inputNode);
			var outputNode = doc.createElement("Output");
			testNode.appendChild(outputNode);
			this.pullTestOutputFields(testNode, outputNode);
			var resultsNode = doc.createElement("Results");
			testNode.appendChild(resultsNode);
			resultsNode.setAttribute("success", "false");
			resultsNode.setAttribute("savedResults", "0");
			resultsNode.setAttribute("liveResults", "0");
		},
		pullTestInputFields : function(testNode, inputNode)
		{
			var doNode = inputNode.ownerDocument.createElement(testNode.parentNode.getAttribute("do"));
			inputNode.appendChild(doNode);
			var tm = this.testInputTable.getTableModel();
			for (var i = 0, l = tm.getRowCount(); i < l; i++)
			{
				var fieldName = tm.getValue(0, i);
				var fieldType = tm.getValue(1, i);
				var fieldData = tm.getValue(2, i);
				this.setTestInputValue(fieldName, fieldType, doNode, fieldData);
			}
		},
		pullTestOutputFields : function(testNode, outputNode) {
		},

		/*

		 pullOneStatement : function(stmtNode){
		  // Clean out all children of the given node and re-build it from scratch:
		  while( stmtNode.childNodes.length != 0) stmtNode.removeChild( stmtNode.childNodes[ 0 ] );
		  stmtNode.setAttribute( "methodName", this.StatementNameField.getValue() );
		  stmtNode.setAttribute( "methodType", this.methodTypeField.getSelection()[0].getModel() );
		  stmtNode.setAttribute( "target",     this.methodTargetField.getSelection()[0].getModel() );
		  var doc = stmtNode.ownerDocument;

		  var commentNode = doc.createElement( "Comment" );
		  stmtNode.appendChild( commentNode );
		  dev.Statics.xmlSetText( commentNode, this.DescriptionField.getValue() );

		  var sqlNode = doc.createElement( "Sql" );
		  stmtNode.appendChild( sqlNode );
		  dev.Statics.xmlSetText( sqlNode, this.stmtField.getValue());

		  var ioModel = this.inputOutputTable.getTableModel();
		  for( var i = 0, l = ioModel.getRowCount(); i < l; i++){
		   var ioNode = doc.createElement( ioModel.getValue( 1, i ) );
		   stmtNode.appendChild( ioNode );
		   ioNode.setAttribute("name", ioModel.getValue( 0, i ) );
		   var type = ioModel.getValue(2, i);
		   if(type && type.length !== 0){
		    ioNode.setAttribute("type", type );
		   } else {
		    ioNode.setAttribute("type", "twine" );
		   }
		  }
		 },
		*/

		/** This handles verifying all of our form fields prior to saving the
		  * record back to the server.
		  */
		verifyFields : function() {
			// Do all verification required here:

			// If everything is ok, return 0
			return 0;
		},

		/** This handles the calls required to save our dataObject back to the
		  * server.
		  */
		doSaveToServer : function()
		{
			if (this.verifyFields() === -1)
			{
				return;                                      // Don't save an invalid object
			}
			this.pullDataFromForm();
			var xmlString = dev.Statics.xmlDocToString(this.dataObject);
			var xmlStringTests = null;
			if (this.testObject) {
				xmlStringTests = dev.Statics.xmlDocToString(this.testObject);
			}
			if (this.isNewObject === true)
			{
				this.m_object_id = new dev.sqldo.IAFile;
				this.m_object_id.setParentFolder("../" + this.PackageField.getValue() + "/");
				this.m_object_id.setFileName(this.GenerateClassField.getValue() + ".sql.xml");
				this.m_object_id.setFileContents(xmlString);
				dev.Api.SaveIAFile(this.m_object_id, function(response)
				{
					// pick up any new information here.
					this.isNewObject = false;

					// Updates our tab name, and the overview name
					this.resetTabName(this.m_object_id.getFileName());
					this.resetDirty();

					// Remember to add the new guy to the tree:
					var app = qx.core.Init.getApplication();
					var devNode = app.findNode(app.treeRoot, "Development");
					if (devNode !== null)
					{
						var splits = this.PackageField.getValue().split("/");
						var logicNode = app.findNode(devNode, splits[splits.length - 1]);
						if (logicNode !== null)
						{
							app.tree.resetSelection();
							app.createAnimatedTreeItem(logicNode, this.m_object_id, this.m_object_id.getFileName(), "dev/icon/16x16/plain/data_scroll.png", dev.dataobj.DevTreeNodes.editObject);
						}
					}

					// Also Save our Tests file
					if (xmlStringTests)
					{
						var testIAFile = new dev.sqldo.IAFile;
						testIAFile.setParentFolder("../" + this.PackageField.getValue() + "/test/");
						testIAFile.setFileName(this.GenerateClassField.getValue() + "0001.xml");
						testIAFile.setFileContents(xmlStringTests);
						dev.Api.SaveIAFile(testIAFile, function(response)
						{
							// nothing to do.
						}, this);
					}
				}, this);
			} else
			{
				this.m_object_id.setParentFolder("../" + this.PackageField.getValue() + "/");
				this.m_object_id.setFileName(this.GenerateClassField.getValue() + ".sql.xml");
				this.m_object_id.setFileContents(xmlString);
				dev.Api.SaveIAFile(this.m_object_id, function(response)
				{
					// Updates our tab name, and the overview name
					this.resetTabName(this.m_object_id.getFileName());
					this.resetDirty();

					// Also Save our Tests file
					if (xmlStringTests)
					{
						var testIAFile = new dev.sqldo.IAFile;
						testIAFile.setParentFolder("../" + this.PackageField.getValue() + "/test/");
						testIAFile.setFileName(this.GenerateClassField.getValue() + "0001.xml");
						testIAFile.setFileContents(xmlStringTests);
						dev.Api.SaveIAFile(testIAFile, function(response)
						{
							// nothing to do.
						}, this);
					}
				}, this);
			}
		},
		loadSqlStatement : function()
		{
			var sql = qx.lang.String.trimRight(this.stmtField.getValue());
			if (sql === null || sql.length === 0)
			{
				// Nothing to do.
				dev.Statics.doAlert("Please enter a SQL Statement first.");
				return;
			}

			// Set up the SQLStatement object that is used by the ExecuteGenericSQL Api.
			var sqlDO = new dev.sqldo.SQLStatement();
			sqlDO.setSql(this.stmtField.getValue());

			// Translate the Target value into something that the ExecuteGenericSQL Api is expecting:

			// lds or Director-Config
			var target = dev.Statics.getDDSelectedValue(this.methodTargetField);
			if (target === "odbc") {
				sqlDO.setHostDB("lds");
			} else if (target === "sqldb") {
				sqlDO.setHostDB("Director-Config");
			} else
			{
				sqlDO.setHostDB("lds");  // Default to lds if we don't recognize the target.
			}

			// Now send our sql test group to the server for processing:
			dev.Api.ExecuteGenericSQL(sqlDO, function(response)
			{
				// Walk the results for metadata and column rows
				var dt =
				{
					0 : "WLONGVARCHAR",
					1 : "WVARCHAR",
					2 : "WCHAR",
					3 : "BIT",
					4 : "BYTEINT",
					5 : "BIGINT",
					6 : "LONGVARBINARY",
					7 : "VARBINARY",
					8 : "BINARY",
					9 : "LONGVARCHAR",
					11 : "CHAR",
					12 : "NUMERIC",
					13 : "DECIMAL",
					14 : "INTEGER",
					15 : "SMALLINT",
					16 : "FLOAT",
					17 : "REAL",
					18 : "DOUBLE",
					19 : "DATE",
					20 : "TIME",
					21 : "TIMESTAMP",
					22 : "VARCHAR"
				};

				// Find the metadata node
				var metaNode = dev.Statics.xmlFindChild(response, "MetaData");
				var colNames = [];
				if (metaNode !== null)
				{
					if (qx.lang.String.startsWith(sql.toUpperCase(), "INSERT") || qx.lang.String.startsWith(sql.toUpperCase(), "UPDATE") || qx.lang.String.startsWith(sql.toUpperCase(), "DELETE"))
					{
						dev.Statics.doAlertGreen("Rows affected by this SQL Statement: " + metaNode.getAttribute("rows"));
						return;
					}
					var metaRowData = [];
					for (var i = 0, l = metaNode.childNodes.length; i < l; i++)
					{
						var node = metaNode.childNodes[i];
						if (node.nodeName === "Column")
						{
							metaRowData.push([node.getAttribute("position"), node.getAttribute("name"), dt[Number(node.getAttribute("dbtype")) + 10]]);
							colNames.push(node.getAttribute("name"));
						}
					}
					this.stmtMetaTable.getTableModel().setData(metaRowData);
				}

				// Reset the results table columns:
				var tableParent = this.stmtResultsTable.getLayoutParent();
				tableParent.remove(this.stmtResultsTable);
				dev.Statics.cleanupStandardTable(this.stmtResultsTable);
				this.stmtResultsTable = null;
				var resultsRowData = [];
				this.stmtResultsTable = dev.Statics.createStandardTable(colNames, resultsRowData);
				tableParent.add(this.stmtResultsTable, {
					flex : 1
				});

				// Ensure that all columns have a minimum width:
				var sizing = this.stmtResultsTable.getTableColumnModel().getBehavior();
				for (var i = 0, l = colNames.length; i < l; i++)
				{
					var hash = {

					};
					hash.width = "1*";
					hash.minWidth = 50;
					sizing.set(i, hash);
				}
				this.stmtResultsTable.getDataRowRenderer()._renderFont(new qx.bom.Font(12, ["monospace"]));

				// Find all o fthe row data:
				for (var i = 0, l = response.childNodes.length; i < l; i++)
				{
					var node = response.childNodes[i];
					if (node.nodeName === "Row")
					{
						var colData = [];
						for (var j = 0, k = node.childNodes.length; j < k; j++)
						{
							var node2 = node.childNodes[j];
							if (node2.nodeName === "Column") {
								colData.push(dev.Statics.xmlGetBase64(dev.Statics.xmlFindChild(node2, "value")));
							}
						}
						resultsRowData.push(colData);
					}
				}
				this.stmtResultsTable.getTableModel().setData(resultsRowData);

				// Switch to the results tab:
				var our_tab = dev.Statics.findQXParent(this.stmtResultsTable, qx.ui.tabview.Page);
				our_tab.getButton().execute();
			}, this);
		}
	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct : function()
	{
		this._disposeObjects("tabview", "dataObject", "m_object_id");
		dev.Statics.destroyExtraObjects(this);
	}
});
