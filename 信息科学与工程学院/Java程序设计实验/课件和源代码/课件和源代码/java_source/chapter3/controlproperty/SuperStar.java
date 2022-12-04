public class  SuperStar{
      private String name;
      private int age;
	  public SuperStar(){
	  }
	  public SuperStar(String name2,int age2){
         name=nam2;
		 age=age2;
	  }
      public int getAge(){ 	//接口 
		   int tempAge=makeUp(40);//化妆后的年龄
		   return tempAge; 
	   }
	  public void setAge(int age2){  //接口
		  age=age2; 
	  }
	  private int makeUp(int age2){	//化妆	   
		  return  age2;
	  }
}

 