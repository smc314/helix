/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating DoubleCheck2 layout entities.
 */
qx.Mixin.define("admin.utils.layout.DoubleCheck2", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForDoubleCheck2: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "DoubleCheck2" );
			xmlNode.setAttribute( "varName1", "checkVar1" );
			xmlNode.setAttribute( "label1", "True or False?" );
			xmlNode.setAttribute( "width1", "120" );
			xmlNode.setAttribute( "varName2", "checkVar2" );
			xmlNode.setAttribute( "label2", "False or True?" );
			xmlNode.setAttribute( "width2", "120" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForDoubleCheck2: function()
		{
			return [  ];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForDoubleCheck2: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.DoubleCheck2.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName1", "label1", "width1",
				"varName2", "label2", "width2"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForDoubleCheck2: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForDoubleCheck2: function(xmlNode, testSettingsArray)
		{
			var varName1 = xmlNode.getAttribute("varName1");
			if(varName1){
				var setting1 = {
					varName : varName1,
					htmlid : "qx.ui.form.CheckBox." + varName1
				};
				testSettingsArray.push( setting1 );
			}
			var varName2 = xmlNode.getAttribute("varName2");
			if(varName2){
				var setting2 = {
					varName : varName2,
					htmlid : "qx.ui.form.CheckBox." + varName2
				};
				testSettingsArray.push( setting2 );
			}

		}

	}

});
