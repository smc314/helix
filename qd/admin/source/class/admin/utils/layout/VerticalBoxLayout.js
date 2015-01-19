/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating VerticalBoxLayout layout entities.
 */
qx.Mixin.define("admin.utils.layout.VerticalBoxLayout", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForVerticalBoxLayout: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "VerticalBoxLayout" );
			xmlNode.setAttribute( "spacing", "0" );
			xmlNode.setAttribute( "flex", "1" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForVerticalBoxLayout: function()
		{
			return [
				"Button",
				"FieldArea",
				"GroupBox",
				"HorizontalBoxLayout",
				"HorizontalSplitPane",
				"HtmlEmbed",
				"IFrame",
				"Label",
				"List",
				"Spacer",
				"StandardTable",
				"TextArea",
				"Tree",
				"TreeVirtual",
				"VerticalBoxLayout",
				"VerticalSplitPane",
			];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForVerticalBoxLayout: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.VerticalBoxLayout.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName", "spacing", "flex"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForVerticalBoxLayout: function()
		{
			// If we alreadyd have it - just return it
			if(this.VerticalBoxLayout_RMC){
				return this.VerticalBoxLayout_RMC;
			}
			// If not, create it, store it, and return it.
			var rmc = new qx.ui.menu.Menu();
			this.VerticalBoxLayout_RMC = rmc;
			this.addStandardContextMenuItems( rmc );

			rmc.addSeparator();
			admin.Statics.addToRMCMenu( rmc, "Convert To HorizontalBoxLayout",
				"admin/icon/16x16/plain/refresh.png",
				this.rmcVerticalBoxLayout_ConvertToHorizontal, this );

			return rmc;
		},

		rmcVerticalBoxLayout_ConvertToHorizontal: function()
		{

		}


	}

});
