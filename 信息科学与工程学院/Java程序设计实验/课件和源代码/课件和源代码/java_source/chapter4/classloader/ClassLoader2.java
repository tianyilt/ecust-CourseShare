class  A{
	public static int i=getI();
	public static int  getI(){ System.out.println("geti!"); return 1;}
	public   int  getG(){ System.out.println("getg!"); return 1;}
	 
}


  class  B extends A{
	public static int j=getj();
	public static int  getj(){ System.out.println("getj!"); return 1;}
	public static void main(String[] args) 
	{
		 
	}
}

public class ClassLoader2{

  public static void main(String[] args)  
	{ 
	   try{
		Class c=ClassLoader.getSystemClassLoader().loadClass("A");

		 // A a=(A)c.newInstance();
		// System.out.println(a.getG()); 
	   }catch(Exception e){
	      System.out.println(e);
	   }
	  // B b=null;
	  // b=new B();
		 
	}
}