/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating RadioGroup4 layout entities.
 */
qx.Mixin.define("admin.utils.layout.RadioGroup4", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForRadioGroup4: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "RadioGroup4" );
			xmlNode.setAttribute( "groupName", "" );
			xmlNode.setAttribute( "varName1", "" );
			xmlNode.setAttribute( "label1", "First Radio Option" );
			xmlNode.setAttribute( "varName2", "" );
			xmlNode.setAttribute( "label2", "Second Radio Option" );
			xmlNode.setAttribute( "varName3", "" );
			xmlNode.setAttribute( "label3", "Third Radio Option" );
			xmlNode.setAttribute( "varName4", "" );
			xmlNode.setAttribute( "label4", "Fourth Radio Option" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForRadioGroup4: function()
		{
			return [ ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForRadioGroup4: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.RadioGroup4.xml" );
			this.pushXmlToFields( xmlNode, [
				"groupName",
				"varName1", "label1",
				"varName2", "label2",
				"varName3", "label3",
				"varName4", "label4"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForRadioGroup4: function()
		{
			return null;
		}


	}

});
