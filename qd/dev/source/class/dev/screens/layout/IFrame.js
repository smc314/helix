/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the dev.screens.LayoutDesigner and defines everything
 * required to be known for manipulating IFrame layout entities.
 */
qx.Mixin.define("dev.screens.layout.IFrame", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForIFrame: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "IFrame" );
			xmlNode.setAttribute( "varName", "" );
			xmlNode.setAttribute( "flex", "1" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForIFrame: function()
		{
			return [ ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForIFrame: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.IFrame.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "flex"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForIFrame: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForIFrame : function(xmlNode, testSettingsArray)
		{
			return;
		}


	}

});
