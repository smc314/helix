/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/doctor.png)
#asset(dev/icon/16x16/plain/stethoscope.png)
#asset(dev/icon/16x16/plain/stethoscope.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("dev.utils.UnitTestTreeNodes", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			app.createTreeFolder2( parentNode, null, "Unit Tests",
				"dev/icon/16x16/plain/doctor.png", dev.utils.UnitTestTreeNodes.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			dev.Api.ListUnitTests(function(response){
				var objs = dev.sqldo.UnitTestSummary.readElementChildren(response);

				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].getTestName(),
						"dev/icon/16x16/plain/stethoscope.png", dev.utils.UnitTestTreeNodes.editObject );
				}
				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.getTestName() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "dev/icon/16x16/plain/stethoscope.png" );
				tabPage.add( new dev.utils.UnitTestDisplay( obj ), {flex: 10} );
			}
		}

	}

});
