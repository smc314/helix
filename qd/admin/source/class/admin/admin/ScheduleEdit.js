/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/alarmclock.png)
#asset(admin/icon/16x16/plain/alarmclock_preferences.png)
************************************************************************ */
qx.Class.define("admin.admin.ScheduleEdit", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "ScheduleEdit.MainPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = admin.Api.GetOneScheduleItem;
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
			var live = this.createOverviewLayout( tab_page, "Scheduled Task",
				"admin/icon/64x64/shadow/alarmclock.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getTaskName() );

			this.addStatusHeading("General");
			this.addStatusHint("Use this editor to manage the timing of this scheduled task.  The task can either run at a specific time of day, or periodically on a given interval.");

			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("ScheduleEdit.MainPage.xml"),
				live );

			this.radioGroup = new qx.ui.form.RadioGroup( this.useIntervalField, this.useTimeOfDayField );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("ScheduleEdit.NextPage.xml"),
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

			this.dataObject = new admin.admin.SchedItem;
			this.dataObject.setTaskName( "New Task Name" );
			this.dataObject.setTaskUrl( "/logic/admin/ProcessObjectName" );
			this.dataObject.setInputDocument( "<EmptyXmlDoc/>" );
			this.dataObject.setIsActive( 1 );
			this.dataObject.setRunEvery( 10 ); // minutes
			this.dataObject.setLastRun( "" );
			this.dataObject.setUseInterval( 1 );
			this.dataObject.setRunAtTime( "1235" );
			this.dataObject.setDowSunday( 1 );
			this.dataObject.setDowMonday( 1 );
			this.dataObject.setDowTuesday( 1 );
			this.dataObject.setDowWednesday( 1 );
			this.dataObject.setDowThursday( 1 );
			this.dataObject.setDowFriday( 1 );
			this.dataObject.setDowSaturday( 1 );

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.SchedItem.readElementChildren(response);
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


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */
			if(this.dataObject.getRunAtTime().length !== 0){
				this.RunAtHourField.setValue( this.dataObject.getRunAtTime().substr( 0, 2 ) );
				this.RunAtMinuteField.setValue( this.dataObject.getRunAtTime().substr( 2 ) );
			}

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
			if(this.dataObject.getUseInterval() === 0){
				this.dataObject.setRunAtTime(
					admin.Statics.zeroFill( Number(this.RunAtHourField.getValue()), 2 ) +
					admin.Statics.zeroFill( Number(this.RunAtMinuteField.getValue()), 2 )
				);
			}

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
				admin.Api.InsertScheduleItem( this.dataObject,
				function(response){
					// pick up any new information here.
					var objectList = admin.sqldo.SchedItem.readElementChildren( response );
					if(objectList.length != 0){
						this.dataObject = objectList[ 0 ];
					}
					this.isNewObject = false;

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getTaskName() );

					this.loadDataIntoForm(); // Gets all of our overview labels

					this.resetDirty();

					// Remember to add the new guy to the tree:
					qx.core.Init.getApplication().addNewTreeItem( "Scheduled Tasks",
						this.dataObject.getTaskName(), this.dataObject,
						"admin/icon/16x16/plain/alarmclock_preferences.png",
						admin.admin.ScheduleTreeNodes.editObject );

				}, this);
			} else {
				admin.Api.UpdateScheduleItem( this.dataObject,
				function(response){
					// pick up any new information here.
					this.loadDataIntoForm(); // Gets all of our overview labels
					this.resetTabName( this.dataObject.getTaskName() );
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
