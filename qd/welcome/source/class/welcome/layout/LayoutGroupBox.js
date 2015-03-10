/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("welcome.layout.LayoutGroupBox", {

	members : {

		createGroupBox: function ( theThis, elem, parent ) {
			if(elem.getAttribute( "isCheck") && elem.getAttribute("isCheck") === "true"){
				var obj = new qx.ui.groupbox.CheckGroupBox();
			} else if(elem.getAttribute( "isRadio") && elem.getAttribute("isRadio") === "true"){
				var obj = new qx.ui.groupbox.RadioGroupBox();
			} else {
				var obj = new qx.ui.groupbox.GroupBox();
			}

			obj.setLayout(new qx.ui.layout.VBox);
			this.processAttributes( theThis, elem, obj );
			this.processChildren( theThis, elem, obj );
			return obj;
		}

	}
});
