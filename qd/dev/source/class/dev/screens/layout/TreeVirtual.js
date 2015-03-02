/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the dev.screens.LayoutDesigner and defines everything
 * required to be known for manipulating TreeVirtual layout entities.
 */
qx.Mixin.define("dev.screens.layout.TreeVirtual", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForTreeVirtual: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "TreeVirtual" );
			xmlNode.setAttribute( "flex", "1" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForTreeVirtual: function()
		{
			return [
				"Column"
			];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForTreeVirtual: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.TreeVirtual.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "flex"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForTreeVirtual: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForTreeVirtual: function(xmlNode, testSettingsArray)
		{
			var varName1 = xmlNode.getAttribute("varName");
			if(varName1){
				var setting1 = {
					varName : varName1,
					htmlid : "qx.ui.treevirtual.TreeVirtual." + varName1,
					verify : null,
					verifyType : null,
					verifyMin : null,
					verifyMax : null,
					upper : null,
					required : null
				};
				testSettingsArray.push( setting1 );
			}

		}


	}

});
