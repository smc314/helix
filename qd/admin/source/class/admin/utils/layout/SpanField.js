/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
/**
 * This mixin is loaded by the admin.utils.LayoutDesigner and defines everything
 * required to be known for manipulating SpanField layout entities.
 */
qx.Mixin.define("admin.utils.layout.SpanField", {

	members: {

		/** This will create an xml node with our default values.
		 */
		createXmlNodeForSpanField: function(xmlNodeParent)
		{
			var xmlNode = xmlNodeParent.ownerDocument.createElement( "SpanField" );
			xmlNode.setAttribute( "label1", "New Field:" );
			xmlNode.setAttribute( "type1", "TextField" );
			return xmlNode;
		},

		/** This will return a list of node names that can be children of our
		  * xml node in a valid layout.
		  */
		validChildrenForSpanField: function()
		{
			return [
				"List1Value",
				"List2Value"
			];
		},

		/** When this type of node is selected in the tree, this method will be
		 * called to tell the details editor how to lay itself out and how to map
		 * the xmlNode attriutes to the widgets on the settings pane.
		 */
		editDetailsForSpanField: function(treeNode, xmlNode)
		{
			this.reRenderSettingsPane( "LayoutDesigner.SpanField.xml" );
			this.pushXmlToFields( xmlNode, [
				"varName1", "label1", "type1", "tooltip1", "verify1", "verify1type",
				"verify1min", "verify1max", "upper1", "required1"
			] );
		},

		/** When the user invokes the context menu on one of our nodes, this
		 * is the menu that we will return.  Ensure that we only create the menu
		 * once, and then return it if it already exists.
		 */
		rmcMenuForSpanField: function()
		{
			return null;
		},

		/** This will read the data out of the given XML node and convert it into a
		  * series of test settings that can be used in our automation component.
		  */
		testSettingsForSpanField: function(xmlNode, testSettingsArray)
		{
			var varName1 = xmlNode.getAttribute("varName1");
			if(varName1){
				var setting1 = {
					varName : varName1,
					verify : xmlNode.getAttribute("verify1"),
					verifyType : xmlNode.getAttribute("verify1type"),
					verifyMin : xmlNode.getAttribute("verify1min"),
					verifyMax : xmlNode.getAttribute("verify1max"),
					upper : xmlNode.getAttribute("upper1"),
					required : xmlNode.getAttribute("required1")
				};
				var type1 = xmlNode.getAttribute("type1");
				switch( type1 ){
					case "TextField" : setting1.htmlid = "qx.ui.form.TextField." + varName1; break;
					case "PasswordField" : setting1.htmlid = "qx.ui.form.PasswordField." + varName1; break;
					case "ComboBox" : setting1.htmlid = "qx.ui.form.SelectBox." + varName1; break;
					case "ComboBoxEdit" : setting1.htmlid = "qx.ui.form.ComboBox." + varName1; break;
					case "DateField" : setting1.htmlid = "qx.ui.form.DateField." + varName1; break;
					case "TextArea" : setting1.htmlid = "qx.ui.form.TextArea." + varName1; break;
					case "TextField" : setting1.htmlid = "qx.ui.form.TextField." + varName1; break;
				}
				testSettingsArray.push( setting1 );
			}
		}


	}

});
