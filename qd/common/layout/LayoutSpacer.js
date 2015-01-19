/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("PACKAGE.layout.LayoutSpacer", {

	members : {
		
		createSpacer : function ( theThis, elem, parent ) {
			var obj = new qx.ui.core.Spacer;
			this.processAttributes( theThis, elem, obj );
			return obj;
		}

	}
});
