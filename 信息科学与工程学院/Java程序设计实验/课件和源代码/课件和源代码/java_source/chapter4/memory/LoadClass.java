class HelloWorld
{
	public int i=0;
}
public class  LoadClass
{
   
	public static void main(String[] args)  throws Exception
	{
		/*
		Class c1=null; //类Class的对象c1 
		c1=ClassLoader.getSystemClassLoader().loadClass("HelloWorld" );
		HelloWorld h=(HelloWorld)c1.newInstance();
		h.i=3;
		System.out.println(h.i);
		*/
       Class c1=null; //类Class的对象c1 
		c1=ClassLoader.getSystemClassLoader().loadClass("Teacher" );






		 
	}
}
