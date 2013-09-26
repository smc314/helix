/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/refresh.png)
#asset(dev/icon/16x16/plain/components.png)
#asset(dev/icon/16x16/plain/delete2.png)
#asset(dev/icon/16x16/plain/components.png)
************************************************************************ */
qx.Class.define("dev.proj.ProjectPage", {
	extend: qx.ui.container.Composite,

	properties : {
	},

	construct: function (object_id) {
		this.base(arguments, new qx.ui.layout.VBox());
		this.doFormLayout();
		this.getProjectData();
	},

	events : {

	},

	members: {

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {
			this.splitPane = new qx.ui.splitpane.Pane("horizontal");

			this.projectContainer = new qx.ui.container.Composite(new qx.ui.layout.VBox()).set({
				width: 300
			});

			this.editorContainer = new qx.ui.container.Composite( new qx.ui.layout.VBox() );

			this.splitPane.add(this.projectContainer, 0);
			this.splitPane.add(this.editorContainer, 1);

			this.projectList = new qx.ui.form.List();
			this.projectContainer.add( this.createListToolbar() );
			this.projectContainer.add( this.projectList, {flex: 10} );

			this.editorTabs = new qx.ui.tabview.TabView;
			this.editorContainer.add( this.editorTabs, {flex: 10} );

			this.add( this.splitPane, {flex: 10} );

			this.projectList.addListener("dblclick", function(event){
				this.editProject( this.projectList.getSelection()[0].getUserData( "Project" ) );
			}, this );
		},

		createListToolbar : function() {
			var toolbar = new qx.ui.toolbar.ToolBar();
			var part0 = new qx.ui.toolbar.Part();
			toolbar.add( part0 );
			dev.Statics.addToToolbar( part0, "dev/icon/16x16/plain/refresh.png", "Refresh Project List",
				this.getProjectData, this, this, "Refresh" );
			dev.Statics.addToToolbar( part0, "dev/icon/16x16/plain/components.png", "Add New Project",
				this.doNewProject, this, this, "New" );
			dev.Statics.addToToolbar( part0, "dev/icon/16x16/plain/delete2.png", "Delete Selected Projects",
				this.doDeleteProjects, this, this, "Delete" );

			return toolbar;
		},

		getProjectData : function() {
			this.projectList.removeAll();
			dev.Api.GetProjectList( function(response) {
				var objectList = dev.sqldo.Project.readElementChildren( response );
				for(var i = 0, l = objectList.length; i < l; i++){
					var proj = objectList[ i ];
					var listItem = new qx.ui.form.ListItem( proj.getProjName(), null, proj.getGuid() );
					listItem.setUserData("Project", proj);
					this.projectList.add( listItem );
				}

			}, this );
			/*
			this.projectList.add( new qx.ui.form.ListItem( "Sample Project 1", null, "Sample Project 1" ) );
			this.projectList.add( new qx.ui.form.ListItem( "Mobile Project 1", null, "Mobile Project 1" ) );
			this.projectList.add( new qx.ui.form.ListItem( "Simple Data", null, "Simple Data" ) );
			this.projectList.add( new qx.ui.form.ListItem( "Complex Application", null, "Complex Application" ) );
			*/
		},

		doNewProject : function() {
			var tab_page = this.addEditingTab( "NEW1" );
			if(tab_page !== null){
				tab_page.setIcon("dev/icon/16x16/plain/components.png");
				tab_page.add( new dev.proj.ProjectEditor( 0 ), {flex:10} );
			}
		},

		doDeleteProjects : function() {
		},

		addEditingTab : function(tabName) {
			// first check to see if this tab name already exists
			var pages = this.editorTabs.getChildren();
			for(var i = 0, l = pages.length; i < l; i++){
				var page = pages[i];
				if(page.getLabel() === tabName || page.getLabel() === "*" + tabName ){
					page.getButton().setValue( true ); // bring it to the front
					return null; // it's already there
				}
			}
			// Didn't find it, create it
			var page = dev.Statics.addTabPage( this.editorTabs, tabName, true, true );
			return page;
		},

		editProject : function( proj ) {
			var tab_page = this.addEditingTab( proj.getProjName() );
			if(tab_page !== null){
				tab_page.setIcon("dev/icon/16x16/plain/components.png");
				tab_page.add( new dev.proj.ProjectEditor( proj ), {flex:10} );
			}
		}

	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		this._disposeObjects(

		);
		dev.Statics.destroyExtraObjects(this);

	}

});
