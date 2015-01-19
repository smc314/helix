/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("PACKAGE.layout.LayoutRadioGroup5", {

	members : {
		
		createRadioGroup5: function ( theThis, node, parent ) {

			var rg = PACKAGE.Statics.addRadioGroupHorizontal(theThis, parent, this.fieldAreaFirst,
				null, // groupName is not used
				node.getAttribute("labelPrefix"),
				node.getAttribute("varName1"), node.getAttribute("label1"),
				node.getAttribute("varName2"), node.getAttribute("label2"),
				node.getAttribute("varName3"), node.getAttribute("label3"),
				node.getAttribute("varName4"), node.getAttribute("label4")
			);

			theThis[ node.getAttribute("groupName") ] = rg;

			// Set read only state:
			this.setReadOnly(theThis, node, "readOnly1", "varName1");
			this.setReadOnly(theThis, node, "readOnly2", "varName2");
			this.setReadOnly(theThis, node, "readOnly3", "varName3");
			this.setReadOnly(theThis, node, "readOnly4", "varName4");

		}

	}
});
