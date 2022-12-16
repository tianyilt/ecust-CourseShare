import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.RandomAccessFile;


public class TestIoStream 
{
	public static void main(String[] args) throws Exception
	{ 
		/*
		File file=new File("d:/aa.txt");
		FileOutputStream input=new FileOutputStream(file);
	 
       // input.skip(file.length());
		for(int i=1;i<=10;i++){
           input.write(97+i);
		}
		*/

        RandomAccessFile random=new RandomAccessFile("d:/aa.txt","rw");
        long k=random.length();
		random.seek(k);//移动到文件末尾
         for(int i=0;i<10;i++){
           random.writeByte(97+i);
		} 
		
		System.out.println("Hello World!");
	}
}
