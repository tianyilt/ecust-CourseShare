
import java.io.*;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Calendar;

public class  TestIo3{ 

	//将d:/save/a/ecust.txt文件中的字符读取到unicodeStr变量中 
	public static void readFile() throws Exception{  
        String file="d:/save/a/ecust.txt";
		String unicodeStr= null;//字符串是以Unicode编码格式存在内存中的。（UTF-16 的 UTF-16BE 格式)
		byte[] unicodeBytes=null;//保存读取文件的字节数据。（GBK为Windows系统默认保存文本文件的编码格式）
		File ecust=new File(file); 
		int filesize=(int)ecust.length();//文件字节大小
        unicodeBytes=new byte[filesize];

		
        FileInputStream inputStream=new FileInputStream(ecust);
		int i=0;
		int content=0;//保存每次读取文件的一个字节数据
		while((content=inputStream.read())!=-1){
  
           unicodeBytes[i]=(byte)content;//将读取到的字节数据保存到数组中
		   i++;

		}

		unicodeStr=new String(unicodeBytes,"GBK");//按照"GBK"编码格式转换unicodeBytes字节数组中的数据至String
		// public String(byte bytes[], Charset charset)
		System.out.println("["+unicodeStr+"]");
		inputStream.close();

	}


    //将d:/save/a/ecust.txt文件复制到d:/save/b/ecust.txt中 
	public static void copyFile() throws Exception {  
        String sourcefile="d:/save/a/ecust.txt"; 
		String destinationfile="d:/save/b/ecust.txt"; 
		 
		File source=new File(sourcefile);
		File destination=new File(destinationfile);
		destination.createNewFile();
        FileInputStream sourceStream=new FileInputStream(source);
		FileOutputStream destinationStream=new FileOutputStream(destination);
		int content=0;
		while((content=sourceStream.read())!=-1){

           destinationStream.write(content);

		}
		sourceStream.close();
		destinationStream.close(); 
	}

 
	public static void main(String[] args)  throws Exception
	{ 
		 
		 TestIo.copyFile(); 
		 TestIo.readFile();
		 
	}
}
