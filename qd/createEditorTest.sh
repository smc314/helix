#!/bin/bash
#############################################################################################
# This script makes it easy to start a new logic skeleton.  We'll create the header and body
# files with everything required.  Just pass us the new Class name.

CLASSNAME=$1
PACKAGE=$2
JAVASCRIPT=${CLASSNAME}.js
TMP=`pwd`
FOLDER=${TMP##*/}
THISYEAR=`date +%Y`

#############################################################################################
# Here's the new class file that is based on an ObjectEdit standard.
#############################################################################################
echo "Creating editor test file ${JAVASCRIPT} based on class: ${CLASSNAME} and package ${PACKAGE}"
cat >${JAVASCRIPT} <<EOF
/* ************************************************************************

   Copyright: ${THISYEAR} Your Company, Inc.

   Authors: You and your developers

************************************************************************ */

/**
 * This class demonstrates how to define unit tests for your application.
 *
 * Execute <code>generate.py test</code> to generate a testrunner application
 * and open it from <tt>test/index.html</tt>
 *
 * The methods that contain the tests are instance methods with a
 * <code>test</code> prefix. You can create an arbitrary number of test
 * classes like this one. They can be organized in a regular class hierarchy,
 * i.e. using deeper namespaces and a corresponding file structure within the
 * <tt>test</tt> folder.
 */
qx.Class.define("${PACKAGE}.test.${FOLDER}.${CLASSNAME}",
{
	extend : ${PACKAGE}.test.HubEditorTest,

	construct : function() {
		this.base(arguments);
	},

	members :
	{
		/** Which tools/new menu should be invoked to create a new editor.
		  */
		_toolsNew: "Attachment Definition",

		/** Where are our new items saved in the tree, which parent node:
		  */
		_treeNode: "Attachment Def",

		/** Defines our tab name after a save
		  */
		_tabNameSaved: "SMC1ATTD",

		/** This defines our test data, which consists of an array of fields.
		  */
		_testData: [
			{name: "DefNameField", value: "SMC6ATTD", defaultValue: "NEW1" },
			{name: "DescriptionField", value: "New Attachment Definition Description"},
			{name: "useTCPField", value: "true"},
			{name: "GroupField", value: "Group6"},
			{name: "HostNameField", value: "Host6", valueAfterSave: "HOST6", valueAfterReload: "HOST6"},
			{name: "PortField", value: "3141"},
			{name: "TimeoutField", value: "200"},
			{name: "ServiceNameField", value: "Service6", valueAfterSave: "SERVICE6", valueAfterReload: "SERVICE6"},
			{name: "ConnectionTypeField", value: "ODBC"},
			{name: "UserIDField", value: "User6", valueAfterSave: "USER6", valueAfterReload: "USER6"},
			{name: "PassField", value: "Pass6"}

		],

		/*
		---------------------------------------------------------------------------
		  TESTS

		  test0010 through test00X0 are already defined in our parent class.
		  you can override any of those here that you like, or you can add
		  more to the list of tests to execute specific tests unique to this
		  editor.

		  Begin your tests with number 0500 to ensure no numbering conflicts.
		---------------------------------------------------------------------------
		*/

		/**
		  * Start your own tests here
		  */
		test0500_ : function() {
		}


	}

});
EOF
