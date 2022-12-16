 
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Calendar;

public class  TestIo2{ 
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
	public static void main(String[] args)  throws Exception{ 
		 
    	 TestIo2.createFile();
		  
	}
}
