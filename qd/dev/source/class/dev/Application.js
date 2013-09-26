/* ************************************************************************

   Copyright:

   License:

   Authors:

************************************************************************ */

/* ************************************************************************

#asset(dev/icon/128x128/shadow/components.png)
#asset(dev/icon/128x128/shadow/data_gear.png)
#asset(dev/icon/128x128/shadow/window_sidebar.png)
#asset(dev/icon/128x128/shadow/server_client_exchange.png)
#asset(dev/*)

************************************************************************ */

/**
 * This is the main application class of your custom application "dev"
 */
qx.Class.define("dev.Application",
{
	extend : qx.application.Standalone,



	/*
	*****************************************************************************
	MEMBERS
	*****************************************************************************
	*/

	members :
	{
		/**
		* This method contains the initial application code and gets called
		* during startup of the application
		*
		* @lint ignoreDeprecated(alert)
		*/
		main : function() {
			// Call super class
			this.base(arguments);

			// Enable logging in debug variant
			if (qx.core.Environment.get("qx.debug"))
			{
				// support native logging capabilities, e.g. Firebug for Firefox
				qx.log.appender.Native;
				// support additional cross-browser console. Press F7 to toggle visibility
				qx.log.appender.Console;
				// support logging back to the helix server
				//dev.LogAppender;
			}

			// Setup the application skeleton
			this.setupInitialLayout();
		},

		setupInitialLayout : function() {
			var doc = this.getRoot();
			this.rootTabView = new qx.ui.tabview.TabView;
			this.rootTabView.setBarPosition( "right" );
			doc.add( this.rootTabView, {left: 0, top: 0, right: 0, bottom: 0} );

			var largeFont = new qx.bom.Font( 30 );
			var tabPage = dev.Statics.addTabPage( this.rootTabView, "My Projects", false, true );
			var tabButton = tabPage.getChildControl( "button" );
			tabPage.setIcon( "dev/icon/128x128/shadow/components.png" );
			tabButton.setFont( largeFont );
			tabButton.setIconPosition( "top" );
			tabPage.add( new dev.proj.ProjectPage(0), {flex: 10} );

			tabPage = dev.Statics.addTabPage( this.rootTabView, "My Data", false, false );
			tabButton = tabPage.getChildControl( "button" );
			tabPage.setIcon( "dev/icon/128x128/shadow/data_gear.png" );
			tabButton.setFont( largeFont );
			tabButton.setIconPosition( "top" );
			tabPage.add( new dev.data.DataPage(0), {flex: 10} );

			tabPage = dev.Statics.addTabPage( this.rootTabView, "My Screens", false, false );
			tabButton = tabPage.getChildControl( "button" );
			tabPage.setIcon( "dev/icon/128x128/shadow/window_sidebar.png" );
			tabButton.setFont( largeFont );
			tabButton.setIconPosition( "top" );
			tabPage.add( new dev.screens.ScreensPage(0), {flex: 10} );

			tabPage = dev.Statics.addTabPage( this.rootTabView, "My API's", false, false );
			tabButton = tabPage.getChildControl( "button" );
			tabPage.setIcon( "dev/icon/128x128/shadow/server_client_exchange.png" );
			tabButton.setFont( largeFont );
			tabButton.setIconPosition( "top" );
			tabPage.add( new dev.apis.ApiPage(0), {flex: 10} );
		}
	}
});
