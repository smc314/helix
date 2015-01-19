/* ************************************************************************

   Copyright: 2008 - 2014 Hericus Software, LLC

   License: MIT License

   Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/media_rewind.png)
#asset(admin/icon/16x16/plain/media_fast_forward.png)
************************************************************************ */


/** This class defines a simple dialog that presents a single drop-down
  * and a text entry window to the user.  You can set the window title,
  * icon, and label to customize
  * the presentation of the window.  You should also get the dropdown
  * after creating the window, but before opening it, and populate it with
  * the values that you want the user to choose from.
  */
qx.Class.define("admin.admin.LogMsgDialog", {
	extend : admin.dialog.OKDialog,

	/** You may pass in window title, icon, and label values.
	  */
	construct : function ( title ) {
		// Call the parent constructor:
		this.base( arguments, title );
	},

	members : {

		/** This method is used to allow child classes to override the size
		  * of this dialog box.
		  */
		doSetSpace : function () {
			this.setWidth(600);
			this.setHeight(500);
		},

		/** This method allows you to set the focus of whichever field you
		  * want when this window becomes active.  This will be called every
		  * time this window becomes the active window, which will only happen
		  * once for a modal window.
		  */
		setFocusFirst : function () {
			this.idField.selectAllText();
			this.idField.focus();
		},

		/** This method is used to allow child classes to add objects to our
		  * main layout.
		  */
		doFormLayout : function ( layout ) {
			this.createNextPrev( layout );

			var leftSize = 80;
			var middleSize = 80;
			admin.Statics.addFieldsToForm( this, layout,
				"ID:", leftSize, "idField", "TextField",
				"Date:", middleSize, "dateField", "TextField");

			admin.Statics.addFieldsToForm( this, layout,
				"Machine:", leftSize, "machineField", "TextField",
				"Application:", middleSize, "applicationField", "TextField");

			admin.Statics.addFieldsToForm( this, layout,
				"Channel:", leftSize, "channelField", "TextField",
				"Thread:", middleSize, "threadField", "TextField");

			admin.Statics.addFieldsToForm( this, layout,
				"SUID:", leftSize, "suidField", "TextField");

			admin.Statics.addFieldsToForm( this, layout,
				"File:", leftSize, "fileField", "TextField",
				"Line#:", leftSize, "lineField", "TextField");

			var l1 = new qx.ui.basic.Label("Log Message:");
			layout.add(l1);

			this.textArea = new qx.ui.form.TextArea;
			this.textArea.setWrap(true);
			this.textArea.setAllowStretchX(true);
			this.textArea.setAllowStretchY(true);
			this.textArea.setFont("monospace");
			layout.add(this.textArea, {flex:1});
		},

		/** This will create the Next Message, Previous Message buttons
		 * that are displayed on the form.
		 */
		createNextPrev : function (layout) {
			var hbox = new qx.ui.layout.HBox(10);
			var nplayout = new qx.ui.container.Composite(hbox);
			nplayout.set({paddingTop:2, paddingBottom:2});

			this.prevBtn = new qx.ui.form.Button("Previous Log Message",
				"admin/icon/16x16/plain/media_rewind.png");
			this.prevBtn.addListener("execute", this.movePrev, this);
			this.nextBtn = new qx.ui.form.Button("Next Log Message",
				"admin/icon/16x16/plain/media_fast_forward.png");
			this.nextBtn.addListener("execute", this.moveNext, this);
			this.nextBtn.setIconPosition("right");

			var label = new qx.ui.basic.Label("");
			label.setAllowGrowX(true);
			label.setMinWidth(20);
			label.setWidth(20);

			nplayout.add(this.prevBtn);
			nplayout.add(label, {flex:1} );
			nplayout.add(this.nextBtn);

			layout.add(nplayout);

		},

		movePrev : function() {
			if(this.tableModel === undefined || this.currentRow === undefined){
				return; // caller hasn't set us up properly.
			}
			if(this.currentRow === 0){
				return; // already at the top of the table.
			}
			this.currentRow --;
			this.loadRow();
		},

		moveNext : function() {
			if(this.tableModel === undefined || this.currentRow === undefined){
				return; // caller hasn't set us up properly.
			}
			if(this.currentRow === this.tableModel.getRowCount() ){
				return; // already at the bottom of the table.
			}
			this.currentRow ++;
			this.loadRow();
		},

		loadRow : function() {
			if(this.tableModel === undefined || this.currentRow === undefined){
				return; // caller hasn't set us up properly.
			}

			this.idField.setValue( String(this.tableModel.getValue(1, this.currentRow)) );
			this.dateField.setValue( this.tableModel.getValue( 2, this.currentRow ) );
			this.machineField.setValue( this.tableModel.getValue( 3, this.currentRow ) );
			this.applicationField.setValue( this.tableModel.getValue( 4, this.currentRow ) );
			this.threadField.setValue( String(this.tableModel.getValue( 5, this.currentRow )) );
			this.suidField.setValue( String(this.tableModel.getValue( 6, this.currentRow )) );
			this.fileField.setValue( this.tableModel.getValue( 7, this.currentRow ) );
			this.lineField.setValue( String(this.tableModel.getValue( 8, this.currentRow )) );
			this.channelField.setValue( this.tableModel.getValue( 9, this.currentRow ) );
			this.textArea.setValue( this.tableModel.getValue( 10, this.currentRow ) );

			this.setCaption("Log Msg: " + this.idField.getValue() );
			this.logTable.getSelectionModel().setSelectionInterval(this.currentRow, this.currentRow);
		}

	},

	destruct : function() {
		this._disposeObjects( "ok_btn", "idField", "dateField",
			"machineField", "applicationField",
			"channelField", "threadField", "fileField", "lineField", "textArea"
		);
	}

});
