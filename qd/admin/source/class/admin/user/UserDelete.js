/* ************************************************************************************

Copyright: 2008 - 2015 Hericus Software, LLC

License: The MIT License

Authors: Steven M. Cherry

************************************************************************************ */
/* ************************************************************************
#asset(admin/icon/32x32/shadow/sign_warning.png)
************************************************************************ */

/** This class is logically clustered with the UserEditor, but is invoked via the main
 * Application.js class.  This has the static functions required to properly delete a
 * user.
 */
qx.Class.define("admin.user.UserDelete", {

	type: "static",

	statics: {

		/** This handles deleting the given user.  We'll prompt the user with the usual
		 * "are you sure" message, and then handle the delete.
		 */
		doDelete : function(treeNode) {

			var helixObj = treeNode.helixObj;

			if( !(helixObj instanceof admin.sqldo.User) ){
				admin.Statics.doAlert("Programming error: not passing a User object to UserDelete.");
			}

			// Standard Are You Sure message:
			var app = qx.core.Init.getApplication();
			var windowLabel = "Are you sure you want to delete the user: " + helixObj.getUName() + " ?";
			var windowTitle = "Deleting...";
			var windowIcon = "admin/icon/32x32/shadow/sign_warning.png";

			var dialog = new admin.dialog.QuestionDialog(windowTitle, windowIcon, windowLabel);
			app.getRoot().add( dialog );
			dialog.addOkEventListener("execute", function() {
				admin.Api.DeleteUser( helixObj, function(response) {
					// Close any open editors:
					app.closeEditingTab( helixObj.getUName() );
					treeNode.getParent().remove(treeNode);
				});
			});
			dialog.open();

		}

	}

});
