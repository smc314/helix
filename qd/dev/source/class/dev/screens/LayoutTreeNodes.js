/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/folder_cubes.png)
#asset(dev/icon/16x16/plain/folder_cubes.png)
#asset(dev/icon/16x16/plain/folder_cubes.png)
#asset(dev/icon/16x16/plain/folder_cubes.png)
#asset(dev/icon/16x16/plain/folder_green.png)
#asset(dev/icon/16x16/plain/code.png)
#asset(dev/icon/16x16/plain/code_cplusplus.png)
#asset(dev/icon/16x16/plain/code.png)
#asset(dev/icon/16x16/plain/code_cplusplus.png)
#asset(dev/icon/16x16/plain/data_new.png)
#asset(dev/icon/16x16/plain/data_scroll.png)
#asset(dev/icon/16x16/plain/data_scroll.png)
#asset(dev/icon/16x16/plain/scroll.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("dev.screens.LayoutTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();

			var layouts = app.createTreeFolder( parentNode, null, "Visual Layouts",
				"dev/icon/16x16/plain/folder_cubes.png");

			var adm = new dev.sqldo.IAFolder();
			adm.setParentFolder("../../../qd/admin/source/layouts/");
			app.createTreeFolder2( layouts, adm, "admin",
				"dev/icon/16x16/plain/folder_cubes.png", dev.screens.LayoutTreeNodes.populateChildren );

			var d = new dev.sqldo.IAFolder();
			d.setParentFolder("../../../qd/dev/source/layouts/");
			app.createTreeFolder2( layouts, d, "dev",
				"dev/icon/16x16/plain/folder_cubes.png", dev.screens.LayoutTreeNodes.populateChildren );

			var t = new dev.sqldo.IAFolder();
			t.setParentFolder("../../../qd/ttvx/source/layouts/");
			app.createTreeFolder2( layouts, t, "ttvx",
				"dev/icon/16x16/plain/folder_cubes.png", dev.screens.LayoutTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			dev.Api.GetIAFileList(treeNode.helixObj, function(response){

				// First read in all of the folders:
				var objs = dev.sqldo.IAFolder.readElementChildren( response );
				objs.sort( function(a, b) {
					// Sort on the folder name
					if(a.getFolderName() < b.getFolderName()) return -1;
					else if(a.getFolderName() > b.getFolderName()) return +1;
					else return 0;
				} );
				for(var i = 0, l = objs.length; i < l; i++){
					var folder = app.createTreeFolder2( treeNode, objs[i], objs[i].getFolderName(),
						"dev/icon/16x16/plain/folder_green.png",
						dev.screens.LayoutTreeNodes.populateChildren );
				}

				// Then read in all of the files:
				var objs = dev.sqldo.IAFile.readElementChildren(response);
				objs.sort( function(a, b) {
					// Sort on the file name:
					if(a.getFileName() < b.getFileName()) return -1;
					else if(a.getFileName() > b.getFileName()) return +1;
					else  return 0;
				} );
				for(var i = 0, l = objs.length; i < l; i++){
					var fileName = objs[i].getFileName();
					var iconName = "dev/icon/16x16/plain/code.png";
					if( /.cpp$/.test( fileName ) ){ // endsWith( ".cpp" )
						// iconName = "dev/icon/16x16/plain/code_cplusplus.png";
						continue; // skip these
					} else if( /.sh$/.test( fileName) ){ // endsWith( ".sh" )
						// iconName = "dev/icon/16x16/plain/code.png";
						continue; // skip these
					} else if( /.h$/.test( fileName) ){ // endsWith( ".h" )
						// iconName = "dev/icon/16x16/plain/code_cplusplus.png";
						continue; // skip these
					} else if( /.db.xml$/.test( fileName) ){ // endsWith( ".db.xml" )
						// iconName = "dev/icon/16x16/plain/data_new.png";
						continue; // skip these
					} else if( /.sql.xml$/.test( fileName) ){ // endsWith( ".sql.xml" )
						iconName = "dev/icon/16x16/plain/data_scroll.png";
					} else if( /.xml$/.test( fileName) ){ // endsWith( ".xml" )
						iconName = "dev/icon/16x16/plain/data_scroll.png";
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
						iconName, dev.screens.LayoutTreeNodes.editObject
					);
				}

				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();

			var editor = new dev.screens.LayoutDesigner( treeNode.helixObj );
			var tabPage = app.addEditingTab( treeNode.getLabel() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( treeNode.getIcon() );
				tabPage.add( editor, {flex: 10} );
			}

		},

		/** This handles creating a new editor for an object that lives in our portion of the tree.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();

			var tabPage = app.addEditingTabDup( "New Visual Layout" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "dev/icon/16x16/plain/scroll.png" );
				tabPage.add( new dev.screens.LayoutDesigner( 0 ), {flex: 10} );
			}
		}

	}

});
