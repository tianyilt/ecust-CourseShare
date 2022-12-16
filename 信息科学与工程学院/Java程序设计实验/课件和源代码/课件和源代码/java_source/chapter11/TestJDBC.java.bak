
import java.sql.*;
class  TestJDBC
{

	public static void main(String[] args) 
	{   String driver="com.microsoft.jdbc.sqlserver.SQLServerDriver";
	    String url="jdbc:microsoft:sqlserver://localhost:1433;DatabaseName=studentDB";
		String user="tom";
		String password="11111111";
		String sql="select * from student"; 

		Connection conn;
		Statement stmt;
		ResultSet rs;

		String myId;
		String myName;
		Date myBirthday;
		int myAge;
		String mySex;
		

		try{
			Class.forName(driver);
			 
			conn=DriverManager.getConnection(url, user,password);
		 
			stmt=conn.createStatement();			 
			rs=stmt.executeQuery(sql);

			while(rs.next()){
				myId=rs.getString("id");
				myName=rs.getString("name");
				myAge=rs.getInt("age");
				 myBirthday=rs.getDate("birthday");
                mySex=rs.getString("sex");
                System.out.println( myId+" "+myName+" "+myAge+" "+myBirthday+" "+mySex);
			}

			stmt.close();
			conn.close();
       

		}catch( Exception e){
			System.out.println("error  in Exception");
			  System.out.println(e.getMessage());
		}
	 
	}
}
