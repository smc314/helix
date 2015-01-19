/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/sports_car.png)
#asset(admin/icon/16x16/plain/sports_car.png)
#asset(admin/icon/16x16/plain/sports_car.png)
#asset(admin/icon/16x16/plain/sports_car.png)
#asset(admin/icon/32x32/shadow/sign_warning.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("admin.utils.LoadTestTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			app.createTreeFolder2( parentNode, null, "Load Tests",
				"admin/icon/16x16/plain/sports_car.png", admin.utils.LoadTestTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			admin.Api.GetLoadTests(function(response){
				var objs = admin.sqldo.LoadTest.readElementChildren(response);

				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].getName(),
						"admin/icon/16x16/plain/sports_car.png", admin.utils.LoadTestTreeNodes.editObject );
				}
				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.getName() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/sports_car.png" );
				tabPage.add( new admin.utils.RunLoadTest( obj ), {flex: 10} );
			}
		},

		/** This handles creating a new editor for an object that lives in our portion of the tree.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();
			var tabPage = app.addEditingTabDup( "Run Load Test" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/sports_car.png" );
				tabPage.add( new admin.utils.RunLoadTest( 0 ), {flex: 10} );
			}
		},

		/** This handles deleting one of our objects in the tree
		  */
		doDelete : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;

			var windowLabel = "Are you sure you want to delete the Load Test: " + obj.getName() + " ?";
			var windowTitle = "Deleting...";
			var windowIcon = "admin/icon/32x32/shadow/sign_warning.png";

			var dialog = new admin.dialog.QuestionDialog( windowTitle, windowIcon, windowLabel );
			app.getRoot().add( dialog );
			dialog.addOkEventListener( "execute", function() {
				admin.Api.DeleteLoadTest( obj, function(response) {
					app.closeEditingTab( obj.getName() );
					treeNode.getParent().remove( treeNode );
				});
			});
			dialog.open();
		}
	}

});
