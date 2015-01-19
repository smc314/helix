/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutLabel", {

	members : {

		createLabel : function ( theThis, elem, parent ) {
			var obj = new qx.ui.basic.Label;
			admin.Statics.trackExtraObj( theThis, obj);
			this.processAttributes( theThis, elem, obj );
			return obj;
		}

	}
});
