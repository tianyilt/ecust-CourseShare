import java.io.*;
class  TestChineseWords
{
	public static void main(String[] args) throws Exception
	{
		String str1="华理"; 
		String str2="a华理b";
		String str3="a华b理1";
		String str4="cdef1234";

		System.out.println(str1.length());
		System.out.println(str2.length());
		System.out.println(str3.length());
		System.out.println(str4.length());

		 

		 byte[] b1=str1.getBytes("GBK");//把Unicode编码表示的str1按照GBK编码转换
		 byte[] b2=str2.getBytes();//把Unicode编码表示的str2按照Windows系统默认的编码（GBK）转换
		 byte[] b3=str3.getBytes("GBK"); 
		 byte[] b4=str4.getBytes("GBK");
		 
         byte[] b11=str1.getBytes("utf-8");//把Unicode编码表示的str1按照GBK编码转换
		
		 //str1的GBK编码
		 System.out.print (str1+" GBK编码:   ");
		 for(int i=0;i<b1.length;i++){ 
			//System.out.print( "  "+b1[i]);
			System.out.printf( " %x",b1[i]);//以16进制输出
		 } 
		 System.out.println();
		 //System.out.println(b1.length);


		 //str1的utf-8编码
		 for(int i=0;i<b11.length;i++){ 
			//System.out.print( "  %x"+b11[i]);
			//System.out.printf( " %x",b11[i]);//以16进制输出
		 }
		 System.out.println();

         //str2的GBK编码
		 System.out.print (str2+" GBK编码: ");
		 for(int i=0;i<b2.length;i++){ 
			//System.out.print(  " "+ b2[i]);
			System.out.printf( " %x",b2[i]);//以16进制输出
		 }
		 
		 System.out.println();
		// System.out.println(b2.length);

          //str3的GBK编码
		  System.out.print (str3+" GBK编码:");
		 for(int i=0;i<b3.length;i++){ 
			//System.out.print(  " "+ b3[i]);
			System.out.printf( " %x",b3[i]);//以16进制输出
		 }
		 
		 System.out.println();
		// System.out.println(b3.length);


          //str4的GBK编码
		 System.out.print (str4+"GBK编码:");
		 for(int i=0;i<b4.length;i++){ 
			//System.out.print( " "+  b4[i]);
			System.out.printf( " %x",b4[i]);//以16进制输出
		 }
		 
		 System.out.println();
		 //System.out.println(b4.length);

         int k='华'; 
		 String s=Integer.toHexString(k);//10进制转换成16进制
		 System.out.println("华  int: "+k+"   unicode: "+s );
		 System.out.println('\u534e' );
		 System.out.printf("%x",k );
		 System.out.println(  ); 

		 int unicode1=0x53;  //'华'的unicode编码的高字节
		 int unicode2=0x4e;  //'华'的unicode编码的低字节
         System.out.println(""+unicode1+" "+unicode2 ); 


		 int a='a'; 
		 String s2=Integer.toHexString(a);//10进制转换成16进制
		 System.out.println("a  int: "+a+"   unicode: "+s2 );
		// System.out.println('\u534e' );
		 System.out.printf("%x",a );
		 System.out.println(  ); 
		  

         
          FileOutputStream file=new FileOutputStream("chinese.txt");
		
		 file.write(unicode1); //'华'的unicode编码的高字节
		 file.write(unicode2); //'华'的unicode编码的低字节

		 int c1=0xbb;//'华'的GBK编码的高字节
		 int c2=0xaa;//'华'的GBK编码的低字节 
		 file.write(c1);//'华'的GBK编码的高字节
		 file.write(c2);//'华'的GBK编码的低字节 

		  
		 for(int i=0;i<b1.length;i++){ 
            file.write(b1[i]);
			System.out.print  (b1[i]);
			System.out.print  (" ");
		 }
		 System.out.println(  ); 


		 for(int i=0;i<b2.length;i++){
            System.out.print  (b2[i]);
			System.out.print  (" ");
		 }
		 System.out.println(  ); 


		 for(int i=0;i<b3.length;i++){
            System.out.print  (b3[i]);
			System.out.print  (" ");
		 }
		 System.out.println(  ); 

		 
	}
}
