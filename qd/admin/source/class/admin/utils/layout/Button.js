/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating Button layout entities.
 */
qx.Mixin.define("admin.utils.layout.Button", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForButton: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "Button" );
			xmlNode.setAttribute( "label", "Button Text" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForButton: function()
		{
			return [  ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForButton: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.Button.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "label"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForButton: function()
		{
			return null;
		}


	}

});
