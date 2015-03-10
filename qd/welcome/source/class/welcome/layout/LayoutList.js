/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutList", {

	members : {

		createList : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.List;
			this.processAttributes( theThis, elem, obj );
			return obj;
		}

	}
});
