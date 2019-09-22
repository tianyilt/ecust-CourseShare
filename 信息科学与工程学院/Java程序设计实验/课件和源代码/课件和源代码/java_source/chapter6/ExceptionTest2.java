class   ExceptionTest2
{   
	 
	public static void main(String[] args) 
	{


        try{
		 System.out.println( 1/0);
		}catch(Exception e){
             System.out.println("Exception is caught");
		}catch(ArithmeticException e){
             System.out.println("ArithmeticException is caught");
		}

	}
}
