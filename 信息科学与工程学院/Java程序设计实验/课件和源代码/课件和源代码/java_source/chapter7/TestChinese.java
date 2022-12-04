import java.io.*;
public class TestChinese{
	public static void main(String[] args) throws Exception{  
	  String ecustString="ecust华东理工大学";
	  byte[] ecustByte =ecustString.getBytes(); // Unicode转换成GBK编码
	  byte[] ecustByte2 =ecustString.getBytes("GBK");// Unicode转换成GBK编码
	  byte[] ecustByte3 =ecustString.getBytes("Unicode"); //Unicode转换成Unicode编码
	   
	  try{
		File file=new File("d:/save/TestChinese1.txt");
		File file2=new File("d:/save/TestChinese2.txt");
		File file3=new File("d:/save/TestChinese3.txt");
		file.createNewFile();
		file2.createNewFile();
		file3.createNewFile();
		FileOutputStream outputFile=new FileOutputStream(file);
		FileOutputStream outputFile2=new FileOutputStream(file2);
		FileOutputStream outputFile3=new FileOutputStream(file3); 
		  
		   
		  System.out.println("------------------ ecust华东理工大学 -getBytes()--------------" );	
           for(int i=0;i<ecustByte.length;i++){
            System.out.print(ecustByte[i]);	System.out.print(" ");	
			outputFile.write(ecustByte[i]); //写汉字的低字节 无乱码
		  }
		  System.out.println( );

		  System.out.println("------------------ ecust华东理工大学 -getBytes(GBK)--------------" );	
           for(int i=0;i<ecustByte2.length;i++){
            System.out.print(ecustByte2[i]);	System.out.print(" ");	
			outputFile2.write(ecustByte2[i]); //写汉字的低字节 无乱码
		  }
		  System.out.println( );

		  System.out.println("------------------ ecust华东理工大学 -getBytes(Unicode)--------------" );	
           for(int i=0;i<ecustByte3.length;i++){
            System.out.print(ecustByte3[i]);	System.out.print(" ");	
			outputFile3.write(ecustByte3[i]);  
		  }
		  System.out.println( );

		   
           
		 outputFile.close();
		 outputFile2.close();
		 outputFile3.close();
		 
	     } catch(IOException e){System.out.println(e);		         }	    
		 }
	 }