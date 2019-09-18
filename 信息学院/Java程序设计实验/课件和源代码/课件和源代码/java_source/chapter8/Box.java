class Employee{
	private int age;
	public void setAge(int age){this.age=age;}
	public int getAge(){return age;}
}

public class Box{
	private Object object;
	public Box( ){ 		super();	}
	public Box(Object object){		super();		this.object=object;	}

	public void add(Object object){this.object=object;}
	public Object get(){return object;} 

	public static void main(String[] args) {
		 
        String strObject=null;
		Employee tom=new Employee( );
		tom.setAge(20);
		Box myBox=new Box();
		myBox.add(tom);//upcasting
        //strObject=(String)myBox.get( ); //编译正确，运行报错    //有没有一种技术可以在编译期间，就可以找出错误 ？泛型
		//Employee jack=  myBox.get( ); //编译报错，     Object->String 需要downcasting
		Employee jack= (Employee)myBox.get( );//编译正确，运行正确
		System.out.println(jack.getAge());
	}
}
