/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutTripleField", {

	members : {

		createTripleField: function ( theThis, node, parent ) {

			admin.Statics.addFieldsToForm(theThis, parent,
				node.getAttribute("label1"), this.fieldAreaFirst,
				node.getAttribute("varName1"),
				node.getAttribute("type1"),
				node.getAttribute("label2"), this.fieldAreaSecond,
				node.getAttribute("varName2"),
				node.getAttribute("type2"),
				node.getAttribute("label3"), this.fieldAreaThird,
				node.getAttribute("varName3"),
				node.getAttribute("type3")
			);

			// Check for tooltips:
			this.addToolTip(theThis, node, "tooltip1", "varName1");
			this.addToolTip(theThis, node, "tooltip2", "varName2");
			this.addToolTip(theThis, node, "tooltip3", "varName3");

			// Set read only state:
			this.setReadOnly(theThis, node, "readOnly1", "varName1");
			this.setReadOnly(theThis, node, "readOnly2", "varName2");
			this.setReadOnly(theThis, node, "readOnly3", "varName3");

			// Check for field verification
			this.checkFieldVerification(theThis, node);

			// Load any static combo values
			this.loadComboValues(theThis, node, 1);
			this.loadComboValues(theThis, node, 2);
			this.loadComboValues(theThis, node, 3);

		}

	}
});
