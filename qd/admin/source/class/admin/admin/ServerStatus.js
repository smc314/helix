/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/server_ok.png)
#asset(admin/icon/16x16/plain/barcode.png)
************************************************************************ */
qx.Class.define("admin.admin.ServerStatus", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "ServerStatus.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "ServerStatus.NextPage.xml", doc:null});

		if(object_id === 0){
			this.dataObject = new admin.sqldo.Table();
			this.dataObject.setTName("Ivory Director Server Status");
		} else {
			this.dataObject = object_id;
		}

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = null; //admin.Api.GetObjectAPICallFIXME;
		},

		/** This function will reset the name of our tab to match our object name.
		  */
		resetTabName : function() {
			var our_page = admin.Statics.findQXParent(this, qx.ui.tabview.Page);
			if(our_page === null){
				return; // couldn't find a tabview.Page parent in the hierarchy
			}
			// Update both our tab page name, and our summary area name.
			our_page.getButton().setLabel( this.dataObject.getTName() );
			this.updateSummaryName( this.dataObject.getTName() );
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
			this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "Next Tab", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var root = new qx.ui.container.Composite(new qx.ui.layout.HBox);
			tab_page.add(root, { flex: 10 });

			var live = new qx.ui.container.Composite(new qx.ui.layout.VBox).set({
				decorator: "pane",
				backgroundColor: "red",
				padding: 5,
				minWidth: 200
			});

			root.add(this.initGeneralStatus(
				"Server Status",  // This is the large title in the overview section
				"admin/icon/64x64/shadow/server_ok.png", // Large icon in overview
				this.dataObject.getTName()), // Name of object, should match tab name.
				{ flex: 1 });
			root.add(live, { flex: 10 });

			this.addStatusHeading("General");
			this.overview_label1 = this.addStatusItem("Overview Label1:",
				"admin/icon/16x16/plain/barcode.png");


			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("ServerStatus.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("ServerStatus.NextPage.xml"),
				tab_page );

		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.Table.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
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

		/** This handles the calls required to save our dataObject back to the
		  * server.
		  */
		doSaveToServer : function ( )
		{
			this.pullDataFromForm();
			admin.Api.SaveObjectAPICallFIXME( this.dataObject,
			function(response){
				// pick up any new information here.

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
