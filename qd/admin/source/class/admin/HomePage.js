/* ************************************************************************

Copyright:

License:

Authors:

************************************************************************ */
/* ************************************************************************
#asset(admin/background-plain.png)
#asset(admin/background-overlay.png)
#asset(admin/icon/48x48/shadow/arrow2_up_left_blue.png)
#asset(admin/icon/48x48/shadow/arrow2_up_blue.png)
#asset(admin/icon/48x48/shadow/document_ok.png)
#asset(admin/icon/48x48/shadow/question_and_answer.png)
#asset(admin/ivory-director-transparent.png)
************************************************************************ */
qx.Class.define("admin.HomePage", {
	extend: qx.ui.container.Scroll,

	construct: function (object_id) {
		this.base(arguments, new qx.ui.container.Composite(new qx.ui.layout.Canvas()));

		this.doFormLayout();
	},

	members: {

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {
			this.setupHeader();
			this.setupTextRow();
			this.setupTreeText();
			this.setupMenuText();
			this.setupButtonRow2();
		},

		setupHeader: function () {
			var decorator = new qx.ui.decoration.Decorator();
			decorator.setBackgroundImage("admin/background-plain.png");
			decorator.setBackgroundRepeat("repeat-x");

			var hbox = new qx.ui.layout.HBox();
			var header = new qx.ui.container.Composite(hbox);
			header.setHeight(440);
			header.setDecorator(decorator);
			this.getChildren()[0].add(header, { left: 0, top: 0, right: 0 });

			var left = new qx.ui.container.Composite(new qx.ui.layout.HBox());
			var cbox = new qx.ui.layout.HBox();
			var center = new qx.ui.container.Composite(cbox);
			cbox.setAlignX("center");
			var rbox = new qx.ui.layout.HBox();
			var right = new qx.ui.container.Composite(rbox);
			rbox.setAlignX("right");

			header.add(left, { flex: 1 });
			header.add(center, { flex: 1 });
			header.add(right, { flex: 1 });

			center.add(new qx.ui.basic.Image("admin/background-overlay.png"));
		},

		setupTextRow: function () {

			var hbox = new qx.ui.layout.HBox();
			var header = new qx.ui.container.Composite(hbox);
			header.setHeight(145);
			this.getChildren()[0].add(header, { left: 0, top: 10, right: 0 });

			var app = qx.core.Init.getApplication();

			var atom = new qx.ui.basic.Atom(
			"<p style=\"font-size: 24pt; text-shadow: black 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:white;\">" + app.ApplicationName + "<br/>" +
			"<span style=\"font-size: 16pt;\">Version " + app.ViaHubVersion + "</span></p>");

			atom.setRich(true);
			atom.setIconPosition("right");
			header.add(atom);

		},

		setupTreeText: function () {

			var hbox = new qx.ui.layout.HBox();
			var header = new qx.ui.container.Composite(hbox);
			header.setHeight(145);
			this.getChildren()[0].add(header, { left: 40, top: 250, right: 0 });

			var atom = new qx.ui.basic.Atom(
			"<p style=\"font-size: 16pt; text-shadow: grey 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:black;\">Use the tree at the left<br/>to select a server<br/>to monitor.</p>",
			"admin/icon/48x48/shadow/arrow2_up_left_blue.png");

			atom.setRich(true);
			atom.setIconPosition("left");
			header.add(atom);

		},

		setupMenuText: function () {

			var hbox = new qx.ui.layout.HBox();
			var header = new qx.ui.container.Composite(hbox);
			header.setHeight(145);
			this.getChildren()[0].add(header, { left: 390, top: 250, right: 0 });

			var atom = new qx.ui.basic.Atom(
			"<p style=\"font-size: 16pt; text-shadow: grey 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:black;\">Use the menus at the top<br/>to connect to servers,<br/>use tools and switch applications.</p>",
			"admin/icon/48x48/shadow/arrow2_up_blue.png");

			atom.setRich(true);
			atom.setIconPosition("left");
			header.add(atom);

		},

		setupButtonRow2: function () {

			var hbox = new qx.ui.layout.HBox(20);
			var header = new qx.ui.container.Composite(hbox);
			header.setHeight(145);
			this.getChildren()[0].add(header, { left: 40, top: 375, right: 0 });

			// OnLine Documentation
			var docs = new qx.ui.basic.Atom(
				"<p style=\"font-size: 16pt; text-shadow: grey 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:black;\">adminboard Monitor<br/>online documentation</p>",
				"admin/icon/48x48/shadow/document_ok.png");
			docs.setIconPosition("left");
			docs.setRich(true);
			docs.setCursor("pointer");
			docs.addListener("click", qx.core.Init.getApplication().showDocs,
				qx.core.Init.getApplication());
			header.add(docs);

			// Questions and Answers
			/*
			var hbox2 = new qx.ui.layout.HBox(20);
			var header2 = new qx.ui.container.Composite(hbox2);
			header2.setHeight(145);
			this.getChildren()[0].add(header2, { left: 390, top: 375, right: 0 });

			var qa = new qx.ui.basic.Atom(
				"<p style=\"font-size: 16pt; text-shadow: grey 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:black;\">Ivory Hub Q&amp;A<br/>discussion forum</p>",
				"admin/icon/48x48/shadow/question_and_answer.png");
			qa.setIconPosition("left");
			qa.setRich(true);
			qa.setCursor("pointer");
			qa.addListener("click", qx.core.Init.getApplication().showQA,
				qx.core.Init.getApplication());
			header2.add(qa);
			*/

			// Ivory Director Logo
			var hbox3 = new qx.ui.layout.HBox(20);
			var header3 = new qx.ui.container.Composite(hbox3);
			header3.setHeight(267);
			this.getChildren()[0].add(header3, { left: 160, top: 500, right: 0 });

			var logo = new qx.ui.basic.Atom( "", "admin/ivory-director-transparent.png");
			logo.setIconPosition("left");
			header3.add(logo);

		}
	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		admin.Statics.destroyExtraObjects(this);

	}

});
