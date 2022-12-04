 
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Calendar; 

public class  TestIo4{ 
	//按照16进制方式显示str的encoding编码格式
	public static void Encode(String encoding,String str)throws Exception { 
        byte[] bytes=str.getBytes(encoding);//GBK为Windows系统默认保存文本文件的编码格式
		System.out.print(""+str+" "+encoding+": ");
		for(int i=0;i<bytes.length;i++){
			System.out.printf(" %x",(bytes[i]));
		} 
		System.out.println( );
	} 
   
	public static void main(String[] args)  throws Exception	{ 
		 //以下3条代码可以看出Unicode编码是两个字节表示字符，而GBK编码是一个字节表示字符，两个字节表示汉字
		
		 TestIo.Encode("Unicode","abc");
		 TestIo.Encode("Ascii","abc");
		 TestIo.Encode("GBK","abc"); 
         //以下3条代码可以看出Unicode编码是两个字节表示英文字符和汉字
		 //而GBK编码是一个字节表示英文字符，两个字节表示汉字 
		 TestIo.Encode("Unicode","abc华东理工大学ecust");
		 TestIo.Encode("UTF-16BE","abc华东理工大学ecust"); //可以看出Unicode编码实际是采用UTF-16BE编码格式+BOM头（fe ff)
         TestIo.Encode("UTF-8","abc华东理工大学ecust"); 
		 TestIo.Encode("GBK","abc华东理工大学ecust");
		 
		  
	}
} 