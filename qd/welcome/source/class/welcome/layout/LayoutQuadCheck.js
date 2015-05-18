/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutQuadCheck", {

	members : {

		createQuadCheck: function ( theThis, node, parent ) {

			welcome.Statics.addCheckboxes2(theThis, parent, this.fieldAreaFirst,
				Number( node.getAttribute("width1") ),
				Number( node.getAttribute("width2") ),
				Number( node.getAttribute("width3") ),
				Number( node.getAttribute("width4") ),
				node.getAttribute("varName1"),
				node.getAttribute("label1"),
				node.getAttribute("varName2"),
				node.getAttribute("label2"),
				node.getAttribute("varName3"),
				node.getAttribute("label3"),
				node.getAttribute("varName4"),
				node.getAttribute("label4")
			);

			// Set read only state:
			this.setReadOnly(theThis, node, "readOnly1", "varName1");
			this.setReadOnly(theThis, node, "readOnly2", "varName2");
			this.setReadOnly(theThis, node, "readOnly3", "varName3");
			this.setReadOnly(theThis, node, "readOnly4", "varName4");

		}

	}
});
