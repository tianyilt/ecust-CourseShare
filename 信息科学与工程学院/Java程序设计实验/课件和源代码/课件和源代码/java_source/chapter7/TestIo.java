
import java.io.*;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Calendar;

public class  TestIo{
    
	//按照16进制方式显示str的encoding编码格式
	public static void Encode(String encoding,String str)throws Exception { 
        byte[] bytes=str.getBytes(encoding);//GBK为Windows系统默认保存文本文件的编码格式
		System.out.print(""+str+" "+encoding+": ");
		for(int i=0;i<bytes.length;i++){
			System.out.printf(" %x",(bytes[i]));
		} 
		System.out.println( );
	}
	//在d:/save目录下创建a,b子目录
	//在d:/save/a目录下创建c子目录
	public static void createDirectory() throws Exception{  
		String directory="d:/save";
		String aDirectory="d:/save/a";
		String bDirectory="d:/save/b";
		String cDirectory="d:/save/a/c";
		File a=new File(aDirectory);
		File b=new File(bDirectory);
		File c=new File(cDirectory);
		a.mkdir();
		b.mkdir();
		c.mkdir(); 
	}


    //将字符串unicodeStr＝"华东理工大学ecust"保存到d:/save/a/ecust.txt文件中 
	public static void createFile() throws Exception{  
         String file="d:/save/a/ecust.txt";
		String unicodeStr="华东理工大学ecust";//字符串是以Unicode编码格式存在内存中的。（UTF-16 的 UTF-16BE 格式)
		byte[] unicodeBytes=unicodeStr.getBytes("GBK");//GBK为Windows系统默认保存文本文件的编码格式
		File ecust=new File(file);
		ecust.createNewFile();
        FileOutputStream outputStream=new FileOutputStream(ecust);
		for(int i=0;i<unicodeBytes.length;i++){
			outputStream.write(unicodeBytes[i]);
		}
		outputStream.close();

	}

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


  //递归方式显示directory目录下所有的文件和子目录
	public static void dir(int level ,String directory){ 
        //directory:文件的绝对路径+文件名
	    //level:目录的层次

         File file=new File(directory);
		 File file2=null;
		 String[] list=file.list();
		 for(int i=0;i<list.length;i++){ 
		   file2=new File(directory+"/"+list[i]); 
		   if(file2.isFile()){ 
              //以下代码控制"-",以便显示更美观
			 String filename="";
			 for(int t=1;t<=level;t++){
				 filename+="-";
			 }
			 filename+=list[i] ;
			  System.out.println( "文件名:"+filename );  
		   }
		   if(file2.isDirectory()){
                //System.out.println("时间："+cd.getTime()+"目录名:"+list[i]); 
				String directory2="";
			    for(int t=1;t<=level;t++){
				     directory2+="-";
			    }
			    directory2+=list[i] ; 
				System.out.println( "目录名:"+directory2); 
			  
			    dir(level+1,directory +"/"+list[i]);  //递归 
			} 
		 } 
		 return ;

	}
	public static void main(String[] args)  throws Exception
	{ 
		 //以下3条代码可以看出Unicode编码是两个字节表示字符，而GBK编码是一个字节表示字符，两个字节表示汉字
		
		 TestIo.Encode("Unicode","abc");
		 TestIo.Encode("Ascii","abc");
		 TestIo.Encode("GBK","abc");


         //以下3条代码可以看出Unicode编码是两个字节表示字符,汉字
		 //而GBK编码是一个字节表示字符，两个字节表示汉字 
		 TestIo.Encode("Unicode","abc华东理工大学ecust");
		 TestIo.Encode("UTF-16BE","abc华东理工大学ecust"); //可以看出Unicode编码实际是采用UTF-16BE编码格式+BOM头（fe ff)
         TestIo.Encode("UTF-8","abc华东理工大学ecust"); 
		 TestIo.Encode("GBK","abc华东理工大学ecust");
		 
		 TestIo.createDirectory();
		 TestIo.createFile();
		 TestIo.copyFile(); 
		 TestIo.readFile();
		 TestIo.dir(1,"d:/save/a"); 
	}
}
