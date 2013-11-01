/* ************************************************************************

Copyright: 2013 Hericus Software, LLC

License: The MIT License (MIT)

Authors: Steven M. Cherry

************************************************************************ */


/**
 *    This mixin provides methods that allow manipulation of editor tabs
 *    to make writing tests easier.
 */
qx.Class.define("dev.test.SimpleTestUtil", {

	extend: qx.core.Object,

	construct: function(test) {
		this.base(arguments);

	    this._test         = test;

		Array.max = function( array ) {
		    return Math.max.apply( Math, array );
		};

		Array.min = function( array ) {
		    return Math.min.apply( Math, array );
		};

		// Array Remove - By John Resig (MIT Licensed)
		Array.prototype.remove = function(from, to) {

		  var rest    = this.slice((to || from) + 1 || this.length);
		  this.length = from < 0 ? this.length + from : from;

		  return this.push.apply(this, rest);
		};

		// Array Remove - By John Resig (MIT Licensed)
		// Array.remove = function(array, from, to) {
		//   var rest = array.slice((to || from) + 1 || array.length);
		//   array.length = from < 0 ? array.length + from : from;
		//   return array.push.apply(array, rest);
		// };
	},


	members: {

		_test: null,


		compareArrays: function( expected, actual ) {

			console.log( "expected: " + expected );
			console.log( "actual: " + actual );

			this.compareArraySizes( expected, actual );
			this.compareArrayContents( expected, actual );
			this.compareExtraInArrays( expected, actual );
		},


		compareExtraInArrays: function( left, right ) {

			if ( left.length === right.length ) {

				return;
			}

			var minSizeOfArrays = Array.min( [left.length, right.length] );
			var maxSizeOfArrays = Array.max( [left.length, right.length] );
			var more			= null;

			if ( left.length > right.length ) {
				more = left;
			}
			else {
				more = right;
			}

			for (var i = minSizeOfArrays, l = maxSizeOfArrays; i < l; i++) {

				// console.log( "Found extra " + i + " = " + more[i] );
				this._test.assertEquals( more[i], null, "Found extra " + i + " = " + more[i] );
			}
		},


		compareArraySizes: function( expected, actual ) {

			this._test.assertEquals( expected.length,
									 actual.length,
							   		 "Should have " + expected.length + ", found: " + actual.length );
		},


		compareArrayContents: function( expected, actual ) {

			var minSizeOfArrays = Array.min( [expected.length, actual.length] );

			for (var i = 0, l = minSizeOfArrays; i < l; i++) {

				this._test.assertEquals( expected[i],
								   		 actual[i],
								   		 "item[" + i + "] should be " + expected[i] );
			}
		},


		copyMap: function( oldMap, newMap ) {

			//this.debug( "oldMap" + JSON.stringify( oldMap ) );
			//this.debug( "newMap" + JSON.stringify( newMap ) );

			for ( var i in oldMap ) {
				newMap[i] = oldMap[i];
			}

			//this.debug( "newMap" + JSON.stringify( newMap ) );
		},


		/**
		 *    tests to see if the given string starts with the given value.
		 */
		startsWith: function( source, match ) {

			if ( source.slice( 0, match.length ) === match ) {

				this.debug( "MATCH!" );
				return true;
			}

			return false;
		},


		/**
		 *     Try to pretty print an object.
		 */
		pprint: function(obj) {

			// Setup Arrays
			var sortedKeys = new Array();
			var sortedObj = {};
			var str = '';

			// Separate keys and sort them
			for (var i in obj){
				sortedKeys.push(i);
			}
			sortedKeys.sort();
			//console.log( sortedKeys );

			for(var p in sortedKeys) {
				var property_name = sortedKeys[p];
				var property_value = obj[property_name];
				var property_type = typeof obj[property_name];

				if ( property_name == 'content' || property_name == 'frameContent' ) {

					str += property_name + ':<' + property_type +  '>: {lots_o_stuff}\n';
					continue;
				}
				if ( typeof property_value == 'string' && property_value.lastIndexOf( 'function', 0 ) == 0 ) {

					str += property_name + ':<' + property_type +  '>: {function}\n';
					continue;
				}

				if (typeof property_value == 'string') {
					str += property_name + ':<string>: ' + property_value + ';\n';
				} else {
					str += property_name + ':<' + property_type +  '>: {' + print(property_value) + '}\n';
					//str += property_name + ': {\n' + print(property_name) + '}';
				}
					//console.log( str );
			}

			return str;
		}
	},

	statics: { },

	destruct: function() { }
});
