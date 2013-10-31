/* ************************************************************************

   Copyright:

   License:

   Authors:

************************************************************************ */

/* ************************************************************************
************************************************************************ */
qx.Theme.define("dev.theme.Appearance",
{
	extend : qx.theme.modern.Appearance,
	appearances :
	{
		"tabview" : {
			style : function(states) {
				return {
					contentPadding : 3
				}
			}
		},
		"tabview-page/button/close-button" :
		{
			alias : "atom",
			style : function(states) {
				return {
					icon : "dash/icon/16x16/plain/error.png"
				};
			}
		}
	}
});
