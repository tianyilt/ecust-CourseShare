
import java.util.ArrayList;
class Employee{
	private int age;
	public void setAge(int age){this.age=age;}
	public int getAge(){return age;}
}
public class TestArrayList{   
	public static void main(String[] args) 	{
		ArrayList<Employee>  list=new ArrayList<Employee> ();

		for(int i=0;i<24;i++){
           Employee e=new Employee();
		   e.setAge(i);
		   list.add(e);
		}		

		Employee e=null;
		for(int i=0;i<24;i++){ 
		   e=list.get(i);
		   System.out.print(" "+e.getAge());
		}

        System.out.println( );

		for(Employee e2: list){
             System.out.print(" "+e2.getAge());
		}		 
	}
}
