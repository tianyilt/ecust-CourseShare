public class Student{

	private int age=0;
	public void setAge(int tempAge){
		age=tempAge;
	}
	public int getAge(){
		return age;
	}
		 
	public static void main(String[] args){
		System.out.println("Hello World!");
		Student zhang=new Student();
		zhang.setAge(1);
		System.out.println("zhang.getAge():"+ zhang.getAge()); 
		zhang.setAge(2);
		System.out.println("zhang.getAge():"+ zhang.getAge());
	}
}
