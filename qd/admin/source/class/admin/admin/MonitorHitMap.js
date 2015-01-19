/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/user_time.png)
#asset(admin/icon/16x16/plain/barcode.png)
************************************************************************ */
qx.Class.define("admin.admin.MonitorHitMap", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "MonitorHitMap.MainPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = admin.Api.GetHitMap;
		},

		/** This function will reset the name of our tab to match our object name.
		  */
		resetTabName : function() {
			var our_page = admin.Statics.findQXParent(this, qx.ui.tabview.Page);
			if(our_page === null){
				return; // couldn't find a tabview.Page parent in the hierarchy
			}
			// Update both our tab page name, and our summary area name.
			our_page.getButton().setLabel( "Monitor Hit Map" );
			this.updateSummaryName( "Monitor Hit Map" );
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
			var sc_part = new qx.ui.toolbar.Part;

			// Refresh button:
			admin.Statics.addToToolbarWithShortcut(sc_part, "admin/icon/16x16/plain/refresh.png",
				this.tr("Reload From Server"), this.doRevert, this, this, "Control-U", "Refresh");

			tb.add(sc_part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** Overload the fieldModified function because we don't care about the isDirty
		 * flag.
		 */
		fieldModified : function (e) {
			this.isDirty = false;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Monitor Hit Map",
				"admin/icon/64x64/shadow/user_time.png",
				"Ivory Director Hit Map" );

			this.addStatusHeading("General");
			this.overview_label1 = this.addStatusItem("Overview Label1:",
				"admin/icon/16x16/plain/barcode.png");


			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("MonitorHitMap.MainPage.xml"),
				live );

		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.selectApiCall( this.getObjectDetails, this );

		},

		doRevert: function(e){
			this.selectApiCall( this.getObjectDetails, this );
		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.HitMap.readElementChildren(response);
			var rowData = [];
			for(var i = 0, l = objectList.length; i < l; i++){
				var obj = objectList[i];
				rowData.push([
					obj.getMethodName(),
					obj.getTotalHits(),
					obj.getAverageCycles(),
					obj.getMinCycles(),
					obj.getMaxCycles(),
					//obj.getTotalHits() * obj.getAverageCycles()
					obj.getTotalCycles()
				]);

			}
			this.hitTable.getTableModel().setData( rowData );
		},

		/** This handles loading our GUI form fields based on the information contained
		  * in our data object.
		  */
		loadDataIntoForm : function ()
		{
			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			this.overview_label1.setLabel("Overview Label1: " +
				this.dataObject.getTName());

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

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
