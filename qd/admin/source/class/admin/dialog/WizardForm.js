/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */


/** This class defines a single form that can be used in a wizard.  We set
  * up all of the method signatures that are available in wizard forms.
  */
qx.Class.define("admin.dialog.WizardForm", {
	extend : qx.ui.container.Composite,

	/** Standard Constructor.
	  */
	construct : function ( ) {
		this.base( arguments );
		this.setLayout( new qx.ui.layout.VBox() );
		this.wizardDialog = null;

		this.loadDynamicLayouts( 0, function() {
			// allow children to add their own items to our layout:
			this.doFormLayout( this );

			this.addListenerOnce("appear", this.setFocusFirst, this);

		}, this);
	},

	members : {
		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {

		},

		/** This method is called just before a form is removed from the wizard
		  * as the current display form.  It is intended to give you an opportunity
		  * to gather all of the data from the fields in your form into whatever
		  * data object you are using to hold your data.
		  */
		pullDataFromForm : function () {

		},

		/** This method is called just after your form is displayed in the wizard
		  * as the current display form.  It is intended to give you an opportunity
		  * to set all of the fields in the form with the appropriate data from
		  * whatever data object you are using to hold your data.
		  */
		loadDataIntoForm : function () {

		},

		/** You may use this method to control the forward flow of the wizard as
		  * the user presses the "Next" button.  If you do not use this method,
		  * then the order the forms were added to the wizard will be the order
		  * in which they are displayed.
		  * <p>
		  * Note: you may not override the "previous" form name because the wizard
		  * automatically keeps a "back history", and uses that to traverse the
		  * forms in the opposite order in which they were displayed.
		  */
		getNextFormName : function () {
			// if you return null here, then the order in which the forms were
			// added to the wizard is the order in which they will be displayed.
			return null;
		},

		/** This is used to tell us which wizard dialog is controling us.  We can
		  * then use this reference to update the caption, icon, and button states
		  * of the wizard dialog.
		  * <p>
		  * Note: usually it is not necessary to override this method.
		  */
		setWizard : function ( wizard ) {
			this.wizardDialog = wizard;
		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {

		},

		loadDynamicLayouts : function ( start, callback ) {
			if(!this.dynamicLayouts){
				// nothing to do, run the callback.
				callback.call(this );
				return;
			}
			if(start >= this.dynamicLayouts.length){
				// we're done.  Call the callback
				callback.call(this);
				return;
			}

			var url = "layouts/" + this.dynamicLayouts[start].name;
			// load the layout:
			admin.Api.LoadXMLDoc( url,
			function( response ){
				this.dynamicLayouts[start].doc = response.ownerDocument;
				// recurse for all of the rest of the layouts
				this.loadDynamicLayouts( start + 1, callback );
			}, this);
		},

		getDynamicLayout : function ( layoutName ){
			for(var i = 0, l = this.dynamicLayouts.length; i < l; i++){
				if(this.dynamicLayouts[i].name === layoutName){
					return this.dynamicLayouts[i].doc;
				}
			}
			return null;
		}


	},

	destruct : function() {
		this.wizardDialog = null;
		admin.Statics.destroyExtraObjects(this);
	}

});
