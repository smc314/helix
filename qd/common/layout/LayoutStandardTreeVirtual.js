/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("PACKAGE.layout.LayoutStandardTreeVirtual", {

	members : {
		
		createStandardTreeVirtual: function ( theThis, elem, parent ) {
			// first pull out the column list:
			var columns = elem.getElementsByTagName( "Column" );
			var titles = [];
			for(var i = 0, l = columns.length; i < l; i++){
				titles.push( columns[i].getAttribute("title") );
			}
		
			var obj = PACKAGE.Statics.createStandardTreeVirtual( titles );
			this.processAttributes( theThis, elem, obj );

			// Adjust column sizes if given:
			var sizing = obj.getTableColumnModel().getBehavior();
			for(var i = 0, l = columns.length; i < l; i++){
				var hash = {};
				if(columns[i].getAttribute("width")){
					hash.width = columns[i].getAttribute("width");
				}
				if(columns[i].getAttribute("minWidth")){
					hash.minWidth = Number(columns[i].getAttribute("minWidth"));
				}
				if(columns[i].getAttribute("maxWidth")){
					hash.maxWidth = Number(columns[i].getAttribute("maxWidth"));
				}
				sizing.set( i, hash );
			}
			
			// A table has no children.
			return obj;
		}

	}
});
