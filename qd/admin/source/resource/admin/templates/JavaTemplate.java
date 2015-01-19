{{!
	This is a mustache template that demonstrates using Java
	with a given sql statement
}}
/* *****************************************************************************
   This is a Java application generated to test the following SQL statement:

   {{{sqlText}}}

***************************************************************************** */

package SampleSqlCode;

import java.sql.*;

public class JDBCSample
{
	public static void main(String args[])
	{
		// FIXME: Update the Hort, Port, User, and password in this connection
		String connStr= "jdbc:ivory://FIXMEHost:FIXMEPort/LDS?user=FIXMEUser&password=FIXMEPass";
		String mySelectQuery = "{{{sqlText}}}";
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			// Load the driver class:
			Class.forName("com.ivory.jdbcDriver.IvoryDriver");

			// Create the connection:
			con = DriverManager.getConnection( connStr );

			// Create a Statement:
			ps = con.prepareStatement( mySelectQuery );

			// Execute our SQL:
			ps.execute();
			rs = ps.getResultSet();
			ResultSetMetaData rsmd = rs.getMetaData();
			int colCount = rsmd.getColumnCount();

			// Walk the result set:
			while(rs.next() ){
				for(int i = 1; i <= colCount; i++){
					System.out.print( rs.getString( i ) + " " );
				}
				System.out.println();
			}
		} catch (SQLException e) {
			System.err.println("SQL error " + e.getMessage());
			System.err.println("SQL code  " + e.getErrorCode());
			System.err.println("SQL state " + e.getSQLState());
			System.exit(1);		
		} catch (ClassNotFoundException e) {
			System.err.println("Driver error " + e.getMessage());
			System.exit(2);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if(rs != null){
				try {
					rs.close();
				} catch (SQLException e) {
					System.err.println("Close result set error " + e.getMessage());
				}
			}
			if(ps != null){
				try {
					ps.close();
				} catch (SQLException e) {
					System.err.println("Close prepared statement error " + e.getMessage());
				}
			}
			if(con != null){
				try { 
					con.close(); 
				} catch (SQLException e) {
					System.err.println("Close connection error " + e.getMessage());
				}
			}
		}
	}
}
