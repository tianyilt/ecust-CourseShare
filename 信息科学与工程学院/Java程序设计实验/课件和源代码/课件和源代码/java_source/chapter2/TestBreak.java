class  TestBreak
{  
	public static void main(String[] args) 
	{    
  outside:
	  // System.out.println("hello3" );
     for(int i=1;i<4;i++){
		 for(int j=1;j<=5;j++){
			 System.out.println("hello"+i+j);
			 if( true ){
			     break outside;
			    }
            System.out.println("hello2" );
		  }

	 } 
	   System.out.println("hello3" );
	 
     }

	}