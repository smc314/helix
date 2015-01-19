/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("dev.layout.LayoutDoubleCheck2", {

	members : {

		createDoubleCheck2: function ( theThis, node, parent ) {

			dev.Statics.addCheckboxes2(theThis, parent, this.fieldAreaFirst,
				Number( node.getAttribute("width1") ),
				Number( node.getAttribute("width2") ),
				0,
				0,
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
