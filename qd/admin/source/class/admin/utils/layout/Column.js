/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating Column layout entities.
 */
qx.Mixin.define("admin.utils.layout.Column", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForColumn: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "Column" );
			xmlNode.setAttribute( "title", "Column Title" );
			xmlNode.setAttribute( "width", "1*" );
			xmlNode.setAttribute( "minWidth", "" );
			xmlNode.setAttribute( "maxWidth", "" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForColumn: function()
		{
			return [  ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForColumn: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.Column.xml" );
			this.pushXmlToFields( xmlNode, [
				"title", "width", "minWidth", "maxWidth"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForColumn: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForColumn: function(xmlNode, testSettingsArray)
		{
			return;
		}


	}

});
