/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutLongLabel", {

	members : {

		createLongLabel : function ( theThis, elem, parent ) {
			admin.Statics.addLongLabel(parent,
				elem.getAttribute("label"),
				elem.getAttribute("varName"),
				theThis
			);
			return null;
		}

	}
});
