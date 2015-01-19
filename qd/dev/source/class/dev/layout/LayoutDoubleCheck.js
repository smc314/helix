/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("dev.layout.LayoutDoubleCheck", {

	members : {

		createDoubleCheck: function ( theThis, node, parent ) {

			dev.Statics.addCheckboxes(theThis, parent, this.fieldAreaFirst,
				node.getAttribute("varName1"),
				node.getAttribute("label1"),
				node.getAttribute("varName2"),
				node.getAttribute("label2")
			);

			// Set read only state:
			this.setReadOnly(theThis, node, "readOnly1", "varName1");
			this.setReadOnly(theThis, node, "readOnly2", "varName2");

		}

	}
});
