/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating VerticalSplitPane layout entities.
 */
qx.Mixin.define("admin.utils.layout.VerticalSplitPane", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForVerticalSplitPane: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "VerticalSplitPane" );
			xmlNode.setAttribute( "leftsize", "10" );
			xmlNode.setAttribute( "rightsize", "10" );

			var topNode = xmlNodeParent.ownerDocument.createElement("VerticalSplitPaneTop");
			xmlNode.appendChild( topNode );

			var bottomNode = xmlNodeParent.ownerDocument.createElement( "VerticalSplitPaneBottom" );
			xmlNode.appendChild( bottomNode );

			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForVerticalSplitPane: function()
		{
			return [ ];
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForVerticalSplitPaneTop: function()
		{
			return [
				"Button",
				"FieldArea",
				"GroupBox",
				"HorizontalBoxLayout",
				"HorizontalSplitPane",
				"HtmlEmbed",
				"IFrame",
				"Label",
				"List",
				"Spacer",
				"StandardTable",
				"TextArea",
				"Tree",
				"TreeVirtual",
				"VerticalBoxLayout",
				"VerticalSplitPane",
			];
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForVerticalSplitPaneBottom: function()
		{
			return [
				"Button",
				"FieldArea",
				"GroupBox",
				"HorizontalBoxLayout",
				"HorizontalSplitPane",
				"HtmlEmbed",
				"IFrame",
				"Label",
				"List",
				"Spacer",
				"StandardTable",
				"TextArea",
				"Tree",
				"TreeVirtual",
				"VerticalBoxLayout",
				"VerticalSplitPane",
			];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForVerticalSplitPane: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.VerticalSplitPane.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "leftsize", "rightsize"
			] );
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForVerticalSplitPaneTop: function(treeNode, xmlNode)
		{
			this.clearSettingsPane(); // Nothing to edit for this node.
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForVerticalSplitPaneBottom: function(treeNode, xmlNode)
		{
			this.clearSettingsPane(); // Nothing to edit for this node.
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForVerticalSplitPane: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForVerticalSplitPane: function(xmlNode, testSettingsArray)
		{
			return;
		}


	}

});
