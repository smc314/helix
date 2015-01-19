/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("PACKAGE.layout.LayoutDoubleField", {

	members : {
		
		createDoubleField: function ( theThis, node, parent ) {

			PACKAGE.Statics.addFieldsToForm(theThis, parent,
				node.getAttribute("label1"), this.fieldAreaFirst,
				node.getAttribute("varName1"),
				node.getAttribute("type1"),
				node.getAttribute("label2"), this.fieldAreaSecond,
				node.getAttribute("varName2"),
				node.getAttribute("type2")
			);

			// Check for tooltips:
			this.addToolTip(theThis, node, "tooltip1", "varName1");
			this.addToolTip(theThis, node, "tooltip2", "varName2");

			// Set read only state:
			this.setReadOnly(theThis, node, "readOnly1", "varName1");
			this.setReadOnly(theThis, node, "readOnly2", "varName2");

			// Check for field verification
			this.checkFieldVerification(theThis, node);

			// Load any static combo values
			this.loadComboValues(theThis, node, 1);
			this.loadComboValues(theThis, node, 2);

		}

	}
});
