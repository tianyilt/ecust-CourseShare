interface BoxInterface<T> {  
     // private T t; 
     public void add(T t) ;
     public T get()   ;
}
class Box<T> implements BoxInterface<T>{
	 private T t; 
	 public void add(T t) {  this.t = t;     } 
     public T get() {     return t;      }  
} 
class Employee{
	private int age;
	public void setAge(int age){this.age=age;}
	public int getAge(){return age;}
} 
public class TestGenericsInterface{
	public static void main(String[] args) {
          Employee tom=new Employee( );
		  tom.setAge(20);

          Box<Employee> myBox=new Box<Employee>(); 
		  myBox.add(tom); 
		  Employee rose=  myBox.get( );//不需要Cast
		  System.out.println(rose.getAge());
		  System.out.println(myBox.toString());

		  BoxInterface<Employee> myBox3=new Box<Employee>(); 
		  myBox3.add(tom); 
		 // Employee sun=(Employee)  myBox3.get( );//不需要Cast
		 Employee sun=   myBox3.get( );//不需要Cast
		  System.out.println(sun.getAge());  
	} 
}
