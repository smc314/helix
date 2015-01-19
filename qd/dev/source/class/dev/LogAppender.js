/* ************************************************************************

   Copyright: 2013 Hericus Software LLC, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

************************************************************************ */

/* ************************************************************************

#require(qx.log.appender.Util)

************************************************************************ */

/**
 * Processes the incoming log entry and sends it to the server for storage.
 */
qx.Class.define("dev.LogAppender",
{
	/*
	*****************************************************************************
	  STATICS
	*****************************************************************************
	*/

	statics : {
		/**
		  * Processes a single log entry
		  *
		  * @signature function(entry)
		  * @param entry {Map} The entry to process
		  * @return {void}
		  */
		process : function(entry){
			var logObj = new dev.sqldo.LogObj;
			logObj.setAppName( "Helix User Interface" ); // hard code this
			if( entry.level === "debug" ){
				logObj.setChannel( 4 );
			} else if(entry.level === "info" ){
				logObj.setChannel( 3 );
			} else if(entry.level === "warn" ){
				logObj.setChannel( 2 );
			} else if(entry.level === "error" ){
				logObj.setChannel( 1 );
			} else {
				logObj.setChannel( 4 ); // default to debug
			}

			logObj.setMsg( qx.log.appender.Util.toText( entry ) );
			logObj.setFile( "dev" );
			logObj.setMachineName( "HelixGui" );
			logObj.setTid( 1234567 );
			var d = new Date();
			logObj.setTimestamp_a( Math.floor( d.getTime() / 1000) );
			logObj.setTimestamp_b( d.getTime() % 1000 );

			dev.Api.SaveLogMsg( logObj );
		}
	},

	/*
	*****************************************************************************
	  DEFER
	*****************************************************************************
	*/

	defer : function(statics) {
		qx.log.Logger.register(statics);
	}
});
