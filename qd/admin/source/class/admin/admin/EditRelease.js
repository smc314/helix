/* ************************************************************************

   Copyright: 2008 - 2012 Hericus Software, Inc.

   License: MIT License

   Authors:  Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/download.png)
#asset(admin/icon/16x16/plain/barcode.png)
************************************************************************ */
qx.Class.define("admin.admin.EditRelease", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "EditRelease.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "EditRelease.NextPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = null; //admin.Api.GetObjectAPICallFIXME;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
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
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			//this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "Next Tab", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Ivory Hub Release",
				"admin/icon/64x64/shadow/download.png",
				this.m_object_id.HubVersions[0].getFull() );

			this.addStatusHeading("General");
			this.overview_label1 = this.addStatusItem("Overview Label1:",
				"admin/icon/16x16/plain/barcode.png");


			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("EditRelease.MainPage.xml"),
				live );

			this.hubVersionField.setReadOnly( true );
			this.hubDateField.setReadOnly( true );
			this.mfVersionField.setReadOnly( true );
			this.mfDateField.setReadOnly( true );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("EditRelease.NextPage.xml"),
				tab_page );

		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = false;

			this.dataObject = this.m_object_id;

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.HubManifest.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.isNewObject = false;
			this.loadDataIntoForm();
		},

		/** This handles loading our GUI form fields based on the information contained
		  * in our data object.
		  */
		loadDataIntoForm : function ()
		{
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			admin.Statics.loadAllFields(this, this.dataObject);

			this.hubVersionField.setValue( this.dataObject.HubVersions[0].getFull() );
			this.hubDateField.setValue( this.dataObject.HubVersions[0].getDate() );
			this.mfVersionField.setValue( this.dataObject.MainframeVersions[0].getFull() );
			this.mfDateField.setValue( this.dataObject.MainframeVersions[0].getDate() );


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			this.overview_label1.setLabel("Ivory Hub Release");

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

			// Once data is loaded, reset our dirty flag
			this.resetDirty();

		},

		/** This handles pulling data from GUI form fields and loading their values
		  * back into our data object.
		  */
		pullDataFromForm : function ()
		{
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
		verifyFields : function()
		{
			// Use the built-in verification to do as much work for us as possible:
			if( admin.Statics.verifyAllFields(this) === -1) return -1;

			// Then do any special verification required here:

			// If everything is ok, return 0
			return 0;
		},

		/** This handles the calls required to save our dataObject back to the
		  * server.
		  */
		doSaveToServer : function ( )
		{
			if(this.verifyFields() === -1){
				return; // Don't save an invalid object
			}
			this.pullDataFromForm();
			admin.Api.SaveHubManifest( this.dataObject,
			function(response){
				// pick up any new information here.
				this.resetDirty();
			}, this);

		}


	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct : function() {
		this._disposeObjects(
			"tabview",
			"dataObject",
			"m_object_id"
		);
		admin.Statics.destroyExtraObjects( this );
	}

});
