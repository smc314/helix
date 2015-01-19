/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("PACKAGE.layout.LayoutLongLabelRich", {

	members : {
		
		createLongLabelRich : function ( theThis, elem, parent ) {
			PACKAGE.Statics.addLongLabelRich(parent,
				elem.getAttribute("label"),
				elem.getAttribute("varName"),
				theThis
			);
			return null;
		}

	}
});
