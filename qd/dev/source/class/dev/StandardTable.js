/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/edit.png)
#asset(dev/icon/16x16/plain/document_new.png)
#asset(dev/icon/16x16/plain/delete2.png)
#asset(dev/icon/32x32/shadow/sign_warning.png)
************************************************************************ */
qx.Class.define("dev.StandardTable", {
	extend: qx.core.Object,

	properties : {
		/**
		* This gives you direct access to the qx.ui.table.Table that we manipulate.
		*/
		table : {init : null, check : "Object"},

		/**
		* This gives you direct access to the data array that we use to populate
		* the information in the table.
		*/
		tableData : {init : null, check : "Array"},

		/**
		* This is the list of fields that we pull from each array object to
		* populate the colums for each row of data displayed in the table.
		*/
		dataFields : {init : null, check : "Array"},

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
		moveDownButton : {init: null, check : "Object", apply: "_applyMoveDownButton"},

		/** This is the function we use when editing a row.
		  */
		editRowFunction : {init: null, check : "Function", apply: "_applyEditRowFunction"},

		/** This is the context to use when calling the function we use when editing a row.
		  */
		editRowFunctionThis : {init: null, check : "Object", apply: "_applyEditRowFunctionThis"},

		/** This is the function we use when adding a row.
		  */
		addRowFunction : {init: null, check : "Function"},

		/** This is the function we use when removing a row.
		  */
		deleteRowFunction : {init: null, check : "Function"}
	},

	construct: function (qxTable, addButton, deleteButton, moveUpButton, moveDownButton,
		editRowFunction, editRowFunctionThis,
		addRowFunction, deleteRowFunction
	) {
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
		if(editRowFunction){
			this.setEditRowFunction( editRowFunction );
			if(editRowFunctionThis){
				this.setEditRowFunctionThis( editRowFunctionThis );
			}
		}
		if(addRowFunction){
			this.setAddRowFunction( addRowFunction );
		}
		if(deleteRowFunction){
			this.setDeleteRowFunction( deleteRowFunction );
		}

		this.createRMCMenu();

	},

	members: {
		/** This is the default data that we will add to the table when the user clicks the "add" button.
		  */
		defaultRowData : [],

		setDefaultRowData : function( dataRow ){
			this.defaultRowData = dataRow;
		},

		createRMCMenu : function() {
			if(this.rmc !== undefined && this.rmc !== null){
				this._disposeFields( "rmc" );
				this.rmc = null;
			}

			this.rmc = new qx.ui.menu.Menu;

			// edit
			if(this.getEditRowFunction() !== null){
				dev.Statics.addToRMCMenu( this.rmc, "Edit...",
					"dev/icon/16x16/plain/edit.png",
					this.rmcEdit, this );
			}

			// Add New...
			if(this.getAddRowButton() !== null){
				dev.Statics.addToRMCMenu( this.rmc, "Add New...",
					"dev/icon/16x16/plain/document_new.png",
					function(){ this.getAddRowButton().execute(); }, this );
			}

			// Delete...
			if(this.getDeleteRowButton() !== null){
				dev.Statics.addToRMCMenu( this.rmc, "Delete...",
					"dev/icon/16x16/plain/delete2.png",
					function(){ this.getDeleteRowButton().execute(); }, this );
			}

			this.getTable().setContextMenu( this.rmc );
			this.getTable().addListener( "dblclick", this.rmcEdit, this );
		},

		rmcEdit : function() {
			if(this.getTable().getSelectionModel().isSelectionEmpty() ){
				dev.Statics.doAlert("Nothing selected to edit!");
				return;
			}
			if(this.getEditRowFunction() !== null){
				if(this.getEditRowFunctionThis() !== null){
					// If they've given us a context - then go ahead and use it
					this.getEditRowFunction().call( this.getEditRowFunctionThis() );
				} else {
					// If not - then use this standard table as the context
					this.getEditRowFunction().call( this );
				}
			}
		},

		bindTableData : function(dataArray, dataFields){
			this.setTableData( dataArray );
			this.setDataFields( dataFields );

			this.refreshTable();
		},

		refreshTable : function() {
			var dataArray = this.getTableData();

			var rowData = [];
			for(var i = 0, l = dataArray.length; i < l; i++){
				rowData.push( this.getRowDataFromObject( dataArray[i] ) );
			}
			this.getTable().getTableModel().setData( rowData );
		},

		getRowDataFromObject : function( rowObj ){
			var dataFields = this.getDataFields();
			var row = [];
			for(var i = 0, l = dataFields.length; i < l; i++){
				var getName = "get" + dataFields[i];
				row.push( rowObj[getName]() );
			}
			return row;
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
			if(this.getAddRowFunction() !== null){
				var rowObj = this.getAddRowFunction().call( this.getEditRowFunctionThis() );
				rows.push(
					this.getRowDataFromObject(
						rowObj
					)
				);
				this.getTableData().push( rowObj );
			} else {
				rows.push( this.defaultRowData );
			}
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
				dev.Statics.doAlert("Nothing selected to delete.");
				return; // nothing selected, bail out
			}
			var tm = t.getTableModel();
			var sm = t.getSelectionModel();

			var windowTitle = "Deleting...";
			var windowIcon = "dev/icon/32x32/shadow/sign_warning.png";
			var windowLabel = "Are you sure you want to delete the selected items?";
			var tmpWindow = new dev.dialog.QuestionDialog( windowTitle, windowIcon, windowLabel);
			qx.core.Init.getApplication().getRoot().add(tmpWindow);
			tmpWindow.addOkEventListener("execute", function() {

				// Run the selected indexes in reverse and remove them from the table:
				for(var i = selected.length - 1; i >= 0; i--){
					if(this.getDeleteRowFunction() !== null){
						var rowObj = this.getTableData()[ selected[i] ];
						this.getDeleteRowFunction().call( this.getEditRowFunctionThis(), rowObj );
						this.getTableData().splice( selected[i], 1 ); // Remove this row
					}
					// Remove it from the table model as well
					tm.removeRows( selected[ i ], 1); // remove this row.
				}

				sm.resetSelection();
			}, this);
			tmpWindow.open();
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
		},

		_applyEditRowFunction: function(value, old){
			// When the user hooks up an MoveUp button, we need to listen to it to
			// enable the add functionality.
			if(value === old){
				// Setting the same guy again.  nothing to do.
				return;
			}
		},

		_applyEditRowFunctionThis: function(value, old){
			// When the user hooks up an MoveUp button, we need to listen to it to
			// enable the add functionality.
			if(value === old){
				// Setting the same guy again.  nothing to do.
				return;
			}
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
