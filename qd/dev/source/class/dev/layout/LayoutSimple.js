/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Class.define("dev.layout.LayoutSimple", {

	type : "static",

	statics : {

		createLabel : function ( theThis, elem, parent ) {
			var obj = new qx.ui.basic.Label;
			dev.Statics.trackExtraObj( theThis, obj);
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
		},

		createSpacer : function ( theThis, elem, parent ) {
			var obj = new qx.ui.core.Spacer;
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
		},

		createList : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.List;
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
		},

		createButton : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.Button();
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
		},

		createTextArea : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.TextArea;
			obj.setNativeContextMenu( true );
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			// a text area has no children.
			return obj;
		},

		createHtmlEmbed : function ( theThis, elem, parent ){
			var obj = new qx.ui.embed.Html;
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			obj.setOverflow("auto", "auto");
			// an html embed has no children.
			return obj;
		},

		createIFrame : function ( theThis, elem, parent ){
			var obj = new qx.ui.embed.Iframe().set({decorator: null});
			dev.layout.LayoutEngine.processAttributes( theThis, elem, obj );
			// an iframe embed has no children.
			return obj;
		}

	}
});
