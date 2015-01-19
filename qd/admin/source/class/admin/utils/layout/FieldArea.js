/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating FieldArea layout entities.
 */
qx.Mixin.define("admin.utils.layout.FieldArea", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForFieldArea: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "FieldArea" );
			xmlNode.setAttribute( "first", "80" );
			xmlNode.setAttribute( "second", "80" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForFieldArea: function()
		{
			return [
				"DoubleCheck2",
				"DoubleCheck",
				"DoubleField",
				"LongLabel",
				"QuadCheck",
				"RadioGroup2",
				"RadioGroup3",
				"RadioGroup4",
				"RadioGroup5",
				"SingleCheck",
				"SpanField"
			];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForFieldArea: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.FieldArea.xml" );
			this.pushXmlToFields( xmlNode, [
				"first", "second"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForFieldArea: function()
		{
			return null;
		}


	}

});
