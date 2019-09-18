class Parent{
  int x=1,y=2;
  void show(){   System.out.println(x+" " +y);  }
}
class Child extends Parent{
  int y=3,z=4;
  void show(){   System.out.println(x+" "+y+" "+z);  }
}
public class TestDowncasting{
  public static void main(String[] args){
    Parent p1=new Parent();
    Child  c1=new Child();
	Child c2=null;
    p1=(Parent)c1;
    if( p1 instanceof Child ){ c2=(Child)p1; }
    c2.show();
    }
 }
