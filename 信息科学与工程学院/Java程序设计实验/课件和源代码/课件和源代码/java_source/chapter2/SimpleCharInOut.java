import java.io.*;

public class SimpleCharInOut{
	public static void main(String[] args) 
	{
        char ch='\u0000';
		System.out.println("enter a character please:");
		try{
			ch=(char)System.in.read();
		}catch(IOException e){
			System.out.println("error");
		 }


		System.out.println("You have entered  a character:"+ch);
	}
}
