/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(PACKAGE/icon/64x64/shadow/control_panel2.png)
************************************************************************ */
qx.Class.define("PACKAGE.help.CheckForUpdates", {
	extend: PACKAGE.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "CheckForUpdates.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "CheckForUpdates.NextPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = null; //PACKAGE.Api.GetObjectAPICallFIXME;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			//this.base(arguments, tb); // Call the parent class first

			var sc_part = new qx.ui.toolbar.Part;

			// Refresh button
			PACKAGE.Statics.addToToolbarWithShortcut(sc_part, "PACKAGE/icon/16x16/plain/refresh.png",
				this.tr("Refresh From Server"), this.doRevert, this, this, "Control-U");

			// Download button
			PACKAGE.Statics.addToToolbarWithShortcut(sc_part, "PACKAGE/icon/16x16/plain/download.png",
				this.tr("Download Selected Release"), this.doDownload, this, this, "Control-D");

			// Install button
			PACKAGE.Statics.addToToolbarWithShortcut(sc_part, "PACKAGE/icon/16x16/plain/server_into.png",
				this.tr("Install Selected Release"), this.doInstall, this, this, "Control-I");

			tb.add(sc_part);
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(PACKAGE.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(PACKAGE.Statics.addEditorSubTab(this.tabview, "Next Tab", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Ivory Hub Releases", 
				"PACKAGE/icon/64x64/shadow/download.png",
				"Download Releases" );

			this.addStatusHeading("Current Version Info");
			this.overview_label1 = this.addStatusItem("Hub: ", 
				"PACKAGE/icon/16x16/plain/barcode.png");
			this.overview_label2 = this.addStatusItem("Built: ", 
				"PACKAGE/icon/16x16/plain/barcode.png");
			this.overview_label3 = this.addStatusItem("Mainframe: ", 
				"PACKAGE/icon/16x16/plain/barcode.png");
			this.overview_label4 = this.addStatusItem("Built: ", 
				"PACKAGE/icon/16x16/plain/barcode.png");


			PACKAGE.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("CheckForUpdates.MainPage.xml"),
				live );

			var tcm = this.releaseTable.getTableColumnModel();
			tcm.setDataCellRenderer( 4, new qx.ui.table.cellrenderer.Boolean() );
			tcm.setDataCellRenderer( 5, new qx.ui.table.cellrenderer.Boolean() );

			this.relDescField.set({decorator: "pane", padding:5});
			this.relDescField.setSelectable( true );

			this.releaseTable.getSelectionModel().addListener( "changeSelection", function(e) {
				var row = this.releaseTable.getFocusedRow();
				var hubVersion = this.releaseTable.getTableModel().getValue( 0, row );
				var release = null;
				for(var i = 0, l = this.releaseList.length; i < l; i++){
					if(this.releaseList[ i ].HubVersions[0].getFull() === hubVersion){
						release = this.releaseList[ i ];
						break;
					}
				}
				if(release !== null){
					this.relSummaryField.setValue( release.getReleaseSummary() );
					this.relDescField.setHtml( this.messageToHtml(release.getReleaseDescription()) );
				}
				this.resetDirty();
			}, this);

		},

		messageToHtml: function( message )
		{
			var newstr = message.replace(/</g, "&lt;");
			newstr = newstr.replace(/>/g, "&gt;" );
			newstr = newstr.replace(/\n/g, "<br/>" );
			newstr = newstr.replace(/\b(((\S+)?)(@|mailto\:|(news|(ht|f)tp(s?))\:\/\/)\S+)\b/g, this.createAHref );
			return newstr;

		},

		createAHref: function( full, url )
		{
			return "<a href=\"" + full + "\" target=\"_blank\">" + full + "</a>";
		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			PACKAGE.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("CheckForUpdates.NextPage.xml"),
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

			this.doRevert();
		},

		doRevert: function(e) {
			PACKAGE.Api.GetReleaseList( this.getObjectDetails, this );
		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = PACKAGE.sqldo.HubManifest.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.releaseList = objectList;
			var data = [];
			for(var i = 0, l = objectList.length; i < l; i++){
				var obj = objectList[i];
				data.push([
					obj.HubVersions[0].getFull(),
					obj.HubVersions[0].getDate(),
					obj.MainframeVersions[0].getFull(),
					obj.MainframeVersions[0].getDate(),
					Boolean(obj.getFullRelease()),
					Boolean(obj.getHotFix())
				]);
			}
			this.releaseTable.getTableModel().setData( data );
			this.releaseTable.getTableModel().sortByColumn( 1, false);
			this.loadDataIntoForm();
		},

		/** This handles loading our GUI form fields based on the information contained
		  * in our data object.
		  */
		loadDataIntoForm : function ()
		{
			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			var props = PACKAGE.Singleton.getInstance().getSystemProperties();
			this.overview_label1.setLabel("Hub: " + props[PACKAGE.Singleton.HubVersion] );
			this.overview_label2.setLabel("Built: " + props[PACKAGE.Singleton.HubBuiltOn] );
			this.overview_label3.setLabel("Mainframe: " + props[PACKAGE.Singleton.MainframeVersion] );
			this.overview_label4.setLabel("Built: " + props[PACKAGE.Singleton.MainframeBuiltOn] );

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
			if( PACKAGE.Statics.verifyAllFields(this) === -1) return -1;

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
				PACKAGE.Api.InsertObjectAPICallFIXME( this.dataObject,
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
						"PACKAGE/icon/16x16/plain/control_panel2.png" );

				}, this);
			} else {
				PACKAGE.Api.UpdateObjectAPICallFIXME( this.dataObject,
				function(response){
					// pick up any new information here.

					this.loadDataIntoForm(); // Gets all of our overview labels
					this.resetDirty();
				}, this);
			}

		},

		doDownload : function() {
			if(this.releaseTable.getSelectionModel().isSelectionEmpty() ){
				PACKAGE.Statics.doAlert("No Release selected to download.");
				return;
			}
			var row = this.releaseTable.getFocusedRow();
			var hubVersion = this.releaseTable.getTableModel().getValue( 0, row );
			var release = null;
			for(var i = 0, l = this.releaseList.length; i < l; i++){
				if(this.releaseList[ i ].HubVersions[0].getFull() === hubVersion){
					release = this.releaseList[ i ];
					break;
				}
			}
			if(release !== null){
				PACKAGE.Api.DownloadDistribution( release, function(response) {
					PACKAGE.Statics.doAlertGreen("Release downloaded and ready to install.");
				}, this);
			}
		},

		doInstall: function() {
			if(this.releaseTable.getSelectionModel().isSelectionEmpty() ){
				PACKAGE.Statics.doAlert("No Release selected to install.");
				return;
			}
			var row = this.releaseTable.getFocusedRow();
			var hubVersion = this.releaseTable.getTableModel().getValue( 0, row );
			var release = null;
			for(var i = 0, l = this.releaseList.length; i < l; i++){
				if(this.releaseList[ i ].HubVersions[0].getFull() === hubVersion){
					release = this.releaseList[ i ];
					break;
				}
			}
			if(release !== null){
				PACKAGE.Api.InstallDistribution( release, function(response) {
					PACKAGE.Statics.doAlertGreen("Release installed and Hub Server re-starting...");
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
		PACKAGE.Statics.destroyExtraObjects( this );
	}

});
