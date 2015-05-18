/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating HorizontalBoxLayout layout entities.
 */
qx.Mixin.define("admin.utils.layout.HorizontalBoxLayout", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForHorizontalBoxLayout: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "HorizontalBoxLayout" );
			xmlNode.setAttribute( "varName", "" );
			xmlNode.setAttribute( "spacing", "5" );
			xmlNode.setAttribute( "flex", "1" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForHorizontalBoxLayout: function()
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
		editDetailsForHorizontalBoxLayout: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.HorizontalBoxLayout.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "spacing", "flex"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForHorizontalBoxLayout: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForHorizontalBoxLayout: function(xmlNode, testSettingsArray)
		{
			return;
		}


	}

});
