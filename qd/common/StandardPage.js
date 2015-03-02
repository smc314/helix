/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#require(qx.event.handler.DragDrop)
#asset(PACKAGE/icon/32x32/shadow/sign_warning.png)
#asset(PACKAGE/icon/16x16/plain/window_split_ver.png)
#asset(PACKAGE/icon/16x16/plain/window_split_hor.png)
#asset(PACKAGE/icon/16x16/plain/window_delete.png)
************************************************************************ */
qx.Class.define("PACKAGE.StandardPage", {
	
	extend : qx.ui.container.Composite,

	construct : function () {
		this.base(arguments);
		this.name = "Standard Page";
		this.icon = "PACKAGE/icon/32x32/shadow/sign_warning.png";
		
		this.setLayout( new qx.ui.layout.VBox() );
		
	},
	
	properties : {
		 initialiPACKAGE : {init : false, check : "Boolean" }
	},
	
	members : {
		name : null,
		icon : null,
		
		/** This is called the first time that we are displayed.
		 * 
		 */
		initializeAppearance : function( ) {
			
			var tabview = this.setupToolbarAndTabs( this );
		 	this.initialTabView( tabview ); 
			
			this.initializeSplits() ;
			this.setInitialiPACKAGE(true);
		},
		
		/** This function initializes our toolbar and tab form (with no tabs), which
		 * is the basis of each of our work areas.
		 */
		setupToolbarAndTabs : function( widget ) {
			var toolbar = this.initializeToolbar( ); 
			widget.add( toolbar);
			var tabview = new qx.ui.tabview.TabView;

			tabview.setDroppable(true);
			tabview.addListener("drop", PACKAGE.StandardPage.handleDragDrop);
			tabview.addListener("dragover", PACKAGE.StandardPage.handleDragOver);

			widget.add( tabview, {flex:10} );
			return tabview;
		},


		rmcCloseTab : function ( e ){
			var menu_btn = e.getData();
			var menu_btn_menu = menu_btn.getLayoutParent();
			var btn = menu_btn_menu.getOpener();
			var tabview = PACKAGE.Statics.findQXParent( btn, qx.ui.tabview.TabView );
			var pageSearched = PACKAGE.StandardPage.findTabPage( btn );
			if(pageSearched){
				tabview.remove(pageSearched);
				pageSearched.dispose();
			}
			//e.stopPropagation();
		},
		
		rmcCloseOtherTabs : function (e){
			var i = 0;
		},
		
		rmcCloseAllTabs : function (e){
			var i = 0;
		},
		
		/**
		 * This function is responsible for initializing the toolbars that each of
		 * our standard meta-pages holds.
		 * 
		 * @type member
		 */
		initializeToolbar : function( ) {
			var tb = new qx.ui.toolbar.ToolBar;
			
			var nv_part = new qx.ui.toolbar.Part;
			var split_part = new qx.ui.toolbar.Part;
			tb.add(nv_part);
			tb.addSpacer();
			tb.add(split_part);
			
			// Standard tool bar looks like this:
			//
			// | []New []View                               | [V] [H] [X]
			//
			// Where V is the Vertical split icon,
			// H is the Horizontal split icon,
			// and X is the Close split icon.
			
			// New/View part
			var nbtn = new qx.ui.toolbar.MenuButton("New");
			var nmenu = new qx.ui.menu.Menu;
			nbtn.setMenu( nmenu );
			this.populateNewMenu( nmenu, nbtn );
			this.populateNewMenuSecondLevels( nmenu, nbtn );
			nv_part.add( nbtn );
			
			var vbtn = new qx.ui.toolbar.MenuButton("View", null, vmenu);
			var vmenu = new qx.ui.menu.Menu;
			vbtn.setMenu( vmenu );
			this.populateViewMenu( vmenu, vbtn );
			this.populateViewMenuSecondLevels( vmenu, vbtn );
			nv_part.add( vbtn );
		
			// Custom part(s)
			this.addCustomToolbarParts( tb );

			
			// Final part for splits
			var split_vertical = new qx.ui.toolbar.Button(null, "PACKAGE/icon/16x16/plain/window_split_ver.png");
			split_vertical.setUserData( "PACKAGE.CurrentPage", this );
			split_vertical.addListener("execute", this.doSplitVertical);
			split_vertical.setToolTip( new qx.ui.tooltip.ToolTip("New Vertical Split") );
			var split_horizontal = new qx.ui.toolbar.Button(null, "PACKAGE/icon/16x16/plain/window_split_hor.png");
			split_horizontal.setUserData( "PACKAGE.CurrentPage", this );
			split_horizontal.addListener("execute", this.doSplitHorizontal);
			split_horizontal.setToolTip( new qx.ui.tooltip.ToolTip("New Horizontal Split") );
			var split_close = new qx.ui.toolbar.Button(null, "PACKAGE/icon/16x16/plain/window_delete.png");
			split_close.setUserData( "PACKAGE.CurrentPage", this );
			split_close.addListener("execute", this.doCloseSplit);
			split_close.setToolTip( new qx.ui.tooltip.ToolTip("Close This Split") );
		
			split_part.add( split_vertical);
			split_part.add( split_horizontal );
			split_part.add( split_close );
			 
			return tb;
		},
		
		/** This function is reponsible for putting items on the "New" menu on our
		 * toolbar.  It is called every time we initialize the toolbar, or create a
		 * new toolbar for a new split.  Subclasses should always override this so
		 * that the "New" menu is appropriate for their page.
		 */
		populateNewMenu : function ( nmenu, nbtn ) {
			var single = PACKAGE.Singleton.getInstance();
			var nmenus = single.getNewMenus();
			
			var current_name = this.getCurrentPageName();
			
			var menus = nmenus[current_name];
			for(var label in menus){
				if( (label !== "MenuLabelIcon") &&
					(menus.hasOwnProperty(label))
				){
					var obj = menus[label];
					this.addViewMenuItem(nmenu, nbtn, label, 
						obj.icon, obj.callback );
				}
			}
		},
		
		/** This function is reponsible for putting items on the "View" menu on our
		 * toolbar.  It is called every time we initialize the toolbar, or create a
		 * new toolbar for a new split.  Subclasses should always override this so
		 * that the "View" menu is appropriate for their page.
		 */
		populateViewMenu : function ( vmenu, vbtn ) {
			var single = PACKAGE.Singleton.getInstance();
			var vmenus = single.getViewMenus();
			
			var current_name = this.getCurrentPageName();
			
			var menus = vmenus[current_name];
			for(var label in menus){
				if( (label !== "MenuLabelIcon") &&
					(menus.hasOwnProperty(label))
				){
					var obj = menus[label];
					this.addViewMenuItem(vmenu, vbtn, label, 
						obj.icon, obj.callback );
				}
			}
		},
		
		getCurrentPageName : function() {
			return this.name;
		},
		
		getNewMenus : function() {
			var ret = {};
			//ret["Menu1"] = { icon: null, callback: static.callback.function}; 
			//ret["Menu2"] = { icon: null, callback: static.callback.function};
			//...
			return ret; 
		},
		
		getViewMenus : function() {
			var ret = {};
			//ret["Menu1"] = { icon: null, callback: static.callback.function}; 
			//ret["Menu2"] = { icon: null, callback: static.callback.function};
			//...
			return ret; 
		},
		
		populateNewMenuSecondLevels : function (nmenu, nbtn ){
			nmenu.add ( new qx.ui.menu.Separator() );
			var single = PACKAGE.Singleton.getInstance();
			var nmenus = single.getNewMenus();
			
			var current_name = this.getCurrentPageName();
			
			for (var name in nmenus) {
				if (nmenus.hasOwnProperty(name)) {
					if(name !== current_name){
						// add these as sub-menus
						var sub = new qx.ui.menu.Menu;
						var menus = nmenus[name];
						for(var label in menus){
							if( (label !== "MenuLabelIcon") &&
								(menus.hasOwnProperty(label))
							){
								var obj = menus[label];
								this.addViewMenuItem(sub, nbtn, label, 
									obj.icon, obj.callback );
							}
						}
						nmenu.add(new qx.ui.menu.Button(name, menus["MenuLabelIcon"], null, sub) );
					}
				}
			}
		},

		populateViewMenuSecondLevels : function (vmenu, vbtn ){
			vmenu.add ( new qx.ui.menu.Separator() );
			var single = PACKAGE.Singleton.getInstance();
			var vmenus = single.getViewMenus();
			
			var current_name = this.getCurrentPageName();
			
			for (var name in vmenus) {
				if (vmenus.hasOwnProperty(name)) {
					if(name !== current_name){
						// add these as sub-menus
						var sub = new qx.ui.menu.Menu;
						var menus = vmenus[name];
						for(var label in menus){
							if( (label !== "MenuLabelIcon") &&
								(menus.hasOwnProperty(label))
							){
								var obj = menus[label];
								this.addViewMenuItem(sub, vbtn, label, 
									obj.icon, obj.callback );
							}
						}
						vmenu.add(new qx.ui.menu.Button(name, menus["MenuLabelIcon"], null, sub) );
					}
				}
			}
		},

		/** This function allows the objects that inherit from this one to add
		 * view menu items in a standard manner.
		 * 
		 * @param name {Object}
		 * @param icon {Object}
		 * @param callback {Object}
		 */
		addViewMenuItem : function (vmenu, vbtn, name, icon, callback) {
			// Create the menu button with a client command that will create a
			// tab button + page, and then call the callback function to fill out that page.
			var menu_button = new qx.ui.menu.Button(name, icon, this.createComandCreateView( callback ) );
			
			// On the menu button, tell it what it's toolbar parent Button is.  This menu
			// could be nested several layers down, and so this gives us a quick way
			// directly back to the toolbar.
			menu_button.setUserData("parentButton", vbtn);
			
			// Also on the menu button, tell it what it's parent standard page is.  The 
			// page keeps a list of all views that have been opened on it.  This allows each
			// page to ask for views by name.
			menu_button.setUserData("parentStandardPage", this);
			
			// Add the new menu button to the given menu.		
			vmenu.add(menu_button);
			
		},
		
		/** This function returns a special command that will be used to create a new
		 * view when the menu is invoked.  The provided callback must create the
		 * normal form/composite that will be loaded into the tab page.
		 * 
		 */
		createComandCreateView : function ( callback ){
			var c1 = new qx.ui.command.Command();
			c1.addListener("execute", function(event) {
				var menu_Button = event.getData().getUserData("parentButton"); // button.
				var parentToolbar = PACKAGE.Statics.findQXParent( menu_Button, qx.ui.toolbar.ToolBar );
				var layoutParent = parentToolbar.getLayoutParent();
				// Our layout's always have 2 children:
				// 0 = the toolbar
				// 1 = the tab view.
				var children = layoutParent.getChildren();
				if(children.length < 2){
					return; // bail out.
				}
				var tabview = children[1];
				
				var tab_page = PACKAGE.StandardPage.addStandardTab( tabview, event.getData().getLabel(), true);
				
				var f1 = callback();
				f1.setUserData("parentStandardPage", event.getData().getUserData("parentStandardPage"));
				
				tab_page.add(f1, {flex:1});
			});
			
			return c1;
		},
		
		
		/** This function allows a page to add a custom section to the toolbar,
		 * just after the "New" and "View" portion of the toolbar.  Be cautious and
		 * don't add too many items to the toolbar, as it is put into each split
		 * on the screen and often doesn't not have much space.
		 */
		addCustomToolbarParts : function ( tb ) {
			
		},
		
		/**
		 * This function is responsible for creating a simple tab view that we can add to
		 * an existing widget.
		 * 
		 * @type member
		 */
		initialTabView : function( tabView ) {
			
			var p1_1 = PACKAGE.StandardPage.addStandardTab( tabView, "View 1", true);
			var p1_2 = PACKAGE.StandardPage.addStandardTab( tabView, "View 2", false);
			var p1_3 = PACKAGE.StandardPage.addStandardTab( tabView, "View 3", false);
			
			var f1 = new qx.ui.form.TextField("View 1 Text");
			f1.set({ width : "100%", height : "100%"});
			var f2 = new qx.ui.form.TextField("View 2 Text");
			f2.set({ width : "100%", height : "100%"});
			var f3 = new qx.ui.form.TextField("View 3 Text");
			f3.set({ width : "100%", height : "100%"});
			
			p1_1.add(f1);
			p1_2.add(f2);
			p1_3.add(f3);
		},
		
		/** This function is responsible for creating the initial split layout that will
		 * be represented on this page.
		 */
		initializeSplits : function( ) {
			
		},
		
		doSplitVertical : function( ) {
			// layout
			//   -> toolbar
			//        -> toolbar part
			//             -> toolbar button === this.
			var parentToolbar = PACKAGE.Statics.findQXParent( this, qx.ui.toolbar.ToolBar );
			var layoutParent = parentToolbar.getLayoutParent();
			var current_page = this.getUserData("PACKAGE.CurrentPage");
			var splitpane = new qx.ui.splitpane.Pane("vertical");
			
			current_page.doSplit( layoutParent, splitpane, 1, 1);
		},
		
		doSplitHorizontal : function( ) {
			// layout
			//   -> toolbar
			//        -> toolbar part
			//             -> toolbar button === this.
			var parentToolbar = PACKAGE.Statics.findQXParent( this, qx.ui.toolbar.ToolBar ); 
			var layoutParent = parentToolbar.getLayoutParent();
			var current_page = this.getUserData("PACKAGE.CurrentPage");
			var splitpane = new qx.ui.splitpane.Pane("horizontal");
			
			current_page.doSplit( layoutParent, splitpane, 1, 1);
		},
		
		doCloseSplit : function( ) {
			// splitpane
			//     -> first area == Composite(VBox)
			//         -> toolbar
			//             -> toolbar button === this.
			//         -> tabview
			//     -> second area == Composite(VBox)
			//         -> toolbar
			//             -> toolbar button === this.
			//         -> tabview
			//
			// Don't count on the hierarchy above being direct parents/children.
			// Always use flexible functions to find parents of children.
			
			// First find out if we are in the first or second area:
			var our_toolbar = PACKAGE.Statics.findQXParent( this, qx.ui.toolbar.ToolBar );
			var our_area = PACKAGE.Statics.findQXParent(our_toolbar, qx.ui.container.Composite);
			var our_splitpane = PACKAGE.Statics.findQXParent(our_area, qx.ui.splitpane.Pane);
			var other_area = null;
			if( PACKAGE.Statics.getSplitFirst(our_splitpane) === our_area ){
				// we are the first area.
				other_area = PACKAGE.Statics.getSplitSecond(our_splitpane);
			} else {
				// we are the second area.
				other_area = PACKAGE.Statics.getSplitFirst(our_splitpane);
			}
			// delete everything in our area first:
			var ch1 = our_area.getChildren()[0];
			our_area.remove(ch1);
			ch1.dispose();
			ch1 = our_area.getChildren()[0];
			our_area.remove(ch1);
			ch1.dispose();
			
			// Now remove our splitpane from it's parent.
			var splitpane_parent = our_splitpane.getLayoutParent();
			splitpane_parent.remove(our_splitpane);
			
			// In it's place, set up a new toolbar and tabs view:
			var ourPage = null;
			if(splitpane_parent instanceof PACKAGE.StandardPage){
				ourPage = splitpane_parent;
				// for some reason, when closing the last split, the base
				// page does not get it's __heights[] array reset.
				// There's 2 ways to handle this:
				//ourPage._getLayout().__heights = [];
				// or just reset the layout with a new one:
				ourPage.setLayout( new qx.ui.layout.VBox() );
			} else {
				ourPage = PACKAGE.Statics.findQXParent( splitpane_parent, PACKAGE.StandardPage );
			}
			var new_tabview = ourPage.setupToolbarAndTabs( splitpane_parent );
			
			// Move all of the tabs from the old tabview into the new one:
			var old_tabview = other_area.getChildren()[1];
			var tab_page = old_tabview.getChildren()[0];
			while( tab_page !== null && tab_page !== undefined){
				var is_checked = tab_page.getButton().getValue();
				old_tabview.remove(tab_page);
				new_tabview.add(tab_page, {flex:1});							
				if(is_checked){	
					tab_page.getButton().setValue(true);
				}

				tab_page = old_tabview.getChildren()[0];
			}

			// Finally, dispose of the splitpane itself.
			other_area.dispose();
			our_splitpane.dispose();
			return;
		},
		
		doSplit : function( layoutParent, splitpane, flex1, flex2 ) {
			var children = layoutParent.getChildren();
			// The standard splitpane has a decorator that adds a border around
			// the whole widget.  We don't want that, so use the Background decorator
			// instead to get a 0 border.
			splitpane.set({decorator : new qx.ui.decoration.Decorator});
			splitpane.setLayoutProperties({left: 0, right: 0, bottom: 0, width: "100%", height: "100%"});
			
			// left Widget
			var leftWidget = new qx.ui.container.Composite(new qx.ui.layout.VBox);
			leftWidget.setBackgroundColor("white");
			
			// rightWidget
			var rightWidget = new qx.ui.container.Composite(new qx.ui.layout.VBox);
			rightWidget.setBackgroundColor("white");
			
			// add widgets to splitpane
			splitpane.add(leftWidget, flex1);
			splitpane.add(rightWidget, flex2);
			
			// Move all of the layoutParent's children into the first splitpane
			var ch1 = children[0];
			while( ch1 != null){
				leftWidget.add( ch1 );
				ch1 = children[0];
			}
		
			// Make the splitpane the new single child of the layoutParent
			layoutParent.add( splitpane );
		
			// Initialize the second splitpane with a new toolbar:
			this.setupToolbarAndTabs( rightWidget );
		}
		
	},
	
	statics : {
		
		findTabPage : function (tab_button) {
			var tabview = PACKAGE.Statics.findQXParent( tab_button, qx.ui.tabview.TabView );
			if(!tabview){
				return null; // didn't find the tabview itself.
			}
			var pagesArray = tabview.getChildren();
			
			for(var i = 0, l = pagesArray.length; i < l; i++){
				var tmpPage = pagesArray[i];
				if(tmpPage.getButton() === tab_button){
					return tmpPage;
				}
			}
			// if we get here, we didn't find it.
			return null;
		},
		
		/** This function is called when the user closes a tab.
		 */
		closeTabHandler : function (e){
			var btn = e.getData();
			var tabview = PACKAGE.Statics.findQXParent( btn, qx.ui.tabview.TabView );
			var pageSearched = PACKAGE.StandardPage.findTabPage( btn );
			if(pageSearched){
				//tabview.remove(pageSearched);
				pageSearched.dispose();
				delete pageSearched;
			}
		},

		/** This is the standard way to add a tab to one of our tab-views.  It will
		 * add a proper tab to the given tabview, enable the close button, enable the
		 * closetab event (pointing it to PACKAGE.StandardPage.closeTabHandler) and it will
		 * make the new tab checked if you ask.
		 * 
		 * We will return the new tab page upon success.
		 * 
		 * @param tabview {Object}
		 * @param tabName {Object}
		 * @param set_as_checked {Object}
		 */
		addStandardTab : function ( tabview, tabName, set_as_checked) {
			
			var our_spage = PACKAGE.Statics.findQXParent( tabview, PACKAGE.StandardPage );

			var tab_page = new qx.ui.tabview.Page(tabName);
			tab_page.setLayout(new qx.ui.layout.VBox());

			tab_page.getButton().setShowCloseButton(true);
			tab_page.getButton().addListener("close", PACKAGE.StandardPage.closeTabHandler, true );
			
			
			tab_page.getButton().setDraggable(true);
			tab_page.getButton().addListener("dragstart", PACKAGE.StandardPage.handleDragStart);
			tab_page.getButton().addListener("droprequest", PACKAGE.StandardPage.handleDropRequest);
			
			tab_page.setDroppable(true);
			tab_page.addListener("drop", PACKAGE.StandardPage.handleDragDrop);
			tab_page.addListener("dragover", PACKAGE.StandardPage.handleDragOver);
			
			if( set_as_checked ) {
				tab_page.getButton().setValue(true);
			}
			
			tabview.add(tab_page);
		
			return tab_page;
		},
		
		handleDragStart : function (e) {
			e.addType("items");
			e.addAction("move");
		},
		
		handleDropRequest : function (e) {
		},
		
		handleDragDrop : function ( e ) {
			var orig_button = e.getRelatedTarget();
			if(!(orig_button instanceof qx.ui.tabview.TabButton) ){
				// not a tabview button.
				return;
			}
			var orig_tabview = PACKAGE.Statics.findQXParent( orig_button, qx.ui.tabview.TabView );
			var orig_page = PACKAGE.StandardPage.findTabPage( orig_button );
			
			var new_tabview = null;
			var dropping_where = e.getCurrentTarget();
			if(dropping_where instanceof qx.ui.tabview.TabView){
				new_tabview = dropping_where;
			} else {
				new_tabview = PACKAGE.Statics.findQXParent( dropping_where, qx.ui.tabview.TabView );
			}
			
			if(new_tabview === orig_tabview){
				// dropping on the same tabview as dragged from.
				return;
			}
			
			// Select another button on the old tabview:
			var itemsList = orig_tabview.getChildren();
			var lengthList = itemsList.length;
			var btnIndex = orig_tabview.indexOf(orig_page);
			if(lengthList > 1){
				if (btnIndex < (lengthList-1) ){
					itemsList[(btnIndex+1)].getButton().setValue(true);
				} else {
					itemsList[(btnIndex-1)].getButton().setValue(true);
				}
			}
			
			// Finally, move the button and page from the old tab view
			orig_tabview.remove(orig_page);
			new_tabview.add(orig_page);							
			orig_button.setValue(true);
		},
		
		handleDragOver : function (event) {
			//e.getTarget().setBackgroundColor("#f2f2f2");    
		},
		
		handleDragOut : function (event) {
			//e.getTarget().setBackgroundColor("#fff");
		},
		
		handleDragEnd : function(event) {
			// we don't need to do anything here
			// If we had a succesful move action we might have removed
			// the source here or something else
		}

		
		
		
		
	}
});
