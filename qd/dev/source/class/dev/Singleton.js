/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
qx.Class.define("dev.Singleton", {
	type: "singleton",
	extend: qx.core.Object,

	construct: function () {
		this.base(arguments);

	},

	properties: {
		userProperties: { init: {} },
		systemProperties: { init: {} },
		newMenus: { init: {} },
		viewMenus: { init: {} },
		serverSettingsInternal: { init: [] },
		buildServersXML: { init: null }
	},

	members: {

		/** This is a wrapper method around our internal server settings.
		* If we find that they haven't yet been pulled from the server, we'll
		* do that, and populate our internal list.  If they've already been
		* populated, we'll return them directly.
		*
		* @return Array<dev.admin.sqldo.Setting>
		*/
		getServerSettings: function () {
			if (this.getServerSettingsInternal().length === 0) {
				this.refreshServerSettings();
			}
			return this.getServerSettingsInternal();
		},

		/** Use this method to signal us that our server settings list needs to
		* be refreshed from the server.
		*/
		refreshServerSettings: function () {
			// retrieve the settings from the Server:
			dev.Api.selectAllSettings(function (response) {
				var ret = dev.sqldo.Setting.readElementChildren(response);
				var our = [];
				for (var i = 0, l = ret.length; i < l; i++) {
					var obj = ret[i];
					our[obj.getName()] = obj.getValue();
				}
				this.setServerSettingsInternal(our);
			}, this);
		},

		getSystemProperty: function (whichProp) {
			return this.getSystemProperties[whichProp];
		}

	},

	statics: {

		/** Constant string used to look up a value from systemProperties */
		AreWeHomeBase: "AreWeHomeBase"

	},

	destruct: function () {

	}
});
