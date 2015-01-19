/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/security_agent_edit.png)
#asset(admin/icon/16x16/plain/fire.png)
#asset(admin/icon/16x16/plain/error.png)
#asset(admin/icon/16x16/plain/sign_warning.png)
#asset(admin/icon/16x16/plain/information2.png)
#asset(admin/icon/16x16/plain/bug_green.png)
#asset(admin/icon/16x16/plain/step.png)
#asset(admin/icon/16x16/plain/table2_view.png)
************************************************************************ */
qx.Class.define("admin.admin.ManageServerLogs", {
	extend: admin.ObjectEdit,

	construct: function (object_id) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({ name: "ManageServerLogs.MainPage.xml", doc: null });
		this.dynamicLayouts.push({ name: "ManageServerLogs.NextPage.xml", doc: null });

		this.base(arguments, object_id);
	},

	members: {

		/** This is where the subclasses will tell us which API functions to use,
		* which callbacks to use, which names to use, etc.
		*/
		setupNamesAndFunctions: function () {
			this.selectApiCall = admin.Api.GetLogSettings;
		},

		/** This function will reset the name of our tab to match our object name.
		*/
		resetTabName: function () {
			var our_page = admin.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return; // couldn't find a tabview.Page parent in the hierarchy
			}
			// Update both our tab page name, and our summary area name.
			our_page.getButton().setLabel("Ivory Director Log Settings");
			this.updateSummaryName("Ivory Director Log Settings");
		},

		/** This function is responsible for initializing our toolbar.  We extend
		* the parent class functionality by adding our own icons and actions.
		*/
		initializeToolbar: function (tb) {
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
		doFormLayout: function () {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "Channel Settings", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		* set of form fields.
		*/
		createMainTab: function (tab_page) {
			var live = this.createOverviewLayout(tab_page,
				"Log Settings", "admin/icon/64x64/shadow/security_agent_edit.png",
				"Ivory Director Log Settings");

			this.addStatusHeading("Log Channels");
			this.overview_panic = this.addStatusItem("Panic:", "admin/icon/16x16/plain/fire.png");
			this.overview_error = this.addStatusItem("Error:", "admin/icon/16x16/plain/error.png");
			this.overview_warn = this.addStatusItem("Warn:", "admin/icon/16x16/plain/sign_warning.png");
			this.overview_info = this.addStatusItem("Info:", "admin/icon/16x16/plain/information2.png");
			this.overview_debug = this.addStatusItem("Debug:", "admin/icon/16x16/plain/bug_green.png");
			this.overview_trace = this.addStatusItem("Trace:", "admin/icon/16x16/plain/step.png");
			this.overview_sqltrace = this.addStatusItem("SQL Trace:", "admin/icon/16x16/plain/table2_view.png");


			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("ManageServerLogs.MainPage.xml"),
				live);

		},

		/** This creates a standard tab that is controlled by the layout page
		* rendered onto it.
		*/
		createNextTab: function (tab_page) {
			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("ManageServerLogs.NextPage.xml"),
				tab_page);

		},

		/** We override this function so that we can call the select API without
		*  an input object.
		*/
		doRevert: function (e) {
			admin.Api.GetLogSettings(this.getObjectDetails, this);
		},

		/** This allows our subclasses to do something in the scenario where the
		* edit view is opened up for a brand new object.
		*/
		initializeNewObject: function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			admin.Api.GetLogSettings(this.getObjectDetails, this);

		},

		/** This method is called by the "get" API function and should be prepared to read
		* our data object from the XML sent back to us by the server.
		*/
		getObjectDetails: function (response) {
			var objectList = admin.sqldo.LogSettings.readElementChildren(response);
			if (objectList.length === 0) {
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.loadDataIntoForm();
			this.m_object_id = 1; // enable the refresh button.
		},

		/** This handles loading our GUI form fields based on the information contained
		* in our data object.
		*/
		loadDataIntoForm: function () {
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			admin.Statics.loadAllFields(this, this.dataObject);


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			this.overview_panic.setLabel("Panic: " + this.onOrOff( this.panicField ) );
			this.overview_error.setLabel("Error: " + this.onOrOff( this.errorField ) );
			this.overview_warn.setLabel("Warn: " + this.onOrOff( this.warnField ) );
			this.overview_info.setLabel("Info: " + this.onOrOff( this.infoField ) );
			this.overview_debug.setLabel("Debug: " + this.onOrOff( this.debugField ) );
			this.overview_trace.setLabel("Trace: " + this.onOrOff( this.traceField ) );
			this.overview_sqltrace.setLabel("SQL Trace: " + this.onOrOff( this.sqlField ) );

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

			// Once data is loaded, reset our dirty flag:
			this.resetDirty();
		},

		onOrOff : function (checkField) {
			return checkField.getValue() === true ? "On" : "Off";
		},

		/** This handles pulling data from GUI form fields and loading their values
		* back into our data object.
		*/
		pullDataFromForm: function () {
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
		doSaveToServer: function () {
			this.pullDataFromForm();
			admin.Api.UpdateLogSettings(this.dataObject, function (response) {
				// pick up any new information here.

				this.loadDataIntoForm(); // gets the overview labels.
			}, this);

		}


	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		this._disposeObjects(
			"tabview",
			"dataObject",
			"m_object_id"
		);
		admin.Statics.destroyExtraObjects(this);
	}

});
