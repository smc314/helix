/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating LongLabel layout entities.
 */
qx.Mixin.define("admin.utils.layout.LongLabel", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForLongLabel: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "LongLabel" );
			xmlNode.setAttribute( "varName", "" );
			xmlNode.setAttribute( "label", "Text for the long label" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForLongLabel: function()
		{
			return [ ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForLongLabel: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.LongLabel.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "label"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForLongLabel: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForLongLabel: function(xmlNode, testSettingsArray)
		{
			var varName1 = xmlNode.getAttribute("varName");
			if(varName1){
				var setting1 = {
					varName : varName1,
					verify : null,
					verifyType : null,
					verifyMin : null,
					verifyMax : null,
					upper : null,
					required : null
				};
				setting1.htmlid = "qx.ui.basic.Label." + varName1;
				testSettingsArray.push( setting1 );
			}

		}


	}

});
