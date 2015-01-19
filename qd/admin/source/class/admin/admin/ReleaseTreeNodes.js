/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/download.png)
#asset(admin/icon/16x16/plain/download.png)
#asset(admin/icon/16x16/plain/download.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("admin.admin.ReleaseTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			app.createTreeFolder2( parentNode, null, "Releases",
				"admin/icon/16x16/plain/download.png", admin.admin.ReleaseTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			admin.Api.GetReleaseList(function(response){
				var objs = admin.sqldo.HubManifest.readElementChildren(response);

				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].HubVersions[0].getFull(),
						"admin/icon/16x16/plain/download.png", admin.admin.ReleaseTreeNodes.editObject );
				}
				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.HubVersions[0].getFull() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/download.png" );
				tabPage.add( new admin.admin.EditRelease( obj ), {flex: 10} );
			}
		}

	}

});
