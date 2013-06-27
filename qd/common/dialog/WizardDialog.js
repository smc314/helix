/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(PACKAGE/icon/16x16/plain/arrow2_left_blue.png)
#asset(PACKAGE/icon/16x16/plain/arrow2_right_blue.png)
#asset(PACKAGE/icon/16x16/plain/ok.png)
#asset(PACKAGE/icon/16x16/plain/error.png)
************************************************************************ */


/** This class defines a simple dialog base class that defines a dialog window
  * with an OK and Cancel button.
  */
qx.Class.define("PACKAGE.dialog.WizardDialog", {
	extend : qx.ui.window.Window,

	/** You may pass in window title.
	  */
	construct : function ( title, icon ) {
		this.base( arguments, title );

		// These are the values we capture and the caller can 
		// interrogate to find out how things went
		this.okPressed = false;
		
		this.wizardForms = {};
		this.formList = [];
		this.backHistory = [];
		this.firstForm = "";
		this.currentForm = "";
		this.currentFormIdx = 0;
		this.currentFormClass = null;
		
		this.doSetSpace();
		this.setModal(true);
		this.setShowClose(false);
		this.setShowMaximize(false);
		this.setShowMinimize(false);
		this.setAllowMinimize(false);
		this.addListenerOnce("resize", this.center, this);
		this.setLayout( new qx.ui.layout.VBox(10) );

		var full_layout = new qx.ui.container.Composite(new qx.ui.layout.HBox(10, null, "separator-horizontal"));
		this.add(full_layout, {flex:1});
		
		var icon_text_layout = new qx.ui.container.Composite(new qx.ui.layout.VBox(10));
		icon_text_layout.set({ width: 200, maxWidth:200});
		full_layout.add( icon_text_layout );
		
		this.child_layout = new qx.ui.container.Composite(new qx.ui.layout.VBox(10));
		full_layout.add( this.child_layout, {flex:1} );
		
		this.image = new qx.ui.basic.Image( icon );
		icon_text_layout.add(this.image);
		
		this.caption = new qx.ui.basic.Label(  );
		this.caption.set({rich:true, width:180});
		this.caption.setValue( "This is some text that should end up being wrapped, and will describe what is happening in this wizard.  Each page of the wizard may update this text to help the user understand what it is that they are supposed to do on each page.");
		icon_text_layout.add( this.caption, {flex:1} );
		
		// Previous/Next Finish Cancel Buttons
		var hbox = new qx.ui.layout.HBox(10);
		var hbl = new qx.ui.container.Composite(hbox);
		hbl.set({paddingTop:0, paddingBottom:2});
		hbox.setAlignX("right");
		this.prev_btn = new qx.ui.form.Button(this.tr("Back"), "PACKAGE/icon/16x16/plain/arrow2_left_blue.png");
		this.prev_btn.setIconPosition("left");
		hbl.add(this.prev_btn);
		this.next_btn = new qx.ui.form.Button(this.tr("Next"), "PACKAGE/icon/16x16/plain/arrow2_right_blue.png");
		this.next_btn.setIconPosition("right");
		hbl.add(this.next_btn);
		var sp1 = new qx.ui.core.Spacer();
		sp1.setWidth(10);
		hbl.add(sp1);
		this.ok_btn = new qx.ui.form.Button(this.tr("Finish"), "PACKAGE/icon/16x16/plain/ok.png");
		hbl.add(this.ok_btn);
		var sp2 = new qx.ui.core.Spacer();
		sp2.setWidth(10);
		hbl.add(sp2);
		this.close_btn = new qx.ui.form.Button(this.tr("Cancel"), "PACKAGE/icon/16x16/plain/error.png");
		hbl.add(this.close_btn);

		this.prev_btn.addListener("execute", this.backButtonPressed, this);
		this.next_btn.addListener("execute", this.nextButtonPressed, this);
		
		this.ok_btn.addListener("execute", function() {
			this.okPressed = true;
			// Pull whatever data is in the current form.
			var form = this.wizardForms[ this.currentForm ];
			form.pullDataFromForm();

			if(this.doFinish()){
				this.close();
				qx.core.Init.getApplication().getRoot().remove(this);
			}
		}, this);

		this.close_btn.addListener("execute", function() {
			this.okPressed = false;
			this.doClose();
			this.close();
			qx.core.Init.getApplication().getRoot().remove(this);
		}, this);


		this.add(hbl);
	},
	
	members : {

		/** Allows you to add an event listener to our OK button.
		  */
		addOkEventListener : function (event_name, event_fcn, event_this) {
			this.ok_btn.addListener(event_name, event_fcn, event_this);
		},

		/** Allows you to add an event listener to our Cancel button.
		  */
		addCancelEventListener : function (event_name, event_fcn, event_this) {
			this.close_btn.addListener(event_name, event_fcn, event_this);
		},
		
		/** This method is called when the user has pressed the Finish
		  * button, but before the dialog is closed.  Handle any tasks that
		  * are required when the user has completed the wizard.
		  * 
		  * @return true if the doFinish is successful, false if anything went wrong.
		  *         If false is returned, the wizard dialog will not be closed.
		  */
		doFinish : function () {
			return true; // success.
		},
		
		/** last chance to cleanup */
		doClose : function () {
		},

		/** This method is triggered any time the back button is pressed.
		  */
		backButtonPressed : function ( e ) {
			// unload the current form
			var form = this.wizardForms[ this.currentForm ];
			form.pullDataFromForm();
			
			var next_name = this.backHistory.pop();
			if(!next_name){
				// for some reason there's nothing left in the back history.
				// bail out.
				return;
			} else {
				// find the new form name in the formList, so that we can
				// keep our currentFormIdx accurate:
				for(var i = 0, l = this.formList.length; i < l; i++){
					if(this.formList[i] === next_name){
						this.currentFormIdx = i;
						break;
					}
				}
			}
			
			// clear the GUI
			this.clearFormLayout();
			
			// switch to the next form
			this.currentForm = next_name;
			form = this.wizardForms[ this.currentForm ];
			this.currentFormClass = form;
			this.child_layout.add( form ); // display the form
			form.loadDataIntoForm(); // tell it that it's up.
			
			if(this.backHistory.length == 0){ // they've gone all the way to the beginning
				this.updateButtons( false, true, this.enableFinish(), null); // disable the back button
			}
			this.updateButtons( null, true, this.enableFinish(), null); // enable the next button
		},

		/** This method is triggered any time the next button is pressed.
		  */
		nextButtonPressed : function ( e ) {
			var form = this.wizardForms[ this.currentForm ];
			form.pullDataFromForm();
			var next_name = form.getNextFormName();
			if(!next_name){
				// forms are not telling us where to go next.  Pick the
				// next form from the original list of forms as they were added
				next_name = this.formList[ this.currentFormIdx + 1 ];
				this.currentFormIdx += 1;
			} else {
				// find the new form name in the formList, so that we can
				// keep our currentFormIdx accurate:
				for(var i = 0, l = this.formList.length; i < l; i++){
					if(this.formList[i] === next_name){
						this.currentFormIdx = i;
						break;
					}
				}
			}
			
			// add the current form to the back history before we switch to
			// the new form.
			this.backHistory.push( this.currentForm );
			
			// unload the GUI
			this.clearFormLayout();
			
			// switch to the next form
			this.currentForm = next_name;
			form = this.wizardForms[ this.currentForm ];
			this.currentFormClass = form;
			this.child_layout.add( form ); // display the form
			form.loadDataIntoForm(); // tell it that it's up.

			if(this.currentFormIdx === ( this.formList.length - 1 ) ){ // we're at the end of the forms
				this.updateButtons(true, false, this.enableFinish(), null);
			}
			this.updateButtons( true, null, this.enableFinish(), null); // ensure the back button is enabled.
		},

		/** Returns whether the OK button was pressed to exit the dialog.
		  * True if OK was pressed, False if any other method was used to
		  * exit the dialog.
		  */
		getOkPressed : function() {
			return this.okPressed;
		},
		
		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function () {
			this.setWidth(700);
			this.setHeight(450);
		},
		
		/** This method will clear all widgets from the child layout that is used
		  * to display the form to the user.
		  */
		clearFormLayout : function () {
			this.child_layout.removeAll();
		},
		
		/** This method allows you to update the icon that is displayed on the
		  * left side of the wizard.  Use a 128 size icon, or it will look small.
		  */
		updateIcon : function ( icon ) {
			this.image.setSource( icon );
		},
		
		/** This method allows you to update the caption that is displayed on the
		  * left side of the wizard.
		  */
		updateCaption : function ( text ){
			this.caption.setValue( text );
		},
		
		/** This allows you to change the state of our back/next/finish/cancel
		  * buttons.
		  */
		updateButtons : function( backEnabled, nextEnabled, finishEnabled, cancelEnabled) {
			if(backEnabled !== null){
				this.prev_btn.setEnabled(backEnabled);
			}
			if( nextEnabled !== null){
				this.next_btn.setEnabled(nextEnabled);
			}
			if(finishEnabled !== null){
				this.ok_btn.setEnabled(finishEnabled);
			}
			if(cancelEnabled !== null){
				this.close_btn.setEnabled(cancelEnabled);
			}
		},
		
		/** This method should be overridden by our children and used to indicate
		  * whether or not the finish button should be enabled.  This is called
		  * every time the back or next button is pressed.
		  */
		enableFinish : function () {
			return false;
		},
		
		/** This allows you to add a wizard form to our list that will be displayed
		  * to the user.
		  */
		addWizardForm : function ( name, form ) {
			this.wizardForms[name] = form;
			this.formList.push( name );
			form.setWizard( this ); // give the form a pointer back to us.
		},
		
		/** Tell us which wizard form is the first, by using this method.
		  */
		setStartForm : function ( name ){
			this.firstForm = name;
			this.clearFormLayout(); // get rid of anything that is there
			this.child_layout.add( this.wizardForms[ this.firstForm ] ); // display the first form
			this.wizardForms[ this.firstForm ].loadDataIntoForm(); // tell it that it's up.
			this.currentForm = name;
			// find the new form name in the formList, so that we can
			// keep our currentFormIdx accurate:
			for(var i = 0, l = this.formList.length; i < l; i++){
				if(this.formList[i] === name){
					this.currentFormIdx = i;
					break;
				}
			}
			
			if(this.currentFormIdx === ( this.formList.length - 1 ) ){ // we're at the end of the forms
				this.updateButtons(null, false, this.enableFinish(), null);
			}
			this.updateButtons( false, null, this.enableFinish(), null); // ensure the back button is disabled.
		}

	},

	destruct : function() {
		this._disposeObjects( "ok_btn", "close_btn", "image", "caption", "child_layout" );

		for(var i = 0, l = this.wizardForms.length; i < l; i++){
			this.wizardForms[i].destruct();
			this.wizardForms[i] = null;
		}
		this.wizardForms = null;
	}
	
});
