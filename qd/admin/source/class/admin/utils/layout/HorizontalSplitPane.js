/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating HorizontalSplitPane layout entities.
 */
qx.Mixin.define("admin.utils.layout.HorizontalSplitPane", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForHorizontalSplitPane: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "HorizontalSplitPane" );
			xmlNode.setAttribute( "varName", "" );
			xmlNode.setAttribute( "leftsize", "1" );
			xmlNode.setAttribute( "rightsize", "1" );

			var leftNode = xmlNodeParent.ownerDocument.createElement( "HorizontalSplitPaneLeft" );
			xmlNode.appendChild( leftNode );

			var rightNode = xmlNodeParent.ownerDocument.createElement( "HorizontalSplitPaneRight" );
			xmlNode.appendChild( rightNode );

			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForHorizontalSplitPane: function()
		{
			return [ ];
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForHorizontalSplitPaneRight: function()
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
		validChildrenForHorizontalSplitPaneLeft: function()
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
		editDetailsForHorizontalSplitPane: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.HorizontalSplitPane.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "leftsize", "rightsize"
			] );
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForHorizontalSplitPaneLeft: function(treeNode, xmlNode)
		{
			this.clearSettingsPane(); // Nothing to edit here.
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForHorizontalSplitPaneRight: function(treeNode, xmlNode)
		{
			this.clearSettingsPane(); // Nothing to edit here.
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForHorizontalSplitPane: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForHorizontalSplitPane: function(xmlNode, testSettingsArray)
		{
			return;
		}


	}

});
