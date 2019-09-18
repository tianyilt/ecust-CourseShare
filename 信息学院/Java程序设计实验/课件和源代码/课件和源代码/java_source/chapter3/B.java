class B 
{ int s=getS();
  static int t=getT();
  
	{
		System.out.println("Hello World!");
	}
	public static int getS(){
		System.out.println("s:");
		return 1;
	}
   public static int getT(){
		System.out.println("t:");
		return 2;
	}
   {
		System.out.println(" block ");
	}
	public B(){
		System.out.println("new object  ");
	}

	public static void main(String[] args) 
	{
		  System.out.println("new object before");
		new B();
		  System.out.println("new object after");
	}
}
