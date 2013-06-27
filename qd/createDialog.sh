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
THISYEAR=`date +%Y`
FOLDER=${TMP##*/}

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

/** This class defines a normal dialog window that extends the OKCancelDialog and
  * presents the user with a nice dialog layout.
  */
qx.Class.define("${PACKAGE}.${FOLDER}.${CLASSNAME}", {
	extend: ${PACKAGE}.dialog.OKCancelDialog,

	construct : function ( title ) {
		this.dynamicLayouts = [];
		this.dynamicLayouts.push({name: "${CLASSNAME}.MainPage.xml", doc:null});

		this.base(arguments, title);
	},

	members : {

		/** This method is used to allow child classes to override the size of this
		  * dialog box.
		  */
		doSetSpace : function() {
			this.setHeight(600);
			this.setWidth(400);
		},

		/** This method allows you to set the focus to whichever field you want when
		  * this window becomes active.  This will be called every time this window 
		  * becomes the active window, which will only happen once for a modal window.
		  */
		setFocusFirst : function() {
			// Something like this:
			// this.idField.selectAllText();
			// this.idField.focus();
		},

		/** This is where subclasses will implement their form layout.
		  */
		doFormLayout : function( layout ) {
			${PACKAGE}.LayoutEngine.renderLayout( this,
				this.getDynamicLayout("${CLASSNAME}.MainPage.xml"),
				layout );

			// Any other special layout goes here.

			/* ******************************************************* */
			/* For simple form fields this will handle automatically   */
			/* loading all fields that are registered in this object   */
			/* directly from our data object.                          */
			/* ******************************************************* */
			${PACKAGE}.Statics.loadAllFields(this, this.dataObject);

			this.addOkEventListener( "execute", this.pullDataFromForm, this );
		},

		/** This handles pulling data from GUI form fields and loading their values
		  * back into our data object.
		  */
		pullDataFromForm : function ()
		{
			// First verify everything that is in the form fields
			if(this.verifyFields() === -1){
				return;
			}

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

		verifyFields : function()
		{
			// Use the built-in verification to do as much work for us as possible:
			if( ${PACKAGE}.Statics.verifyAllFields(this) === -1) return -1;

			// Then do any special verification required here:

			// If everything is ok, return 0
			return 0;
		}

	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct : function() {
		this._disposeObjects(
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
