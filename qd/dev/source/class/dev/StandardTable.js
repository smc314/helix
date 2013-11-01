/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
qx.Class.define("dev.StandardTable", {
	extend: qx.core.Object,

	properties : {
		/**
		* This gives you direct access to the qx.ui.table.Table that we manipulate.
		*/
		table : {init : null, check : "Object"},

		/** This is the button we use to trigger add-row activity.
		  */
		addRowButton : {init: null, check : "Object", apply: "_applyAddRowButton"},

		/** This is the button we use to trigger delete-row activity.
		  */
		deleteRowButton : {init: null, check : "Object", apply: "_applyDeleteRowButton"},

		/** This is the button we use to trigger move-up activity.
		  */
		moveUpButton : {init: null, check : "Object", apply: "_applyMoveUpButton"},

		/** This is the button we use to trigger move-down activity.
		  */
		moveDownButton : {init: null, check : "Object", apply: "_applyMoveDownButton"}

	},

	construct: function (qxTable, addButton, deleteButton, moveUpButton, moveDownButton) {
		this.base(arguments);

		this.setTable( qxTable );
		if(addButton){
			this.setAddRowButton( addButton );
		}
		if(deleteButton){
			this.setDeleteRowButton( deleteButton );
		}
		if(moveUpButton){
			this.setMoveUpButton( moveUpButton );
		}
		if(moveDownButton){
			this.setMoveDownButton( moveDownButton );
		}
	},

	members: {
		/** This is the default data that we will add to the table when the user clicks the "add" button.
		  */
		defaultRowData : [],

		setDefaultRowData : function( dataRow ){
			this.defaultRowData = dataRow;
		},

		getSelectedIndexes : function () {
			var t = this.getTable();
			if(t === null){
				return [];
			}
			var smodel = t.getSelectionModel();
			if(smodel.isSelectionEmpty()){
				return [];
			}

			var selectedRowData = [];
			smodel.iterateSelection(function(index){ selectedRowData.push( index ); } );

			return selectedRowData;
		},

		getFirstSelected : function(){
			var selected = this.getSelectedIndexes();
			if(selected.length === 0){
				return null;
			} else {
				return selected[ 0 ];
			}
		},

		selectFirstRow : function() {
			var t = this.getTable();
			if(t === null){
				return;
			}
			var smodel = t.getSelectionModel();
			smodel.resetSelection();
			smodel.setSelectionInterval( 0, 0 );
		},

		selectLastRow : function() {
			var t = this.getTable();
			if(t === null){
				return;
			}
			var lastRow = t.getTableModel().getRowCount() - 1;
			var smodel = t.getSelectionModel();
			smodel.setSelectionInterval( lastRow, lastRow );
		},

		getRowValue : function( row, col ){
			var t = this.getTable();
			if(t === null){
				return null;
			}
			return t.getTableModel().getValue( col, row );
		},

		doAddRow : function() {
			var t = this.getTable();
			if(t === null){
				return;
			}
			var tm = t.getTableModel();
			var sm = t.getSelectionModel();
			var rows = [];
			rows.push( this.defaultRowData );
			tm.addRows( rows );
			var lastRow = tm.getRowCount() - 1;
			sm.setSelectionInterval( lastRow, lastRow );
		},

		doDeleteRow : function() {
			var t = this.getTable();
			if(t === null){
				return;
			}
			var selected = this.getSelectedIndexes();
			if(selected.length === 0){
				return; // nothing selected, bail out
			}
			var tm = t.getTableModel();
			var sm = t.getSelectionModel();

			// Run the selected indexes in reverse and remove them from the table:
			for(var i = selected.length - 1; i >= 0; i--){
				tm.removeRows( selected[ i ], 1); // remove this row.
			}

			sm.resetSelection();
		},

		doMoveUp: function() {
			var t = this.getTable();
			if(t === null){
				return;
			}
			var selected = this.getSelectedIndexes();
			if(selected.length === 0 || selected[ 0 ] === 0){
				return; // nothing selected - or selection is at top - bail out
			}

			var tm = t.getTableModel();
			var sm = t.getSelectionModel();

			// Move the data around
			var rowData = tm.getData();
			for(var i = 0, l = selected.length; i < l; i++){
				var tmp = rowData[ selected[i] - 1 ];
				rowData[ selected[i] - 1 ] = rowData[ selected[i] ];
				rowData[ selected[i] ] = tmp;
			}
			tm.setData( rowData );

			// Update the selection
			sm.resetSelection();
			for(var i = 0, l = selected.length; i < l; i++){
				sm.addSelectionInterval( selected[i] - 1, selected[i] - 1);
			}

		},

		doMoveDown: function() {
			var t = this.getTable();
			if(t === null){
				return;
			}
			var selected = this.getSelectedIndexes();
			var tm = t.getTableModel();
			var sm = t.getSelectionModel();
			var rowData = tm.getData();
			if(selected.length === 0 || selected[ selected.length - 1 ] === (rowData.length - 1) ){
				return; // nothing selected - or selection is at bottom - bail out
			}

			// Move the data around
			for(var i = selected.length - 1; i >= 0; i--){
				var tmp = rowData[ selected[i] + 1 ];
				rowData[ selected[i] + 1 ] = rowData[ selected[i] ];
				rowData[ selected[i] ] = tmp;
			}
			tm.setData( rowData );

			// Update the selection
			sm.resetSelection();
			for(var i = 0, l = selected.length; i < l; i++){
				sm.addSelectionInterval( selected[i] + 1, selected[i] + 1);
			}

		},

		setEditable : function( column ) {
			var t = this.getTable();
			if(t === null){
				return;
			}
			t.getTableModel().setColumnEditable( column, true );
		},

		setEditableAsDropDown : function( colNum, ddValues ) {
			var t = this.getTable();
			if(t === null){
				return;
			}

			// create a "meta" cell renderer object
			var propCellRendererFactory = new qx.ui.table.cellrenderer.Dynamic (
				function(cellInfo){
					var renderer = new qx.ui.table.cellrenderer.Replace;
					var replaceMap = {};
					for( var i = 0, l = ddValues.length; i < l; i++){
						replaceMap[ ddValues[i] ] = ddValues[i];
					}
					renderer.setReplaceMap( replaceMap );
					renderer.addReversedReplaceMap();
					return renderer;
				}
			);

			// Create a "meta" cell editor object
			var propCellEditorFactory = new qx.ui.table.celleditor.Dynamic(
				function(cellInfo){
					var cellEditor = new qx.ui.table.celleditor.SelectBox();
					var options = [];
					for(var i = 0, l = ddValues.length; i < l; i++){
						options.push( [ ddValues[i], null, ddValues[i] ] );
					}
					cellEditor.setListData( options );
					return cellEditor;
				}
			);

			var tm = t.getTableModel();
			var tcm = t.getTableColumnModel();
			tm.setColumnEditable( colNum, true);
			tcm.setDataCellRenderer( colNum, propCellRendererFactory );
			tcm.setCellEditorFactory( colNum, propCellEditorFactory );

		},


		_applyAddRowButton : function(value, old){
			// When the user hooks up an AddRow button, we need to listen to it to
			// enable the add functionality.
			if(value === old){
				// Setting the same guy again.  nothing to do.
				return;
			}
			if(old !== null){
				// remove our listener from the old button
				old.removeListener("execute", this.doAddRow, this);
			}
			value.addListener("execute", this.doAddRow, this );
		},

		_applyDeleteRowButton : function(value, old){
			// When the user hooks up an DeleteRow button, we need to listen to it to
			// enable the add functionality.
			if(value === old){
				// Setting the same guy again.  nothing to do.
				return;
			}
			if(old !== null){
				// remove our listener from the old button
				old.removeListener("execute", this.doDeleteRow, this);
			}
			value.addListener("execute", this.doDeleteRow, this );
		},

		_applyMoveUpButton : function(value, old){
			// When the user hooks up an MoveUp button, we need to listen to it to
			// enable the add functionality.
			if(value === old){
				// Setting the same guy again.  nothing to do.
				return;
			}
			if(old !== null){
				// remove our listener from the old button
				old.removeListener("execute", this.doMoveUp, this);
			}
			value.addListener("execute", this.doMoveUp, this );
		},

		_applyMoveDownButton : function(value, old){
			// When the user hooks up an MoveUp button, we need to listen to it to
			// enable the add functionality.
			if(value === old){
				// Setting the same guy again.  nothing to do.
				return;
			}
			if(old !== null){
				// remove our listener from the old button
				old.removeListener("execute", this.doMoveDown, this);
			}
			value.addListener("execute", this.doMoveDown, this );
		}

	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		//this._disposeObjects(
		//	"toolbar"
		//);
	}

});
