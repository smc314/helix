/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutTree", {

	members : {

		createTree: function ( theThis, elem, parent ) {
			var obj = new qx.ui.tree.Tree();
			this.processAttributes( theThis, elem, obj );

			// A tree has no children
			return obj;
		}

	}
});
