/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/fire.png)
#asset(admin/icon/16x16/plain/error.png)
#asset(admin/icon/16x16/plain/sign_warning.png)
#asset(admin/icon/16x16/plain/information2.png)
#asset(admin/icon/16x16/plain/bug_green.png)
#asset(admin/icon/16x16/plain/step.png)
#asset(admin/icon/16x16/plain/table2_view.png)
#asset(admin/icon/16x16/plain/media_play.png)
#asset(admin/icon/16x16/plain/fire.png)
#asset(admin/icon/16x16/plain/error.png)
#asset(admin/icon/16x16/plain/sign_warning.png)
#asset(admin/icon/16x16/plain/information2.png)
#asset(admin/icon/16x16/plain/bug_green.png)
#asset(admin/icon/16x16/plain/step.png)
#asset(admin/icon/16x16/plain/table2_view.png)
#asset(admin/icon/16x16/plain/media_play.png)
#asset(admin/icon/16x16/plain/media_beginning.png)
#asset(admin/icon/16x16/plain/media_end.png)
#asset(admin/icon/16x16/plain/media_play.png)
#asset(admin/icon/16x16/plain/eraser2.png)
#asset(admin/icon/16x16/plain/binocular.png)
#asset(admin/icon/16x16/plain/document_time.png)
#asset(admin/icon/16x16/plain/user_headset.png)
#asset(admin/icon/64x64/shadow/security_agent.png)
#asset(admin/icon/16x16/plain/document_text.png)
#asset(admin/icon/16x16/plain/server.png)
#asset(admin/icon/16x16/plain/application_server.png)
#asset(admin/icon/16x16/plain/thread.png)
#asset(admin/icon/16x16/plain/id_card.png)
#asset(admin/icon/16x16/plain/message.png)
#asset(admin/icon/16x16/plain/microscope.png)
#asset(admin/icon/16x16/plain/server.png)
#asset(admin/icon/16x16/plain/server_new.png)
#asset(admin/icon/16x16/plain/application_server.png)
#asset(admin/icon/16x16/plain/application_server_new.png)
#asset(admin/icon/16x16/plain/thread.png)
#asset(admin/icon/16x16/plain/thread_add.png)
#asset(admin/icon/16x16/plain/id_card.png)
#asset(admin/icon/16x16/plain/id_card_new.png)
#asset(admin/icon/16x16/plain/colors_rgb.png)
#asset(admin/icon/16x16/plain/photographic_filter.png)
#asset(admin/icon/16x16/plain/colors_cmyk.png)
************************************************************************ */
qx.Class.define("admin.admin.MonitorServerLogs", {
	extend: admin.ObjectEdit,

	construct: function (object_id) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({ name: "MonitorServerLogs.MainPage.xml", doc: null });
		this.dynamicLayouts.push({ name: "MonitorServerLogs.NextPage.xml", doc: null });

		this.base(arguments, object_id);

		/*
		this.panicImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/fire.png" );
		this.errorImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/error.png" );
		this.warnImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/sign_warning.png" );
		this.infoImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/information2.png" );
		this.debugImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/bug_green.png" );
		this.traceImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/step.png" );
		this.sqltraceImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/table2_view.png" );
		this.unknownImg = new qx.ui.basic.Image( "admin/icon/16x16/plain/media_play.png" );
		*/

		this.panicImg = "admin/icon/16x16/plain/fire.png";
		this.errorImg = "admin/icon/16x16/plain/error.png";
		this.warnImg = "admin/icon/16x16/plain/sign_warning.png";
		this.infoImg = "admin/icon/16x16/plain/information2.png";
		this.debugImg = "admin/icon/16x16/plain/bug_green.png";
		this.traceImg = "admin/icon/16x16/plain/step.png";
		this.sqltraceImg = "admin/icon/16x16/plain/table2_view.png";
		this.unknownImg = "admin/icon/16x16/plain/media_play.png";
	},

	members: {

		/** This is where the subclasses will tell us which API functions to use,
		* which callbacks to use, which names to use, etc.
		*/
		setupNamesAndFunctions: function () {
			this.selectApiCall = null; //admin.Api.GetObjectAPICallFIXME;
		},

		/** This function will reset the name of our tab to match our object name.
		*/
		resetTabName: function () {
			var our_page = admin.Statics.findQXParent(this, qx.ui.tabview.Page);
			if (our_page === null) {
				return; // couldn't find a tabview.Page parent in the hierarchy
			}
			// Update both our tab page name, and our summary area name.
			our_page.getButton().setLabel(this.dataObject.getTName());
			this.updateSummaryName(this.dataObject.getTName());
		},

		/** This function is responsible for initializing our toolbar.  We extend
		* the parent class functionality by adding our own icons and actions.
		*/
		initializeToolbar: function (tb) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			//this.base(arguments, tb); // Call the parent class first

			// Then add any other actions that you would like here:
			var part = new qx.ui.toolbar.Part;

			admin.Statics.addToToolbar(part, "admin/icon/16x16/plain/media_beginning.png",
				"Jump to Begining of Log", this.loadFirstLogMessages, this, this, "Jump To Start");
			admin.Statics.addToToolbar(part, "admin/icon/16x16/plain/media_end.png",
				"Jump to End of Log", this.loadLastLogMessages, this, this, "Jump To End");
			admin.Statics.addToToolbar(part, "admin/icon/16x16/plain/media_play.png",
				"Refresh Logs Based on Current Filters", this.loadCurrentLogMessages, this, this, "Apply Filters");
			admin.Statics.addToToolbar(part, "admin/icon/16x16/plain/eraser2.png",
				"Clear all filters and refresh logs", this.clearFilters, this, this, "Clear Filters");
			admin.Statics.addToToolbar(part, "admin/icon/16x16/plain/binocular.png",
				"Find log messages by ID, Timestamp, or Text", this.doFind, this, this, "Find");

			tb.add(part);

			var part2 = new qx.ui.toolbar.Part;
			admin.Statics.addToToolbar(part2, "admin/icon/16x16/plain/document_time.png",
				"Refresh List of Log Files", this.loadLogFiles, this, this, "Load Log Files");
			admin.Statics.addToToolbar(part2, "admin/icon/16x16/plain/user_headset.png",
				"Forward Current Log File to Support", this.forwardToSupport, this, this, "Forward To Support");

			tb.add(part2);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** Overload the fieldModified function because we don't care about the isDirty
		 * flag.
		 */
		fieldModified : function (e) {
			this.isDirty = false;
		},

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(admin.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(admin.Statics.addEditorSubTab(this.tabview, "Filters", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		* set of form fields.
		*/
		createMainTab: function (tab_page) {
			var live = this.createOverviewLayout(tab_page,
				"Log Messages", "admin/icon/64x64/shadow/security_agent.png",
				"Ivory Director Logs");

			this.addStatusHeading("Current Filters");
			this.overview_label2 = this.addStatusItem("Log File:", "admin/icon/16x16/plain/document_text.png");
			this.overview_label3 = this.addStatusItem("Machine:", "admin/icon/16x16/plain/server.png");
			this.overview_label4 = this.addStatusItem("App:", "admin/icon/16x16/plain/application_server.png");
			this.overview_label5 = this.addStatusItem("Thread:", "admin/icon/16x16/plain/thread.png");
			this.overview_label5a = this.addStatusItem("SUID:", "admin/icon/16x16/plain/id_card.png");
			this.overview_label6 = this.addStatusItem("Msg:", "admin/icon/16x16/plain/message.png");
			this.overview_label7 = this.addStatusItem("Panic: On", this.panicImg );
			this.overview_label8 = this.addStatusItem("Error: On", this.errorImg );
			this.overview_label9 = this.addStatusItem("Warn: On", this.warnImg );
			this.overview_label10 = this.addStatusItem("Info: On", this.infoImg );
			this.overview_label11 = this.addStatusItem("Debug: On", this.debugImg );
			this.overview_label12 = this.addStatusItem("Trace: On", this.traceImg );
			this.overview_label13 = this.addStatusItem("Sql Trace: On", this.sqltraceImg );

			this.overview_label2.setRich(true);

			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("MonitorServerLogs.MainPage.xml"),
				live);


			// Add our table interaction stuff:
			this.logTable.setContextMenu(this.createRMCMenu());
			this.logTable.addListener("dblclick", this.onDoubleClick, this);

		},

		/** This creates a standard tab that is controlled by the layout page
		* rendered onto it.
		*/
		createNextTab: function (tab_page) {
			admin.layout.LayoutEngine.renderLayout(this,
				this.getDynamicLayout("MonitorServerLogs.NextPage.xml"),
				tab_page);

			admin.Statics.addToDropDown(this.LogFileField, "<Default>", "<Default>");
		},

		createRMCMenu: function () {
			this.rmc = new qx.ui.menu.Menu;

			admin.Statics.addToRMCMenu(this.rmc, "Show Details",
				"admin/icon/16x16/plain/microscope.png", this.onDoubleClick, this);
			admin.Statics.addRMCSeparator(this.rmc);
			admin.Statics.addToRMCMenu(this.rmc, "Show only this Machine",
				"admin/icon/16x16/plain/server.png", this.showOnlyMachine, this);
			admin.Statics.addToRMCMenu(this.rmc, "Show any Machine",
				"admin/icon/16x16/plain/server_new.png", this.showAllMachines, this);
			admin.Statics.addRMCSeparator(this.rmc);
			admin.Statics.addToRMCMenu(this.rmc, "Show only this Application",
				"admin/icon/16x16/plain/application_server.png", this.showOnlyApplication, this);
			admin.Statics.addToRMCMenu(this.rmc, "Show any Application",
				"admin/icon/16x16/plain/application_server_new.png", this.showAllApplications, this);
			admin.Statics.addRMCSeparator(this.rmc);
			admin.Statics.addToRMCMenu(this.rmc, "Show only this Thread",
				"admin/icon/16x16/plain/thread.png", this.showOnlyThread, this);
			admin.Statics.addToRMCMenu(this.rmc, "Show any Thread",
				"admin/icon/16x16/plain/thread_add.png", this.showAllThreads, this);
			admin.Statics.addRMCSeparator(this.rmc);
			admin.Statics.addToRMCMenu(this.rmc, "Show only this SUID",
				"admin/icon/16x16/plain/id_card.png", this.showOnlySUID, this);
			admin.Statics.addToRMCMenu(this.rmc, "Show any SUID",
				"admin/icon/16x16/plain/id_card_new.png", this.showAllSUID, this);
			admin.Statics.addRMCSeparator(this.rmc);
			admin.Statics.addToRMCMenu(this.rmc, "Show only this Channel",
				"admin/icon/16x16/plain/colors_rgb.png", this.showOnlyChannel, this);
			admin.Statics.addToRMCMenu(this.rmc, "Don't Show this Channel",
				"admin/icon/16x16/plain/photographic_filter.png", this.dontShowChannel, this);
			admin.Statics.addToRMCMenu(this.rmc, "Show any Channel",
				"admin/icon/16x16/plain/colors_cmyk.png", this.showAllChannels, this);

			return this.rmc;
		},

		onDoubleClick: function () {
			var row = this.logTable.getFocusedRow();
			var tm = this.logTable.getTableModel();
			var id = tm.getValue(1, row);

			var windowTitle = "Log Msg: " + id;

			var tmpWindow = new admin.admin.LogMsgDialog(windowTitle);
			tmpWindow.logTable = this.logTable;
			tmpWindow.tableModel = tm;
			tmpWindow.currentRow = row;
			tmpWindow.loadRow();

			qx.core.Init.getApplication().getRoot().add(tmpWindow);
			tmpWindow.open();

		},

		showOnlyMachine: function () {
			var row = this.logTable.getFocusedRow();
			var tm = this.logTable.getTableModel();
			var machine = tm.getValue(3, row);

			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setMachineName(machine);
			this.loadLogMessages(this.dataObject);
		},

		showAllMachines: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setMachineName("");
			this.loadLogMessages(this.dataObject);
		},

		showOnlyApplication: function () {
			var row = this.logTable.getFocusedRow();
			var tm = this.logTable.getTableModel();
			var app = tm.getValue(4, row);

			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setAppName(app);
			this.loadLogMessages(this.dataObject);
		},

		showAllApplications: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setAppName("");
			this.loadLogMessages(this.dataObject);
		},

		showOnlyThread: function () {
			var row = this.logTable.getFocusedRow();
			var tm = this.logTable.getTableModel();
			var thread = tm.getValue(5, row);

			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setThreadID(thread);
			this.loadLogMessages(this.dataObject);
		},

		showAllThreads: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setThreadID(0);
			this.loadLogMessages(this.dataObject);
		},

		showOnlySUID: function () {
			var row = this.logTable.getFocusedRow();
			var tm = this.logTable.getTableModel();
			var val = tm.getValue(6, row);

			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setSUID(val);
			this.loadLogMessages(this.dataObject);
		},

		showAllSUID: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setSUID("");
			this.loadLogMessages(this.dataObject);
		},

		showOnlyChannel: function () {
			var row = this.logTable.getFocusedRow();
			var tm = this.logTable.getTableModel();
			var channel = tm.getValue(9, row);

			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setPanic(0);
			this.dataObject.setError(0);
			this.dataObject.setWarn(0);
			this.dataObject.setInfo(0);
			this.dataObject.setDebug(0);
			this.dataObject.setTrace(0);
			this.dataObject.setSqlTrace(0);
			switch (channel) {
				case "Panic": this.dataObject.setPanic(1); break;
				case "Error": this.dataObject.setError(1); break;
				case "Warn": this.dataObject.setWarn(1); break;
				case "Info": this.dataObject.setInfo(1); break;
				case "Debug": this.dataObject.setDebug(1); break;
				case "Trace": this.dataObject.setTrace(1); break;
				case "SQLTrace": this.dataObject.setSqlTrace(1); break;
			}
			this.loadLogMessages(this.dataObject);
		},

		dontShowChannel: function () {
			var row = this.logTable.getFocusedRow();
			var tm = this.logTable.getTableModel();
			var channel = tm.getValue(9, row);

			admin.Statics.pullAllFields(this, this.dataObject);
			switch (channel) {
				case "Panic": this.dataObject.setPanic(0); break;
				case "Error": this.dataObject.setError(0); break;
				case "Warn": this.dataObject.setWarn(0); break;
				case "Info": this.dataObject.setInfo(0); break;
				case "Debug": this.dataObject.setDebug(0); break;
				case "Trace": this.dataObject.setTrace(0); break;
				case "SQLTrace": this.dataObject.setSqlTrace(0); break;
			}
			this.loadLogMessages(this.dataObject);
		},

		showAllChannels: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setPanic(1);
			this.dataObject.setError(1);
			this.dataObject.setWarn(1);
			this.dataObject.setInfo(1);
			this.dataObject.setDebug(1);
			this.dataObject.setTrace(1);
			this.dataObject.setSqlTrace(1);
			this.loadLogMessages(this.dataObject);
		},


		/** This allows our subclasses to do something in the scenario where the
		* edit view is opened up for a brand new object.
		*/
		initializeNewObject: function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */

			// Reload the user properties to pick up any recent changes:
			admin.Api.UserProperties({}, {}, this, function () {

				this.dataObject = new admin.sqldo.LogMessageFilter();

				// Now use our userProperties to initialize our log filters:
				var props = admin.Singleton.getInstance().getUserProperties();

				this.dataObject.setStartId(-1);

				if(this.m_object_id && this.m_object_id instanceof admin.sqldo.IAFile){
					this.dataObject.setLogFile( this.m_object_id.getParentFolder() +
						this.m_object_id.getFileName() );
				} else {
					var val = props["LogMessageFilter.LogFile"];
					if (val !== undefined) {
						this.dataObject.setLogFile(val);
					} else {
						this.dataObject.setLogFile("<Default>");
					}
				}
				val = props["LogMessageFilter.GetMax"];
				if (val !== undefined) {
					this.dataObject.setGetMax(Number(val));
				} else {
					this.dataObject.setGetMax(50);
				}
				val = props["LogMessageFilter.MachineName"];
				if (val !== undefined) {
					this.dataObject.setMachineName(val);
				} else {
					this.dataObject.setMachineName("");
				}
				val = props["LogMessageFilter.AppName"];
				if (val !== undefined) {
					this.dataObject.setAppName(val);
				} else {
					this.dataObject.setAppName("");
				}
				val = props["LogMessageFilter.ThreadID"];
				if (val !== undefined) {
					this.dataObject.setThreadID(Number(val));
				} else {
					this.dataObject.setThreadID(0);
				}
				val = props["LogMessageFilter.SUID"];
				if (val !== undefined) {
					this.dataObject.setSUID(val);
				} else {
					this.dataObject.setSUID("");
				}
				val = props["LogMessageFilter.Message"];
				if (val !== undefined) {
					this.dataObject.setMessage(val);
				} else {
					this.dataObject.setMessage("");
				}
				val = props["LogMessageFilter.Panic"];
				if (val !== undefined) {
					this.dataObject.setPanic(Number(val));
				} else {
					this.dataObject.setPanic(1);
				}
				val = props["LogMessageFilter.Error"];
				if (val !== undefined) {
					this.dataObject.setError(Number(val));
				} else {
					this.dataObject.setError(1);
				}
				val = props["LogMessageFilter.Warn"];
				if (val !== undefined) {
					this.dataObject.setWarn(Number(val));
				} else {
					this.dataObject.setWarn(1);
				}
				val = props["LogMessageFilter.Info"];
				if (val !== undefined) {
					this.dataObject.setInfo(Number(val));
				} else {
					this.dataObject.setInfo(1);
				}
				val = props["LogMessageFilter.Debug"];
				if (val !== undefined) {
					this.dataObject.setDebug(Number(val));
				} else {
					this.dataObject.setDebug(1);
				}
				val = props["LogMessageFilter.Trace"];
				if (val !== undefined) {
					this.dataObject.setTrace(Number(val));
				} else {
					this.dataObject.setTrace(1);
				}
				val = props["LogMessageFilter.SqlTrace"];
				if (val !== undefined) {
					this.dataObject.setSqlTrace(Number(val));
				} else {
					this.dataObject.setSqlTrace(1);
				}
				val = props["LogMessageFilter.ShowColIcon"];
				if (val !== undefined) {
					this.dataObject.setShowColIcon(Number(val));
				} else {
					this.dataObject.setShowColIcon(1);
				}
				val = props["LogMessageFilter.ShowColID"];
				if (val !== undefined) {
					this.dataObject.setShowColID(Number(val));
				} else {
					this.dataObject.setShowColID(1);
				}
				val = props["LogMessageFilter.ShowColDate"];
				if (val !== undefined) {
					this.dataObject.setShowColDate(Number(val));
				} else {
					this.dataObject.setShowColDate(1);
				}
				val = props["LogMessageFilter.ShowColMachine"];
				if (val !== undefined) {
					this.dataObject.setShowColMachine(Number(val));
				} else {
					this.dataObject.setShowColMachine(0);
				}
				val = props["LogMessageFilter.ShowColApplication"];
				if (val !== undefined) {
					this.dataObject.setShowColApplication(Number(val));
				} else {
					this.dataObject.setShowColApplication(0);
				}
				val = props["LogMessageFilter.ShowColThread"];
				if (val !== undefined) {
					this.dataObject.setShowColThread(Number(val));
				} else {
					this.dataObject.setShowColThread(1);
				}
				val = props["LogMessageFilter.ShowColSUID"];
				if (val !== undefined) {
					this.dataObject.setShowColSUID(Number(val));
				} else {
					this.dataObject.setShowColSUID(0);
				}
				val = props["LogMessageFilter.ShowColFile"];
				if (val !== undefined) {
					this.dataObject.setShowColFile(Number(val));
				} else {
					this.dataObject.setShowColFile(0);
				}
				val = props["LogMessageFilter.ShowColLine"];
				if (val !== undefined) {
					this.dataObject.setShowColLine(Number(val));
				} else {
					this.dataObject.setShowColLine(0);
				}
				val = props["LogMessageFilter.ShowColChannel"];
				if (val !== undefined) {
					this.dataObject.setShowColChannel(Number(val));
				} else {
					this.dataObject.setShowColChannel(0);
				}
				val = props["LogMessageFilter.ShowColMessage"];
				if (val !== undefined) {
					this.dataObject.setShowColMessage(Number(val));
				} else {
					this.dataObject.setShowColMessage(1);
				}


				// Also populate the current list of log files:
				admin.Api.GetLogFiles(function (response) {
					admin.Statics.populateDropDown(this.LogFileField, response,
						"LogFile", "<Default>");

					this.loadDataIntoForm();

					if (this.dataObject.getLogFile() === "<Default>") {
						this.dataObject.setLogFile("");
					}

					// Override our log table model with our remote version:
					var tm = new admin.admin.LogTableModel( this );
					this.logTable.setTableModel( tm );
					// jump to the bottom of the logs by default.
					this.logTable.getTableModel().addListenerOnce( "dataChanged", function(e) {
						this.logTable.scrollCellVisible( 0, 1000000 );
					}, this);

					this.showHideColumns();

					var tcm = this.logTable.getTableColumnModel();
					tcm.setDataCellRenderer( 0, new qx.ui.table.cellrenderer.Image() );
					tcm.addListener("visibilityChanged", this.colsChanged, this);


				}, this);

			});

		},

		showHideColumns: function() {

			var tcm = this.logTable.getTableColumnModel();
			tcm.removeListener("visibilityChanged", this.colsChanged, this);

			// Turn on/off columns by user preference:
			tcm.setColumnVisible( 0, Boolean(this.dataObject.getShowColIcon()) ); // Icon
			tcm.setColumnVisible( 1, Boolean(this.dataObject.getShowColID()) ); // ID
			tcm.setColumnVisible( 2, Boolean(this.dataObject.getShowColDate()) ); // Date
			tcm.setColumnVisible( 3, Boolean(this.dataObject.getShowColMachine()) ); // Machine
			tcm.setColumnVisible( 4, Boolean(this.dataObject.getShowColApplication()) ); // Application
			tcm.setColumnVisible( 5, Boolean(this.dataObject.getShowColThread()) ); // Thread
			tcm.setColumnVisible( 6, Boolean(this.dataObject.getShowColSUID()) ); // SUID
			tcm.setColumnVisible( 7, Boolean(this.dataObject.getShowColFile()) ); // File
			tcm.setColumnVisible( 8, Boolean(this.dataObject.getShowColLine()) ); // Line
			tcm.setColumnVisible( 9, Boolean(this.dataObject.getShowColChannel()) ); // Channel
			tcm.setColumnVisible( 10, Boolean(this.dataObject.getShowColMessage()) ); // Message


			tcm.addListener("visibilityChanged", this.colsChanged, this);
		},

		colsChanged: function() {
			var tcm = this.logTable.getTableColumnModel();
			this.dataObject.setShowColIcon( tcm.isColumnVisible(0) === true ? 1 : 0 );
			this.dataObject.setShowColID( tcm.isColumnVisible(1) === true ? 1 : 0 );
			this.dataObject.setShowColDate( tcm.isColumnVisible(2) === true ? 1 : 0 );
			this.dataObject.setShowColMachine( tcm.isColumnVisible(3) === true ? 1 : 0 );
			this.dataObject.setShowColApplication( tcm.isColumnVisible(4) === true ? 1 : 0 );
			this.dataObject.setShowColThread( tcm.isColumnVisible(5) === true ? 1 : 0 );
			this.dataObject.setShowColSUID( tcm.isColumnVisible(6) === true ? 1 : 0 );
			this.dataObject.setShowColFile( tcm.isColumnVisible(7) === true ? 1 : 0 );
			this.dataObject.setShowColLine( tcm.isColumnVisible(8) === true ? 1 : 0 );
			this.dataObject.setShowColChannel( tcm.isColumnVisible(9) === true ? 1 : 0 );
			this.dataObject.setShowColMessage( tcm.isColumnVisible(10) === true ? 1 : 0 );
		},

		loadLogFiles: function () {
			admin.Api.GetLogFiles(function (response) {
				admin.Statics.populateDropDown(this.LogFileField, response,
					"LogFile", "<Default>");
			}, this);
		},

		loadLogMessages: function (filter) {
			this.loadDataIntoForm();

			if (filter.getLogFile() === "<Default>") {
				filter.setLogFile("");
			}

			this.logTable.getTableModel().reloadData();

			/*
			admin.Api.GetLogMessages(filter, function (response) {
				var objectList = admin.sqldo.LogObj.readElementChildren(response);
				var rowData = [];
				for (var i = 0, l = objectList.length; i < l; i++) {
					var obj = objectList[i];
					if (i === 0) this.oldestID = obj.getId();
					if (i === (l - 1)) this.newestID = obj.getId();
					rowData.push([
						this.getChannelIcon( obj.getChannel() ),
						obj.getId(),
						obj.getTimestamp_c(),
						obj.getMachineName(),
						obj.getAppName(),
						obj.getTid(),
						obj.getFile(),
						obj.getLine(),
						this.getChannelName(obj.getChannel()),
						obj.getMsg()
					]);
				}
				this.logTable.getTableModel().setData(rowData);

			}, this);
			*/

		},

		loadFirstLogMessages: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setStartId(0);
			this.dataObject.setForward(1);
			this.loadLogMessages(this.dataObject);
			this.logTable.scrollCellVisible( 0, 0 );
		},

		loadPrevLogMessages: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setStartId(this.oldestID - 1);
			this.dataObject.setForward(-1);
			this.loadLogMessages(this.dataObject);
		},

		loadCurrentLogMessages: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setForward(1);
			this.loadLogMessages(this.dataObject);
		},

		loadNextLogMessages: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setStartId(this.newestID + 1);
			this.dataObject.setForward(1);
			this.loadLogMessages(this.dataObject);
		},

		loadLastLogMessages: function () {
			admin.Statics.pullAllFields(this, this.dataObject);
			this.dataObject.setStartId(-1);
			this.logTable.getTableModel().addListenerOnce( "dataChanged", function(e) {
				var tm = this.logTable.getTableModel();
				this.logTable.scrollCellVisible( 0, tm.getRowCount() );
			}, this);
			this.loadLogMessages(this.dataObject);
		},

		clearFilters: function() {
			this.dataObject.setLogFile( "" );
			this.dataObject.setStartId( -1 );
			this.dataObject.setGetMax(50);
			this.dataObject.setMachineName("");
			this.dataObject.setAppName("");
			this.dataObject.setThreadID(0);
			this.dataObject.setSUID("");
			this.dataObject.setMessage("");
			this.dataObject.setPanic(1);
			this.dataObject.setError(1);
			this.dataObject.setWarn(1);
			this.dataObject.setInfo(1);
			this.dataObject.setDebug(1);
			this.dataObject.setTrace(1);
			this.dataObject.setSqlTrace(1);
			admin.Statics.loadAllFields(this, this.dataObject);
			this.loadLastLogMessages();
		},

		doFind: function() {

			var tmpWindow = new admin.admin.LogFindDialog("Find Log Message...");
			tmpWindow.addOkEventListener("execute", function() {
				if(tmpWindow.idField.getValue() !== null){
					this.dataObject.setFindByID( Number( tmpWindow.idField.getValue() ) );
				} else {
					this.dataObject.setFindByID( 0 );
				}

				if(tmpWindow.dateField.getValue() !== null){
					this.dataObject.setFindByDate(
						tmpWindow.dateField.getDateFormat().format( tmpWindow.dateField.getValue()) );
				} else {
					this.dataObject.setFindByDate( "" );
				}

				if(tmpWindow.messageField.getValue() !== null){
					this.dataObject.setFindByMsg( tmpWindow.messageField.getValue() );
				} else {
					this.dataObject.setFindByMsg( "" );
				}

				admin.Api.FindLogMessage( this.dataObject, function(response) {
					var objs = admin.sqldo.LogMessageFilter.readElementChildren( response );
					if(objs.length !== 0){
						var targetRow = objs[0].getFirstRow();
						this.logTable.scrollCellVisible( 0, targetRow );
						this.logTable.getSelectionModel().setSelectionInterval( targetRow, targetRow );
					}
				}, this );
			}, this );

			qx.core.Init.getApplication().getRoot().add(tmpWindow);
			tmpWindow.open();
		},

		forwardToSupport: function() {
			admin.Statics.pullAllFields(this, this.dataObject);

			if (this.dataObject.getLogFile() === "<Default>" ||
				this.dataObject.getLogFile() === ""
			) {
				this.dataObject.setLogFile("ihd.log");
			}

			admin.Api.ForwardToSupport(this.dataObject, function (response) {
				// The ForwardToSupport call now just prepares the file that should
				// be sent to support.  We'll use the ForwardToSupportDialog to get
				// the real work done

				// Which file was created to send to support?
				var objs = admin.sqldo.IAFile.readElementChildren( response );

				var ftsDialog = new admin.dialog.ForwardToSupportDialog( objs[0].getFileName() );
				ftsDialog.addListener( "forwardFinished", function() {
					// Tell the server it can get rid of the support bundle
					var sb = new admin.sqldo.SupportBundle;
					sb.setFileName( ftsDialog.forwardFile );
					admin.Api.CleanupSupportFile( sb, function(response){
						// nothing to do
					}, this);
				}, this);

				// Now open that dialog and let the user choose what to do:
				ftsDialog.open();

			}, this);

		},

		getChannelName: function (channel) {
			switch (channel) {
				case 0: return "Panic";
				case 1: return "Error";
				case 2: return "Warn";
				case 3: return "Info";
				case 4: return "Debug";
				case 5: return "Trace";
				case 6: return "SQLTrace";
				default: return "Unknown";
			}
		},

		getChannelIcon: function(channel){
			switch(channel){
				case 0: return this.panicImg;
				case 1: return this.errorImg;
				case 2: return this.warnImg;
				case 3: return this.infoImg;
				case 4: return this.debugImg;
				case 5: return this.traceImg;
				case 6: return this.sqltraceImg;
				default: return this.unknownImg;
			}
		},

		/** This method is called by the "get" API function and should be prepared to read
		* our data object from the XML sent back to us by the server.
		*/
		getObjectDetails: function (response) {
			var objectList = admin.sqldo.Table.readElementChildren(response);
			if (objectList.length === 0) {
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.loadDataIntoForm();
		},

		/** This handles loading our GUI form fields based on the information contained
		* in our data object.
		*/
		loadDataIntoForm: function () {
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			admin.Statics.loadAllFields(this, this.dataObject);


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			this.overview_label3.setLabel("Machine: " + this.dataObject.getMachineName());
			this.overview_label4.setLabel("App: " + this.dataObject.getAppName());
			this.overview_label5.setLabel("Thread: " + this.dataObject.getThreadID());
			this.overview_label5a.setLabel("SUID: " + this.dataObject.getSUID());
			this.overview_label6.setLabel("Msg: " + this.dataObject.getMessage());
			this.overview_label7.setLabel(this.dataObject.getPanic() === 1 ? "Panic: On" : "Panic: Off");
			this.overview_label8.setLabel(this.dataObject.getError() === 1 ? "Error: On" : "Error: Off");
			this.overview_label9.setLabel(this.dataObject.getWarn() === 1 ? "Warn: On" : "Warn: Off");
			this.overview_label10.setLabel(this.dataObject.getInfo() === 1 ? "Info: On" : "Info: Off");
			this.overview_label11.setLabel(this.dataObject.getDebug() === 1 ? "Debug: On" : "Debug: Off");
			this.overview_label12.setLabel(this.dataObject.getTrace() === 1 ? "Trace: On" : "Trace: Off");
			this.overview_label13.setLabel(this.dataObject.getSqlTrace() === 1 ? "Sql Trace: On" : "Sql Trace: Off");


			if(this.dataObject.getLogFile().length === 0 ||
				this.dataObject.getLogFile() === "<Default>"
			){
				this.overview_label2.setLabel(
					"<a href=\"/logfile/viaserv.log\">" +
					"Log File: " + this.dataObject.getLogFile() +
					"</a>"
				);
			} else {
				this.overview_label2.setLabel(
					"<a href=\"/logfile/" + this.dataObject.getLogFile() + "\">" +
					"Log File: " + this.dataObject.getLogFile() +
					"</a>"
				);
			}

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

		},

		/** This handles pulling data from GUI form fields and loading their values
		* back into our data object.
		*/
		pullDataFromForm: function () {
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* pulling all fields that are registered in this object   */
			/* directly from our form and saving them to the dataObject*/
			/* ******************************************************* */
			admin.Statics.pullAllFields(this, this.dataObject);

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

		},

		/** This handles the calls required to save our dataObject back to the
		* server.
		*/
		doSaveToServer: function () {
			this.pullDataFromForm();
			admin.Api.SaveObjectAPICallFIXME(this.dataObject,
			function (response) {
				// pick up any new information here.

			}, this);

		}


	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {

		this._disposeFields("rmc");

		this._disposeObjects(
			"tabview",
			"dataObject",
			"m_object_id"
		);
		admin.Statics.destroyExtraObjects(this);
	}

});
