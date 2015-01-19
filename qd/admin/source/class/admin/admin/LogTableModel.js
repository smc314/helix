/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */


/** This class defines a remote table model that we use to bring back log
  * messages as the user requests them.  This allows us to work with the
  * qooxdoo remote table model which does not require that all data be in
  * memory on the client at once.
  */
qx.Class.define("admin.admin.LogTableModel", {
	extend : qx.ui.table.model.Remote,

	construct : function ( logMonitor ) {
		this.__logMonitor = logMonitor;

		// Call the parent constructor:
		this.base( arguments );

		// Setup our columns:
		this.setColumns(
			[" ", "ID", "Date", "Machine", "Application", "Thread", "SUID", "File", "Line", "Channel", "Message"],
			["icon", "id", "date", "machine", "application", "thread", "suid", "file", "line", "channel", "message"]
		);
	},

	members : {

		__logMonitor : null,

		/** This method is overloaded and is what the base class uses to determine
		  * how many rows should be displayed for the table.  We must remember to
		  * call _onRowCountLoaded with the new row count at some point during this
		  * method.
		  */
		_loadRowCount : function () {
			admin.Api.GetLogMsgCount( this.__logMonitor.dataObject, function(response) {
				var objs = admin.sqldo.LogMessageFilter.readElementChildren( response );
				if(objs.length === 0){
					// Ensure we call this even in an error:
					this._onRowCountLoaded( 0 );
				} else {
					this._onRowCountLoaded( objs[0].getFilterMatchCount() );
				}
			}, this);
		},

		/** This method is overloaded to load the data from the server for the given
		  * range of rows.  The row indexes are given as 0-based table row values.
		  * We need to translate them into log message id's and request those rows
		  * from the server.  We must remember to call _onRowDataLoaded with the new
		  * data during this method
		  */
		_loadRowData : function (firstRow, lastRow) {
			this.__logMonitor.dataObject.setFirstRow( firstRow );
			this.__logMonitor.dataObject.setLastRow( lastRow );
			admin.Api.GetLogMessagesByRange( this.__logMonitor.dataObject, function(response) {
				var objs = admin.sqldo.LogObj.readElementChildren( response );
				var rowData = [];
				for(var i = 0, l = objs.length; i < l; i++){
					var obj = objs[i];
					rowData.push( {
						icon: this.__logMonitor.getChannelIcon( obj.getChannel() ),
						id: obj.getId(),
						date: obj.getTimestamp_c(),
						machine: obj.getMachineName(),
						application: obj.getAppName(),
						thread: obj.getTid(),
						suid: obj.getSUID(),
						file: obj.getFile(),
						line: obj.getLine(),
						channel: this.__logMonitor.getChannelName( obj.getChannel() ),
						message: obj.getMsg()
					});
				}

				this._onRowDataLoaded( rowData );

			}, this);
		}

	},

	destruct : function() {
	}

});
