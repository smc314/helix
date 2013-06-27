#!/bin/bash
#############################################################################################
# This script makes it easy to start a new logic skeleton.  We'll create the header and body
# files with everything required.  Just pass us the new Class name.

CLASSNAME=$1
PACKAGE=$2
JAVASCRIPT=${CLASSNAME}.js
TMP=`pwd`
FOLDER=${TMP##*/}
THISYEAR=`date +%Y`

#############################################################################################
# Here's the new class file that is based on an ObjectEdit standard.
#############################################################################################
echo "Creating file ${JAVASCRIPT} based on class: ${CLASSNAME} and package ${PACKAGE}"
cat >${JAVASCRIPT} <<EOF
/* ************************************************************************************

	Copyright: ${THISYEAR} Your Company, Inc.

	Authors: You and your developers

************************************************************************************ */
/* ************************************************************************
#asset(${PACKAGE}/icon/16x16/plain/users.png)
************************************************************************ */

/** This class is invoked via the main Application.js class and has the static functions required 
  * to properly handle populating nodes in the tree.
  */
qx.Class.define("${PACKAGE}.${FOLDER}.${CLASSNAME}", {

	type: "static",

	statics: {

		/** This handles creating our main tree node.
		  */
		createRootNode : function(parentNode) {
			var app = qx.core.Init.getApplication();
			app.createTreeFolder2( parentNode, null, "FIXME-RootNodeName",
				"${PACKAGE}/icon/16x16/plain/users.png", ${PACKAGE}.${FOLDER}.${CLASSNAME}.populateChildren );

		},

		/** This handles populating the children for our root tree node.
		  */
		populateChildren : function( treeNode ){
			var app = qx.core.Init.getApplication();
			${PACKAGE}.Api.FIXME_PopulateChildren(function(response){
				var objs = ${PACKAGE}.sqldo.FIXME.readElementChildren(response);

				for(var i = 0, l = objs.length; i < l; i++){
					app.createTreeItem2( treeNode, objs[i], objs[i].getUName(),
						"${PACKAGE}/icon/16x16/plain/user_lock.png", ${PACKAGE}.${FOLDER}.${CLASSNAME}.editObject );
				}
				treeNode.setOpen( true );

			} );
		},

		/** This handles editing one of our objects in the tree.
		  */
		editObject : function( treeNode ) {
			var app = qx.core.Init.getApplication();
			var obj = treeNode.helixObj;
			var tabPage = app.addEditingTab( obj.getUName() );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "${PACKAGE}/icon/16x16/plain/user_lock.png" );
				tabPage.add( new ${PACKAGE}.${FOLDER}.UserEditor( obj ), {flex: 10} );
			}
		},

		/** This handles creating a new editor for an object that lives in our portion of the tree.
		  */
		newObject : function() {
			var app = qx.core.Init.getApplication();
			app.switchToTablesTab();
			var tabPage = app.addEditingTabDup( "NEW1" );
			if( tabPage != null) { // brand new
				tabPage.setIcon( "${PACKAGE}/icon/16x16/plain/user_lock.png" );
				tabPage.add( new ${PACKAGE}.${FOLDER}.UserEditor( 0 ), {flex: 10} );
			}
		}
	}

});
EOF
