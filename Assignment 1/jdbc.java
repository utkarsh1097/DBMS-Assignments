/*Reference from https://www.tutorialspoint.com/postgresql/postgresql_java.htm */

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.io.*;

public class jdbc
{
	public static void main(String args[])
	{
		try
        {
			long start = System.currentTimeMillis();
			BufferedReader BR = new BufferedReader(new FileReader("cases.txt"));
			String sqlcommand;
			Connection c = null;
			Statement stmt = null;
			try
			{
				Class.forName("org.postgresql.Driver");
				c = DriverManager.getConnection("jdbc:postgresql://localhost:5432/test","postgres", "SanUtki123");
				c.setAutoCommit(false);
				stmt = c.createStatement();
				//starts reading file
				while((sqlcommand = BR.readLine())!=null)
				{
					stmt.executeUpdate(sqlcommand);
				}
				stmt.close();
				c.commit();
				c.close();
			} 
			catch(Exception e) 
			{
				System.err.println( e.getClass().getName()+": "+ e.getMessage() );
				System.exit(0);
			}
			BR.close();
			long end = System.currentTimeMillis();
			System.out.println(end-start);
		}
		catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e) 
        {
            e.printStackTrace();
        }
	}
}