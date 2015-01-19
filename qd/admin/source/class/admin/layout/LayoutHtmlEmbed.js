/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutHtmlEmbed", {

	members : {

		createHtmlEmbed : function ( theThis, elem, parent ){
			var obj = new qx.ui.embed.Html;
			this.processAttributes( theThis, elem, obj );
			obj.setOverflow("auto", "auto");
			// an html embed has no children.
			return obj;
		}

	}
});
