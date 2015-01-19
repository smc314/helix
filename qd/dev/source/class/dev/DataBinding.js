/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */

/** This class defines a series of static methods that make it straightforward for
  * us to hook our layout.xml files into the standard qooxdoo data binding functions.
  * We're really just translating the instructions in the xml into native qooxdoo functions.
  *
  * We also have several methods to help with data binding on tables, and various other
  * standard layouts that we use.
  */
qx.Class.define("dev.DataBinding", {

	type : "static",

	statics : {

		/** This function makes it easy to bind the widgets in your layout to your data
		 * model.  This should be called after DataBinding.renderLayout, and after you
		 * have a valid data object either manually created, or loaded from the server.
		 */
		bindLayout : function ( theThis, dataObject, layoutDoc) {
			var xmlDoc = null;
			var elem = null;
			if(typeof(layoutDoc) === "string" || layoutDoc instanceof String){
				xmlDoc = dev.Statics.xmlStringToDoc( layoutDoc );
			} else {
				xmlDoc = layoutDoc;
			}
			if(xmlDoc === null){
				theThis.error( "Invalid XML Document passed to bindLayout" );
				return null;
			}
			elem = xmlDoc.documentElement;

			// Start at the root and work our way down
			if(elem.nodeName === "parsererror"){
				theThis.error("Invalid XML Document passed to bindLayout" );
				theThis.error( dev.Statics.xmlDocToString( xmlDoc ) );
				return null;
			}

			// walk all of the elements in the layout and handle the data binding.
			dev.DataBinding.bindElementAndChildren( theThis, dataObject, elem);

		},

		/** This method will create the binding for the current node and
		  * then recursively call ourselves for all child nodes found.
		  */
		bindElementAndChildren : function (theThis, dataObject, elem ) {

			if(elem.nodeName === "VerticalBoxLayout"){
				dev.DataBinding.processChildren( theThis, dataObject, elem ); // just recurse to the children
			} else if(elem.nodeName === "HorizontalBoxLayout"){
				dev.DataBinding.processChildren( theThis, dataObject, elem ); // just recurse to the children
			} else if(elem.nodeName === "VerticalSplitPane") {
				dev.DataBinding.processChildren( theThis, dataObject, elem ); // just recurse to the children
			} else if(elem.nodeName === "GroupBox") {
				dev.DataBinding.bindGroupBox( theThis, dataObject, elem );
			} else if(elem.nodeName === "TreeVirtual" ) {
				dev.DataBinding.bindTreeVirtual( theThis, dataObject, elem);
			} else if(elem.nodeName === "RecursiveCheckBoxTree" ) {
				dev.DataBinding.bindRecursiveCheckBoxTree( theThis, dataObject, elem );
			} else if(elem.nodeName === "HorizontalSplitPane") {
				dev.DataBinding.processChildren( theThis, dataObject, elem ); // just recurse to the children
			} else if(elem.nodeName === "TextArea") {
				dev.DataBinding.bindTextArea( theThis, dataObject, elem );
			} else if(elem.nodeName === "HtmlEmbed") {
				dev.DataBinding.bindHtmlEmbed( theThis, dataObject, elem );
			} else if(elem.nodeName === "IFrame") {
				dev.DataBinding.bindIFrame( theThis, dataObject, elem );
			} else if(elem.nodeName === "StandardTable") {
				dev.DataBinding.bindStandardTable( theThis, dataObject, elem );
			} else if(elem.nodeName === "StandardTreeVirtual") {
				dev.DataBinding.bindStandardTreeVirtual( theThis, dataObject, elem );
			} else if(elem.nodeName === "FieldArea") {
				dev.DataBinding.bindFieldArea( theThis, dataObject, elem );
			} else if(elem.nodeName === "Label") {
				dev.DataBinding.bindLabel( theThis, dataObject, elem );
			} else if(elem.nodeName === "Spacer") {
				dev.DataBinding.processChildren( theThis, dataObject, elem ); // just recurse to the children
			} else if(elem.nodeName === "List") {
				dev.DataBinding.bindList( theThis, dataObject, elem );
			} else if(elem.nodeName === "Button") {
				dev.DataBinding.bindButton( theThis, dataObject, elem );
			}
		},

		getObjectController : function ( theThis, dataObject ) {
			if(theThis.objectControllers === undefined){
				theThis.objectControllers = [];
			}

			for(var i = 0, l = theThis.objectControllers.length; i < l; i++){
				var oc = theThis.objectControllers[ i ];
				if(oc.getModel() === dataObject){
					return oc; // Found an existing object controller for the given data model.
				}
			}

			// If we get to here, there isn't an object controller that corresponds to
			// the given data model.  Create it, add it, and return it.
			var oc = new qx.data.controller.Object( dataObject );
			theThis.objectControllers.push( oc );
			return oc;
		},

		bindGroupBox : function ( theThis, dataObject, elem) {
			if(elem.getAttribute( "varName" ) && elem.getAttribute("varName").length !== 0){
				// bind the group box as a variable.
				theThis.warn("bindGroupBox - not implemented yet.  Step on it!");
			}
			/*
			if(elem.getAttribute( "isCheck") && elem.getAttribute("isCheck") === "true"){
				var obj = new qx.ui.groupbox.CheckGroupBox();
			} else if(elem.getAttribute( "isRadio") && elem.getAttribute("isRadio") === "true"){
				var obj = new qx.ui.groupbox.RadioGroupBox();
			} else {
				var obj = new qx.ui.groupbox.GroupBox();
			}
			*/

			// Remember to also process all of the children inside the group-box
			dev.DataBinding.processChildren( theThis, dataObject, elem );
		},

		bindLabel : function ( theThis, dataObject, elem) {
			theThis.warn("bindLabel - not implemented yet.  Step on it!"); return;

			var obj = new qx.ui.basic.Label;
			dev.Statics.trackExtraObj( theThis, obj);
			dev.DataBinding.processAttributes( theThis, elem, obj );
			return obj;
		},

		bindList : function ( theThis, dataObject, elem) {
			theThis.warn("bindList - not implemented yet.  Step on it!"); return;
			var obj = new qx.ui.form.List;
			dev.DataBinding.processAttributes( theThis, elem, obj );
			return obj;
		},

		bindButton : function ( theThis, dataObject, elem) {
			theThis.warn("bindButton - not implemented yet.  Step on it!"); return;
			var obj = new qx.ui.form.Button();
			dev.DataBinding.processAttributes( theThis, elem, obj );
			return obj;
		},

		bindTreeVirtual : function ( theThis, dataObject, elem) {
			theThis.warn("bindTreeVirtual - not implemented yet.  Step on it!"); return;
			// first pull out the column list:
			var columns = elem.getElementsByTagName( "Column" );
			var titles = [];
			for(var i = 0, l = columns.length; i < l; i++){
				titles.push( columns[i].getAttribute("title") );
			}

			var obj = dev.Statics.createStandardTreeVirtual( titles );
			dev.DataBinding.processAttributes( theThis, elem, obj );

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

			// A tree has no children.
			return obj;
		},

		bindRecursiveCheckBoxTree : function ( theThis, dataObject, elem) {
			// first pull out the column list:
			// A tree has no children.
			return null;
		},

		bindTextArea : function ( theThis, dataObject, elem) {
			theThis.warn("bindTextArea - not implemented yet.  Step on it!"); return;
			var obj = new qx.ui.form.TextArea;
			obj.setNativeContextMenu( true );
			dev.DataBinding.processAttributes( theThis, elem, obj );
			// a text area has no children.
			return obj;
		},

		bindHtmlEmbed : function ( theThis, dataObject, elem){
			theThis.warn("bindHtmlEmbed - not implemented yet.  Step on it!"); return;
			var obj = new qx.ui.embed.Html;
			dev.DataBinding.processAttributes( theThis, elem, obj );
			obj.setOverflow("auto", "auto");
			// an html embed has no children.
			return obj;
		},

		bindIFrame : function ( theThis, dataObject, elem){
			theThis.warn("bindIFrame - not implemented yet.  Step on it!"); return;
			var obj = new qx.ui.embed.Iframe().set({decorator: null});
			dev.DataBinding.processAttributes( theThis, elem, obj );
			// an iframe embed has no children.
			return obj;
		},

		bindStandardTable : function ( theThis, dataObject, elem) {
			if(!elem.getAttribute( "varName" )) return;            // needs a varName attribute
			if(elem.getAttribute("varName").length === 0) return;   // varName attr needs to have a value
			if(!elem.getAttribute( "data" )) return;               // needs a data attribute
			if(elem.getAttribute( "data" ).length === 0) return;   // data attribute needs to have a value

			var varName = elem.getAttribute("varName");
			var data = elem.getAttribute("data");

			// use the column list to load the table with the initial data:
			var columns = elem.getElementsByTagName( "Column" );
			var rows = dataObject[ data ];

			var tableData = [];
			for(var row_counter = 0, row_length = rows.length; row_counter < row_length; row_counter++ ){
				var row = rows[i];
			}

			for(var i = 0, l = columns.length; i < l; i++){
				titles.push( columns[i].getAttribute("title") );
				if(columns[i].getAttribute("data")){
					props.push( columns[i].getAttribute("data") );
				} else {
					props.push( null );
				}
			}

			var filtered = "false";
			if(elem.getAttribute( "filtered" )){
				filtered = elem.getAttribute("filtered");
			}

			var obj = dev.Statics.createStandardTable( titles, filtered );
			dev.DataBinding.processAttributes( theThis, elem, obj );

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
		},

		bindStandardTreeVirtual: function ( theThis, dataObject, elem) {
			theThis.warn("bindStandardTreeVirtual - not implemented yet.  Step on it!"); return;
			// first pull out the column list:
			var columns = elem.getElementsByTagName( "Column" );
			var titles = [];
			for(var i = 0, l = columns.length; i < l; i++){
				titles.push( columns[i].getAttribute("title") );
			}

			var obj = dev.Statics.createStandardTreeVirtual( titles );
			dev.DataBinding.processAttributes( theThis, elem, obj );

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
		},

		checkFieldVerification : function(theThis, node) {
			var verify1 = node.getAttribute("verify1");
			if(verify1 && verify1 === "true"){
				if(theThis.fieldVerificationList === undefined){
					theThis.fieldVerificationList = [];
				}

				theThis.fieldVerificationList.push( {
					varName: node.getAttribute("varName1"),
					label: node.getAttribute("label1"),
					type: node.getAttribute("verify1type"),
					min: node.getAttribute("verify1min"),
					max: node.getAttribute("verify1max"),
					upper: node.getAttribute("upper1"),
					required: node.getAttribute("required1")
				} );
			}

			var verify2 = node.getAttribute("verify2");
			if(verify2 && verify2 === "true"){
				if(theThis.fieldVerificationList === undefined){
					theThis.fieldVerificationList = [];
				}

				theThis.fieldVerificationList.push( {
					varName: node.getAttribute("varName2"),
					label: node.getAttribute("label2"),
					type: node.getAttribute("verify2type"),
					min: node.getAttribute("verify2min"),
					max: node.getAttribute("verify2max"),
					upper: node.getAttribute("upper2"),
					required: node.getAttribute("required2")
				} );
			}

			var verify3 = node.getAttribute("verify3");
			if(verify3 && verify3 === "true"){
				if(theThis.fieldVerificationList === undefined){
					theThis.fieldVerificationList = [];
				}

				theThis.fieldVerificationList.push( {
					varName: node.getAttribute("varName3"),
					label: node.getAttribute("label3"),
					type: node.getAttribute("verify3type"),
					min: node.getAttribute("verify3min"),
					max: node.getAttribute("verify3max"),
					upper: node.getAttribute("upper3"),
					required: node.getAttribute("required3")
				} );
			}

			var verify4 = node.getAttribute("verify4");
			if(verify4 && verify4 === "true"){
				if(theThis.fieldVerificationList === undefined){
					theThis.fieldVerificationList = [];
				}

				theThis.fieldVerificationList.push( {
					varName: node.getAttribute("varName4"),
					label: node.getAttribute("label4"),
					type: node.getAttribute("verify4type"),
					min: node.getAttribute("verify4min"),
					max: node.getAttribute("verify4max"),
					upper: node.getAttribute("upper4"),
					required: node.getAttribute("required4")
				} );
			}

		},

		bindField : function ( theThis, dataObject, elem, index ) {
			var varName = elem.getAttribute("varName" + index);
			var type = elem.getAttribute("type" + index);
			var data = elem.getAttribute("data" + index);

			if(!varName || !type || !data) {
				theThis.debug("Not enough information to bind " + elem.nodeName + " to widget." );
				return; // Not enough information to bind this field
			}

			var oc = dev.DataBinding.getObjectController( theThis, dataObject );

			if(type === "TextField"){
				oc.addTarget( theThis[ varName ], "value", data );
			} else if(type === "PasswordField"){
				oc.addTarget( theThis[ varName ], "value", data );
			} else if(type === "DateField"){
				oc.addTarget( theThis[ varName ], "value", data );
			} else if(type === "TextArea"){
				oc.addTarget( theThis[ varName ], "value", data );
			} else if(type === "ComboBox" || type === "ComboBoxEdit"){
				var dataSource = elem.getAttribute("data" + index + "Source");
				if(!dataSource){
					theThis.warn("Not enough information to bind " + type + " in " + elem.nodeName + " to widget.");
					return;
				}
				if(dataSource === "Static"){
					// The values for this list are staticly included in the layout.  Pull them out, convert
					// them to an array, and use them as the model for the list.
					var staticArray = new qx.data.Array( );
					var childNodeName = "List" + index + "Value";
					for(var i = 0, l = elem.childNodes.length; i < l; i++){
						var node = elem.childNodes[i];
						if(node.nodeName === childNodeName){
							staticArray.push( node.getAttribute( "label" ) );
						}
					}
					// Bind the model to the select or combo-box:
					var lc = new qx.data.controller.List( staticArray, theThis[ varName ] );
					// Also bind the selection to the dataObject property:
					lc.bind("selection[0]", dataObject, data );
					// Record the list controller in case we need to use it more:
					theThis[ varName + "ListController" ] = lc
				} else {
					// Determine which child array hold the values for this list

				}
			}

		},

		bindFieldArea : function ( theThis, dataObject, elem ) {
			//var cols = Number( elem.getAttribute("columns") );
			var first = Number( elem.getAttribute("first") );
			var second = Number( elem.getAttribute("second") );

			// Get the list of children:
			for(var i = 0, l = elem.childNodes.length; i < l; i ++){
				var node = elem.childNodes[i];
				if (node.nodeName === "QuadField") {
					dev.DataBinding.bindField( theThis, dataObject, node, 1);
					dev.DataBinding.bindField( theThis, dataObject, node, 2);
					dev.DataBinding.bindField( theThis, dataObject, node, 3);
					dev.DataBinding.bindField( theThis, dataObject, node, 4);
				} else if (node.nodeName === "TripleField") {
					dev.DataBinding.bindField( theThis, dataObject, node, 1);
					dev.DataBinding.bindField( theThis, dataObject, node, 2);
					dev.DataBinding.bindField( theThis, dataObject, node, 3);
				} else if (node.nodeName === "DoubleField") {
					dev.DataBinding.bindField( theThis, dataObject, node, 1);
					dev.DataBinding.bindField( theThis, dataObject, node, 2);
				} else if(node.nodeName === "SpanField"){
					dev.DataBinding.bindField( theThis, dataObject, node, 1);
				} else if(node.nodeName === "DoubleCheck"){
					dev.Statics.addCheckboxes(theThis, parent, first,
						node.getAttribute("varName1"),
						node.getAttribute("label1"),
						node.getAttribute("varName2"),
						node.getAttribute("label2") );

                        // Set read only state:
                    	dev.DataBinding.setReadOnly(theThis, node, "readOnly1", "varName1");
                		dev.DataBinding.setReadOnly(theThis, node, "readOnly2", "varName2");
				} else if(node.nodeName === "DoubleCheck2"){
					theThis.warn("bindFieldArea - DoubleCheck2 - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "QuadCheck"){
					theThis.warn("bindFieldArea - QuadCheck - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "SingleCheck"){
					theThis.warn("bindFieldArea - SingleCheck - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "RadioGroup2"){
					theThis.warn("bindFieldArea - RadioGroup2 - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "RadioGroup3"){
					theThis.warn("bindFieldArea - RadioGroup3 - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "RadioGroup4"){
					theThis.warn("bindFieldArea - RadioGroup4 - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "RadioGroup5"){
					theThis.warn("bindFieldArea - RadioGroup5 - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "LongLabel"){
					theThis.warn("bindFieldArea - LongLabel - not implemented yet.  Step on it!"); return;
				} else if(node.nodeName === "LongLabelRich"){
					theThis.warn("bindFieldArea - LongLabelRich - not implemented yet.  Step on it!"); return;
				}
			}

			// A field area creates multiple children.  return null
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
					theThis.error("Unknown attribute (" + name + ") in layout element (" + elem.nodeName + ")" );
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

		processChildren : function ( theThis, dataObject, elem ){
			for(var i = 0, l = elem.childNodes.length; i < l; i++){
				var node = elem.childNodes[i];
				dev.DataBinding.bindElementAndChildren( theThis, dataObject, node );
			}
		}
	}
});
