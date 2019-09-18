package c;
import a.*;
import b.*;
public class C 
{
	 public static void main(String[] args){

	   System.out.println("---------------默认 A 类-----------------");
       /*
	   A a=new A();  //不能访问不同包中的默认修饰的类
	    
	   a.x1=1;
	   a.x2=2;
	   a.x3=3;
	   a.x4=4;
	   
	   System.out.println(a.x1);
	   System.out.println(a.x2);
	   System.out.println(a.x3);
	   System.out.println(a.x4);
       */

	   System.out.println("---------------public B  类-----------------");
       B b=new B();  //只能访问不同包中public修饰的类
	   b.y1=1;       //在能访问到类的前提下，非子类只能访问该类中public修饰的成员
	   /*
	   b.y2=2;
	   b.y3=3;
	   b.y4=4;
	   */       
	   
	   System.out.println(b.y1);
	   /*
	   System.out.println(b.y2);
	   System.out.println(b.y3);
	   System.out.println(b.y4);
	   */


	 }
}
