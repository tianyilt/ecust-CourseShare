class  Student 
{

	private String name; 
	private int age;
	public  Student(){
	}
	public   Student(String name2,int age2){
     name=name2;
	 age=age2;
	} 
	public int getAge(){return age;}
	public void setAge(int age2){age=age2;}
}

public class  TestStudent
{ 
	public static void  ChangeStudent(Student stu){ 
	   int age=stu.getAge();
	   age++;
	   stu.setAge(age); 
	   return;
    } 
	public  static void ChangeAge(int age){
		age++;
		return;
	}

	public static void main(String[] args) 
	{
		int age=10;
		ChangeAge(age);
		System.out.println("age:"+age);

		Student tom=new Student("tom",10);
        ChangeStudent(tom);
        System.out.println("tom age:"+tom.getAge());
	}
}
