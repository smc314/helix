/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating DoubleField layout entities.
 */
qx.Mixin.define("admin.utils.layout.DoubleField", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForDoubleField: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "DoubleField" );
			xmlNode.setAttribute( "label1", "New Field:" );
			xmlNode.setAttribute( "type1", "TextField" );
			xmlNode.setAttribute( "label2", "New Field:" );
			xmlNode.setAttribute( "type2", "TextField" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForDoubleField: function()
		{
			return [ "List1Value", "List2Value" ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForDoubleField: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.DoubleField.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName1", "label1", "type1", "tooltip1", "verify1", "verify1type",
				"verify1min", "verify1max", "upper1", "required1",
				"varName2", "label2", "type2", "tooltip2", "verify2", "verify2type",
				"verify2min", "verify2max", "upper2", "required2"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForDoubleField: function()
		{
			return null;
		}


	}

});
