public class TestTryCatch2{
  public static void main(String[] args){
    int i=3;
    for(int j=1;j>=-1;j--){
        try{
            System.out.println("try block entered");
	System.out.println(i/j);  
	System.out.println("Ending try block");
	}
           catch(ArithmeticException e){
	         System.out.println("Arithmetic Exception caugth");
                }
            finally{
	         System.out.println("finally block is executed ");
                }
        System.out.println("After try block");
       }
   }
}   

