/* ************************************************************************

   Copyright: 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors:  You and your developers

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/64x64/shadow/control_panel2.png)
************************************************************************ */
qx.Class.define("dev.proj.ProjectEditor", {
	extend: dev.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "ProjectEditor.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "ProjectEditor.NextPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = dev.Api.GetProject;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb); // Call the parent class first

			// Then add any other actions that you would like here:
			var part = new qx.ui.toolbar.Part;
			
			dev.Statics.addToToolbarWithShortcut( part, "dev/icon/16x16/plain/refresh.png",
				"Reload the project from the filesystem", this.doReload, this, this, null, "Reload");

			tb.add(part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(dev.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(dev.Statics.addEditorSubTab(this.tabview, "Data Sources", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Helix Project", 
				"dev/icon/64x64/shadow/control_panel2.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getProjName() );

			this.addStatusHeading("General");
			this.overview_label1 = this.addStatusItem("Overview Label1:", 
				"dev/icon/16x16/plain/barcode.png");


			dev.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("ProjectEditor.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			dev.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("ProjectEditor.NextPage.xml"),
				tab_page );

		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = true;

			this.dataObject = new dev.sqldo.Project();
			this.dataObject.setGuid( "NEW" ); // tells the server we are a new object.
			this.dataObject.setDeployment( "C++ Standalone" );
			this.dataObject.setDescription( "Project Description goes here" );
			this.dataObject.setLocation( "./" );
			this.dataObject.setProjName( "New Project" );
			this.dataObject.setShortName( "proj1" );
			
			var firstApp = new dev.sqldo.Application();
			this.dataObject.Apps.push( firstApp );
			firstApp.setGuid( "NEW" );
			firstApp.setAppName( "New Application" );
			firstApp.setDescription( "Application Description goes here" );
			firstApp.setPackageName( "app1" );

			var firstData = new dev.sqldo.ProjectData();
			this.dataObject.Data.push( firstData );
			firstData.setGuid( "NEW" );
			firstData.setDataName( "Project Data Source" );
			firstData.setDescription( "Data Source Description goes here" );
			firstData.setDataType( 1 );
			firstData.setConnectionString( "helixdev" );
			firstData.setDevTimeUser( "n/a" );
			firstData.setDevTimePass( "n/a" );

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = dev.sqldo.Project.readElementChildren(response);
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
			dev.Statics.loadAllFields(this, this.dataObject);


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			this.overview_label1.setLabel("Overview Label1: " + 
				this.dataObject.getProjName());

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
			dev.Statics.pullAllFields(this, this.dataObject);

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
			if( dev.Statics.verifyAllFields(this) === -1) return -1;

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
			if(this.isNewObject === true){
				dev.Api.InsertObjectAPICallFIXME( this.dataObject,
				function(response){
					// pick up any new information here.
					this.isNewObject = false;

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getTName() ); 

					this.loadDataIntoForm(); // Gets all of our overview labels

					this.resetDirty();

					// Remember to add the new guy to the tree:
					qx.core.Init.getApplication().addNewTreeItem( "Parent Tree Node",
						this.dataObject.getTName(), this.dataObject,
						"dev/icon/16x16/plain/control_panel2.png" );

				}, this);
			} else {
				dev.Api.UpdateObjectAPICallFIXME( this.dataObject,
				function(response){
					// pick up any new information here.

					this.loadDataIntoForm(); // Gets all of our overview labels
					this.resetDirty();
				}, this);
			}

		},

		doReload : function () {

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
		dev.Statics.destroyExtraObjects( this );
	}

});
