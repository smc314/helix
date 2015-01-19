/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/user_headset.png)
#asset(admin/icon/16x16/plain/folder_closed.png)
#asset(admin/icon/16x16/plain/document.png)
#asset(admin/icon/16x16/plain/data_scroll.png)
#asset(admin/icon/16x16/plain/security_agent.png)
#asset(admin/icon/16x16/plain/document.png)
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/16x16/plain/eye_blue.png)
#asset(admin/icon/16x16/plain/delete2.png)
#asset(admin/icon/16x16/plain/refresh.png)
#asset(admin/icon/16x16/plain/eye_blue.png)
#asset(admin/icon/16x16/plain/delete2.png)
#asset(admin/icon/16x16/plain/box_next.png)
#asset(admin/icon/16x16/plain/compress.png)
#asset(admin/icon/16x16/plain/compress_green.png)
#asset(admin/icon/32x32/shadow/box_next.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("admin.admin.SupportTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			var obj = new admin.sqldo.IAFolder();
			obj.setParentFolder("./support/");
			app.createTreeFolder2( parentNode, obj, "Support",
				"admin/icon/16x16/plain/user_headset.png", admin.admin.SupportTreeNodes.populateChildren );

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
						"admin/icon/16x16/plain/folder_closed.png",
						admin.admin.SupportTreeNodes.populateChildren);
					folder.setContextMenu( admin.admin.SupportTreeNodes.createFolderContextMenu( objs[i] ) );
				}

				// Then read in all of the files
				var objs = admin.sqldo.IAFile.readElementChildren(response);
				for(var i = 0, l = objs.length; i < l; i++){
					var item = app.createTreeItem2( treeNode, objs[i], objs[i].getFileName(),
						"admin/icon/16x16/plain/document.png",
						admin.admin.SupportTreeNodes.editObject);
					item.setContextMenu( admin.admin.SupportTreeNodes.createFileContextMenu( objs[i] ) );
				}

				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			if(obj instanceof admin.sqldo.IAFile ){
				var tabPage = app.addEditingTabDup( obj.getFileName() );
				if( tabPage != null) { // brand new
					var n = obj.getFileName();
					var last4 = n.substr(n.length - 4, n.length);
					var first5 = n.substr(0, 5);
					if(first5 === "mflog" ){
						tabPage.setIcon("admin/icon/16x16/plain/data_scroll.png" );
						tabPage.add( new admin.admin.MonitorMFLogs( obj ), {flex: 10} );

					} else if( last4 === ".log" || last4 === ".LOG" || last4 === ".Log"){
						tabPage.setIcon("admin/icon/16x16/plain/security_agent.png" );
						tabPage.add( new admin.admin.MonitorServerLogs( obj ), {flex: 10} );

					} else {
						tabPage.setIcon( "admin/icon/16x16/plain/document.png" );
						tabPage.add( new admin.admin.FileBrowse( obj ), {flex: 10} );
					}
				}
			}
		},

		/** This creates a context menu and returns it. If the context menu already
		  * exists on the application, we'll simply return it.
		  */
		createFolderContextMenu: function(iaFolder) {
			var app = qx.core.Init.getApplication();
			if(app.SupportTreeNodes_FolderContextMenu){
				return app.SupportTreeNodes_FolderContextMenu;
			}
			var menu = new qx.ui.menu.Menu;
			// The first are standard items that we need to replicate:
			admin.Statics.addToRMCMenu(menu, "Refresh Folder", "admin/icon/16x16/plain/refresh.png",
				admin.admin.SupportTreeNodes.refreshFolder, app );
			admin.Statics.addToRMCMenu(menu, "View Selected Item", "admin/icon/16x16/plain/eye_blue.png",
				app.viewTreeSelection, app );
			admin.Statics.addToRMCMenu(menu, "Delete Selected Item", "admin/icon/16x16/plain/delete2.png",
				app.deleteTreeSelection, app );

			// Save our menu for future reference:
			app.SupportTreeNodes_FolderContextMenu = menu;

			// return it to the caller
			return menu;
		},

		/** This creates a context menu and returns it. If the context menu already
		  * exists on the application, we'll simply return it.
		  */
		createFileContextMenu: function( iaFile ) {
			var app = qx.core.Init.getApplication();
			if(app.SupportTreeNodes_FileContextMenu){
				return app.SupportTreeNodes_FileContextMenu;
			}
			var menu = new qx.ui.menu.Menu;
			// The first are standard items that we need to replicate:
			admin.Statics.addToRMCMenu(menu, "Refresh Folder", "admin/icon/16x16/plain/refresh.png",
				admin.admin.SupportTreeNodes.refreshFolder, app );
			admin.Statics.addToRMCMenu(menu, "View Selected Item", "admin/icon/16x16/plain/eye_blue.png",
				app.viewTreeSelection, app );
			admin.Statics.addToRMCMenu(menu, "Delete Selected Item", "admin/icon/16x16/plain/delete2.png",
				app.deleteTreeSelection, app );

			// Now add our own specific stuff:
			admin.Statics.addRMCSeparator( menu );

			//var n = iaFile.getFileName();
			//var last4 = n.substr(n.length - 4, n.length);
			//if( last4 === ".zip" || last4 === ".ZIP" || last4 === ".Zip"){
			admin.Statics.addToRMCMenu(menu, "Move to Folder",
				"admin/icon/16x16/plain/box_next.png",
				admin.admin.SupportTreeNodes.moveToFolder, app);

			admin.Statics.addToRMCMenu(menu, "Extract Zip File",
				"admin/icon/16x16/plain/compress.png",
				admin.admin.SupportTreeNodes.extractFile, app);

			//admin.Statics.addToRMCMenu(menu, "Move And Extract",
				//"admin/icon/16x16/plain/compress_green.png",
				//admin.admin.SupportTreeNodes.moveAndExtract, app);

			//}

			// Save our menu for future reference:
			app.SupportTreeNodes_FileContextMenu = menu;

			// return it to the caller
			return menu;
		},

		refreshFolder: function(e){
			var treeNode = this.tree.getSelection()[0];
			if(treeNode instanceof qx.ui.tree.TreeFile){
				treeNode = treeNode.getParent(); // go up to the parent folder
			}
			treeNode.removeAll();
			admin.admin.SupportTreeNodes.populateChildren( treeNode );
		},

		moveToFolder: function( e ){
			var treeNode = this.tree.getSelection()[0];
			if(treeNode.helixObj){
				// capture the current path:
				var p = treeNode.getParent();
				var path = p.getLabel() + "/";
				p = p.getParent();
				while( p && p.getLabel() !== "RootNodeIsInvisible") {
					path = p.getLabel() + "/" + path;
					p = p.getParent();
				}

				var dialog = new admin.SingleTextEntryDialog( "Move to Folder",
					"admin/icon/32x32/shadow/box_next.png",
					"Enter the destination folder for the selected item:" );
				dialog.textField.setValue( path );
				dialog.addOkEventListener("execute", function() {
					treeNode.helixObj.setTargetFolder( dialog.textField.getValue() );
					admin.Api.MoveSupportFile( treeNode.helixObj, function(response) {
						// Refresh the tree:
						p = treeNode.getParent();
						p.removeAll();
						admin.admin.SupportTreeNodes.populateChildren( p );
					} );
				});
				var app = qx.core.Init.getApplication();
				app.getRoot().add( dialog );
				dialog.open();
			}
		},

		moveAndExtract: function( e ){
			var treeNode = e.getTarget();
			if(treeNode.helixObj){

			}
		},

		extractFile: function ( e ) {
			var treeNode = this.tree.getSelection()[0];
			if(treeNode.helixObj){
				admin.Api.ExtractSupportFile( treeNode.helixObj, function(response) {
					// Refresh the tree:
					treeNode = treeNode.getParent();
					treeNode.removeAll();
					admin.admin.SupportTreeNodes.populateChildren( treeNode);
				} );
			}
		}

	}

});
