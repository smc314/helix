/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("PACKAGE.layout.LayoutSpanField", {

	members : {
		
		createSpanField: function ( theThis, node, parent ) {

			PACKAGE.Statics.addFieldsToForm(theThis, parent,
				node.getAttribute("label1"), this.fieldAreaFirst,
				node.getAttribute("varName1"),
				node.getAttribute("type1")
			);

			// Check for tooltips:
			this.addToolTip(theThis, node, "tooltip1", "varName1");

			// Set read only state:
			this.setReadOnly(theThis, node, "readOnly1", "varName1");

			// Check for field verification
			this.checkFieldVerification(theThis, node);

			// Load any static combo values
			this.loadComboValues(theThis, node, 1);

			if(node.getAttribute("type1") === "TextArea" && node.getAttribute("height1")){
				theThis[node.getAttribute("varName1")].setMaxHeight(
					Number( node.getAttribute("height1") )
				);
				theThis[node.getAttribute("varName1")].setHeight(
					Number( node.getAttribute("height1") )
				);
			}

		}

	}
});
