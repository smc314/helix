/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("dev.layout.LayoutLongLabelRich", {

	members : {

		createLongLabelRich : function ( theThis, elem, parent ) {
			dev.Statics.addLongLabelRich(parent,
				elem.getAttribute("label"),
				elem.getAttribute("varName"),
				theThis
			);
			return null;
		}

	}
});
