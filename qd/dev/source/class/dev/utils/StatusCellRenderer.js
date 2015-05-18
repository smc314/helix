/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */

/**
 * The cell renderer used for displaying Red, Yellow, Green backgrounds.
 */
qx.Class.define("dev.utils.StatusCellRenderer",
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
    _getCellStyle : function(cellInfo) {
    	var style = this.base(arguments, cellInfo); // call the parent first.
    	if(cellInfo.value.substr(0, 4) === "Warn"){
    		style = style + "background:yellow;";
    	} else if(cellInfo.value.substr(0, 4) === "Fail"){
    		style = style + "background:#dc363a;";
    	} else if(cellInfo.value.substr(0, 4) === "Succ"){
    		style = style + "background:#339669;";
    	}
    	return style;
    }
  }
});
