/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(PACKAGE/icon/32x32/shadow/sign_warning.png)
#asset(PACKAGE/icon/32x32/shadow/ok.png)
************************************************************************ */
qx.Class.define("PACKAGE.Statics", {

	type: "static",

	statics: {

		/** This function makes it easy to populate a list from XML that has a
		* given format.  Tell us the element Name that you want us to use from the XML
		* document and we will find all instances of that element name in the document,
		* pull out their "name" and "id" attributes, and use those to create the
		* list items.
		*
		* @param list {Object}
		* @param xmlDoc {Object}
		* @param elementName {Object}
		*/
		populateList: function (list, xmlDoc, elementName) {
			list.removeAll();

			var element_list = xmlDoc.getElementsByTagName(elementName);
			for (var i = 0, l = element_list.length; i < l; i++) {
				var opt = new qx.ui.form.ListItem(
					element_list[i].getAttribute("name"),
					null,
					element_list[i].getAttribute("id")
				);
				list.add(opt);
			}
		},

		/** This function makes it easy to populate a list from an array of data objects.
		* Tell us the names of the two getter functions we should use to get the label
		* and the value and we'll pull everything out of the array of objects.
		*
		* @param list {Object}
		* @param ary {Object} data object array
		* @param labelGetter {Object} label getter name
		* @param valueGetter {Object} value getter name
		*/
		populateListFromArray: function (list, ary, labelGetter, valueGetter) {
			list.removeAll();

			for (var i = 0, l = ary.length; i < l; i++) {
				var opt = new qx.ui.form.ListItem(
					ary[i][labelGetter](),
					null,
					String(ary[i][valueGetter]())
				);
				list.add(opt);
			}
		},

		/** This function makes it easy to add a static item to a drop down list.
		*
		* @param dropDown {Object}
		* @param itemName {Object}
		* @param itemID {Object}
		*/
		addToDropDown: function (dropDown, itemName, itemID
		) {
			var item = new qx.ui.form.ListItem(itemName, null, itemID);
			dropDown.add(item);

		},

		/** This function makes it easy to populate a dropdown from XML that has a
		* given format.  Tell us the element Name that you want us to use from the XML
		* document and we will find all instances of that element name in the document,
		* pull out their "name" and "id" attributes, and use those to create the drop
		* down list items.
		*
		* @param dropDown {Object}
		* @param xmlDoc {Object}
		* @param elementName {Object}
		*/
		populateDropDown: function (dropDown, xmlDoc, elementName,
			addEmptyItem, autoSelectItem
		) {
			dropDown.removeAll();
			if (addEmptyItem) {
				var empty = new qx.ui.form.ListItem(addEmptyItem, null, addEmptyItem);
				dropDown.add(empty);
			}

			var element_list = xmlDoc.getElementsByTagName(elementName);
			for (var i = 0, l = element_list.length; i < l; i++) {
				var opt = new qx.ui.form.ListItem(
					element_list[i].getAttribute("name"),
					null,
					element_list[i].getAttribute("id")
				);
				dropDown.add(opt);
			}

			if (autoSelectItem !== undefined) {
				PACKAGE.Statics.selectDropDownIndex(dropDown, autoSelectItem);
			}

		},

		/** This function makes it easy to populate a dropdown from XML that has a
		* given format.  Tell us the element Name that you want us to use from the XML
		* document and we will find all instances of that element name in the document,
		* pull out their "name" and "id" attributes, and use those to create the drop
		* down list items.
		*
		* @param dropDown {Object}
		* @param xmlDoc {Object}
		* @param elementName {Object}
		*/
		populateDropDownNoName: function (dropDown, xmlDoc, elementName,
			addEmptyItem, autoSelectItem
		) {
			dropDown.removeAll();
			if (addEmptyItem) {
				var empty = new qx.ui.form.ListItem(addEmptyItem, null, addEmptyItem);
				dropDown.add(empty);
			}

			var element_list = xmlDoc.getElementsByTagName(elementName);
			for (var i = 0, l = element_list.length; i < l; i++) {
				var opt = new qx.ui.form.ListItem(
					element_list[i].getAttribute("id"),
					null,
					element_list[i].getAttribute("id")
				);
				dropDown.add(opt);
			}

			if (autoSelectItem !== undefined) {
				PACKAGE.Statics.selectDropDownIndex(dropDown, autoSelectItem);
			}

		},

		/** This function allows you to select a value in a drop down, based on it's
		* index number into the child array of the parent dropdown.
		*
		* @param dropDown {Object}
		* @param index {Integer}
		*/
		selectDropDownIndex: function (dropDown, index) {
			var list = dropDown.getChildControl("list");
			if (list.getChildren().length > index) {
				list.setSelection([list.getChildren()[index]]);
			} else {
				dropDown.warn("Tried to select an index greater than dropDown size.");
			}
		},

		/** This function makes it easy to populate a dropdown from another
		* dropdown that shares the same list of choices.
		*
		* @param source {Object}
		* @param target {Object}
		*/
		copyDropDown: function (source, target) {
			target.removeAll();
			var source_children = source.getChildControl("list").getChildren();
			for (var i = 0, l = source_children.length; i < l; i++) {
				var opt = new qx.ui.form.ListItem(
					source_children[i].getLabel().toString(),
					null,
					source_children[i].getModel()
				);
				target.add(opt);
			}
		},

		/** If you hold data in a drop-down for future look-ups outside of
		* the drop-down, then this will allow you to look up a text label
		* based on the value of the text in the drop down.
		*/
		getTextByValue: function (dropDown, value) {
			if (!dropDown || !value) {
				return "";
			}
			var li = PACKAGE.Statics.findListItem(dropDown.getChildControl("list"), value);
			if (li === null) {
				return "";
			} else {
				return li.getLabel();
			}
		},

		/** This function replaces the old findItem() method that used to exist on
		*  a list, and will search the list by Model value rather than by label.
		*/
		findListItem: function (list, modelvalue) {
			var li = null;
			// get all items of the list
			var items = list.getChildren();

			// go through all items
			for (var i = 0, l = items.length; i < l; i++) {
				// get the label of the current item
				var currentValue = items[i].getModel();

				// if the label fits with the search text
				if (currentValue &&
					currentValue.indexOf(modelvalue) == 0 &&
					currentValue.length == modelvalue.length
				) {
					// just return the first found element
					li = items[i];
					break;
				}
			}
			return li;
		},

		/** This function will search the list by Label rather than by Model value.
		*/
		findListItemByLabel: function (list, labelvalue) {
			return list.findItem(labelvalue);
		},

		/** This function will take the given value and find it in the current drop
		* down list.  If found, it will set the dropdown to have that item selected.
		* If not found, this will make no changes to the dropdown selection.
		*
		* @param dropDown {Object}
		* @param value {Object}
		*/
		setDropDownByValue: function (dropDown, value) {
			if (!dropDown || !value) {
				return;
			}
			var list = dropDown.getChildControl("list");
			var li = PACKAGE.Statics.findListItem(list, value);

			// if no element was found, do nothing.
			if (li === null) {
				return;
			} else {
				list.setSelection([li]);
			}
		},

		/** This function will take the given label and find it in the current drop
		* down list.  If found, it will set the dropdown to have that item selected.
		* If not found, this will make no changes to the dropdown selection.
		*
		* @param dropDown {Object}
		* @param label {Object}
		*/
		setDropDownByLabel: function (dropDown, label) {
			if (!dropDown || !label) {
				return;
			}
			var list = dropDown.getChildControl("list");
			var li = PACKAGE.Statics.findListItemByLabel(list, label);

			// if no element was found, do nothing.
			if (li === null) {
				return;
			} else {
				list.setSelection([li]);
			}
		},


		/** This function will take the given label and find it in the current combo-box
		* If found, it will set the combo-box to have that item selected.
		* If not found, this will add a new item to the combo box and then set that as the
		* selected item
		*
		* @param dropDown {Object}
		* @param label {Object}
		*/
		setComboByLabelWithAdd: function (dropDown, label) {
			if (!dropDown || !label) {
				return;
			}
			var list = dropDown.getChildControl("list");
			var li = PACKAGE.Statics.findListItemByLabel(list, label);

			if (li === null) {
				// if no element was found, add it in as a new item in the list:
				dropDown.add(new qx.ui.form.ListItem(label, null, label));
				var item = list.findItem(label); // value and label are the same now
				list.setSelection([item]);
			} else {
				list.setSelection([li]);
			}
		},

		/** Used to check a drop down to see if has no or empty selection.
		*/
		isDropDownUnSelected: function (dropDown) {
			var list = dropDown.getChildControl("list");

			if (list.isSelectionEmpty()) {
				return true;
			}
			if (!list.getSelection()[0].getModel()) {
				return true;
			}
			if (list.getSelection()[0].getModel().length === 0) {
				return true;
			}
			if (list.getSelection()[0].getModel() === "0") {
				return true;
			}
		},

		getDDSelectedValue: function (dropDown) {
			if (PACKAGE.Statics.isDropDownUnSelected(dropDown)) {
				return null;
			}
			return dropDown.getSelection()[0].getModel();
		},

		getDDSelectedLabel: function (dropDown) {
			if (PACKAGE.Statics.isDropDownUnSelected(dropDown)) {
				return null;
			}
			return dropDown.getSelection()[0].getLabel();
		},

		setDropDownReadOnly: function (dropDown, tf) {
			dropDown.getChildControl("textfield").setReadOnly(tf);
		},

		/** This method will recursively search the ui tree to find the
		* parent of the given child that has the specified parentType.
		* When you call this method, do not put the parentType value
		* in quotes.  Do it like this:
		* <pre>
		var parent = PACKAGE.Statics.findQXParent( child, qx.ui.table.Table );
		* </pre>
		*/
		findQXParent: function (child, parentType) {
			if (!child.getLayoutParent) {
				return null;
			}
			var parent = child.getLayoutParent();
			if (parent === null) {
				return null;
			}
			if (parent instanceof parentType) {
				return parent;
			} else {
				return PACKAGE.Statics.findQXParent(parent, parentType);
			}
		},


		/** This uses the qx.xml.Document.fromString method to
		* parse the string and return it as an XML document.
		*/
		xmlStringToDoc: function (xml_string) {
			return qx.xml.Document.fromString(xml_string);
		},

		/** Finds the first child of the given element that has the
		* node name that is requested.
		*/
		xmlFindChild: function (elem, childName) {
			if (!elem) {
				return null;
			}
			for (var i = 0, l = elem.childNodes.length; i < l; i++) {
				var node = elem.childNodes[i];
				if (node.nodeName === childName) {
					return node;
				}
			}
			return null;
		},

		/** Finds the first child of the given element that has the
		* node name that is requested along with an attribute with the given
		* value.
		*/
		xmlFindChildWithAttr: function (elem, childName, attrName, attrValue) {
			if (!elem) {
				return null;
			}
			for (var i = 0, l = elem.childNodes.length; i < l; i++) {
				var node = elem.childNodes[i];
				if (node.nodeName === childName) {
					if(node.hasAttribute( attrName ) && (node.getAttribute( attrName ) == attrValue) ){
						return node;
					}
				}
			}
			return null;
		},

		/** This uses different methods (IE vs. mozilla et. al.) to
		* convert the given xml document into a string.
		*/
		xmlDocToString: function (xml_doc) {
			return qx.xml.Element.serialize(xml_doc);
		},

		/** This will get the contents of the text node that we find as either
		  * the given node, or a child of the given node.
		  */
		xmlGetText : function(elem) {
			if(elem === null || elem === undefined){
				return "";
			}
			if(elem.nodeType === 3){ // 3 = TEXT_NODE
				// they've handed us the text node directly.  Just return the contents
				return elem.nodeValue;
			} else {
				// Walk the children to find the TEXT child
				for(var i = 0, l = elem.childNodes.length; i < l; i++){
					var node = elem.childNodes[i];
					if(node.nodeType === 3){ // 3 = TEXT_NODE
						// this is the one.
						return node.nodeValue;
					}
				}
			}
			// Didn't find it.
			return "";
		},

		/** This will set the contents text node as a child of the given
		  * parent node.
		  */
		xmlSetText : function(parent, contents) {
			var doc = parent.ownerDocument;
			var text = doc.createTextNode( contents );
			parent.appendChild(text);
		},

		/** This will get the contents of the CDATA section that we find as either
		  * the given node, or a child of the given node.
		  */
		xmlGetCDATASection : function(elem) {
			if(elem === null || elem === undefined){
				return "";
			}
			if(elem.nodeType === 4){ // 4 = CDATA_SECTION_NODE
				// they've handed us the CDATA node directly.  Just return the contents
				return elem.nodeValue;
			} else {
				// Walk the children to find the CDATA child
				for(var i = 0, l = elem.childNodes.length; i < l; i++){
					var node = elem.childNodes[i];
					if(node.nodeType === 4){ // 4 = CDATA_SECTION_NODE
						// this is the one.
						return node.nodeValue;
					}
				}
			}
			// Didn't find it.
			return "";
		},

		/** This will set the contents into a CDATA section as a child of the given
		  * parent node.
		  */
		xmlSetCDATASection : function(parent, contents) {
			var doc = parent.ownerDocument;
			var cdata = doc.createCDATASection( contents );
			parent.appendChild(cdata);
		},

		/** This will get the contents of the CDATA section and base64 decode them
		  * before returning.
		  */
		xmlGetBase64 : function(elem) {
			var b64 = PACKAGE.Statics.xmlGetCDATASection( elem );
			return PACKAGE.Statics.decode64( b64 );
		},

		/** This will set the contens of a CDATA section with the base64 encoded
		  * version of the given input.
		  */
		xmlSetBase64 : function(parent, contents){
			var b64 = PACKAGE.Statics.encode64( contents );
			PACKAGE.Statics.xmlSetCDATASection( parent, b64 );
		},

		/** This will check our standard xml response document to see if a filter
		  * has been applied.  We check the node given (should be the root node)
		  * for an attribute called "filtered" with a value of "true".  If we
		  * find it, we'll return true.  If not, we'll return false.
		  */
		isResponseFiltered : function(response) {
			if(response === null || response === undefined){
				return false;
			}
			if( response.getAttribute("filtered") === "true" ){
				return true;
			} else {
				return false;
			}
		},

		/** This function can be used by anyone who needs to set the
		* overflow:"auto" for the firefox bug.
		*/
		setOverflow: function (widget) {
			if (!qx.core.Environment.get("qx.client") === "mshtml") {
				widget.set({ overflow: "auto" });
			}
		},

		/** This function can be used by anyone who needs to set the
		*   html id attribute to a predictable value at runtime.  Very usefule
		*   for automated UI testing.
		*/
		setHtmlID : function (widget, varName) {
			widget.htmlid = widget.classname + "." + varName;
			widget.addListenerOnce( "appear", function(e) {
				this.getContentElement().getDomElement().id = this.htmlid;
			}, widget );
		},

		/** This method helps us with form field layouts.  The idea is that
		* the form is a vertical box layout.  Each row is either one or
		* two fields (with labels) laid out in a horizontal box layout.
		*/
		addFieldsToForm: function (theThis, layout,
			label1Name, label1Size, field1Name, field1Type,
			label2Name, label2Size, field2Name, field2Type,
			label3Name, label3Size, field3Name, field3Type,
			label4Name, label4Size, field4Name, field4Type) {

			var hb = new qx.ui.container.Composite(new qx.ui.layout.HBox());
			hb.set({ paddingTop: 3 });
			hb._getLayout().setAlignY("middle");

			var l1 = new qx.ui.basic.Label(label1Name); PACKAGE.Statics.trackExtraObj(theThis, l1);
			l1.setWidth(label1Size);
			hb.add(l1);

			var f1 = null;
			if (field1Type === "TextField") {
				f1 = new qx.ui.form.TextField;
				f1.setNativeContextMenu( true );
				f1.setWidth(100); // set the preferred width so everything flex's equally
				f1.addListenerOnce( "appear", function( e ) {
					var de = e.getTarget().getContentElement().getDomElement();
					de.setAttribute("autocomplete", "on");
					de.setAttribute("name", field1Name );
				});
			} else if (field1Type === "PasswordField") {
				f1 = new qx.ui.form.PasswordField;
				f1.setNativeContextMenu( true );
				f1.setWidth(100); // set the preferred width so everything flex's equally
			} else if (field1Type === "ComboBox") {
				f1 = new qx.ui.form.SelectBox;
				f1.setWidth(100); // set the preferred width so everything flex's equally
				f1.setMaxListHeight(400);
			} else if (field1Type === "ComboBoxEdit") {
				f1 = new qx.ui.form.ComboBox;
				f1.setNativeContextMenu( true );
				f1.setWidth(100); // set the preferred width so everything flex's equally
			} else if (field1Type === "DateField") {
				f1 = new qx.ui.form.DateField;
				f1.setNativeContextMenu( true );
				f1.setWidth(100); // set the preferred width so everything flex's equally
				f1.setDateFormat( new qx.util.format.DateFormat( "yyyy/MM/dd HH:mm:ss" ) );
			} else if (field1Type === "TextArea") {
				f1 = new qx.ui.form.TextArea;
				f1.setNativeContextMenu( true );
				f1.setMaxHeight(80);
			} else {
				theThis.error("Unknown field type: " + field1Type);
			}
			hb.add(f1, { flex: 1 });
			theThis[field1Name] = f1;
			PACKAGE.Statics.trackNamedAttr(theThis, field1Name);
			PACKAGE.Statics.setHtmlID( f1, field1Name );

			if (label2Name) {
				var l2 = new qx.ui.basic.Label(""); PACKAGE.Statics.trackExtraObj(theThis, l2);
				l2.setWidth(5);
				hb.add(l2);

				var l3 = new qx.ui.basic.Label(label2Name); PACKAGE.Statics.trackExtraObj(theThis, l3);
				l3.setWidth(label2Size);
				hb.add(l3);

				var f2 = null;
				if (field2Type === "TextField") {
					f2 = new qx.ui.form.TextField;
					f2.setNativeContextMenu( true );
					f2.setWidth(100);
					f2.addListenerOnce( "appear", function( e ) {
						var de = e.getTarget().getContentElement().getDomElement();
						de.setAttribute("autocomplete", "on");
						de.setAttribute("name", field2Name );
					});
				} else if (field2Type === "PasswordField") {
					f2 = new qx.ui.form.PasswordField;
					f2.setNativeContextMenu( true );
					f2.setWidth(100);
				} else if (field2Type === "ComboBox") {
					f2 = new qx.ui.form.SelectBox;
					f2.setWidth(100);
					f2.setMaxListHeight(400);
				} else if (field2Type === "ComboBoxEdit") {
					f2 = new qx.ui.form.ComboBox;
					f2.setNativeContextMenu( true );
					f2.setWidth(100);
				} else if (field2Type === "DateField") {
					f2 = new qx.ui.form.DateField;
					f2.setNativeContextMenu( true );
					f2.setWidth(100);
					f2.setDateFormat( new qx.util.format.DateFormat( "yyyy/MM/dd HH:mm:ss" ) );
				} else if (field2Type === "Spacer") {
					f2 = new qx.ui.core.Spacer;
					f2.setWidth(100);
				} else {
					theThis.error("Unknown field type: " + field2Type);
				}
				hb.add(f2, { flex: 1 });
				if (field2Name) {
					theThis[field2Name] = f2;
					PACKAGE.Statics.trackNamedAttr(theThis, field2Name);
					PACKAGE.Statics.setHtmlID( f2, field2Name );
				}
			}

			if (label3Name) {
				var l4 = new qx.ui.basic.Label(""); PACKAGE.Statics.trackExtraObj(theThis, l4);
				l4.setWidth(5);
				hb.add(l4);

				var l5 = new qx.ui.basic.Label(label3Name); PACKAGE.Statics.trackExtraObj(theThis, l5);
				l5.setWidth(label3Size);
				hb.add(l5);

				var f3 = null;
				if (field3Type === "TextField") {
					f3 = new qx.ui.form.TextField;
					f3.setNativeContextMenu( true );
					f3.setWidth(100);
					f3.addListenerOnce( "appear", function( e ) {
						var de = e.getTarget().getContentElement().getDomElement();
						de.setAttribute("autocomplete", "on");
						de.setAttribute("name", field2Name );
					});
				} else if (field3Type === "PasswordField") {
					f3 = new qx.ui.form.PasswordField;
					f3.setNativeContextMenu( true );
					f3.setWidth(100);
				} else if (field3Type === "ComboBox") {
					f3 = new qx.ui.form.SelectBox;
					f3.setWidth(100);
					f3.setMaxListHeight(400);
				} else if (field3Type === "ComboBoxEdit") {
					f3 = new qx.ui.form.ComboBox;
					f3.setNativeContextMenu( true );
					f3.setWidth(100);
				} else if (field3Type === "DateField") {
					f3 = new qx.ui.form.DateField;
					f3.setNativeContextMenu( true );
					f3.setWidth(100);
					f3.setDateFormat( new qx.util.format.DateFormat( "yyyy/MM/dd HH:mm:ss" ) );
				} else if (field3Type === "Spacer") {
					f3 = new qx.ui.core.Spacer;
					f3.setWidth(100);
				} else {
					theThis.error("Unknown field type: " + field3Type);
				}
				hb.add(f3, { flex: 1 });
				if (field3Name) {
					theThis[field3Name] = f3;
					PACKAGE.Statics.trackNamedAttr(theThis, field3Name);
					PACKAGE.Statics.setHtmlID( f3, field3Name );
				}
			}

			if (label4Name) {
				var l6 = new qx.ui.basic.Label(""); PACKAGE.Statics.trackExtraObj(theThis, l6);
				l6.setWidth(5);
				hb.add(l6);

				var l7 = new qx.ui.basic.Label(label4Name); PACKAGE.Statics.trackExtraObj(theThis, l7);
				l7.setWidth(label4Size);
				hb.add(l7);

				var f4 = null;
				if (field4Type === "TextField") {
					f4 = new qx.ui.form.TextField;
					f4.setNativeContextMenu( true );
					f4.setWidth(100);
					f4.addListenerOnce( "appear", function( e ) {
						var de = e.getTarget().getContentElement().getDomElement();
						de.setAttribute("autocomplete", "on");
						de.setAttribute("name", field2Name );
					});
				} else if (field4Type === "PasswordField") {
					f4 = new qx.ui.form.PasswordField;
					f4.setNativeContextMenu( true );
					f4.setWidth(100);
				} else if (field4Type === "ComboBox") {
					f4 = new qx.ui.form.SelectBox;
					f4.setWidth(100);
					f4.setMaxListHeight(400);
				} else if (field4Type === "ComboBoxEdit") {
					f4 = new qx.ui.form.ComboBox;
					f4.setNativeContextMenu( true );
					f4.setWidth(100);
				} else if (field4Type === "DateField") {
					f4 = new qx.ui.form.DateField;
					f4.setNativeContextMenu( true );
					f4.setWidth(100);
					f4.setDateFormat( new qx.util.format.DateFormat( "yyyy/MM/dd HH:mm:ss" ) );
				} else if (field4Type === "Spacer") {
					f4 = new qx.ui.core.Spacer;
					f4.setWidth(100);
				} else {
					theThis.error("Unknown field type: " + field4Type);
				}
				hb.add(f4, { flex: 1 });
				if (field4Name) {
					theThis[field4Name] = f4;
					PACKAGE.Statics.trackNamedAttr(theThis, field4Name);
					PACKAGE.Statics.setHtmlID( f4, field4Name );
				}
			}

			var l8 = new qx.ui.basic.Label(""); PACKAGE.Statics.trackExtraObj(theThis, l8);
			l8.setWidth(2);
			hb.add(l8);

			layout.add(hb);
		},

		/** This method helps us with form field layouts.  The idea is that
		* the form is a vertical box layout.  Each row is either one or
		* two fields (with labels) laid out in a horizontal box layout.
		*/
		addTextFieldsToForm: function (theThis, layout,
			label1Name, label1Size, field1Name, field1Type,
			label2Name, label2Size, field2Name, field2Type,
			label3Name, label3Size, field3Name, field3Type,
			label4Name, label4Size, field4Name, field4Type) {

			var hb = new qx.ui.container.Composite(new qx.ui.layout.HBox());
			hb.set({ paddingTop: 3 });
			hb._getLayout().setAlignY("middle");

			var l1 = new qx.ui.basic.Label(label1Name);
			PACKAGE.Statics.trackExtraObj(theThis, l1);
			l1.setWidth(label1Size);
			hb.add(l1);

			var f1 = null;
			if (field1Type === "TextField") {
				f1 = new qx.ui.form.TextField;
				f1.setNativeContextMenu( true );
				f1.setWidth(50); // set the preferred width so everything flex's equally
				f1.addListenerOnce( "appear", function( e ) {
					var de = e.getTarget().getContentElement().getDomElement();
					de.setAttribute("autocomplete", "on");
					de.setAttribute("name", field1Name );
				});
			} else {
				theThis.error("Unknown field type: " + field1Type);
			}
			hb.add(f1, { flex: 1 });
			theThis[field1Name] = f1;
			PACKAGE.Statics.trackNamedAttr(theThis, field1Name);
			PACKAGE.Statics.setHtmlID( f1, field1Name );

			if (label2Name) {
				var l2 = new qx.ui.basic.Label(""); PACKAGE.Statics.trackExtraObj(theThis, l2);
				l2.setWidth(5);
				hb.add(l2);

				var l3 = new qx.ui.basic.Label(label2Name); PACKAGE.Statics.trackExtraObj(theThis, l3);
				l3.setWidth(label2Size);
				hb.add(l3);

				var f2 = null;
				if (field2Type === "TextField") {
					f2 = new qx.ui.form.TextField;
					f2.setNativeContextMenu( true );
					f2.setWidth(50);
					f2.addListenerOnce( "appear", function( e ) {
						var de = e.getTarget().getContentElement().getDomElement();
						de.setAttribute("autocomplete", "on");
						de.setAttribute("name", field2Name );
					});
				} else if (field2Type === "Spacer") {
					f2 = new qx.ui.core.Spacer;
					f2.setWidth(50);
				} else {
					theThis.error("Unknown field type: " + field2Type);
				}
				hb.add(f2, { flex: 1 });
				if (field2Name) {
					theThis[field2Name] = f2;
					PACKAGE.Statics.trackNamedAttr(theThis, field2Name);
					PACKAGE.Statics.setHtmlID( f2, field2Name );
				}
			}

			if (label3Name) {
				var l2 = new qx.ui.basic.Label(""); PACKAGE.Statics.trackExtraObj(theThis, l2);
				l2.setWidth(5);
				hb.add(l2);

				var l3 = new qx.ui.basic.Label(label3Name); PACKAGE.Statics.trackExtraObj(theThis, l3);
				l3.setWidth(label3Size);
				hb.add(l3);

				var f2 = null;
				if (field3Type === "TextField") {
					f2 = new qx.ui.form.TextField;
					f2.setNativeContextMenu( true );
					f2.setWidth(50);
					f2.addListenerOnce( "appear", function( e ) {
						var de = e.getTarget().getContentElement().getDomElement();
						de.setAttribute("autocomplete", "on");
						de.setAttribute("name", field3Name );
					});
				} else if (field3Type === "Spacer") {
					f2 = new qx.ui.core.Spacer;
					f2.setWidth(50);
				} else {
					theThis.error("Unknown field type: " + field3Type);
				}
				hb.add(f2, { flex: 1 });
				if (field3Name) {
					theThis[field3Name] = f2;
					PACKAGE.Statics.trackNamedAttr(theThis, field3Name);
					PACKAGE.Statics.setHtmlID( f2, field3Name );
				}
			}

			if (label4Name) {
				var l2 = new qx.ui.basic.Label(""); PACKAGE.Statics.trackExtraObj(theThis, l2);
				l2.setWidth(5);
				hb.add(l2);

				var l3 = new qx.ui.basic.Label(label4Name); PACKAGE.Statics.trackExtraObj(theThis, l3);
				l3.setWidth(label4Size);
				hb.add(l3);

				var f2 = null;
				if (field4Type === "TextField") {
					f2 = new qx.ui.form.TextField;
					f2.setNativeContextMenu( true );
					f2.setWidth(50);
					f2.addListenerOnce( "appear", function( e ) {
						var de = e.getTarget().getContentElement().getDomElement();
						de.setAttribute("autocomplete", "on");
						de.setAttribute("name", field4Name );
					});
				} else if (field4Type === "Spacer") {
					f2 = new qx.ui.core.Spacer;
					f2.setWidth(50);
				} else {
					theThis.error("Unknown field type: " + field4Type);
				}
				hb.add(f2, { flex: 1 });
				if (field4Name) {
					theThis[field4Name] = f2;
					PACKAGE.Statics.trackNamedAttr(theThis, field4Name);
					PACKAGE.Statics.setHtmlID( f2, field4Name );
				}
			}

			var l3 = new qx.ui.basic.Label("");
			PACKAGE.Statics.trackExtraObj(theThis, l3);
			l3.setWidth(2);
			hb.add(l3);

			layout.add(hb);
		},

		/** Use this method when you want to add a text area to a form and include
		* a simple label at the top of the text area.  Text area size will be set
		* to fill horizontally and vertically all area that is available.
		*/
		addTextArea: function (theThis, layout, flexHeight, labelText, textName) {
			var l1 = new qx.ui.basic.Label(labelText);
			l1.set({ paddingTop: 3 });
			layout.add(l1);
			var ta = new qx.ui.form.TextArea;
			ta.setNativeContextMenu( true );
			ta.set({ wrap: true });
			ta.setAllowStretchX(true);
			ta.setAllowStretchY(true);
			layout.add(ta, { flex: flexHeight });
			theThis[textName] = ta;
			PACKAGE.Statics.trackNamedAttr(theThis, textName);
			PACKAGE.Statics.setHtmlID( ta, textName );
		},

		/** Use this method when you want to add a label to a form that will
		* cross more of the space than a label:field combination would.
		*/
		addLongLabel: function (layout, labelText, textName, theThis) {
			var l1 = new qx.ui.basic.Label(labelText);
			l1.set({ paddingTop: 3 });
			layout.add(l1);
			if (textName) {
				theThis[textName] = l1;
				PACKAGE.Statics.setHtmlID( l1, textName );
			}
		},

		addLongLabelRich: function (layout, labelText, textName, theThis) {
			var l1 = new qx.ui.basic.Label(labelText);
			l1.set({ paddingTop: 3 });
			l1.setRich(true);
			layout.add(l1);
			if (textName) {
				theThis[textName] = l1;
				PACKAGE.Statics.setHtmlID( l1, textName );
			}
		},

		/** Use this to create a "box with buttons" standard GUI layout.  It's
		* a list box on the left with variable height, that has one or more
		* buttons to the right side of the box.  Usually these buttons are
		* for "Add", "Delete", "Modify", "Move UP", "Move Down", etc.  You
		* decide what they are and what they do, we'll lay them out correctly.
		*/
		addBoxWithButtons: function (theThis, layout, boxName, flexHeight, flexWidth,
			button1Name, button1Label, button1Icon,
			button2Name, button2Label, button2Icon,
			button3Name, button3Label, button3Icon,
			button4Name, button4Label, button4Icon
		) {
			var hb = new qx.ui.container.Composite(new qx.ui.layout.HBox(5));
			hb.set({ paddingTop: 3 });
			hb._getLayout().setAlignY("top");

			var list1 = new qx.ui.form.List;
			//list1.set({ height: "100%", width: "1*", overflow: "scrollY" });
			theThis[boxName] = list1;
			PACKAGE.Statics.trackNamedAttr(theThis, boxName);
			PACKAGE.Statics.setHtmlID( list1, boxName);
			hb.add(list1, {flex:1});

			var vb = new qx.ui.container.Composite( new qx.ui.layout.VBox(5) );
			vb._getLayout().setAlignX("left");
			//vb.setStretchChildrenOrthogonalAxis(true);
			//vb.setHeight("100%");
			//vb.setWidth("auto");

			if (button1Name) {
				var b = new qx.ui.form.Button(button1Label, button1Icon);
				b.setCenter(false);
				theThis[button1Name] = b;
				PACKAGE.Statics.trackNamedAttr(theThis, button1Name);
				PACKAGE.Statics.setHtmlID( b, button1Name);
				vb.add(b);
			}
			if (button2Name) {
				var b = new qx.ui.form.Button(button2Label, button2Icon);
				b.setCenter(false);
				theThis[button2Name] = b;
				PACKAGE.Statics.trackNamedAttr(theThis, button2Name);
				PACKAGE.Statics.setHtmlID( b, button2Name);
				vb.add(b);
			}
			if (button3Name) {
				var b = new qx.ui.form.Button(button3Label, button3Icon);
				b.setCenter(false);
				theThis[button3Name] = b;
				PACKAGE.Statics.trackNamedAttr(theThis, button3Name);
				PACKAGE.Statics.setHtmlID( b, button3Name);
				vb.add(b);
			}
			if (button4Name) {
				var b = new qx.ui.form.Button(button4Label, button4Icon);
				b.setCenter(false);
				theThis[button4Name] = b;
				PACKAGE.Statics.trackNamedAttr(theThis, button4Name);
				PACKAGE.Statics.setHtmlID( b, button4Name);
				vb.add(b);
			}

			hb.add(vb);

			layout.add(hb, {flex:1});
		},

		/** Use this method to add checkboxes (up to 4) onto a form that is
		* being laid out with the addFieldsToForm methodology.
		*
		* @param theThis {Object}
		* @param layout {Object}
		* @param leftSize {Object}
		* @param checkbox1Name {Object}
		* @param checkbox1Label {Object}
		* @param checkbox2Name {Object}
		* @param checkbox2Label {Object}
		* @param checkbox3Name {Object}
		* @param checkbox3Label {Object}
		* @param checkbox4Name {Object}
		* @param checkbox4Label {Object}
		*/
		addCheckboxes: function (theThis, layout, leftSize,
			checkbox1Name, checkbox1Label,
			checkbox2Name, checkbox2Label,
			checkbox3Name, checkbox3Label,
			checkbox4Name, checkbox4Label, initialLabel
		) {
			var hb = new qx.ui.container.Composite(new qx.ui.layout.HBox());
			hb.set({ paddingTop: 3 });
			//hb.setVerticalChildrenAlign("middle");

			// Empty spacer to align things properly.
			var tmpLabel;
			if (initialLabel) {
				tmpLabel = new qx.ui.basic.Label(initialLabel); PACKAGE.Statics.trackExtraObj(theThis, tmpLabel);
			} else {
				tmpLabel = new qx.ui.core.Spacer();
			}
			tmpLabel.setWidth(leftSize);
			hb.add(tmpLabel);

			if (checkbox1Name) {
				var cb1 = new qx.ui.form.CheckBox(checkbox1Label);
				cb1.setAlignY("middle");
				hb.add(cb1);
				theThis[checkbox1Name] = cb1;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox1Name);
				PACKAGE.Statics.setHtmlID( cb1, checkbox1Name);
			}
			if (checkbox2Name) {
				var cb2 = new qx.ui.form.CheckBox(checkbox2Label);
				cb2.setAlignY("middle");
				hb.add(cb2);
				theThis[checkbox2Name] = cb2;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox2Name);
				PACKAGE.Statics.setHtmlID( cb2, checkbox2Name);
			}
			if (checkbox3Name) {
				var cb3 = new qx.ui.form.CheckBox(checkbox3Label);
				cb3.setAlignY("middle");
				hb.add(cb3);
				theThis[checkbox3Name] = cb3;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox3Name);
				PACKAGE.Statics.setHtmlID( cb3, checkbox3Name);
			}
			if (checkbox4Name) {
				var cb4 = new qx.ui.form.CheckBox(checkbox4Label);
				cb4.setAlignY("middle");
				hb.add(cb4);
				theThis[checkbox4Name] = cb4;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox4Name);
				PACKAGE.Statics.setHtmlID( cb4, checkbox4Name);
			}

			layout.add(hb);
		},

		/** Use this method to add checkboxes (up to 4) onto a form that is
		* being laid out with the addFieldsToForm methodology.
		*
		* @param theThis {Object}
		* @param layout {Object}
		* @param leftSize {Int}
		* @param width1 {Int}
		* @param width2 {Int}
		* @param width3 {Int}
		* @param width4 {Int}
		* @param checkbox1Name {Object}
		* @param checkbox1Label {Object}
		* @param checkbox2Name {Object}
		* @param checkbox2Label {Object}
		* @param checkbox3Name {Object}
		* @param checkbox3Label {Object}
		* @param checkbox4Name {Object}
		* @param checkbox4Label {Object}
		*/
		addCheckboxes2: function (theThis, layout, leftSize,
			width1, width2, width3, width4,
			checkbox1Name, checkbox1Label, checkbox2Name, checkbox2Label,
			checkbox3Name, checkbox3Label, checkbox4Name, checkbox4Label
		) {
			var cl = new qx.ui.container.Composite(new qx.ui.layout.Basic());
			cl.setPaddingTop(3);

			if (checkbox1Name) {
				var cb1 = new qx.ui.form.CheckBox(checkbox1Label);
				cl.add(cb1, { top: 0, left: leftSize });
				theThis[checkbox1Name] = cb1;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox1Name);
				PACKAGE.Statics.setHtmlID( cb1, checkbox1Name);
			}
			if (checkbox2Name) {
				var cb2 = new qx.ui.form.CheckBox(checkbox2Label);
				cl.add(cb2, { top: 0, left: leftSize + width1 });
				theThis[checkbox2Name] = cb2;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox2Name);
				PACKAGE.Statics.setHtmlID( cb2, checkbox2Name);
			}
			if (checkbox3Name) {
				var cb3 = new qx.ui.form.CheckBox(checkbox3Label);
				cl.add(cb3, { top: 0, left: leftSize + width1 + width2 });
				theThis[checkbox3Name] = cb3;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox3Name);
				PACKAGE.Statics.setHtmlID( cb3, checkbox3Name);
			}
			if (checkbox4Name) {
				var cb4 = new qx.ui.form.CheckBox(checkbox4Label);
				cl.add(cb4, { top: 0, left: leftSize + width1 + width2 + width3 });
				theThis[checkbox4Name] = cb4;
				PACKAGE.Statics.trackNamedAttr(theThis, checkbox4Name);
				PACKAGE.Statics.setHtmlID( cb4, checkbox4Name);
			}

			layout.add(cl);
		},

		/** Use this method to add a radio button group to your layout, and
		* create multiple radio buttons in a single call.
		*/
		addRadioGroupVertical: function (theThis, layout, leftSize,
			r1Name, r1Label,
			r2Name, r2Label,
			r3Name, r3Label,
			r4Name, r4Label,
			r5Name, r5Label
		) {
			var rg = new qx.ui.form.RadioGroup();
			if (r1Name) rg.add(PACKAGE.Statics.addRadioButtonVertical(theThis, layout,
				leftSize, r1Name, r1Label));
			if (r2Name) rg.add(PACKAGE.Statics.addRadioButtonVertical(theThis, layout,
				leftSize, r2Name, r2Label));
			if (r3Name) rg.add(PACKAGE.Statics.addRadioButtonVertical(theThis, layout,
				leftSize, r3Name, r3Label));
			if (r4Name) rg.add(PACKAGE.Statics.addRadioButtonVertical(theThis, layout,
				leftSize, r4Name, r4Label));
			if (r5Name) rg.add(PACKAGE.Statics.addRadioButtonVertical(theThis, layout,
				leftSize, r5Name, r5Label));
			return rg;
		},

		addRadioButtonVertical: function (theThis, layout, leftSize, r1Name, r1Label
		) {
			if (r1Name) {
				var hb = new qx.ui.container.Composite(new qx.ui.layout.HBox());
				hb.set({ paddingTop: 3 });
				hb._getLayout().setAlignY("middle");

				// Empty spacer to align things properly.
				var tmpLabel = new qx.ui.core.Spacer();
				tmpLabel.setWidth(leftSize);
				hb.add(tmpLabel);

				var rb = new qx.ui.form.RadioButton(r1Label);
				hb.add(rb);
				theThis[r1Name] = rb;
				PACKAGE.Statics.trackNamedAttr(theThis, r1Name);
				PACKAGE.Statics.setHtmlID( rb, r1Name);
				layout.add(hb);
				return rb;
			} else {
				return null;
			}
		},

		/** Use this method to add a radio button group to your layout, and
		* create multiple radio buttons in a single call.
		*/
		addRadioGroupHorizontal: function (theThis, layout, leftSize, groupName,
			labelPrefix,
			r1Name, r1Label, r1Value,
			r2Name, r2Label, r2Value,
			r3Name, r3Label, r3Value,
			r4Name, r4Label, r4Value,
			r5Name, r5Label, r5Value
		) {
			var rg = new qx.ui.form.RadioGroup();
			var hb = new qx.ui.container.Composite(new qx.ui.layout.HBox());
			hb.set({ paddingTop: 3 });

			if (labelPrefix) {
				// Real label with text
				var tmpLabel = new qx.ui.basic.Label(labelPrefix);
			} else {
				// Empty spacer to align things properly.
				var tmpLabel = new qx.ui.core.Spacer();
			}
			tmpLabel.setWidth(leftSize);
			hb.add(tmpLabel);

			// Now all of the radio buttons.
			if (r1Name) {
				var rb = new qx.ui.form.RadioButton(r1Label);
				hb.add(rb);
				theThis[r1Name] = rb;
				PACKAGE.Statics.trackNamedAttr(theThis, r1Name);
				PACKAGE.Statics.setHtmlID( rb, r1Name);
				rg.add(rb);
			}
			if (r2Name) {
				var rb = new qx.ui.form.RadioButton(r2Label);
				hb.add(rb);
				theThis[r2Name] = rb;
				PACKAGE.Statics.trackNamedAttr(theThis, r2Name);
				PACKAGE.Statics.setHtmlID( rb, r2Name);
				rg.add(rb);
			}
			if (r3Name) {
				var rb = new qx.ui.form.RadioButton(r3Label);
				hb.add(rb);
				theThis[r3Name] = rb;
				PACKAGE.Statics.trackNamedAttr(theThis, r3Name);
				PACKAGE.Statics.setHtmlID( rb, r3Name);
				rg.add(rb);
			}
			if (r4Name) {
				var rb = new qx.ui.form.RadioButton(r4Label);
				hb.add(rb);
				theThis[r4Name] = rb;
				PACKAGE.Statics.trackNamedAttr(theThis, r4Name);
				PACKAGE.Statics.setHtmlID( rb, r4Name);
				rg.add(rb);
			}
			if (r5Name) {
				var rb = new qx.ui.form.RadioButton(r5Label);
				hb.add(rb);
				theThis[r5Name] = rb;
				PACKAGE.Statics.trackNamedAttr(theThis, r5Name);
				PACKAGE.Statics.setHtmlID( rb, r5Name);
				rg.add(rb);
			}
			layout.add(hb);
			return rg;
		},

		/** This method helps us with widget layouts that involve two lists.  On the
		* left is a list of items that are "included", and on the right is a list of
		* items that are "available to be included".  Between the two lists are two
		* buttons stacked vertically: "<- Add", and "Remove ->".  Above each list is
		* a label that describes the list.
		*/
		createDoubleList: function (theThis, layout,
			leftListLabel, leftListName, middleSize,
			rightListLabel, rightListName, listHeight
		) {
			var form_layout = new qx.ui.container.Composite(new qx.ui.layout.VBox);
			form_layout.set({ paddingTop: 3 });

			var hb1 = new qx.ui.container.Composite(new qx.ui.layout.HBox);
			var l1 = new qx.ui.basic.Label(leftListLabel); PACKAGE.Statics.trackExtraObj(theThis, l1);
			hb1.add(l1);
			hb1.add(new qx.ui.core.Spacer, { flex: 1 });
			var l2 = new qx.ui.core.Spacer;
			l2.setWidth(middleSize + 3);
			hb1.add(l2);
			var l3 = new qx.ui.basic.Label(rightListLabel); PACKAGE.Statics.trackExtraObj(theThis, l3);
			hb1.add(l3);
			hb1.add(new qx.ui.core.Spacer, { flex: 1 });
			form_layout.add(hb1);

			var hb2 = new qx.ui.container.Composite(new qx.ui.layout.HBox);
			hb2._getLayout().setAlignY("middle");
			var list1 = new qx.ui.form.List;
			list1.set({ height: listHeight, selectionMode: "multi" });
			theThis[leftListName] = list1;
			PACKAGE.Statics.trackNamedAttr(theThis, leftListName);
			PACKAGE.Statics.setHtmlID( list1, leftListName);
			hb2.add(list1, { flex: 1 });

			var vb1 = new qx.ui.container.Composite(new qx.ui.layout.VBox(10));
			vb1.set({ padding: 5 });
			vb1._getLayout().setAlignY("middle");
			vb1.setWidth(middleSize);
			var add_button = new qx.ui.form.Button("<- Add");
			var remove_button = new qx.ui.form.Button("Remove ->");
			vb1.add(add_button);
			PACKAGE.Statics.setHtmlID( add_button, "Add");
			PACKAGE.Statics.setHtmlID( remove_button, "Remove");
			vb1.add(remove_button);
			hb2.add(vb1);

			var list2 = new qx.ui.form.List;
			list2.set({ minHeight: listHeight, selectionMode: "multi" });
			theThis[rightListName] = list2;
			PACKAGE.Statics.trackNamedAttr(theThis, rightListName);
			PACKAGE.Statics.setHtmlID( list2, rightListName);
			hb2.add(list2, { flex: 1 });

			form_layout.add(hb2, { flex: 1 });

			add_button.addListener("execute", function () {
				var selected = list2.getSelection();
				for (var i = 0, l = selected.length; i < l; i++) {
					var item = selected[i];
					// is it in the left list already?
					var match = PACKAGE.Statics.findListItem(list1, item.getModel());
					if (match === null) {
						match = new qx.ui.form.ListItem(item.getLabel(), null, item.getModel());
						list1.add(match);
					}
				}
			});

			remove_button.addListener("execute", function () {
				var selected = list1.getSelection();
				for (var i = 0, l = selected.length; i < l; i++) {
					list1.remove(selected[i]);
				}
			});

			layout.add(form_layout, { flex: 1 });

		},

		/** Use this to create a table with standard options.
		*/
		createStandardTable: function (columnArray, filtered) {
			// table model
			var tableModel = (filtered == "true") ? new qx.ui.table.model.Filtered() : new qx.ui.table.model.Simple();
			tableModel.setColumns(columnArray);
			// Customize the table column model.  We want one that automatically
			// resizes columns.
			var custom = {
				tableColumnModel: function (obj) {
					return new qx.ui.table.columnmodel.Resize(obj);
				}
			};

			// table
			var the_table = new qx.ui.table.Table(tableModel, custom);
			the_table.set({ height: 1, minHeight: 1 });
			the_table.getSelectionModel().setSelectionMode(
				qx.ui.table.selection.Model.MULTIPLE_INTERVAL_SELECTION);
			the_table.getDataRowRenderer().setHighlightFocusRow(false);
			the_table.setFocusCellOnPointerMove( false );
			the_table.setShowCellFocusIndicator(false);
			the_table.setAlwaysUpdateCells( false );

			return the_table;
		},

		/** Use this to create a treeVirtual with standard options.
		*/
		createStandardTreeVirtual: function (columnArray) {
			var theTree = new qx.ui.treevirtual.TreeVirtual ( columnArray );
			theTree.set({ height: 1, minHeight:1 });
			theTree.setAlwaysShowOpenCloseSymbol(true);
			theTree.getSelectionModel().setSelectionMode(
				qx.ui.table.selection.Model.MULTIPLE_INTERVAL_SELECTION);
			theTree.getDataRowRenderer().setHighlightFocusRow(false);
			theTree.setFocusCellOnMouseMove( false );
			theTree.setShowCellFocusIndicator(false);
			theTree.setAlwaysUpdateCells( false );

			// ensure that the tree column remains sufficiently wide
			var resizeBehavior = theTree.getTableColumnModel().getBehavior();
			resizeBehavior.set( 0, {width: "1*", minWidth:180 });

			return theTree;
		},

		cleanupStandardTable: function (table) {
			if (!table) {
				return;
			}
			try {
				var tcm = table.getTableColumnModel();
				if (tcm) {
					var tcm_behavior = tcm.getBehavior();
					var rcd = tcm_behavior._resizeColumnData;
					if (rcd) {
						for (var i = 0, l = rcd.length; i < l; i++) {
							rcd[i].dispose();
						}
					}
				}

				if (table.getTableModel()) {
					table.getTableModel().dispose();
				}
				if (table.__columnMenuButtons) {
					table._disposeMap("__columnMenuButtons");
				}
			} catch (e) {
			}
		},

		/** Use this when adding items to a toolbar
		*
		* @param toolbar {Object} either a toolbar or a toolbar part
		* @param icon {String}
		* @param tooltip {String}
		* @param action {Function}
		* @param action_this {Object}
		* @param ownerObj {Object}
		* @param label {String}
		*/
		addToToolbar: function (toolbar, icon, tooltip, action, action_this, ownerObj, label) {
			label = (label == undefined) ? null : label;
			var btn = new qx.ui.toolbar.Button(label, icon);
			PACKAGE.Statics.setHtmlID( btn, label);
			//btn.setHeight("auto");
			if (action && action_this) {
				btn.addListener("execute", action, action_this);
			}
			var tip = new qx.ui.tooltip.ToolTip(tooltip);
			btn.setToolTip(tip);
			toolbar.add(btn);
			// tool tips have to be collected and tracked so that they
			// can be properly disposed.
			if (!ownerObj.toolTipList) {
				ownerObj.toolTipList = [];
			}
			ownerObj.toolTipList.push(tip);
			return btn;
		},

		trackExtraObj: function (ownerObj, obj) {
			if (!ownerObj.extrasList) {
				ownerObj.extrasList = [];
			}
			ownerObj.extrasList.push(obj);
		},

		trackNamedAttr: function (ownerObj, attrName) {
			if (!ownerObj.namedAttrList) {
				ownerObj.namedAttrList = [];
			}
			ownerObj.namedAttrList.push(attrName);

			// also handle the dirty flag checking here:
			if(ownerObj.isDirty !== undefined &&
				ownerObj.fieldModified !== undefined &&
				qx.lang.String.endsWith(attrName, "ReadOnlyField") !=  true
			){
				if( ownerObj[attrName] instanceof qx.ui.form.AbstractField ){
					ownerObj[attrName].addListener("input", ownerObj.fieldModified, ownerObj);
					ownerObj[attrName].addListener("changeValue", ownerObj.fieldModified, ownerObj);
				} else if(ownerObj[attrName] instanceof qx.ui.table.Table ) {
					ownerObj[attrName].addListener("dataEdited", ownerObj.fieldModified, ownerObj );
				} else if(ownerObj[attrName] instanceof qx.ui.form.SelectBox) {
					ownerObj[attrName].addListener("changeSelection", ownerObj.fieldModified, ownerObj );
				} else if(ownerObj[attrName] instanceof qx.ui.form.RadioButton) {
					ownerObj[attrName].addListener("changeValue", ownerObj.fieldModified, ownerObj );
				} else if(ownerObj[attrName] instanceof qx.ui.form.Button) {
					// Do nothing.
				} else {
					ownerObj[attrName].addListener("changeValue", ownerObj.fieldModified, ownerObj );
				}
			}
		},

		/** Use this in your destruct function, we will check for the
		*  following items to be destroyed:
		*  	qx.ui.popu.ToolTip
		*  	qx.ui.command.Command
		*/
		destroyExtraObjects: function (ownerObj) {

			if (ownerObj.toolTipList) {
				for (var i = 0, l = ownerObj.toolTipList.length; i < l; i++) {
					var obj = ownerObj.toolTipList[i];
					obj.dispose();
				}
				ownerObj.toolTipList = null;
			}

			if (ownerObj.commandList) {
				for (var i = 0, l = ownerObj.commandList.length; i < l; i++) {
					var obj = ownerObj.commandList[i];
					obj.dispose();
				}
				ownerObj.commandList = null;
			}
			if (ownerObj.extrasList) {
				for (var i = 0, l = ownerObj.extrasList.length; i < l; i++) {
					var obj = ownerObj.extrasList[i];
					obj.dispose();
				}
				ownerObj.extrasList = null;
			}
			if (ownerObj.namedAttrList) {
				for (var i = 0, l = ownerObj.namedAttrList.length; i < l; i++) {
					var obj = ownerObj[ownerObj.namedAttrList[i]];
					if (obj) {
						obj.dispose();
						ownerObj[ownerObj.namedAttrList[i]] = null;
					}
				}
				ownerObj.namedAttrList = null;
			}
			if (ownerObj.dynamicLayouts) {
				for (var i = 0, l = ownerObj.dynamicLayouts.length; i < l; i++) {
					var obj = ownerObj.dynamicLayouts[i];
					obj.name = null;
					delete obj.doc;
					obj.doc = null;
				}
				ownerObj.dynamicLayouts = null;
			}
		},

		/** Use this to destroy an array of PACKAGE data objects
		*
		*/
		disposeArray: function (arr) {
			for (var n in arr) {
				if (arr.hasOwnProperty(n)) {
					var obj = arr[n];
					if (obj.dispose) {
						obj.dispose();
					}
					arr[n] = null;
				}
			}
		},

		/** Use this when adding items to a context menu in your form or table.
		*
		* @param menu {Object}
		* @param label {Object}
		* @param icon {Object}
		* @param callback {Object}
		* @param theThis {Object}
		* @return {Object} returns the button created for the menu item.
		*/
		addToRMCMenu: function (menu, label, icon, callback, theThis) {
			var cmd = new qx.ui.command.Command();
			cmd.addListener('execute', callback, theThis);
			var btn = new qx.ui.menu.Button(label, icon, cmd);
			menu.add(btn);
			PACKAGE.Statics.setHtmlID( btn, label);

			// commands have to be collected and tracked so that they
			// can be properly disposed.
			if (!theThis.commandList) {
				theThis.commandList = [];
			}
			theThis.commandList.push(cmd);

			return btn;
		},

		/** Use this to put a separator into an RMC menu.
		*
		*/
		addRMCSeparator: function (menu) {
			menu.add(new qx.ui.menu.Separator());
		},

		/** Use this when you need to add a sub-menu to an existing RMC menu.
		*
		* @param menu {Object}
		* @param label {Object}
		* @param icon {Object}
		*/
		addSubRMCMenu: function (menu, label, icon) {
			var sub = new qx.ui.menu.Menu;
			var btn = new qx.ui.menu.Button(label, icon, null, sub);
			menu.add(btn);
			PACKAGE.Statics.setHtmlID( btn, label);
			return sub;
		},

		/** Use this when adding a page to an existing tab view.
		*
		* @param tabview {Object}
		* @param name {String}
		* @param showClose {boolean}
		* @param isChecked {boolean}
		*/
		addTabPage: function (tabview, name, showClose, isChecked) {
			var tab_page = new qx.ui.tabview.Page(name);
			var vbox = new qx.ui.layout.VBox();
			tab_page.setLayout(vbox);
			tab_page.getButton().setShowCloseButton(showClose);
			tab_page.getButton().setValue(isChecked);
			tabview.add(tab_page);
			PACKAGE.Statics.setHtmlID( tab_page.getButton(), name);
			return tab_page;
		},

		/** Use this when adding a tab page to an existing editor.
		*
		* @param tabview {Object}
		* @param name {String}
		* @param isChecked {boolean}
		* @param toolbar {Object}
		*/
		addEditorSubTab: function (tabview, name, isChecked, toolbar) {
			var tab_page = new qx.ui.tabview.Page(name);
			if (toolbar) {
				tab_page.add(toolbar);
			}
			var vbox = new qx.ui.layout.VBox();
			tab_page.setLayout(vbox);
			tab_page.getButton().setValue(isChecked);
			PACKAGE.Statics.setHtmlID( tab_page.getButton(), name);
			tabview.add(tab_page);
			var scroller = new qx.ui.container.Scroll();
			tab_page.add(scroller, { flex: 1 });
			return scroller;
		},

		getSplitFirst: function (pane) {
			return pane._getChildren()[2];
		},

		getSplitSecond: function (pane) {
			return pane._getChildren()[3];
		},

		doAlert: function (message, title, doAfter, theThis) {
			var windowTitle = title ? title : "Alert";
			var windowIcon = "PACKAGE/icon/32x32/shadow/sign_warning.png";
			var tmpWindow = new PACKAGE.dialog.MessageDialog(windowTitle, windowIcon,
				message);
			if (doAfter) {
				tmpWindow.addOkEventListener("execute", doAfter, theThis);
			}
			tmpWindow.open();
			qx.core.Init.getApplication().getRoot().add(tmpWindow);
		},

		doAlertGreen: function (message, title, doAfter, theThis) {
			var windowTitle = title ? title : "Alert";
			var windowIcon = "PACKAGE/icon/32x32/shadow/ok.png";
			var tmpWindow = new PACKAGE.dialog.MessageDialog(windowTitle, windowIcon,
				message);
			if (doAfter) {
				tmpWindow.addOkEventListener("execute", doAfter, theThis);
			}
			tmpWindow.open();
			qx.core.Init.getApplication().getRoot().add(tmpWindow);
		},

		/** Use this to set the PACKAGE data object into a tree node.  This handles
		* the setting in a standard way that makes it easy to set/get the PACKAGE
		* data object associated with a tree node.
		*/
		setTreeNodeDO: function (tree, nodeID, dataObject) {
			var realNode = tree.getTableModel().getData()[nodeID];
			realNode.PACKAGEDataObject = dataObject;
		},

		/** Use this to get the PACKAGE data object from a tree node.  Use the
		* setTreeNodeDO in order to use this method properly.
		*/
		getTreeNodeDO: function (tree, nodeID) {
			var realNode = tree.getTableModel().getData()[nodeID];
			return realNode.PACKAGEDataObject;
		},

		/** Use this to get the PACKAGE data object from a tree by using the row number.
		* Use the setTreeNodeDO in order to use this method properly.
		*/
		getTreeNodeDOByRow: function (tree, row) {
			var realNode = tree.getTableModel().getNodeFromRow(row);
			return realNode.PACKAGEDataObject;
		},

		/** Use this to set the PACKAGE data object into a table row.  This will work
		* with the Simple table model.
		*/
		setTableRowDO: function (table, row, dataObject) {
			table.getTableModel().getRowData(row).PACKAGEDataObject = dataObject;
		},

		/** Use this to get the PACKAGE data object from a table row.  This will work
		* with the Simple table model.
		*/
		getTableRowDO: function (table, row) {
			return table.getTableModel().getRowData(row).PACKAGEDataObject;
		},

		/**
		* Given a node id or a node object, this will walk the tree up to the node's
		* root parent, and return that root node object.
		*
		* @param tree {Object} The tree in which to search.
		*
		* @param nodeReference {Object | Integer}
		*   The node to use as the start of the search.  The node can be
		*   represented either by the node object, or the node id (as would have
		*   been returned by addBranch(), addLeaf(), etc.).
		*
		* @return {Object}
		*   The node object that represents the highest parent that can be found in the tree.
		*/
		getTreeNodeParentRoot: function (tree, nodeReference) {
			var node = null;
			if (typeof (nodeReference) == "object") {
				node = nodeReference;
			} else if (typeof (nodeReference) == "number") {
				node = tree.getTableModel().getData()[nodeReference];
			} else {
				throw new Error("Expected node object or node id");
			}

			while (node.parentNodeId !== 0) {
				node = tree.getTableModel().getData()[node.parentNodeId];
			}

			return node;
		},

		verifyAllFields: function (theThis) {
			if (theThis.fieldVerificationList === undefined) {
				// No verification list has been set up.  Do nothing.
				return;
			}

			for (var i = 0, l = theThis.fieldVerificationList.length; i < l; i++) {

				var obj = theThis.fieldVerificationList[i];
				var verifyResult = 0;
				if (obj.type === "string") {
					verifyResult = PACKAGE.Statics.verifyStringField(theThis, obj);
				} else if (obj.type === "int") {
					verifyResult = PACKAGE.Statics.verifyIntegerField(theThis, obj);
				} else {
					theThis.debug("Unknown verify type: " + obj.type);
				}
				if (verifyResult === -1) {
					var field = theThis[obj.varName];
					// Find the parent tab and activate it:
					var our_tab = PACKAGE.Statics.findQXParent(field, qx.ui.tabview.Page);
					our_tab.getButton().execute();

					// Return our failed result:
					return -1;
				}

			}

		},

		verifyStringField: function (theThis, verifyObj) {
			var field = theThis[verifyObj.varName];

			var required = true;
			var minLen = 0;
			var maxLen = 0;
			if (verifyObj.min !== undefined) {
				minLen = Number(verifyObj.min);
			}
			if (verifyObj.max !== undefined) {
				maxLen = Number(verifyObj.max);
			}
			if (verifyObj.required !== undefined) {
				if (verifyObj.required !== "true") {
					required = false;
				}
			}

			// Ensure that the field is not empty
			if (minLen > 0 || required) {
				if (PACKAGE.Statics.verifyTextField(field, verifyObj.label) === -1) return -1;
			}

			// Ensure that the field has a minimum length
			var val = qx.lang.String.trimRight(field.getValue());
			if (minLen > 0 && val.length < minLen) {
				PACKAGE.Statics.doAlert(verifyObj.label + " field must be at least " + verifyObj.min + " characters.",
					verifyObj.label + " field is too short!", function () {
						field.focus();
					});
				return -1;
			}
			if (maxLen > 0 && val.length > maxLen) {
				PACKAGE.Statics.doAlert(verifyObj.label + " field must not be longer than " + verifyObj.max + " characters.",
					verifyObj.label + " field is too long!", function () {
						field.focus();
					});
				return -1;
			}

			// Finally, see if we need to force text to uppercase:
			if (verifyObj.upper !== undefined && verifyObj.upper === "true") {
				field.setValue(field.getValue().toUpperCase());
			}

			// All checks pass, return 0
			return 0;
		},

		verifyIntegerField: function (theThis, verifyObj) {
			var field = theThis[verifyObj.varName];

			var required = true;
			if (verifyObj.required !== undefined) {
				if (verifyObj.required !== "true") {
					required = false;
				}
			}

			// Ensure that the field is not empty
			var val = -1;
			if (required) {
				var val = PACKAGE.Statics.verifyInteger(field, verifyObj.label);
			}
			if (val === -1 && required) return -1;
			if (val === -1 && !required) return 0; // it's ok for it to be empty

			// If the field has a value, verify the value.

			// Ensure that the field has a minimum length
			if (verifyObj.min !== undefined &&
				Number(verifyObj.min) > 0 &&
				val < Number(verifyObj.min)
			) {
				PACKAGE.Statics.doAlert(verifyObj.label + " field must be at least " + verifyObj.min + " in value.",
					verifyObj.label + " value is too small!", function () {
						field.focus();
					});
				return -1;
			}
			if (verifyObj.max !== undefined &&
				Number(verifyObj.max) > 0 &&
				val > Number(verifyObj.max)
			) {
				PACKAGE.Statics.doAlert(verifyObj.label + " field must not be larger than " + verifyObj.max + ".",
					verifyObj.label + " value is too large!", function () {
						field.focus();
					});
				return -1;
			}

			// All checks pass, return 0
			return 0;
		},

		verifyTextField: function (field, name) {
			if (!field.getValue() || qx.lang.String.trimRight(field.getValue()).length === 0) {
				PACKAGE.Statics.doAlert(name + " field is empty.  Please enter a value",
					name + " field is empty!", function () {
						field.focus();
					});
				return -1;
			}
			return 0;
		},

		verifyDropDown: function (field, name) {
			if (PACKAGE.Statics.isDropDownUnSelected(field)) {
				PACKAGE.Statics.doAlert(name + " field is empty.  Please enter a value",
					name + " field is empty!", function () {
						field.focus();
					});
				return -1;
			}
			return 0;
		},

		verifyInteger: function (field, name) {
			// First make sure there is something in it.
			if (PACKAGE.Statics.verifyTextField(field, name) === -1) return -1;

			// Now make sure that what is in it is really an integer

			var intValue = parseInt(field.getValue());
			// First check to see if it is NaN
			if (isNaN(intValue)) {
				PACKAGE.Statics.doAlert(name + " field has an invalid integer.  Please enter a valid integer.",
					name + " field is not a valid integer!", function () {
						field.focus();
					});
				return -1;
			}

			// Now convert back to a string and ensure that the lengths are the same:
			var intValueAsString = intValue.toString();
			if (qx.lang.String.trimRight(field.getValue()).length !== intValueAsString.length) {
				PACKAGE.Statics.doAlert(name + " field has an invalid integer.  Please enter a valid integer.",
					name + " field is not a valid integer!", function () {
						field.focus();
					});
				return -1;
			}

			// If that all works, we're ok.
			return intValue;
		},

		/** We have a certain design to our data objects and our form layout implementation that
		* allows us to generically load and pull data into and from our form layouts.  This function
		* will loop through all of the members of theThis that end in "Field" and attempt to
		* load them from the given data object.  If the data object does not have a matching name,
		* they will be skipped.  If for some other reason we can't automatically load them, we'll
		* skip them as well.
		*
		* @param theThis {Object} This is the current object which has the field as a member.
		* @param dataObject {Object} This is a standard auto-generated data object class.
		*/
		loadAllFields: function (theThis, dataObject) {

			// Loop through all members of theThis and find all fields:
			for (var m in theThis) {
				if (theThis.hasOwnProperty(m)) {
					if (m.substr(m.length - 5, m.length) === "Field") {
						// This is a member that ends in "Field".  Load data for it:
						PACKAGE.Statics.loadOneField(theThis, dataObject, m);
					}
				}
			}

		},

		/** This function is designed to implement a flexible approach for loading data
		* from a standardized data object into a field on a form.  Naming conventions
		* must be followed, and standard LayoutEngine functions should be used before
		* invoking this method.
		*
		* @param theThis {Object} This is the current object which has the field as a member.
		* @param dataObject {Object} This is a standard auto-generated data object class.
		* @param fieldName {Object} This is the full field name, which should end with "Field"
		*                           and match the name of a member in the data object.
		*/
		loadOneField: function (theThis, dataObject, fieldName) {
			var shortName = fieldName.substr(0, fieldName.length - 5); // chop off the "Field" ending.
			var firstChar = shortName.substr(0, 1);
			var capShortName = firstChar.toUpperCase() + shortName.substr(1, shortName.length);
			var getName = "get" + capShortName;
			var setName = "set" + capShortName;
			var initName = "$$init_" + shortName; // used to determine data type.

			var formField = theThis[fieldName];
			if (formField === null || formField === undefined) {
				theThis.debug("Unknown formfield '" + fieldName + "'");
				return; // bail out.
			}

			var initValue = dataObject[initName];
			if (initValue === undefined) {
				theThis.debug("Unknown dataObject field '" + shortName + "'");
				return; // bail out.
			}

			if (formField instanceof qx.ui.form.TextField ||
				formField instanceof qx.ui.form.PasswordField
			) {
				if (initValue === 0) {
					// The data object is an integer type.  Coerce to a string in order
					// to load it into the text field
					formField.setValue(String(dataObject[getName]()));
				} else {
					// Load it as a string.
					formField.setValue(dataObject[getName]());
				}

			} else if (formField instanceof qx.ui.form.TextArea) {
				// Check to see if we also have a CK version of this textArea - if so, that one
				// takes precedence.
				var ckField = theThis[ fieldName + "CK" ];
				if(ckField !== undefined && ckField !== null){
					// We have a CKEditor on top of the text area
					if(ckField.status === 'ready'){
						ckField.setData( dataObject[getName]() );
					} else {
						var content = dataObject[getName]();
						ckField.on('instanceReady', function(evt){
							ckField.setData( content );
						});
					}
				} else {
					// Standard textArea
					if(initValue === 0){
						formField.setValue( String(dataObject[getName]() ) );
					} else {
						formField.setValue( dataObject[getName]() );
					}
				}

			} else if (formField instanceof qx.ui.form.DateField) {
				if(dataObject[getName]() !== null &&
					dataObject[getName]().length >= 19
				){
					formField.setValue( formField.getDateFormat().parse( dataObject[getName]() ) );
				} else {
					formField.setValue( null );
				}

			} else if (formField instanceof qx.ui.form.SelectBox) {
				PACKAGE.Statics.setDropDownByValue(formField, String(dataObject[getName]()));

			} else if (formField instanceof qx.ui.form.ComboBox) {
				if (initValue === 0) {
					// The data object is an integer type.  Coerce to a string in order
					// to load it into the text field
					formField.setValue(String(dataObject[getName]()));
				} else {
					// Load it as a string.
					formField.setValue(dataObject[getName]());
				}

			} else if (formField instanceof qx.ui.form.CheckBox) {
				formField.setValue(Boolean(Number(dataObject[getName]())));

			} else if (formField instanceof qx.ui.groupbox.CheckGroupBox) {
				formField.setValue(Boolean(Number(dataObject[getName]())));

			} else if (formField instanceof qx.ui.form.RadioButton) {
				formField.setValue(Boolean(Number(dataObject[getName]())));

			} else if (formField instanceof qx.ui.groupbox.RadioGroupBox) {
				formField.setValue(Boolean(Number(dataObject[getName]())));

			} else {
				theThis.warn("Unknown field type for field '" + fieldName + "'.");
			}

		},

		/** We have a certain design to our data objects and our form layout implementation that
		* allows us to generically load and pull data into and from our form layouts.  This function
		* will loop through all of the members of theThis that end in "Field" and attempt to
		* pull their data and store it in the given data object.  If the data object does not have
		* a matching name, they will be skipped.  If for some other reason we can't automatically
		* pull their data, we'll skip them as well.
		*
		* @param theThis {Object} This is the current object which has the field as a member.
		* @param dataObject {Object} This is a standard auto-generated data object class.
		*/
		pullAllFields: function (theThis, dataObject) {

			// Loop through all members of theThis and find all fields:
			for (var m in theThis) {
				if (theThis.hasOwnProperty(m)) {
					if (m.substr(m.length - 5, m.length) === "Field") {
						// This is a member that ends in "Field".  Load data for it:
						PACKAGE.Statics.pullOneField(theThis, dataObject, m);
					}
				}
			}

		},

		/** This function is designed to implement a flexible approach for pulling data
		* from a form field into a standardized data object.  Naming conventions
		* must be followed, and standard LayoutEngine functions should be used before
		* invoking this method.
		*
		* @param theThis {Object} This is the current object which has the field as a member.
		* @param dataObject {Object} This is a standard auto-generated data object class.
		* @param fieldName {Object} This is the full field name, which should end with "Field"
		*                           and match the name of a member in the data object.
		*/
		pullOneField: function (theThis, dataObject, fieldName) {
			var shortName = fieldName.substr(0, fieldName.length - 5); // chop off the "Field" ending.
			var firstChar = shortName.substr(0, 1);
			var capShortName = firstChar.toUpperCase() + shortName.substr(1, shortName.length);
			var getName = "get" + capShortName;
			var setName = "set" + capShortName;
			var initName = "$$init_" + shortName; // used to determine data type.

			var formField = theThis[fieldName];
			if (formField === null || formField === undefined) {
				theThis.debug("Unknown formfield '" + fieldName + "'");
				return; // bail out.
			}

			var initValue = dataObject[initName];
			if (initValue === undefined) {
				theThis.debug("Unknown dataObject field '" + shortName + "'");
				return; // bail out.
			}

			if (formField instanceof qx.ui.form.TextField ||
				formField instanceof qx.ui.form.PasswordField
			) {
				if (initValue === 0) {
					// The data object is an integer type.  Coerce to a number in order
					// to populate it from the text field
					dataObject[setName](Number(formField.getValue()));
				} else {
					// Load it as a string.
					dataObject[setName](formField.getValue());
				}
			} else if (formField instanceof qx.ui.form.TextArea) {
				// Check to see if we also have a CK version of this textArea - if so, that one
				// takes precedence.
				var ckField = theThis[ fieldName + "CK" ];
				if(ckField !== undefined && ckField !== null){
					// We have a CKEditor on top of the text area
					dataObject[ setName ]( ckField.getData() );
				} else {
					// Standard textArea
					if(initValue === 0){
						dataObject[ setName ](Number(formField.getValue()) );
					} else {
						dataObject[ setName ](formField.getValue() );
					}
				}

			} else if (formField instanceof qx.ui.form.DateField) {
				if(formField.getValue() === null){
					dataObject[ setName ]( "" );
				} else {
					dataObject[ setName ]( formField.getDateFormat().format( formField.getValue() ) );
				}

			} else if (formField instanceof qx.ui.form.SelectBox) {
				if (initValue === 0) {
					// The data object is an integer type.  Coerce to a number in order
					// to populate it from the text field
					dataObject[setName](Number(formField.getSelection()[0].getModel()));
				} else {
					// Load it as a string.
					dataObject[setName](formField.getSelection()[0].getModel());
				}

			} else if (formField instanceof qx.ui.form.ComboBox) {
				if (initValue === 0) {
					// The data object is an integer type.  Coerce to a number in order
					// to populate it from the text field
					dataObject[setName](Number(formField.getValue()));
				} else {
					// Load it as a string.
					dataObject[setName](formField.getValue());
				}

			} else if (formField instanceof qx.ui.form.CheckBox ||
				formField instanceof qx.ui.groupbox.CheckGroupBox
			) {
				if (initValue === 0) {
					// The data object is an integer type.  Coerce from bool to number
					dataObject[setName](Number(formField.getValue()));
				} else {
					// Load it as a string by coercing from bool to number to string
					dataObject[setName](String(Number(formField.getValue())));
				}


			} else if (formField instanceof qx.ui.form.RadioButton) {
				dataObject[setName](Number(formField.getValue()));

			} else if (formField instanceof qx.ui.groupbox.RadioGroupBox) {
				dataObject[setName](Number(formField.getValue()));

			} else {
				theThis.warn("Unknown field type for field '" + fieldName + "'.");
			}

		},

		formatSQLError: function (errString) {
			if (errString.indexOf("Error - SQL_ERROR:") === -1) {
				return errString; // not a sql error.
			}

			errString = errString.replace(/\n/g, "<br/>");
			errString = errString.replace(/\t/g, "&nbsp;&nbsp;&nbsp;&nbsp;");
			errString = errString.replace(/\[Viaserv\]\[ODBC Driver\]/g, "");

			return errString;
		},

		isDevVersion: function () {
			if (PACKAGE.Singleton.getInstance().getUserProperties()["PACKAGEClientVersion"].substr(0, 4) === "314.") {
				return true;
			} else {
				return false;
			}
		},

		isFreeVersion: function () {
			var license = PACKAGE.LicenseCode.getInstance();
			if (license["/is/free/version"]) {
				return true;
			} else {
				return false;
			}
		},

		areWeHomeBase: function () {
			if (window.location.hostname === "PACKAGE.hericus.com") {
				return true;
			} else {
				return false;
			}
		},

		decimalToHex: function (i) {
			var hex = Number(i).toString(16);
			hex = "00000000".substr(0, 8 - hex.length) + hex;
			return hex;
		},

		/** Create a hex character representation of the given number, and ensure
		  * it is at least 2 characters wide.
		  */
		decimalToHex2: function (i) {
			var hex = Number(i).toString(16);
			hex = "00".substr(0, 2 - hex.length) + hex;
			return hex;
		},

		/** This code was written by Tyler Akins and has been placed in the
		* public domain.  It would be nice if you left this header intact.
		* Base64 code from Tyler Akins -- http://rumkin.com
		*/
		encode64: function (input) {
			var keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
			var output = "";
			var chr1, chr2, chr3;
			var enc1, enc2, enc3, enc4;
			var i = 0;
			var len = 0;

			if(input.length === 0){
				return output;
			}

			do {
				chr1 = input.charCodeAt(i++);
				chr2 = input.charCodeAt(i++);
				chr3 = input.charCodeAt(i++);

				enc1 = chr1 >> 2;
				enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
				enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
				enc4 = chr3 & 63;

				if (isNaN(chr2)) {
					enc3 = enc4 = 64;
				} else if (isNaN(chr3)) {
					enc4 = 64;
				}

				output = output + keyStr.charAt(enc1) + keyStr.charAt(enc2) +
				keyStr.charAt(enc3) + keyStr.charAt(enc4);
				len += 4;
				if( len % 64 === 0 ){
					// add a newline to the string:
					output = output + "\n";
				}
			} while (i < input.length);
			output += "\n";

			return output;
		},

		/** This code was written by Tyler Akins and has been placed in the
		* public domain.  It would be nice if you left this header intact.
		* Base64 code from Tyler Akins -- http://rumkin.com
		*/
		decode64: function (input) {
			var keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
			var output = "";
			var chr1, chr2, chr3;
			var enc1, enc2, enc3, enc4;
			var i = 0;

			if(input.length === 0){
				return output;
			}

			// remove all characters that are not A-Z, a-z, 0-9, +, /, or =
			input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");

			do {
				enc1 = keyStr.indexOf(input.charAt(i++));
				enc2 = keyStr.indexOf(input.charAt(i++));
				enc3 = keyStr.indexOf(input.charAt(i++));
				enc4 = keyStr.indexOf(input.charAt(i++));

				chr1 = (enc1 << 2) | (enc2 >> 4);
				chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
				chr3 = ((enc3 & 3) << 6) | enc4;

				output = output + String.fromCharCode(chr1);

				if (enc3 != 64) {
					output = output + String.fromCharCode(chr2);
				}
				if (enc4 != 64) {
					output = output + String.fromCharCode(chr3);
				}
			} while (i < input.length);

			return output;
		},

		encryptPwd: function (password, len) {
			var fibs = 0;
			var k = 0;
			var input = password;
			if (input.length < len) {
				while (input.length < len) {
					input = input + " ";
				}
			}
			var temp = "";
			// first character in ring is not used.  Added to make the
			// C# 1-based indexing algorithm work.
			var ring = "  !#$%&+-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
			var ringLen = ring.length - 1;
			var fib1 = 0;
			var fib2 = 1;
			for (var i = 0; i < input.length; i++) {
				fibs = fib1 + fib2;
				fib1 = fib2;
				fib2 = fibs;
				var done = true;
				for (var j = 1; j <= ringLen; j++) {
					if (input.substr(i, 1) == ring.substr(j, 1)) {
						if (j + fibs <= ringLen) {
							temp = temp + ring.substr(j + fibs, 1);
						} else {
							k = (j + fibs) % ringLen;
							if (k == 0) {
								k = ringLen;
							}
							temp = temp + ring.substr(k, 1);
						}
						done = false;
						break;
					}
				}
				// char not found
				if (done) {
					return "        ";
				}
			}
			return temp;
		},

		decryptPwd: function (enc) {
			var fibs = 0;
			var k = 0;

			var temp = "";
			var ring = "  !#$%&+-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
			var ringLen = ring.length - 1;
			var fib1 = 0;
			var fib2 = 1;
			for (var i = 0; i < enc.length; i++) {
				fibs = fib1 + fib2;
				fib1 = fib2;
				fib2 = fibs;
				var done = true;
				for (var j = 1; j <= ringLen; j++) {
					if (enc.substr(i, 1) == ring.substr(j, 1)) {
						if (j > fibs) {
							temp = temp + ring.substr(j - fibs, 1);
						} else {
							k = (j - fibs) % ringLen;
							if (k < 0) {
								k = -k;
							}
							k = ringLen - k;
							temp = temp + ring.substr(k, 1);
						}
						done = false;
						break;
					}
				}
				// char not found
				if (done) {
					PACKAGE.Statics.doAlert("A password contains an invalid character. The field will be cleared in the form.  If you save the record without providing a new password, the record will be saved with the cleared password.");
					return "";
				}
			}
			return temp;
		},

		/** Use this when adding items to a toolbar
		*
		* @param toolbar {Object} either a toolbar or a toolbar part
		* @param icon {String}
		* @param tooltip {String}
		* @param action {Function}
		* @param action_this {Object}
		* @param ownerObj {Object}
		* @param shortcut {String}
		* @param label {String}
		*/
		addToToolbarWithShortcut: function (toolbar, icon, tooltip, action, action_this, ownerObj, shortcut, label) {
			// create and configure the command
			label = (label == undefined) ? null : label;
			var command = new qx.ui.command.Command(shortcut);
			command.setLabel(label);
			command.setIcon(icon);
			command.setToolTipText(tooltip);
			command.addListener("execute", action, action_this);
			var button = new qx.ui.toolbar.Button();
			button.setCommand(command);
			toolbar.add(button);
			PACKAGE.Statics.setHtmlID( button, label);

			return button;
		},

		getTableHeight: function (table) {
			var headerHeight = table.getPaneScroller(0).getChildControl("header").getBounds().height;
			var statusbarHeight = table.getChildControl("statusbar").getBounds().height;
			var dataHeight = table.getTableModel().getRowCount() * table.getRowHeight();
			var footerHeight = table.getRowHeight();
			var height = headerHeight + statusbarHeight + dataHeight + footerHeight;

			return height;
		},

		getVisibleRowCapacity: function (table) {
			var headerHeight = table.getPaneScroller(0).getChildControl("header").getBounds().height;
			var statusbarHeight = table.getChildControl("statusbar").getBounds().height;
			var scrollerHeight = table.getRowHeight();
			var height = table.getBounds().height;

			var count = Math.floor((height - headerHeight - statusbarHeight - scrollerHeight) / table.getRowHeight());

			return Math.max(0, count);
		},

		moveRowsUp : function( table ){
			var smodel = table.getSelectionModel();
			var tmodel = table.getTableModel();
			var rowData = tmodel.getData();
			var selection = [];
			if(smodel.isSelectionEmpty()){
				// nothing selected.  bail out.
				return;
			}
			smodel.iterateSelection(function(index){
				selection.push( index );
			} );
			if(selection[0] === 0){ // They've selected the first row
				return; // can't go further up.
			}
			for(var i = 0, l = selection.length; i < l; i++){
				var tmp = rowData[ selection[i] - 1 ]
				rowData[ selection[i] - 1 ] = rowData[ selection[i] ];
				rowData[ selection[i] ] = tmp;
			}
			tmodel.setData( rowData );
			// re-do the selection so that they still see the highlights:
			smodel.resetSelection();
			for(var i = 0, l = selection.length; i < l; i++){
				smodel.addSelectionInterval( selection[i] - 1, selection[i] - 1);
			}
		},

		moveRowsDown : function( table ){
			var smodel = table.getSelectionModel();
			var tmodel = table.getTableModel();
			var rowData = tmodel.getData();
			var selection = [];
			if(smodel.isSelectionEmpty()){
				// nothing selected.  bail out.
				return;
			}
			smodel.iterateSelection(function(index){
				selection.push( index );
			} );
			if(selection[ selection.length - 1 ] === (rowData.length - 1)){ // They've selected the last row
				return; // can't go further down.
			}
			for(var i = selection.length - 1; i >= 0; i--){
				var tmp = rowData[ selection[i] + 1]
				rowData[ selection[i] + 1 ] = rowData[ selection[i] ];
				rowData[ selection[i] ] = tmp;
			}
			tmodel.setData( rowData );
			// re-do the selection so that they still see the highlights:
			smodel.resetSelection();
			for(var i = 0, l = selection.length; i < l; i++){
				smodel.addSelectionInterval( selection[i] + 1, selection[i] + 1);
			}
		},

		compareVersions: function (ver1, ver2) {
			// convert version strings to number
			var tokens = ver1.split(".");
			var major1 = Number(tokens[0]);
			var minor1 = Number(tokens[1]);
			var rev1 = Number(tokens[2]);

			tokens = ver2.split(".");
			var major2 = Number(tokens[0]);
			var minor2 = Number(tokens[1]);
			var rev2 = Number(tokens[2]);

			// return 0:equal, -1:less then, 1:greater than
			if (major1 == major2) {
				if (minor1 == minor2) {
					if (rev1 == rev2) {
						return 0;
					}
					return (rev1 < rev2) ? -1 : 1;
				}
				return (minor1 < minor2) ? -1 : 1;
			}
			return (major1 < major2) ? -1 : 1;
		},

		isNumber : function (n) {
			return !isNaN(parseFloat(n)) && isFinite(n);
		},

		zeroFill : function(number, width) {
			width -= number.toString().length;
			if(width > 0){
				return new Array( width + (/\./.test( number ) ? 2 : 1) ).join( '0' ) + number;
			}
			return number + ""; // always return a string
		},

		isActiveEditor : function (widget) {
			var page = PACKAGE.Statics.findQXParent(widget, qx.ui.tabview.Page);
			return qx.core.Init.getApplication().tabView.isSelected(page);
		},

		/*
		 * Binary data needs to be converted to hex
		*/
		convertToHex : function (value) {
			return "X'" + value.toString(16) + "'";
		},

		/*
		 * Binary data needs to be converted to hex
		*/
		convertToHex2 : function (value) {
			var hexval = "0x";
			for (var i = 0; i < value.length; i++) {
				var hex = value.substr(i,1).charCodeAt(0).toString(16);
				if (hex.length == 1) { hexval += "0"; }
				hexval += hex;
			}
			return hexval;
		},

		getUserFromCurConnection : function() {
			var uprops = ldm.Singleton.getInstance().getUserProperties();
			var curcon = uprops["CurrentConnection"];
			var myregexp = /.*?[(]?(\S+)([@]\S+[:]\S+)/;
			var match = myregexp.exec(curcon);
			return (match[1]) ? match[1] : "";
		}

	}
});
