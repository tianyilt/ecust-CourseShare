 class AnonymousParent{
	AnonymousParent(){
	 System.out.println("Anonymous Parent");
	 }
 }

public class  AnonymousClassDemo{  
	
	public  void method(){
		System.out.println("  before AnonymousClass");
		//以下语句产生一个匿名类，并生该类的一个对象。
		 new AnonymousParent(){ 
			      private int i=1;
			      public void prtI(){
				    System.out.println(i);
			       }
		        }; 
		//匿名类定义的结尾
	   System.out.println("after AnonymousClass ");
	};	

	public static void main(String[] args){
		(new AnonymousClassDemo()).method();
	}
}

