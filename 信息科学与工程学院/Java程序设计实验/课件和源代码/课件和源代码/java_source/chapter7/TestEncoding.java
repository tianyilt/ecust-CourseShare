public class TestEncoding 
{
   public static void prn1() throws Exception{
        System.out.println("------------prn1-------------------------" );
		char c1='汉';
		System.out.println(" \'"+c1+"\'字符");  

        int i1='汉';
		System.out.println("汉(unicode编码格式)(10进制): "+i1);//'汉'字符的编码：一个整数
		System.out.printf("汉(unicode编码格式)(16进制):  %x ",i1);//将'汉'字符以16进制格式显示
		System.out.println( );
		String str=Integer.toHexString(i1); //将'汉'字符的整形编码转换为16进制的字符串
		System.out.println("汉(unicode编码格式)(16进制): "+str); 
		System.out.println( );
        

		//System.out.println("-------------------------------------" );


		char c2='a';
		System.out.println(" \'"+c2+"\'字符");

		int i2='a';
		System.out.println("a(unicode编码格式)(10进制): "+i2);//'a'字符的编码：一个整数
		System.out.printf("a(unicode编码格式)(16进制):  %x",i2);//将'a'字符以16进制格式显示
		System.out.println( ); 
		String str2=Integer.toHexString(i2); //将'a'字符的整形编码转换为16进制的字符串
		System.out.println("a(unicode编码格式)(16进制): "+str2); 
		System.out.println( );

		System.out.println("-------------prn1------------------------" );


   }

   public static void prn2() throws Exception{
	   System.out.println();
	   System.out.println();
	    System.out.println("-------------prn2------------------------" );


      //byte[] bytes='a'.getBytes("unicode");//错误，必须为String
		byte[] bytes1="a".getBytes("unicode");  //将字符串"a"按照unicode编码格式转换
		System.out.print("\"a\"(unicode编码格式):  " );
		for (int i=0; i<bytes1.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes1[i]);
		}
		System.out.println( );
		System.out.println("-------------------------------------" );


		byte[] bytes2="汉".getBytes("unicode");  //将字符串"汉"按照unicode编码格式转换
		System.out.print("\"汉\"(unicode编码格式):  " );
		for (int i=0; i<bytes2.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes2[i]);
		}
		System.out.println( );
		System.out.println("---------------prn2----------------------" ); 
   }


   public static void prn3() throws Exception{
	   System.out.println();
	   System.out.println();
	   System.out.println("---------------prn3----------------------" ); 
   

        byte[] bytes3="a".getBytes("ascii");  //将字符串"a"按照ascii编码格式转换
		System.out.print("\"a\"(ascii编码格式):  " );
		for (int i=0; i<bytes3.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes3[i]);
		}
		System.out.println( );
		//System.out.println("-------------------------------------" );

        /*
		byte[] bytes4="汉".getBytes("ascii");  //汉字没有ascii编码
		System.out.print("汉:  " );
		for (int i=0; i<bytes4.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes4[i]);
		}
		System.out.println( );
		
		System.out.println("-------------------------------------" );
        */
        System.out.println("---------------prn3----------------------" ); 
   
   }


  public static void prn4()throws Exception {
	  System.out.println();
	  System.out.println();

      System.out.println("---------------prn4----------------------" ); 
   
      byte[] bytes4="a".getBytes("GBK");  //将字符串"a"按照GBK编码格式转换:unicode编码格式转换成GBK编码格式
		System.out.print("\"a\"(GBK编码格式):  " );
		for (int i=0; i<bytes4.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes4[i]);
		}
		System.out.println( );
		//System.out.println("-------------------------------------" );


		byte[] bytes5="汉".getBytes("GBK");  //将字符串"汉"按照GBK编码格式转换:unicode编码格式转换成GBK编码格式
		System.out.print("\"汉\"(GBK编码格式):  " );
		for (int i=0; i<bytes5.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes5[i]);
		}
		System.out.println( );
		System.out.println("-----------------prn4--------------------" );

  }


  public static void prn5() throws Exception{
	  System.out.println();
	  System.out.println();
     System.out.println("----------------prn5---------------------" );

     byte[] bytes6="ab".getBytes("unicode");  //将字符串"a"按照GBK编码格式转换:unicode编码格式转换成GBK编码格式
		System.out.print("\"ab\"(unicode编码格式):  " );
		for (int i=0; i<bytes6.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes6[i]);
		}
		System.out.println( );
		//System.out.println("-------------------------------------" );


		byte[] bytes7="汉字".getBytes("unicode");  //将字符串"汉"按照GBK编码格式转换:unicode编码格式转换成GBK编码格式
		System.out.print("\"汉字\"(unicode编码格式):  " );
		for (int i=0; i<bytes7.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes7[i]);
		}
		System.out.println( );
		System.out.println("---------------prn5----------------------" ); 

  }


  public static void prn6() throws Exception{
	  System.out.println();
	  System.out.println();

    System.out.println("---------------prn6----------------------" );

    byte[] bytes8="ab".getBytes("GBK");  //将字符串"a"按照GBK编码格式转换:unicode编码格式转换成GBK编码格式
		System.out.print("\"ab\"(GBK编码格式):  " );
		for (int i=0; i<bytes8.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes8[i]);
		}
		System.out.println( );
		//System.out.println("-------------------------------------" );


		byte[] bytes9="汉字".getBytes("GBK");  //将字符串"汉"按照GBK编码格式转换:unicode编码格式转换成GBK编码格式
		System.out.print("\"汉字\"(GBK编码格式):  " );
		for (int i=0; i<bytes9.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes9[i]);
		}
		System.out.println( );
		System.out.println("---------------prn6----------------------" );
  }




  public static void prn7() throws Exception{
	  System.out.println();
	  System.out.println();
     System.out.println("----------------prn7---------------------" );

     byte[] bytes10="汉".getBytes("utf-16le");  //将字符串"汉"按照utf-16le编码格式转换
		System.out.print("\"汉\"(utf-16le编码格式):  " );
		for (int i=0; i<bytes10.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes10[i]);
		}
		System.out.println( );
		//System.out.println("-------------------------------------" );

		 byte[] bytes11="汉".getBytes("utf-16be");  //将字符串"汉"按照utf-16be编码格式转换
		System.out.print("\"汉\"(utf-16be编码格式):  " );
		for (int i=0; i<bytes11.length ;i++ )
		{
			System.out.printf("第%d个字节: %x ",i+1,bytes11[i]);
		}
		System.out.println( );
		System.out.println("------------prn7-------------------------" );

  }
	public static void main(String[] args) throws Exception	{
		 
		 
		prn1(); 
		prn2(); 
		prn3();
		prn4();
		prn5();
		prn6();
		prn7();
		 
	}
}
