/* ************************************************************************

   Copyright:

   License:

   Authors:

************************************************************************ */
/* ************************************************************************
#asset(admin/icon/16x16/plain/error.png)
************************************************************************ */

qx.Theme.define("admin.theme.Appearance",
{
	extend : qx.theme.simple.Appearance,

	appearances :
	{
		"tabview" :
		{
			style : function(states)
			{
				return {
					contentPadding : 8
				};
			}
		},

		"tabview-page/button/close-button" :
		{
			alias : "atom",
			style : function(states)
			{
				return {
					icon : "admin/icon/16x16/plain/error.png"
				};
			}
		}
	}
});
