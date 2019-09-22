class   TestFinally
{   
	 
	public static void main(String[] args) 
	{


        try{
		 System.out.println( 1/0);
		} finally{
             System.out.println("finally statements executed ");
		}
        System.out.println("after finally statements");
	}
}
