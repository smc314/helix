/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutButton", {

	members : {

		createButton : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.Button();
			this.processAttributes( theThis, elem, obj );
			return obj;
		}

	}
});
