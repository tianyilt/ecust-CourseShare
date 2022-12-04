
package controlproperty.b;
import controlproperty.a.*;
//import controlproperty.a.PublicClass;
//import controlproperty.a.DefaultClass;

public class  TestControlProperty
{

    public void test(){

      //---在不同包中，只可以访问public  类-------------------------------------
		PublicClass publicClass=new PublicClass();
      //  DefaultClass defaultClass=new DefaultClass();
		//---------------------------------------- 
        

		//------在不同包中，在能访问类的条件下， 
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

        /*
        defaultClass.age=1;
		defaultClass.name="11";
		defaultClass.x=1.0f;
		defaultClass.y=true;
		*/

	}
	public static void main(String[] args) 
	{
		TestControlProperty testControlProperty=new TestControlProperty();
        testControlProperty.test();
 
	}
}
