/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutIFrame", {

	members : {

		createIFrame : function ( theThis, elem, parent ){
			var obj = new qx.ui.embed.Iframe().set({decorator: null});
			this.processAttributes( theThis, elem, obj );
			// an iframe embed has no children.
			return obj;
		}

	}
});
