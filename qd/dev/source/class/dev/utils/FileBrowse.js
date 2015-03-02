/* ************************************************************************

Copyright: 2008 - 2014 Hericus Software, LLC

License: MIT License

Authors:  Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/refresh.png)
#asset(dev/icon/64x64/shadow/document.png)
#asset(dev/icon/16x16/plain/table_row.png)
#asset(dev/icon/16x16/plain/document.png)
#asset(dev/icon/16x16/plain/folder_closed.png)
#asset(dev/icon/16x16/plain/document.png)
************************************************************************ */
/* ************************************************************************
************************************************************************ */
qx.Class.define("dev.utils.FileBrowse", {
	extend: dev.ObjectEdit,

	construct: function (objectId) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({ name: "FileBrowse.MainPage.xml", doc: null });

		this.base(arguments, objectId);
	},

	members: {

		/** This is where the subclasses will tell us which API functions to use,
		* which callbacks to use, which names to use, etc.
		*/
		setupNamesAndFunctions: function () {
			this.selectApiCall = dev.Api.GetIAFileDetails;
		},

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(dev.Statics.addEditorSubTab(this.tabview, "General", true));
		},

		/**
		  * This function is responsible for initializing our toolbar
		  *
		  * @param tb {var} TODOC
		  * @return {var} TODOC
		  */
		initializeToolbar : function(tb)
		{
			// Save/Cancel part
			var sc_part = new qx.ui.toolbar.Part;

			// Revert button
			dev.Statics.addToToolbarWithShortcut(sc_part, "dev/icon/16x16/plain/refresh.png",
				this.tr("Reload From Server"), this.doRevert, this, this, "Control-U", "Refresh");

			tb.add(sc_part);

			return tb;
		},

		/** This catches events from form fields that indicate a change in our
		 * dirty status.  We'll update the isDirty flag, and also update our
		 * tab label to indicate that we are dirty.
		 */
		fieldModified : function(e) {
		},

		formatXml : function(xml) {
			var xsltText = '<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">\
								<xsl:output method="xml" indent="yes" version="1.0"/>\
								<xsl:strip-space elements="*"/>\
								<xsl:template match="/">\
									<xsl:copy-of select="."/>\
								</xsl:template>\
							</xsl:stylesheet>';
			var xsltDoc = dev.Statics.xmlStringToDoc(xsltText);
			var xmlDoc = dev.Statics.xmlStringToDoc(xml);

			var xsltProcessor = new XSLTProcessor();
			xsltProcessor.importStylesheet(xsltDoc);
			var fragment = xsltProcessor.transformToDocument(xmlDoc);

			return dev.Statics.xmlDocToString(fragment);
		},

		/** This is the main page with the overall server summary
		*/
		createMainTab: function (tabPage) {
			var live = this.createOverviewLayout(tabPage,
				"File Browser", "dev/icon/64x64/shadow/document.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getFileName());

			this.addStatusHeading("Cursor Location");
			this.overview_pos = this.addStatusItem("Ln: 0 Col: 0", "dev/icon/16x16/plain/table_row.png");

			dev.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("FileBrowse.MainPage.xml"),
				live);

			var ruler = ".........1.........2.........3.........4.........5.........6.........7.........8";

			this.RulerLabel.setValue(ruler);
			this.RulerLabel.setFont(new qx.bom.Font(14, ["monospace"]));

			this.FileContentsField.setCursor("text");
			this.FileContentsField.setFont(new qx.bom.Font(14, ["monospace"]));
			this.FileContentsField.addListener("keyup", this.getLineNumber, this);
			this.FileContentsField.addListener("mouseup", this.getLineNumber, this);
		},

		getLineNumber : function () {
			var rows = this.FileContentsField.getValue().substr(0,this.FileContentsField.getTextSelectionStart()).split("\n");
			this.overview_pos.setLabel("Ln: " + rows.length + " Col: " + (rows[rows.length-1].length + 1));
		},

		/** This allows our subclasses to do something in the scenario where the
		* edit view is opened up for a brand new object.
		*/
		initializeNewObject: function () {
			this.isNewObject = true;
			this.dataObject = new dev.sqldo.IAFile();
			this.objectArray = [];

			this.dataObject.setFileName("NEW1");

			this.loadDataIntoForm();
		},

		getObjectDetails: function (response) {
			this.objectArray = dev.sqldo.IAFile.readElementChildren(response);
			if (this.objectArray.length === 0) {
				this.resetDirty();
				dev.Statics.doAlert("File " + this.m_object_id.getName1() + " was not found.");
				return;
			}
			this.dataObject = this.objectArray[0];

			this.loadDataIntoForm();
			this.resetDirty();
		},

		loadDataIntoForm: function () {
			dev.Statics.loadAllFields(this, this.dataObject);

			//if (qx.lang.String.startsWith(this.FileContentsField.getValue(), "<?xml") == true) {
			//	this.FileContentsField.setValue(this.formatXml(this.FileContentsField.getValue()));
			//}
		},

		pullDataFromForm: function () {
			dev.Statics.pullAllFields(this, this.dataObject);

		},

		verifyFields: function () {

		},

		doSaveToServer: function () {

		}

	},

	statics: {

		editObject: function (treeNode) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			if (obj instanceof dev.sqldo.IAFile) {
				var tab_page = app.addEditingTab(obj.getFileName());
				if (tab_page != null) {
					tab_page.setIcon("dev/icon/16x16/plain/document.png");
					tab_page.add(new dev.utils.FileBrowse(obj), { flex: 10 });
				}
			}
		},

		populateChildren : function (treeNode) {
			var app = qx.core.Init.getApplication();
			dev.Api.GetIAFileList(treeNode.helixObj, function (response) {
				var obj_list = dev.sqldo.IAFolder.readElementChildren(response);

				for (var i = 0, l = obj_list.length; i < l; i++) {
					var obj = obj_list[i];

					app.createTreeFolder2(treeNode, obj, obj.getFolderName(), "dev/icon/16x16/plain/folder_closed.png", dev.utils.FileBrowse.populateChildren);
				}

				obj_list = dev.sqldo.IAFile.readElementChildren(response);

				for (var i = 0, l = obj_list.length; i < l; i++) {
					var obj = obj_list[i];

					app.createTreeItem2(treeNode, obj, obj.getFileName(), "dev/icon/16x16/plain/document.png", dev.utils.FileBrowse.editObject);
				}
			}, this);
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
		dev.Statics.destroyExtraObjects(this);
	}

});
