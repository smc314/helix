/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutSplitPane", {

	members : {

		createVerticalSplitPane : function ( theThis, elem, parent ) {
			return this.createSplitPane( theThis, elem, parent, "vertical" );
		},

		createHorizontalSplitPane : function ( theThis, elem, parent ) {
			return this.createSplitPane( theThis, elem, parent, "horizontal" );
		},

		createSplitPane : function ( theThis, elem, parent, orientation ) {
			var flex1 = Number( elem.getAttribute( "leftsize") );
			var flex2 = Number( elem.getAttribute("rightsize") );
			var obj = new qx.ui.splitpane.Pane(orientation);
			// The standard splitpane has a decorator that adds a border around
			// the whole widget.  We don't want that, so use the Background decorator
			// instead to get a 0 border.
			obj.set({decorator : new qx.ui.decoration.Decorator});

			// remove leftsize and rightsize before processing attrs:
			elem.removeAttribute("leftsize");
			elem.removeAttribute("rightsize");
			this.processAttributes( theThis, elem, obj );

			// A split-pane has only 2 children.  Process them by hand:
			if(orientation === "vertical"){
				var firstHalf = welcome.Statics.xmlFindChild(elem, "VerticalSplitPaneTop" );
			} else {
				var firstHalf = welcome.Statics.xmlFindChild(elem, "HorizontalSplitPaneLeft");
			}
			// find the first real child of VerticalSplitPaneTop
			for(var i = 0, l = firstHalf.childNodes.length; i < l; i++){
				var node = firstHalf.childNodes[i];
				var child = this.createElementAndChildren( theThis, node, obj );
				if(child){
					obj.add(child, flex1);
					break;
				}
			}

			if(orientation === "vertical"){
				var secondHalf = welcome.Statics.xmlFindChild(elem, "VerticalSplitPaneBottom" );
			} else {
				var secondHalf = welcome.Statics.xmlFindChild(elem, "HorizontalSplitPaneRight" );
			}
			// find the first real child of VerticalSplitPaneBottom
			for(var i = 0, l = secondHalf.childNodes.length; i < l; i++){
				var node = secondHalf.childNodes[i];
				var child = this.createElementAndChildren( theThis, node, obj );
				if(child){
					obj.add(child, flex2);
					break;
				}
			}

			return obj;
		}

	}
});
