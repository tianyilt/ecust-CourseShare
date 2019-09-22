class Box<T> {      
   private    T t; 
   // private   static T t2;  //static 无法修饰泛型类型变量

   public void add(T t) {  this.t = t;     } 
   public T get() {     return t;      }

   public <U> void printClassName(U u){ 
      System.out.println("T: " + t.getClass().getName()); 
      System.out.println("U: " + u.getClass().getName()); 
    }  
    
	/*
   public static    void printClassName2( ){ 
	    T a=null; 
        System.out.println("T: " + a.getClass().getName());  
    }  
	*/
	 //static方法无法访问泛型类型变量
}
public class TestStaticGeneric {
	public static void main(String[] args) {
      Integer intObject=new Integer(1);
	  String  strObject=new String("tom");
	  Box<String> mybox=new Box<String>();
	  mybox.add(strObject);
	  mybox.<Integer>printClassName(intObject);
	  mybox.printClassName(intObject);//type inference,可省掉<U> 
	}
}