/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating GroupBox layout entities.
 */
qx.Mixin.define("admin.utils.layout.GroupBox", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForGroupBox: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "GroupBox" );
			xmlNode.setAttribute( "varName", "" );
			xmlNode.setAttribute( "legend", "Group Box Text Legend" );
			xmlNode.setAttribute( "flex", "1" );
			xmlNode.setAttribute( "isCheck", "false" );
			xmlNode.setAttribute( "isRadio", "false" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForGroupBox: function()
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
		editDetailsForGroupBox: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.GroupBox.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "legend", "flex", "isCheck", "isRadio"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForGroupBox: function()
		{
			return null;
		}


	}

});
