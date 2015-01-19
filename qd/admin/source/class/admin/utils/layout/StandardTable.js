/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating StandardTable layout entities.
 */
qx.Mixin.define("admin.utils.layout.StandardTable", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForStandardTable: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "StandardTable" );
			xmlNode.setAttribute( "flex", "1" );

			var col1Node = xmlNodeParent.ownerDocument.createElement( "Column" );
			col1Node.setAttribute("title", "Column 1");
			col1Node.setAttribute("width", "1*");
			xmlNode.appendChild( col1Node );

			var col2Node = xmlNodeParent.ownerDocument.createElement( "Column" );
			col2Node.setAttribute("title", "Column 2");
			col2Node.setAttribute("width", "2*");
			xmlNode.appendChild( col2Node );

			var col3Node = xmlNodeParent.ownerDocument.createElement( "Column" );
			col3Node.setAttribute("title", "Column 3");
			col3Node.setAttribute("width", "3*");
			xmlNode.appendChild( col3Node );

			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForStandardTable: function()
		{
			return [ "Column" ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForStandardTable: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.StandardTable.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "flex"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForStandardTable: function()
		{
			return null;
		}


	}

});
