{{!
	This is a mustache template that demonstrates using Ole-DD
	with a given sql statement
}}
/* *****************************************************************************
   This is an C# application generated to test the following SQL statement:

   {{{sqlText}}}

***************************************************************************** */

using System;
using System.Collections.Generic;
using System.Text;
using System.Data.OleDb;

namespace SampleSqlCode
{
	class Program
	{
		static void Main(string[] args)
		{
			// FIXME: Update the DSN, User, and password in this connection
			string connStr= "Provider=VSQLOLE;DSN=FIXME;UID=FIXME;PWD=FIXME";
			string mySelectQuery = "{{{sqlText}}}";

			OleDbConnection myConnection = new OleDbConnection(connStr);
			OleDbCommand myCommand = new OleDbCommand(mySelectQuery, 
				myConnection);

			try {
				myConnection.Open();
			} catch (Exception ex){
				Console.WriteLine(ex.Message);
				return; // if we can't open the conn, bail out.
			}

			OleDbDataReader myReader = myCommand.ExecuteReader();

			try{
				while(myReader.Read() ){
					for(int i = 0; i < myReader.FieldCount; i++){
						Console.Write(
							myReader.GetString( i + 1 ) + " "
						);
					}
					Console.WriteLine();
				}
			} catch (Exception ex){
				Console.WriteLine( ex.Message );
			} finally {
				myReader.Close();
				myConnection.Close();
			}
		}
	}
}
