/* ************************************************************************

   Copyright:  Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */
qx.Mixin.define("admin.layout.LayoutCKTextArea", {

	members : {

		createCKTextArea : function ( theThis, elem, parent ) {
			var obj = new qx.ui.form.TextArea;
			obj.setNativeContextMenu( true );
			this.processAttributes( theThis, elem, obj );

			// Now create the CKEditor overlay for the text area:
			obj.addListenerOnce( "appear", function(e) {
				var domElement = obj.getContentElement().getDomElement();
				var hint = obj.getBounds();
				var ckField = CKEDITOR.replace(domElement,
					{
						height : hint.height - 100,
						width : hint.width,
						resize_enabled : false,
						tabIndex : obj.getTabIndex(),
						toolbar : 'Standard'
					}
				);
				// If the owner object has a dirty flag, and supports fieldModification
				// notifications, then go ahead and subscribe to change events:
				if(theThis.isDirty !== undefined && theThis.fieldModified !== undefined){
					ckField.helixOwner = theThis;
					ckField.on("change", function() {
						this.helixOwner.fieldModified();
					} );
				}
				theThis[ elem.getAttribute("varName") + "CK" ] = ckField;
			}, theThis );

			// a text area has no children.
			return obj;
		}

	}
});
