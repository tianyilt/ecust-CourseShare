import java.io.*;
public class TestFileInputStream{
    public static void main(String[] args){  
      byte[] info=new byte[6];  
      try{ File file=new File("d:/save/TestOutput.txt");	 
	    FileInputStream inputFile=new FileInputStream(file);
              inputFile.read(info); 
	    for(int i=0;i<info.length;i++){
		System.out.println(info[i]);
	     }
	      inputFile.close();
	   } catch(IOException e){
		System.out.println(e);
	   }	    
     } }