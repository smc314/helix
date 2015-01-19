/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/text_rich_colored.png)
#asset(admin/icon/16x16/plain/barcode.png)
#asset(admin/icon/16x16/plain/clipboard_next_down.png)
#asset(admin/icon/16x16/plain/navigate_right2.png)
#asset(admin/icon/16x16/plain/navigate_left2.png)
#asset(admin/icon/16x16/plain/window_height.png)
#asset(admin/icon/16x16/plain/window_width.png)
#asset(admin/icon/16x16/plain/window_split_ver.png)
#asset(admin/icon/16x16/plain/window_split_hor.png)
#asset(admin/icon/16x16/plain/window.png)
#asset(admin/icon/16x16/plain/text_tree.png)
#asset(admin/icon/16x16/plain/text.png)
#asset(admin/icon/16x16/plain/text_rich_marked.png)
#asset(admin/icon/16x16/plain/window_earth.png)
#asset(admin/icon/16x16/plain/table2.png)
#asset(admin/icon/16x16/plain/text_normal.png)
#asset(admin/icon/16x16/plain/ufo.png)
#asset(admin/icon/16x16/plain/table.png)
#asset(admin/icon/16x16/plain/keyboard_key.png)
#asset(admin/icon/16x16/plain/form_blue.png)
#asset(admin/icon/16x16/plain/window_dialog.png)
#asset(admin/icon/16x16/plain/window_logon.png)
#asset(admin/icon/16x16/plain/navigate_check.png)
#asset(admin/icon/16x16/plain/checkbox_unchecked.png)
#asset(admin/icon/16x16/plain/checkbox.png)
#asset(admin/icon/16x16/plain/checks.png)
#asset(admin/icon/16x16/plain/bullet_ball_glass_blue.png)
#asset(admin/icon/16x16/plain/bullet_ball_glass_green.png)
#asset(admin/icon/16x16/plain/bullet_ball_glass_red.png)
#asset(admin/icon/16x16/plain/bullet_ball_glass_red.png)
#asset(admin/icon/16x16/plain/text_bold.png)
************************************************************************ */
qx.Class.define("admin.utils.LayoutEditor", {
	extend: admin.ObjectEdit,

	construct: function (object_id) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({ name: "LayoutEditor.MainPage.xml", doc: null });
		this.dynamicLayouts.push({ name: "LayoutEditor.NextPage.xml", doc: null });

		this.base(arguments, object_id);
	},

	members: {

		/** This is where the subclasses will tell us which API functions to use,
		* which callbacks to use, which names to use, etc.
		*/
		setupNamesAndFunctions: function () {
			this.selectApiCall = admin.Api.GetIAFileDetails;
		},

		/** This function will reset the name of our tab to match our object name.
		*/
		resetTabName: function () {
			var our_page = admin.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return; // couldn't find a tabview.Page parent in the hierarchy
			}
			// Update both our tab page name, and our summary area name.
			our_page.getButton().setLabel(this.dataObject.getFileName());
			this.updateSummaryName(this.dataObject.getFileName());
		},

		/** This function is responsible for initializing our toolbar.  We extend
		* the parent class functionality by adding our own icons and actions.
		*/
		initializeToolbar: function (tb) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb); // Call the parent class first

			// Then add any other actions that you would like here:
			// var part = new qx.ui.toolbar.Part;
			//
			// admin.Statics.addToToolbar( part, "admin/icon/16x16/plain/refresh.png",
			//	"Tooltip for action here", this.actionHandler, this, this);
			//
			// tb.add(part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "Rendering", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		* set of form fields.
		*/
		createMainTab: function (tab_page) {
			var live = this.createOverviewLayout(tab_page,
				"Layout Editor", "admin/icon/64x64/shadow/text_rich_colored.png",
				this.m_object_id === 0 ? "" : this.m_object_id.getFileName());

			this.addStatusHeading("General");
			this.overview_label1 = this.addStatusItem("Overview Label1:",
				"admin/icon/16x16/plain/barcode.png");


			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("LayoutEditor.MainPage.xml"),
				live);


			this.syntaxField.setFont("monospace");
			this.FileContentsField.setFont("monospace");

			//this.layoutFileNameField.addListener("changeSelection", this.loadFile, this);

			// Set up our edit buttons:
			admin.Statics.addToToolbar(this.editButtons,
				"admin/icon/16x16/plain/clipboard_next_down.png", "Copy Syntax into Layout",
				this.copySyntax, this, this);

			admin.Statics.addToToolbar(this.editButtons,
				"admin/icon/16x16/plain/navigate_right2.png", "Indent Selected Text",
				this.indentSelection, this, this);

			admin.Statics.addToToolbar(this.editButtons,
				"admin/icon/16x16/plain/navigate_left2.png", "Un-Indent Selected Text",
				this.outdentSelection, this, this);

			// Set up our syntax buttons:
			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window_height.png", "Vertical Box Layout",
				this.showVerticalBoxLayout, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window_width.png", "Horizontal Box Layout",
				this.showHorizontalBoxLayout, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window_split_ver.png", "Vertical Split Pane",
				this.showVerticalSplitPane, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window_split_hor.png", "Horizontal Split Pane",
				this.showHorizontalSplitPane, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window.png", "Group Box",
				this.showGroupBox, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/text_tree.png", "Tree With Columns",
				this.showTreeVirtual, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/text.png", "Text Area",
				this.showTextArea, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/text_rich_marked.png", "HTML Embed",
				this.showHtmlEmbed, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window_earth.png", "I-Frame",
				this.showIFrame, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/table2.png", "Standard Table",
				this.showStandardTable, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/text_normal.png", "Label",
				this.showLabel, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/ufo.png", "Spacer",
				this.showSpacer, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/table.png", "List",
				this.showList, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/keyboard_key.png", "Button",
				this.showButton, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/form_blue.png", "Field Area",
				this.showFieldArea, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window_dialog.png", "Field Area - Double Field",
				this.showDoubleField, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/window_logon.png", "Field Area - Span Field",
				this.showSpanField, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/navigate_check.png", "Field Area - Single Check",
				this.showSingleCheck, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/checkbox_unchecked.png", "Field Area - Double Check",
				this.showDoubleCheck, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/checkbox.png", "Field Area - Double Check 2",
				this.showDoubleCheck2, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/checks.png", "Field Area - Quad Check",
				this.showQuadCheck, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/bullet_ball_glass_blue.png", "Field Area - Radio Group 2",
				this.showRadioGroup2, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/bullet_ball_glass_green.png", "Field Area - Radio Group 3",
				this.showRadioGroup3, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/bullet_ball_glass_red.png", "Field Area - Radio Group 4",
				this.showRadioGroup4, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/bullet_ball_glass_red.png", "Field Area - Horizontal Radio Group 4",
				this.showRadioGroup5, this, this);

			admin.Statics.addToToolbar(this.layoutButtons,
				"admin/icon/16x16/plain/text_bold.png", "Field Area - Long Label",
				this.showLongLabel, this, this);

		},

		copySyntax: function () {
			var syntax = this.syntaxField.getValue();
			var cursor = this.FileContentsField.getTextSelectionStart();
			if (cursor === null) {
				cursor = 0;
			}
			var contents = this.FileContentsField.getValue();
			if (contents === null) {
				contents = "";
			}
			if (cursor === 0) {
				contents = syntax + "\n" + contents;
				this.FileContentsField.setValue(contents);
			} else if (cursor === contents.length - 1) {
				contents = contents + "\n" + syntax;
				this.FileContentsField.setValue(contents);
			} else {
				var first = contents.substr(0, cursor);
				var second = contents.substr(cursor, contents.length - cursor);
				contents = first + "\n" + syntax + "\n" + second;
				this.FileContentsField.setValue(contents);
			}
		},

		indentSelection: function () {
			var contents = this.FileContentsField.getValue();
			if (contents === null) {
				return; // nothing to do.
			}
			var selection = this.FileContentsField.getTextSelection();
			if (selection === null) {
				return; // nothing to do.
			}
			var start = this.FileContentsField.getTextSelectionStart();
			var end = this.FileContentsField.getTextSelectionEnd();

			var first = contents.substr(0, start);
			var last = contents.substr(end);

			var lines = selection.split("\n");
			contents = first;
			for (var i = 0, l = lines.length; i < l; i++) {
				contents = contents + "\t" + lines[i] + "\n";
			}
			contents = contents + last;
			this.FileContentsField.setValue(contents);
			this.FileContentsField.setTextSelection(start, end + lines.length);
		},

		outdentSelection: function () {
			var contents = this.FileContentsField.getValue();
			if (contents === null) {
				return; // nothing to do.
			}
			var selection = this.FileContentsField.getTextSelection();
			if (selection === null) {
				return; // nothing to do.
			}
			var start = this.FileContentsField.getTextSelectionStart();
			var end = this.FileContentsField.getTextSelectionEnd();

			var first = contents.substr(0, start);
			var last = contents.substr(end);

			var lines = selection.split("\n");
			contents = first;
			for (var i = 0, l = lines.length; i < l; i++) {
				contents = contents + lines[i].substr(1) + "\n";
			}
			contents = contents + last;
			this.FileContentsField.setValue(contents);
			this.FileContentsField.setTextSelection(start, end - lines.length);
		},

		showVerticalBoxLayout: function () {
			this.syntaxField.setValue(
				"<VerticalBoxLayout varName=\"optionalVariableName\" spacing=\"0\" flex=\"1\" >\n" +
				"\t<!-- Layout Contents go here. -->\n" +
				"</VerticalBoxLayout>"
			);
		},

		showHorizontalBoxLayout: function () {
			this.syntaxField.setValue(
				"<HorizontalBoxLayout varName=\"optionalVariableName\" spacing=\"0\" flex=\"1\" >\n" +
				"\t<!-- Layout Contents go here. -->\n" +
				"</HorizontalBoxLayout>"
			);
		},

		showVerticalSplitPane: function () {
			this.syntaxField.setValue(
				"<VerticalSplitPane varName=\"optionalVariableName\" leftsize=\"1\" rightsize=\"1\" >\n" +
				"\t<!-- leftsize and rightsize are flex settings for the first and second halves. -->\n" +
				"\t<VerticalSplitPaneTop>\n" +
				"\t\t<!-- Top pane layout items go here.  \n" +
				"\t\tUsually start with a Vertical or Horizontal Box Layout -->\n" +
				"\t</VerticalSplitPaneTop>\n" +
				"\t<VerticalSplitPaneBottom>\n" +
				"\t\t<!-- Bottom pane layout items go here.  \n" +
				"\t\tUsually start with a Vertical or Horizontal Box Layout -->\n" +
				"\t</VerticalSplitPaneBottom>\n" +
				"</VerticalSplitPane>"
			);
		},

		showHorizontalSplitPane: function () {
			this.syntaxField.setValue(
				"<HorizontalSplitPane varName=\"optionalVariableName\" leftsize=\"1\" rightsize=\"1\" >\n" +
				"\t<!-- leftsize and rightsize are flex settings for the first and second halves. -->\n" +
				"\t<HorizontalSplitPaneLeft>\n" +
				"\t\t<!-- Left pane layout items go here.  \n" +
				"\t\tUsually start with a Vertical or Horizontal Box Layout -->\n" +
				"\t</HorizontalSplitPaneLeft>\n" +
				"\t<HorizontalSplitPaneRight>\n" +
				"\t\t<!-- Right pane layout items go here.  \n" +
				"\t\tUsually start with a Vertical or Horizontal Box Layout -->\n" +
				"\t</HorizontalSplitPaneRight>\n" +
				"</HorizontalSplitPane>"
			);
		},

		showGroupBox: function () {
			this.syntaxField.setValue(
				"<GroupBox varName=\"optionalVariableName\" legend=\"Group Box Label\" flex=\"1\" >\n" +
				"\t<!-- Optional attributes include isCheck=\"true\" and isRadio=\"true\". \n" +
				"\tIf you use either of those, the varName attribute is more important. -->\n" +
				"\t<!-- Layout Contents go here. -->\n" +
				"</GroupBox>"
			);
		},

		showTreeVirtual: function () {
			this.syntaxField.setValue(
				"<TreeVirtual varName=\"variableName\" flex=\"1\" >\n" +
				"\t<Column title=\"Column Title\" width=\"1*\" minWidth=\"50\" maxWidth=\"250\"/>\n" +
				"\t<Column title=\"Second Column\" width=\"1*\" minWidth=\"50\" maxWidth=\"250\"/>\n" +
				"\t<Column title=\"Third Column\" width=\"1*\" minWidth=\"50\" maxWidth=\"250\"/>\n" +
				"\t<!-- width, minWidth, maxWidth are all optional but allow you to customize\n" +
				"\tthe size of the columns.  width is a flex attribute if you include the trailing *.\n" +
				"\tminWidth and maxWidth are absolute values.-->\n" +
				"</TreeVirtual>"
			);
		},

		showTextArea: function () {
			this.syntaxField.setValue(
				"<TextArea varName=\"variableName\" flex=\"1\" wrap=\"true\" allowGrowX=\"true\" allowGrowY=\"true\"/>\n"
			);
		},

		showHtmlEmbed: function () {
			this.syntaxField.setValue(
				"<HtmlEmbed varName=\"variableName\" flex=\"1\" allowStetchX=\"true\" allowStretchY=\"true\"/>\n"
			);
		},

		showIFrame: function () {
			this.syntaxField.setValue(
				"<IFrame varName=\"variableName\" flex=\"1\"/>\n"
			);
		},

		showStandardTable: function () {
			this.syntaxField.setValue(
				"<StandardTable varName=\"variableName\" flex=\"1\" >\n" +
				"\t<Column title=\"Column Title\" width=\"1*\" minWidth=\"50\" maxWidth=\"250\"/>\n" +
				"\t<Column title=\"Second Column\" width=\"1*\" minWidth=\"50\" maxWidth=\"250\"/>\n" +
				"\t<Column title=\"Third Column\" width=\"1*\" minWidth=\"50\" maxWidth=\"250\"/>\n" +
				"\t<!-- width, minWidth, maxWidth are all optional but allow you to customize\n" +
				"\tthe size of the columns.  width is a flex attribute if you include the trailing *.\n" +
				"\tminWidth and maxWidth are absolute values.-->\n" +
				"</StandardTable>"
			);
		},

		showLabel: function () {
			this.syntaxField.setValue(
				"<Label text=\"Something relevant to point out:\" paddingTop=\"3\"/>\n"
			);
		},

		showSpacer: function () {
			this.syntaxField.setValue(
				"<Spacer flex=\"3\"/>\n"
			);
		},

		showList: function () {
			this.syntaxField.setValue(
				"<List varName=\"variableName\" flex=\"3\"/>\n"
			);
		},

		showButton: function () {
			this.syntaxField.setValue(
				"<Button varName=\"variableName\" label=\"Do Something\"/>\n"
			);
		},

		showFieldArea: function () {
			this.syntaxField.setValue(
				"<FieldArea first=\"80\" second=\"80\">\n" +
				"\t<!-- A Field area is designed to layout fields on a form arranged in\n" +
				"\ttwo columns.  Fields can span columns if required, and fields are not\n" +
				"\trequired in the right hand column.  The first and second attributes above\n" +
				"\tare used to reserve space for the field labels, so that all of the fields\n" +
				"\twill align properly. -->\n" +
				"\t<!-- Field Area Contents go here. -->\n" +
				"</FieldArea>"
			);
		},

		showDoubleField: function () {
			this.syntaxField.setValue(
				"<!-- The DoubleField lays out 2 fields on a single line in your form. -->\n" +
				"<DoubleField varName1=\"name1Field\" label1=\"Field Label:\" type1=\"TextField\"\n" +
				"\ttooltip1=\"Optional tooltip text goes here.\"\n" +
				"\tverify1=\"true\" verify1type=\"string\" verify1min=\"0\" verify1max=\"20\" upper1=\"true\" required1=\"false\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Second Label:\" type2=\"TextField\"\n" +
				"\ttooltip2=\"Optional tooltip text goes here.\"\n" +
				"\tverify2=\"true\" verify2type=\"int\" verify2min=\"0\" verify2max=\"65536\" upper2=\"false\" required2=\"false\"\n" +
				"/>\n" +
				"<!-- Options for type1/type2 are:\n" +
				"\tTextField - standard single line text field\n" +
				"\tPasswordField - TextField with the password flag turned on\n" +
				"\tComboBox - Select only drop-down combo box\n" +
				"\tComboBoxEdit - Editable drop-down combo box\n" +
				"\tTextArea (type1 only) - Multi-line text field. Use height1=\"80\" to control\n" +
				"\t\tthe hight of this field.\n" +
				"\tSpacer (type2 only) - use this with an empty varName2 and label2=\" \" to \n" +
				"\t\tskip the second field on the line.\n" +
				"-->"
			);
		},

		showSpanField: function () {
			this.syntaxField.setValue(
				"<!-- The SpanField lays out 1 field that spans both columns in your form. -->\n" +
				"<SpanField varName1=\"name1Field\" label1=\"Field Label:\" type1=\"TextField\"\n" +
				"\ttooltip1=\"Optional tooltip text goes here.\"\n" +
				"\tverify1=\"true\" verify1type=\"string\" verify1min=\"0\" verify1max=\"20\" upper1=\"true\" required1=\"false\"\n" +
				"/>"
			);
		},

		showDoubleCheck: function () {
			this.syntaxField.setValue(
				"<!-- The DoubleCheck lays out 2 check-boxes on a single line. -->\n" +
				"<DoubleCheck varName1=\"name1Field\" label1=\"Do Action?\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Do Second Action?\" />"
			);
		},

		showDoubleCheck2: function () {
			this.syntaxField.setValue(
				"<!-- The DoubleCheck2 lays out 2 check-boxes on a single line\n" +
				"and allows you to specify exactly how wide they each are.  This is useful for\n" +
				"aligning multiple rows of check boxes in a form.\n" +
				"-->\n" +
				"<DoubleCheck2 varName1=\"name1Field\" label1=\"Do Action?\" width1=\"120\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Do Second Action?\" width2=\"140\" />"
			);
		},

		showQuadCheck: function () {
			this.syntaxField.setValue(
				"<!-- The QuadCheck lays out 4 check-boxes on a single line\n" +
				"and allows you to specify exactly how wide they each are.  This is useful for\n" +
				"aligning multiple rows of check boxes in a form.\n" +
				"-->\n" +
				"<QuadCheck varName1=\"name1Field\" label1=\"Do Action?\" width1=\"120\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Do Second Action?\" width2=\"140\"\n" +
				"\tvarName3=\"name3Field\" label3=\"Do Third Action?\" width3=\"140\"\n" +
				"\tvarName4=\"name4Field\" label4=\"Do Fourth Action?\" width4=\"140\"/>"
			);
		},

		showSingleCheck: function () {
			this.syntaxField.setValue(
				"<!-- The SingleCheck lays out 1 check-box on a single line. -->\n" +
				"<SingleCheck varName1=\"name1Field\" label1=\"Do Action?\"/>"
			);
		},

		showRadioGroup2: function () {
			this.syntaxField.setValue(
				"<!-- The RadioGroup2 lays out 2 radio buttons vertically. -->\n" +
				"<RadioGroup2 groupName=\"groupField\" \n" +
				"\tvarName1=\"name1Field\" label1=\"Do This Action?\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Or This Action?\"/>"
			);
		},

		showRadioGroup3: function () {
			this.syntaxField.setValue(
				"<!-- The RadioGroup3 lays out 3 radio buttons vertically. -->\n" +
				"<RadioGroup3 groupName=\"groupField\"\n" +
				"\tvarName1=\"name1Field\" label1=\"Do This Action?\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Or This Action?\"\n" +
				"\tvarName3=\"name3Field\" label3=\"Or That Action?\"/>"
			);
		},

		showRadioGroup4: function () {
			this.syntaxField.setValue(
				"<!-- The RadioGroup4 lays out 4 radio buttons vertically. -->\n" +
				"<RadioGroup4 groupName=\"groupField\"\n" +
				"\tvarName1=\"name1Field\" label1=\"Do This Action?\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Or This Action?\"\n" +
				"\tvarName3=\"name3Field\" label3=\"Or That Action?\"\n" +
				"\tvarName4=\"name4Field\" label4=\"Or Something Else?\"/>"
			);
		},

		showRadioGroup4: function () {
			this.syntaxField.setValue(
				"<!-- The RadioGroup5 lays out 4 radio buttons horizontally with an optional label prefix. -->\n" +
				"<RadioGroup5 groupName=\"groupField\" labelPrefix=\"Four Options:\"\n" +
				"\tvarName1=\"name1Field\" label1=\"Do This Action?\"\n" +
				"\tvarName2=\"name2Field\" label2=\"Or This Action?\"\n" +
				"\tvarName3=\"name3Field\" label3=\"Or That Action?\"\n" +
				"\tvarName4=\"name4Field\" label4=\"Or Something Else?\"/>"
			);
		},

		showLongLabel: function () {
			this.syntaxField.setValue(
				"<!-- The Long Label lays out a single label than can be as wide as the form. -->\n" +
				"<LongLabel label=\"This says something about whatever comes below...\"/>"
			);
		},



		/** This creates a standard tab that is controlled by the layout page
		* rendered onto it.
		*/
		createNextTab: function (tab_page) {
			this.renderingPage = tab_page;
			this.tabview.addListener("changeSelection", function (obj) {

				// Remove all of the existing layout children.
				if (this.renderingPage.getChildren().length !== 0) {
					this.renderingPage.remove(this.renderingPage.getChildren()[0]);
					//this.renderingPage.setLayout( new qx.ui.layout.VBox() );
				}

				// Re-render the layout based on the current contents field.
				admin.layout.LayoutEngine.renderLayout(this,
					this.FileContentsField.getValue(),
					this.renderingPage);

			}, this);
		},

		/** This allows our subclasses to do something in the scenario where the
		* edit view is opened up for a brand new object.
		*/
		initializeNewObject: function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = true;
			this.dataObject = new admin.sqldo.IAFile();
			this.dataObject.setFileName("NEW1");

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		loadFile: function (e) {
			if (this.layoutFileNameField.isSelectionEmpty()) {
				return; // Nothing to do.
			}
			var fileName = this.layoutFileNameField.getSelection()[0].getModel();
			if (fileName === "<New>") {
				// Nothing to load for this one
				return;
			}

			// The name is in the short form of package/file, split this up so that
			// we can send in the real path to the file:
			var splits = fileName.split("/");
			var realName = "/qd/" + splits[0] + "/source/layouts/" + splits[1];
			admin.Api.LoadXMLDoc(realName, function (response) {
				var xmlDoc = response.ownerDocument;
				this.FileContentsField.setValue(admin.Statics.xmlDocToString(xmlDoc));
			}, this);


		},

		/** This method is called by the "get" API function and should be prepared to read
		* our data object from the XML sent back to us by the server.
		*/
		getObjectDetails: function (response) {
			var objectList = admin.sqldo.IAFile.readElementChildren(response);
			if (objectList.length === 0) {
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.isNewObject = false;
			this.loadDataIntoForm();
			this.resetDirty();
		},

		/** This handles loading our GUI form fields based on the information contained
		* in our data object.
		*/
		loadDataIntoForm: function () {
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			admin.Statics.loadAllFields(this, this.dataObject);


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

		},

		/** This handles pulling data from GUI form fields and loading their values
		* back into our data object.
		*/
		pullDataFromForm: function () {
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* pulling all fields that are registered in this object   */
			/* directly from our form and saving them to the dataObject*/
			/* ******************************************************* */
			admin.Statics.pullAllFields(this, this.dataObject);

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

		},

		/** This handles verifying all of our form fields prior to saving the
		* record back to the server.
		*/
		verifyFields: function () {
			// Use the built-in verification to do as much work for us as possible:
			if (admin.Statics.verifyAllFields(this) === -1) return -1;

			// Then do any special verification required here:

			// If everything is ok, return 0
			return 0;
		},

		/** This handles the calls required to save our dataObject back to the
		* server.
		*/
		doSaveToServer: function () {
			if(this.verifyFields() === -1){
				return; // Don't save an invalid object
			}
			this.pullDataFromForm();
			if(this.isNewObject === true){
				admin.Api.SaveIAFile( this.dataObject, function(response){
					// Pick up any new information here
					var objectList = admin.sqldo.IAFile.readElementChildren( response );
					if(objectList.length != 0){
						this.dataObject = objectList[0];
					}
					this.isNewObject = false;

					// Updates our tab name and the overview name
					this.resetTabName( this.dataObject.getFileName() );

					this.loadDataIntoForm(); // Get's all of our overview labels

					this.resetDirty();

					// Remember to add the new guy to the tree
					// ...
				}, this);
			} else {
				admin.Api.SaveIAFile( this.dataObject, function (response) {
					// pick up any new information here
					this.loadDataIntoForm(); // Gets all of our overview labels
					this.resetTabName( this.dataObject.getFileName() );
					this.resetDirty();
				}, this);
			}
		}


	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		this._disposeObjects(
			"tabview",
			"dataObject",
			"m_object_id"
		);
		admin.Statics.destroyExtraObjects(this);
	}

});
