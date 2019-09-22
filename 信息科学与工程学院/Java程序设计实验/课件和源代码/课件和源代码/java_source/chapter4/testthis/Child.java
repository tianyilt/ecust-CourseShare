class  Parent{	
	public void pr1(){		
		System.out.println(this);	 
	} 
}
public class Child extends Parent{
	public void pr2(){		
		System.out.println(this);	 
		//System.out.println(super);//语法错误 super不是对象
	}
	public static void main(String[] args) 	{
		 Child c1=new Child();
		 c1.pr1();// 打印结果为Child@1x095da
		 c1.pr2();// 打印结果为Child@1x095da:和pr1打印的内容一样
	}
}
