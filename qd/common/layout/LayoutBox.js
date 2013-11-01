/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
qx.Class.define("PACKAGE.layout.LayoutBox", {

	type : "static",

	statics: {

		createVerticalBoxLayout : function ( theThis, elem, parent ) {
			var obj = new qx.ui.container.Composite( new qx.ui.layout.VBox );
			PACKAGE.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			PACKAGE.layout.LayoutEngine.processChildren( theThis, elem, obj );
			return obj;
		},

		createHorizontalBoxLayout: function ( theThis, elem, parent ) {
			var obj = new qx.ui.container.Composite( new qx.ui.layout.HBox );
			PACKAGE.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			PACKAGE.layout.LayoutEngine.processChildren( theThis, elem, obj );
			return obj;
		}

	}
});
