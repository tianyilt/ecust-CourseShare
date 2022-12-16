import java.io.*;
public class TestSimpleChineseFileOutputStream{
	public static void main(String[] args) throws Exception{  
	  byte[] info={97,98,99,100,101,102};  //字符'a'的ASCII值为97,依此类推;
	  char[] c={'x','y','z'}; 
	  char[]  ecustChar ={'华','东','理','工','大','学'}; //unicode编码
	   
	  try{
		File file1=new File("d:/save");
		file1.mkdir();
		File file=new File("d:/save/TestSimpleChineseFileOutputStream.txt");
		file.createNewFile();
		FileOutputStream outputFile=new FileOutputStream(file);
		
		System.out.println("----------------{97,98,99,100,101,102}--------------" );
		for(int i=0;i<info.length;i++){
		    System.out.print(info[i]);	System.out.print(" ");	
			outputFile.write(info[i]);
		  }
		 System.out.println( );


         System.out.println("------------------{'x','y','z'}---------------" );		
		 for(int i=0;i<c.length;i++){
			 System.out.print(c[i]);	System.out.print(" ");	
			//outputFile.write( c[i]); //写低字节 正确
			//outputFile.write((byte)c[i]); //   正确
			outputFile.write((int)c[i]); //写低字节  正确
		  }
		  System.out.println( );


          System.out.println("-----------------{'华','东','理','工','大','学'}---------------" );		
		  for(int i=0;i<ecustChar.length;i++){
			   	
            System.out.print(ecustChar[i]);	System.out.print(" ");	
			outputFile.write(ecustChar[i]); //写汉字的低字节 乱码
		  }
		  System.out.println( );  
           
		 outputFile.close();
	     } catch(IOException e){System.out.println(e);		         }	    
		 }
	 }