/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutSingleCheck", {

	members : {

		createSingleCheck: function ( theThis, node, parent ) {

			welcome.Statics.addCheckboxes(theThis, parent, this.fieldAreaFirst,
				node.getAttribute("varName1"),
				node.getAttribute("label1")
			);

			// Set read only state:
			this.setReadOnly(theThis, node, "readOnly1", "varName1");

		}

	}
});
