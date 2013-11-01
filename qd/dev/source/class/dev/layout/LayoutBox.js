/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
qx.Class.define("dev.layout.LayoutBox", {

	type : "static",

	statics: {

		createVerticalBoxLayout : function ( theThis, elem, parent ) {
			var obj = new qx.ui.container.Composite( new qx.ui.layout.VBox );
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			dev.layout.LayoutEngine.processChildren( theThis, elem, obj );
			return obj;
		},

		createHorizontalBoxLayout: function ( theThis, elem, parent ) {
			var obj = new qx.ui.container.Composite( new qx.ui.layout.HBox );
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			dev.layout.LayoutEngine.processChildren( theThis, elem, obj );
			return obj;
		}

	}
});
