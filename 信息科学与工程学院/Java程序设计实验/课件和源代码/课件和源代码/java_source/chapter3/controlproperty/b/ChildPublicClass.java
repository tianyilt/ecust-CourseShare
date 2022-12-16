
package controlproperty.b;
import controlproperty.a.*;
//import controlproperty.a.PublicClass;
//import controlproperty.a.DefaultClass;

public class  ChildPublicClass extends PublicClass
{

    public void test(){

      //---在不同包中，只可以访问public  类-------------------------------------
		PublicClass publicClass=new PublicClass();
      //  DefaultClass defaultClass=new DefaultClass();
		//---------------------------------------- 
        

		//------在不同包中的子类访问父类中成员， 
		//---   除了public成员能被访问外，其它成员都不能被访问
        /*
		public int age;
        protected String name;
        float x;
        private boolean y;
		*/

		 publicClass.age=1;
		 publicClass.name="11"; //不能访问
		 publicClass.x=1.0f;  //不能访问
		 publicClass.y=true;  //不能访问


         //------在不同包中的子类 ， 
		 //--- 只继承了父类中的publi、protected成员,而default,private没有继承 
		 this.name="333";
         this.x=2.0f;   //不能访问
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
		 childPublicClass.x=3.0f; //不能访问
         childPublicClass.y=false;  //不能访问
	}
}
