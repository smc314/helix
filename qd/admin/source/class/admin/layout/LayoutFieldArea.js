/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutFieldArea", {

	members : {

		/** A FieldArea isn't really a widget per se. It's more a collection of fields
		  * that share common spacing characteristics.  All we do at this level is to
		  * capture the spacing characteristics and persist them in our class for the
		  * child fields to use.
		  */
		createFieldArea: function ( theThis, elem, parent ) {
			this.fieldAreaFirst = Number( elem.getAttribute("first") );
			this.fieldAreaSecond = Number( elem.getAttribute("second") );
			this.fieldAreaThird = Number( elem.getAttribute("third") );
			this.fieldAreaFourth = Number( elem.getAttribute("fourth") );

			// Now process all of our field children
			this.processChildren( theThis, elem, parent );

			// A field area produces multiple children.  return null.
			return null;
		},

		/** Used to add tooltips to widgets within a field area.
		  */
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

		/** Used to set fields in a field area to read-only.
		  */
        setReadOnly : function (theThis, node, roAttr, varAttr) {
            var roText = node.getAttribute(roAttr);
            if(roText){
                var obj = theThis[ node.getAttribute(varAttr) ];
				obj.setReadOnly( roText == "true" ? true : false );
			}
        },

		/** Used to handle field verification for fields in a field area.
		  */
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

		/** Used to load static values for a combo-box within a field area.
		  */
		loadComboValues : function ( theThis, elem, position ) {
			var varName = "varName" + position;
			var typeName = "type" + position;
			var subNodeName = "List" + position + "Value";

			if(elem.getAttribute(typeName) === "ComboBox" ||
				elem.getAttribute(typeName) === "ComboBoxEdit"
			){
				// Check for sub-items that provide static data for the combo-box
				for(var i = 0, l = elem.childNodes.length; i < l; i++){
					var node = elem.childNodes[i];
					if(node.nodeName === subNodeName){
						admin.Statics.addToDropDown( theThis[elem.getAttribute(varName)],
							node.getAttribute( "label" ),
							node.getAttribute( "model" )
						);
					}
				}
			}
		}

	}
});
