/* ************************************************************************

   Copyright: 2014 Your Company, Inc.

   Authors:  You and your developers

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/carabiner.png)
#asset(dev/icon/16x16/plain/carabiner.png)
#asset(dev/icon/16x16/plain/about.png)
#asset(dev/icon/64x64/shadow/data_scroll.png)
#asset(dev/icon/16x16/plain/delete2.png)
#asset(dev/icon/16x16/plain/control_panel2.png)
************************************************************************ */
qx.Class.define("dev.screens.LayoutDesigner", {
	extend: dev.ObjectEdit,

	include: [
		dev.screens.layout.Button,
		dev.screens.layout.Column,
		dev.screens.layout.DoubleCheck2,
		dev.screens.layout.DoubleCheck,
		dev.screens.layout.DoubleField,
		dev.screens.layout.FieldArea,
		dev.screens.layout.GroupBox,
		dev.screens.layout.HorizontalBoxLayout,
		dev.screens.layout.HorizontalSplitPane,
		dev.screens.layout.HtmlEmbed,
		dev.screens.layout.IFrame,
		dev.screens.layout.Label,
		dev.screens.layout.List1Value,
		dev.screens.layout.List2Value,
		dev.screens.layout.List,
		dev.screens.layout.LongLabel,
		dev.screens.layout.QuadCheck,
		dev.screens.layout.RadioGroup2,
		dev.screens.layout.RadioGroup3,
		dev.screens.layout.RadioGroup4,
		dev.screens.layout.RadioGroup5,
		dev.screens.layout.SingleCheck,
		dev.screens.layout.Spacer,
		dev.screens.layout.SpanField,
		dev.screens.layout.StandardTable,
		dev.screens.layout.TextArea,
		dev.screens.layout.Tree,
		dev.screens.layout.TreeVirtual,
		dev.screens.layout.VerticalBoxLayout,
		dev.screens.layout.VerticalSplitPane
	],

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "LayoutDesigner.GeneralPage.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.DesignPage.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.TestSettingsPage.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.Button.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.Column.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.DoubleCheck2.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.DoubleCheck.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.DoubleField.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.FieldArea.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.GroupBox.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.HorizontalBoxLayout.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.HorizontalSplitPane.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.HtmlEmbed.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.IFrame.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.Label.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.List1Value.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.List2Value.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.List.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.LongLabel.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.QuadCheck.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.RadioGroup2.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.RadioGroup3.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.RadioGroup4.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.RadioGroup5.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.SingleCheck.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.Spacer.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.SpanField.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.StandardTable.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.TextArea.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.TreeVirtual.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.Tree.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.VerticalBoxLayout.xml", doc:null});
		this.dynamicLayouts.push({name: "LayoutDesigner.VerticalSplitPane.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {
		layoutElementNames : [
			"Button",
			"Column",
			"DoubleCheck2",
			"DoubleCheck",
			"DoubleField",
			"FieldArea",
			"GroupBox",
			"HorizontalBoxLayout",
			"HorizontalSplitPane",
			"HtmlEmbed",
			"IFrame",
			"Label",
			"List1Value",
			"List2Value",
			"List",
			"LongLabel",
			"QuadCheck",
			"RadioGroup2",
			"RadioGroup3",
			"RadioGroup4",
			"RadioGroup5",
			"SingleCheck",
			"Spacer",
			"SpanField",
			"StandardTable",
			"TextArea",
			"TreeVirtual",
			"Tree",
			"VerticalBoxLayout",
			"VerticalSplitPane"
		],

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = dev.Api.GetIAFileDetails;
		},

		/** our specific help url
		  */
		getHelpUrl: function() {
			return "/devdoc/html/namespaces.html";
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb); // Call the parent class first

			// Then add any other actions that you would like here:
			var part = new qx.ui.toolbar.Part;

			this.addMenuButton = new qx.ui.toolbar.MenuButton("Add", "dev/icon/16x16/plain/carabiner.png",
				this.getAddMenu() );
			this.addMenuButton.setToolTipText("Add a new layout element.");
			part.add( this.addMenuButton );
			this.addMenuButton.setEnabled(false); // create it disabled.

			dev.Statics.addToToolbarWithShortcut( part, "dev/icon/16x16/plain/carabiner.png",
				this.tr("Generate Test Settings"), this.genTestSettings, this, this, "Control-G",
				this.tr("Generate Test Settings") );

			tb.add(part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		getAddMenu: function() {
			if(this.addMenu){
				return this.addMenu; // we've already created it once.
			}

			this.addMenu = new qx.ui.menu.Menu();
			for(var i = 0, l = this.layoutElementNames.length; i < l; i++){
				this.addMenu.add( this.createAddMenuItem( this.layoutElementNames[ i ] ) );
			}

			return this.addMenu;
		},

		createAddMenuItem: function( xmlNodeName ) {
			var addButton = new qx.ui.menu.Button(xmlNodeName, "dev/icon/16x16/plain/about.png");
			addButton.xmlNodeName = xmlNodeName;
			addButton.editorThis = this;
			addButton.addListener("execute", function(e){
				var currentTreeNode = null;
				var selection = this.editorThis.layoutTree.getSelection();
				if(selection.length === 0){
					currentTreeNode = this.editorThis.layoutTree.getRoot();
				} else {
					currentTreeNode = selection[0];
				}
				var currentXmlNode = currentTreeNode.xmlNode;

				// Create the new XML Node
				var newXmlNode = null;
				if(this.editorThis[ "createXmlNodeFor" + this.xmlNodeName ]){
					newXmlNode = this.editorThis[ "createXmlNodeFor" + this.xmlNodeName ]( currentXmlNode );
				} else {
					newXmlNode = currentXmlNode.ownerDocument.createElement( this.xmlNodeName );
				}
				currentXmlNode.appendChild( newXmlNode );

				// Create the new tree node for the new xml node:
				var treeNode = new qx.ui.tree.TreeFolder( newXmlNode.nodeName );
				currentTreeNode.add( treeNode );

				// Tie them together
				treeNode.xmlNode = newXmlNode;
				treeNode.setOpen( true );
				this.editorThis.createRMCMenuForNode( newXmlNode, treeNode );

				// Create any children in the tree that are required
				this.editorThis.createTreeChildren( newXmlNode, treeNode );

				// Indicate that something has changed
				this.editorThis.fieldModified();

				// Re-render the layout to reflect the updates
				this.editorThis.renderDynamicLayout();
			});
			return addButton;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(dev.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createDesignTab(dev.Statics.addEditorSubTab(this.tabview, "Design", false));
			this.createTestSettingsTab(dev.Statics.addEditorSubTab(this.tabview, "Sample Test Settings", false));

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Layout Designer",
				"dev/icon/64x64/shadow/data_scroll.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getFileName() );

			this.addStatusHeading("General");
			this.addStatusHint("Use this editor to define the visual layout that your form should have.");

			dev.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("LayoutDesigner.GeneralPage.xml"),
				live );

			// Find the list of all data objects that we have and use that to populate
			// the drop-down on the form:


		},

		/** This is the design page.
		  */
		createDesignTab: function(tab_page)
		{
			dev.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("LayoutDesigner.DesignPage.xml"),
				tab_page );

			// Some fine tuning to the layout objects there:
			this.treePane.set({minWidth: 200, decorator: "main"});
			this.renderingPane.set({decorator: "main"});
			this.settingsPane.set({decorator: "main"});

			// Setup the tree and tree root
			this.layoutTree.setRootOpenClose(true);
			this.layoutTree.addListener("changeSelection", this.handleTreeSelection, this);
			this.layoutTree.setContextMenu( this.createTreeRMC() );

		},

		/** This is the test settings page.
		  */
		createTestSettingsTab: function(tab_page)
		{
			dev.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("LayoutDesigner.TestSettingsPage.xml"),
				tab_page );

			this.TestSettingsField.setCursor("text");
			this.TestSettingsField.setFont( new qx.bom.Font(14, ["monospace"]) );

		},

		createTreeRMC: function()
		{
			this.treeRMC = new qx.ui.menu.Menu();
			this.addStandardContextMenuItems( this.treeRMC );

			return this.treeRMC;
		},

		addStandardContextMenuItems : function( rmcMenu )
		{
			dev.Statics.addToRMCMenu(rmcMenu, "Delete Node",
				"dev/icon/16x16/plain/delete2.png", this.deleteTreeSelection, this );
		},

		deleteTreeSelection: function()
		{
			var currentTreeNode = null;
			var selection = this.layoutTree.getSelection();
			if(selection.length === 0){
				dev.Statics.doAlert("Nothing selected to delete");
				return;
			}

			currentTreeNode = selection[0];
			var currentXmlNode = currentTreeNode.xmlNode;

			// Remove the node from the tree
			currentTreeNode.getParent().remove( currentTreeNode );

			// Remove the node from the XML:
			currentXmlNode.parentNode.removeChild( currentXmlNode );

			// Reset the tree selection:
			this.layoutTree.resetSelection();

			// Clear the details editing section:
			this.clearSettingsPane();

			// Indicate that something has changed
			this.fieldModified();

			// Re-render the layout to reflect the updates
			this.renderDynamicLayout();
		},

		handleTreeSelection: function( e )
		{
			var data = e.getData();
			if(data.length === 0){
				return; // Nothing selected
			}

			var currentTreeNode = data[0];
			var currentXmlNode = currentTreeNode.xmlNode;
			var editDetailsFunction = "editDetailsFor" + currentXmlNode.nodeName;
			if( this[editDetailsFunction] ){
				this[editDetailsFunction]( currentTreeNode, currentXmlNode );
			} else {
				this.error("Missing edit details function: " + editDetailsFunction );
			}

			// Update the Add menu to display valid choices for the current selection:
			var addChildren = this.addMenu.getChildren();
			// Get the list of valid children of the current node:
			var validChildrenFunction = "validChildrenFor" + currentXmlNode.nodeName;
			if(this[validChildrenFunction] ){
				var validChildren = this[ validChildrenFunction ]();

				// Walk all of the add menu items:
				for(var i = 0, l = addChildren.length; i < l; i++){
					var addChild = addChildren[i];
					var found = false;
					for(var j = 0, k = validChildren.length; j < k; j++){
						if(validChildren[j] === addChild.getLabel()){
							addChild.setVisibility( "visible" );
							found = true;
						}
					}
					if(found === false){
						addChild.setVisibility( "excluded" );
					}
				}
			}

			// Enable the add button once something is selected:
			this.addMenuButton.setEnabled(true);


		},

		clearSettingsPane: function( )
		{
			// Set up an empty object to hold all of the variables generated by the
			// layout engine.  This way they won't conflict with our own object
			// variables.  Note - this object needs to be a qooxdoo object because
			// the layout engine expects to be able to use it for logging any errors
			// that it encounters.
			this.settingsVariableContainer = new qx.core.Object;

			// Remove all existing layout children in the render pane:
			if(this.settingsPane.getChildren().length !== 0){
				this.settingsPane.remove(this.settingsPane.getChildren()[0] );
			}

		},

		reRenderSettingsPane: function( layoutName )
		{
			this.clearSettingsPane();

			// Re-render the layout based on teh current xml document:
			dev.layout.LayoutEngine.renderLayout(this.settingsVariableContainer,
				this.getDynamicLayout( layoutName), this.settingsPane );
		},

		pushXmlToFields: function(xmlNode, attrList)
		{
			for(var i = 0, l = attrList.length; i < l; i++){
				var attrName = attrList[i];
				var attrValue = xmlNode.getAttribute( attrName );
				var fieldName = attrName + "Field";
				var formField = this.settingsVariableContainer[ fieldName ];
				if(formField === null || formField === undefined){
					this.debug("Unknown formField '" + formField + "'");
					continue; // skip this one
				}
				// Tie the xmlNode and attribute name to the form field so that
				// we can retrieve it later in call-backs.
				formField.xmlNode = xmlNode;
				formField.xmlNodeAttrName = attrName;
				formField.editorThis = this;
				if(formField instanceof qx.ui.form.CheckBox){
					formField.setValue( attrValue === "true" ? true : false );
					formField.addListener( "changeValue", function(e) {
						this.xmlNode.setAttribute( this.xmlNodeAttrName, this.getValue() ? "true" : "false" );
						this.editorThis.renderDynamicLayout();
						this.editorThis.fieldModified(e);
					});
				} else if(formField instanceof qx.ui.groupbox.CheckGroupBox){
					formField.setValue( attrValue === "true" ? true : false );
					formField.addListener( "changeValue", function(e) {
						this.xmlNode.setAttribute( this.xmlNodeAttrName, this.getValue() ? "true" : "false" );
						this.editorThis.renderDynamicLayout();
						this.editorThis.fieldModified(e);
					});
				} else if(formField instanceof qx.ui.form.SelectBox){
					dev.Statics.setDropDownByValue( formField, attrValue );
					formField.addListener("changeSelection", function(e){
						this.xmlNode.setAttribute( this.xmlNodeAttrName, this.getSelection()[0].getModel() );
						this.editorThis.renderDynamicLayout();
						this.editorThis.fieldModified(e);
					});
					if(attrValue === null || attrValue === undefined || attrValue.length === 0){
						dev.Statics.selectDropDownIndex( formField, 0 );
						xmlNode.setAttribute( attrName, formField.getSelection()[0].getModel() );
					}
				} else {
					// All others - treat like a text box:
					// formField.setLiveUpdate(true); // re-rendering the whole form on each update is slow.
					formField.setValue( attrValue );
					formField.addListener("changeValue", function(e){
						this.xmlNode.setAttribute( this.xmlNodeAttrName, this.getValue() );
						this.editorThis.renderDynamicLayout();
						this.editorThis.fieldModified(e);
					});
				}
			}
		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = true;
			this.dataObject = new dev.sqldo.IAFile();
			this.dataObject.setFileName("NewLayoutFile.MainPage.xml");
			this.dataObject.setParentFolder("../../../qd/dev/source/layouts/" );
			this.dataObject.setFileContents(
				"<VerticalBoxLayout spacing=\"0\" flex=\"1\">" +
				"<GroupBox legend=\"Sample GroupBox\" flex=\"1\">" +
				"</GroupBox>" +
				"</VerticalBoxLayout>"
			);

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = dev.sqldo.IAFile.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.isNewObject = false;
			this.loadDataIntoForm();
		},

		createRMCMenuForNode: function(xmlNode, treeNode)
		{
			var createMenuName = "rmcMenuFor" + xmlNode.nodeName;
			if(this[createMenuName]){
				var nodeContextMenu = this[createMenuName]();
				if(nodeContextMenu){
					treeNode.setContextMenu( nodeContextMenu );
				}
			}
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
			dev.Statics.loadAllFields(this, this.dataObject);

			this.dataXml = dev.Statics.xmlStringToDoc( this.dataObject.getFileContents() );
			this.xmlRoot = this.dataXml.documentElement;
			this.treeRoot = new qx.ui.tree.TreeFolder( this.xmlRoot.nodeName );
			this.treeRoot.setOpen(true);
			this.treeRoot.xmlNode = this.xmlRoot;
			this.layoutTree.setRoot( this.treeRoot );
			this.layoutTree.setHideRoot( false );
			this.createRMCMenuForNode( this.xmlRoot, this.treeRoot );
			this.createTreeChildren( this.xmlRoot, this.treeRoot );


			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

			// Once data is loaded, reset our dirty flag
			this.resetDirty();

			// Do the initial rendering
			this.renderDynamicLayout();

			this.clearSettingsPane();
		},

		renderDynamicLayout: function()
		{
			// Set up an empty object to hold all of the variables generated by the
			// layout engine.  This way they won't conflict with our own object
			// variables.  Note - this object needs to be a qooxdoo object because
			// the layout engine expects to be able to use it for logging any errors
			// that it encounters.
			this.renderVariableContainer = new qx.core.Object;

			// Remove all existing layout children in the render pane:
			if(this.renderingPane.getChildren().length !== 0){
				this.renderingPane.remove(this.renderingPane.getChildren()[0] );
			}

			// Re-render the layout based on the current xml document:
			dev.layout.LayoutEngine.renderLayout(this.renderVariableContainer, this.dataXml, this.renderingPane );
		},

		createTreeChildren: function(parentXml, parentTreeFolder)
		{
			for(var i = 0, l = parentXml.childNodes.length; i < l; i++){
				var xmlNode = parentXml.childNodes[i];
				if(xmlNode.nodeType !== 1){
					continue; // only process Element nodes
				}
				var treeNode = new qx.ui.tree.TreeFolder( xmlNode.nodeName );
				treeNode.xmlNode = xmlNode;
				treeNode.setOpen( true );
				parentTreeFolder.add( treeNode );
				this.createRMCMenuForNode( xmlNode, treeNode );

				// Handle all children of this node as well:
				this.createTreeChildren( xmlNode, treeNode );
			}
		},

		/** This will walk our tree and create a series of test settings that can be used
		 *  in an automated test of this form.
		 */
		genTestSettings : function() {
			var testSettings =
				"<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n" +
				"<HelixUITest>\n" +
				"\n"
			;
			var settingsPrefix = this.dataObject.getFileName().split('.')[0];

			// Walk our xml tree to pick up all of the settings we can find.
			var settingsArray = [];
			this.loadSettingsArray( this.xmlRoot, settingsArray );

			// Now take all of those settings and represent them in a way that makes it easy
			// for the developer to pick them up and copy them into their automated tests.

			// Give them the list of page objects first:
			testSettings +=
				"\t<!-- Settings Values for the Editor elements the user can manipulate on this form -->\n"
			;
			for(var i = 0, l = settingsArray.length; i < l; i++){
				var setting = settingsArray[ i ];
				testSettings +=
					"\t<Setting name=\"" + settingsPrefix + "." + setting.varName + ".EditFieldID\" " +
					"value=\"" + setting.htmlid + "\"/>\n" +
					"\t<Setting name=\"" + settingsPrefix + "." + setting.varName + ".DisplayFieldID\" " +
					"value=\"" + setting.htmlid + "\"/>\n" +
					"\n"
				;
			}

			// Now give them a list of placeholders for the data values
			testSettings +=
				"\t<!-- Input Data Values for the Editor elements the user can manipulate on this form -->\n"
			;
			for(var i = 0, l = settingsArray.length; i < l; i++){
				var setting = settingsArray[ i ];
				testSettings +=
					"\t<Setting name=\"" + settingsPrefix + "." + setting.varName + ".DataValue\" " +
					"value=\"Input Data Value Goes Here\"/>\n"
				;
			}

			// Now give them a list of fields as they would be laid out in a test:
			testSettings +=
				"\n" +
				"\t<!-- Sample set of fields as represented by this layout design -->\n" +
				"\t<Tab name=\"Tab Name Goes Here\">\n"
			;
			for(var i = 0, l = settingsArray.length; i < l; i++){
				var setting = settingsArray[ i ];
				testSettings +=
					"\t\t<Field name=\"" + setting.varName + "\" \n" +
					"\t\t\tvalue=\"${" + settingsPrefix + "." + setting.varName + ".DataValue}\" \n" +
					"\t\t\teditId=\"${" + settingsPrefix + "." + setting.varName + ".EditFieldID}\" \n" +
					"\t\t\tdisplayId=\"${" + settingsPrefix + "." + setting.varName + ".DisplayFieldID}\" \n" +
					"\t\t\ttype=\"" + setting.htmlid.split('.')[3] + "\" " +
					"/>\n"
				;
			}
			testSettings +=
				"\t</Tab>\n" +
				"\n"
			;

			testSettings +=
				"</HelixUITest>\n"

			this.TestSettingsField.setValue( testSettings );

		},

		loadSettingsArray : function( xmlNode, settingsArray) {
			// First load all of our own settings:
			var testSettingsFunction = "testSettingsFor" + xmlNode.nodeName;
			if( this[testSettingsFunction] ){
				this[testSettingsFunction]( xmlNode, settingsArray);
			} else {
				this.warn("Missing test settings function: " + testSettingsFunction);
			}

			// Now loop through our children
			for(var i = 0, l = xmlNode.childNodes.length; i < l; i++){
				if(xmlNode.childNodes[i].nodeType !== 1){
					continue; // only process Element nodes
				}
				this.loadSettingsArray( xmlNode.childNodes[i], settingsArray );
			}

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
			dev.Statics.pullAllFields(this, this.dataObject);

			this.dataObject.setFileContents( dev.Statics.xmlDocToString( this.dataXml ) );

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

		},

		/** This handles verifying all of our form fields prior to saving the
		  * record back to the server.
		  */
		verifyFields : function()
		{
			// Use the built-in verification to do as much work for us as possible:
			if( dev.Statics.verifyAllFields(this) === -1) return -1;

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
			if(this.isNewObject === true){
				dev.Api.SaveIAFile( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );
					this.resetDirty();

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getFileName() );

					// Remember to add the new guy to the tree:
					/*
					qx.core.Init.getApplication().addNewTreeItem( "Parent Tree Node",
						this.dataObject.getTName(), this.dataObject,
						"dev/icon/16x16/plain/control_panel2.png" );
					*/

				}, this);
			} else {
				dev.Api.SaveIAFile( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );
					this.resetDirty();

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getFileName() );

				}, this);
			}

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
		dev.Statics.destroyExtraObjects( this );
	}

});
