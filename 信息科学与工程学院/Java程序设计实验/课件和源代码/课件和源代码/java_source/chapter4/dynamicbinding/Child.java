class  Parent{
	public String str="Parent";
	public void prn(){ System.out.println(str);}
	public void prn1(){ System.out.println(str);}	 
}
public class Child extends Parent{
    public String str="Child";
	public void prn1(){ System.out.println(str);}
	public static void main(String[] args) 	{
		Parent parent=new Parent();
        parent.prn1();
		parent.prn();

		System.out.println("------以下体现了动态绑定和静态绑定--");		
		Child child=new Child();
		child.prn1();
		child.prn();
		System.out.println(child.str);

        System.out.println("----以下体现了多态-----------------");
        parent=child;
        parent.prn1();
		parent.prn();		
		System.out.println(parent.str);		 
	}
}
