
 
 

public class  ChildPublicClass extends PublicClass
{

    public void test(){

      	PublicClass publicClass=new PublicClass();
      //  DefaultClass defaultClass=new DefaultClass();
		//---------------------------------------- 
        

		//------在同包中的子类访问父类中成员， 
		//---   除了private成员不能被访问外，其它成员都能被访问
        /*
		public int age;
        protected String name;
        float x;
        private boolean y;
		*/

		 publicClass.age=1;
		 publicClass.name="11";  
		 publicClass.x=1.0f;   
		 publicClass.y=true;  //不能访问


         //------在同包中的子类 ， 
		 //--- 继承了父类中的publi、protected，default成员,而private没有继承 
		 this.age=2;
		 this.name="333";
         this.x=2.0f;    
         this.y=false;  //不能访问
        /*
        defaultClass.age=1;
		defaultClass.name="11";
		defaultClass.x=1.0f;
		defaultClass.y=true;
		*/

	}
	public static void main(String[] args) 
	{
		ChildPublicClass childPublicClass=new ChildPublicClass();
        childPublicClass.test();
        
		 childPublicClass.name="22";
		 childPublicClass.x=3.0f;  
         childPublicClass.y=false;  //不能访问
	}
}
