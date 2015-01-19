/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating QuadCheck layout entities.
 */
qx.Mixin.define("admin.utils.layout.QuadCheck", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForQuadCheck: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "QuadCheck" );
			xmlNode.setAttribute( "varName1", "checkVar1" );
			xmlNode.setAttribute( "label1", "True or False?" );
			xmlNode.setAttribute( "width1", "120" );
			xmlNode.setAttribute( "varName2", "checkVar2" );
			xmlNode.setAttribute( "label2", "True or False?" );
			xmlNode.setAttribute( "width2", "120" );
			xmlNode.setAttribute( "varName3", "checkVar3" );
			xmlNode.setAttribute( "label3", "True or False?" );
			xmlNode.setAttribute( "width3", "120" );
			xmlNode.setAttribute( "varName4", "checkVar4" );
			xmlNode.setAttribute( "label4", "True or False?" );
			xmlNode.setAttribute( "width4", "120" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForQuadCheck: function()
		{
			return [ ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForQuadCheck: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.QuadCheck.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName1", "label1", "width1",
				"varName2", "label2", "width2",
				"varName3", "label3", "width3",
				"varName4", "label4", "width4"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForQuadCheck: function()
		{
			return null;
		}


	}

});
