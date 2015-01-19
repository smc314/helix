/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/control_panel2.png)
#asset(admin/icon/16x16/plain/barcode.png)
#asset(admin/icon/16x16/plain/control_panel2.png)
************************************************************************ */
qx.Class.define("admin.admin.MonitorLRTask", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "MonitorLRTask.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "MonitorLRTask.NextPage.xml", doc:null});

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
			var sc_part = new qx.ui.toolbar.Part;

			// Refresh button
			admin.Statics.addToToolbarWithShortcut( sc_part, "admin/icon/16x16/plain/refresh.png",
				"Reload From Server", this.initializeNewObject, this, this, "Control-U", "Refresh" );

			// Uncomment this to get a test button
			//admin.Statics.addToToolbarWithShortcut( sc_part, "admin/icon/16x16/plain/refresh.png",
			//	"Create New Test Task", this.createTestTask, this, this, "Control-T" );

			tb.add(sc_part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "Next Tab", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Long Running Tasks",
				"admin/icon/64x64/shadow/control_panel2.png",
				"Long Running Tasks");

			this.addStatusHeading("General");
			this.overview_label1 = this.addStatusItem("Overview Label1:",
				"admin/icon/16x16/plain/barcode.png");


			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("MonitorLRTask.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("MonitorLRTask.NextPage.xml"),
				tab_page );

		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */

			admin.Api.GetAllLRTasks( this.getObjectDetails, this );

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.LRTask.readElementChildren( response );
			var rowData = [];
			for( var i = 0, l = objectList.length; i < l; i++){
				var obj = objectList[i];
				rowData.push([
					obj.getTaskName(),
					obj.getTaskID(),
					obj.getTaskStart(),
					obj.getTaskCurrent(),
					obj.getTaskFinish(),
					obj.getTaskMsg()
				]);
			}
			this.tasksTable.getTableModel().setData( rowData );

			this.loadDataIntoForm();
		},

		/** This handles loading our GUI form fields based on the information contained
		  * in our data object.
		  */
		loadDataIntoForm : function ()
		{
			this.resetDirty();
		},

		/** This handles pulling data from GUI form fields and loading their values
		  * back into our data object.
		  */
		pullDataFromForm : function ()
		{
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
			if(this.isNewObject === true){
				admin.Api.InsertObjectAPICallFIXME( this.dataObject,
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
						"admin/icon/16x16/plain/control_panel2.png" );

				}, this);
			} else {
				admin.Api.UpdateObjectAPICallFIXME( this.dataObject,
				function(response){
					// pick up any new information here.

					this.loadDataIntoForm(); // Gets all of our overview labels
					this.resetDirty();
				}, this);
			}

		},

		createTestTask : function () {
			admin.Api.LongRunningTest(function(response){


			}, this );

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
