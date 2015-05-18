/* ************************************************************************

   Copyright: 2015 Your Company, Inc.

   Authors:  You and your developers

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/64x64/shadow/users4_edit.png)
#asset(admin/icon/16x16/plain/users4_edit.png)
************************************************************************ */
qx.Class.define("admin.user.GroupEditor", {
	extend: admin.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "GroupEditor.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "GroupEditor.UserPage.xml", doc:null});
		this.dynamicLayouts.push({name: "GroupEditor.ActionPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = admin.Api.GetOneGroup;
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
			this.createUserTab(admin.Statics.addEditorSubTab(this.tabview, "Users In Group", false));
			this.createActionTab(admin.Statics.addEditorSubTab(this.tabview, "Action Permissions", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Group Editor",
				"admin/icon/64x64/shadow/users4_edit.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getGroupname() );

			this.addStatusHeading("General");
			this.addStatusHint(
				"This edits group properties, group membership and group permissions. " +
				"Use the different tabs to access each of the settings of the group being edited."
			);

			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("GroupEditor.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createUserTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("GroupEditor.UserPage.xml"),
				tab_page );

			this.groupButtonBox._getLayout().setAlignY("middle");
			this.UsersForGroupList.setSelectionMode( "multi" );
			this.AllUsersList.setSelectionMode( "multi" );

			this.AddAllUsersBtn.addListener("execute", function() {
				this.addAllFromListToList( this.AllUsersList, this.UsersForGroupList );
				this.fieldModified();
			}, this);
			this.AddUserBtn.addListener("execute", function() {
				this.addSelectedFromListToList( this.AllUsersList, this.UsersForGroupList );
				this.fieldModified();
			}, this);
			this.RemoveUserBtn.addListener("execute", function() {
				this.removeSelectedFromList( this.UsersForGroupList );
				this.fieldModified();
			}, this);
			this.RemoveAllUsersBtn.addListener("execute", function() {
				this.UsersForGroupList.removeAll();
				this.fieldModified();
			}, this);
		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createActionTab: function(tab_page)
		{
			admin.layout.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("GroupEditor.ActionPage.xml"),
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

			this.dataObject = new admin.sqldo.Group;
			this.allUsers = [];
			this.allActions = [];

			admin.Api.GetUsers(function(response){
				this.allUsers = admin.sqldo.User.readElementChildren( response );
				admin.Statics.populateListFromArray( this.AllUsersList, this.allUsers,
					"getUsername", "getId" );
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
			var objectList = admin.sqldo.Group.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];

			this.allUsers = admin.sqldo.User.readElementChildren(
				admin.Statics.xmlFindChild( response, "AllUsers" )
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

			admin.Statics.populateListFromArray( this.UsersForGroupList, this.dataObject.UsersForGroup,
				"getUsername", "getUserid" );
			admin.Statics.populateListFromArray( this.AllUsersList, this.allUsers,
				"getUsername", "getId" );

			admin.Statics.populateListFromArray( this.AllowedActionsList, this.dataObject.ActionsForGroup,
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
			this.dataObject.UsersForGroup = [];
			for(var i = 0, l = this.UsersForGroupList.getChildren().length; i < l; i++){
				var item = this.UsersForGroupList.getChildren()[ i ];
				var user = new admin.sqldo.UserGroup;
				user.setUserid( Number(item.getModel()) );
				user.setUsername( item.getLabel() );
				user.setGroupid( this.dataObject.getId() );
				this.dataObject.UsersForGroup.push( user );
			}

			this.dataObject.ActionsForGroup = [];
			for(var i = 0, l = this.AllowedActionsList.getChildren().length; i < l; i++){
				var item = this.AllowedActionsList.getChildren()[ i ];
				var action = new admin.sqldo.Action;
				action.setId( Number(item.getModel()) );
				action.setPath( item.getLabel() );
				action.setUserid( this.dataObject.getId() );
				action.setAllow( 1 );
				this.dataObject.ActionsForGroup.push( action );
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
				admin.Api.InsertGroup( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getFullName() );

					// Remember to add the new guy to the tree:
					qx.core.Init.getApplication().addNewTreeItem( "Groups",
						this.dataObject.getGroupname(), this.dataObject,
						"admin/icon/16x16/plain/users4_edit.png" );

				}, this);
			} else {
				admin.Api.UpdateGroup( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getGroupname() );

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
