/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutVerticalBoxLayout", {

	members: {

		createVerticalBoxLayout : function ( theThis, elem, parent ) {
			var obj = new qx.ui.container.Composite( new qx.ui.layout.VBox );
			this.processAttributes( theThis, elem, obj );
			this.processChildren( theThis, elem, obj );
			return obj;
		}

	}
});
