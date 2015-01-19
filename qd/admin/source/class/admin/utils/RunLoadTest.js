/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/bullet_triangle_glass_green.png)
#asset(admin/icon/64x64/shadow/sports_car.png)
************************************************************************ */
qx.Class.define("admin.utils.RunLoadTest", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "RunLoadTest.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "RunLoadTest.NextPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = admin.Api.GetOneLoadTest;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb); // Call the parent class first

			// Then add any other actions that you would like here:
			var part = new qx.ui.toolbar.Part;

			admin.Statics.addToToolbar( part, "admin/icon/16x16/plain/bullet_triangle_glass_green.png",
				"Initiate the Load Test", this.doRunLoadTest, this, this, "Run Test");

			tb.add(part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "Results", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Load Test",
				"admin/icon/64x64/shadow/sports_car.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getName() );

			this.addStatusHeading("Overview");
			this.addStatusHint("This form allows you to run a simple load test that will iterate " +
				"over a series of SQL statements using a given number of threads and a given number " +
				"of reconnections for each thread." );


			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("RunLoadTest.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("RunLoadTest.NextPage.xml"),
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
			this.dataObject = new admin.sqldo.LoadTest();
			this.dataObject.setName( "New Load Test" );
			this.dataObject.setDescr( "Record a description of your test here." );
			this.dataObject.setHost( "Viazos19" );
			this.dataObject.setPort( 6311 );
			this.dataObject.setUser( "SMC" );
			this.dataObject.setPass( "SMC" );
			this.dataObject.setThreads( 10 );
			this.dataObject.setIterations( 20 );
			this.dataObject.setReconnectEveryN( 5 );
			this.dataObject.setUseAutoCommit( 0 );
			this.dataObject.setSqlStatements(
				"select * from HWRD.AUTHORS;\n" +
				"select * from HWRD.LDSSAMP;\n" +
				"select * from UNKNOWN.BADTABLE;\n"
			);

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.LoadTest.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.timings = admin.sqldo.LoadTestTiming.readElementChildren(response);
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


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			//this.overview_label1.setLabel("Overview Label1: " +
				//this.dataObject.getTName());

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */
			var rowData = [];
			for(var i = 0, l = this.timings.length; i < l; i++){
				var obj = this.timings[i];
				rowData.push([
					obj.getDescr(),
					obj.getThread(),
					obj.getAvg(),
					obj.getMin(),
					obj.getMax(),
					obj.getTotal()
				]);
			}
			this.timingsTable.getTableModel().setData( rowData );

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

		/** This will execute our load test.
		  */
		doRunLoadTest : function () {
			if(this.verifyFields() === -1){
				return; // Don't save an invalid object
			}
			this.pullDataFromForm();
			admin.Api.RunLoadTest( this.dataObject, function(response) {
				this.getObjectDetails( response );
			}, this);

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
				admin.Api.SaveLoadTest( this.dataObject,
				function(response){
					// pick up any new information here.
					this.isNewObject = false;

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getName() );

					this.loadDataIntoForm(); // Gets all of our overview labels

					this.resetDirty();
				}, this);
			} else {
				admin.Api.UpdateLoadTest( this.dataObject,
				function(response){
					// pick up any new information here.

					this.loadDataIntoForm(); // Gets all of our overview labels
					this.resetDirty();
				}, this);
			}

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
