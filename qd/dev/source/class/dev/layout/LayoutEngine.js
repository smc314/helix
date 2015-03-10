/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Class.define("dev.layout.LayoutEngine", {
	extend: qx.core.Object,

	include : [
		dev.layout.LayoutButton,
		dev.layout.LayoutDoubleCheck2,
		dev.layout.LayoutDoubleCheck,
		dev.layout.LayoutDoubleField,
		dev.layout.LayoutFieldArea,
		dev.layout.LayoutGroupBox,
		dev.layout.LayoutHorizontalBoxLayout,
		dev.layout.LayoutHtmlEmbed,
		dev.layout.LayoutIFrame,
		dev.layout.LayoutLabel,
		dev.layout.LayoutList,
		dev.layout.LayoutLongLabel,
		dev.layout.LayoutLongLabelRich,
		dev.layout.LayoutQuadCheck,
		dev.layout.LayoutQuadField,
		dev.layout.LayoutRadioGroup2,
		dev.layout.LayoutRadioGroup3,
		dev.layout.LayoutRadioGroup4,
		dev.layout.LayoutRadioGroup5,
		dev.layout.LayoutSingleCheck,
		dev.layout.LayoutSpacer,
		dev.layout.LayoutSpanField,
		dev.layout.LayoutSplitPane,
		dev.layout.LayoutStandardTable,
		dev.layout.LayoutStandardTreeVirtual,
		dev.layout.LayoutTextArea,
		dev.layout.LayoutCKTextArea,
		dev.layout.LayoutTree,
		dev.layout.LayoutTreeVirtual,
		dev.layout.LayoutTripleField,
		dev.layout.LayoutVerticalBoxLayout
	],

	statics : {

		/** This method combines the loadxml call with the call to renderLayout
		  * as a convienence.
		  */
		loadRenderLayout : function ( theThis, docURL, parent, callback ){

			dev.Api.LoadXMLDoc( docURL,
			function(response){
				var obj = dev.layout.LayoutEngine.renderLayout( theThis, response, parent);
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
				xmlDoc = dev.Statics.xmlStringToDoc( layoutDoc );
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
				theThis.error( dev.Statics.xmlDocToString( xmlDoc ) );
				return null;
			}
			var layoutEngine = new dev.layout.LayoutEngine;
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
					dev.Statics.trackNamedAttr( theThis, val );
					dev.Statics.setHtmlID( obj, val );
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
