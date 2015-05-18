/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Class.define("PACKAGE.layout.LayoutEngine", {
	extend: qx.core.Object,

	include : [
		PACKAGE.layout.LayoutButton,
		PACKAGE.layout.LayoutDoubleCheck2,
		PACKAGE.layout.LayoutDoubleCheck,
		PACKAGE.layout.LayoutDoubleField,
		PACKAGE.layout.LayoutFieldArea,
		PACKAGE.layout.LayoutGroupBox,
		PACKAGE.layout.LayoutHorizontalBoxLayout,
		PACKAGE.layout.LayoutHtmlEmbed,
		PACKAGE.layout.LayoutIFrame,
		PACKAGE.layout.LayoutLabel,
		PACKAGE.layout.LayoutList,
		PACKAGE.layout.LayoutLongLabel,
		PACKAGE.layout.LayoutLongLabelRich,
		PACKAGE.layout.LayoutQuadCheck,
		PACKAGE.layout.LayoutQuadField,
		PACKAGE.layout.LayoutRadioGroup2,
		PACKAGE.layout.LayoutRadioGroup3,
		PACKAGE.layout.LayoutRadioGroup4,
		PACKAGE.layout.LayoutRadioGroup5,
		PACKAGE.layout.LayoutSingleCheck,
		PACKAGE.layout.LayoutSpacer,
		PACKAGE.layout.LayoutSpanField,
		PACKAGE.layout.LayoutSplitPane,
		PACKAGE.layout.LayoutStandardTable,
		PACKAGE.layout.LayoutStandardTreeVirtual,
		PACKAGE.layout.LayoutTextArea,
		PACKAGE.layout.LayoutCKTextArea,
		PACKAGE.layout.LayoutTree,
		PACKAGE.layout.LayoutTreeVirtual,
		PACKAGE.layout.LayoutTripleField,
		PACKAGE.layout.LayoutVerticalBoxLayout
	],

	statics : {
		
		/** This method combines the loadxml call with the call to renderLayout
		  * as a convienence.
		  */
		loadRenderLayout : function ( theThis, docURL, parent, callback ){
		
			PACKAGE.Api.LoadXMLDoc( docURL, 
			function(response){
				var obj = PACKAGE.layout.LayoutEngine.renderLayout( theThis, response, parent);
				callback.call(theThis, response.ownerDocument, obj); 
			}, theThis );
		
		},  
		  
		/** This function makes it easy to create your widget layout by describing
		 * the contents of your layout using an XML document.  This allows you to
		 * be more compact in your layout description, while still taking full advantage
		 * of the qooxdoo widget system.
		 * 
		 * @param theThis {Object} This is the object that we will attach any variables to.
		 * @param layoutDoc {Object} This is an XML string that we will parse to read your layout.
		 * @param parent {Object} This is the widget parent that the new layout will be added to.
		 */
		renderLayout : function ( theThis, layoutDoc, parent ) {
			var xmlDoc = null;
			var elem = null;
			if(typeof(layoutDoc) === "string" || layoutDoc instanceof String){
				xmlDoc = PACKAGE.Statics.xmlStringToDoc( layoutDoc );
			} else {
				xmlDoc = layoutDoc;
			}
			if(xmlDoc === null){
				theThis.error( "Invalid XML Document passed to renderLayout" );
				return null;
			}
			elem = xmlDoc.documentElement;
			
			// Start at the root and work our way down
			if(elem.nodeName === "parsererror"){
				theThis.error("Invalid XML Document passed to renderLayout" );
				theThis.error( PACKAGE.Statics.xmlDocToString( xmlDoc ) );
				return null;
			}
			var layoutEngine = new PACKAGE.layout.LayoutEngine;
			var obj = layoutEngine.createElementAndChildren( theThis, elem, parent );
			
			if((parent) && (obj) && (parent !== obj)){
				var flex = layoutEngine.getFlexAttr(elem);
				if(flex){
					parent.add(obj, {flex: flex});
				} else {
					parent.add(obj);
				}
			}
			return obj;
		}
	},

	members : {
		

		/** This method will create the object that represents the current node and
		  * then recursively call ourselves for all child nodes found.
		  */
		createElementAndChildren : function (theThis, elem, parent) {

			if(elem.nodeType !== 1){
				return null; // Only process Element nodes
			}
			var methodName = "create" + elem.nodeName;
			if(this[ methodName ] !== undefined){
				return this[ methodName ]( theThis, elem, parent );
			} else {
				theThis.error( "No method " + methodName + " found to handle layout element " + elem.nodeName );
				return null;
			}

		},
		
		createRecursiveCheckBoxTree : function ( theThis, elem, parent ) {
			// first pull out the column list:
			// A tree has no children.
			return null;
		},

		processAttributes : function ( theThis, elem, obj ){
			var attrMap = elem.attributes;
			if(attrMap === null){
				return;
			}
			for(var i = 0, l = attrMap.length; i < l; i++){
				var node = attrMap.item( i );
				var name = node.nodeName;
				var val = node.nodeValue;
				if(name === "varName"){
					theThis[ val ] = obj;
					PACKAGE.Statics.trackNamedAttr( theThis, val );
					PACKAGE.Statics.setHtmlID( obj, val );
				} else if(name === "label" ){
					obj.setLabel( val );
				} else if(name === "legend" ){
					obj.setLegend( val );
				} else if(name === "icon" ){
					obj.setIcon( val );
				} else if(name === "text" ){
					obj.setValue( val );
				} else if(name === "flex" ){
					// skip this attribute.
				} else if(name === "isCheck" ){
					// skip this attribute.
				} else if(name === "isRadio" ){
					// skip this attribute.
				} else if(name === "alignY" ){
					obj._getLayout().setAlignY( val );
				} else if(name === "alignX" ){
					obj._getLayout().setAlignX( val );
				} else if(name === "spacing" ){
					obj._getLayout().setSpacing( Number(val) );
				} else if(name === "separator" ){
					// skip this attribute.
				} else if(name === "reversed" ){
					if(val === "true"){
						obj._getLayout().setReversed( true );
					} else {
						obj._getLayout().setReversed( false );
					}
				} else if(name === "minWidth" ){
					obj.setMinWidth( Number(val) );
				} else if(name === "width" ){
					obj.setWidth( Number(val) );
				} else if(name === "maxWidth" ){
					obj.setMaxWidth( Number(val) );
				} else if(name === "minHeight" ){
					obj.setMinHeight( Number(val) );
				} else if(name === "height" ){
					obj.setHeight( Number(val) );
				} else if(name === "maxHeight" ){
					obj.setMaxHeight( Number(val) );
				} else if(name === "allowGrowX" ){
					if(val === "true"){
						obj.setAllowGrowX( true );
					} else {
						obj.setAllowGrowY( false );
					}
				} else if(name === "allowShrinkX" ){
					if(val === "true"){
						obj.setAllowShrinkX( true );
					} else {
						obj.setAllowShrinkX( false );
					}
				} else if(name === "allowGrowY" ){
					if(val === "true"){
						obj.setAllowGrowY( true );
					} else {
						obj.setAllowGrowY( false );
					}
				} else if(name === "allowShrinkY" ){
					if(val === "true"){
						obj.setAllowShrinkY( true );
					} else {
						obj.setAllowShrinkY( false );
					}
				} else if(name === "allowStretchX" ){
					if(val === "true"){
						obj.setAllowStretchX( true );
					} else {
						obj.setAllowStretchX( false );
					}
				} else if(name === "allowStretchY" ){
					if(val === "true"){
						obj.setAllowStretchY( true );
					} else {
						obj.setAllowStretchY( false );
					}
				} else if(name === "nativeContextMenu" ){
					if(val === "true"){
						obj.setNativeContextMenu( true );
					} else {
						obj.setNativeContextMenu( false );
					}
				} else if(name === "marginTop" ){
					obj.setMarginTop( Number(val) );
				} else if(name === "marginRight" ){
					obj.setMarginRight( Number(val) );
				} else if(name === "marginBottom" ){
					obj.setMarginBottom( Number(val) );
				} else if(name === "marginLeft" ){
					obj.setMarginLeft( Number(val) );
				} else if(name === "margin" ){
					obj.setMargin( Number(val) );
				} else if(name === "paddingTop" ){
					obj.setPaddingTop( Number(val) );
				} else if(name === "paddingRight" ){
					obj.setPaddingRight( Number(val) );
				} else if(name === "paddingBottom" ){
					obj.setPaddingBottom( Number(val) );
				} else if(name === "paddingLeft" ){
					obj.setPaddingLeft( Number(val) );
				} else if(name === "padding" ){
					obj.setPadding( Number(val) );
				} else if(name === "appearance" ){
					obj.setAppearance( val );
				} else if(name === "overflow" ){
					obj.set({overflow:val});
				} else if(name === "wrap" ){
					if(val === "true"){
						obj.setWrap( true );
					} else {
						obj.setWrap( false );
					}
				} else if(name === "readOnly" ){
					if(val === "true"){
						obj.setReadOnly( true );
					} else {
						obj.setReadOnly( false );
					}
				} else if(name === "filename" ){
					// Ignore this one.
				} else if(name === "filtered" ){
					// Ignore this one.
				} else {
					theThis.warn("Unknown attribute (" + name + ") in layout element (" + elem.nodeName + ")" );
				}
			}
		},
		
		getFlexAttr : function (elem){
			var attrMap = elem.attributes;
			if(attrMap === null){
				return null;
			}
			for(var i = 0, l = attrMap.length; i < l; i++){
				var node = attrMap.item( i );
				var name = node.nodeName;
				var val = node.nodeValue;
				if(name === "flex"){
					return Number(val);
				}
			}
			// didn't find it.
			return null;
		},

		processChildren : function ( theThis, elem, obj ){
			for(var i = 0, l = elem.childNodes.length; i < l; i++){
				var node = elem.childNodes[i];
				var child = this.createElementAndChildren( theThis, node, obj );
				if(child){
					var flex_num = this.getFlexAttr(node);
					if(flex_num){
						obj.add(child, {flex: flex_num});
					} else {
						obj.add(child);
					}
				}
			}
		}
	}
});
