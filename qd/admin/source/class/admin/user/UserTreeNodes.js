/* ************************************************************************************

Copyright: 2008 - 2015 Hericus Software, LLC.

License: The MIT License

Authors: Steven M. Cherry

************************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/users.png)
#asset(admin/icon/16x16/plain/user_lock.png)
#asset(admin/icon/16x16/plain/user_lock.png)
#asset(admin/icon/16x16/plain/user_lock.png)
#asset(admin/icon/32x32/shadow/sign_warning.png)
************************************************************************ */

/** This class is logically clustered with the UserEditor, but is invoked via the main
 * Application.js class.  This has the static functions required to properly handle populating
 * nodes in the tree.
 */
qx.Class.define("admin.user.UserTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main "Users" tree node.
		 */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			app.createTreeFolder2( parentNode, null, "Users",
				"admin/icon/16x16/plain/users.png", admin.user.UserTreeNodes.populateChildren );

		},

		/** This handle populating our "Users" tree node children.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			admin.Api.GetUsers(function(response){
				var objs = admin.sqldo.User.readElementChildren(response);

				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].getUsername(),
						"admin/icon/16x16/plain/user_lock.png", admin.user.UserTreeNodes.editObject );
				}
				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our view objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.getUsername() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/user_lock.png" );
				tabPage.add( new admin.user.UserEditor( obj ), {flex: 10} );
			}
		},

		/** This handles creating a new view editor.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();

			// make sure the users node has been populated
			var node = app.findNode(app.treeRoot, "Users");
			if (node != null) {
				if (node.isOpen() == false) {
					node.setOpen(true);
				}
			}

			var tabPage = app.addEditingTabDup( "NEW1" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/user_lock.png" );
				tabPage.add( new admin.user.UserEditor( 0 ), {flex: 10} );
			}
		},

		/** This handles deleting one of our objects in the tree.
		 */
		doDelete : function (treeNode) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;

			var windowLabel = "Are you sure you want to delete the User: " + obj.getUsername() + " ?";
			var windowTitle = "Deleting...";
			var windowIcon = "admin/icon/32x32/shadow/sign_warning.png";

			var dialog = new admin.dialog.QuestionDialog( windowTitle, windowIcon, windowLabel );
			app.getRoot().add( dialog );
			dialog.addOkEventListener("execute", function() {
				admin.Api.DeleteUser( obj, function(response) {
					app.closeEditingTab( obj.getUsername() );
					treeNode.getParent().remove( treeNode );
				});
			});
			dialog.open();
		}

	}

});
