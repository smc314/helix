/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("dev.layout.LayoutTextArea", {

	members : {

		createTextArea : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.TextArea;
			obj.setNativeContextMenu( true );
			this.processAttributes( theThis, elem, obj );
			// a text area has no children.
			return obj;
		}

	}
});
