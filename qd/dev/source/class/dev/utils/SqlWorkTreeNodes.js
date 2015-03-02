/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/table2_run.png)
#asset(dev/icon/16x16/plain/data_scroll.png)
#asset(dev/icon/16x16/plain/scroll_run.png)
#asset(dev/icon/16x16/plain/scroll_run.png)
#asset(dev/icon/16x16/plain/scroll_run.png)
#asset(dev/icon/32x32/shadow/sign_warning.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("dev.utils.SqlWorkTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			var obj = new dev.sqldo.IAFolder();
			obj.setParentFolder("./sqlwork/");
			app.createTreeFolder2( parentNode, obj, "SQL Workbench Sessions",
				"dev/icon/16x16/plain/table2_run.png", dev.utils.SqlWorkTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			dev.Api.GetWorkFileList(treeNode.helixObj, function(response){

				// First read in all of the folders
				var objs = dev.sqldo.IAFolder.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					var folder = app.createTreeFolder2( treeNode, objs[i], objs[i].getFolderName(),
						"dev/icon/16x16/plain/data_scroll.png",
						dev.utils.SqlWorkTreeNodes.populateChildren);
				}

				// Then read in all of the files:
				objs = dev.sqldo.IAFile.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					var obj = new dev.sqldo.SQLWork();
					obj.setFileName(objs[i].getFileName());
					app.createTreeItem2( treeNode, obj, obj.getFileName(),
						"dev/icon/16x16/plain/scroll_run.png", dev.utils.SqlWorkTreeNodes.editObject );
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
				tabPage.setIcon( "dev/icon/16x16/plain/scroll_run.png" );
				tabPage.add( new dev.utils.ExecuteSQL( obj ), {flex: 10} );
			}
		},

		/** This handles creating a new editor for an object that lives in our portion of the tree.
		  */
		newObject : function() {
			// expand tree node
			var app = qx.core.Init.getApplication();

			// make sure the aci node has been populated
			var node = app.findNode(app.treeRoot, "SQL Workbench Sessions");
			if (node != null) {
				if (node.isOpen() == false) {
					node.setOpen(true);
				}
			}

			var tabPage = app.addEditingTabDup( "NEW1" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "dev/icon/16x16/plain/scroll_run.png" );
				tabPage.add( new dev.utils.ExecuteSQL( 0 ), {flex: 10} );
			}
		},

		/** This handles deleting one of our objects in the tree.
		  */
		doDelete : function( treeNode ){
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;

			var name = obj.getFileName();
			var windowLabel = "Are you sure you want to delete the SQL Workbench file: " + name + " ?";
			var windowTitle = "Deleting...";
			var windowIcon = "dev/icon/32x32/shadow/sign_warning.png";

			var dialog = new dev.dialog.QuestionDialog( windowTitle, windowIcon, windowLabel );
			app.getRoot().add( dialog );
			dialog.addOkEventListener( "execute", function() {
				dev.Api.DeleteSQLWork( obj, function(response) {
					app.closeEditingTab( name );
					treeNode.getParent().remove( treeNode );
				});

			});
			dialog.open();

		}
	}

});
