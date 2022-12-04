public class  TestControlProperty
{
    public void test(){

      //---在同一个包中，可以访问public ,default类-------------------------------------
		PublicClass publicClass=new PublicClass();
        DefaultClass defaultClass=new DefaultClass();
		//---------------------------------------- 
        

		//------在同一个包中，在能访问类的条件下， 
		//---   除了private成员不能访问外，其它成员都能被访问
        /*
		public int age;
        protected String name;
        float x;
        private boolean y;
		*/

		publicClass.age=1;
		publicClass.name="11";
		publicClass.x=1.0f;
		publicClass.y=true; //error

 
        defaultClass.age=1;
		defaultClass.name="11";
		defaultClass.x=1.0f;
		defaultClass.y=true;//error

	}

	public static void main(String[] args) 
	{
		 
		 
        TestControlProperty testControlProperty=new TestControlProperty();
        testControlProperty.test();

	}
}
