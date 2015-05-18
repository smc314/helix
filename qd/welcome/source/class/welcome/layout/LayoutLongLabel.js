/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutLongLabel", {

	members : {

		createLongLabel : function ( theThis, elem, parent ) {
			welcome.Statics.addLongLabel(parent,
				elem.getAttribute("label"),
				elem.getAttribute("varName"),
				theThis
			);
			return null;
		}

	}
});
