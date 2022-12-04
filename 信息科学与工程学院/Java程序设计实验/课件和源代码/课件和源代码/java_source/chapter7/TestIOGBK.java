
import java.io.*;
public class  TestIOGBK
{
	public static void main(String[] args) throws Exception
	{
		FileOutputStream output1=new FileOutputStream("d:\\save\\TestIOGBK1");
		FileOutputStream output2=new FileOutputStream("d:\\save\\TestIOGBK2");
		String str1="ecust华东理工大学";
		String str2="ecust华东理工大学";
		byte[] b1=str1.getBytes("unicode");
		byte[] b2=str2.getBytes("GBK");

		for(int i=0;i<b1.length;i++){
			 output1.write(b1[i]);
		} 
		for(int i=0;i<b2.length;i++){
			 output2.write(b2[i]);
		} 
        
        //--------------------------------------------------------------------------------
		File f1=new File("d:\\save\\TestIOGBK1");
		File f2=new File("d:\\save\\TestIOGBK2");
		int f1size=(int)f1.length();//文件字节大小
		int f2size=(int)f2.length();//文件字节大小
		
		FileInputStream input1=new FileInputStream("d:\\save\\TestIOGBK1");
		FileInputStream input2=new FileInputStream("d:\\save\\TestIOGBK2");
		
		byte[] b11=new byte[f1size];
		byte[] b22=new byte[f2size];

		int c=-1;
		int i=0;
		while( true){

           c= input1.read();
		   if(c==-1) break;  //代表读到文件末尾了。
		   b11[i]=(byte)c; //int -> byte 
		   i++;
		}


        c=-1;
		i=0;
		while( true){ 
           c= input2.read();
		   if(c==-1) break;  //代表读到文件末尾了。 
		   b22[i]=(byte)c;
		   i++;
		}

		String str11=new String(b11,"unicode");
        String str22=new String(b22,"GBK");
		String str33=new String(b11,"GBK"); // unicode写，然后以GBK读,乱码
		String str44=new String(b22,"unicode");// GBK写，然后以unicode读,乱码

		System.out.println(str11);
		System.out.println(str22);
		System.out.println(str33);
		System.out.println(str44);


		 
	}
}
