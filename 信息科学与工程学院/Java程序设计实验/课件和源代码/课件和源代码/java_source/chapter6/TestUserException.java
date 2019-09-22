class  userException extends Exception{
    userException(){
		super();
	}
	userException(String s){
		super(s);
	}
	public String toString(){
		return "userException";
	}
}

public class  TestUserException{
	public static void  main(String[] args){
		try{
			throw new userException();
		 }catch(userException e){
			 System.out.println(e.toString());
		  }
		  catch(Exception  e){
             System.out.println( "Exception");
			 e.printStackTrace();
		  }
	}

}
