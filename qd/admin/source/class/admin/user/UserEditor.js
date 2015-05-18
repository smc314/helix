/* ************************************************************************

   Copyright: 2015 Your Company, Inc.

   Authors:  You and your developers

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/user_lock.png)
#asset(admin/icon/16x16/plain/user_lock.png)
************************************************************************ */
qx.Class.define("admin.user.UserEditor", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "UserEditor.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "UserEditor.GroupPage.xml", doc:null});
		this.dynamicLayouts.push({name: "UserEditor.ActionPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = admin.Api.GetOneUser;
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
			this.createGroupTab(admin.Statics.addEditorSubTab(this.tabview, "Group Membership", false));
			this.createActionTab(admin.Statics.addEditorSubTab(this.tabview, "Action Permissions", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "User Editor",
				"admin/icon/64x64/shadow/user_lock.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getFullName() );

			this.addStatusHeading("General");
			this.addStatusHint(
				"This edits user properties, group membership and user permissions. " +
				"Use the different tabs to access each of the settings of the user being edited."
			);


			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("UserEditor.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createGroupTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("UserEditor.GroupPage.xml"),
				tab_page );

			this.groupButtonBox._getLayout().setAlignY("middle");
			this.GroupMembershipList.setSelectionMode( "multi" );
			this.AvailableGroupsList.setSelectionMode( "multi" );

			this.AddAllGroupsBtn.addListener("execute", function() {
				this.addAllFromListToList( this.AvailableGroupsList, this.GroupMembershipList );
				this.fieldModified();
			}, this);
			this.AddGroupBtn.addListener("execute", function() {
				this.addSelectedFromListToList( this.AvailableGroupsList, this.GroupMembershipList );
				this.fieldModified();
			}, this);
			this.RemoveGroupBtn.addListener("execute", function() {
				this.removeSelectedFromList( this.GroupMembershipList );
				this.fieldModified();
			}, this);
			this.RemoveAllGroupsBtn.addListener("execute", function() {
				this.GroupMembershipList.removeAll();
				this.fieldModified();
			}, this);
		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createActionTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("UserEditor.ActionPage.xml"),
				tab_page );

			this.actionButtonBox._getLayout().setAlignY("middle");
			this.AllowedActionsList.setSelectionMode( "multi" );
			this.AvailableActionsList.setSelectionMode( "multi" );

			this.AddAllActionsBtn.addListener("execute", function() {
				this.addAllFromListToList( this.AvailableActionsList, this.AllowedActionsList );
				this.fieldModified();
			}, this);
			this.AddActionBtn.addListener("execute", function() {
				this.addSelectedFromListToList( this.AvailableActionsList, this.AllowedActionsList );
				this.fieldModified();
			}, this);
			this.RemoveActionBtn.addListener("execute", function() {
				this.removeSelectedFromList( this.AllowedActionsList );
				this.fieldModified();
			}, this);
			this.RemoveAllActionsBtn.addListener("execute", function() {
				this.AllowedActionsList.removeAll();
				this.fieldModified();
			}, this);
		},

		addSelectedFromListToList: function(fromList, toList)
		{
			var selected = fromList.getSelection();
			for(var i = 0, l = selected.length; i < l; i++){
				var item = selected[i];
				// is it in the target list already?
				var match = admin.Statics.findListItem( toList, item.getModel() );
				if(match === null){
					match = new qx.ui.form.ListItem(item.getLabel(), null, item.getModel() );
					toList.add(match);
				}
			}
		},

		addAllFromListToList : function(fromList, toList)
		{
			var children = fromList.getChildren();
			for(var i = 0, l = children.length; i < l; i++){
				var item = children[i];
				// is it in the target list already?
				var match = admin.Statics.findListItem( toList, item.getModel() );
				if(match === null){
					match = new qx.ui.form.ListItem(item.getLabel(), null, item.getModel() );
					toList.add(match);
				}
			}
		},

		removeSelectedFromList: function(fromList)
		{
			var selected = fromList.getSelection();
			for(var i = 0, l = selected.length; i < l; i++){
				fromList.remove(selected[i]);
			}
		},


		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = true;

			this.dataObject = new admin.sqldo.User;
			this.allGroups = [];
			this.allActions = [];

			admin.Api.GetGroups(function(response){
				this.allGroups = admin.sqldo.Group.readElementChildren( response );
				admin.Statics.populateListFromArray( this.AvailableGroupsList, this.allGroups,
					"getGroupname", "getId" );
				this.resetDirty();
			}, this);

			admin.Api.GetActions(function(response){
				this.allActions = admin.sqldo.Action.readElementChildren( response );
				admin.Statics.populateListFromArray( this.AvailableActionsList, this.allActions,
					"getPath", "getId" );
				this.resetDirty();
			}, this);

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = admin.sqldo.User.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];

			this.allGroups = admin.sqldo.Group.readElementChildren(
				admin.Statics.xmlFindChild( response, "AllGroups" )
			);
			this.allActions = admin.sqldo.Action.readElementChildren(
				admin.Statics.xmlFindChild( response, "AllActions" )
			);
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

			admin.Statics.populateListFromArray( this.GroupMembershipList, this.dataObject.GroupMembership,
				"getGroupname", "getGroupid" );
			admin.Statics.populateListFromArray( this.AvailableGroupsList, this.allGroups,
				"getGroupname", "getId" );

			admin.Statics.populateListFromArray( this.AllowedActionsList, this.dataObject.AllowedActions,
				"getPath", "getId" );
			admin.Statics.populateListFromArray( this.AvailableActionsList, this.allActions,
				"getPath", "getId" );

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
			/* Any other type of data that needs to be pulled from the */
			/* form should be handled here.                            */
			/* ******************************************************* */
			this.dataObject.GroupMembership = [];
			for(var i = 0, l = this.GroupMembershipList.getChildren().length; i < l; i++){
				var item = this.GroupMembershipList.getChildren()[ i ];
				var group = new admin.sqldo.UserGroup;
				group.setGroupid( Number(item.getModel()) );
				group.setGroupname( item.getLabel() );
				group.setUserid( this.dataObject.getId() );
				this.dataObject.GroupMembership.push( group );
			}

			this.dataObject.AllowedActions = [];
			for(var i = 0, l = this.AllowedActionsList.getChildren().length; i < l; i++){
				var item = this.AllowedActionsList.getChildren()[ i ];
				var action = new admin.sqldo.Action;
				action.setId( Number(item.getModel()) );
				action.setPath( item.getLabel() );
				action.setUserid( this.dataObject.getId() );
				action.setAllow( 1 );
				this.dataObject.AllowedActions.push( action );
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
				admin.Api.InsertUser( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getFullName() );

					// Remember to add the new guy to the tree:
					qx.core.Init.getApplication().addNewTreeItem( "Users",
						this.dataObject.getUsername(), this.dataObject,
						"admin/icon/16x16/plain/user_lock.png" );

				}, this);
			} else {
				admin.Api.UpdateUser( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getFullName() );

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
