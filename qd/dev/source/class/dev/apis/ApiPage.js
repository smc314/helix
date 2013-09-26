/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */
/* ************************************************************************
************************************************************************ */
qx.Class.define("dev.apis.ApiPage", {
	extend: qx.ui.container.Composite,

	properties : {
	},

	construct: function (object_id) {
		this.base(arguments, new qx.ui.layout.VBox());
		this.doFormLayout();
	},

	events : {

	},

	members: {

		/** This is where subclasses will implement their form layout.
		*/
		doFormLayout: function () {

		}

	},

	/* **********************************************************************
	DESTRUCTOR
	********************************************************************** */
	destruct: function () {
		this._disposeObjects(

		);
		dev.Statics.destroyExtraObjects(this);

	}

});
