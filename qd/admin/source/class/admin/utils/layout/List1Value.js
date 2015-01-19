/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating List1Value layout entities.
 */
qx.Mixin.define("admin.utils.layout.List1Value", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForList1Value: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "List1Value" );
			xmlNode.setAttribute( "label", "List Value Name" );
			xmlNode.setAttribute( "model", "ListValueInternalID" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForList1Value: function()
		{
			return [ ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForList1Value: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.List1Value.xml" );
			this.pushXmlToFields( xmlNode, [
				"label", "model"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForList1Value: function()
		{
			return null;
		}


	}

});
