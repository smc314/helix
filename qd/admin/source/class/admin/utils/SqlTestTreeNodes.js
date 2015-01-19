/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/data_scroll.png)
#asset(admin/icon/16x16/plain/data_scroll.png)
#asset(admin/icon/16x16/plain/scroll.png)
#asset(admin/icon/16x16/plain/scroll.png)
#asset(admin/icon/16x16/plain/scroll.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("admin.utils.SqlTestTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			var obj = new admin.sqldo.IAFolder();
			obj.setParentFolder("./test/");
			app.createTreeFolder2( parentNode, obj, "SQL Tests",
				"admin/icon/16x16/plain/data_scroll.png", admin.utils.SqlTestTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			admin.Api.GetIAFileList(treeNode.helixObj, function(response){

				// First read in all of the folders
				var objs = admin.sqldo.IAFolder.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					var folder = app.createTreeFolder2( treeNode, objs[i], objs[i].getFolderName(),
						"admin/icon/16x16/plain/data_scroll.png",
						admin.utils.SqlTestTreeNodes.populateChildren);
				}

				// Then read in all of the files:
				objs = admin.sqldo.IAFile.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].getFileName(),
						"admin/icon/16x16/plain/scroll.png", admin.utils.SqlTestTreeNodes.editObject );
				}
				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.getFileName() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/scroll.png" );
				tabPage.add( new admin.utils.SqlTest( obj ), {flex: 10} );
			}
		},

		/** This handles creating a new editor for an object that lives in our portion of the tree.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();
			var tabPage = app.addEditingTabDup( "NEW1" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/scroll.png" );
				tabPage.add( new admin.utils.SqlTest( 0 ), {flex: 10} );
			}
		}
	}

});
