class  InnerClassInBlock{ 
	// InnerClass i;  不能访问定义在块中的内部类。
	{
		System.out.println("  before InnerClass");
		//InnerClass inner=new InnerClass(); 不能在未定义内部类时，就使用它
		class InnerClass{ 
			private int i=1;
			public void prtI(){
				System.out.println(i);
			}
		};

		InnerClass inner=new InnerClass();
		inner.prtI();

		System.out.println("after InnerClass ");
	}	


	public static void main(String[] args){
		new OuterClass();
	}
}
