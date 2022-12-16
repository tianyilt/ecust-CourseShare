public class  TestString
{
	public static void main(String[] args) 
	{
		try{
		String str1="abcdef华东理工大学";
		byte[] b=str1.getBytes("GBK");
		String str2=new String(b,"GBK");
		System.out.println( str2 );
		System.out.println(  str2);
		}catch(Exception e){
               e.printStackTrace();
		}

		try{
		String str3="abcdef华东理工大学";
		byte[] b=str3.getBytes("unicode");
		String str4=new String(b,"GBK");   //乱码
		System.out.println( str3 );
		System.out.println(  str4);
		}catch(Exception e){
               e.printStackTrace();
		}
	}
}
