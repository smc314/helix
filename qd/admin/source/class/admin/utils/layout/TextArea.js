/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating TextArea layout entities.
 */
qx.Mixin.define("admin.utils.layout.TextArea", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForTextArea: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "TextArea" );
			xmlNode.setAttribute( "flex", "1" );
			xmlNode.setAttribute( "wrap", "true" );
			xmlNode.setAttribute( "allowGrowX", "true" );
			xmlNode.setAttribute( "allowGrowY", "true" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForTextArea: function()
		{
			return [ ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForTextArea: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.TextArea.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "flex", "wrap", "allowGrowX", "allowGrowY"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForTextArea: function()
		{
			return null;
		}


	}

});
