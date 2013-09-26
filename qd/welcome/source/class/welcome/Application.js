/* ************************************************************************

Copyright:

License:

Authors:

************************************************************************ */

/* ************************************************************************

#asset(welcome/Helix_Cropped_1024_844.jpg)
#asset(welcome/icon/256x256/shadow/astrologer.png)
#asset(welcome/Helix_Cropped_256_211.jpg)
#asset(welcome/icon/256x256/shadow/toolbox.png)
#asset(welcome/Helix_Blue_Cropped_256_256.jpg)

************************************************************************ */

/**
* This is the main application class of your custom application "welcome"
*/
qx.Class.define("welcome.Application",
{
	extend: qx.application.Standalone,

	/* *****************************************************************************
	MEMBERS
	***************************************************************************** */

	members: {

		/**
		* This method contains the initial application code and gets called
		* during startup of the application
		*
		* @lint ignoreDeprecated(alert)
		*/
		main: function () {
			// Call super class
			this.base(arguments);

			// Enable logging in debug variant
			if (qx.core.Environment.get("qx.debug")) {
				// support native logging capabilities, e.g. Firebug for Firefox
				qx.log.appender.Native;
				// support additional cross-browser console. Press F7 to toggle visibility
				qx.log.appender.Console;
			}

			this.HelixVersion = "314.314.314.314";

			/*
			-------------------------------------------------------------------------
			Below is your actual application code...
			-------------------------------------------------------------------------
			*/
			var decorator = new qx.ui.decoration.Background();
			decorator.setBackgroundImage("welcome/Helix_Cropped_1024_844.jpg");
			decorator.setBackgroundRepeat("scale");
			this.getRoot().setDecorator( decorator );

			this.setupHeader();
			this.setupApps();

		},

		setupHeader: function () {
			var hbox = new qx.ui.layout.HBox();
			var header = new qx.ui.container.Composite(hbox);
			header.setHeight(440);
			this.getRoot().add(header, { left: 0, top: 0, right: 0 });

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

			var titleFont = new qx.bom.Font(50, ["Times New Roman"] );
			var title = new qx.ui.basic.Label( "Helix Web Development SDK" );
			title.setFont( titleFont );
			title.setTextColor( "#0179b5" );
			center.add( title );

		},

		setupApps : function () {

			// Application Development
			var dev = this.createButton("Development",
				//"welcome/icon/256x256/shadow/astrologer.png",
				"welcome/Helix_Cropped_256_211.jpg",
				"/qd/dev/build/index.html");
			this.getRoot().add(dev, {left : 20, top: 80 } );

			// Administration
			var admin = this.createButton("Administration",
				//"welcome/icon/256x256/shadow/toolbox.png",
				"welcome/Helix_Blue_Cropped_256_256.jpg",
				"/qd/admin/build/index.html");
			this.getRoot().add(admin, {right: 20, bottom: 80 } );

		},

		createButton : function(label, icon, url) {
			var btn = new qx.ui.form.Button(label, icon);
			var btnFont = new qx.bom.Font( 50, ["Times New Roman"] );
			btn.setFont( btnFont );
			btn.setIconPosition("top");
			btn.addListener("execute", function (e) {
				window.location.assign(url);
			});
			return btn;
		}


	}
});
