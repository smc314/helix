/* ************************************************************************

   Copyright: 2008 - 2015 Hericus Software, LLC.

   License: The MIT License

   Authors: Steven M. Cherry

************************************************************************ */

/* ************************************************************************

#asset(login/back.png)
#asset(login/hericus-logo-dots.png)
#asset(login/gears_view.png)
#asset(login/debug.png)
#asset(login/*)

************************************************************************ */

/**
 * This is the main application class of your custom application "login"
 */
qx.Class.define("login.Application",
{
  extend : qx.application.Standalone,



  /*
  *****************************************************************************
     MEMBERS
  *****************************************************************************
  */

  members :
  {
    /**
     * This method contains the initial application code and gets called
     * during startup of the application
     */
    main : function()
    {
      // Call super class
      this.base(arguments);

      // Enable logging in debug variant
      //if (qx.core.Environment.get("qx.debug"))
      //{
        // support native logging capabilities, e.g. Firebug for Firefox
        qx.log.appender.Native;
        // support additional cross-browser console. Press F7 to toggle visibility
        qx.log.appender.Console;
      //}

      /*
      -------------------------------------------------------------------------
        Below is your actual application code...
      -------------------------------------------------------------------------
      */
      this.setupHeader();
      this.setupLogon();

    },

    setupHeader : function () {
    	var decorator = new qx.ui.decoration.Decorator();
    	decorator.setBackgroundImage("login/back.png");
    	decorator.setBackgroundRepeat("repeat-x");
    	var hbox = new qx.ui.layout.HBox();
    	var header = new qx.ui.container.Composite(hbox);
    	header.setHeight(60);
    	header.setDecorator( decorator );
    	this.getRoot().add(header, {left:0, top:0, right:0});

    	this.left_header = new qx.ui.container.Composite(new qx.ui.layout.HBox());
    	var cbox = new qx.ui.layout.HBox();
    	var cheader = new qx.ui.container.Composite(cbox);
    	cbox.setAlignX("center");
    	var rbox = new qx.ui.layout.HBox();
    	var rheader = new qx.ui.container.Composite(rbox);
    	rbox.setAlignX("right");

    	header.add(this.left_header, {width:"38%"});
    	header.add(cheader, {width:"24%"} );
    	header.add(rheader, {width:"38%"});

    	cheader.add(new qx.ui.basic.Image("login/hericus-logo-dots.png"));



    },

    setupLogon : function () {

		var hbox = new qx.ui.container.Composite( new qx.ui.layout.HBox() );
		hbox._getLayout().setAlignX("center");
		var vbox = new qx.ui.container.Composite( new qx.ui.layout.VBox() );
		vbox.setDecorator( "pane" );
		hbox.add(vbox);

    	var zedbox = new qx.ui.container.Composite(new qx.ui.layout.HBox() );
    	zedbox._getLayout().setAlignX("center");
    	vbox.add( zedbox );

    	var atom = new qx.ui.basic.Atom(
    		"<p style=\"font: 28pt/40pt Garamond, Georgia, serif;weight:bold;\">Helix SDK</p>",
    		"login/gears_view.png");
    	atom.setRich(true);
    	atom.setIconPosition("left");
    	zedbox.add( atom );

    	var atom2 = new qx.ui.basic.Atom("", "login/debug.png");
    	atom2.setPaddingLeft(10);
    	zedbox.add(atom2 );


    	/* Container layout */
		var layout = new qx.ui.layout.Grid(9, 5);
		layout.setColumnAlign(0, "left", "top");
		layout.setColumnAlign(2, "left", "top");

		/* Container widget */
		this.__container = new qx.ui.groupbox.GroupBox("Please Login").set( {
			contentPadding : [ 16, 16, 16, 16 ]
		});
		this.__container.setLayout(layout);

		var hbox2 = new qx.ui.container.Composite( new qx.ui.layout.HBox() );
		hbox2._getLayout().setAlignX("center");
		hbox2.add( this.__container );
		vbox.add(hbox2);
		this.getRoot().add(hbox, {top:"10%", left:0, right:0});

		/* Labels */
		var labels = [ "User Name:", "Password:" ];
		for ( var i = 0; i < labels.length; i++) {
			this.__container.add(new qx.ui.basic.Label(labels[i])
					.set( {
						allowShrinkX :false,
						paddingTop :3
					}), {
				row :i,
				column :0
			});
		}

		/* Text fields */
		this.userField = new qx.ui.form.TextField();
		this.passField = new qx.ui.form.PasswordField();

		this.__container.add(this.userField.set( {allowShrinkX :false,paddingTop :3
			}), {row :0, column :1 });

		this.__container.add(this.passField.set( {allowShrinkX :false, paddingTop :3
			}), {row :1, column :1 });

		/* Button */
		var button1 = this.__okButton = new qx.ui.form.Button( "Login");
		button1.setAllowStretchX(false);

		this.__container.add(button1, {row :4,column :1});

		/* Check input on click */
		button1.addListener("execute", this.doLogin, this);

		this.__container.addListenerOnce("appear", function(e) {
			this.userField.focus();
		}, this );

		/* Prepare effect as soon as the container is ready */
		//this.__container.addListener("appear", this.prepareEffect, this);

		this.__container.addListener("keypress",
		function(e){
			if(e.getKeyIdentifier() === "Enter"){
				if(!(e.getTarget() instanceof qx.ui.form.TextArea)){
					button1.press();
					button1.execute();
				}
			}
		}, this );

    },

    doLogin : function () {
		var requestDoc = qx.xml.Document.create(null, "Authenticate");
		var requestRoot = requestDoc.documentElement;
		requestRoot.setAttribute("user", this.userField.getValue());
		requestRoot.setAttribute("pass", this.passField.getValue());

		this.SendRequest( requestDoc, "/Authenticate",
		function(response){
			this.debug("Got a good response - replacing to admin.");
			window.location.replace("/qd/admin/source/index.html");
		},
		function(req){
	    	// if log-in fails, then animate the container:
	        //this.__effect.start();
			this.debug("Got a bad response - refocusing on userfield.");
	        this.userField.selectAll();
	        this.userField.focus();
		} );

    },

	/*
    prepareEffect : function () {
    	this.userField.focus();
    	this.__effect = new qx.fx.effect.combination.Shake(this.__container.getContainerElement().getDomElement());
    },
	*/

	/** This function will walk a zed response XML document and look for
	 * errors in it.  If errors are found, and the doAlert parameter is set
	 * to true, then we will alert to the user that errors were found.
	 * <p>
	 * Returns true if errors were found, and false if no errors were found.
	 *
	 */
	returnHasErrors : function ( response, doAlert ) {
		if(response == null){
			return true;
		}

		// Check the response for errors:
		var error_response = response.getAttribute("haserror");
		if(error_response !== null && error_response === "true"){
			if( doAlert ){
				var errors = response.getElementsByTagName('Errors')[0].getElementsByTagName('Error');
				var err_msg = "";
				for(var i = 0; i < errors.length; i++){
					err_msg = err_msg + errors[i].getAttribute('msg') + "\n\n";
				}
				if(errors.length > 1){
					alert("Errors occurred during processing:\n\n" + err_msg);
				} else {
					alert("Error occurred during processing:\n\n" + err_msg);
				}
			}
			return true;
		}

		return false;
	},

	/** This will setup our request, add all of the callbacks, and
	  * then send the request to the server.
	  */
	SendRequest : function( requestDoc, requestName, callback, errorCallback) {
		var req = new qx.bom.request.Xhr;
		req.onreadystatechange = qx.lang.Function.bind(function() {
			this.debug("In onreadystatechange with readyState = " + req.readyState);
			if(req.readyState != 4){
				return;
			}

			if(!req.responseXML){
				if(errorCallback){
					errorCallback.call(this, req);
				}
				return;
			}

			var response = req.responseXML.documentElement;
			if(this.returnHasErrors( response, true) ){
				if(errorCallback){
					errorCallback.call(this, req);
				}
				return;
			}
			if(callback){
				callback.call(this, response );
			}
		}, this);

		// Now send the request
		req.open("POST", requestName, true);
		req.send(qx.xml.Element.serialize(requestDoc));
	}

  }
});
