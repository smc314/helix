/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the dev.screens.LayoutDesigner and defines everything
 * required to be known for manipulating SingleCheck layout entities.
 */
qx.Mixin.define("dev.screens.layout.SingleCheck", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForSingleCheck: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "SingleCheck" );
			xmlNode.setAttribute( "label1", "New Field:" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForSingleCheck: function()
		{
			return [ ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForSingleCheck: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.SingleCheck.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName1", "label1"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForSingleCheck: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForSingleCheck: function(xmlNode, testSettingsArray)
		{
			var varName1 = xmlNode.getAttribute("varName1");
			if(varName1){
				var setting1 = {
					varName : varName1,
					htmlid : "qx.ui.form.CheckBox." + varName1
				};
				testSettingsArray.push( setting1 );
			}

		}


	}

});
