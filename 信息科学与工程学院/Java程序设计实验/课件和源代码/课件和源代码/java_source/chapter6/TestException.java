public class TestException{
  public static void main(String[] args){
	 try {
		    try{
		       int i=1/0;
	          }catch(ArrayIndexOutOfBoundsException e){
		         System.out.println("error1"+e);
	          }
	      }catch(ArithmeticException e){
		     System.out.println("error2 "+e);
	     }
   }

}
