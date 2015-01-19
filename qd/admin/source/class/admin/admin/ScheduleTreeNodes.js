/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/date_time.png)
#asset(admin/icon/16x16/plain/alarmclock_preferences.png)
#asset(admin/icon/16x16/plain/alarmclock_pause.png)
#asset(admin/icon/16x16/plain/alarmclock.png)
#asset(admin/icon/16x16/plain/alarmclock.png)
#asset(admin/icon/32x32/shadow/sign_warning.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("admin.admin.ScheduleTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			app.createTreeFolder2( parentNode, null, "Scheduled Tasks",
				"admin/icon/16x16/plain/date_time.png", admin.admin.ScheduleTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			admin.Api.GetScheduleItems(function(response){

				var objs = admin.sqldo.SchedItem.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					if(objs[i].getIsActive() == 1){
						var item = app.createTreeItem2( treeNode, objs[i],
							objs[i].getTaskName(),
							"admin/icon/16x16/plain/alarmclock_preferences.png",
							admin.admin.ScheduleTreeNodes.editObject);
					} else {
						var item = app.createTreeItem2( treeNode, objs[i],
							objs[i].getTaskName(),
							"admin/icon/16x16/plain/alarmclock_pause.png",
							admin.admin.ScheduleTreeNodes.editObject);
					}
				}

				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.getTaskName() );
			if( tabPage != null) { // brand new
				tabPage.setIcon("admin/icon/16x16/plain/alarmclock.png" );
				tabPage.add( new admin.admin.ScheduleEdit( obj ), {flex: 10} );
			}
		},

		/** This handles loading a brand new cached catalog.
		  */
		newObject : function( ) {
			var app = qx.core.Init.getApplication();
			var tabPage = app.addEditingTabDup( "Scheduled Task" );
			if( tabPage != null) { // brand new
				tabPage.setIcon("admin/icon/16x16/plain/alarmclock.png" );
				tabPage.add( new admin.admin.ScheduleEdit( 0 ), {flex: 10} );
			}
		},

		/** This handles deleting one of our objects in the tree.
		  */
		doDelete : function( treeNode ){
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;

			var windowLabel = "Are you sure you want to delete the Scheduled Task: " + obj.getTaskName() + " ?";
			var windowTitle = "Deleting...";
			var windowIcon = "admin/icon/32x32/shadow/sign_warning.png";

			var dialog = new admin.dialog.QuestionDialog( windowTitle, windowIcon, windowLabel );
			app.getRoot().add( dialog );
			dialog.addOkEventListener( "execute", function() {
				admin.Api.DeleteScheduleItem( obj, function(response) {
					app.closeEditingTab( obj.getTaskName() );
					treeNode.getParent().remove( treeNode );
				});

			});
			dialog.open();

		}
	}

});
