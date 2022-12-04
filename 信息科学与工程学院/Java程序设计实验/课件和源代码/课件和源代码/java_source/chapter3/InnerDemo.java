class  Outer{  
  private String outer_x="outer";
  void prtOuterString(){
	  System.out.println(outer_x);
	  // System.out.println(inner_x);  不能直接访问内部类的成员变量
  }
  void prtInnerString(){
	  Inner i=new Inner();
	  i.inner_x="outer inner";  //　能访问内部类中的成员，尽管它是private属性
	  i.prtInnerString2();
   }

  //以下为内部类 Inner
  class Inner{
	 private String inner_x="inner";
	 void prtInnerString2(){
	   System.out.println(inner_x);
     }	   
	 void prtOuterString2(){
        System.out.println(outer_x);  //能直接访问外部类中的成员，尽管它是private属性
	 }
  } 
 //

}

public class InnerDemo{	 
   public static void main(String[] args){    
          Outer o=new Outer();
	      o.prtOuterString(); 
		  o.prtInnerString();		  
	      //Inner i=new Inner();不能直接访问内部类
	      //i.prtInnerString();　　

	      //Outer.Inner i=new Outer.Inner();　格式不对
	      //            i.prtInnerString();
          //Outer.Inner i=new o.Inner(); 　　　格式不对
	      //           i.prtInnerString();
	      Outer.Inner i=o.new  Inner() ;
	      i.prtInnerString2();
		  i.prtOuterString2();
   }
}