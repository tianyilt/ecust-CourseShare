//C包中的TestPackage.java
package C;    //创建C包,并把TestPackage.class放至C包   
                       // 的名空间里
import A.*;          //加载A包
import B.*;          //加载B包

public class  TestPackage{
  public static void main(String[] args){
     A.T1  at1=new A.T1();
     B.T1  bt1=new B.T1();
     T2    t2=new T2();
     at1.p1();
     bt1.p1();
     bt1.p2();
     t2.p1();      
     }
}
