/* ************************************************************************

Copyright:

License:

Authors:

************************************************************************ */
/* ************************************************************************
#asset(dev/background-plain.png)
#asset(dev/Helix_Cropped_1024_844.jpg)
#asset(dev/icon/48x48/shadow/arrow2_up_left_blue.png)
#asset(dev/icon/48x48/shadow/arrow2_up_blue.png)
#asset(dev/icon/48x48/shadow/document_ok.png)
#asset(dev/icon/48x48/shadow/question_and_answer.png)
************************************************************************ */
qx.Class.define("dev.HomePage", {
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
			decorator.setBackgroundImage("dev/Helix_Cropped_1024_844.jpg");
			decorator.setBackgroundRepeat("scale");

			var hbox = new qx.ui.layout.HBox();
			var header = new qx.ui.container.Composite(hbox);
			//header.setHeight(440);
			header.setDecorator(decorator);
			this.getChildren()[0].add(header, { left: 0, top: 0, right: 0, bottom: 0 });

		},

		setupTextRow: function () {

			var hbox = new qx.ui.layout.HBox();
			var header = new qx.ui.container.Composite(hbox);
			header.setHeight(145);
			this.getChildren()[0].add(header, { left: 10, top: 10, right: 0 });

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
			"dev/icon/48x48/shadow/arrow2_up_left_blue.png");

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
			"dev/icon/48x48/shadow/arrow2_up_blue.png");

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
				"<p style=\"font-size: 16pt; text-shadow: grey 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:black;\">devboard Monitor<br/>online documentation</p>",
				"dev/icon/48x48/shadow/document_ok.png");
			docs.setIconPosition("left");
			docs.setRich(true);
			docs.setCursor("pointer");
			docs.addListener("click", qx.core.Init.getApplication().showDocs,
				qx.core.Init.getApplication());
			header.add(docs);

			// Questions and Answers
			var hbox2 = new qx.ui.layout.HBox(20);
			var header2 = new qx.ui.container.Composite(hbox2);
			header2.setHeight(145);
			this.getChildren()[0].add(header2, { left: 390, top: 375, right: 0 });

			var qa = new qx.ui.basic.Atom(
				"<p style=\"font-size: 16pt; text-shadow: grey 1px 1px 1px; font-family: QuicksandBold,sans-serif;weight:bold;color:black;\">Helix Q&amp;A<br/>discussion forum</p>",
				"dev/icon/48x48/shadow/question_and_answer.png");
			qa.setIconPosition("left");
			qa.setRich(true);
			qa.setCursor("pointer");
			qa.addListener("click", qx.core.Init.getApplication().showQA,
				qx.core.Init.getApplication());
			header2.add(qa);

		}
	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		dev.Statics.destroyExtraObjects(this);

	}

});
