/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/data_scroll.png)
#asset(dev/icon/16x16/plain/data_scroll.png)
#asset(dev/icon/16x16/plain/scroll.png)
#asset(dev/icon/16x16/plain/scroll.png)
#asset(dev/icon/16x16/plain/scroll.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("dev.utils.SqlTestTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			var obj = new dev.sqldo.IAFolder();
			obj.setParentFolder("./test/");
			app.createTreeFolder2( parentNode, obj, "SQL Tests",
				"dev/icon/16x16/plain/data_scroll.png", dev.utils.SqlTestTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			dev.Api.GetIAFileList(treeNode.helixObj, function(response){

				// First read in all of the folders
				var objs = dev.sqldo.IAFolder.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					var folder = app.createTreeFolder2( treeNode, objs[i], objs[i].getFolderName(),
						"dev/icon/16x16/plain/data_scroll.png",
						dev.utils.SqlTestTreeNodes.populateChildren);
				}

				// Then read in all of the files:
				objs = dev.sqldo.IAFile.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].getFileName(),
						"dev/icon/16x16/plain/scroll.png", dev.utils.SqlTestTreeNodes.editObject );
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
				tabPage.setIcon( "dev/icon/16x16/plain/scroll.png" );
				tabPage.add( new dev.utils.SqlTest( obj ), {flex: 10} );
			}
		},

		/** This handles creating a new editor for an object that lives in our portion of the tree.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();
			var tabPage = app.addEditingTabDup( "NEW1" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "dev/icon/16x16/plain/scroll.png" );
				tabPage.add( new dev.utils.SqlTest( 0 ), {flex: 10} );
			}
		}
	}

});
