/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/folder_cubes.png)
#asset(admin/icon/16x16/plain/folder_cubes.png)
#asset(admin/icon/16x16/plain/folder_cubes.png)
#asset(admin/icon/16x16/plain/folder_cubes.png)
#asset(admin/icon/16x16/plain/folder_cubes.png)
#asset(admin/icon/16x16/plain/folder_green.png)
#asset(admin/icon/16x16/plain/code.png)
#asset(admin/icon/16x16/plain/code_cplusplus.png)
#asset(admin/icon/16x16/plain/code.png)
#asset(admin/icon/16x16/plain/code_cplusplus.png)
#asset(admin/icon/16x16/plain/data_new.png)
#asset(admin/icon/16x16/plain/data_scroll.png)
#asset(admin/icon/16x16/plain/data_scroll.png)
#asset(admin/icon/16x16/plain/server_connection.png)
#asset(admin/icon/16x16/plain/scroll.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("admin.dev.DevTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			var dev = app.createTreeFolder( parentNode, null, "Development",
				"admin/icon/16x16/plain/folder_cubes.png");

			var obj = new admin.sqldo.IAFolder();
			obj.setParentFolder("../logic/");
			app.createTreeFolder2( dev, obj, "Data Objects",
				"admin/icon/16x16/plain/folder_cubes.png", admin.dev.DevTreeNodes.populateChildren );

			var layouts = app.createTreeFolder( dev , null, "Visual Layouts",
				"admin/icon/16x16/plain/folder_cubes.png");

			var adm = new admin.sqldo.IAFolder();
			adm.setParentFolder("../../../qd/admin/source/layouts/");
			app.createTreeFolder2( layouts, adm, "admin",
				"admin/icon/16x16/plain/folder_cubes.png", admin.dev.DevTreeNodes.populateChildren );

			var d = new admin.sqldo.IAFolder();
			d.setParentFolder("../../../qd/dev/source/layouts/");
			app.createTreeFolder2( layouts, d, "dev",
				"admin/icon/16x16/plain/folder_cubes.png", admin.dev.DevTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			admin.Api.GetIAFileList(treeNode.helixObj, function(response){

				// First read in all of the folders:
				var objs = admin.sqldo.IAFolder.readElementChildren( response );
				objs.sort( function(a, b) {
					// Sort on the folder name
					if(a.getFolderName() < b.getFolderName()) return -1;
					else if(a.getFolderName() > b.getFolderName()) return +1;
					else return 0;
				} );
				for(var i = 0, l = objs.length; i < l; i++){
					var folder = app.createTreeFolder2( treeNode, objs[i], objs[i].getFolderName(),
						"admin/icon/16x16/plain/folder_green.png",
						admin.dev.DevTreeNodes.populateChildren );
				}

				// Then read in all of the files:
				var objs = admin.sqldo.IAFile.readElementChildren(response);
				objs.sort( function(a, b) {
					// Sort on the file name:
					if(a.getFileName() < b.getFileName()) return -1;
					else if(a.getFileName() > b.getFileName()) return +1;
					else  return 0;
				} );
				for(var i = 0, l = objs.length; i < l; i++){
					var fileName = objs[i].getFileName();
					var iconName = "admin/icon/16x16/plain/code.png";
					if( /.cpp$/.test( fileName ) ){ // endsWith( ".cpp" )
						// iconName = "admin/icon/16x16/plain/code_cplusplus.png";
						continue; // skip these
					} else if( /.sh$/.test( fileName) ){ // endsWith( ".sh" )
						// iconName = "admin/icon/16x16/plain/code.png";
						continue; // skip these
					} else if( /.h$/.test( fileName) ){ // endsWith( ".h" )
						// iconName = "admin/icon/16x16/plain/code_cplusplus.png";
						continue; // skip these
					} else if( /.db.xml$/.test( fileName) ){ // endsWith( ".db.xml" )
						// iconName = "admin/icon/16x16/plain/data_new.png";
						continue; // skip these
					} else if( /.sql.xml$/.test( fileName) ){ // endsWith( ".sql.xml" )
						iconName = "admin/icon/16x16/plain/data_scroll.png";
					} else if( /.xml$/.test( fileName) ){ // endsWith( ".xml" )
						iconName = "admin/icon/16x16/plain/data_scroll.png";
					} else if( /.o$/.test( fileName) ){ // endsWith( ".o" )
						continue; // skip these
					} else if( /.obj$/.test( fileName) ){ // endsWith( ".obj" )
						continue; // skip these
					} else if( /.pdb$/.test( fileName) ){ // endsWith( ".pdb" )
						continue; // skip these
					} else {
						continue; // skip anything we don't recognize
					}

					var item = app.createTreeItem2( treeNode, objs[i], objs[i].getFileName(),
						iconName, admin.dev.DevTreeNodes.editObject
					);
				}

				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();

			var editor = null;
			if( /.sql.xml$/.test( treeNode.getLabel() ) ){ // endsWith( ".sql.xml" )
				editor = new admin.dev.SqlDOEditor( treeNode.helixObj );
			} else if( /.xml$/.test( treeNode.getLabel() ) ){ // endsWith( ".xml" )
				//editor = new admin.utils.LayoutEditor( treeNode.helixObj );
				editor = new admin.utils.LayoutDesigner( treeNode.helixObj );
			} else {
				editor = new admin.admin.FileBrowse( treeNode.helixObj );
			}

			if(editor != null){
				var tabPage = app.addEditingTab( treeNode.getLabel() );
				if( tabPage != null) { // brand new
					tabPage.setIcon( treeNode.getIcon() );
					tabPage.add( editor, {flex: 10} );
				}
			}
		},

		/** This handles creating a new editor for an object that lives in our portion of the tree.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();

			// Make sure the Monitored Servers node has been populated
			var node = app.findNode( app.treeRoot, "Monitored Servers" );
			if(node != null){
				if(node.isOpen() == false){
					node.setOpen( true );
				}
			}
			var tabPage = app.addEditingTabDup( "Monitored Server" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/server_connection.png" );
				tabPage.add( new admin.server.ServerView( 0 ), {flex: 10} );
			}
		},

		/** This handles creating a new editor for a visual layout.
		  */
		newVisualLayout: function() {
			var app = qx.core.Init.getApplication();

			var tabPage = app.addEditingTabDup( "New Visual Layout" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "admin/icon/16x16/plain/scroll.png" );
				tabPage.add( new admin.utils.LayoutDesigner( 0 ), {flex: 10} );
			}
		}

	}

});
