import java.io.*;

public class ApplicationLineInOut{
	public static void main(String[] args) 
	{
        String string="";
		System.out.println("enter a string please:");
		try{			
			BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
			string=br.readLine();			 
		}catch(IOException e){
			System.out.println("error");
		 }
		System.out.println("You have entered  a string:"+string);
	}
}
