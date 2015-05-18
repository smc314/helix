/* ************************************************************************************

Copyright: 2008 - 2015 Hericus Software, LLC.

License: The MIT License

Authors: Steven M. Cherry

************************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/businesspeople2.png)
#asset(admin/icon/16x16/plain/users4_edit.png)
#asset(admin/icon/16x16/plain/users4_edit.png)
#asset(admin/icon/16x16/plain/users4_edit.png)
#asset(admin/icon/32x32/shadow/sign_warning.png)
************************************************************************ */

/** This class is logically clustered with the Groupditor, but is invoked via the main
 * Application.js class.  This has the static functions required to properly handle populating
 * nodes in the tree.
 */
qx.Class.define("admin.user.GroupTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main "Group" tree node.
		 */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			app.createTreeFolder2( parentNode, null, "Groups",
				"admin/icon/16x16/plain/businesspeople2.png", admin.user.GroupTreeNodes.populateChildren );

		},

		/** This handle populating our "Group" tree node children.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			admin.Api.GetGroups(function(response){
				var objs = admin.sqldo.Group.readElementChildren(response);

				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].getGroupname(),
						"admin/icon/16x16/plain/users4_edit.png", admin.user.GroupTreeNodes.editObject );
				}
				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our view objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.getGroupname() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/users4_edit.png" );
				tabPage.add( new admin.user.GroupEditor( obj ), {flex: 10} );
			}
		},

		/** This handles creating a new view editor.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();

			// make sure the users node has been populated
			var node = app.findNode(app.treeRoot, "Groups");
			if (node != null) {
				if (node.isOpen() == false) {
					node.setOpen(true);
				}
			}

			var tabPage = app.addEditingTabDup( "NEW1" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/users4_edit.png" );
				tabPage.add( new admin.user.GroupEditor( 0 ), {flex: 10} );
			}
		},

		/** This handles deleting one of our objects in the tree.
		 */
		doDelete : function (treeNode) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;

			var windowLabel = "Are you sure you want to delete the Group: " + obj.getGroupname() + " ?";
			var windowTitle = "Deleting...";
			var windowIcon = "admin/icon/32x32/shadow/sign_warning.png";

			var dialog = new admin.dialog.QuestionDialog( windowTitle, windowIcon, windowLabel );
			app.getRoot().add( dialog );
			dialog.addOkEventListener("execute", function() {
				admin.Api.DeleteGroup( obj, function(response) {
					app.closeEditingTab( obj.getGroupname() );
					treeNode.getParent().remove( treeNode );
				});
			});
			dialog.open();
		}

	}

});
