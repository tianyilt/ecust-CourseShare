package d;
import a.*;
import b.*;

//不能继承别的包中用默认属性修饰的类
/*
class  D extends A
{
	  
	public void prn(){
      System.out.println("x1:"+x1+"  x2: "+x2+"  x3:"+x3+"  x4:"+x4);
	}
}
*/

//能继承别的包中用public属性修饰的类
class  E extends B
{
	public void prn(){
	  //不能访问默认、私有属性修饰的成员,只能访问public ,protected修饰的成员
	  y1=1;  //public
	  y2=2;  //protected
	  // y3=3; //默认
	  // y4=4; //私有
	   
      System.out.println("y1:"+y1+"  y2: "+y2 );
     // System.out.println( "  y3:"+y3+"  y4:"+y4);
	}  
}

public class Test
{   public static void main(String[] args){
      //D d=new D();
	 // d.prn();
	  E e=new E();
	  e.prn();

    }
}
