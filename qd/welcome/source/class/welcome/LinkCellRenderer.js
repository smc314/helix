/* ************************************************************************

   Copyright: 2013 Hericus Software, LLC

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */

/**
 * The cell renderer used for displaying hyper links inside a table.
 */
qx.Class.define("welcome.LinkCellRenderer",
{
  extend : qx.ui.table.cellrenderer.Default,

  /*
  *****************************************************************************
     MEMBERS
  *****************************************************************************
  */

  members :
  {
    // overridden
    _getContentHtml : function(cellInfo) {
    	return "<a href=\"/DownloadBuildStatusFile?historyid=" +
				this.buildHistoryID + "&fileName=" + cellInfo.value +
				"\">" + cellInfo.value + "</a>";
      //return qx.html.String.escape(this._formatValue(cellInfo));
    },

	setBuildHistoryID : function(id){
		this.buildHistoryID = id;
	}


  }
});
