public class  TestMethodException{
	public void a() throws Exception{
		 throw new Exception();
	}

	public static void main(String[] args){
		TestMethodException t1=new TestMethodException();
		try{
		   t1.a();
		 }catch(Exception e){ 
		   System.out.println("Exception error");
		 }
	 }
}
