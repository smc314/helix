/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Class.define("dev.LayoutEngine", {

	type : "static",

	statics : {

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
			var obj = dev.LayoutEngine.createElementAndChildren( theThis, elem, parent );

			if((parent) && (obj) && (parent !== obj)){
				var flex = dev.LayoutEngine.getFlexAttr(elem);
				if(flex){
					parent.add(obj, {flex: flex});
				} else {
					parent.add(obj);
				}
			}
			return obj;
		},

		/** This method combines the loadxml call with the call to renderLayout
		  * as a convienence.
		  */
		loadRenderLayout : function ( theThis, docURL, parent, callback ){

			dev.Api.LoadXMLDoc( docURL,
			function(response){
				var obj = dev.LayoutEngine.renderLayout( theThis, response, parent);
				callback.call(theThis, response.ownerDocument, obj);
			}, theThis );

		},


		/** This method will create the object that represents the current node and
		  * then recursively call ourselves for all child nodes found.
		  */
		createElementAndChildren : function (theThis, elem, parent) {

			if(elem.nodeName === "VerticalBoxLayout"){
				return dev.LayoutEngine.createVBox( theThis, elem, parent );
			} else if(elem.nodeName === "HorizontalBoxLayout"){
				return dev.LayoutEngine.createHBox( theThis, elem, parent );
			} else if(elem.nodeName === "VerticalSplitPane") {
				return dev.LayoutEngine.createVerticalSplitPane( theThis, elem, parent );
			} else if(elem.nodeName === "GroupBox") {
				return dev.LayoutEngine.createGroupBox( theThis, elem, parent );
			} else if(elem.nodeName === "Tree" ) {
				return dev.LayoutEngine.createTree( theThis, elem, parent );
			} else if(elem.nodeName === "TreeVirtual" ) {
				return dev.LayoutEngine.createTreeVirtual( theThis, elem, parent );
			} else if(elem.nodeName === "RecursiveCheckBoxTree" ) {
				return dev.LayoutEngine.createRecursiveCheckBoxTree( theThis, elem, parent );
			} else if(elem.nodeName === "HorizontalSplitPane") {
				return dev.LayoutEngine.createHorizontalSplitPane( theThis, elem, parent );
			} else if(elem.nodeName === "TextArea") {
				return dev.LayoutEngine.createTextArea( theThis, elem, parent );
			} else if(elem.nodeName === "HtmlEmbed") {
				return dev.LayoutEngine.createHtmlEmbed( theThis, elem, parent );
			} else if(elem.nodeName === "IFrame") {
				return dev.LayoutEngine.createIFrame( theThis, elem, parent );
			} else if(elem.nodeName === "StandardTable") {
				return dev.LayoutEngine.createStandardTable( theThis, elem, parent );
			} else if(elem.nodeName === "StandardTreeVirtual") {
				return dev.LayoutEngine.createStandardTreeVirtual( theThis, elem, parent );
			} else if(elem.nodeName === "FieldArea") {
				return dev.LayoutEngine.createFieldArea( theThis, elem, parent );
			} else if(elem.nodeName === "Label") {
				return dev.LayoutEngine.createLabel( theThis, elem, parent );
			} else if(elem.nodeName === "Spacer") {
				return dev.LayoutEngine.createSpacer( theThis, elem, parent );
			} else if(elem.nodeName === "List") {
				return dev.LayoutEngine.createList( theThis, elem, parent );
			} else if(elem.nodeName === "Button") {
				return dev.LayoutEngine.createButton( theThis, elem, parent );
			} else if(elem.nodeName === "LayoutEngine") {
				dev.LayoutEngine.processChildren( theThis, elem, parent);
				return null;
			} else {
				return null;
			}
		},

		createVBox : function ( theThis, elem, parent ) {
			var obj = new qx.ui.container.Composite(new qx.ui.layout.VBox);
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			dev.LayoutEngine.processChildren( theThis, elem, obj );
			return obj;
		},

		createHBox : function ( theThis, elem, parent ) {
			var obj = new qx.ui.container.Composite(new qx.ui.layout.HBox);
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			dev.LayoutEngine.processChildren( theThis, elem, obj );
			return obj;
		},

		createGroupBox : function ( theThis, elem, parent ) {

			if(elem.getAttribute( "isCheck") && elem.getAttribute("isCheck") === "true"){
				var obj = new qx.ui.groupbox.CheckGroupBox();
			} else if(elem.getAttribute( "isRadio") && elem.getAttribute("isRadio") === "true"){
				var obj = new qx.ui.groupbox.RadioGroupBox();
			} else {
				var obj = new qx.ui.groupbox.GroupBox();
			}

			obj.setLayout(new qx.ui.layout.VBox);
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			dev.LayoutEngine.processChildren( theThis, elem, obj );
			return obj;
		},

		createLabel : function ( theThis, elem, parent ) {
			var obj = new qx.ui.basic.Label;
			dev.Statics.trackExtraObj( theThis, obj);
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
		},

		createSpacer : function ( theThis, elem, parent ) {
			var obj = new qx.ui.core.Spacer;
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
		},

		createList : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.List;
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
		},

		createButton : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.Button();
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			return obj;
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
			dev.LayoutEngine.processAttributes( theThis, elem, obj );

			// A split-pane has only 2 children.  Process them by hand:
			if(orientation === "vertical"){
				var firstHalf = dev.Statics.xmlFindChild(elem, "VerticalSplitPaneTop" );
			} else {
				var firstHalf = dev.Statics.xmlFindChild(elem, "HorizontalSplitPaneLeft");
			}
			// find the first real child of VerticalSplitPaneTop
			for(var i = 0, l = firstHalf.childNodes.length; i < l; i++){
				var node = firstHalf.childNodes[i];
				var child = dev.LayoutEngine.createElementAndChildren( theThis, node, obj );
				if(child){
					obj.add(child, flex1);
					break;
				}
			}

			if(orientation === "vertical"){
				var secondHalf = dev.Statics.xmlFindChild(elem, "VerticalSplitPaneBottom" );
			} else {
				var secondHalf = dev.Statics.xmlFindChild(elem, "HorizontalSplitPaneRight" );
			}
			// find the first real child of VerticalSplitPaneBottom
			for(var i = 0, l = secondHalf.childNodes.length; i < l; i++){
				var node = secondHalf.childNodes[i];
				var child = dev.LayoutEngine.createElementAndChildren( theThis, node, obj );
				if(child){
					obj.add(child, flex2);
					break;
				}
			}

			return obj;
		},

		createVerticalSplitPane : function ( theThis, elem, parent ) {
			return dev.LayoutEngine.createSplitPane( theThis, elem, parent, "vertical" );
		},

		createHorizontalSplitPane : function ( theThis, elem, parent ) {
			return dev.LayoutEngine.createSplitPane( theThis, elem, parent, "horizontal" );
		},

		createTreeVirtual : function ( theThis, elem, parent ) {
			// first pull out the column list:
			var columns = elem.getElementsByTagName( "Column" );
			var titles = [];
			for(var i = 0, l = columns.length; i < l; i++){
				titles.push( columns[i].getAttribute("title") );
			}

			var obj = dev.Statics.createStandardTreeVirtual( titles );
			dev.LayoutEngine.processAttributes( theThis, elem, obj );

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

		createTree : function ( theThis, elem, parent ) {
			var obj = new qx.ui.tree.Tree();
			dev.LayoutEngine.processAttributes( theThis, elem, obj );

			// A tree has no children.
			return obj;
		},

		createRecursiveCheckBoxTree : function ( theThis, elem, parent ) {
			// first pull out the column list:
			// A tree has no children.
			return null;
		},

		createTextArea : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.TextArea;
			obj.setNativeContextMenu( true );
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			// a text area has no children.
			return obj;
		},

		createHtmlEmbed : function ( theThis, elem, parent ){
			var obj = new qx.ui.embed.Html;
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			obj.setOverflow("auto", "auto");
			// an html embed has no children.
			return obj;
		},

		createIFrame : function ( theThis, elem, parent ){
			var obj = new qx.ui.embed.Iframe().set({decorator: null});
			dev.LayoutEngine.processAttributes( theThis, elem, obj );
			// an iframe embed has no children.
			return obj;
		},

		createStandardTable : function ( theThis, elem, parent ) {
			// first pull out the column list:
			var columns = elem.getElementsByTagName( "Column" );
			var titles = [];
			for(var i = 0, l = columns.length; i < l; i++){
				titles.push( columns[i].getAttribute("title") );
			}

			var filtered = "false";
			if(elem.getAttribute( "filtered" )){
				filtered = elem.getAttribute("filtered");
			}

			var obj = dev.Statics.createStandardTable( titles, filtered );
			dev.LayoutEngine.processAttributes( theThis, elem, obj );

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

		createStandardTreeVirtual: function ( theThis, elem, parent ) {
			// first pull out the column list:
			var columns = elem.getElementsByTagName( "Column" );
			var titles = [];
			for(var i = 0, l = columns.length; i < l; i++){
				titles.push( columns[i].getAttribute("title") );
			}

			var obj = dev.Statics.createStandardTreeVirtual( titles );
			dev.LayoutEngine.processAttributes( theThis, elem, obj );

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

		addToolTip : function (theThis, node, tipAttr, varAttr) {

			var tipText = node.getAttribute(tipAttr);
			if(tipText){
				var obj = theThis[ node.getAttribute(varAttr) ];
				if(tipText.indexOf("<br") != -1 ||
					tipText.indexOf("<p>") != -1
				){
					// Tip contains some html markup.  Use a rich tip.
					var tip = new qx.ui.tooltip.ToolTip(tipText);
					tip.setRich(true);
					obj.setToolTip( tip );

				} else {
					// Tip is simple text:
					obj.setToolTipText( tipText );
				}

			}
		},

        setReadOnly : function (theThis, node, roAttr, varAttr) {
            var roText = node.getAttribute(roAttr);
            if(roText){
                var obj = theThis[ node.getAttribute(varAttr) ];
				obj.setReadOnly( roText == "true" ? true : false );
			}
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

		createFieldArea : function ( theThis, elem, parent ) {
			//var cols = Number( elem.getAttribute("columns") );
			var first = Number( elem.getAttribute("first") );
			var second = Number( elem.getAttribute("second") );

			// Get the list of children:
			for(var i = 0, l = elem.childNodes.length; i < l; i ++){
				var node = elem.childNodes[i];
				if (node.nodeName === "QuadField") {
					dev.Statics.addFieldsToForm(theThis, parent,
						node.getAttribute("label1"), first,
						node.getAttribute("varName1"),
						node.getAttribute("type1"),
						node.getAttribute("label2"), second,
						node.getAttribute("varName2"),
						node.getAttribute("type2"),
						node.getAttribute("label3"), first,
						node.getAttribute("varName3"),
						node.getAttribute("type3"),
						node.getAttribute("label4"), second,
						node.getAttribute("varName4"),
						node.getAttribute("type4"));
					// Check for tooltips:
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip1", "varName1");
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip2", "varName2");
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip3", "varName3");
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip4", "varName4");
                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly3", "varName3");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly4", "varName4");
					// Check for field verification
					dev.LayoutEngine.checkFieldVerification(theThis, node);
				} else if (node.nodeName === "TripleField") {
					dev.Statics.addFieldsToForm(theThis, parent,
						node.getAttribute("label1"), first,
						node.getAttribute("varName1"),
						node.getAttribute("type1"),
						node.getAttribute("label2"), second,
						node.getAttribute("varName2"),
						node.getAttribute("type2"),
						node.getAttribute("label3"), first,
						node.getAttribute("varName3"),
						node.getAttribute("type3"));
					// Check for tooltips:
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip1", "varName1");
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip2", "varName2");
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip3", "varName3");
                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly3", "varName3");
					// Check for field verification
					dev.LayoutEngine.checkFieldVerification(theThis, node);
				} else if (node.nodeName === "DoubleField") {
					dev.Statics.addFieldsToForm(theThis, parent,
						node.getAttribute("label1"), first,
						node.getAttribute("varName1"),
						node.getAttribute("type1"),
						node.getAttribute("label2"), second,
						node.getAttribute("varName2"),
						node.getAttribute("type2") );
					// Check for tooltips:
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip1", "varName1");
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip2", "varName2");
                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
					// Check for field verification
					dev.LayoutEngine.checkFieldVerification(theThis, node);
				} else if(node.nodeName === "SpanField"){
					dev.Statics.addFieldsToForm(theThis, parent,
						node.getAttribute("label1"), first,
						node.getAttribute("varName1"),
						node.getAttribute("type1") );
					// Check for tooltips:
					dev.LayoutEngine.addToolTip(theThis, node, "tooltip1", "varName1");
                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					if(node.getAttribute("type1") === "TextArea" && node.getAttribute("height1")){
						theThis[node.getAttribute("varName1")].setMaxHeight(
							Number( node.getAttribute("height1") )
						);
						theThis[node.getAttribute("varName1")].setHeight(
							Number( node.getAttribute("height1") )
						);
					}
					// Check for field verification
					dev.LayoutEngine.checkFieldVerification(theThis, node);
				} else if(node.nodeName === "DoubleCheck"){
					dev.Statics.addCheckboxes(theThis, parent, first,
						node.getAttribute("varName1"),
						node.getAttribute("label1"),
						node.getAttribute("varName2"),
						node.getAttribute("label2") );

                        // Set read only state:
                    	dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
                		dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
				} else if(node.nodeName === "DoubleCheck2"){
					dev.Statics.addCheckboxes2(theThis, parent, first,
						Number( node.getAttribute("width1")),
						Number( node.getAttribute("width2")),
						0,
						0,
						node.getAttribute("varName1"),
						node.getAttribute("label1"),
						node.getAttribute("varName2"),
						node.getAttribute("label2") );

                        // Set read only state:
    					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
    					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
				} else if(node.nodeName === "QuadCheck"){
					dev.Statics.addCheckboxes2(theThis, parent, first,
						Number( node.getAttribute("width1")),
						Number( node.getAttribute("width2")),
						Number( node.getAttribute("width3")),
						Number( node.getAttribute("width4")),
						node.getAttribute("varName1"),
						node.getAttribute("label1"),
						node.getAttribute("varName2"),
						node.getAttribute("label2"),
						node.getAttribute("varName3"),
						node.getAttribute("label3"),
						node.getAttribute("varName4"),
						node.getAttribute("label4")
					);

                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly3", "varName3");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly4", "varName4");
				} else if(node.nodeName === "SingleCheck"){
					dev.Statics.addCheckboxes(theThis, parent, first,
						node.getAttribute("varName1"),
						node.getAttribute("label1") );

                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
				} else if(node.nodeName === "RadioGroup2"){
					var rg = dev.Statics.addRadioGroupVertical(theThis, parent, first,
						node.getAttribute("varName1"),
						node.getAttribute("label1") ,
						node.getAttribute("varName2"),
						node.getAttribute("label2")
					);
					theThis[ node.getAttribute("groupName") ] = rg;

                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
				} else if(node.nodeName === "RadioGroup3"){
					var rg = dev.Statics.addRadioGroupVertical(theThis, parent, first,
						node.getAttribute("varName1"),
						node.getAttribute("label1") ,
						node.getAttribute("varName2"),
						node.getAttribute("label2"),
						node.getAttribute("varName3"),
						node.getAttribute("label3")
					);
					theThis[ node.getAttribute("groupName") ] = rg;

                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
                    dev.LayoutEngine.setReadOnly(theThis, node, "readOnly3", "varName3");
				} else if(node.nodeName === "RadioGroup4"){
					var rg = dev.Statics.addRadioGroupVertical(theThis, parent, first,
						node.getAttribute("varName1"),
						node.getAttribute("label1") ,
						node.getAttribute("varName2"),
						node.getAttribute("label2"),
						node.getAttribute("varName3"),
						node.getAttribute("label3") ,
						node.getAttribute("varName4"),
						node.getAttribute("label4")
					);
					theThis[ node.getAttribute("groupName") ] = rg;

                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
                    dev.LayoutEngine.setReadOnly(theThis, node, "readOnly3", "varName3");
                    dev.LayoutEngine.setReadOnly(theThis, node, "readOnly4", "varName4");
				} else if(node.nodeName === "RadioGroup5"){
					var rg = dev.Statics.addRadioGroupHorizontal(theThis, parent, first,
						null, // groupName is not used
						node.getAttribute("labelPrefix"),
						node.getAttribute("varName1"), node.getAttribute("label1") ,
						node.getAttribute("varName2"), node.getAttribute("label2"),
						node.getAttribute("varName3"), node.getAttribute("label3") ,
						node.getAttribute("varName4"), node.getAttribute("label4")
					);
					theThis[ node.getAttribute("groupName") ] = rg;

                    // Set read only state:
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly1", "varName1");
					dev.LayoutEngine.setReadOnly(theThis, node, "readOnly2", "varName2");
                    dev.LayoutEngine.setReadOnly(theThis, node, "readOnly3", "varName3");
                    dev.LayoutEngine.setReadOnly(theThis, node, "readOnly4", "varName4");
				} else if(node.nodeName === "LongLabel"){
					dev.Statics.addLongLabel(parent,
						node.getAttribute("label"),
						node.getAttribute("varName"),
						theThis);
				} else if(node.nodeName === "LongLabelRich"){
					dev.Statics.addLongLabelRich(parent,
						node.getAttribute("label"),
						node.getAttribute("varName"),
						theThis);
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

		processChildren : function ( theThis, elem, obj ){
			for(var i = 0, l = elem.childNodes.length; i < l; i++){
				var node = elem.childNodes[i];
				var child = dev.LayoutEngine.createElementAndChildren( theThis, node, obj );
				if(child){
					var flex_num = dev.LayoutEngine.getFlexAttr(node);
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
