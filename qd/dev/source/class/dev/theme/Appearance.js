/* ************************************************************************

   Copyright:

   License:

   Authors:

************************************************************************ */
/* ************************************************************************
#asset(dev/icon/16x16/plain/error.png)
************************************************************************ */

/* ************************************************************************
************************************************************************ */
qx.Theme.define("dev.theme.Appearance",
{
	extend : qx.theme.simple.Appearance,
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
					icon : "dev/icon/16x16/plain/error.png"
				};
			}
		}
	}
});
