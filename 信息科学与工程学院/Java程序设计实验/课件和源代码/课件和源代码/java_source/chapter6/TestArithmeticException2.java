
class  TestArithmeticException2{
    public void method(){ 
		 int i=5;
		 int j=0;
		 System.out.println("before Excepton"); 
		 j=1/(i-5);  
		 System.out.println("after Excepton"); 
	} 
	public static void main(String[] args) {
		 TestArithmeticException2 exception=new TestArithmeticException2();
		 System.out.println("before exception.method()");  
		 exception.method(); 
		 System.out.println("after exception.method()"); 
	}
}
