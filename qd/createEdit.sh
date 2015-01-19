#!/bin/bash
#############################################################################################
# This script makes it easy to start a new logic skeleton.  We'll create the header and body
# files with everything required.  Just pass us the new Class name.

CLASSNAME=$1
PACKAGE=$2
JAVASCRIPT=${CLASSNAME}.js
LAYOUT1=../../../layouts/${CLASSNAME}.MainPage.xml
LAYOUT2=../../../layouts/${CLASSNAME}.NextPage.xml
TMP=`pwd`
FOLDER=${TMP##*/}
THISYEAR=`date +%Y`

#############################################################################################
# Here's the new class file that is based on an ObjectEdit standard.
#############################################################################################
echo "Creating file ${JAVASCRIPT} based on class: ${CLASSNAME} and package ${PACKAGE}"
cat >${JAVASCRIPT} <<EOF
/* ************************************************************************

   Copyright: ${THISYEAR} Your Company, Inc.

   Authors:  You and your developers

************************************************************************ */
/* ************************************************************************
#asset(${PACKAGE}/icon/64x64/shadow/control_panel2.png)
************************************************************************ */
qx.Class.define("${PACKAGE}.${FOLDER}.${CLASSNAME}", {
	extend: ${PACKAGE}.ObjectEdit,

	construct : function ( object_id ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "${CLASSNAME}.MainPage.xml", doc:null});
		this.dynamicLayouts.push({name: "${CLASSNAME}.NextPage.xml", doc:null});

		this.base(arguments, object_id);
	},

	members : {

		/** This is where the subclasses will tell us which API functions to use,
		  * which callbacks to use, which names to use, etc.
		  */
		setupNamesAndFunctions : function() {
			this.selectApiCall = null; //${PACKAGE}.Api.GetObjectAPICallFIXME;
		},

		/** This function is responsible for initializing our toolbar.  We extend
		  * the parent class functionality by adding our own icons and actions.
		  */
		initializeToolbar : function( tb ) {
			// If you don't want the standard toolbar save/refresh actions, don't call this
			this.base(arguments, tb); // Call the parent class first

			// Then add any other actions that you would like here:
			// var part = new qx.ui.toolbar.Part;
			//
			// ${PACKAGE}.Statics.addToToolbar( part, "${PACKAGE}/icon/16x16/plain/refresh.png",
			//	"Tooltip for action here", this.actionHandler, this, this);
			//
			// tb.add(part);

			// remember to return the toolbar we've enhanced:
			return tb;
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function() {
			this.tabview = new qx.ui.tabview.TabView;
			this.add(this.tabview, { flex: 10 });

			this.createMainTab(${PACKAGE}.Statics.addEditorSubTab(this.tabview, "General", true));
			this.createNextTab(${PACKAGE}.Statics.addEditorSubTab(this.tabview, "Next Tab", false));
			// Load more tabs here

		},

		/** This is the main page with the overall object summary and the first
		  * set of form fields.
		  */
		createMainTab: function(tab_page)
		{
			var live = this.createOverviewLayout( tab_page, "Large Title", 
				"${PACKAGE}/icon/64x64/shadow/control_panel2.png",
				this.m_object_id === 0 ? "NEW1" : this.m_object_id.getName1() );

			this.addStatusHeading("General");
			this.overview_label1 = this.addStatusItem("Overview Label1:", 
				"${PACKAGE}/icon/16x16/plain/barcode.png");


			${PACKAGE}.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("${CLASSNAME}.MainPage.xml"),
				live );

		},

		/** This creates a standard tab that is controlled by the layout page
		  * rendered onto it.
		  */
		createNextTab: function(tab_page)
		{
			${PACKAGE}.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("${CLASSNAME}.NextPage.xml"),
				tab_page );

		},

		/** This allows our subclasses to do something in the scenario where the
		  * edit view is opened up for a brand new object.
		  */
		initializeNewObject : function () {
			/* ******************************************************* */
			/* Do Any initialization here to this.dataObject           */
			/* ******************************************************* */
			this.isNewObject = true;

			/* ******************************************************* */
			/* If you would like to launch a wizard, then do it like   */
			/* this:                                                   */
			/* ******************************************************* */
			/*
			var windowTitle = "New Object Wizard";
			var windowIcon = "${PACKAGE}/icon/128x128/shadow/box_software.png";
			var tmpWindow = new ${PACKAGE}.${FOLDER}.NewObjectWizard(windowTitle, windowIcon, this);
			tmpWindow.open();
			qx.core.Init.getApplication().getRoot().add(tmpWindow);
			*/

			// After you've initialized this.dataObject then:
			this.loadDataIntoForm();

		},

		/** This method is called by the "get" API function and should be prepared to read
		  * our data object from the XML sent back to us by the server.
		  */
		getObjectDetails : function (response)
		{
			var objectList = ${PACKAGE}.sqldo.Table.readElementChildren(response);
			if(objectList.length === 0){
				return; // Nothing to do.
			}
			this.dataObject = objectList[0];
			this.isNewObject = false;
			this.loadDataIntoForm();
		},

		/** This handles loading our GUI form fields based on the information contained
		  * in our data object.
		  */
		loadDataIntoForm : function ()
		{
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			${PACKAGE}.Statics.loadAllFields(this, this.dataObject);


			/* ******************************************************* */
			/* Handle the overview form here directly.                 */
			/* ******************************************************* */
			this.overview_label1.setLabel("Overview Label1: " + 
				this.dataObject.getTName());

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

			// Once data is loaded, reset our dirty flag
			this.resetDirty();

		},

		/** This handles pulling data from GUI form fields and loading their values
		  * back into our data object.
		  */
		pullDataFromForm : function ()
		{
			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* pulling all fields that are registered in this object   */
			/* directly from our form and saving them to the dataObject*/
			/* ******************************************************* */
			${PACKAGE}.Statics.pullAllFields(this, this.dataObject);

			/* ******************************************************* */
			/* Any other type of data that needs to be loaded into the */
			/* form should be handled here.                            */
			/* ******************************************************* */

		},

		/** This handles verifying all of our form fields prior to saving the
		  * record back to the server.
		  */
		verifyFields : function()
		{
			// Use the built-in verification to do as much work for us as possible:
			if( ${PACKAGE}.Statics.verifyAllFields(this) === -1) return -1;

			// Then do any special verification required here:

			// If everything is ok, return 0
			return 0;
		},

		/** This handles the calls required to save our dataObject back to the
		  * server.
		  */
		doSaveToServer : function ( )
		{
			if(this.verifyFields() === -1){
				return; // Don't save an invalid object
			}
			this.pullDataFromForm();
			if(this.isNewObject === true){
				${PACKAGE}.Api.InsertObjectAPICallFIXME( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );

					// Updates our tab name, and the overview name
					this.resetTabName( this.dataObject.getTName() ); 

					// Remember to add the new guy to the tree:
					qx.core.Init.getApplication().addNewTreeItem( "Parent Tree Node",
						this.dataObject.getTName(), this.dataObject,
						"${PACKAGE}/icon/16x16/plain/control_panel2.png" );

				}, this);
			} else {
				${PACKAGE}.Api.UpdateObjectAPICallFIXME( this.dataObject, function(response){
					// pick up any new information here.
					this.getObjectDetails( response );
				}, this);
			}

		}


	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct : function() {
		this._disposeObjects(
			"tabview",
			"dataObject",
			"m_object_id"
		);
		${PACKAGE}.Statics.destroyExtraObjects( this );
	}

});
EOF

#############################################################################################
# Here's the first layout file that is referenced by the new class.  
#############################################################################################
echo "Creating file ${LAYOUT1} based on class: ${CLASSNAME} and package ${PACKAGE}"
cat >${LAYOUT1} <<EOF
<VerticalBoxLayout spacing="0" flex="1">
	<GroupBox legend="ObjectName Overview">
		<FieldArea columns="2" first="80" second="80">
			<DoubleField 
				varName1="varName1Field" label1="First Label:" type1="TextField"
				tooltip1="First field tooltip if required"
				verify1="true" verify1type="string" verify1min="1" verify1max="4"
				upper1="true" required1="true"
				varName2="varName2Field" label2="Second Label:" type2="TextField"
				tooltip2="Second field tooltip if required"
				verify2="true" verify2type="string" verify2min="1" verify2max="4"
				upper2="true" required2="true"
			/>
			<SpanField 
				varName1="varName3Field" label1="Third Label:" type1="TextField"
				tooltip1="This field goes all the way across both columns."
			/>
			<RadioGroup3 groupName="radioGroupVarName"
				varName1="firstRadioField" label1="First Radio Choice"
				varName2="secondRadioField" label2="Second Radio Choice"
				varName3="thirdRadioField" label3="Third Radio Choice"
			/>
			<SingleCheck varName1="singleCheckField" label1="Checkbox Option"
			/>
		</FieldArea>
		<Label text="Standalone Label" paddingTop="3"/>
		<TextArea varName="textAreaField" flex="3" wrap="true" allowGrowX="true" allowGrowY="true"/>
	</GroupBox>
	<GroupBox legend="Table Information Description" flex="1">
		<StandardTable varName="tableName" flex="1">
			<Column title="Column 1 Title" width="1*" minWidth="60" maxWidth="100"/>
			<Column title="Column 2 Title" width="1*" minWidth="60" maxWidth="100"/>
			<Column title="Column 3 Title" width="1*" minWidth="60" maxWidth="100"/>
			<Column title="Column 4 Title" width="1*" minWidth="60" maxWidth="100"/>
		</StandardTable>
	</GroupBox>
</VerticalBoxLayout>
EOF

#############################################################################################
# Here's the second layout file that is referenced by the new class.
#############################################################################################
echo "Creating file ${LAYOUT2} based on class: ${CLASSNAME} and package ${PACKAGE}"
cat >${LAYOUT2} <<EOF
<VerticalBoxLayout spacing="0" flex="1">
	<GroupBox legend="Second tab page description">
		<FieldArea columns="2" first="80" second="80">
			<DoubleField 
				varName1="varName4Field" label1="First Label:" type1="TextField"
				tooltip1="First field tooltip if required"
				verify1="true" verify1type="string" verify1min="1" verify1max="4"
				upper1="true" required1="true"
				varName2="varName5Field" label2="Second Label:" type2="TextField"
				tooltip2="Second field tooltip if required"
				verify2="true" verify2type="string" verify2min="1" verify2max="4"
				upper2="true" required2="true"
			/>
			<SpanField 
				varName1="varName6Field" label1="Third Label:" type1="TextField"
				tooltip1="This field goes all the way across both columns."
			/>
			<RadioGroup3 groupName="radioGroup2VarName"
				varName1="firstRadio2Field" label1="First Radio Choice"
				varName2="secondRadio2Field" label2="Second Radio Choice"
				varName3="thirdRadio2Field" label3="Third Radio Choice"
			/>
			<SingleCheck varName1="singleCheck2Field" label1="Checkbox Option"
			/>
		</FieldArea>
		<Label text="Standalone Label" paddingTop="3"/>
		<TextArea varName="textArea2Field" flex="3" wrap="true" allowGrowX="true" allowGrowY="true"/>
	</GroupBox>
	<GroupBox legend="Table Information Description" flex="1">
		<StandardTable varName="tableName2" flex="1">
			<Column title="Column 1 Title" width="1*" minWidth="60" maxWidth="100"/>
			<Column title="Column 2 Title" width="1*" minWidth="60" maxWidth="100"/>
			<Column title="Column 3 Title" width="1*" minWidth="60" maxWidth="100"/>
			<Column title="Column 4 Title" width="1*" minWidth="60" maxWidth="100"/>
		</StandardTable>
	</GroupBox>
</VerticalBoxLayout>
EOF

